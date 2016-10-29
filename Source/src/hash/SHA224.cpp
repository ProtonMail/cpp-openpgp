#include <hash/SHA224.h>
#include <openssl/sha.h>


SHA224::SHA224()
{

}

SHA224::SHA224(const std::string & str) : SHA224()
{
    update(str);
}

std::string SHA224::hexdigest(){
    
    char outputBuffer[65];
    unsigned char hash[SHA224_DIGEST_LENGTH];
    SHA256_CTX sha256;
    
    SHA224_Init(&sha256);
    SHA224_Update(&sha256, stack.c_str(), stack.length());
    SHA224_Final(hash, &sha256);
    int i = 0;
    for(i = 0; i < SHA224_DIGEST_LENGTH; i++)
    {
        sprintf(outputBuffer + (i * 2), "%02x", hash[i]);
    }
    auto bufferSize = SHA224_DIGEST_LENGTH * 2;
    outputBuffer[64] = 0;
    std::string d = std::string(outputBuffer, bufferSize);
    return d;
}

unsigned int SHA224::blocksize() const{
    return 512;
}

unsigned int SHA224::digestsize() const{
    return 224;
}

void SHA224::update(const std::string &str){
    stack = str;
}
