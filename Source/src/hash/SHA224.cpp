#include <hash/SHA224.h>
#include <openssl/sha.h>

SHA224::SHA224()
{

}

SHA224::SHA224(const std::string & str) : SHA224()
{
    update(str);
}

void SHA224::update(const std::string &str){
    stack = str;
}

std::string SHA224::hexdigest(){
    
    unsigned char hash[SHA224_DIGEST_LENGTH];
    SHA256_CTX sha256;
    SHA224_Init(&sha256);
    SHA224_Update(&sha256, stack.c_str(), stack.length());
    SHA224_Final(hash, &sha256);
    
    std::stringstream ss;
    ss << std::hex << std::setfill('0');
    for (int i = 0; i < SHA224_DIGEST_LENGTH; i++)
    {
        ss << std::hex << std::setw(2)  << static_cast<unsigned int>(hash[i]);
    }
    return ss.str();
}

unsigned int SHA224::blocksize() const{
    return 512;
}

unsigned int SHA224::digestsize() const{
    return 224; //SHA224_DIGEST_LENGTH * 8
}
