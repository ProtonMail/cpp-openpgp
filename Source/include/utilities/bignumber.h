//
//  bignumber.hpp
//  OpenPGP_OSX_Lib
//
//  Created by Yanfeng Zhang on 10/13/16.
//
//  The MIT License
// 
//  Copyright (c) 2019 Proton Technologies AG
// 
//  Permission is hereby granted, free of charge, to any person obtaining a copy
//  of this software and associated documentation files (the "Software"), to deal
//  in the Software without restriction, including without limitation the rights
//  to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
//  copies of the Software, and to permit persons to whom the Software is
//  furnished to do so, subject to the following conditions:
// 
//  The above copyright notice and this permission notice shall be included in
//  all copies or substantial portions of the Software.
// 
//  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
//  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
//  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
//  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
//  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
//  OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
//  THE SOFTWARE.



#ifndef bignumber_hpp
#define bignumber_hpp

#include <stdio.h>
#include <string>
#include <memory>
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

