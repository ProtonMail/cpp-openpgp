#include <hash/Hash.h>

#include <openssl/hmac.h>
#include <iostream>
#include <iomanip>
Hash::Hash() :
stack(),
clen(0)
{}

Hash::~Hash(){
    stack.clear();
    clen = 0;
}

std::string Hash::digest(){
    return unhexlify(hexdigest());
}







namespace pm {
    
    
    std::string hash_hmac(std::string algo, std::string data, std::string key, bool is_raw_data)
    {
        unsigned char hash[32];
        
        HMAC_CTX hmac;
        HMAC_CTX_init(&hmac);
        HMAC_Init_ex(&hmac, &key[0], (int)key.length(), EVP_sha256(), NULL);
        HMAC_Update(&hmac, (unsigned char*)&data[0], data.length());
        unsigned int len = 32;
        HMAC_Final(&hmac, hash, &len);
        HMAC_CTX_cleanup(&hmac);
        
        
        if(is_raw_data)
        {
            return std::string((char *)hash, len);
        }
        else
        {
            std::stringstream ss;
            ss << std::hex << std::setfill('0');
            for (int i = 0; i < len; i++)
            {
                ss << std::hex << std::setw(2)  << (unsigned int)hash[i];
            }
            
            return (ss.str());
        }
    }
}

