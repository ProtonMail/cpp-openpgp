// AUTOGENERATED FILE - DO NOT MODIFY!
// This file generated by Djinni from open_pgp.djinni

#pragma once

#include <memory>
#include <string>

namespace ProtonMail {

class IPMScheme {
public:
    virtual ~IPMScheme() {}

    virtual std::string getValue() = 0;

    virtual std::string getType() = 0;

    virtual std::string getGroup() = 0;

    static std::shared_ptr<IPMScheme> create_instance(const std::string & type, const std::string & value);
};

}  // namespace ProtonMail
