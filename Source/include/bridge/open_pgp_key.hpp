// AUTOGENERATED FILE - DO NOT MODIFY!
// This file generated by Djinni from open_pgp.djinni

#pragma once

#include <string>
#include <utility>

namespace ProtonMail {

struct OpenPgpKey final {
    std::string public_key;
    std::string private_key;

    OpenPgpKey(std::string public_key_,
               std::string private_key_)
    : public_key(std::move(public_key_))
    , private_key(std::move(private_key_))
    {}
};

}  // namespace ProtonMail
