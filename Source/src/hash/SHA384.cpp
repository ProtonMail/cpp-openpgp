#include <hash/SHA384.h>
#include <openssl/sha.h>

SHA384::SHA384()
{
}

SHA384::SHA384(const std::string & str) : SHA384()
{
    update(str);
}

std::string SHA384::hexdigest(){
    char outputBuffer[129];
    unsigned char hash[SHA384_DIGEST_LENGTH];
    SHA512_CTX sha512;
    SHA384_Init(&sha512);
    SHA384_Update(&sha512, stack.c_str(), stack.length());
    SHA384_Final(hash, &sha512);
    int i = 0;
    for(i = 0; i < SHA384_DIGEST_LENGTH; i++)
    {
        sprintf(outputBuffer + (i * 2), "%02x", hash[i]);
    }
    auto bufferSize = SHA384_DIGEST_LENGTH * 2;
    outputBuffer[128] = 0;
    std::string d = std::string(outputBuffer, bufferSize);
    return d;
}

unsigned int SHA384::blocksize() const{
    return 1024;
}

unsigned int SHA384::digestsize() const{
    return 384;
}

void SHA384::update(const std::string &str){
    stack = str;
}
