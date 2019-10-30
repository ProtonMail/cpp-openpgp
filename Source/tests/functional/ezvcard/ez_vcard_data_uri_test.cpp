//
//  ez_vcard_data_uri_test.cpp
//  ezvcard_test
//
//  Created by Yanfeng Zhang on 4/5/18.
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
#include <ezvcard/io/chain/chaining_text_string_parser.hpp>
#include "helper_property_sensei.hpp"
#include "clearable_string_builder.hpp"
#include "data_uri.hpp"
#include "base64.h"
#include <exception>

using namespace ezvcard;

namespace tests {
    namespace ez_vcard_tests {
        SUITE(ez_vcard_data_uri_test)
        {
            
            const std::string dataString = "test-data";
            const std::string dataBytes = dataString;
            
//            private final byte[] dataBytes;
//            {
//                try {
//                    dataBytes = dataString.getBytes("UTF-8");
//                } catch (UnsupportedEncodingException e) {
//                    throw new RuntimeException(e);
//                }
//            }
//            private final String dataBase64 = Base64.encodeBase64String(dataBytes);
            TEST(constructor) {
                DataUri::Ptr uri = std::make_shared<DataUri>("text");
                
                VERIFY_ARE_EQUAL("text/plain", uri->getContentType());
                VERIFY_ARE_EQUAL(uri->getData(), "");
                VERIFY_ARE_EQUAL("text", uri->getText());
                
                uri = std::make_shared<DataUri>("text/html", "text", true);
                VERIFY_ARE_EQUAL("text/html", uri->getContentType());
                VERIFY_ARE_EQUAL(uri->getData(), "");
                VERIFY_ARE_EQUAL("text", uri->getText());
                
                //convert content type to lower case
                uri = std::make_shared<DataUri>("TEXT/HTML", "text", true);
                VERIFY_ARE_EQUAL("text/html", uri->getContentType());
                VERIFY_ARE_EQUAL(uri->getData(), "");
                VERIFY_ARE_EQUAL("text", uri->getText());

                uri = std::make_shared<DataUri>("image/png", dataBytes, false);
                VERIFY_ARE_EQUAL("image/png", uri->getContentType());
                VERIFY_ARE_EQUAL(uri->getData(), dataBytes);
                VERIFY_ARE_EQUAL("", uri->getText());
                
                //convert null content type to empty string
                uri = std::make_shared<DataUri>("", dataBytes, false);
                VERIFY_ARE_EQUAL("", uri->getContentType());
            }
            
            TEST(copy) {
                DataUri::Ptr uri = std::make_shared<DataUri>("text/html", "text", true);
                DataUri::Ptr copy = std::make_shared<DataUri>(uri);
                VERIFY_ARE_EQUAL("text/html", copy->getContentType());
                VERIFY_ARE_EQUAL(copy->getData(), "");
                VERIFY_ARE_EQUAL("text", copy->getText());
                //assertEqualsAndHash(uri, copy);
                
                uri = std::make_shared<DataUri>("image/png", dataBytes, false);
                copy = std::make_shared<DataUri>(uri);
                VERIFY_ARE_EQUAL("image/png", copy->getContentType());
                VERIFY_ARE_EQUAL(copy->getData(), dataBytes);
                VERIFY_ARE_EQUAL("", copy->getText());
                //assertEqualsAndHash(uri, copy);
            }

            TEST(parse) {
                auto dataBase64 = base64_encode(dataBytes);
                DataUri::Ptr expected = std::make_shared<DataUri>("image/png", dataBytes, false);
                DataUri::Ptr actual = DataUri::parse("data:image/png;base64," + dataBase64);
                VERIFY_IS_TRUE(expected->equals(actual));
                
                expected = std::make_shared<DataUri>("", dataBytes, false);
                actual = DataUri::parse("data:;base64," + dataBase64);
                VERIFY_IS_TRUE(expected->equals(actual));
                
                expected = std::make_shared<DataUri>("image/png", dataString, true);
                actual = DataUri::parse("data:image/png;charset=UTF-8;base64," + dataBase64);
                VERIFY_IS_TRUE(expected->equals(actual));
                
                //order of charset and base64 matter
                expected = std::make_shared<DataUri>("image/png", dataString, true);
                actual = DataUri::parse("data:image/png;base64;charset=UTF-8," + dataBase64);
                VERIFY_IS_TRUE(expected->equals(actual));
                
                //ignore unknown tokens
                expected = std::make_shared<DataUri>("image/png", dataString, true);
                actual = DataUri::parse("data:image/png;charset=UTF-8;foo;base64;bar," + dataBase64);
                VERIFY_IS_TRUE(expected->equals(actual));
                
                expected = std::make_shared<DataUri>("image/png", dataBase64, true);
                actual = DataUri::parse("data:image/png;charset=UTF-8," + dataBase64);
                VERIFY_IS_TRUE(expected->equals(actual));
                
                expected = std::make_shared<DataUri>("image/png", dataBase64, true);
                actual = DataUri::parse("data:image/png;charset=UTF-8;foobar," + dataBase64);
                VERIFY_IS_TRUE(expected->equals(actual));
            }

            TEST(parse_comma_in_content_type) {
                auto dataBase64 = base64_encode(dataBytes);
                DataUri::Ptr expected = std::make_shared<DataUri>("text/pla", "in;base64," + dataBase64, true);
                DataUri::Ptr actual = DataUri::parse("data:text/pla,in;base64," + dataBase64);
                VERIFY_IS_TRUE(expected->equals(actual));
            }
            
            TEST(parse_short_string) {
                VERIFY_THROWS(DataUri::parse("a"), std::invalid_argument);
            }
            
            TEST(parse_not_a_uri) {
                VERIFY_THROWS(DataUri::parse("not-valid"), std::invalid_argument);
            }
            
            TEST(parse_wrong_scheme) {
                VERIFY_THROWS(DataUri::parse("mailto:johndoe@gmail.com"), std::invalid_argument);
            }
            
            TEST(parse_no_comma) {
                VERIFY_THROWS(DataUri::parse("data:text/plain;base64"), std::invalid_argument);
            }
            
//            TEST(parse_bad_charset) {
//                auto dataBase64 = base64_encode(dataBytes);
//                VERIFY_THROWS(DataUri::parse("data:text/plain;charset=foobar;base64," + dataBase64), std::invalid_argument);
//            }

                                
            TEST(toString_) {
                auto dataBase64 = base64_encode(dataBytes);
                DataUri::Ptr uri = std::make_shared<DataUri>("text/plain", dataBytes, false);
                VERIFY_ARE_EQUAL("data:text/plain;base64," + dataBase64, uri->toString());

                uri = std::make_shared<DataUri>("text/plain", dataBytes, false);
                VERIFY_ARE_EQUAL("data:text/plain;base64," + dataBase64, uri->toString("UTF-8"));

                uri = std::make_shared<DataUri>("text/plain", dataString, true);
                VERIFY_ARE_EQUAL("data:text/plain," + dataString, uri->toString());

                uri = std::make_shared<DataUri>("text/plain", dataString, true);
                VERIFY_ARE_EQUAL("data:text/plain;charset=UTF-8;base64," + dataBase64, uri->toString("UTF-8"));

                uri = std::make_shared<DataUri>("text/plain", "", true);
                VERIFY_ARE_EQUAL("data:text/plain,", uri->toString());
            }
            
//            TEST(toString_bad_charset) {
//                DataUri::Ptr uri = std::make_shared<DataUri>("text/plain", dataString, true);
//                VERIFY_THROWS( uri->toString("foobar"), std::invalid_argument));
//            }

            TEST(equals) {
                
                auto uri1 = std::make_shared<DataUri>("text/plain", dataBytes, false);
                auto uri2 = std::make_shared<DataUri>("image/png", dataBytes, false);
                auto uri3 = std::make_shared<DataUri>("text/plain", "other-string", false);
                auto uri4 = std::make_shared<DataUri>("text/plain", dataString, true);
                auto uri5 = std::make_shared<DataUri>("text/html", dataString, true);
                auto uri6 = std::make_shared<DataUri>("text/plain", "other-string", true);
                auto uri7 = std::make_shared<DataUri>("text/plain", "", true);
                
                VERIFY_IS_FALSE(uri1->equals(uri2));
                VERIFY_IS_FALSE(uri2->equals(uri3));
                VERIFY_IS_FALSE(uri3->equals(uri4));
                VERIFY_IS_FALSE(uri4->equals(uri5));
                VERIFY_IS_FALSE(uri5->equals(uri6));
                VERIFY_IS_FALSE(uri6->equals(uri7));
                //
            }
        }
    }
}
