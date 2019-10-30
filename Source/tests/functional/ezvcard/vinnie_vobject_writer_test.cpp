//
//  vinnie_vobject_writer_test.cpp
//  OpenPGP
//
//  Created by Yanfeng Zhang on 5/9/17.
//  Copyright © 2017 Yanfeng Zhang. All rights reserved.
//

#include "utils_test.h"

#include <codecvt>
#include <list>
#include <locale>
#include <string>
#include <stack>
#include <queue>
#include <sstream>

#include <ezvcard/io/vobject_data_listener.hpp>
#include "vobject_writer.hpp"
#include <ezvcard/vcard_version.hpp>
#include "string_util.hpp"
#include "charset.hpp"

#include "std_extension.hpp"

namespace tests {
    namespace ez_vcard_tests {
        
        using namespace vinnie;
        
        SUITE(vinnie_vobject_writer)
        {
            std::string testString(const std::string& exclude) {
                std::stringstream ss;
                for (int c = 0; c < 128; c++) {
                    bool contains = false;
                    for (int i = 0; i < exclude.length(); i++) {
                        if (c == exclude[i]) {
                            contains = true;
                            break;
                        }
                    }
                    if (!contains) {
                        ss << std::string(1, c);
                    }
                }
                return ss.str();
            }
            
            auto styles = std::list<SyntaxStyle> {NEW, OLD};
            auto booleans = std::list<bool> { false, true };
            
            TEST(writeBeginComponent) {
                for (SyntaxStyle style : styles) {
                    auto sw = std::make_shared<std::stringstream>("");
                    auto writer = std::make_shared<VObjectWriter>(sw, style);
                    
                    writer->writeBeginComponent("COMP");
                    writer->writeBeginComponent(" ");
                    
                    VERIFY_THROWS(writer->writeBeginComponent(""), std::invalid_argument);
                    
                    auto actual = sw->str();
                    std::string expected =
                    "BEGIN:COMP\r\n"
                    "BEGIN: \r\n";
                    
                    VERIFY_ARE_EQUAL(expected, actual);
                }
            }
            
            TEST(writeEndComponent) {
                for (SyntaxStyle style : styles) {
                    auto sw = std::make_shared<std::stringstream>("");
                    auto writer = std::make_shared<VObjectWriter>(sw, style);
                    
                    writer->writeEndComponent("COMP");
                    writer->writeEndComponent(" ");
                    
                    VERIFY_THROWS(writer->writeEndComponent(""), std::invalid_argument);
                    
                    auto actual = sw->str();
                    std::string expected =
                    "END:COMP\r\n"
                    "END: \r\n";
                    VERIFY_ARE_EQUAL(expected, actual);
                }
            }
            
            TEST(writeVersion) {
                for (SyntaxStyle style : styles) {
                   auto sw = std::make_shared<std::stringstream>("");
                    auto writer = std::make_shared<VObjectWriter>(sw, style);
                    
                    writer->writeVersion("1");
                    writer->writeVersion(" ");
                    
                    VERIFY_THROWS(writer->writeVersion(""), std::invalid_argument);
                    
                    auto actual = sw->str();
                    std::string expected =
                    "VERSION:1\r\n"
                    "VERSION: \r\n";
                    
                    VERIFY_ARE_EQUAL(expected, actual);
                }
            }
            
            TEST(write_VObjectProperty) {
                for (SyntaxStyle style : styles) {
                    auto sw = std::make_shared<std::stringstream>("");
                    auto writer = std::make_shared<VObjectWriter>(sw, style);
                    
                    auto property = std::make_shared<VObjectProperty>();
                    property->setGroup("group");
                    property->setName("PROP");
                    property->getParameters()->put("PARAM", "pvalue");
                    property->setValue("value");
                    
                    writer->writeProperty(property);
                    
                    auto actual = sw->str();
                    std::string expected =
                    "group.PROP;PARAM=pvalue:value\r\n";
                    
                    VERIFY_ARE_EQUAL(expected, actual);
                }
            }
            
            TEST(setCaretDecoding) {
                for (SyntaxStyle style : styles) {
                    auto sw = std::make_shared<std::stringstream>("");
                    auto writer = std::make_shared<VObjectWriter>(sw, style);
                    
                    VERIFY_IS_FALSE(writer->isCaretEncodingEnabled());
                    writer->setCaretEncodingEnabled(true);
                    VERIFY_IS_TRUE(writer->isCaretEncodingEnabled());
                }
            }
            
            TEST(setSyntaxStyle) {
                for (SyntaxStyle style : styles) {
                    auto sw = std::make_shared<std::stringstream>("");
                    auto writer = std::make_shared<VObjectWriter>(sw, style);
                    
                    VERIFY_ARE_EQUAL(style, writer->getSyntaxStyle());
                    for (SyntaxStyle style2 : styles) {
                        writer->setSyntaxStyle(style2);
                        VERIFY_ARE_EQUAL(style2, writer->getSyntaxStyle());
                    }
                }
            }
            
            TEST(group) {
                for (SyntaxStyle style : styles) {
                    auto sw = std::make_shared<std::stringstream>("");
                    auto writer = std::make_shared<VObjectWriter>(sw, style);
                    
                    writer->writeProperty("group", "PROP", std::make_shared<VObjectParameters>(), "value");
                    writer->writeProperty("", "PROP", std::make_shared<VObjectParameters>(), "value");
                    
                    auto actual = sw->str();
                    std::string expected =
                    "group.PROP:value\r\n"
                    "PROP:value\r\n";
                    
                    VERIFY_ARE_EQUAL(expected, actual);
                }
            }
            
            TEST(group_invalid_characters) {
                for (SyntaxStyle style : styles) {
                    auto sw = std::make_shared<std::stringstream>("");
                    auto writer = std::make_shared<VObjectWriter>(sw, style);
                    std::string testString = ".;:\n\r";
                    for (char c : testString) {
                        std::string in_c = std::string(1, c);
                        VERIFY_THROWS(writer->writeProperty(in_c, "PROP", std::make_shared<VObjectParameters>(), ""),
                                      std::invalid_argument);
                    }
                    
                    auto actual = sw->str();
                    std::string expected =
                    "";
                    
                    VERIFY_ARE_EQUAL(expected, actual);
                }
            }
            
            TEST(group_starts_with_whitespace) {
                for (SyntaxStyle style : styles) {
                    auto sw = std::make_shared<std::stringstream>("");
                    auto writer = std::make_shared<VObjectWriter>(sw, style);
                    std::string testString = " \t";
                    for (char c : testString) {
                        std::string in_c = std::string(1, c);
                        VERIFY_THROWS(writer->writeProperty(in_c, "PROP", std::make_shared<VObjectParameters>(), ""),
                                      std::invalid_argument);
                        
                        auto actual = sw->str();
                        std::string expected =
                        "";
                        
                        VERIFY_ARE_EQUAL(expected, actual);
                    }
                }
            }
            
            TEST(property_name) {
                for (SyntaxStyle style : styles) {
                    auto sw = std::make_shared<std::stringstream>("");
                    auto writer = std::make_shared<VObjectWriter>(sw, style);
                    
                    writer->writeProperty("", "PROP", std::make_shared<VObjectParameters>(), "");
                    
                    VERIFY_THROWS(writer->writeProperty("", "", std::make_shared<VObjectParameters>(), ""), std::invalid_argument);
                    
                    auto actual = sw->str();
                    std::string expected =
                    "PROP:\r\n";
                    
                    VERIFY_ARE_EQUAL(expected, actual);
                }
            }
            
            TEST(property_name_invalid_characters) {
                for (SyntaxStyle style : styles) {
                    auto sw = std::make_shared<std::stringstream>("");
                    auto writer = std::make_shared<VObjectWriter>(sw, style);
                    std::string testString = ".;:\n\r";
                    for (char c : testString) {
                        std::string in_c = std::string(1, c);
                        VERIFY_THROWS(writer->writeProperty("", in_c, std::make_shared<VObjectParameters>(), ""), std::invalid_argument);
                        
                        auto actual = sw->str();
                        std::string expected =
                        "";
                        
                        VERIFY_ARE_EQUAL(expected, actual);
                    }
                }
            }
            
            TEST(property_name_starts_with_whitespace) {
                for (SyntaxStyle style : styles) {
                    auto sw = std::make_shared<std::stringstream>("");
                    auto writer = std::make_shared<VObjectWriter>(sw, style);
                    std::string testString = " \t";
                    for (char c : testString) {
                        std::string in_c = std::string(1, c);
                        VERIFY_THROWS(writer->writeProperty("", in_c, std::make_shared<VObjectParameters>(), ""), std::invalid_argument);
                        writer->writeProperty("", "PROP" + in_c, std::make_shared<VObjectParameters>(), "");
                    }
                    
                    auto actual = sw->str();
                    std::string expected =
                    "PROP :\r\n"
                    "PROP	:\r\n";
                    
                    VERIFY_ARE_EQUAL(expected, actual);
                }
            }
            
            /**
             * When the parameters multimap has a key with an empty list, the parameter
             * should not be written. This should never happen if the user sticks to the
             * API of the VObjectParameters class and does not modify the backing map
             * manually.
             */
            TEST(parameters_multivalued_empty_values) {
                for (SyntaxStyle style : styles) {
                    for (auto caretEncoding : booleans ) {
                        auto sw = std::make_shared<std::stringstream>("");
                        auto writer = std::make_shared<VObjectWriter>(sw, style);
                        writer->setCaretEncodingEnabled(caretEncoding);
                        
                        auto parameters = std::make_shared<VObjectParameters>();
                        parameters->putAll("PARAM", {});
                        writer->writeProperty("", "PROP", parameters, "");
                       
                        auto actual = sw->str();
                        std::string expected =
                        "PROP:\r\n";
                        
                        VERIFY_ARE_EQUAL(expected, actual);
                    }
                }
            }
            
            TEST(parameters_multivalued) {
                auto list = std::list<VObjectParameters::Ptr>();
                auto parameters = std::make_shared<VObjectParameters>();
                parameters->put("SINGLE", "one");
                list.push_back(parameters);
                
                parameters = std::make_shared<VObjectParameters>();
                parameters->put("MULTIPLE", "one");
                parameters->put("MULTIPLE", "two");
                list.push_back(parameters);
                
                parameters = std::make_shared<VObjectParameters>();
                parameters->put("SINGLE", "one");
                parameters->put("MULTIPLE", "one");
                parameters->put("MULTIPLE", "two");
                list.push_back(parameters);
                
                SyntaxStyle style = OLD;
                {
                    for (auto caretEncoding : booleans) {
                        auto sw = std::make_shared<std::stringstream>("");
                        auto writer = std::make_shared<VObjectWriter>(sw, style);
                        writer->setCaretEncodingEnabled(caretEncoding);
                        for (auto p : list) {
                            writer->writeProperty("", "PROP", p, "");
                        }
                        
                        auto actual = sw->str();
                        std::string expected =
                        "PROP;SINGLE=one:\r\n"
                        "PROP;MULTIPLE=one;MULTIPLE=two:\r\n"
                        "PROP;SINGLE=one;MULTIPLE=one;MULTIPLE=two:\r\n";
                        
                        VERIFY_ARE_EQUAL(expected, actual);
                    }
                }
                
                style = NEW;
                {
                    for (auto caretEncoding : booleans) {
                        auto sw = std::make_shared<std::stringstream>("");
                        auto writer = std::make_shared<VObjectWriter>(sw, style);
                        writer->setCaretEncodingEnabled(caretEncoding);
                        for (auto p : list) {
                            writer->writeProperty("", "PROP", p, "");
                        }
                        auto actual = sw->str();
                        std::string expected =
                        "PROP;SINGLE=one:\r\n"
                        "PROP;MULTIPLE=one,two:\r\n"
                        "PROP;SINGLE=one;MULTIPLE=one,two:\r\n";
                        VERIFY_ARE_EQUAL(expected, actual);
                    }
                }
            }
            
            TEST(parameters_nameless) {
                auto list = std::list<VObjectParameters::Ptr>();
                auto parameters = std::make_shared<VObjectParameters>();
                parameters->put("", "one");
                list.push_back(parameters);
                
                parameters = std::make_shared<VObjectParameters>();
                parameters->put("", "one");
                parameters->put("", "two");
                list.push_back(parameters);
                
                SyntaxStyle style = OLD;
                {
                    for (auto caretEncoding : booleans) {
                        auto sw = std::make_shared<std::stringstream>("");
                        auto writer = std::make_shared<VObjectWriter>(sw, style);
                        writer->setCaretEncodingEnabled(caretEncoding);
                        for (auto p : list) {
                            writer->writeProperty("", "PROP", p, "");
                        }
                        
                        auto actual = sw->str();
                        std::string expected =
                        "PROP;one:\r\n"
                        "PROP;one;two:\r\n";
                        
                        VERIFY_ARE_EQUAL(expected, actual);
                    }
                }
                
                style = NEW;
                {
                    for (auto caretEncoding : booleans) {
                        auto sw = std::make_shared<std::stringstream>("");
                        auto writer = std::make_shared<VObjectWriter>(sw, style);
                        writer->setCaretEncodingEnabled(caretEncoding);
                        for (auto p : list) {
                            VERIFY_THROWS(writer->writeProperty("", "PROP", p, ""), std::invalid_argument);
                        }
                        auto actual = sw->str();
                        std::string expected =
                        "";
                        VERIFY_ARE_EQUAL(expected, actual);
                    }
                }
            }
            
            TEST(parameters_invalid_characters_in_name) {
                for (SyntaxStyle style : styles) {
                    for (auto caretEncoding : booleans) {
                        auto sw = std::make_shared<std::stringstream>("");
                        auto writer = std::make_shared<VObjectWriter>(sw, style);
                        writer->setCaretEncodingEnabled(caretEncoding);
                        std::string testString = ";:=\n\r";
                        for (char c : testString) {
                            auto c_in = std::string(1, c);
                            auto parameters = std::make_shared<VObjectParameters>();
                            parameters->put(c_in, "");
                            VERIFY_THROWS(writer->writeProperty("", "PROP", parameters, ""), std::invalid_argument);
                            auto actual = sw->str();
                            std::string expected =
                            "";
                            VERIFY_ARE_EQUAL(expected, actual);
                        }
                    }
                }
            }
            
            /**
             * When there are invalid characters in a parameter value.
             */
            TEST(parameters_invalid_characters_in_value) {
                SyntaxStyle style = OLD;
                {
                    for (auto caretEncoding : booleans) {
                        std::string testString = ":\n\r";
                        for (char c : testString) {
                            auto sw = std::make_shared<std::stringstream>("");
                            auto writer = std::make_shared<VObjectWriter>(sw, style);
                            writer->setCaretEncodingEnabled(caretEncoding);
                            
                            auto c_in = std::string(1, c);
                            auto parameters = std::make_shared<VObjectParameters>();
                            parameters->put("PARAM", c_in);
                            
                            VERIFY_THROWS(writer->writeProperty("", "PROP", parameters, ""), std::invalid_argument);
                            auto actual = sw->str();
                            std::string expected =
                            "";
                            VERIFY_ARE_EQUAL(expected, actual);
                        }
                    }
                }
                
                style = NEW;
                {
                    bool caretEncoding = false;
                    {
                        std::string testString = "\"\n\r";
                        for (char c : testString) {
                            auto sw = std::make_shared<std::stringstream>("");
                            auto writer = std::make_shared<VObjectWriter>(sw, style);
                            writer->setCaretEncodingEnabled(caretEncoding);
                            auto c_in = std::string(1, c);
                            auto parameters = std::make_shared<VObjectParameters>();
                            parameters->put("PARAM", c_in);
                            VERIFY_THROWS(writer->writeProperty("", "PROP", parameters, ""), std::invalid_argument);
                            auto actual = sw->str();
                            std::string expected =
                            "";
                            VERIFY_ARE_EQUAL(expected, actual);
                        }
                    }
                    
                    caretEncoding = true;
                    {
                        //no characters are disallowed
                    }
                }
            }
            
            /**
             * When escapable characters exist in a parameter value.
             */
            TEST(parameters_escape_special_characters_in_value) {
                //Old style:
                //Replaces \ with \\
                //Replaces ; with \;
                SyntaxStyle style = OLD;
                {
                    for (auto caretEncoding : booleans) {
                        auto sw = std::make_shared<std::stringstream>("");
                        auto writer = std::make_shared<VObjectWriter>(sw, style);
                        writer->getFoldedLineWriter()->disableLineLength();
                        writer->setCaretEncodingEnabled(caretEncoding);
                        
                        auto input = testString(":\r\n");
                        auto expectedOutput = input;
                        replaceAll(expectedOutput, "\\", "\\\\");
                        replaceAll(expectedOutput, ";", "\\;");
                        
                        auto parameters = std::make_shared<VObjectParameters>();
                        parameters->put("PARAM", input);
                        writer->writeProperty("", "PROP", parameters, "");
                        auto actual = sw->str();
                        std::string expected =
                        "PROP;PARAM=" + expectedOutput + ":\r\n";
                        VERIFY_ARE_EQUAL(expected, actual);
                    }
                }
                
                style = NEW;
                {
                    //New style without caret escaping
                    //surrounds in double quotes, since it contains , ; or :
                    auto caretEncoding = false;
                    {
                        auto sw = std::make_shared<std::stringstream>("");
                        auto writer = std::make_shared<VObjectWriter>(sw, style);
                        writer->getFoldedLineWriter()->disableLineLength();
                        writer->setCaretEncodingEnabled(caretEncoding);
                        
                        auto input = testString("\"\r\n");
                        auto expectedOutput = input;
                        
                        auto parameters = std::make_shared<VObjectParameters>();
                        parameters->put("PARAM", input);
                        writer->writeProperty("", "PROP", parameters, "");
                        auto actual = sw->str();
                        std::string expected =
                        "PROP;PARAM=\"" + expectedOutput + "\":\r\n";
                        VERIFY_ARE_EQUAL(expected, actual);
                    }
                    
                    //New style with caret escaping
                    //replaces ^ with ^^
                    //replaces newline with ^n
                    //replaces " with ^'
                    //surrounds in double quotes, since it contains , ; or :
                    caretEncoding = true;
                    {
                        auto sw = std::make_shared<std::stringstream>("");
                        auto writer = std::make_shared<VObjectWriter>(sw, style);
                        writer->getFoldedLineWriter()->disableLineLength();
                        writer->setCaretEncodingEnabled(caretEncoding);
                        
                        auto input = testString("\r\n") + "\r\n\n\r"; //make sure all three kinds of newline sequences are handled
                        auto expectedOutput = input;
                        replaceAll(expectedOutput, "^", "^^");
                        replaceAll(expectedOutput, "\"", "^'");
                        replaceAll(expectedOutput, "\r\n", "^n");
                        replaceAll(expectedOutput, "\r", "^n");
                        replaceAll(expectedOutput, "\n", "^n");
                        
                        auto parameters = std::make_shared<VObjectParameters>();
                        parameters->put("PARAM", input);
                        writer->writeProperty("", "PROP", parameters, "");
                        auto actual = sw->str();
                        std::string expected =
                        "PROP;PARAM=\"" + expectedOutput + "\":\r\n";
                        VERIFY_ARE_EQUAL(expected, actual);
                    }
                }
            }
            
            /**
             * When the property value is null, it should treat the value as an empty
             * string.
             */
            TEST(property_value_null) {
                for (SyntaxStyle style : styles) {
                    auto sw = std::make_shared<std::stringstream>("");
                    auto writer = std::make_shared<VObjectWriter>(sw, style);
                    writer->writeProperty("", "PROP", std::make_shared<VObjectParameters>(), "");
                    auto actual = sw->str();
                    auto expected =
                    "PROP:\r\n";
                    VERIFY_ARE_EQUAL(expected, actual);
                }
            }
            
            /**
             * When the property value contains newlines, it should encode in
             * quoted-printable in old style, and escape newlines in new style.
             */
            TEST(property_value_with_newlines) {
                SyntaxStyle style = OLD;
                {
                    auto sw = std::make_shared<std::stringstream>("");
                    auto writer = std::make_shared<VObjectWriter>(sw, style);
                    writer->getFoldedLineWriter()->disableLineLength();
                    
                    auto parameters = std::make_shared<VObjectParameters>();
                    auto expectedParams = std::make_shared<VObjectParameters>(parameters);
                    
                    writer->writeProperty("", "PROP", parameters, "one\r\ntwo");
                    VERIFY_IS_TRUE( parameters->equals(expectedParams));  //nothing should be added to the parameters object that was passed into the method
                    
                    parameters = std::make_shared<VObjectParameters>();
                    expectedParams = std::make_shared<VObjectParameters>(parameters);
                    writer->writeProperty("", "PROP", parameters, "one\rtwo");
                    VERIFY_IS_TRUE( parameters->equals(expectedParams));
                    
                    parameters = std::make_shared<VObjectParameters>();
                    expectedParams = std::make_shared<VObjectParameters>(parameters);
                    writer->writeProperty("", "PROP", parameters, "one\ntwo");
                    VERIFY_IS_TRUE( parameters->equals(expectedParams));
                    
                    parameters = std::make_shared<VObjectParameters>();
                    parameters->put("", "QUOTED-PRINTABLE");
                    expectedParams = std::make_shared<VObjectParameters>(parameters);
                    writer->writeProperty("", "PROP", parameters, "one\r\ntwo");
                    VERIFY_IS_TRUE( parameters->equals(expectedParams));
                    
                    parameters = std::make_shared<VObjectParameters>();
                    parameters->put("ENCODING", "QUOTED-PRINTABLE");
                    expectedParams = std::make_shared<VObjectParameters>(parameters);
                    writer->writeProperty("", "PROP", parameters, "one\r\ntwo");
                    VERIFY_IS_TRUE( parameters == expectedParams);
                    
                    parameters = std::make_shared<VObjectParameters>();
                    parameters->put("CHARSET", "UTF-16");
                    expectedParams = std::make_shared<VObjectParameters>(parameters);
                    writer->writeProperty("", "PROP", parameters, "one\r\ntwo");
                    VERIFY_IS_TRUE( parameters->equals(expectedParams));
                    
                    auto actual = sw->str();
                    auto expected =
                    "PROP;ENCODING=QUOTED-PRINTABLE;CHARSET=UTF-8:one=0D=0Atwo\r\n"
                    "PROP;ENCODING=QUOTED-PRINTABLE;CHARSET=UTF-8:one=0Dtwo\r\n"
                    "PROP;ENCODING=QUOTED-PRINTABLE;CHARSET=UTF-8:one=0Atwo\r\n"
                    "PROP;QUOTED-PRINTABLE;CHARSET=UTF-8:one=0D=0Atwo\r\n"
                    "PROP;ENCODING=QUOTED-PRINTABLE;CHARSET=UTF-8:one=0D=0Atwo\r\n"
                    "PROP;CHARSET=UTF-16;ENCODING=QUOTED-PRINTABLE:=FE=FF=00o=00n=00e=00=0D=00=0A=00t=00w=00o\r\n";
                    VERIFY_ARE_EQUAL(expected, actual);
                }
                
                style = NEW;
                {
                    auto sw = std::make_shared<std::stringstream>("");
                    auto writer = std::make_shared<VObjectWriter>(sw, style);
                    writer->writeProperty("", "PROP", std::make_shared<VObjectParameters>(), "one\r\ntwo");
                    writer->writeProperty("", "PROP", std::make_shared<VObjectParameters>(), "one\rtwo");
                    writer->writeProperty("", "PROP", std::make_shared<VObjectParameters>(), "one\ntwo");
                    
                    auto actual = sw->str();
                    auto expected =
                    "PROP:one\\ntwo\r\n"
                    "PROP:one\\ntwo\r\n"
                    "PROP:one\\ntwo\r\n";
                    
                    VERIFY_ARE_EQUAL(expected, actual);
                }
            }
            
            /**
             * When a QUOTED-PRINTABLE parameter value is present, the writer should
             * encode the value in quoted-printable.
             */
            TEST(property_value_quoted_printable) {
                std::wstring propValue = L"value \u00e4\u00f6\u00fc\u00df";
                
                using convert_type = std::codecvt_utf8<wchar_t>;
                std::wstring_convert<convert_type, wchar_t> converter;
                auto input = converter.to_bytes( propValue );
                
                 for (SyntaxStyle style : styles) {
                     auto sw = std::make_shared<std::stringstream>("");
                     auto writer = std::make_shared<VObjectWriter>(sw, style);
                     writer->getFoldedLineWriter()->disableLineLength();
                    
                    //no parameters
                    auto parameters = std::make_shared<VObjectParameters>();
                    writer->writeProperty("", "PROP", parameters, input);
                    
                    //no charset
                    parameters = std::make_shared<VObjectParameters>();
                    parameters->put("ENCODING", "QUOTED-PRINTABLE");
                    writer->writeProperty("", "PROP", parameters, input);
                    
                    //UTF-8
                    parameters = std::make_shared<VObjectParameters>();
                    parameters->put("ENCODING", "QUOTED-PRINTABLE");
                    parameters->put("CHARSET", "UTF-8");
                    writer->writeProperty("", "PROP", parameters, input);
                    
                    //UTF-16
                    parameters = std::make_shared<VObjectParameters>();
                    parameters->put("ENCODING", "QUOTED-PRINTABLE");
                    parameters->put("CHARSET", "UTF-16");
                    writer->writeProperty("", "PROP", parameters, input);
                    
                    //invalid
                    parameters = std::make_shared<VObjectParameters>();
                    parameters->put("ENCODING", "QUOTED-PRINTABLE");
                    parameters->put("CHARSET", "invalid");
                    writer->writeProperty("", "PROP", parameters, input);
                    
                    std::string actual = sw->str();
                    std::string expected =
                    "PROP:" + input + "\r\n"
                    "PROP;ENCODING=QUOTED-PRINTABLE;CHARSET=UTF-8:value =C3=A4=C3=B6=C3=BC=C3=9F\r\n"
                    "PROP;ENCODING=QUOTED-PRINTABLE;CHARSET=UTF-8:value =C3=A4=C3=B6=C3=BC=C3=9F\r\n"
                    "PROP;ENCODING=QUOTED-PRINTABLE;CHARSET=UTF-16:=FE=FF=00v=00a=00l=00u=00e=00 =00=E4=00=F6=00=FC=00=DF\r\n"
                    "PROP;ENCODING=QUOTED-PRINTABLE;CHARSET=UTF-8:value =C3=A4=C3=B6=C3=BC=C3=9F\r\n";
                    
                    VERIFY_ARE_EQUAL(expected, actual);
                }
            }
        }
    }
}
