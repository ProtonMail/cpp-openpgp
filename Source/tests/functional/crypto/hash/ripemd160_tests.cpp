//
//  ripemd160_tests.cpp
//  OpenPGP
//
//  Created by Yanfeng Zhang on 10/28/16.
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



#import "utils_test.h"
#include <hash/RIPEMD160.h>


namespace tests {
    namespace hash_tests {
        SUITE(ripemd160)
        {
            TEST(RIPE_MD_160) {
                //RIPE-MD 160 bits with test vectors from http://homes.esat.kuleuven.be/~bosselae/ripemd160.html
                {
                    auto hash = RIPEMD160("");
                    auto hash_out = hash.hexdigest();
                    VERIFY_ARE_EQUAL(hash_out, "9c1185a5c5e9fc54612808977ee8f548b2258d31");
                }
                
                {
                    auto hash = RIPEMD160("a");
                    auto hash_out = hash.hexdigest();
                    VERIFY_ARE_EQUAL(hash_out, "0bdc9d2d256b3ee9daae347be6f4dc835a467ffe");
                }
                
                {
                    auto hash = RIPEMD160("abc");
                    auto hash_out = hash.hexdigest();
                    VERIFY_ARE_EQUAL((hash_out), "8eb208f7e05d987a9b044a8e98c6b087f15a0bfc");
                }
                
                {
                    auto hash = RIPEMD160("message digest");
                    auto hash_out = hash.hexdigest();
                    VERIFY_ARE_EQUAL((hash_out), "5d0689ef49d2fae572b881b123a85ffa21595f36");
                }
            }
        }
    }
}

