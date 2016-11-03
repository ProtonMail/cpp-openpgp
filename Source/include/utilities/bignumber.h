//
//  bignumber.hpp
//  OpenPGP_OSX_Lib
//
//  Created by Yanfeng Zhang on 10/13/16.
//  Copyright © 2016 Yanfeng Zhang. All rights reserved.
//

#ifndef bignumber_hpp
#define bignumber_hpp

#include <stdio.h>
#include <string>
#include <openssl/rsa.h>


typedef std::shared_ptr<BIGNUM> Biginteger;

namespace ProtonMail {
    namespace BN {
        
        Biginteger toBI(const std::string &input);
        int num_bits(const Biginteger &input);
        Biginteger valueOf(int value);
        std::string fromBI(int bit_length, const Biginteger &input);
        Biginteger nnmod(const Biginteger &a, const Biginteger &b);
        Biginteger dup(const Biginteger &a);
        const Biginteger one();
        Biginteger rand_and_comp(int bit_length, const Biginteger &compA, const Biginteger &compB);
        Biginteger nnmod_exp(const Biginteger &a, const Biginteger &e, const Biginteger &m);
        int compareToZero(const Biginteger &a);
        Biginteger mul_add_nnmod(const Biginteger &a, const Biginteger &b, const Biginteger &c, const Biginteger &d);
        Biginteger add(const Biginteger &a, const Biginteger &b);
        Biginteger subtract(const Biginteger &a, const Biginteger &b);
        Biginteger multiply(const Biginteger &a, const Biginteger &b);
        Biginteger rshift(const Biginteger &a, int n);
    
    }
}

#endif /* bignumber_hpp */

