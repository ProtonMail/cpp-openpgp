#pragma once

#include "bridge/srp_client.hpp"

namespace ProtonMail {

    class SrpClientImpl : public ProtonMail::SrpClient {
    private:


    public:
        SrpClientImpl();
        ~SrpClientImpl();

//        static std::vector<uint8_t> expand_hash(const std::vector<uint8_t> & input);
//        
//        /**SRP */
//        static SrpProofs generate_proofs(int32_t bit_length, const std::vector<uint8_t> & modulus_repr, const std::vector<uint8_t> & server_ephemeral_repr, const std::vector<uint8_t> & hashed_password_repr);
//        
//        static std::vector<uint8_t> generate_Verifier(int32_t bit_length, const std::vector<uint8_t> & modulus_repr, const std::vector<uint8_t> & hashed_password_repr);

    };

}
