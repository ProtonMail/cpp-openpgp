//
//  vcard_buffer_test.cpp
//  OpenPGP
//
//  Created by Yanfeng Zhang on 12/6/16.
//  Copyright © 2016 Yanfeng Zhang. All rights reserved.
//

#include "utils_test.h"

#include <list>
#include <string>

#include <ezvcard/io/buffer.hpp>

namespace tests {
    namespace ez_vcard_tests {
        SUITE(vinnie_buffer)
        {
            TEST(buffer_clear) {
                Buffer buffer;
                VERIFY_ARE_EQUAL("", buffer.get());
                buffer.append('a');
                VERIFY_ARE_EQUAL("a", buffer.get());
                buffer.clear();
                VERIFY_ARE_EQUAL("", buffer.get());
            }
            
            TEST(buffer_getAndClear) {
                Buffer buffer;
                buffer.append('a');
                VERIFY_ARE_EQUAL("a", buffer.getAndClear());
                VERIFY_ARE_EQUAL("", buffer.get());
                VERIFY_ARE_EQUAL("", buffer.getAndClear());
                VERIFY_ARE_EQUAL("", buffer.get());
            }
            
            TEST(buffer_append) {
                Buffer buffer;
                buffer.append('a');
                buffer.append("bcd");
                VERIFY_ARE_EQUAL("abcd", buffer.get());
            }
            
            TEST(buffer_chop) {
                Buffer buffer;
                buffer.append('a');
                buffer.append('b');
                buffer.chop();
                VERIFY_ARE_EQUAL("a", buffer.get());
                
                buffer.chop();
                VERIFY_ARE_EQUAL("", buffer.get());
                VERIFY_ARE_EQUAL(0, buffer.size());
                
                buffer.chop();
                VERIFY_ARE_EQUAL("", buffer.get());
                VERIFY_ARE_EQUAL(0, buffer.size());
            }
            
            TEST(buffer_size) {
                Buffer buffer;
                VERIFY_ARE_EQUAL(0, buffer.size());
                
                buffer.append('a');
                VERIFY_ARE_EQUAL(1, buffer.size());
                
                buffer.clear();
                VERIFY_ARE_EQUAL(0, buffer.size());
            }
        }
    }
}

