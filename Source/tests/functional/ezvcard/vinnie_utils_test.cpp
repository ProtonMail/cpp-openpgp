//
//  vinnie_utils_test.cpp
//  OpenPGP
//
//  Created by Yanfeng Zhang on 12/7/16.
//  Copyright © 2016 Yanfeng Zhang. All rights reserved.
//

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
