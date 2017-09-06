#include <openpgp/PGPMessage.h>

#include <package/Tag4.h>
#include <package/Tag2.h>
#include <package/Tag11.h>
#include <openpgp/sigcalc.h>
#include <encryption/RSA.h>

// OpenPGP Message :- Encrypted Message | Signed Message | Compressed Message | Literal Message.
const bool PGPMessage::OpenPGPMessage(std::list <Token>::iterator it, std::list <Token> & s) const{
    if ((*it == ENCRYPTEDMESSAGE) || (*it == SIGNEDMESSAGE) || (*it == COMPRESSEDMESSAGE) || (*it == LITERALMESSAGE)){
        *it = OPENPGPMESSAGE;
        return true;
    }
    return false;
}

// Compressed Message :- Compressed Data Packet.
const bool PGPMessage::CompressedMessage(std::list <Token>::iterator it, std::list <Token> & s) const{
    if (*it == CDP){
        *it = COMPRESSEDMESSAGE;
        return true;
    }
    return false;
}

// Literal Message :- Literal Data Packet.
const bool PGPMessage::LiteralMessage(std::list <Token>::iterator it, std::list <Token> & s) const{
    if (*it == LDP){
        *it = LITERALMESSAGE;
        return true;
    }
    return false;
}

// ESK :- Public-Key Encrypted Session Key Packet | Symmetric-Key Encrypted Session Key Packet.
const bool PGPMessage::EncryptedSessionKey(std::list <Token>::iterator it, std::list <Token> & s) const{
    if ((*it == PKESKP) || (*it == SKESKP)){
        *it = ESK;
        return true;
    }
    return false;
}

// ESK Sequence :- ESK | ESK Sequence, ESK.
const bool PGPMessage::ESKSequence(std::list <Token>::iterator it, std::list <Token> & s) const{
    if (*it == ESK){
        *it = ESKSEQUENCE;
        return true;
    }
    else if (*it == ESKSEQUENCE){
        std::list <Token>::iterator it2 = it; it2++;
        if (*it2 == ESK){
            s.erase(it2);
            *it = ESKSEQUENCE;
            return true;
        }
    }
    return false;
}

// Encrypted Data :- Symmetrically Encrypted Data Packet | Symmetrically Encrypted Integrity Protected Data Packet
const bool PGPMessage::EncryptedData(std::list <Token>::iterator it, std::list <Token> & s) const{
    if ((*it == SEDP) || (*it == SEIPDP)){
        *it = ENCRYPTEDDATA;
        return true;
    }
    return false;
}

// Encrypted Message :- Encrypted Data | ESK Sequence, Encrypted Data.
const bool PGPMessage::EncryptedMessage(std::list <Token>::iterator it, std::list <Token> & s) const{
    if (*it == ENCRYPTEDDATA){
        *it = ENCRYPTEDMESSAGE;
        return true;
    }
    else if (*it == ESKSEQUENCE){
        std::list <Token>::iterator it2 = it; it2++;
        if (*it2 == ENCRYPTEDDATA){
            *it = ENCRYPTEDMESSAGE;
            s.erase(it2);
            return true;
        }
    }
    return false;
}

// One-Pass Signed Message :- One-Pass Signature Packet, OpenPGP Message, Corresponding Signature Packet.
const bool PGPMessage::OnePassSignedMessage(std::list <Token>::iterator it, std::list <Token> & s) const{
    std::list <Token>::iterator it2 = it; it2++;
    std::list <Token>::iterator it3 = it2; it3++;
    if ((*it == OPSP) && (*it2 == OPENPGPMESSAGE) && (*it3 == SP)){
        *it = ONEPASSSIGNEDMESSAGE;
        s.erase(it2);
        s.erase(it3);
        return true;
    }
    return false;
}

// Signed Message :- Signature Packet, OpenPGP Message | One-Pass Signed Message.
const bool PGPMessage::SignedMessage(std::list <Token>::iterator it, std::list <Token> & s) const{
    if (*it == ONEPASSSIGNEDMESSAGE){
        *it = SIGNEDMESSAGE;
        return true;
    }
    else if (*it == SP){
        std::list <Token>::iterator it2 = it; it2++;
        if (*it2 == OPENPGPMESSAGE){
            *it = SIGNEDMESSAGE;
            s.erase(it2);
            return true;
        }
    }
    return false;
}

void PGPMessage::decompress() {
    comp = nullptr;
    // check if compressed
    if ((packets.size() == 1) && (packets[0] -> get_tag() == 8)){
        std::string raw = packets[0] -> raw();
        packets.clear();                                    // free up pointer to compressed packet
        comp = std::make_shared <Tag8> (raw);               // put data in a Compressed Data Packet
        raw = comp -> get_data();                           // get decompressed data
        comp -> set_data("");                               // free up space taken up by compressed data; also prevents data from showing twice
        comp -> set_partial(packets[0] -> get_partial());
        read_raw(raw);                                          // read decompressed data into packets
    }
}

void PGPMessage::done_load()
{
    decompress();
    
    if ((ASCII_Armor == 255) && meaningful()){
        ASCII_Armor = 0;
    }
}

PGPMessage::PGPMessage():
PGP(),
comp(nullptr)
{
    ASCII_Armor = 0;
}

PGPMessage::PGPMessage(const PGPMessage & copy):
PGP(copy),
comp(nullptr)
{
    decompress();
    
    if ((ASCII_Armor == 255) && meaningful()){
        ASCII_Armor = 0;
    }
}

PGPMessage::PGPMessage(std::string & data, bool isRaw):
PGP(data, isRaw),
comp(nullptr)
{
    decompress();
    
    if ((ASCII_Armor == 255) && meaningful()){
        ASCII_Armor = 0;
    }
}

PGPMessage::PGPMessage(std::ifstream & f):
PGP(f),
comp(nullptr)
{
    decompress();
    
    if ((ASCII_Armor == 255) && meaningful()){
        ASCII_Armor = 0;
    }
}

PGPMessage::~PGPMessage(){
    comp.reset();
}

std::string PGPMessage::show(const uint8_t indents, const uint8_t indent_size) const{
    std::stringstream out;
    if (comp){ // if compression was used, add a header
        out << comp -> show(indents, indent_size);
    }
    out << PGP::show(indents + static_cast <bool> (comp), indent_size);
    return out.str();
}

std::string PGPMessage::raw(const uint8_t header, const uint8_t tag) const{
    std::string out = PGP::raw(header, tag);
    if (comp){ // if compression was used; compress data
        comp -> set_data(out);
        out = comp -> write(header);
        comp -> set_data(""); // hold compressed data for as little time as possible
    }
    return out;
}

std::string PGPMessage::write(const uint8_t armor, const uint8_t header, const uint8_t tag) const{
    std::string packet_string = raw(header, tag);
    
    // put data into a Compressed Data Packet if compression is used
    if (comp){
        comp -> set_data(packet_string);
        packet_string = comp -> write(header);
    }
    
    if ((armor == 1) || (!armor && !armored)){ // if no armor or if default, and not armored
        return packet_string;                  // return raw data
    }
    std::string out = "-----BEGIN PGP MESSAGE-----\n";
    for(std::pair <std::string, std::string> const & key : Armor_Header){
        out += key.first + ": " + key.second + "\n";
    }
    out += "\n";
    return out + format_string(ascii2radix64(packet_string), MAX_LINE_LENGTH) + "=" + ascii2radix64(unhexlify(makehex(crc24(packet_string), 6))) +  "\n-----END PGP MESSAGE-----\n";
}

uint8_t PGPMessage::get_comp(){
    if (comp){
        return comp -> get_comp();
    }
    return 0;
}

void PGPMessage::set_comp(const uint8_t c){
    comp.reset(); // free comp / set it to nullptr
    if (c){ // if not uncompressed
        comp = std::make_shared <Tag8> ();
        comp -> set_comp(c);
    }
}

const bool PGPMessage::match(const Token & t) const{
    if (!packets.size()){
        return false;
    }
    
    if ((t != OPENPGPMESSAGE) && (t != ENCRYPTEDMESSAGE)  &&
        (t != SIGNEDMESSAGE)  && (t != COMPRESSEDMESSAGE) &&
        (t != LITERALMESSAGE)){
        throw std::runtime_error("Error: Invalid token to match.");
        // return false;
    }
    
    // get list of packets and convert them to Token
    std::list <Token> s;
    for(Packet::Ptr const & p : packets){
        Token push;
        switch(p -> get_tag()){
            case 8:
                push = CDP;
                break;
            case 11:
                push = LDP;
                break;
            case 1:
                push = PKESKP;
                break;
            case 3:
                push = SKESKP;
                break;
            case 9:
                push = SEDP;
                break;
            case 18:
                push = SEIPDP;
                break;
            case 4:
                push = OPSP;
                break;
            case 2:
                push = SP;
                break;
            default:
                throw std::runtime_error("Error: Non-Message packet found.");
                // return false;
                break;
        }
        s.push_back(push);
    }
    
    while ((*(s.begin()) != t) || (s.size() != 1)){ // while the sentence has not been fully parsed, or has been fully parse but not correctly
        bool reduced = false;
        for(std::list <Token>::iterator it = s.begin(); it != s.end(); it++){ // for each token
            // make sure the sentence continues to fit at least one of the rules at least once per loop over the sentence
            if (OpenPGPMessage(it, s) || CompressedMessage(it, s) || LiteralMessage(it, s) ||
                EncryptedSessionKey(it, s) || ESKSequence(it, s) || EncryptedData(it, s) ||
                EncryptedMessage(it, s) || OnePassSignedMessage(it, s) || SignedMessage(it, s)){
                reduced = true;
                break;
            }
        }
        if (!reduced){
            return false;
        }
    }
    return true;
}

bool PGPMessage::meaningful() const {
    return match(OPENPGPMESSAGE);
}

PGP::Ptr PGPMessage::clone() const{
    return std::make_shared <PGPMessage> (*this);
}



bool PGPMessage::verify(PGPPublicKey::Ptr verifier) {
    if (verifier == nullptr) {
        throw std::runtime_error("Error : verify can't be null");
    }
    // most of the time OpenPGP Message data is compressed
    // then it is encrypted
    if (match(PGPMessage::ENCRYPTEDMESSAGE)){
        // Encrypted Message :- Encrypted Data | ESK Sequence, Encrypted Data.
        throw std::runtime_error("Error: Use decrypt to verify message.");
    }
    else if (match(PGPMessage::SIGNEDMESSAGE)){
        // // Signed Message :- Signature Packet, OpenPGP Message | One-Pass Signed Message.
        // // One-Pass Signed Message :- One-Pass Signature Packet, OpenPGP Message, Corresponding Signature Packet.
        
        // parse packets
        std::vector <Packet::Ptr> packets = get_packets();
        
        /*
         Note that if a message contains more than one one-pass signature,
         then the Signature packets bracket the message; that is, the first
         Signature packet after the message corresponds to the last one-pass
         packet and the final Signature packet corresponds to the first
         one-pass packet.
         */
        
        // Tag4_0, Tag4_1, ... , Tag4_n, Tag8/11, Tag2_n, ... , Tag2_1, Tag2_0
        unsigned int i = 0;
        std::list <Tag4::Ptr> OPSP;                                     // treat as stack
        while ((i < packets.size()) && (packets[i] -> get_tag() == 4)){
            std::string data = packets[i] -> raw();
            OPSP.push_front(std::shared_ptr <Tag4> (new Tag4(data)));   // put next Tag4 onto stack
            i++;
            
            if ((*(OPSP.rbegin())) -> get_nested() != 0){               // check if there are nested packets
                break;                                                  // just in case extra data was placed, allowing for errors later
            }
        }
        
        // get signed data
        std::string binary = packets[i] -> raw();
        i++;
        binary = Tag11(binary).get_literal();                           // binary data hashed directly
        std::string text;                                               // text data line endings converted to <CR><LF>
        
        // cache text version of data
        // probably only one of binary or text is needed at one time
        if (binary[0] == '\n'){
            text = "\r";
        }
        text += std::string(1, binary[0]);
        unsigned int c = 1;
        while (c < binary.size()){
            if (binary[c] == '\n'){                                     // if current character is newline
                if (binary[c - 1] != '\r'){                             // if previous character was not carriage return
                    text += "\r";                                       // add a carriage return
                }
            }
            text += std::string(1, binary[c++]);                        // add current character
        }
        
        // get signatures
        std::list <Tag2::Ptr> SP;                                       // treat as queue
        while ((i < packets.size()) && (packets[i] -> get_tag() == 2)){
            std::string data = packets[i] -> raw();
            SP.push_front(std::shared_ptr <Tag2> (new Tag2(data)));     // put next Tag2 onto queue
            i++;
        }
        
        // check for signatures
        if (!OPSP.size() || !SP.size()){
            throw std::runtime_error("Error: No signature found.");
        }
        
        // both lists should be the same size
        if (OPSP.size() != SP.size()){
            throw std::runtime_error("Error: Different number of One-Pass Signatures and Signature packets.");
        }
        
        // check for matching signature
        bool verify = false;
        while (OPSP.size() && SP.size()){
            
            // extra warnings
            // check that KeyIDs match
            if ((*(OPSP.rbegin())) -> get_keyid() == (*(SP.begin())) -> get_keyid()) {
                
                // check that all the parameters match
                bool match = true;
                
                // Signature Type
                if ((*(OPSP.rbegin())) -> get_type() != (*(SP.begin())) -> get_type()){
                    match = false;
                    std::cerr << "Warning: One-Pass Signature Packet and Signature Packet Signature Type mismatch" << std::endl;
                }
                
                // Hash Algorithm
                if ((*(OPSP.rbegin())) -> get_hash() != (*(SP.begin())) -> get_hash()){
                    match = false;
                    std::cerr << "Warning: One-Pass Signature Packet and Signature Packet Hash Algorithm mismatch" << std::endl;
                }
                
                // Public Key Algorithm
                if ((*(OPSP.rbegin())) -> get_pka() != (*(SP.begin())) -> get_pka()){
                    match = false;
                    std::cerr << "Warning: One-Pass Signature Packet and Signature Packet Public Key Algorithm mismatch" << std::endl;
                }
                
                // check signature
                if (match) {
                    auto sp_key_id = (*(SP.begin())) -> get_keyid();
                    auto signing_key = verifier->find_key(sp_key_id);
                    if (signing_key != nullptr) {
                        // get hashed data
                        std::string digest;
                        switch ((*(OPSP.rbegin())) -> get_type()){
                            case 0:
                                digest = to_sign_00(binary, *(SP.begin()));
                                break;
                            case 1:
                                digest = to_sign_01(text, *(SP.begin()));
                                break;
                                
                                // don't know if other signature types can be here
                                
                                // certifications
                            case 0x10: case 0x11:
                            case 0x12: case 0x13:
                            default:
                            {
                                std::cerr << "Warning: Bad signature type: " << static_cast <unsigned int> ((*(OPSP.rbegin())) -> get_type()) << std::endl;
                                verify = false;
                            }
                                break;
                        }
                        
                        // check if the key matches this signature
                        
                        auto signature = *(SP.begin());
                        auto signing = signing_key->get_mpi();
                        
                        ProtonMail::crypto::rsa key(signing[0], signing[1]);
                        auto hash = signature -> get_hash();
                        
                        std::string encoded = EMSA_PKCS1_v1_5(hash, digest, bitsize(signing[0]) >> 3);
                        verify = key.verify(rawtompi(encoded), signature->get_mpi()[0]);
                        if (verify == false) return verify;
                    } else {
                        // throw std::runtime_error("Error : Can't find the verify key");
                    }
                }
            } else {
                verify = false;
                std::cerr << "Warning: One-Pass Signature Packet and Signature Packet KeyID mismatch" << std::endl;
            }
            
            // free shared_ptr
            OPSP.rbegin() -> reset();
            SP.begin() -> reset();
            
            OPSP.pop_back(); // pop top of stack
            SP.pop_front();  // pop front of queue
        }
        
        // cleanup remaining data
        for(Tag4::Ptr & p : OPSP){
            p.reset();
        }
        
        for(Tag2::Ptr & p : SP){
            p.reset();
        }
        
        return verify;
        
    } else if (match(PGPMessage::COMPRESSEDMESSAGE)){
        // Compressed Message :- Compressed Data Packet.
        
        // only one compressed data packet
        std::string message = get_packets()[0] -> raw();
        
        // decompress data
        Tag8 tag8(message);
        message = tag8.get_data();
        
        auto msg = PGPMessage(message);
        return msg.verify(verifier);
        
    } else if (match(PGPMessage::LITERALMESSAGE)){
        // Literal Message :- Literal Data Packet.
        
        // only one literal data packet
        std::string message = get_packets()[0] -> raw();
        
        // extract data
        Tag11 tag11(message);
        message = tag11.get_literal(); // not sure if this is correct
        
        auto msg = PGPMessage(message);
        return msg.verify(verifier);
    }
    else{
        throw std::runtime_error("Error: Not an OpenPGP Message. Perhaps Detached Signature?");
        // return false;
    }
    
    return false;
}




