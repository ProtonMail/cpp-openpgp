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


namespace ProtonMail {
    
    
    namespace BN {
        
        BIGNUM* toBI(const std::string &input);
        std::string fromBI(int bit_length, BIGNUM* input);
        BIGNUM* nnmod_exp(BIGNUM* a, BIGNUM* e, BIGNUM* m);
        BIGNUM* mul_add_nnmod(BIGNUM* a, BIGNUM* b, BIGNUM* c, BIGNUM* d);
        BIGNUM* add(BIGNUM* a, BIGNUM* b);
        BIGNUM* subtract(BIGNUM* a, BIGNUM* b);
        BIGNUM* multiply(BIGNUM* a, BIGNUM* b);
        BIGNUM* nnmod(BIGNUM* a, BIGNUM* b);
        BIGNUM* valueOf(int value);
        int compareToZero(BIGNUM* a);
        
        
        
    }
    
}

#endif /* bignumber_hpp */

