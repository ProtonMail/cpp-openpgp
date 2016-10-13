#pragma once

#include <openssl/rsa.h>
#include "bridge/srp_client.hpp"

namespace ProtonMail {

    class SrpClientImpl : public ProtonMail::SrpClient {
    private:

    public:
        SrpClientImpl();
        ~SrpClientImpl();
        
        static BIGNUM* toBI(const std::string &input);
        static std::string fromBI(int bit_length, BIGNUM* input);
        static std::string expand_hash(const std::string & input);
        
        static BIGNUM* nnmod_exp(BIGNUM* a, BIGNUM* e, BIGNUM* m);
        static BIGNUM* mul_add_nnmod(BIGNUM* a, BIGNUM* b, BIGNUM* c, BIGNUM* d);        
        static BIGNUM* add(BIGNUM* a, BIGNUM* b);
        static BIGNUM* subtract(BIGNUM* a, BIGNUM* b);
        static BIGNUM* multiply(BIGNUM* a, BIGNUM* b);
        static BIGNUM* nnmod(BIGNUM* a, BIGNUM* b);
        static BIGNUM* valueOf(int value);
        static int compareToZero(BIGNUM* a);
    };

}
