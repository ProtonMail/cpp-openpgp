//
//  ez_vcard_structured_name_scrfibe_test.cpp
//  OpenPGP
//
//  Created by Yanfeng Zhang on 5/30/17.
//  Copyright © 2017 Yanfeng Zhang. All rights reserved.
//

#include "utils_test.h"

#include <ezvcard/ezvcard.hpp>
#include <ezvcard/vcard.hpp>
#include <ezvcard/io/chain/chaining_text_string_parser.hpp>
#include "helper_property_sensei.hpp"
#include "structured_name.hpp"
#include "structured_name_scribe.hpp"
#include "helper_sensei.hpp"

using namespace ezvcard;

namespace tests {
    namespace ez_vcard_tests {
        SUITE(ez_vcard_structured_name_scribe_test)
        {
            class MyFixture
            {
            public:
                StructuredName::Ptr withAllValues = nullptr;
                StructuredName::Ptr withEmptyValues = nullptr;
                
                StructuredNameScribe::Ptr scribe = nullptr;
                Sensei<StructuredName>::Ptr sensei = nullptr;
                
                StructuredName::Ptr empty = nullptr;

            public:
                MyFixture() {
                    
                    withAllValues = std::make_shared<StructuredName>();
                    scribe = std::make_shared<StructuredNameScribe>();
                    sensei = std::make_shared<Sensei<StructuredName>>(scribe);
                    
                    /* setup goes here */
                    withAllValues->setGiven("Jonathan");
                    withAllValues->setFamily("Doe");
                    
                    withAllValues->addAdditionalName("Joh;nny,");
                    withAllValues->addAdditionalName("John");
                    withAllValues->addPrefix("Mr.");
                    withAllValues->addSuffix("III");
                    
                    withEmptyValues = std::make_shared<StructuredName>();
                    withEmptyValues->setGiven("Jonathan");
                    withEmptyValues->setFamily("");
                    withEmptyValues->addAdditionalName("Joh;nny,");
                    withEmptyValues->addAdditionalName("John");
                    
                    empty = std::make_shared<StructuredName>();
                }
                ~MyFixture() {
                    /* teardown goes here */
                
                }
            };

            TEST_FIXTURE(MyFixture, parseText) {
                auto withAllValuesV2_1 = std::make_shared<StructuredName>(withAllValues);
                withAllValuesV2_1->clearNames();
                withAllValuesV2_1->addAdditionalName("Joh;nny,,John");
                auto test = sensei->assertParseText("Doe;Jonathan;Joh\\;nny\\,,John;Mr.;III");
                test->versions({VCardVersion::V2_1()});
                test->ParseTest<StructuredName>::run(withAllValuesV2_1);
                
                test = sensei->assertParseText("Doe;Jonathan;Joh\\;nny\\,,John;Mr.;III");
                test->versions({VCardVersion::V3_0(), VCardVersion::V4_0()});
                test->ParseTest<StructuredName>::run(withAllValues);
                
                auto withEmptyValuesV2_1 = std::make_shared<StructuredName>(withEmptyValues);
                withEmptyValuesV2_1->clearNames();
                withEmptyValuesV2_1->addAdditionalName("Joh;nny,,John");
                
                test = sensei->assertParseText(";Jonathan;Joh\\;nny\\,,John;;");
                test->versions({VCardVersion::V2_1()});
                test->ParseTest<StructuredName>::run(withEmptyValuesV2_1);
                
                test = sensei->assertParseText(";Jonathan;Joh\\;nny\\,,John;;");
                test->versions({VCardVersion::V3_0(), VCardVersion::V4_0()});
                test->ParseTest<StructuredName>::run(withEmptyValues);
                
                test = sensei->assertParseText(";;;;");
                test->ParseTest<StructuredName>::run(empty);
                test = sensei->assertParseText("");
                test->ParseTest<StructuredName>::run(empty);
            }
            
            TEST_FIXTURE(MyFixture, writeText) {
                auto test = sensei->assertWriteText(withAllValues);
                test->versions({VCardVersion::V2_1()});
                test->WriteTextTest<StructuredName>::run("Doe;Jonathan;Joh\\;nny,,John;Mr.;III");
                
                test = sensei->assertWriteText(withAllValues);
                test->versions({VCardVersion::V3_0(), VCardVersion::V4_0()});
                test->run("Doe;Jonathan;Joh\\;nny\\,,John;Mr.;III");
                
                test = sensei->assertWriteText(withEmptyValues);
                test->versions({VCardVersion::V2_1()});
                test->run(";Jonathan;Joh\\;nny,,John");
                
                test = sensei->assertWriteText(withEmptyValues);
                test->versions({VCardVersion::V3_0(), VCardVersion::V4_0()});
                test->run(";Jonathan;Joh\\;nny\\,,John");
                
                test = sensei->assertWriteText(withEmptyValues);
                test->includeTrailingSemicolons(true);
                test->versions({VCardVersion::V3_0(), VCardVersion::V4_0()});
                test->run(";Jonathan;Joh\\;nny\\,,John;;");
                
                test = sensei->assertWriteText(empty);
                test->run("");
                
                test = sensei->assertWriteText(empty);
                test->includeTrailingSemicolons(true);
                test->run(";;;;");
            }
//
//                @Test
//                public void writeXml() {
//                    //@formatter:off
//                    sensei.assertWriteXml(withAllValues).run(
//                                                             "<surname>Doe</surname>" +
//                                                             "<given>Jonathan</given>" +
//                                                             "<additional>Joh;nny,</additional>" +
//                                                             "<additional>John</additional>" +
//                                                             "<prefix>Mr.</prefix>" +
//                                                             "<suffix>III</suffix>"
//                                                             );
//                    
//                    sensei.assertWriteXml(withEmptyValues).run(
//                                                               "<surname/>" +
//                                                               "<given>Jonathan</given>" +
//                                                               "<additional>Joh;nny,</additional>" +
//                                                               "<additional>John</additional>" +
//                                                               "<prefix/>" +
//                                                               "<suffix/>"
//                                                               );
//                    
//                    sensei.assertWriteXml(empty).run(
//                                                     "<surname/>" +
//                                                     "<given/>" +
//                                                     "<additional/>" +
//                                                     "<prefix/>" +
//                                                     "<suffix/>"
//                                                     );
//                    //@formatter:on
//                }
//                
//                @Test
//                public void writeJson() {
//                    sensei.assertWriteJson(withAllValues).run(JCardValue.structured("Doe", "Jonathan", Arrays.asList("Joh;nny,", "John"), "Mr.", "III"));
//                    sensei.assertWriteJson(withEmptyValues).run(JCardValue.structured("", "Jonathan", Arrays.asList("Joh;nny,", "John"), "", ""));
//                    sensei.assertWriteJson(empty).run(JCardValue.structured("", "", "", "", ""));
//                }

//                
//                @Test
//                public void parseXml() {
//                    //@formatter:off
//                    sensei.assertParseXml(
//                                          "<surname>Doe</surname>" +
//                                          "<given>Jonathan</given>" +
//                                          "<additional>Joh;nny,</additional>" +
//                                          "<additional>John</additional>" +
//                                          "<prefix>Mr.</prefix>" +
//                                          "<suffix>III</suffix>"
//                                          ).run(withAllValues);
//                    
//                    sensei.assertParseXml(
//                                          "<surname/>" +
//                                          "<given>Jonathan</given>" +
//                                          "<additional>Joh;nny,</additional>" +
//                                          "<additional>John</additional>" +
//                                          "<prefix/>" +
//                                          "<suffix/>"
//                                          ).run(withEmptyValues);
//                    
//                    sensei.assertParseXml(
//                                          "<surname/>" +
//                                          "<given/>" +
//                                          "<additional/>" +
//                                          "<prefix/>" +
//                                          "<suffix/>"
//                                          ).run(empty);
//                    //@formatter:on
//                }
//                
//                @Test
//                public void parseHtml() {
//                    //@formatter:off
//                    sensei.assertParseHtml(
//                                           "<div>" +
//                                           "<span class=\"family-name\">Doe</span>" +
//                                           "<span class=\"given-name\">Jonathan</span>" +
//                                           "<span class=\"additional-name\">Joh;nny,</span>" +
//                                           "<span class=\"additional-name\">John</span>" +
//                                           "<span class=\"honorific-prefix\">Mr.</span>" +
//                                           "<span class=\"honorific-suffix\">III</span>" +
//                                           "</div>"
//                                           ).run(withAllValues);
//                    
//                    sensei.assertParseHtml(
//                                           "<div>" +
//                                           "<span class=\"given-name\">Jonathan</span>" +
//                                           "<span class=\"additional-name\">Joh;nny,</span>" +
//                                           "<span class=\"additional-name\">John</span>" +
//                                           "</div>"
//                                           ).run(withEmptyValues);
//                    
//                    sensei.assertParseHtml(
//                                           "<div>" +
//                                           "<span class=\"given-name\"></span>" +
//                                           "</div>"
//                                           ).run(empty);
//                    //@formatter:on
//                }
//                
//                @Test
//                public void parseJson() {
//                    JCardValue value = JCardValue.structured("Doe", "Jonathan", Arrays.asList("Joh;nny,", "John"), "Mr.", "III");
//                    sensei.assertParseJson(value).run(withAllValues);
//                    
//                    value = JCardValue.structured(null, "Jonathan", Arrays.asList("Joh;nny,", "John"), "", null);
//                    sensei.assertParseJson(value).run(withEmptyValues);
//                    
//                    value = JCardValue.structured(null, "Jonathan", Arrays.asList("Joh;nny,", "John"));
//                    sensei.assertParseJson(value).run(withEmptyValues);
//                    
//                    value = JCardValue.structured(null, null, "", null, null);
//                    sensei.assertParseJson(value).run(empty);
//                    
//                    sensei.assertParseJson("").run(empty);
//                }
//            }
        }
    }
}



