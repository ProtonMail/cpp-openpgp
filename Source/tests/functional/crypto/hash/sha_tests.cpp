//
//  sha_tests.cpp
//  OpenPGP
//
//  Created by Yanfeng Zhang on 10/28/16.
//  Copyright © 2016 Yanfeng Zhang. All rights reserved.
//

#import "utils_test.h"
#include <hash/Hashes.h>

namespace tests {
    namespace hash_tests {
        SUITE(sha)
        {
            //SHA* with test vectors from NIST FIPS 180-2
            TEST(SHA_1) {
                {
                    auto hash = SHA1("abc");
                    auto hash_out = hash.hexdigest();
                    VERIFY_ARE_EQUAL((hash_out), "a9993e364706816aba3e25717850c26c9cd0d89d");
                }
                
                {
                    auto hash = SHA1("abcdbcdecdefdefgefghfghighijhijkijkljklmklmnlmnomnopnopq");
                    auto hash_out = hash.hexdigest();
                    VERIFY_ARE_EQUAL((hash_out), "84983e441c3bd26ebaae4aa1f95129e5e54670f1");
                }
            }
            
            TEST(SHA_224) {
                {
                    auto hash = SHA224("abc");
                    auto hash_out = hash.hexdigest();
                    VERIFY_ARE_EQUAL((hash_out), "23097d223405d8228642a477bda255b32aadbce4bda0b3f7e36c9da7");
                }
                
                {
                    auto hash = SHA224("abcdbcdecdefdefgefghfghighijhijkijkljklmklmnlmnomnopnopq");
                    auto hash_out = hash.hexdigest();
                    VERIFY_ARE_EQUAL((hash_out), "75388b16512776cc5dba5da1fd890150b0c6455cb4f58b1952522525");
                }
            }
            
            TEST(SHA_256) {
                {
                    auto hash = SHA256("abc");
                    auto hash_out = hash.hexdigest();
                    VERIFY_ARE_EQUAL((hash_out), "ba7816bf8f01cfea414140de5dae2223b00361a396177a9cb410ff61f20015ad");
                }
                
                {
                    auto hash = SHA256("abcdbcdecdefdefgefghfghighijhijkijkljklmklmnlmnomnopnopq");
                    auto hash_out = hash.hexdigest();
                    VERIFY_ARE_EQUAL((hash_out), "248d6a61d20638b8e5c026930c3e6039a33ce45964ff2167f6ecedd419db06c1");
                }
            }
            
            TEST(SHA_384) {
                {
                    auto hash = SHA384("abc");
                    auto hash_out = hash.hexdigest();
                    VERIFY_ARE_EQUAL((hash_out), "cb00753f45a35e8bb5a03d699ac65007272c32ab0eded1631a8b605a43ff5bed8086072ba1e7cc2358baeca134c825a7");
                }
                
                {
                    auto hash = SHA384("abcdbcdecdefdefgefghfghighijhijkijkljklmklmnlmnomnopnopq");
                    auto hash_out = hash.hexdigest();
                    VERIFY_ARE_EQUAL((hash_out), "3391fdddfc8dc7393707a65b1b4709397cf8b1d162af05abfe8f450de5f36bc6b0455a8520bc4e6f5fe95b1fe3c8452b");
                }
            }
            
            TEST(SHA_512) {
                {
                    auto hash = SHA512("abc");
                    auto hash_out = hash.hexdigest();
                    VERIFY_ARE_EQUAL((hash_out), "ddaf35a193617abacc417349ae20413112e6fa4e89a97ea20a9eeee64b55d39a2192992a274fc1a836ba3c23a3feebbd454d4423643ce80e2a9ac94fa54ca49f");
                }
                
                {
                    auto hash = SHA512("abcdbcdecdefdefgefghfghighijhijkijkljklmklmnlmnomnopnopq");
                    auto hash_out = hash.hexdigest();
                    VERIFY_ARE_EQUAL((hash_out), "204a8fc6dda82f0a0ced7beb8e08a41657c16ef468b228a8279be331a703c33596fd15c13b1b07f9aa1d3bea57789ca031ad85c7a71dd70354ec631238ca3445");
                }
            }
        }
    }
}


