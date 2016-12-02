//
//  vinnie_vobject_parameters_test.cpp
//  OpenPGP
//
//  Created by Yanfeng Zhang on 1/4/17.
//  Copyright © 2017 Yanfeng Zhang. All rights reserved.
//


#include "utils_test.h"


#include <ezvcard/util/string_util.hpp>
#include <ezvcard/parameter/vobject_parameters.hpp>

#include <list>
#include <string>
#include <vector>
#include <codecvt>
#include "std_extension.hpp"

namespace tests {
    namespace ez_vcard_tests {
        
        using namespace vinnie;
        
    
        SUITE(vinnie_vobject_parameters)
        {
            TEST(convert_keys_to_uppercase) {
                auto parameters = std::make_shared<VObjectParameters>();
                parameters->put("name", "value1");
                parameters->put("Name", "value2");
                
                std::unordered_map<std::string, std::vector<std::string>> expected;
                expected["NAME"] = std::vector<std::string> {"value1", "value2"};
                VERIFY_IS_TRUE(expected == parameters->getMap());
                
                auto values_list = parameters->get("Name");
                VERIFY_ARE_EQUAL(values_list.size(), 2);
                auto values = std::vector<std::string> {"value1", "value2"};
                VERIFY_IS_TRUE(values_list == values);
                
                VERIFY_IS_TRUE( parameters->remove("nAme", "value1") );
                values_list = parameters->removeAll("naMe");
                VERIFY_ARE_EQUAL(values_list.size(), 1);
                values = std::vector<std::string> { std::begin(values_list), std::end(values_list) };
                values = std::vector<std::string> {"value2"};
                VERIFY_IS_TRUE(values_list == values);
            }
            
            TEST(multivalued_keys) {
                auto parameters = std::make_shared<VObjectParameters>();
                parameters->putAll("name", {"value1", "value1", "value2"});
                parameters->putAll("name2", {});
                
                auto values_list = parameters->get("name");
                VERIFY_ARE_EQUAL(values_list.size(), 3);
                auto values = std::vector<std::string> { std::begin(values_list), std::end(values_list) };
                auto v1 = values[0];
                VERIFY_ARE_EQUAL(v1, "value1");
                auto v2 = values[1];
                VERIFY_ARE_EQUAL(v2, "value1");
                auto v3 = values[2];
                VERIFY_ARE_EQUAL(v3, "value2");
                
                VERIFY_IS_TRUE(parameters->get("name2").size() == 0);
                VERIFY_IS_TRUE(parameters->get("name3").size() == 0);
            }
            
            TEST(replace) {
                auto parameters = std::make_shared<VObjectParameters>();
                parameters->put("name1", "value1");
                
                auto replaced_list = parameters->replace("name1", "value2");
                auto values = std::vector<std::string> { std::begin(replaced_list), std::end(replaced_list) };
                VERIFY_ARE_EQUAL(values.size(), 1);
                auto v1 = values[0];
                VERIFY_ARE_EQUAL(v1, "value1");
                
                replaced_list = parameters->replace("name2", "value3");
                VERIFY_ARE_EQUAL(replaced_list.size(), 0);
                
                auto map = parameters->getMap();
                VERIFY_IS_TRUE(map.size() == 2);
                
                auto values_list = parameters->get("NAME1");
                VERIFY_ARE_EQUAL(values_list.size(), 1);
                values = std::vector<std::string> { std::begin(values_list), std::end(values_list) };
                v1 = values[0];
                VERIFY_ARE_EQUAL(v1, "value2");
                
                values_list = parameters->get("NAME2");
                VERIFY_ARE_EQUAL(values_list.size(), 1);
                values = std::vector<std::string> { std::begin(values_list), std::end(values_list) };
                v1 = values[0];
                VERIFY_ARE_EQUAL(v1, "value3");
                
            }
            
            TEST(replaceAll) {
                auto parameters = std::make_shared<VObjectParameters>();
                parameters->put("name1", "value1");
                
                auto chekclist = parameters->replaceAll("name1", {"value2", "value3"});
                VERIFY_ARE_EQUAL(chekclist.size(), 1);
                auto values = std::vector<std::string> { std::begin(chekclist), std::end(chekclist) };
                auto check = values[0];
                VERIFY_ARE_EQUAL(check, "value1");
                
                chekclist = parameters->replaceAll("name2", {"value4", "value5"});
                VERIFY_ARE_EQUAL(chekclist.size(), 0);
                
                auto map = parameters->getMap();
                VERIFY_IS_TRUE(map.size() == 2);
                
                chekclist = parameters->get("NAME1");
                VERIFY_ARE_EQUAL(chekclist.size(), 2);
                values = std::vector<std::string> { std::begin(chekclist), std::end(chekclist) };
                check = values[0];
                VERIFY_ARE_EQUAL(check, "value2");
                check = values[1];
                VERIFY_ARE_EQUAL(check, "value3");
                
                chekclist = parameters->get("NAME2");
                VERIFY_ARE_EQUAL(chekclist.size(), 2);
                values = std::vector<std::string> { std::begin(chekclist), std::end(chekclist) };
                check = values[0];
                VERIFY_ARE_EQUAL(check, "value4");
                check = values[1];
                VERIFY_ARE_EQUAL(check, "value5");
                
                chekclist = parameters->replaceAll("name1", {});
                VERIFY_ARE_EQUAL(chekclist.size(), 2);
                values = std::vector<std::string> { std::begin(chekclist), std::end(chekclist) };
                check = values[0];
                VERIFY_ARE_EQUAL(check, "value2");
                check = values[1];
                VERIFY_ARE_EQUAL(check, "value3");
                
                map = parameters->getMap();
                VERIFY_IS_TRUE(map.size() == 1);
                
                chekclist = parameters->get("NAME2");
                VERIFY_ARE_EQUAL(chekclist.size(), 2);
                values = std::vector<std::string> { std::begin(chekclist), std::end(chekclist) };
                check = values[0];
                VERIFY_ARE_EQUAL(check, "value4");
                check = values[1];
                VERIFY_ARE_EQUAL(check, "value5");
            }
            
            TEST(remove) {
                auto parameters = std::make_shared<VObjectParameters>();
                parameters->put("name1", "value1");
                parameters->put("name2", "value1");
                parameters->put("name2", "value2");
                
                VERIFY_IS_TRUE(parameters->remove("name1", "value1"));
                VERIFY_IS_FALSE(parameters->remove("name1", "value3"));
                VERIFY_IS_FALSE(parameters->remove("name3", "value1"));
                VERIFY_IS_TRUE(parameters->remove("name2", "value1"));
                
                auto map = parameters->getMap();
                VERIFY_IS_TRUE(map.size() == 2);
                
                auto chekclist = parameters->get("NAME1");
                VERIFY_ARE_EQUAL(chekclist.size(), 0);
                
                chekclist = parameters->get("NAME2");
                VERIFY_ARE_EQUAL(chekclist.size(), 1);
                auto values = std::vector<std::string> { std::begin(chekclist), std::end(chekclist) };
                auto check = values[0];
                VERIFY_ARE_EQUAL(check, "value2");
            }
            
            TEST(removeAll) {
                auto parameters = std::make_shared<VObjectParameters>();
                parameters->putAll("name1", {"value1", "value2"});
                
                auto checklist = parameters->removeAll("name1");
                VERIFY_ARE_EQUAL(checklist.size(), 2);
                auto values = std::vector<std::string> { std::begin(checklist), std::end(checklist) };
                auto check = values[0];
                VERIFY_ARE_EQUAL(check, "value1");
                check = values[1];
                VERIFY_ARE_EQUAL(check, "value2");
                
                checklist = parameters->removeAll("name1");
                VERIFY_ARE_EQUAL(checklist.size(), 0);
                
                auto map = parameters->getMap();
                VERIFY_IS_TRUE(map.size() == 0);
            }
            
            TEST(first) {
                auto parameters = std::make_shared<VObjectParameters>();
                parameters->putAll("name", {"value1", "value2"});
                auto check = parameters->first("name");
                VERIFY_ARE_EQUAL(check, "value1");
                parameters->clear("name");
                check = parameters->first("name");
                VERIFY_ARE_EQUAL(check, "");
                check = parameters->first("name2");
                VERIFY_ARE_EQUAL(check, "");
            }
            
            TEST(copy) {
                auto orig = std::make_shared<VObjectParameters>();
                orig->put("name", "value");
                auto copy = std::make_shared<VObjectParameters>(orig);
                VERIFY_ARE_EQUAL(orig, copy);
                orig->put("name", "value2");
                
                auto values_list = copy->get("name");
                VERIFY_ARE_EQUAL(values_list.size(), 1);
                auto v1 = values_list[0];
                VERIFY_ARE_EQUAL(v1, "value");
            }
            
            TEST(isQuotedPrintable) {
                auto parameters = std::make_shared<VObjectParameters>();
                VERIFY_IS_FALSE(parameters->isQuotedPrintable());
                
                parameters->put("encoding", "foo");
                VERIFY_IS_FALSE(parameters->isQuotedPrintable());
                
                parameters->clear();
                parameters->put("", "QUOTED-PRINTABLE");
                VERIFY_IS_TRUE(parameters->isQuotedPrintable());
                
                parameters->clear();
                parameters->put("", "quoted-printable");
                VERIFY_IS_TRUE(parameters->isQuotedPrintable());
                
                parameters->clear();
                parameters->put("encoding", "quoted-printable");
                VERIFY_IS_TRUE(parameters->isQuotedPrintable());
                
                parameters->clear();
                parameters->put("encoding", "QUOTED-PRINTABLE");
                VERIFY_IS_TRUE(parameters->isQuotedPrintable());
                
                parameters->clear();
                parameters->putAll("", { "foo", "QUOTED-PRINTABLE" });
                VERIFY_IS_TRUE(parameters->isQuotedPrintable());
                
                parameters->clear();
                parameters->putAll("encoding", { "foo", "QUOTED-PRINTABLE" });
                VERIFY_IS_TRUE(parameters->isQuotedPrintable());
            }
            
            TEST(getCharset) {
                auto parameters = std::make_shared<VObjectParameters>();
                VERIFY_IS_NULL(parameters->getCharset());
                
                parameters->put("CHARSET", "unknown");
                VERIFY_THROWS_EQUAL(parameters->getCharset(), std::invalid_argument, "Unsupported Charset");
                
                parameters->clear();
                parameters->put("CHARSET", "illegal name");
                VERIFY_THROWS_EQUAL(parameters->getCharset(), std::invalid_argument, "Unsupported Charset");
                
                parameters->clear();
                parameters->put("CHARSET", "utf-8");
                VERIFY_ARE_EQUAL("UTF-8", parameters->getCharset()->name());
            }
            
            //            TEST(equals_and_hash) {
            //                auto one = std::make_shared<VObjectParameters>();
            //                assertEqualsMethodEssentials(one);
            //                
            //                one.put("name", "value");
            //                VObjectParameters two = new VObjectParameters();
            //                two.put("name", "value");
            //                assertEqualsAndHash(one, two);
            //            }
            
            
        }
    }
}
