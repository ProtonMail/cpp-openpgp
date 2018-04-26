//
//  utils_test.cpp
//  utils_test
//
//  Created by Yanfeng Zhang on 10/28/16.
//  Copyright © 2016 Yanfeng Zhang. All rights reserved.
//

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
