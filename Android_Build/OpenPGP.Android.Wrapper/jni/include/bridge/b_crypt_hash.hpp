// AUTOGENERATED FILE - DO NOT MODIFY!
// This file generated by Djinni from open_pgp.djinni

#pragma once

#include <string>

namespace ProtonMail {

class BCryptHash {
public:
    virtual ~BCryptHash() {}

    /**
     *base 64 *DotSlash encode
     *base 64 *DotSlash decode
     *hash
     */
    static std::string hash_string(const std::string & password, const std::string & salt);
};

}  // namespace ProtonMail
