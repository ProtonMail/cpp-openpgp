//
//  util_string_test.cpp
//  OpenPGP
//
//  Created by Yanfeng Zhang on 12/5/16.
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


#include <ezvcard/util/string_util.hpp>


#include <list>
#include <string>


namespace tests {
    namespace ez_vcard_tests {
        SUITE(ez_vcard_util)
        {
            TEST(string_compare) {
                {
                    auto str1 = "Hello";
                    auto str2 = "hello";
                    auto is_equal = str_equals(str1, str2);
                    VERIFY_IS_TRUE(is_equal);
                }
                
                {
                    auto str1 = "1";
                    auto str2 = "1";
                    auto is_equal = str_equals(str1, str2);
                    VERIFY_IS_TRUE(is_equal);
                }
                
                {
                    auto str1 = "50";
                    auto str2 = "50";
                    auto is_equal = str_equals(str1, str2);
                    VERIFY_IS_TRUE(is_equal);
                }
                
                {
                    auto str1 = "1a1";
                    auto str2 = "1a1";
                    auto is_equal = str_equals(str1, str2);
                    VERIFY_IS_TRUE(is_equal);
                }
                
                {
                    auto str1 = "a0001a.html";
                    auto str2 = "a0001a.html";
                    auto is_equal = str_equals(str1, str2);
                    VERIFY_IS_TRUE(is_equal);
                }
                
                {
                    auto str1 = "Hello world!";
                    auto str2 = "Hello world.";
                    auto is_equal = str_equals(str1, str2);
                    VERIFY_IS_FALSE(is_equal);
                }
                
                {
                    auto str1 = "hello, world!";
                    auto str2 = "HELLO, WORLD!";
                    auto is_equal = str_equals(str1, str2);
                    VERIFY_IS_TRUE(is_equal);
                }
                
                std::list<std::string> syntax = std::list<std::string>();
                syntax.push_back("1");
                syntax.push_back("2");
                syntax.push_back("3");
                syntax.push_back("4");
                syntax.pop_back();
                syntax.push_back("5");
                auto verfify = syntax.back();
                VERIFY_ARE_EQUAL(verfify, "5");
            }
        }
    }
}
