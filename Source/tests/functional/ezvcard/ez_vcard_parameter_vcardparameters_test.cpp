//
//  ez_vcard_parameter_vcardparameters_test.cpp
//  OpenPGP
//
//  Created by Yanfeng Zhang on 1/13/17.
//  Copyright © 2017 Yanfeng Zhang. All rights reserved.
//


#include "utils_test.h"

#include <ezvcard/ezvcard.hpp>
#include <ezvcard/vcard.hpp>
#include <ezvcard/io/chain/chaining_text_string_parser.hpp>

#include "vcard_parameters.hpp"
#include "vcard_version.hpp"
#include "encoding.hpp"
#include "calscale.hpp"
#include "std_extension.hpp"

using namespace ezvcard;
namespace tests {
    namespace ez_vcard_tests {
        
        std::list<int> tolist(const std::list<ValidationWarning::Ptr> in) {
            std::list<int> out;
            for (auto it = in.begin(); it != in.end(); ++it) {
                ValidationWarning::Ptr obj = *it;
                out.push_back(obj->getCode());
            }
            return out;
        }
        
        SUITE(ez_vcard_parameter_vcardparameters_test)
        {
            
            TEST(copy) {
                auto parameters = std::make_shared<VCardParameters>();
                parameters->put("NAME", "value");
                auto copy = std::make_shared<VCardParameters>(parameters);
                VERIFY_ARE_EQUAL(copy, parameters);
            }
            
            TEST(validate_non_standard_values) { //TODO::need complete
                auto parameters = std::make_shared<VCardParameters>();
                parameters->setCalscale(Calscale::get("foo"));
                parameters->setEncoding(Encoding::get("foo"));
                //parameters->setValue(VCardDataType.get("foo"));
                
                //                assertValidate(parameters.validate(V2_1), 3, 6, 3, 3);
                //
                auto warnings = parameters->validate(VCardVersion::V2_1());
                VERIFY_IS_TRUE(warnings.size() > 0);
                auto e = std::list<int>{3, 6, 3, 3};
                auto a = tolist(warnings);
                //VERIFY_IS_TRUE((a == e));
                
                warnings = parameters->validate(VCardVersion::V3_0());
                VERIFY_IS_TRUE(warnings.size() > 0);
                a = tolist(warnings);
                e = std::list<int>{3, 3, 3, 6};
                //                assertValidate(parameters.validate(V3_0), 3, 3, 3, 6);
                //                assertValidate(parameters.validate(V4_0), 3, 3, 3);
                
                warnings = parameters->validate(VCardVersion::V4_0());
                VERIFY_IS_TRUE(warnings.size() > 0);
                a = tolist(warnings);
                e = std::list<int>{3, 3, 3};
            }
            
            TEST(validate_malformed_values) {
                auto parameters = std::make_shared<VCardParameters>();
                parameters->put(VCardParameters::GEO, "invalid");
                parameters->put(VCardParameters::INDEX, "invalid");
                parameters->put(VCardParameters::PREF, "invalid");
                parameters->put(VCardParameters::PID, "invalid");
                
                auto warnings = parameters->validate(VCardVersion::V2_1());
                VERIFY_IS_TRUE(warnings.size() > 0);
                auto e = std::list<int>{5, 5, 27, 5, 6, 6, 6};
                auto a = tolist(warnings);
                VERIFY_IS_TRUE((a == e));
                
                warnings = parameters->validate(VCardVersion::V3_0());
                VERIFY_IS_TRUE(warnings.size() > 0);
                e = std::list<int>{5, 5, 27, 5, 6, 6, 6};
                a = tolist(warnings);
                VERIFY_IS_TRUE((a == e));
                
                warnings = parameters->validate(VCardVersion::V4_0());
                VERIFY_IS_TRUE(warnings.size() > 0);
                e = std::list<int>{5, 5, 27, 5};
                a = tolist(warnings);
                VERIFY_IS_TRUE((a == e));
            }
            
            TEST(validate_pid) {
                auto parameters = std::make_shared<VCardParameters>();
                parameters->replace(VCardParameters::PID, "invalid"); //ASCII value is after "9"
                auto warnings = parameters->validate(VCardVersion::V2_1());
                auto a = tolist(warnings);
                auto e = std::list<int>{27, 6};
                VERIFY_IS_TRUE(a == e);
                warnings = parameters->validate(VCardVersion::V3_0());
                a = tolist(warnings);
                e = std::list<int>{27, 6};
                VERIFY_IS_TRUE(a == e);
                warnings = parameters->validate(VCardVersion::V4_0());
                a = tolist(warnings);
                e = std::list<int>{27};
                VERIFY_IS_TRUE(a == e);
                
                parameters->replace(VCardParameters::PID, "*");//ASCII value is before "0"
                warnings = parameters->validate(VCardVersion::V2_1());
                a = tolist(warnings);
                e = std::list<int>{27, 6};
                VERIFY_IS_TRUE(a == e);
                warnings = parameters->validate(VCardVersion::V3_0());
                a = tolist(warnings);
                e = std::list<int>{27, 6};
                VERIFY_IS_TRUE(a == e);
                warnings = parameters->validate(VCardVersion::V4_0());
                a = tolist(warnings);
                e = std::list<int>{27};
                VERIFY_IS_TRUE(a == e);
                
                parameters->replace(VCardParameters::PID, ".1");
                warnings = parameters->validate(VCardVersion::V2_1());
                a = tolist(warnings);
                e = std::list<int>{31, 27, 6};
                VERIFY_IS_TRUE(a == e);
                warnings = parameters->validate(VCardVersion::V3_0());
                a = tolist(warnings);
                e = std::list<int>{27, 6};
                VERIFY_IS_TRUE(a == e);
                warnings = parameters->validate(VCardVersion::V4_0());
                a = tolist(warnings);
                e = std::list<int>{27};
                VERIFY_IS_TRUE(a == e);
                
                parameters->replace(VCardParameters::PID, "1.");
                warnings = parameters->validate(VCardVersion::V2_1());
                a = tolist(warnings);
                e = std::list<int>{31, 27, 6};
                VERIFY_IS_TRUE(a == e);
                warnings = parameters->validate(VCardVersion::V3_0());
                a = tolist(warnings);
                e = std::list<int>{27, 6};
                VERIFY_IS_TRUE(a == e);
                warnings = parameters->validate(VCardVersion::V4_0());
                a = tolist(warnings);
                e = std::list<int>{27};
                VERIFY_IS_TRUE(a == e);
                
                parameters->replace(VCardParameters::PID, "1");
                warnings = parameters->validate(VCardVersion::V2_1());
                a = tolist(warnings);
                e = std::list<int>{6};
                VERIFY_IS_TRUE(a == e);
                warnings = parameters->validate(VCardVersion::V3_0());
                a = tolist(warnings);
                e = std::list<int>{6};
                VERIFY_IS_TRUE(a == e);
                warnings = parameters->validate(VCardVersion::V4_0());
                a = tolist(warnings);
                e = std::list<int>{};
                VERIFY_IS_TRUE(a == e);
                
                parameters->replace(VCardParameters::PID, "1.1");
                warnings = parameters->validate(VCardVersion::V2_1());
                a = tolist(warnings);
                e = std::list<int>{31, 6};
                VERIFY_IS_TRUE(a == e);
                warnings = parameters->validate(VCardVersion::V3_0());
                a = tolist(warnings);
                e = std::list<int>{6};
                VERIFY_IS_TRUE(a == e);
                warnings = parameters->validate(VCardVersion::V4_0());
                a = tolist(warnings);
                e = std::list<int>{};
                VERIFY_IS_TRUE(a == e);
                
                parameters->replace(VCardParameters::PID, "1.1.1");
                warnings = parameters->validate(VCardVersion::V2_1());
                a = tolist(warnings);
                e = std::list<int>{31, 27, 6};
                VERIFY_IS_TRUE(a == e);
                warnings = parameters->validate(VCardVersion::V3_0());
                a = tolist(warnings);
                e = std::list<int>{27, 6};
                VERIFY_IS_TRUE(a == e);
                warnings = parameters->validate(VCardVersion::V4_0());
                a = tolist(warnings);
                e = std::list<int>{27};
                VERIFY_IS_TRUE(a == e);
            }
            
            
            TEST(validate_index) {
                auto parameters = std::make_shared<VCardParameters>();
                parameters->setIndex(0);
                auto warnings = parameters->validate(VCardVersion::V2_1());
                auto a = tolist(warnings);
                auto e = std::list<int>{28, 6};
                VERIFY_IS_TRUE(a == e);
                warnings = parameters->validate(VCardVersion::V3_0());
                a = tolist(warnings);
                e = std::list<int>{28, 6};
                VERIFY_IS_TRUE(a == e);
                warnings = parameters->validate(VCardVersion::V4_0());
                a = tolist(warnings);
                e = std::list<int>{28};
                VERIFY_IS_TRUE(a == e);
                
                parameters->setIndex(1);
                warnings = parameters->validate(VCardVersion::V2_1());
                a = tolist(warnings);
                e = std::list<int>{6};
                VERIFY_IS_TRUE(a == e);
                warnings = parameters->validate(VCardVersion::V3_0());
                a = tolist(warnings);
                e = std::list<int>{6};
                VERIFY_IS_TRUE(a == e);
                warnings = parameters->validate(VCardVersion::V4_0());
                a = tolist(warnings);
                e = std::list<int>{};
                VERIFY_IS_TRUE(a == e);
            }
            
            TEST(validate_pref) {
                auto parameters = std::make_shared<VCardParameters>();
                parameters->setPref(0);
                auto warnings = parameters->validate(VCardVersion::V2_1());
                auto a = tolist(warnings);
                auto e = std::list<int>{29};
                VERIFY_IS_TRUE(a == e);
                warnings = parameters->validate(VCardVersion::V3_0());
                a = tolist(warnings);
                e = std::list<int>{29};
                VERIFY_IS_TRUE(a == e);
                warnings = parameters->validate(VCardVersion::V4_0());
                a = tolist(warnings);
                e = std::list<int>{29};
                VERIFY_IS_TRUE(a == e);
                
                parameters->setPref(101);
                warnings = parameters->validate(VCardVersion::V2_1());
                a = tolist(warnings);
                e = std::list<int>{29};
                VERIFY_IS_TRUE(a == e);
                warnings = parameters->validate(VCardVersion::V3_0());
                a = tolist(warnings);
                e = std::list<int>{29};
                VERIFY_IS_TRUE(a == e);
                warnings = parameters->validate(VCardVersion::V4_0());
                a = tolist(warnings);
                e = std::list<int>{29};
                VERIFY_IS_TRUE(a == e);
                
                parameters->setPref(50);
                warnings = parameters->validate(VCardVersion::V2_1());
                a = tolist(warnings);
                e = std::list<int>{};
                VERIFY_IS_TRUE(a == e);
                warnings = parameters->validate(VCardVersion::V3_0());
                a = tolist(warnings);
                e = std::list<int>{};
                VERIFY_IS_TRUE(a == e);
                warnings = parameters->validate(VCardVersion::V4_0());
                a = tolist(warnings);
                e = std::list<int>{};
                VERIFY_IS_TRUE(a == e);
            }
            
            //            TEST(validate_supported_versions) {
            //                auto parameters = std::make_shared<VCardParameters>();
            //                parameters.setAltId("value");
            //                parameters->setCalscale(Calscale.GREGORIAN);
            //                parameters.setCharset("UTF-8");
            //                parameters->setGeo(GeoUriBuilder(1.0, 1.0).build());
            //                parameters.setIndex(1);
            //                parameters.setLanguage("value");
            //                parameters.setLevel("value");
            //                parameters.setMediaType("value");
            //                parameters.setSortAs("value");
            //                parameters.setTimezone("value");
            //
            //                assertValidate(parameters.validate(V2_1), 31, 6, 6, 6, 6, 6, 6, 6, 6);
            //                assertValidate(parameters.validate(V3_0), 6, 6, 6, 6, 6, 6, 6, 6, 6);
            //                assertValidate(parameters.validate(V4_0), 6);
            //            }
            //
            //                        @Test
            //                        public void validate_value_supported_versions() {
            //                            parameters.setEncoding(Encoding._7BIT);
            //                            parameters.setValue(VCardDataType.CONTENT_ID);
            //                            assertValidate(parameters.validate(V2_1));
            //                            assertValidate(parameters.validate(V3_0), 4, 4);
            //                            assertValidate(parameters.validate(V4_0), 4, 4);
            //
            //                            parameters.setEncoding(Encoding.B);
            //                            parameters.setValue(VCardDataType.BINARY);
            //                            assertValidate(parameters.validate(V2_1), 4, 4);
            //                            assertValidate(parameters.validate(V3_0));
            //                            assertValidate(parameters.validate(V4_0), 4, 4);
            //
            //                            parameters.setEncoding(null);
            //                            parameters.setValue(VCardDataType.DATE_AND_OR_TIME);
            //                            assertValidate(parameters.validate(V2_1), 4);
            //                            assertValidate(parameters.validate(V3_0), 4);
            //                            assertValidate(parameters.validate(V4_0));
            //                        }
            //
            TEST(validate_charset) {
                auto parameters = std::make_shared<VCardParameters>();
                parameters->setCharset("invalid");
                
                auto warnings = parameters->validate(VCardVersion::V2_1());
                auto a = tolist(warnings);
                auto e = std::list<int>{22};
                VERIFY_ARE_EQUAL(a, e);
                
                warnings = parameters->validate(VCardVersion::V3_0());
                a = tolist(warnings);
                e = std::list<int>{6, 22};
                VERIFY_ARE_EQUAL(a, e);
                
                warnings = parameters->validate(VCardVersion::V4_0());
                a = tolist(warnings);
                e = std::list<int>{6, 22};
                VERIFY_ARE_EQUAL(a, e);
                
                parameters->setCharset("UTF-8");
                warnings = parameters->validate(VCardVersion::V2_1());
                a = tolist(warnings);
                e = std::list<int>{};
                VERIFY_ARE_EQUAL(a, e);
                warnings = parameters->validate(VCardVersion::V3_0());
                a = tolist(warnings);
                e = std::list<int>{6};
                VERIFY_ARE_EQUAL(a, e);
                warnings = parameters->validate(VCardVersion::V4_0());
                a = tolist(warnings);
                e = std::list<int>{6};
                VERIFY_ARE_EQUAL(a, e);
            }
            //
            //            @Test
            //            public void validate_parameter_name() {
            //                parameters.replace("YES/NO", "value");
            //                assertValidate(parameters.validate(V2_1));
            //                assertValidate(parameters.validate(V3_0), 26);
            //                assertValidate(parameters.validate(V4_0), 26);
            //
            //                parameters.clear();
            //                parameters.replace("NAME[]", "value");
            //                assertValidate(parameters.validate(V2_1), 30);
            //                assertValidate(parameters.validate(V3_0), 26);
            //                assertValidate(parameters.validate(V4_0), 26);
            //
            //                parameters.clear();
            //                parameters.replace("NAME", "value");
            //                assertValidate(parameters.validate(V2_1));
            //                assertValidate(parameters.validate(V3_0));
            //                assertValidate(parameters.validate(V4_0));
            //            }
            //            //
            //            //            @Test
            //            //            public void validate_parameter_value_characters() {
            //            //                for (char c : ",.:=[]".toCharArray()) {
            //            //                    parameters.replace("NAME", "value" + c);
            //            //                    assertValidate(parameters.validate(V2_1), 31);
            //            //                }
            //            //
            //            //                char c = (char) 7;
            //            //                parameters.replace("NAME", "value" + c);
            //            //                assertValidate(parameters.validate(V2_1), 31);
            //            //                assertValidate(parameters.validate(V3_0), 25);
            //            //                assertValidate(parameters.validate(V4_0), 25);
            //            //            }
            //            //
            //            //            /**
            //            //             * Checks that the LABEL parameter is *not* checked for correctness if the
            //            //             * vCard version is 2.1 or 3.0, because the writer converts the parameter to
            //            //             * a LABEL property for these versions.
            //            //             */
            //            //            @Test
            //            //            public void validate_label_parameter_value_characters() {
            //            //                parameters.replace(LABEL, "value.\"");
            //            //                assertValidate(parameters.validate(V2_1));
            //            //                assertValidate(parameters.validate(V3_0));
            //            //                assertValidate(parameters.validate(V4_0), 25);
            //            //
            //            //                char c = (char) 7;
            //            //                parameters.replace(LABEL, "value" + c);
            //            //                assertValidate(parameters.validate(V2_1));
            //            //                assertValidate(parameters.validate(V3_0));
            //            //                assertValidate(parameters.validate(V4_0), 25);
            //            //            }
            //            //
            //            //            /**
            //            //             * Newlines in LABEL parameter values are ignored for version 4.0.
            //            //             */
            //            //            @Test
            //            //            public void validate_label_parameter_newlines() {
            //            //                parameters.replace(LABEL, "value\n");
            //            //                assertValidate(parameters.validate(V2_1));
            //            //                assertValidate(parameters.validate(V3_0));
            //            //                assertValidate(parameters.validate(V4_0));
            //            //
            //            //                parameters.clear();
            //            //                parameters.replace("NAME", "value\n");
            //            //                assertValidate(parameters.validate(V2_1), 31);
            //            //                assertValidate(parameters.validate(V3_0), 25);
            //            //                assertValidate(parameters.validate(V4_0), 25);
            //            //            }
            //            //
            //                        /**
            //                         * Tests to make sure {@link VCardParameters#sanitizeKey(String)
            //                         * sanitizeKey()} is implemented correctly.
            //                         */
            //                        @Test
            //                        public void case_insensitive() {
            //                            parameters.put("NUMBERS", "1");
            //                            assertEquals(Arrays.asList("1"), parameters.get("numbers"));
            //                            parameters.put("numbers", "2");
            //                            assertEquals(Arrays.asList("1", "2"), parameters.get("NUMBERS"));
            //                            parameters.put(null, "3");
            //                            assertEquals(Arrays.asList("3"), parameters.get(null));
            //                        }
            //
            //            @Test
            //            public void encoding() {
            //                assertNull(parameters.getEncoding());
            //
            //                parameters.setEncoding(Encoding.QUOTED_PRINTABLE);
            //                assertEquals(Encoding.QUOTED_PRINTABLE.getValue(), parameters.first(ENCODING));
            //                assertEquals(Encoding.QUOTED_PRINTABLE, parameters.getEncoding());
            //
            //                parameters.setEncoding(null);
            //                assertNull(parameters.getEncoding());
            //            }
            //
            //            @Test
            //            public void value() {
            //                assertNull(parameters.getValue());
            //
            //                parameters.setValue(VCardDataType.TEXT);
            //                assertEquals(VCardDataType.TEXT.getName(), parameters.first(VALUE));
            //                assertEquals(VCardDataType.TEXT, parameters.getValue());
            //
            //                parameters.setValue(null);
            //                assertNull(parameters.getValue());
            //            }
            //
            //            @Test
            //            public void pref() {
            //                assertNull(parameters.getPref());
            //
            //                parameters.setPref(1);
            //                assertEquals("1", parameters.first(PREF));
            //                assertIntEquals(1, parameters.getPref());
            //
            //                parameters.setPref(null);
            //                assertNull(parameters.getPref());
            //            }
            //
            //            @Test(expected = IllegalStateException.class)
            //            public void pref_malformed() {
            //                parameters.put(PREF, "invalid");
            //                parameters.getPref();
            //            }
            //
            //            @Test
            //            public void geo() {
            //                assertNull(parameters.getGeo());
            //
            //                parameters.setGeo(new GeoUri.Builder(-10.98887888, 20.12344111).build());
            //                assertEquals("geo:-10.988879,20.123441", parameters.first(GEO)); //it rounds to 6 decimal places
            //                assertEquals(new GeoUri.Builder(-10.988879, 20.123441).build(), parameters.getGeo());
            //
            //                parameters.setGeo(null);
            //                assertNull(parameters.first(GEO));
            //            }
            //
            //            @Test(expected = IllegalStateException.class)
            //            public void geo_malformed() {
            //                parameters.put(GEO, "invalid");
            //                parameters.getGeo();
            //            }
            //
            //            @Test
            //            public void index() {
            //                assertNull(parameters.getIndex());
            //
            //                parameters.setIndex(1);
            //                assertEquals("1", parameters.first(INDEX));
            //                assertIntEquals(1, parameters.getIndex());
            //
            //                parameters.setIndex(null);
            //                assertNull(parameters.getIndex());
            //            }
            //
            //            @Test(expected = IllegalStateException.class)
            //            public void index_malformed() {
            //                parameters.put(INDEX, "invalid");
            //                parameters.getIndex();
            //            }
            //
            //            @Test
            //            public void calscale() {
            //                assertNull(parameters.getCalscale());
            //
            //                parameters.setCalscale(Calscale.GREGORIAN);
            //                assertEquals(Calscale.GREGORIAN.getValue(), parameters.first(CALSCALE));
            //                assertEquals(Calscale.GREGORIAN, parameters.getCalscale());
            //
            //                parameters.setCalscale(null);
            //                assertNull(parameters.getCalscale());
            //            }
            //
            //            @Test
            //            public void language() {
            //                assertNull(parameters.getLanguage());
            //
            //                parameters.setLanguage("en");
            //                assertEquals("en", parameters.first(LANGUAGE));
            //                assertEquals("en", parameters.getLanguage());
            //
            //                parameters.setLanguage(null);
            //                assertNull(parameters.getLanguage());
            //            }
            //
            //            @Test
            //            public void label() {
            //                assertNull(parameters.getLabel());
            //
            //                parameters.setLabel("value");
            //                assertEquals("value", parameters.first(LABEL));
            //                assertEquals("value", parameters.getLabel());
            //
            //                parameters.setLabel(null);
            //                assertNull(parameters.getLabel());
            //            }
            //
            //            @Test
            //            public void timezone() {
            //                assertNull(parameters.getTimezone());
            //
            //                parameters.setTimezone("value");
            //                assertEquals("value", parameters.first(TZ));
            //                assertEquals("value", parameters.getTimezone());
            //
            //                parameters.setTimezone(null);
            //                assertNull(parameters.getTimezone());
            //            }
            //
            //            @Test
            //            public void type() {
            //                assertNull(parameters.getType());
            //
            //                parameters.setType("value");
            //                assertEquals("value", parameters.first(TYPE));
            //                assertEquals("value", parameters.getType());
            //
            //                parameters.setType(null);
            //                assertNull(parameters.getType());
            //            }
            //
            //            @Test
            //            public void altId() {
            //                assertNull(parameters.getAltId());
            //
            //                parameters.setAltId("value");
            //                assertEquals("value", parameters.first(ALTID));
            //                assertEquals("value", parameters.getAltId());
            //
            //                parameters.setAltId(null);
            //                assertNull(parameters.getAltId());
            //            }
            //
            //            @Test
            //            public void mediaType() {
            //                assertNull(parameters.getMediaType());
            //
            //                parameters.setMediaType("value");
            //                assertEquals("value", parameters.first(MEDIATYPE));
            //                assertEquals("value", parameters.getMediaType());
            //
            //                parameters.setMediaType(null);
            //                assertNull(parameters.getMediaType());
            //            }
            //
            //            @Test
            //            public void level() {
            //                assertNull(parameters.getLevel());
            //
            //                parameters.setLevel("value");
            //                assertEquals("value", parameters.first(LEVEL));
            //                assertEquals("value", parameters.getLevel());
            //
            //                parameters.setLevel(null);
            //                assertNull(parameters.getLevel());
            //            }
            //
            //            @Test
            //            public void sortAs() {
            //                assertTrue(parameters.getSortAs().isEmpty());
            //
            //                parameters.setSortAs("one", "two");
            //                assertEquals(Arrays.asList("one", "two"), parameters.getSortAs());
            //                assertEquals(Arrays.asList("one", "two"), parameters.get(SORT_AS));
            //
            //                parameters.clear();
            //                parameters.put(SORT_AS, "one");
            //                parameters.put(SORT_AS, "two");
            //                assertEquals(Arrays.asList("one", "two"), parameters.getSortAs());
            //
            //                parameters.clear();
            //
            //                parameters.setSortAs("one", "three");
            //                assertEquals(Arrays.asList("one", "three"), parameters.getSortAs());
            //
            //                parameters.setSortAs();
            //                assertTrue(parameters.getSortAs().isEmpty());
            //            }
            //
            //            @Test
            //            public void equals_essentials() {
            //                VCardParameters one = new VCardParameters();
            //                one.put("foo", "bar");
            //                assertEqualsMethodEssentials(one);
            //            }
            //
            //            @Test
            //            public void equals_different_size() {
            //                VCardParameters one = new VCardParameters();
            //                one.put("foo", "one");
            //
            //                VCardParameters two = new VCardParameters();
            //                two.put("foo", "one");
            //                two.put("foo", "two");
            //
            //                assertNotEqualsBothWays(one, two);
            //            }
            //
            //            @Test
            //            public void equals_different_value_size() {
            //                VCardParameters one = new VCardParameters();
            //                one.put("foo", "one");
            //                one.put("bar", "three");
            //
            //                VCardParameters two = new VCardParameters();
            //                two.put("foo", "one");
            //                two.put("foo", "two");
            //
            //                assertNotEqualsBothWays(one, two);
            //            }
            //
            //            @Test
            //            public void equals_case_insensitive() {
            //                VCardParameters one = new VCardParameters();
            //                one.put("foo", "bar");
            //
            //                VCardParameters two = new VCardParameters();
            //                two.put("FOO", "BAR");
            //
            //                assertEqualsAndHash(one, two);
            //            }
            //
            //            @Test
            //            public void equals_order_does_not_matter() {
            //                VCardParameters one = new VCardParameters();
            //                one.put("foo", "one");
            //                one.put("foo", "two");
            //                one.put("foo", "three");
            //
            //                VCardParameters two = new VCardParameters();
            //                two.put("foo", "TWO");
            //                two.put("foo", "one");
            //                two.put("foo", "three");
            //
            //                assertEqualsAndHash(one, two);
            //            }
            //
            //            @Test
            //            public void equals_duplicate_values() {
            //                VCardParameters one = new VCardParameters();
            //                one.put("foo", "one");
            //                one.put("foo", "one");
            //                one.put("foo", "two");
            //
            //                VCardParameters two = new VCardParameters();
            //                two.put("foo", "one");
            //                two.put("foo", "one");
            //                two.put("foo", "two");
            //
            //                assertEqualsAndHash(one, two);
            //            }
            //
            //            @Test
            //            public void equals_different_duplicates_same_value_size() {
            //                VCardParameters one = new VCardParameters();
            //                one.put("foo", "one");
            //                one.put("foo", "one");
            //                one.put("foo", "two");
            //                
            //                VCardParameters two = new VCardParameters();
            //                two.put("foo", "one");
            //                two.put("foo", "two");
            //                two.put("foo", "two");
            //                
            //                assertNotEqualsBothWays(one, two);
            //            }
            //            
            //            @Test
            //            public void equals_multiple_keys() {
            //                VCardParameters one = new VCardParameters();
            //                one.put("foo", "BAR");
            //                one.put("super", "man");
            //                one.put("super", "bad");
            //                one.put("hello", "world");
            //                one.put(null, "null");
            //                
            //                VCardParameters two = new VCardParameters();
            //                two.put("hello", "world");
            //                two.put("super", "MAN");
            //                two.put("foo", "bar");
            //                two.put("super", "bad");
            //                two.put(null, "null");
            //                
            //                assertEqualsAndHash(one, two);
            //            }
            //            
        }
    }
}
