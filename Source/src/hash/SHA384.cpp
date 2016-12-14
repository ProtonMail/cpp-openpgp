#include <hash/SHA384.h>
#include <openssl/sha.h>

SHA384::SHA384()
{
    
}

SHA384::SHA384(const std::string & str) : SHA384()
{
    update(str);
}

void SHA384::update(const std::string &str){
    stack = str;
}

std::string SHA384::hexdigest(){
    
    unsigned char hash[SHA384_DIGEST_LENGTH];
    SHA512_CTX sha512;
    SHA384_Init(&sha512);
    SHA384_Update(&sha512, stack.c_str(), stack.length());
    SHA384_Final(hash, &sha512);
    
    std::stringstream ss;
    ss << std::hex << std::setfill('0');
    for (int i = 0; i < SHA384_DIGEST_LENGTH; i++)
    {
        ss << std::hex << std::setw(2)  << static_cast<unsigned int>(hash[i]);
    }
    return ss.str();
}

unsigned int SHA384::blocksize() const{
    return 1024;
}

unsigned int SHA384::digestsize() const{
    return 384; //SHA384_DIGEST_LENGTH * 8
}
