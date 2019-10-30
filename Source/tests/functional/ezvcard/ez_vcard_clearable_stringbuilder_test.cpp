//
//  ez_vcard_ clearable_stringbuilder_test.cpp
//  OpenPGP
//
//  Created by Yanfeng Zhang on 1/18/17.
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

#include <ezvcard/ezvcard.hpp>
#include <ezvcard/vcard.hpp>
#include <ezvcard/io/buffer.hpp>


namespace tests {
    namespace ez_vcard_tests {
        SUITE(ez_vcard_clearable_stringbuilder_test)
        {
            
            TEST(get) {
                auto sb = std::make_shared<Buffer>();
                VERIFY_ARE_EQUAL("", sb->get());
                
                sb->append("foo");
                VERIFY_ARE_EQUAL("foo", sb->get());
                
                /*
                 * Internal buffer should not be modified when get() is called.
                 */
                VERIFY_ARE_EQUAL("foo", sb->get());
            }
            
            TEST(clear) {
                auto sb = std::make_shared<Buffer>();
                sb->append("foo");
                VERIFY_ARE_EQUAL("foo", sb->get());
                
                sb->clear();
                VERIFY_ARE_EQUAL("", sb->get());
            }

            TEST(getAndClear) {
                auto sb = std::make_shared<Buffer>();
                sb->append("foo");
                VERIFY_ARE_EQUAL("foo", sb->getAndClear());
                VERIFY_ARE_EQUAL("", sb->get());
            }
            
            TEST(append) {
                auto sb = std::make_shared<Buffer>();
                sb->append('f');
                sb->append("oo");
                sb->append(" bar!", 0, 4);
                VERIFY_ARE_EQUAL("foo bar", sb->get());
            }
            
            TEST(length) {
                auto  sb = std::make_shared<Buffer>();
                VERIFY_ARE_EQUAL(0, sb->size());
                
                sb->append("foo");
                VERIFY_ARE_EQUAL(3, sb->size());
            }
        }
    }
}
