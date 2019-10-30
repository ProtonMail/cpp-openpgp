//
//  vcard_buffer_test.cpp
//  OpenPGP
//
//  Created by Yanfeng Zhang on 12/6/16.
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

