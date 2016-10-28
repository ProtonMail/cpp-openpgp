#pragma once

#include "bridge/srp_client.hpp"

namespace ProtonMail {

    class SrpClientImpl : public ProtonMail::SrpClient {
    private:

    public:
        SrpClientImpl();
        ~SrpClientImpl();
        static std::string expand_hash(const std::string & input);
    };

}
