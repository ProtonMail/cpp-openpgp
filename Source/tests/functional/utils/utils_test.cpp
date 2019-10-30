//
//  utils_test.cpp
//  utils_test
//
//  Created by Yanfeng Zhang on 10/28/16.
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


#import "utils_test.h"
#include <utilities/base64.h>
#include <regex>

namespace tests {
    
    namespace utils_tests {
        
        SUITE(base64)
        {
            
            TEST(trim_string_) {
                std::string body = "Asdhfjkhsadfsad asdfasdf.    \nAsdfsadf.  Asdfsdaf      \nAsdfs.    ";
                std::regex re("([ \t]+)(?=(\\r\\n|\\n)|$)");
                body = std::regex_replace(body, re, "");
                std::cout << body << std::endl;
                VERIFY_ARE_EQUAL("Asdhfjkhsadfsad asdfasdf.\nAsdfsadf.  Asdfsdaf\nAsdfs.", body);
            }
            
            // Note: base64 works6 by encoding any 3 bytes as a four-byte string. Each triple is encoded independently of
            // previous and subsequent triples. If, for a given set of input bytes, the number is not an even multiple of 3,
            // the remaining 1 or two bytes are encoded and padded using '=' characters at the end. The encoding format is
            // defined by IETF RFC 4648. Such padding is only allowed at the end of a encoded string, which makes it impossible
            // to generally concatenate encoded strings and wind up with a string that is a valid base64 encoding.
            //
            // Since each triple of bytes is independent of others, we don't have to test particularly large sets if input data,
            // validating that the algorithm can process at least two triples should be sufficient.
            //
            TEST(rfc_4648_tests_encode)
            {
                // These tests are what base64 RFC 4648 proposes.
                {
                    std::vector<unsigned char> str1;
                    VERIFY_ARE_EQUAL("", base64_encode(std::string(str1.begin(), str1.end())));
                }
//                {
//                    std::vector<unsigned char> str1;
//                    str1.push_back('f');
//                    VERIFY_ARE_EQUAL(string_t(_XPLATSTR("Zg==")), utility::conversions::to_base64(str1));
//                }
//                {
//                    std::vector<unsigned char> str1;
//                    str1.push_back('f');
//                    str1.push_back('o');
//                    VERIFY_ARE_EQUAL(string_t(_XPLATSTR("Zm8=")), utility::conversions::to_base64(str1));
//                }
//                {
//                    std::vector<unsigned char> str1;
//                    str1.push_back('f');
//                    str1.push_back('o');
//                    str1.push_back('o');
//                    VERIFY_ARE_EQUAL(string_t(_XPLATSTR("Zm9v")), utility::conversions::to_base64(str1));
//                }
//                {
//                    std::vector<unsigned char> str1;
//                    str1.push_back('f');
//                    str1.push_back('o');
//                    str1.push_back('o');
//                    str1.push_back('b');
//                    VERIFY_ARE_EQUAL(string_t(_XPLATSTR("Zm9vYg==")), utility::conversions::to_base64(str1));
//                }
//                {
//                    std::vector<unsigned char> str1;
//                    str1.push_back('f');
//                    str1.push_back('o');
//                    str1.push_back('o');
//                    str1.push_back('b');
//                    str1.push_back('a');
//                    VERIFY_ARE_EQUAL(string_t(_XPLATSTR("Zm9vYmE=")), utility::conversions::to_base64(str1));
//                }
//                {
//                    std::vector<unsigned char> str1;
//                    str1.push_back('f');
//                    str1.push_back('o');
//                    str1.push_back('o');
//                    str1.push_back('b');
//                    str1.push_back('a');
//                    str1.push_back('r');
//                    VERIFY_ARE_EQUAL(string_t(_XPLATSTR("Zm9vYmFy")), utility::conversions::to_base64(str1));
//                }
            }
        }
    }
}
