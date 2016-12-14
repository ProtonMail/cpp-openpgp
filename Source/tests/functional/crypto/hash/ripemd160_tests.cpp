//
//  ripemd160_tests.cpp
//  OpenPGP
//
//  Created by Yanfeng Zhang on 10/28/16.
//  Copyright © 2016 Yanfeng Zhang. All rights reserved.
//

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

