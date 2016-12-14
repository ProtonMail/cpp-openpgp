#include <hash/SHA512.h>
#include <openssl/sha.h>

SHA512::SHA512() : Hash()
{
    
}

SHA512::SHA512(const std::string & str) : SHA512()
{
    update(str);
}

void SHA512::update(const std::string &str){
    stack = str;
}

std::string SHA512::hexdigest(){
    
    unsigned char hash[SHA512_DIGEST_LENGTH];
    SHA512_CTX sha512;
    SHA512_Init(&sha512);
    SHA512_Update(&sha512, stack.c_str(), stack.length());
    SHA512_Final(hash, &sha512);

    std::stringstream ss;
    ss << std::hex << std::setfill('0');
    for (int i = 0; i < SHA512_DIGEST_LENGTH; i++)
    {
        ss << std::hex << std::setw(2)  << static_cast<unsigned int>(hash[i]);
    }
    return ss.str();
}

unsigned int SHA512::blocksize() const{
    return 1024;
}

unsigned int SHA512::digestsize() const{
    return 512; //SHA512_DIGEST_LENGTH * 8
}
