//
//  util_string_test.cpp
//  OpenPGP
//
//  Created by Yanfeng Zhang on 12/5/16.
//  Copyright © 2016 Yanfeng Zhang. All rights reserved.
//

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
