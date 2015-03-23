#include "encrypt.h"
#include "Tag11.h"
#include "Tag9.h"
#include "Tag18.h"
#include "Tag8.h"
#include "Tag19.h"
#include "Tag1.h"
#include "s2k.h"
#include "Tag3.h"
#include <utilities/mpi.h>
#include "PKCS1.h"
#include "packet.h"
#include "Tag5.h"
#include "Tag2.h"
#include <pgp/PGPKey.h>
#include "revoke.h"
#include <utilities/base64.h>
#include "cfb.h"
#include "BBS.h"

Tag6::Ptr find_encrypting_key(const PGP & k){
    if ((k.get_ASCII_Armor() == 1) || (k.get_ASCII_Armor() == 2)){
        for(Packet::Ptr const & p : k.get_packets()){
            if ((p -> get_tag() == 5) || (p -> get_tag() == 6) || (p -> get_tag() == 7) || (p -> get_tag() == 14)){
                std::string data = p -> raw();
                Tag6::Ptr key(new Tag6(data));
                // make sure key has encrypting keys
                if ((key -> get_pka() == 1) || // RSA
                    (key -> get_pka() == 2) || // RSA
                    (key -> get_pka() == 16)){ // ElGamal
                    return key;
                }
                key.reset();
            }
        }
    }
    return nullptr;
}

//std::vector <std::string> pka_encrypt(const uint8_t pka, std::string data, const std::vector <std::string> & pub){
//
//    if (pka < 3){   // RSA
//        //return {RSA_encrypt(data, pub)};
//    }
//    if (pka == 16){ // ElGamal
//        //return ElGamal_encrypt(data, pub);
//    }
//    else{
//        std::stringstream s; s << static_cast <unsigned int> (pka);
//        throw std::runtime_error("Error: PKA number " + s.str() + " not allowed or unknown.");
//    }
//    return {}; // should never reach here; mainly just to remove compiler warnings
//}

std::vector <std::string> pka_encrypt(const uint8_t pka, const std::string & data, const std::vector <std::string> & pub){
    
 //   std::cout << hexlify(data) << std::endl;
    
    // rawtompi(data);
    if (pka < 3){   // RSA
        return {RSA_encrypt(data, pub)};
    }
    if (pka == 16){ // ElGamal
        //return ElGamal_encrypt(data, pub);
    }
    else{
        std::stringstream s; s << static_cast <unsigned int> (pka);
        throw std::runtime_error("Error: PKA number " + s.str() + " not allowed or unknown.");
    }
    return {}; // should never reach here; mainly just to remove compiler warnings
    
    
}

Packet::Ptr encrypt_data(const std::string & session_key, const std::string & data, const std::string & filename, const uint8_t sym_alg, const uint8_t comp, const bool mdc, const PGPSecretKey::Ptr & signer, const std::string & sig_passphrase){
    // generate prefix
    uint16_t BS = Symmetric_Algorithm_Block_Length.at(Symmetric_Algorithms.at(sym_alg)) >> 3;
    std::string prefix = unhexlify(zfill(bintohex(BBS().rand_b(BS << 3)), BS << 1, '0'));
    
    std::string to_encrypt;
    
    // put data in Literal Data Packet
    Tag11 tag11;
    tag11.set_format('t');
    tag11.set_filename(filename);
    time_t t = now();
    tag11.set_time(t);
    tag11.set_literal(data);
    
    to_encrypt = tag11.write(2);
    
    // if message is to be signed
    if (signer){
        // find preferred hash and compression algorithms of the signer
        // find signing key id
        Tag5::Ptr tag5 = find_signing_key(*signer, 5);
        std::string keyid = tag5 -> get_keyid();
        tag5.reset();
        
        // find signature packet of signing key
        Tag2::Ptr tag2 = nullptr;
        for(Packet::Ptr const & p : signer -> get_packets()){
            if (p -> get_tag() == 2){
                std::string raw = p -> raw();
                Tag2 sig(raw);
                
                if (sig.get_keyid() == keyid){
                    tag2 = std::make_shared <Tag2> (sig);
                    break;
                }
            }
        }
        
        uint8_t h = 2; // default SHA1
        uint8_t c = comp;
        // if a signature packet was found
        if (tag2){
            // check for preferred hash algorithms
            std::string raw = tag2 -> find_subpacket(21);
            if (raw.size()){
                Tag2Sub21 tag2sub21(raw);
                h = tag2sub21.get_pha()[0]; // use first preferred hash algorithm
            }
            // check for preferred compression algorithms
            raw = tag2 -> find_subpacket(22);
            if (raw.size()){
                Tag2Sub22 tag2sub22(raw);
                h = tag2sub22.get_pca()[0]; // use first preferred compression algorithm
            }
        }
        to_encrypt = sign_message(*signer, sig_passphrase, filename, tag11.write(2), h, c).write(2);
    }
    
    if (comp){
        // Compressed Data Packet (Tag 8)
        Tag8 tag8;
        tag8.set_comp(comp);
        tag8.set_data(to_encrypt); // put source data into compressed packet
        to_encrypt = tag8.write(2);
    }
    
    Packet::Ptr encrypted = nullptr;
    
    if (!mdc){
        // Symmetrically Encrypted Data Packet (Tag 9)
        Tag9 tag9;
        //tag9.set_encrypted_data(use_OpenPGP_CFB_encrypt(sym_alg, 9, to_encrypt, session_key, prefix));
        encrypted = std::make_shared<Tag9>(tag9);
    }
    else{
        // Modification Detection Code Packet (Tag 19)
        Tag19 tag19;
        tag19.set_hash(use_hash(2, prefix + prefix.substr(BS - 2, 2) + to_encrypt + "\xd3\x14"));
        
        // Sym. Encrypted Integrity Protected Data Packet (Tag 18)
        Tag18 tag18;
        //encrypt(compressed(literal_data_packet(plain text)) + MDC SHA1(20 octets))
        tag18.set_protected_data(use_OpenPGP_CFB_encrypt(sym_alg, 18, to_encrypt + tag19.write(), session_key, prefix));
        encrypted = std::make_shared<Tag18>(tag18);
    }
    
    return encrypted;
}

std::string encrypt_pm_pka(const PGPPublicKey & pub, const std::string & data)
{
    
    std::string body = "<div><br></div><div><br></div><div>Sent from <a href=\"https://protonmail.ch\">ProtonMail</a>, encrypted email based in Switzerland.<br></div>";
    std::cout << body << std::endl;
    
    std::string session_key = base64_decode("IsKORjNGw7HCsVY1QXHCscOZQsKGDsKywpjCtHfCol4FasOfIGUXw7DDssOqw50=");
    std::cout << session_key << std::endl;
    std::string encoded_msg_body = base64_encode(reinterpret_cast<const unsigned char*>(body.c_str()), (int)body.length());
    
    int residual = encoded_msg_body.length() % 32;
    if((residual) != 0) {
        for(int i = 0; i < 32 - residual; i++) {
            encoded_msg_body = encoded_msg_body + " ";
        }
    }
    std::cout << encoded_msg_body << std::endl;
    int sym_alg = 9;
    uint16_t BS = Symmetric_Algorithm_Block_Length.at(Symmetric_Algorithms.at(sym_alg)) >> 3;
    std::string prefix = unhexlify(zfill(bintohex(BBS().rand_byts(BS << 3)), BS << 1, '0'));
    std::string out_str = use_OpenPGP_CFB_encrypt(sym_alg, 18, encoded_msg_body, session_key, prefix);
    std::cout << out_str << std::endl;
    
    
    std::cout << base64_encode(reinterpret_cast<const unsigned char*>(out_str.c_str()), (int)out_str.length()) << std::endl;
    
    return encoded_msg_body;
}

PGPMessage encrypt_pka(const PGPPublicKey & pub, const std::string & data, const std::string & filename, const uint8_t sym_alg, const uint8_t comp, const bool mdc, const PGPSecretKey::Ptr & signer, const std::string & sig_passphrase)
{
    
    if ((pub.get_ASCII_Armor() != 1) && (pub.get_ASCII_Armor() != 2)){
        throw std::runtime_error("Error: No encrypting key found.");
    }
    
    std::vector <Packet::Ptr> packets = pub.get_packets();
    Tag6::Ptr public_key = find_encrypting_key(pub);
    
    if (!public_key){
        throw std::runtime_error("Error: No encrypting key found.");
    }
    
    // Check if key has been revoked
    if (check_revoked(packets, public_key -> get_keyid())){
        throw std::runtime_error("Error: Key " + hexlify(public_key -> get_keyid()) + " has been revoked. Nothing done.");
    }
    
    std::vector <std::string> mpi = public_key -> get_mpi();
    //std::cout<< hexlify(mpi[0]) << std::endl;
    //std::cout<< hexlify(mpi[1]) << std::endl;

    
    Tag1::Ptr tag1 = std::make_shared<Tag1>();
    tag1 -> set_keyid(public_key -> get_keyid());
    tag1 -> set_pka(public_key -> get_pka());
    
    // do calculations
    
  //  std::cout << Symmetric_Algorithms.at(sym_alg) << std::endl;
    // generate session key
    uint16_t key_len = Symmetric_Algorithm_Key_Length.at(Symmetric_Algorithms.at(sym_alg));
    // get hex version of session key
    std::string session_key = BBS().rand_byts(key_len);//unhexlify("b7c29155cb37130673a2051132ac4debb3960668663ec76ba321e830074da8d6");//
    
 //   std::cout << "SESSION_KEY:" << hexlify(session_key) << std::endl;
    
    //int size = key_len / 8;
    
    //int buf_size =size + 1 + 2;
    
    std::string unencoded = "";
    unencoded += 9;
    unencoded += session_key;
    uint16_t sum = 0;
    for(char & x : session_key){
        sum += static_cast <unsigned char> (x);
    }
    unencoded += (uint8_t)((sum >> 8) & 0xff);
    unencoded += (uint8_t)(sum & 0xff);
    
    std::string nibbles = mpitohex(mpi[0]);        // get hex representation of modulus
    nibbles += std::string(nibbles.size() & 1, 0); // get even number of nibbles
    std::string m = hextompi(hexlify(EME_PKCS1v1_5_ENCODE(std::string(1, sym_alg) + session_key + unhexlify(makehex(sum, 4)), (unsigned int)nibbles.size() >> 1))); //Note: Convert
    
 //   std::cout << "SESSIONKEY_HEX::" << mpitohex(m) << std::endl;
    
    // encrypt m (mpi)
    tag1->set_mpi(pka_encrypt(public_key->get_pka(), m, mpi));
    
    // encrypt data and put it into a packet
    Packet::Ptr encrypted = encrypt_data(session_key, data, filename, sym_alg, comp, mdc, signer, sig_passphrase);
    
    // write data to output container
    PGPMessage out;
    out.set_ASCII_Armor(0);
    out.set_Armor_Header(std::vector <std::pair <std::string, std::string> > (
    {
        std::pair <std::string, std::string> ("Version", "ProtonMail v0.1.0"),
        std::pair <std::string, std::string> ("Comment", "https://protonmail.com")
    }));
    out.set_packets({tag1, encrypted});
    
    // clear data
    packets.clear();
    public_key.reset();
    tag1.reset();
    //  m = 0;
    session_key = "";
    encrypted.reset();
    
    return out;
}

pm::PMPGPMessage encrypt_pka(const PGPPublicKey & pub, const std::string & data, const std::string & filename, const uint8_t sym_alg, const uint8_t comp, const bool mdc, const PGPSecretKey::Ptr & signer, const std::string & sig_passphrase, bool is_pm_pka)
{
//    std::string unencrypt_msg = [unencrypt_message UTF8String];
//    unencrypt_msg = encode_utf8_base64_msg(unencrypt_msg);
//    if(isDebugMode)
//        std::cout << unencrypt_msg << std::endl;
//    
//    uint16_t test_BS = Symmetric_Algorithm_Block_Length.at(Symmetric_Algorithms.at(9)) >> 3;
//    std::string prefix = unhexlify(zfill(bintohex(BBS().rand_byts(test_BS << 3)), test_BS << 1, '0'));
//    
//    std::string random_key = BBS().rand_byts(256);
//    
//    
//    std::string aes_encrypted_data = use_OpenPGP_CFB_encrypt(9, 9, unencrypt_msg, random_key, prefix);
//    if(isDebugMode)
//        std::cout << aes_encrypted_data << std::endl;
//    aes_encrypted_data = encode_utf8_base64(aes_encrypted_data);
//    if(isDebugMode)
//        std::cout << aes_encrypted_data << std::endl;
//    
//    random_key = encode_utf8_base64(random_key);
//    if(isDebugMode)
//        std::cout << random_key << std::endl;
//    
//    std::string user_pub_key = [pub_key UTF8String];
//    PGPPublicKey pub(user_pub_key);
//    
//    PGPMessage encrypted_pgp = encrypt_pka(pub, random_key);
//    std::string encrypted_random_key = encrypted_pgp.write();
//    
//    
//    std::string out_msg =  protonmail_cryoto_headerMessage + aes_encrypted_data + protonmail_cryoto_tailMessage + "||" + protonmail_cryoto_headerRandomKey + encrypted_random_key + protonmail_cryoto_tailRandomKey;
//    
//    return [[NSString alloc] initWithUTF8String:out_msg.c_str()];
    return pm::PMPGPMessage();
}

PGPMessage encrypt_sym(const std::string & passphrase, const std::string & data, const std::string & filename, const uint8_t sym_alg, const uint8_t comp, const bool mdc, const PGPSecretKey::Ptr & signer, const std::string & sig_passphrase){
    //std::cerr << "Warning: encrypt_sym is untested. Potentially incorrect" << std::endl;
    
    // generate Symmetric-Key Encrypted Session Key Packets (Tag 3)
    S2K3::Ptr s2k = std::make_shared <S2K3> ();
    s2k -> set_type(3);
    s2k -> set_hash(8); // SHA1
    s2k -> set_salt(unhexlify(bintohex(BBS().rand_b(64))));
    s2k -> set_count(96);
    
    Tag3::Ptr tag3 = std::make_shared <Tag3> ();
    tag3 -> set_version(4);
    tag3 -> set_s2k(s2k);
    tag3 -> set_sym(sym_alg);
    // don't set esk (?)
    
    // generate session key
    // get hex version of session key
    std::string session_key = tag3->get_key(passphrase);
    
//    // unhexlify session key
//    session_key = unhexlify(std::string((key_len >> 2) - session_key.size(), '0') + session_key);
//    
//    // encrypt session key
//    std::string encrypted_session_key = session_key;
    
    // encrypt data
    Packet::Ptr encrypted = encrypt_data(session_key.substr(1, session_key.size() - 1), data, filename, session_key[0], comp, mdc, signer, sig_passphrase);
    
    // write to output container
    PGPMessage out;
    out.set_ASCII_Armor(0);
    out.set_Armor_Header(std::vector <std::pair <std::string, std::string> > (
    {
        std::pair <std::string, std::string> ("Version", "ProtonMail v0.1.0"),
        std::pair <std::string, std::string> ("Comment", "https://protonmail.com")
    }));

    out.set_packets({tag3, encrypted});
    
    // clear data
    s2k.reset();
    tag3.reset();
    session_key = "";
    //encrypted_session_key = "";
    encrypted.reset();
    
    return out;
}
