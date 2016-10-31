#include <hash/SHA1.h>
#include <openssl/sha.h>



SHA1::SHA1() : Hash()
{

}

SHA1::SHA1(const std::string & str) : SHA1()
{
    update(str);
}

void SHA1::update(const std::string & str){
    stack = str;
}

std::string SHA1::hexdigest(){
    char outputBuffer[41];
    unsigned char hash[SHA_DIGEST_LENGTH];
    SHA_CTX sha1;
    SHA1_Init(&sha1);
    SHA1_Update(&sha1, stack.c_str(), stack.length());
    SHA1_Final(hash, &sha1);
    int i = 0;
    for(i = 0; i < SHA_DIGEST_LENGTH; i++)
    {
        sprintf(outputBuffer + (i * 2), "%02x", hash[i]);
    }
    auto bufferSize = SHA_DIGEST_LENGTH * 2;
    outputBuffer[40] = 0;
    std::string d = std::string(outputBuffer, bufferSize);
    return d;
}

unsigned int SHA1::blocksize() const{
    return 512;
}

unsigned int SHA1::digestsize() const{
    return 160;
}
