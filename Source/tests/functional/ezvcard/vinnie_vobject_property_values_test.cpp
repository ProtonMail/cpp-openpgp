//
//  vinnie_vobject_property_values_test.cpp
//  OpenPGP
//
//  Created by Yanfeng Zhang on 1/12/17.
//  Copyright © 2017 Yanfeng Zhang. All rights reserved.
//

#include "utils_test.h"


#include <ezvcard/util/string_util.hpp>
#include <ezvcard/parameter/vobject_parameters.hpp>
#include "vobject_property_values.hpp"
#include <list>
#include <string>
#include <vector>

namespace tests {
    namespace ez_vcard_tests {
        const std::string NEWLINE = "\r\n";
        SUITE(vinnie_vobject_property_values)
        {
            TEST(unescape) {
                auto actual = VObjectPropertyValues::unescape("\\\\ \\, \\; \\n\\N \\\\\\,");
                auto expected = "\\ , ; " + NEWLINE + NEWLINE + " \\,";
                VERIFY_ARE_EQUAL(expected, actual);
                auto input = "no special characters";
                actual = VObjectPropertyValues::unescape(input);
                VERIFY_ARE_EQUAL(input, actual);
            }
            
            TEST(escape) {
                auto actual = VObjectPropertyValues::escape("One; Two, Three\\ Four\n Five\r\n Six\r");
                auto expected = "One\\; Two\\, Three\\\\ Four\n Five\r\n Six\r";
                VERIFY_ARE_EQUAL(expected, actual);
                
                auto input = "no special characters";
                actual = VObjectPropertyValues::escape(input);
                VERIFY_ARE_EQUAL(input, actual);
            }
            
            TEST(parseList) {
                auto actual = VObjectPropertyValues::parseList("one,,two\\,three;four");
                auto expected = std::vector<std::string> {"one", "", "two,three;four"};
                VERIFY_ARE_EQUAL(actual, expected);
                
                
                actual = VObjectPropertyValues::parseList("one");
                expected = std::vector<std::string> {"one" };
                VERIFY_ARE_EQUAL(expected, actual);
                
                actual = VObjectPropertyValues::parseList("");
                expected = std::vector<std::string> {};
                VERIFY_ARE_EQUAL(expected, actual);
            }

            TEST(writeList) {
                auto actual = VObjectPropertyValues::writeList({"one", "null", "", "2", "three,four;five"});
                auto expected = "one,null,,2,three\\,four\\;five";
                VERIFY_ARE_EQUAL(expected, actual);
                
                actual = VObjectPropertyValues::writeList({});
                expected = "";
                VERIFY_ARE_EQUAL(expected, actual);
            }
            
            TEST(parseSemiStructured) {
                auto actual = VObjectPropertyValues::parseSemiStructured("one;;two\\;three,four");
                auto expected = std::vector<std::string> {"one", "", "two;three,four" };
                VERIFY_ARE_EQUAL(expected, actual);
                
                actual = VObjectPropertyValues::parseSemiStructured("one;two;three", 2);
                expected = std::vector<std::string> {"one", "two;three"};
                VERIFY_ARE_EQUAL(expected, actual);
                
                actual = VObjectPropertyValues::parseSemiStructured("");
                expected = std::vector<std::string>{};
                VERIFY_ARE_EQUAL(expected, actual);
            }
            
            TEST(writeSemiStructured) {
                std::string actual, expected;
                
                for (bool includeTrailingSemicolons : { false, true }) {
                    actual = VObjectPropertyValues::writeSemiStructured({ "one", "null", "", "2", "three;four,five"}, false, includeTrailingSemicolons);
                    expected = "one;null;;2;three\\;four,five";
                    VERIFY_ARE_EQUAL(expected, actual);
                    
                    actual = VObjectPropertyValues::writeSemiStructured({"one", "null", "", "2", "three;four,five"}, true, includeTrailingSemicolons);
                    expected = "one;null;;2;three\\;four\\,five";
                    VERIFY_ARE_EQUAL(expected, actual);
                    
                    for (bool escapeCommas : { false, true }) {
                        actual = VObjectPropertyValues::writeSemiStructured({}, escapeCommas, includeTrailingSemicolons);
                        expected = "";
                        VERIFY_ARE_EQUAL(expected, actual);
                    }
                }
                
                {
                    auto input = std::vector<std::string>{"one", "", "two", "", ""};
                    
                    actual = VObjectPropertyValues::writeSemiStructured(input, false, false);
                    expected = "one;;two";
                    VERIFY_ARE_EQUAL(expected, actual);
                    
                    actual = VObjectPropertyValues::writeSemiStructured(input, false, true);
                    expected = "one;;two;;";
                    VERIFY_ARE_EQUAL(expected, actual);
                }
            }
            
            TEST(parseStructured) {
                auto actual = VObjectPropertyValues::parseStructured("one;two,,three;;four\\,five\\;six");
                
                auto expected = std::vector<std::vector<std::string>> {
                    {"one"},
                    {"two", "", "three"},
                    {},
                    {"four,five;six"}
                };
                VERIFY_ARE_EQUAL(expected, actual);
                
                actual = VObjectPropertyValues::parseStructured("");
                expected = {};
                VERIFY_ARE_EQUAL(expected, actual);
            }
            
            TEST(writeStructured) {
                std::string actual, expected;
                
                for (bool includeTrailingSemicolons : { false, true }) {
                    actual = VObjectPropertyValues::writeStructured({
                        {"one"},
                        {"two", "", "3", "null"},
                        {},
                        {"four,five;six"}}, includeTrailingSemicolons);
                    expected = "one;two,,3,null;;four\\,five\\;six";
                    VERIFY_ARE_EQUAL(expected, actual);
                    
                    actual = VObjectPropertyValues::writeStructured({{}}, includeTrailingSemicolons);
                    expected = "";
                    VERIFY_ARE_EQUAL(expected, actual);
                }
                
                {
                    //@formatter:off
                    auto input = std::vector<std::vector<std::string>>{
                        {"one"},
                        {},
                        {"two"},
                        {},
                        {}
                    };

                    
                    actual = VObjectPropertyValues::writeStructured(input, false);
                    expected = "one;;two";
                    VERIFY_ARE_EQUAL(expected, actual);
                    
                    actual = VObjectPropertyValues::writeStructured(input, true);
                    expected = "one;;two;;";
                    VERIFY_ARE_EQUAL(expected, actual);
                }
            }
            
//            TEST(parseMultimap) {
//                Map<String, List<String>> actual = VObjectPropertyValues.parseMultimap("one=two;;ONE=two;THREE;FOUR=five,six\\,seven\\;eight;NINE=;TEN=eleven=twelve");
//                Map<String, List<String>> expected = new HashMap<String, List<String>>();
//                expected.put("ONE", Arrays.asList("two", "two"));
//                expected.put("THREE", Arrays.asList(""));
//                expected.put("FOUR", Arrays.asList("five", "six,seven;eight"));
//                expected.put("NINE", Arrays.asList(""));
//                expected.put("TEN", Arrays.asList("eleven=twelve"));
//                assertEquals(expected, actual);
//                
//                actual = VObjectPropertyValues.parseMultimap("");
//                assertTrue(actual.isEmpty());
//            }
//            
//            TEST(writeMultimap) {
//                Map<String, List<String>> input = new LinkedHashMap<String, List<String>>();
//                input.put("A", asList("one"));
//                input.put("B", asList("two", "three,four;five", null));
//                input.put("C", asList(""));
//                input.put("d", asList("six=seven"));
//                input.put("E", Arrays.<String> asList());
//                
//                String expected = "A=one;B=two,three\\,four\\;five,null;C=;D=six=seven;E";
//                String actual = VObjectPropertyValues.writeMultimap(input);
//                assertEquals(expected, actual);
//            }
            
            TEST(SemiStructuredValueIterator) {
                {
                    SemiStructuredValueIterator it ("one;;two");
                    
                    VERIFY_IS_TRUE(it.hasNext());
                    VERIFY_ARE_EQUAL("one", it.next());
                    
                    VERIFY_IS_TRUE(it.hasNext());
                    VERIFY_ARE_EQUAL(it.next(), "");
                    
                    VERIFY_IS_TRUE(it.hasNext());
                    VERIFY_ARE_EQUAL("two", it.next());
                    
                    VERIFY_IS_FALSE(it.hasNext());
                    VERIFY_ARE_EQUAL(it.next(), "");
                }
                {
                    SemiStructuredValueIterator it ("one;two;three", 2);
                    
                    VERIFY_IS_TRUE(it.hasNext());
                    VERIFY_ARE_EQUAL("one", it.next());
                    
                    VERIFY_IS_TRUE(it.hasNext());
                    VERIFY_ARE_EQUAL("two;three", it.next());
                    
                    VERIFY_IS_FALSE(it.hasNext());
                    VERIFY_ARE_EQUAL(it.next(), "");
                }
            }
            
//            TEST(SemiStructuredValueBuilder) {
//                SemiStructuredValueBuilder builder = new SemiStructuredValueBuilder();
//                builder.append("one,two");
//                builder.append(null);
//                assertEquals("one,two", builder.build(false, false));
//                
//                builder = new SemiStructuredValueBuilder();
//                builder.append("one,two");
//                builder.append(null);
//                assertEquals("one\\,two;", builder.build(true, true));
//            }
            
            TEST(StructuredValueIterator) {
                StructuredValueIterator it("one;two;;;three,four");
                
                VERIFY_IS_TRUE(it.hasNext());
                VERIFY_ARE_EQUAL("one", it.nextValue());
                
                VERIFY_IS_TRUE(it.hasNext());
                VERIFY_ARE_EQUAL(std::vector<std::string>{"two"}, it.nextComponent());
                
                VERIFY_IS_TRUE(it.hasNext());
                VERIFY_ARE_EQUAL(it.nextValue(), "");
                
                VERIFY_IS_TRUE(it.hasNext());
                VERIFY_ARE_EQUAL(std::vector<std::string>{}, it.nextComponent());
                
                VERIFY_IS_TRUE(it.hasNext());
                auto actual = std::vector<std::string>{"three", "four"};
                VERIFY_ARE_EQUAL(actual, it.nextComponent());
                
                VERIFY_IS_FALSE(it.hasNext());
                VERIFY_ARE_EQUAL(it.nextValue(), "");
                VERIFY_ARE_EQUAL(std::vector<std::string>{}, it.nextComponent());
            }
//
//            TEST(StructuredValueBuilder) {
//                StructuredValueBuilder builder = new StructuredValueBuilder();
//                builder.append("one");
//                builder.append(asList("two", "three"));
//                builder.append((Object) null);
//                assertEquals("one;two,three;", builder.build());
//                
//                builder = new StructuredValueBuilder();
//                builder.append("one");
//                builder.append(asList("two", "three"));
//                builder.append((Object) null);
//                assertEquals("one;two,three", builder.build(false));
//                
//                builder = new StructuredValueBuilder();
//                builder.append("one");
//                builder.append(asList("two", "three"));
//                builder.append((Object) null);
//                assertEquals("one;two,three;", builder.build(true));
//            }
        }
    }
}
