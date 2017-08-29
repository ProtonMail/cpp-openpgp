#include <openpgp/PGPKey.h>

#include <openpgp/FindKey.h>

#include <package/Tag6.h>
#include <package/Tag2.h>
#include <package/Tag5.h>
#include <package/Tag7.h>
#include <package/Tag14.h>
#include <package/Tag13.h>
#include <package/Tag17.h>

bool PGPKey::meaningful(uint8_t type) const{
    uint8_t key, subkey;

    if (type == 1){ // Public Key
        key = 6;
        subkey = 14;
    }
    else if (type == 2){ // Private Key
        key = 5;
        subkey = 7;
    }
    else {
        throw std::runtime_error("Error: Non-PGP key in PGPKey structure.");
    }

    if (packets.size() < 3){ // minimum 3 packets: Primary Key + UID + Certification Signature
        return false;
    }

    // One Key packet
    if (packets[0] -> get_tag() != key){
        return false;
    }

    // get key version
    std::string pub = packets[0] -> raw();
    uint8_t version = Tag6(pub).get_version();

    // Zero or more revocation signatures
    unsigned int i = 1;
    while ((i < packets.size()) && (packets[i] -> get_tag() == 2)){
        std::string tag2 = packets[i] -> raw();
        if (Tag2(tag2).get_type() == 0x20){ // Key revocation signature
            i++;
        }
        else{
            return false;
        }
    }

    // One or more User ID packets
    // Zero or more User Attribute packets
    //
    // User Attribute packets and User ID packets may be freely intermixed
    // in this section, so long as the signatures that follow them are
    // maintained on the proper User Attribute or User ID packet.
    bool uid = false;
    while ((i < packets.size()) && ((packets[i] -> get_tag() == 13) || (packets[i] -> get_tag() == 17))){
        // After each User ID packet, zero or more Signature packets (certifications)
        // After each User Attribute packet, zero or more Signature packets (certifications)
        if (packets[i] -> get_tag() == 13){
            uid = true;
        }

        i++;

        // make sure the next packet is a signature
        if ((i >= packets.size()) || (packets[i] -> get_tag() != 2)){
            return false;
        }

        // while the packets continue to be signature packets
        while ((i < packets.size()) && (packets[i] -> get_tag() == 2)){
            std::string tag2 = packets[i] -> raw();
            uint8_t sig_type = Tag2(tag2).get_type();
            if ((0x10 <= sig_type) && (sig_type <= 0x13)){ // make sure they are certifications
                i++;
            }
            else{
                return false;
            }
        }
    }

    if (!uid){ // at least one User ID packet
        return false;
    }

    // Zero or more Subkey packets
    while ((i < packets.size()) && (packets[i] -> get_tag() == subkey)){
        if (version == 3){ // V3 keys MUST NOT have subkeys.
            return false;
        }

        // After each Subkey packet, one Signature packet, plus optionally a revocation
        i++;

        // one Signature packet
        if ((i >= packets.size()) || (packets[i] -> get_tag() != 2)){
            return false;
        }

        // check that the Signature packet is a Subkey binding signature
        std::string tag2 = packets[i] -> raw();
        if (Tag2(tag2).get_type() != 0x18){ // type Subkey binding signature
            return false;
        }

        // optionally a revocation
        i++;
        if (i >= packets.size()){ // if there are no more packets to check
            return true;
        }

        // if the next packet is a subkey, go back to top of loop
        if (packets[i] -> get_tag() == subkey){
            continue;
        }
        else if (packets[i] -> get_tag() == 2){ // else if the next packet is a Signature packet
            tag2 = packets[i] -> raw();
            if (Tag2(tag2).get_type() == 0x20){ // check if it is a Key revocation signature
                i++;
            }
            else{ // if not
                return false;
            }
        }
        else{ // neither a subkey or a revocation signature
            return false;
        }
    }

    return true; // no subkeys
}

PGPKey::PGPKey():
   PGP()
{}

PGPKey::PGPKey(const PGPKey & copy):
    PGP(copy)
{}

PGPKey::PGPKey(std::string & data):
    PGP(data)
{}

PGPKey::PGPKey(std::ifstream & f):
    PGP(f)
{}

PGPKey::~PGPKey(){}

std::string PGPKey::keyid() const{
    for(Packet::Ptr const & p : packets){
        // find primary key
        if ((p -> get_tag() == 5) || (p -> get_tag() == 6)){
            std::string data = p -> raw();
            Tag6 tag6(data);
            return tag6.get_keyid();
        }
    }
    // if no primary key is found
    for(Packet::Ptr const & p : packets){
        // find subkey
        if ((p -> get_tag() == 7) || (p -> get_tag() == 14)){
            std::string data = p -> raw();
            Tag6 tag6(data);
            return tag6.get_keyid();
        }
    }
    throw std::runtime_error("Error: PGP block type is incorrect.");
    return ""; // should never reach here; mainly just to remove compiler warnings
}

// output style is copied from gpg --list-keys
std::string PGPKey::list_keys() const{
    // scan for revoked keys
    std::map <std::string, std::string> revoked;
    for(Packet::Ptr const & p : packets){
        if (p -> get_tag() == 2){
            std::string data = p -> raw();
            Tag2 tag2(data);
            if ((tag2.get_type() == 0x20) || (tag2.get_type() == 0x28)){
                bool found = false;
                for(Tag2Subpacket::Ptr & s : tag2.get_unhashed_subpackets()){
                    if (s -> get_type() == 16){
                        data = s -> raw();
                        Tag2Sub16 tag2sub16(data);
                        revoked[tag2sub16.get_keyid()] = show_date(tag2.get_time());
                        found = true;
                    }
                }
                if (!found){
                    for(Tag2Subpacket::Ptr & s : tag2.get_hashed_subpackets()){
                        if (s -> get_type() == 16){
                            data = s -> raw();
                            Tag2Sub16 tag2sub16(data);
                            revoked[tag2sub16.get_keyid()] = show_date(tag2.get_time());
                            found = true;
                        }
                    }
                }
            }
        }
    }

    std::stringstream out;
    for(Packet::Ptr const & p : packets){
        std::string data = p -> raw();
        switch (p -> get_tag()){
            case 5: case 6: case 7: case 14:
                {
                    Tag6 tag6(data);
                    std::map <std::string, std::string>::iterator r = revoked.find(tag6.get_keyid());
                    std::stringstream s;
                    s << bitsize(tag6.get_mpi()[0]);
                    out << Public_Key_Type.at(p -> get_tag()) << "    " << zfill(s.str(), 4, ' ')
                        << Public_Key_Algorithm_Short.at(tag6.get_pka()) << "/"
                        << hexlify(tag6.get_keyid().substr(4, 4)) << " "
                        << show_date(tag6.get_time())
                        << ((r == revoked.end())?std::string(""):(std::string(" [revoked: ") + revoked[tag6.get_keyid()] + std::string("]")))
                        << "\n";
                }
                break;
            case 13:
                {
                    Tag13 tag13(data);
                    out << "uid                   " << tag13.raw() << "\n";
                }
                break;
            case 17:
                {
                    Tag17 tag17(data);
                    std::vector <Tag17Subpacket::Ptr> subpackets = tag17.get_attributes();
                    for(Tag17Subpacket::Ptr s : subpackets){
                        // since only subpacket type 1 is defined
                        data = s -> raw();
                        Tag17Sub1 sub1(data);
                        out << "att                   [jpeg image of size " << sub1.get_image().size() << "]\n";
                    }
                }
                break;
            case 2: default:
                break;
        }
    }
    return out.str();
}

bool PGPKey::meaningful() const{
    return meaningful(ASCII_Armor);
}

PGP::Ptr PGPKey::clone() const{
    return std::make_shared <PGPKey> (*this);
}

std::ostream & operator<<(std::ostream & stream, const PGPKey & pgp){
    stream << hexlify(pgp.keyid());
    return stream;
}

std::string &operator <<(std::string& str, const PGPSecretKey & pgp) {
    str = hexlify(pgp.keyid());
    return str;
}

PGPSecretKey::PGPSecretKey():
   PGPKey()
{
    ASCII_Armor = 2;
    //std::cout << "PGPSecretKey" << std::endl;
}

PGPSecretKey::PGPSecretKey(const PGPSecretKey & copy):
    PGPKey(copy)
{
    if ((ASCII_Armor == 255) && meaningful()){
        ASCII_Armor = 2;
    }
    //std::cout << "PGPSecretKey" << std::endl;
}

PGPSecretKey::PGPSecretKey(std::string & data):
    PGPKey(data)
{
    if ((ASCII_Armor == 255) && meaningful()){
        ASCII_Armor = 2;
    }
    //std::cout << "PGPSecretKey" << std::endl;
}

PGPSecretKey::PGPSecretKey(std::ifstream & f):
    PGPKey(f)
{
    if ((ASCII_Armor == 255) && meaningful()){
        ASCII_Armor = 2;
    }
    //std::cout << "PGPSecretKey" << std::endl;
}

PGPSecretKey::~PGPSecretKey(){
    //std::cout << "~PGPSecretKey" << std::endl;
}

PGPPublicKey PGPSecretKey::pub() const {
    return Secret2PublicKey(*this);
}

bool PGPSecretKey::meaningful() const{
    return PGPKey::meaningful(2);
}

PGP::Ptr PGPSecretKey::clone() const{
    return std::make_shared <PGPSecretKey> (*this);
}

std::ostream & operator<<(std::ostream & stream, const PGPSecretKey & pgp){
    stream << hexlify(pgp.keyid());
    return stream;
}

PGPPublicKey::PGPPublicKey():
   PGPKey()
{
    ASCII_Armor = 1;
}

PGPPublicKey::PGPPublicKey(const PGPPublicKey & copy):
    PGPKey(copy)
{
    if ((ASCII_Armor == 255) && meaningful()){
        ASCII_Armor = 1;
    }
}

PGPPublicKey::PGPPublicKey(std::string & data):
    PGPKey(data)
{
    if ((ASCII_Armor == 255) && meaningful()){
        ASCII_Armor = 1;
    }
}

PGPPublicKey::PGPPublicKey(std::ifstream & f):
    PGPKey(f)
{
    if ((ASCII_Armor == 255) && meaningful()){
        ASCII_Armor = 1;
    }
}

PGPPublicKey::PGPPublicKey(const PGPSecretKey & sec):
    PGPPublicKey(Secret2PublicKey(sec))
{}

PGPPublicKey::~PGPPublicKey(){}

bool PGPPublicKey::meaningful() const {
    return PGPKey::meaningful(1);
}

PGP::Ptr PGPPublicKey::clone() const{
    return std::make_shared <PGPPublicKey> (*this);
}

Packet::Ptr PGPSecretKey::tag7(int index) {
    for(Packet::Ptr const & p : get_packets()){
        if ((p -> get_tag() == 7)){
            return p;
        }
    }
    return nullptr;
}


Tag6::Ptr PGPPublicKey::tag6(int index) {
    for(Packet::Ptr const & p : get_packets()){
        std::cout << p -> get_tag() << std::endl;
        if ((p -> get_tag() == 14)){
//            auto a = std::static_pointer_cast<Tag6>(p);
//            std::cout << hexlify(a->get_keyid()) << std::endl;
           return std::static_pointer_cast<Tag6>(p);
        }
    }
    return nullptr;
}
