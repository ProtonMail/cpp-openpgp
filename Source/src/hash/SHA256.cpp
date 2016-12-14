#include <hash/SHA256.h>
#include <openssl/sha.h>

SHA256::SHA256() : Hash()
{
    
}

SHA256::SHA256(const std::string & str) : SHA256()
{
    update(str);
}

void SHA256::update(const std::string &str){
    stack = str;
}

std::string SHA256::hexdigest(){

    unsigned char hash[SHA256_DIGEST_LENGTH];
    SHA256_CTX sha256;
    SHA256_Init(&sha256);
    SHA256_Update(&sha256, stack.c_str(), stack.length());
    SHA256_Final(hash, &sha256);
    
    std::stringstream ss;
    ss << std::hex << std::setfill('0');
    for (int i = 0; i < SHA256_DIGEST_LENGTH; i++)
    {
        ss << std::hex << std::setw(2)  << static_cast<unsigned int>(hash[i]);
    }
    return ss.str();
}

unsigned int SHA256::blocksize() const{
    return 512;
}

unsigned int SHA256::digestsize() const{
    return 256; //SHA256_DIGEST_LENGTH * 8
}
