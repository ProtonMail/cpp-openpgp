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

    };

}
