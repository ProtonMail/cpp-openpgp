#include <openpgp/decrypt.h>
#include <utilities/PKCS1.h>
#include <openpgp/decrypt.h>
#include <utilities/mpi.h>
#include <exception/pgp_exception.h>
#include <utilities/base64.h>
#include <openpgp/private_key.h>
#include <exception/pgp_exception_define.h>
#include <exception/pgp_exception.h>


using namespace ProtonMail::pgp;


std::string pka_decrypt(const uint8_t pka, std::vector <std::string> & data, const std::vector <std::string> & pri, const std::vector <std::string> & pub){
    if (pka < 3){   // RSA
        return  mpitoraw(RSA_decrypt(data[0], pri, pub));
    }
    if (pka == 16){ // ElGamal
        return "";//ElGamal_decrypt(data, pri, pub);
    }
    else{
        std::stringstream s; s << static_cast <unsigned int> (pka);
        throw std::runtime_error("Error: PKA number " + s.str() + " not allowed or unknown.");
    }
    return ""; // should never reach here; mainly just to remove compiler warnings
}

PGPMessage decrypt_data(const uint8_t sym, const PGPMessage & m, const std::string & session_key, const bool writefile, const PGPPublicKey::Ptr & verify){
    // currently packet tag being operated on
    uint8_t packet;

    // get blocksize of symmetric key algorithm
    unsigned int BS = Symmetric_Algorithm_Block_Length.at(Symmetric_Algorithms.at(sym)) >> 3;

    // Find encrypted data
    std::string data = "";

    // find start of encrypted data
    unsigned int i = 0;
    std::vector <Packet::Ptr> packets = m.get_packets();
    while ((i < packets.size()) && (packets[i] -> get_tag() != 9) && (packets[i] -> get_tag() != 18)){
        i++;
    }

    // copy initial data to string
    if (packets[i] -> get_tag() == 9){
        data = packets[i] -> raw();
        Tag9 tag9(data);
        data = tag9.get_encrypted_data();
        packet = 9;
    }
    else if (packets[i] -> get_tag() == 18){
        data = packets[i] -> raw();
        Tag18 tag18(data);
        data = tag18.get_protected_data();
        packet = 18;
    }
    else{
        throw std::runtime_error("Error: No encrypted data found.");
    }

    // does not work
    // // if the packet was a partial start
//     if (packets[i] -> get_partial()){
//         i++;
//         // add the rest of the data
//         for(; i < packets.size(); i++){
//             std::string raw = packets[i] -> raw();
//             Partial::Ptr part = std::make_shared <Partial> (raw);
//             data += part -> get_stream();
//
//             // if the current packet is parital end, break after adding data
//             if (packets[i] -> get_partial() == 3){
//                 break;
//             }
//         }
//     }

    if (!data.size()){
        throw std::runtime_error("Error: No encrypted data packet(s) found.");
    }

    // decrypt data
    if (sym == 9)
        data = use_OpenPGP_CFB_decrypt(data, session_key);
    else
        data = use_OpenPGP_CFB_decrypt(sym, packet, data, session_key);

    //std::cout << data << std::endl;
    
    // strip extra data
    if (packet == 18){ // Symmetrically Encrypted Integrity Protected Data Packet (Tag 18)
        std::string checksum = data.substr(data.size() - 20, 20);   // get given SHA1 checksum
        data = data.substr(0, data.size() - 20);                    // remove SHA1 checksum
        if (use_hash(2, data) != checksum){                         // check SHA1 checksum
            throw std::runtime_error("Error: Given checksum and calculated checksum do not match.");
        }
        data = data.substr(0, data.size() - 2);                     // get rid of \xd3\x14
    }
    data = data.substr(BS + 2, data.size() - BS - 2);               // get rid of prefix
    //std::cout << data << std::endl;
    // decompress and parse decrypted data
    return PGPMessage(data, true);
}

std::string decrypt_pm_pka(const PGPSecretKey & pri, const std::string & passphrase, const std::string & msg)
{
    return "";
}

std::string decrypt_pka(const PGPSecretKey & pri, const PGPMessage & m, const std::string & passphrase, const bool writefile, const PGPPublicKey::Ptr & verify){
    bool isDebugMode = false;
    
    if ((m.get_ASCII_Armor() != 0)/* && (m.get_ASCII_Armor() != 3) && (m.get_ASCII_Armor() != 4)*/){
        throw std::runtime_error("Error: No encrypted message found.");
    }

    if (pri.get_ASCII_Armor() != 2){
        throw std::runtime_error("Error: No Private Key found.");
    }

    // reused variables
    uint8_t packet = 0;                         // currently used packet tag
    std::string data;                           // temp stuff
    std::string session_key;                    // session key
    uint8_t sym;                                // symmetric key algorithm used to encrypt original data

    // find corresponding secret key
    Tag5::Ptr sec = 0;
    std::vector <std::string> session_key_mpi;
    uint8_t pka = 0;
    
    // find session key packet; should be first packet
    for(Packet::Ptr const & p : m.get_packets()){
        if ((p -> get_tag() == 1) || (p -> get_tag() == 3)){
            data = p -> raw();
            packet = p -> get_tag();
            if (packet == 1)
            {
                if (p -> get_tag() == 1) {
                    Tag1 tag1(data);
                    sec = find_decrypting_key(pri, tag1.get_keyid());
                    if (!sec){
                        continue;
                    }
                    pka = tag1.get_pka();
                    session_key_mpi = tag1.get_mpi();
                    break;
                }
            }
        }
    }
    
    if (packet == 1) {
    }
    // return symmetrically-encrypted-key decrypted data
    else if (packet == 3){
        return decrypt_sym(m, passphrase);
    }
    else{
        std::stringstream s; s << Packet_Tags.at(packet) << " (Tag " << static_cast <unsigned int> (packet) << ").";
        // throw std::runtime_error("Error: Expected Public-Key Encrypted Session Key Packet (Tag 1). Instead got " + s.str());
    }
    
    // Public-Key Encrypted Session Key Packet (Tag 1)
    // Tag1 tag1(data);
    if (!sec){
        throw std::runtime_error("Error: Correct Private Key not found.");
    }
    
    std::vector <std::string> pub_mpi = sec -> get_mpi();
    std::vector <std::string> pri_mpi = decrypt_secret_key(sec, passphrase);
    
    if (isDebugMode) {
        std::cout<< "D: " << hexlify( pri_mpi[0]) << std::endl;
        std::cout<< "P: " << hexlify(pri_mpi[1]) << std::endl;
        std::cout<< "Q: " << hexlify(pri_mpi[2]) << std::endl;
        std::cout<< "U: " << hexlify(pri_mpi[3]) << std::endl;
    }
    
    // get session key
    session_key = zero + pka_decrypt(pka, session_key_mpi, pri_mpi, pub_mpi);     // symmetric algorithm, session key, 2 octet checksum wrapped in EME_PKCS1_ENCODE
    session_key = EME_PKCS1v1_5_DECODE(session_key);                              // remove EME_PKCS1 encoding
    sym = session_key[0];                                                         // get symmetric algorithm
    std::string checksum = session_key.substr(session_key.size() - 2, 2);         // get 2 octet checksum
    session_key = session_key.substr(1, session_key.size() - 3);                  // remove both from session key
    uint16_t sum = 0;
    for(char & c : session_key){                                                  // calculate session key checksum
        sum += static_cast <uint8_t> (c);
    }
    if (unhexlify(makehex(sum, 4)) != checksum){                                  // check session key checksums
        throw ProtonMail::pgp_exception(ProtonMail::PM_DECRYPT_SESSION_SUMCHECK_NOT_MATCH, "Error: Calculated session key checksum does not match given checksum.");
    }
    
    sec.reset();
    // std::cout << hexlify(session_key) << std::endl;
    
    // decrypt the data with the extracted key
    PGPMessage decrypted = decrypt_data(sym, m, session_key, writefile, verify);
    
    std::string out = "";
    // if signing key provided, check the signature
    if (verify){
        // out = "Message was" + std::string(verify_message(*verify, decrypted)?"":" not") + " signed by key " + hexlify(verify -> keyid()) + ".\n";
    }
    
    // extract data
    for(Packet::Ptr const & p : decrypted.get_packets()){
        if (p -> get_tag() == 11){
            std::string raw = p -> raw();
            Tag11 tag11(raw);
            out += tag11.out(writefile);
        }
    }
    
    return out;
}


std::string decrypt_pka(const PGPSecretKey & pri, const ProtonMail::PMPGPMessage & m, const std::string & passphrase, const bool writefile, const PGPPublicKey::Ptr & verify)
{
    bool isDebugMode = false;
    if(m.get_is_pm_pka())
    {
        PGPMessage pgp_msg = m;
        std::string random_key = decrypt_pka(pri, pgp_msg, passphrase, writefile, verify);
        
        if(isDebugMode)
            std::cout << random_key << std::endl;
        random_key = decode_utf8_base64(random_key);
        if(isDebugMode)
            std::cout << random_key.length() << std::endl;
        if(isDebugMode)
            std::cout << random_key << std::endl;
        
        
        std::string data = use_OpenPGP_CFB_decrypt(9, 9, m.get_encrypt_msg(), random_key, false);
        if(isDebugMode)
            std::cout << data.length() << std::endl;
        if(isDebugMode)
            std::cout << data << std::endl;
        
        //data = base64_decode(data);
        auto data2 = decode_utf8_base64_msg(data);
        
        if(isDebugMode)
        {
            std::cout << data.length() << std::endl;
            std::cout << data << std::endl;
            
            std::cout << data2.length() << std::endl;
            std::cout << data2 << std::endl;
        }
        
        
        return data2;
    }
    else
    {
        PGPMessage pgp_msg = m;
        return decrypt_pka(pri, pgp_msg, passphrase, writefile, verify);
    }
}


std::string decrypt_sym(const PGPMessage & m, const std::string & passphrase, const bool writefile, const PGPPublicKey::Ptr & verify){
    //std::cerr << "Warning: decrypt_sym is untested. Potentially incorrect" << std::endl;

    if ((m.get_ASCII_Armor() != 0)/* && (m.get_ASCII_Armor() != 3) && (m.get_ASCII_Armor() != 4)*/){
        throw std::runtime_error("Error: No encrypted message found.");
    }

    uint8_t packet = 0;                             // currently used packet tag
    std::string data;                           // temp stuff

    // find session key packet; should be first packet
    for(Packet::Ptr const & p : m.get_packets()){
        if ((p -> get_tag() == 1) || (p -> get_tag() == 3)){
            data = p -> raw();
            packet = p -> get_tag();
            break;
        }
    }

    if (packet == 1){
        throw std::runtime_error("Error: Use decrypt_pka to decrypt this data.");
    }
    else if (packet == 3){}
    else{
        std::stringstream s; s << Packet_Tags.at(packet) << " (Tag " << static_cast <unsigned int> (packet) << ").";
        throw std::runtime_error("Error: Expected Symmetric-Key Encrypted Session Key Packet (Tag 3). Instead got " + s.str());
    }

    Tag3 tag3(data);
    data = tag3.get_key(passphrase);
    //std::cout << hexlify(data) << std::endl;
    
    PGPMessage decrypted = decrypt_data(data[0], m, data.substr(1, data.size() - 1), writefile, nullptr);
    
    std::string out = "";
    // extract data
    for(Packet::Ptr const & p : decrypted.get_packets()){
        if (p -> get_tag() == 11){
            std::string raw = p -> raw();
            Tag11 tag11(raw);
            out += tag11.out(writefile);
        }
    }
    return out;

}


std::string decrypt_pka_only_session(const PGPSecretKey & pri, const PGPMessage & m, const std::string & passphrase)
{
    // reused variables
    uint8_t packet = 0;                         // currently used packet tag
    std::string data;                           // temp stuff
    std::string session_key;                    // session key
    uint8_t sym;                                // symmetric key algorithm used to encrypt original data
    
    // find corresponding secret key
    Tag5::Ptr sec = 0;
    std::vector <std::string> session_key_mpi;
    uint8_t pka = 0;
    
    // find session key packet; should be first packet
    for(Packet::Ptr const & p : m.get_packets()){
        if ((p -> get_tag() == 1) || (p -> get_tag() == 3)){
            data = p -> raw();
            packet = p -> get_tag();
            if (packet == 1)
            {
                if (p -> get_tag() == 1) {
                    // Public-Key Encrypted Session Key Packet (Tag 1)
                    Tag1 tag1(data);
                    sec = find_decrypting_key(pri, tag1.get_keyid());
                    if (!sec){
                        continue;
                    }
                    pka = tag1.get_pka();
                    session_key_mpi = tag1.get_mpi();
                    break;
                }
            }
        }
    }
    
    if (packet == 1)
    {
        
    }
    // return symmetrically-encrypted-key decrypted data
    else if (packet == 3){
        return decrypt_sym(m, passphrase);
    }
    else{
        std::stringstream s; s << Packet_Tags.at(packet) << " (Tag " << static_cast <unsigned int> (packet) << ").";
        throw std::runtime_error("Error: Expected Public-Key Encrypted Session Key Packet (Tag 1). Instead got " + s.str());
    }
    
    if (!sec){
        throw std::runtime_error("Error: Correct Private Key not found.");
    }
    
    std::vector <std::string> pub_mpi = sec -> get_mpi();
    std::vector <std::string> pri_mpi = decrypt_secret_key(sec, passphrase);
   
    // get session key
    session_key = zero + pka_decrypt(pka, session_key_mpi, pri_mpi, pub_mpi);     // symmetric algorithm, session key, 2 octet checksum wrapped in EME_PKCS1_ENCODE
    session_key = EME_PKCS1v1_5_DECODE(session_key);                              // remove EME_PKCS1 encoding
    sym = session_key[0];                                                         // get symmetric algorithm
    std::string checksum = session_key.substr(session_key.size() - 2, 2);         // get 2 octet checksum
    session_key = session_key.substr(1, session_key.size() - 3);                  // remove both from session key
    uint16_t sum = 0;
    for(char & c : session_key){                                                  // calculate session key checksum
        sum += static_cast <uint8_t> (c);
    }
    if (unhexlify(makehex(sum, 4)) != checksum){                                  // check session key checksums
        throw ProtonMail::pgp_exception(ProtonMail::PM_DECRYPT_SESSION_SUMCHECK_NOT_MATCH, "Error: Calculated session key checksum does not match given checksum.");
    }
    
    sec.reset();
    
    return session_key;
}



bool check_private_passphrase(const PGPSecretKey &pri, const std::string & passphrase)
{
    // find corresponding secret key
    Tag5::Ptr sec = find_decrypting_key(pri,"", true);
    if (!sec){
        throw std::runtime_error("Error: Correct Private Key not found.");
    }
    
    std::vector <std::string> pub_mpi = sec -> get_mpi();
    std::vector <std::string> pri_mpi = decrypt_secret_key(sec, passphrase);
    
    if (pri_mpi.size() > 0)
        return true;
    
    return false;
}

std::string decrypt_pka_only_sym_session(const PGPMessage & m, const std::string & passphrase)
{
    //std::cerr << "Warning: decrypt_sym is untested. Potentially incorrect" << std::endl;
    
    if ((m.get_ASCII_Armor() != 0)/* && (m.get_ASCII_Armor() != 3) && (m.get_ASCII_Armor() != 4)*/){
        throw std::runtime_error("Error: No encrypted message found.");
    }
    
    uint8_t packet = 0;                             // currently used packet tag
    std::string data;                           // temp stuff
    
    // find session key packet; should be first packet
    for(Packet::Ptr const & p : m.get_packets()){
        if ((p -> get_tag() == 1) || (p -> get_tag() == 3)){
            data = p -> raw();
            packet = p -> get_tag();
            break;
        }
    }
    
    if (packet == 1){
        throw std::runtime_error("Error: Use decrypt_pka to decrypt this data.");
    }
    else if (packet == 3){}
    else{
        std::stringstream s; s << Packet_Tags.at(packet) << " (Tag " << static_cast <unsigned int> (packet) << ").";
        throw std::runtime_error("Error: Expected Symmetric-Key Encrypted Session Key Packet (Tag 3). Instead got " + s.str());
    }
    
    Tag3 tag3(data);
    data = tag3.get_key(passphrase);

    return data;  /// [1 octet symmetric key algorithm] + [session key(s)]
}


std::string decrypt_pka_use_sym_session(const PGPMessage & m, const PGPMessage &key, const std::string & passphrase)
{
    if ((m.get_ASCII_Armor() != 0)/* && (m.get_ASCII_Armor() != 3) && (m.get_ASCII_Armor() != 4)*/){
        throw std::runtime_error("Error: No encrypted message found.");
    }
    
    uint8_t packet = 0;                             // currently used packet tag
    std::string data;                           // temp stuff
    
    // find session key packet; should be first packet
    for(Packet::Ptr const & p : key.get_packets()){
        if ((p -> get_tag() == 1) || (p -> get_tag() == 3)){
            data = p -> raw();
            packet = p -> get_tag();
            break;
        }
    }
    
    if (packet == 1){
        throw std::runtime_error("Error: Use decrypt_pka to decrypt this data.");
    }
    else if (packet == 3){}
    else{
        std::stringstream s; s << Packet_Tags.at(packet) << " (Tag " << static_cast <unsigned int> (packet) << ").";
        throw std::runtime_error("Error: Expected Symmetric-Key Encrypted Session Key Packet (Tag 3). Instead got " + s.str());
    }
    
    Tag3 tag3(data);
    data = tag3.get_key(passphrase);
    
    
    //std::cout << hexlify(data) << std::endl;
    
    PGPMessage decrypted = decrypt_data(data[0], m, data.substr(1, data.size() - 1), false, nullptr);
    
    std::string out = "";
    // extract data
    for(Packet::Ptr const & p : decrypted.get_packets()){
        if (p -> get_tag() == 11){
            std::string raw = p -> raw();
            Tag11 tag11(raw);
            out += tag11.out(false);
        }
    }
    return out;
}




