//
//  b_crypt_hash_impl.cpp
//  OpenPGP
//
//  Created by Yanfeng Zhang on 10/5/17.
//  Copyright © 2017 Yanfeng Zhang. All rights reserved.
//

#include "bridge_impl/b_crypt_hash_impl.hpp"

#include <hash/bcrypt.hpp>

namespace ProtonMail {

std::string BCryptHash::hash_string(const std::string & password, const std::string & salt) {
    ProtonMail::BCrypt bcrypt;
    std::string hashed = bcrypt.hashpw(password, salt);
    return hashed;
}


}
