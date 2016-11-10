#include <algorithm>
#include <vector>

#ifndef __AES__
#define __AES__

#include <utilities/includes.h>
#include <openpgp/cryptomath.h>
#include <encryption/SymAlg.h>
#include <encryption/AES_Const.h>

class AES : public SymAlg{
    private:
        uint8_t b, rounds, columns;
        std::vector <std::vector <uint32_t> > keys;

        void shiftrow(std::vector <uint32_t> & data);
        void invshiftrow(std::vector <uint32_t> & data);
        uint8_t GF(uint8_t a, uint8_t b);
        void mixcolumns(std::vector <uint32_t> & data);
        void invmixcolumns(std::vector <uint32_t> & data);
        std::string OUT(std::vector <uint32_t> & data);

    public:
        AES();
        AES(const std::string & KEY);
        void setkey(const std::string & KEY);
        std::string encrypt(const std::string & DATA);
        std::string decrypt(const std::string & DATA);
        unsigned int blocksize() const;
};


namespace ProtonMail {
    
    std::string aes_cbc_256_encrypt(std::string key, std::string iv, std::string text);
    std::string aes_cbc_256_decrypt(std::string key, std::string iv, std::string enc_text);
    
    std::string openssl_aes_cfb_256_encrypt(const std::string& text, const std::string& key);
    std::string openssl_aes_cfb_256_decrypt(const std::string& enc_text, const std::string& key);
    
    std::string AESEncrypt(const void *const apBuffer, size_t aBufferSize, const void *const apKey, size_t aKeySize, std::string aIVector);
    std::string AESDecrypt(const void *const apBuffer, size_t aBufferSize, const void *const apKey, size_t aKeySize, std::string aIVector);
}





#endif
