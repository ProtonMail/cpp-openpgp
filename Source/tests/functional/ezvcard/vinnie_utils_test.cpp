//
//  vinnie_utils_test.cpp
//  OpenPGP
//
//  Created by Yanfeng Zhang on 12/7/16.
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
        SUITE(vinnie_util)
        {
            TEST(ltrim) {
                std::string actual, expected;
                actual = ltrim("One two three");
                expected = "One two three";
                VERIFY_ARE_EQUAL(actual, expected);
                
                actual = ltrim("\n \t One two three \t \n ");
                expected = "One two three \t \n ";
                VERIFY_ARE_EQUAL(actual, expected);
                
                actual = ltrim("\n \t \t \n ");
                expected = "";
                VERIFY_ARE_EQUAL(actual, expected);
                
                actual = ltrim("");
                expected = "";
                VERIFY_ARE_EQUAL(actual, expected);
            }
    
            TEST(rtrim) {
                std::string actual, expected;
                
                actual = rtrim("One two three");
                expected = "One two three";
                VERIFY_ARE_EQUAL(actual, expected);
                
                actual = rtrim("\n \t One two three \t \n ");
                expected = "\n \t One two three";
                VERIFY_ARE_EQUAL(actual, expected);
                
                actual = rtrim("\n \t \t \n ");
                expected = "";
                VERIFY_ARE_EQUAL(actual, expected);
                
                actual = rtrim("");
                expected = "";
                VERIFY_ARE_EQUAL(actual, expected);
            }
            
            TEST(escapeNewlines) {
                std::string input, actual, expected;
                
                input = "no newlines";
                actual = escapeNewlines(input);
                VERIFY_ARE_EQUAL(input, actual);
                
                input = "one\r\ntwo\nthree\r";
                actual = escapeNewlines(input);
                expected = "one\\ntwo\\nthree\\n";
                VERIFY_ARE_EQUAL(expected, actual);
                
                input = "";
                actual = escapeNewlines(input);
                VERIFY_ARE_EQUAL(input, actual);
            }
        }
    }
}
