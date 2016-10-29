//
//  md5_test.cpp
//  OpenPGP
//
//  Created by Yanfeng Zhang on 10/28/16.
//  Copyright © 2016 Yanfeng Zhang. All rights reserved.
//

#import "utils_test.h"
#include <hash/MD5.h>

namespace tests {
    namespace hash_tests {
        SUITE(md5)
        {
            TEST(MD5_RFC_1321) {
                //MD5 with test vectors from RFC 1321
                {
                    auto md5_hash = MD5("");
                    auto md5_out = md5_hash.digest();
                    VERIFY_ARE_EQUAL(hexlify(md5_out), "d41d8cd98f00b204e9800998ecf8427e");
                }
                
                {
                    auto md5_hash = MD5("abc");
                    auto md5_out = md5_hash.digest();
                    VERIFY_ARE_EQUAL(hexlify(md5_out), "900150983cd24fb0d6963f7d28e17f72");
                }
                
                {
                    auto md5_hash = MD5("message digest");
                    auto md5_out = md5_hash.digest();
                    VERIFY_ARE_EQUAL(hexlify(md5_out), "f96b697d7cb7938d525a2f31aaf161d0");
                }
                
                {
                    auto md5_hash = MD5("abcdefghijklmnopqrstuvwxyz");
                    auto md5_out = md5_hash.digest();
                    VERIFY_ARE_EQUAL(hexlify(md5_out), "c3fcd3d76192e4007dfb496cca67e13b");
                }
                
                {
                    auto md5_hash = MD5("ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789");
                    auto md5_out = md5_hash.digest();
                    VERIFY_ARE_EQUAL(hexlify(md5_out), "d174ab98d277d9f5a5611c2c9f419d9f");
                }
                
                {
                    auto md5_hash = MD5("12345678901234567890123456789012345678901234567890123456789012345678901234567890");
                    auto md5_out = md5_hash.digest();
                    VERIFY_ARE_EQUAL(hexlify(md5_out), "57edf4a22be3c955ac49da2e2107b67a");
                }
                
            }
        }
    }
}
