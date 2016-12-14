#include <hash/MD5.h>
#include <openssl/md5.h>

MD5::MD5() : Hash()
{
    
}

MD5::MD5(const std::string & str) : MD5()
{
    update(str);
}

void MD5::update(const std::string & str){
    stack = str;
}

std::string MD5::hexdigest(){
    unsigned char hash[MD5_DIGEST_LENGTH];
    MD5_CTX md5;
    MD5_Init(&md5);
    MD5_Update(&md5, stack.c_str(), stack.length());
    MD5_Final(hash, &md5);
    
    std::stringstream ss;
    ss << std::hex << std::setfill('0');
    for (int i = 0; i < MD5_DIGEST_LENGTH; i++)
    {
        ss << std::hex << std::setw(2)  << static_cast<unsigned int>(hash[i]);
    }
    return ss.str();
}

unsigned int MD5::blocksize() const{
    return 512;
}

unsigned int MD5::digestsize() const{
    return 128; // MD5_DIGEST_LENGTH * 8
}
