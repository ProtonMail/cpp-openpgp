//
//  ez_vcard_tel_uri_test.cpp
//  OpenPGP
//
//  Created by Yanfeng Zhang on 6/4/17.
//  Copyright © 2017 Yanfeng Zhang. All rights reserved.
//

#include "utils_test.h"

#include <ezvcard/ezvcard.hpp>
#include <ezvcard/vcard.hpp>
#include <ezvcard/io/chain/chaining_text_string_parser.hpp>
#include "helper_property_sensei.hpp"
#include "clearable_string_builder.hpp"
#include "tel_uri.hpp"

using namespace ezvcard;

namespace tests {
    namespace ez_vcard_tests {
        SUITE(ez_vcard_tel_uri_test)
        {
            TEST(parse_number) {
                auto uri = TelUri::parse("tel:+1-212-555-0101");
                VERIFY_ARE_EQUAL(uri->getNumber(), "+1-212-555-0101");
                VERIFY_ARE_EQUAL(uri->getExtension(), "");
                VERIFY_ARE_EQUAL(uri->getPhoneContext(), "");
                VERIFY_ARE_EQUAL(uri->getIsdnSubaddress(), "");
                VERIFY_IS_TRUE(uri->getParameters().empty());
            }
            
            TEST(parse_extension) {
                auto uri = TelUri::parse("tel:+1-212-555-0101;ext=101");
                VERIFY_ARE_EQUAL("+1-212-555-0101", uri->getNumber());
                VERIFY_ARE_EQUAL("101", uri->getExtension());
                VERIFY_ARE_EQUAL(uri->getPhoneContext(), "");
                VERIFY_ARE_EQUAL(uri->getIsdnSubaddress(), "");
                VERIFY_IS_TRUE(uri->getParameters().empty());
            }
            
            TEST(parse_phoneContext) {
                auto uri = TelUri::parse("tel:0101;phone-context=example.com");
                VERIFY_ARE_EQUAL("0101", uri->getNumber());
                VERIFY_ARE_EQUAL(uri->getExtension(), "");
                VERIFY_ARE_EQUAL("example.com", uri->getPhoneContext());
                VERIFY_ARE_EQUAL(uri->getIsdnSubaddress(), "");
                VERIFY_IS_TRUE(uri->getParameters().empty());
            }
            
            TEST(parse_isdnSubaddress) {
                auto uri = TelUri::parse("tel:+1-212-555-0101;isub=value");
                VERIFY_ARE_EQUAL("+1-212-555-0101", uri->getNumber());
                VERIFY_ARE_EQUAL(uri->getExtension(), "");
                VERIFY_ARE_EQUAL(uri->getPhoneContext(), "");
                VERIFY_ARE_EQUAL("value", uri->getIsdnSubaddress());
                VERIFY_IS_TRUE(uri->getParameters().empty());
            }
            
            TEST(parse_multiple_params) {
                auto uri = TelUri::parse("tel:+1-212-555-0101;param1=value1;param2=value2");
                VERIFY_ARE_EQUAL("+1-212-555-0101", uri->getNumber());
                VERIFY_ARE_EQUAL(uri->getExtension(), "");
                VERIFY_ARE_EQUAL(uri->getPhoneContext(), "");
                VERIFY_ARE_EQUAL(uri->getIsdnSubaddress(), "");
                VERIFY_ARE_EQUAL("value1", uri->getParameter("param1"));
                VERIFY_ARE_EQUAL("value2", uri->getParameter("param2"));
                VERIFY_ARE_EQUAL("", uri->getParameter("param3"));
                std::map<std::string, std::string> params;
                params["param1"] = "value1";
                params["param2"] = "value2";
                VERIFY_ARE_EQUAL(params, uri->getParameters());
            }
            
            TEST(parse_param_no_value) {
                auto uri = TelUri::parse("tel:+1-212-555-0101;param1;param2=;param3=");
                VERIFY_ARE_EQUAL("+1-212-555-0101", uri->getNumber());
                VERIFY_ARE_EQUAL(uri->getExtension(), "");
                VERIFY_ARE_EQUAL(uri->getPhoneContext(), "");
                VERIFY_ARE_EQUAL(uri->getIsdnSubaddress(), "");
                VERIFY_ARE_EQUAL("", uri->getParameter("param1"));
                VERIFY_ARE_EQUAL("", uri->getParameter("param2"));
                VERIFY_ARE_EQUAL("", uri->getParameter("param3"));
                std::map<std::string, std::string> params;
                params["param1"] = "";
                params["param2"] = "";
                params["param3"] = "";
                VERIFY_ARE_EQUAL(params, uri->getParameters());
            }
            
            TEST(parse_param_multiple_semicolons) {
                auto uri = TelUri::parse("tel:+1-212-555-0101;param1=value1;;param2=value2;");
                VERIFY_ARE_EQUAL("+1-212-555-0101", uri->getNumber());
                VERIFY_ARE_EQUAL(uri->getExtension(), "");
                VERIFY_ARE_EQUAL(uri->getPhoneContext(), "");
                VERIFY_ARE_EQUAL(uri->getIsdnSubaddress(), "");
                VERIFY_ARE_EQUAL("value1", uri->getParameter("param1"));
                VERIFY_ARE_EQUAL("value2", uri->getParameter("param2"));
                std::map<std::string, std::string> params;
                params["param1"] = "value1";
                params["param2"] = "value2";
                VERIFY_ARE_EQUAL(params, uri->getParameters());
            }
            
            TEST(parse_decode_special_chars_in_param_value) {
                auto uri = TelUri::parse("tel:+1-212-555-0101;param=with%20%3d%20special%20&%20chars");
                VERIFY_ARE_EQUAL("+1-212-555-0101", uri->getNumber());
                VERIFY_ARE_EQUAL(uri->getExtension(), "");
                VERIFY_ARE_EQUAL(uri->getPhoneContext(), "");
                VERIFY_ARE_EQUAL(uri->getIsdnSubaddress(), "");
                VERIFY_ARE_EQUAL("with = special & chars", uri->getParameter("param"));
            }
            
            TEST(parse_empty) {
                auto uri = TelUri::parse("tel:");
                VERIFY_ARE_EQUAL("", uri->getNumber());
                VERIFY_ARE_EQUAL(uri->getExtension(), "");
                VERIFY_ARE_EQUAL(uri->getPhoneContext(), "");
                VERIFY_ARE_EQUAL(uri->getIsdnSubaddress(), "");
                VERIFY_IS_TRUE(uri->getParameters().empty());
            }
            
            TEST(parse_not_tel_uri) {
                VERIFY_THROWS(TelUri::parse("http://www.ietf.org"), std::invalid_argument);
            }
            
            TEST(builder_global) {
                auto uri = Tel::Builder("+1-212-555-0101").build();
                VERIFY_ARE_EQUAL("+1-212-555-0101", uri->getNumber());
                VERIFY_ARE_EQUAL(uri->getExtension(), "");
                VERIFY_ARE_EQUAL(uri->getPhoneContext(), "");
                VERIFY_ARE_EQUAL(uri->getIsdnSubaddress(), "");
                VERIFY_IS_TRUE(uri->getParameters().empty());
            }
            
            TEST(builder_global_no_plus) {
                VERIFY_THROWS(Tel::Builder("1-212-555-0101"), std::invalid_argument);
            }
            
            TEST(builder_global_invalid) {
                VERIFY_THROWS(Tel::Builder("abc123"), std::invalid_argument);
            }
            
            TEST(builder_local) {
                auto uri = Tel::Builder("0101", "example.com").build();
                VERIFY_ARE_EQUAL("0101", uri->getNumber());
                VERIFY_ARE_EQUAL(uri->getExtension(), "");
                VERIFY_ARE_EQUAL("example.com", uri->getPhoneContext());
                VERIFY_ARE_EQUAL(uri->getIsdnSubaddress(), "");
                VERIFY_IS_TRUE(uri->getParameters().empty());
            }
            
            TEST(builder_local_invalid) {
                VERIFY_THROWS(Tel::Builder("abc123", "example.com"), std::invalid_argument);
            }
            
            TEST(builder_extension_invalid) {
                auto builder = Tel::Builder("+1-212-555-0101");
                VERIFY_THROWS(builder.extension("!not-valid!"), std::invalid_argument);
            }
            
            TEST(builder_parameter) {
                auto builder = Tel::Builder("+1-212-555-0101");
                builder.parameter("one", "1");
                builder.parameter("two", "2");
                builder.parameter("one", "");
                auto uri = builder.build();
                
                VERIFY_ARE_EQUAL(uri->getParameter("one"), ""); //removed
                VERIFY_ARE_EQUAL("2", uri->getParameter("two"));
                VERIFY_ARE_EQUAL(uri->getParameter("three"), "");
                
                std::map<std::string, std::string> expected;
                expected["two"] = "2";
                VERIFY_ARE_EQUAL(expected, uri->getParameters());
            }
            
            TEST(builder_parmaeter_invalid_name) {
                auto builder = Tel::Builder("+1-212-555-0101");
                VERIFY_THROWS(builder.parameter("!not-val9id!", "the value"), std::invalid_argument);
            }
            
            //            TEST(builder_copy_constructor) {
            //                TelUri orig = new TelUri.Builder("+1-212-555-0101").extension("111").isdnSubaddress("isdn").parameter("name", "value").build();
            //                TelUri copy = new TelUri.Builder(orig).build();
            //                assertEquals(orig, copy);
            //            }
            
            TEST(getParameters_unmodifiable) {
                auto uri = Tel::Builder("+1-212-555-0101").build();
                uri->put("one", "1");
                // VERIFY_THROWS(builder.parameter("!not-val9id!", "the value"), std::invalid_argument);
            }
            
            TEST(toString_) {
                auto builder = Tel::Builder("+1-212-555-0101");
                builder.extension("101");
                auto uri = builder.build();
                VERIFY_ARE_EQUAL("tel:+1-212-555-0101;ext=101", uri->toString());
            }
            
            //see RFC 3966, bottom of p.5
            TEST(toString_parameter_order) {
                auto builder = Tel::Builder("1010", "example.com");
                builder.extension("101");
                builder.isdnSubaddress("isdn");
                builder.parameter("zebra", "z-value");
                builder.parameter("apple", "a-value");
                auto uri = builder.build();
                VERIFY_ARE_EQUAL("tel:1010;ext=101;isub=isdn;phone-context=example.com;apple=a-value;zebra=z-value", uri->toString());
            }
            
            TEST(toString_special_chars_in_param_value) {
                auto builder = Tel::Builder("+1-212-555-0101");
                std::stringstream ss("");
                ss << "with = special & chars ";
                ss << (char)128;
                builder.parameter("param", ss.str());
                auto uri = builder.build();
                VERIFY_ARE_EQUAL("tel:+1-212-555-0101;param=with%20%3d%20special%20&%20chars%20%80", uri->toString());
            }
            
            TEST(equals_ignore_case) {
                auto builder = Tel::Builder("+18001234567");
                builder.isdnSubaddress("B");
                builder.parameter("NAME", "VALUE");
                auto one = builder.build();
                
                builder = Tel::Builder("+18001234567");
                builder.isdnSubaddress("b");
                builder.parameter("name", "value");
                auto two = builder.build();
                
                one->equals(two);
            }
        }
        
    }
}
