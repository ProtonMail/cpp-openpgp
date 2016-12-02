//
//  vinnie_vobject_reader_test.cpp
//  OpenPGP
//
//  Created by Yanfeng Zhang on 12/7/16.
//  Copyright © 2016 Yanfeng Zhang. All rights reserved.
//
#include "utils_test.h"

#include <list>
#include <string>
#include <stack>
#include <queue>

//#include <ezvcard/io/buffer.hpp>
#include <ezvcard/io/vobject_data_listener.hpp>
#include <ezvcard/io/vobject_reader.hpp>
#include <ezvcard/vcard_version.hpp>

#include "utility.h"


namespace tests {
    namespace ez_vcard_tests {
        
        using namespace vinnie;
        
        class VObjectDataListenerMock : public VObjectDataListener {
        private:
            Context::Ptr copy(Context::Ptr orig) {
                auto p = std::make_shared<std::list<std::string>>(*orig->_parentComponents);
                auto copy = std::make_shared<Context>(p);
                copy->unfoldedLine->append(orig->getUnfoldedLine());
                copy->_lineNumber = orig->_lineNumber;
                return copy;
            }
        public:
            typedef std::shared_ptr<VObjectDataListenerMock> Ptr;
            
            std::vector<Context::Ptr> contexts = std::vector<Context::Ptr>();
            std::queue<VObjectProperty::Ptr> properties;
            std::queue<std::string> calls;
            std::queue<std::string> names;
            std::queue<std::string> warnings;
            void onComponentBegin(const std::string& name, const Context::Ptr & context) {
                calls.push("onComponentBegin");
                names.push(name);
                contexts.push_back(copy(context));
            }
            
            void onComponentEnd(const std::string& name, const Context::Ptr &context) {
                calls.push("onComponentEnd");
                names.push(name);
                contexts.push_back(copy(context));
            }
            
            void onProperty(const VObjectProperty::Ptr& property, const Context::Ptr &context) {
                calls.push("onProperty");
                properties.push(property);
                contexts.push_back(copy(context));
            }
            
            void onVersion(const std::string& value, const Context::Ptr &context) {
                calls.push("onVersion");
                contexts.push_back(copy(context));
            }
            
            void onWarning(Warning::TYPE warning, const VObjectProperty::Ptr& property, std::exception* ex, const Context::Ptr &context) {
                calls.push("onWarning");
                //properties.push(property);
                contexts.push_back(copy(context));
                if (ex != nullptr) {
                    warnings.push(ex->what());
                }
            }
        };
        
        
        auto styles = std::list<SyntaxStyle> {NEW, OLD};
        
        //TODO:: add QUOTED-PRINTABLE tests
        SUITE(vinnie_vobject_reader)
        {
            TEST(structure) {
                std::string string =
                "PROP1:value1\r\n"
                "BEGIN:COMP1\r\n"
                "PROP2:value2\r\n"
                "BEGIN:COMP2\r\n"
                "PROP3:value3\r\n"
                "END:COMP2\r\n"
                "PROP4:value4\r\n"
                "END:COMP1";
                for (SyntaxStyle style : styles) {
                    auto reader = new VObjectReader(string, style);
                    VObjectDataListenerMock::Ptr listener = std::make_shared<VObjectDataListenerMock>();
                    reader->parse(listener);
                    
                    //inorder.verify(listener).onProperty(eq(property().name("PROP1").value("value1").build()), any(Context.class));
                    auto callName = listener->calls.front();
                    listener->calls.pop();
                    VERIFY_ARE_EQUAL(callName, "onProperty");
                    auto property = listener->properties.front();
                    listener->properties.pop();
                    VERIFY_ARE_EQUAL("PROP1" ,property->getName());
                    VERIFY_ARE_EQUAL("value1" ,property->getValue());
                    
                    //inorder.verify(listener).onComponentBegin(eq("COMP1"), any(Context.class));
                    callName = listener->calls.front();
                    listener->calls.pop();
                    VERIFY_ARE_EQUAL(callName, "onComponentBegin");
                    auto name = listener->names.front();
                    listener->names.pop();
                    VERIFY_ARE_EQUAL("COMP1", name);
                    
                    //inorder.verify(listener).onProperty(eq(property().name("PROP2").value("value2").build()), any(Context.class));
                    callName = listener->calls.front();
                    listener->calls.pop();
                    VERIFY_ARE_EQUAL(callName, "onProperty");
                    property = listener->properties.front();
                    listener->properties.pop();
                    VERIFY_ARE_EQUAL("PROP2" ,property->getName());
                    VERIFY_ARE_EQUAL("value2" ,property->getValue());
                    
                    //inorder.verify(listener).onComponentBegin(eq("COMP2"), any(Context.class));
                    callName = listener->calls.front();
                    listener->calls.pop();
                    VERIFY_ARE_EQUAL(callName, "onComponentBegin");
                    name = listener->names.front();
                    listener->names.pop();
                    VERIFY_ARE_EQUAL("COMP2", name);
                    
                    //inorder.verify(listener).onProperty(eq(property().name("PROP3").value("value3").build()), any(Context.class));
                    callName = listener->calls.front();
                    listener->calls.pop();
                    VERIFY_ARE_EQUAL(callName, "onProperty");
                    property = listener->properties.front();
                    listener->properties.pop();
                    VERIFY_ARE_EQUAL("PROP3" ,property->getName());
                    VERIFY_ARE_EQUAL("value3" ,property->getValue());
                    
                    //inorder.verify(listener).onComponentEnd(eq("COMP2"), any(Context.class));
                    callName = listener->calls.front();
                    listener->calls.pop();
                    VERIFY_ARE_EQUAL(callName, "onComponentEnd");
                    name = listener->names.front();
                    listener->names.pop();
                    VERIFY_ARE_EQUAL("COMP2", name);
                    
                    //inorder.verify(listener).onProperty(eq(property().name("PROP4").value("value4").build()), any(Context.class));
                    callName = listener->calls.front();
                    listener->calls.pop();
                    VERIFY_ARE_EQUAL(callName, "onProperty");
                    property = listener->properties.front();
                    listener->properties.pop();
                    VERIFY_ARE_EQUAL("PROP4" ,property->getName());
                    VERIFY_ARE_EQUAL("value4" ,property->getValue());
                    
                    //inorder.verify(listener).onComponentEnd(eq("COMP1"), any(Context.class));
                    callName = listener->calls.front();
                    listener->calls.pop();
                    VERIFY_ARE_EQUAL(callName, "onComponentEnd");
                    name = listener->names.front();
                    listener->names.pop();
                    VERIFY_ARE_EQUAL("COMP1", name);
                    
                    //                    //@formatter:off
                    //                    String lines[] = string.split("\r\n");
                    //                    int line = 0;
                    //                    assertContexts(listener,
                    //                                   context(lines[line], ++line),
                    //                                   context(lines[line], ++line),
                    //                                   context(asList("COMP1"), lines[line], ++line),
                    //                                   context(asList("COMP1"), lines[line], ++line),
                    //                                   context(asList("COMP1", "COMP2"), lines[line], ++line),
                    //                                   context(asList("COMP1"), lines[line], ++line),
                    //                                   context(asList("COMP1"), lines[line], ++line),
                    //                                   context(lines[line], ++line)
                    //                                   );
                    //                    //@formatter:on
                }
            }
            
            /**
             * Asserts that a warning should be thrown when an unmatched END property is
             * found.
             */
            TEST(structured_extra_end) {
                //@formatter:off
                std::string string =
                "BEGIN:COMP1\r\n"
                "PROP:value\r\n"
                "END:COMP2\r\n"
                "END:COMP1\r\n";
                //@formatter:on
                
                for (SyntaxStyle style : styles) {
                    auto reader = new VObjectReader(string, style);
                    VObjectDataListenerMock::Ptr listener = std::make_shared<VObjectDataListenerMock>();
                    reader->parse(listener);
                    
                    //inorder.verify(listener).onComponentBegin(eq("COMP1"), any(Context.class));
                    auto callName = listener->calls.front();
                    listener->calls.pop();
                    VERIFY_ARE_EQUAL(callName, "onComponentBegin");
                    auto name = listener->names.front();
                    listener->names.pop();
                    VERIFY_ARE_EQUAL("COMP1", name);
                    
                    //inorder.verify(listener).onProperty(eq(property().name("PROP").value("value").build()), any(Context.class));
                    callName = listener->calls.front();
                    listener->calls.pop();
                    VERIFY_ARE_EQUAL(callName, "onProperty");
                    auto property = listener->properties.front();
                    listener->properties.pop();
                    VERIFY_ARE_EQUAL("PROP" ,property->getName());
                    VERIFY_ARE_EQUAL("value" ,property->getValue());
                    
                    //inorder.verify(listener).onWarning(eq(Warning.UNMATCHED_END), isNull(VObjectProperty.class), isNull(Exception.class), any(Context.class));
                    callName = listener->calls.front();
                    listener->calls.pop();
                    VERIFY_ARE_EQUAL(callName, "onWarning"); //TODO::finish this
                    //                    property = listener->properties.front();
                    //                    listener->properties.pop();
                    //                    VERIFY_ARE_EQUAL("PROP1" ,property->getName());
                    //                    VERIFY_ARE_EQUAL("value1" ,property->getValue());
                    
                    //inorder.verify(listener).onComponentEnd(eq("COMP1"), any(Context.class));
                    callName = listener->calls.front();
                    listener->calls.pop();
                    VERIFY_ARE_EQUAL(callName, "onComponentEnd");
                    name = listener->names.front();
                    listener->names.pop();
                    VERIFY_ARE_EQUAL("COMP1", name);
                    
                    //                    //@formatter:off
                    //                    String lines[] = string.split("\r\n");
                    //                    int line = 0;
                    //                    assertContexts(listener,
                    //                                   context(lines[line], ++line),
                    //                                   context(asList("COMP1"), lines[line], ++line),
                    //                                   context(asList("COMP1"), lines[line], ++line),
                    //                                   context(lines[line], ++line)
                    //                                   );
                    //                    //@formatter:on
                }
            }
            
            /**
             * Asserts what happens when BEGIN/END components are not nested correctly.
             */
            TEST(structure_components_out_of_order) {
                //@formatter:off
                std::string string =
                "BEGIN:COMP1\r\n"
                "PROP1:value1\r\n"
                "BEGIN:COMP2\r\n"
                "PROP2:value2\r\n"
                "END:COMP1\r\n" //this also ends COMP2
                "PROP3:value3\r\n"
                "END:COMP2\r\n";
                //@formatter:on
                
                for (SyntaxStyle style : styles) {
                    auto reader = new VObjectReader(string, style);
                    VObjectDataListenerMock::Ptr listener = std::make_shared<VObjectDataListenerMock>();
                    reader->parse(listener);
                    
                    //inorder.verify(listener).onComponentBegin(eq("COMP1"), any(Context.class));
                    auto callName = listener->calls.front();
                    listener->calls.pop();
                    VERIFY_ARE_EQUAL(callName, "onComponentBegin");
                    auto name = listener->names.front();
                    listener->names.pop();
                    VERIFY_ARE_EQUAL("COMP1", name);
                    
                    //inorder.verify(listener).onProperty(eq(property().name("PROP1").value("value1").build()), any(Context.class));
                    callName = listener->calls.front();
                    listener->calls.pop();
                    VERIFY_ARE_EQUAL(callName, "onProperty");
                    auto property = listener->properties.front();
                    listener->properties.pop();
                    VERIFY_ARE_EQUAL("PROP1" ,property->getName());
                    VERIFY_ARE_EQUAL("value1" ,property->getValue());
                    
                    //inorder.verify(listener).onComponentBegin(eq("COMP2"), any(Context.class));
                    callName = listener->calls.front();
                    listener->calls.pop();
                    VERIFY_ARE_EQUAL(callName, "onComponentBegin");
                    name = listener->names.front();
                    listener->names.pop();
                    VERIFY_ARE_EQUAL("COMP2", name);
                    
                    //inorder.verify(listener).onProperty(eq(property().name("PROP2").value("value2").build()), any(Context.class));
                    callName = listener->calls.front();
                    listener->calls.pop();
                    VERIFY_ARE_EQUAL(callName, "onProperty");
                    property = listener->properties.front();
                    listener->properties.pop();
                    VERIFY_ARE_EQUAL("PROP2" ,property->getName());
                    VERIFY_ARE_EQUAL("value2" ,property->getValue());
                    
                    /*
                     * COMP2 is ended even though its END property wasn't reached
                     * because COMP1 ended and COMP2 is nested inside of COMP1.
                     */
                    //inorder.verify(listener).onComponentEnd(eq("COMP2"), any(Context.class));
                    callName = listener->calls.front();
                    listener->calls.pop();
                    VERIFY_ARE_EQUAL(callName, "onComponentEnd");
                    name = listener->names.front();
                    listener->names.pop();
                    VERIFY_ARE_EQUAL("COMP2", name);
                    
                    //inorder.verify(listener).onComponentEnd(eq("COMP1"), any(Context.class));
                    callName = listener->calls.front();
                    listener->calls.pop();
                    VERIFY_ARE_EQUAL(callName, "onComponentEnd");
                    name = listener->names.front();
                    listener->names.pop();
                    VERIFY_ARE_EQUAL("COMP1", name);
                    
                    //inorder.verify(listener).onProperty(eq(property().name("PROP3").value("value3").build()), any(Context.class));
                    callName = listener->calls.front();
                    listener->calls.pop();
                    VERIFY_ARE_EQUAL(callName, "onProperty");
                    property = listener->properties.front();
                    listener->properties.pop();
                    VERIFY_ARE_EQUAL("PROP3" ,property->getName());
                    VERIFY_ARE_EQUAL("value3" ,property->getValue());
                    
                    //inorder.verify(listener).onWarning(eq(Warning.UNMATCHED_END), isNull(VObjectProperty.class), isNull(Exception.class), any(Context.class));
                    callName = listener->calls.front();
                    listener->calls.pop();
                    VERIFY_ARE_EQUAL(callName, "onWarning");
                    
                    
                    //                    //@formatter:off
                    //                    String lines[] = string.split("\r\n");
                    //                    int line = 0;
                    //                    assertContexts(listener,
                    //                                   context(lines[line], ++line),
                    //                                   context(asList("COMP1"), lines[line], ++line),
                    //                                   context(asList("COMP1"), lines[line], ++line),
                    //                                   context(asList("COMP1", "COMP2"), lines[line], ++line),
                    //                                   context(asList("COMP1"), lines[line], line+1),
                    //                                   context(lines[line], ++line),
                    //                                   context(lines[line], ++line),
                    //                                   context(lines[line], ++line)
                    //                                   );
                    //                    //@formatter:on
                }
            }
            
            /**
             * When the stream ends, but the components haven't ended.
             */
            TEST(structure_missing_end) {
                //@formatter:off
                std::string string =
                "BEGIN:COMP1\r\n"
                "PROP1:value1\r\n"
                "BEGIN:COMP2\r\n"
                "PROP2:value2\r\n";
                //@formatter:on
                
                for (SyntaxStyle style : styles) {
                    auto reader = new VObjectReader(string, style);
                    VObjectDataListenerMock::Ptr listener = std::make_shared<VObjectDataListenerMock>();
                    reader->parse(listener);
                    
                    //inorder.verify(listener).onComponentBegin(eq("COMP1"), any(Context.class));
                    auto callName = listener->calls.front();
                    listener->calls.pop();
                    VERIFY_ARE_EQUAL(callName, "onComponentBegin");
                    auto name = listener->names.front();
                    listener->names.pop();
                    VERIFY_ARE_EQUAL("COMP1", name);
                    
                    //inorder.verify(listener).onProperty(eq(property().name("PROP1").value("value1").build()), any(Context.class));
                    callName = listener->calls.front();
                    listener->calls.pop();
                    VERIFY_ARE_EQUAL(callName, "onProperty");
                    auto property = listener->properties.front();
                    listener->properties.pop();
                    VERIFY_ARE_EQUAL("PROP1" ,property->getName());
                    VERIFY_ARE_EQUAL("value1" ,property->getValue());
                    
                    //inorder.verify(listener).onComponentBegin(eq("COMP2"), any(Context.class));
                    callName = listener->calls.front();
                    listener->calls.pop();
                    VERIFY_ARE_EQUAL(callName, "onComponentBegin");
                    name = listener->names.front();
                    listener->names.pop();
                    VERIFY_ARE_EQUAL("COMP2", name);
                    
                    //inorder.verify(listener).onProperty(eq(property().name("PROP2").value("value2").build()), any(Context.class));
                    callName = listener->calls.front();
                    listener->calls.pop();
                    VERIFY_ARE_EQUAL(callName, "onProperty");
                    property = listener->properties.front();
                    listener->properties.pop();
                    VERIFY_ARE_EQUAL("PROP2" ,property->getName());
                    VERIFY_ARE_EQUAL("value2" ,property->getValue());
                    
                    //                    //@formatter:off
                    //                    String lines[] = string.split("\r\n");
                    //                    int line = 0;
                    //                    assertContexts(listener,
                    //                                   context(lines[line], ++line),
                    //                                   context(asList("COMP1"), lines[line], ++line),
                    //                                   context(asList("COMP1"), lines[line], ++line),
                    //                                   context(asList("COMP1", "COMP2"), lines[line], ++line)
                    //                                   );
                    //                    //@formatter:on
                }
            }
            
            /**
             * When a BEGIN or END property value is empty.
             */
            TEST(structure_no_component_name) {
                //@formatter:off
                std::string string =
                "BEGIN:\r\n"
                "BEGIN: \r\n"
                "PROP:value\r\n"
                "END:\r\n"
                "END: \r\n";
                //@formatter:on
                
                for (SyntaxStyle style : styles) {
                    auto reader = new VObjectReader(string, style);
                    VObjectDataListenerMock::Ptr listener = std::make_shared<VObjectDataListenerMock>();
                    reader->parse(listener);
                    
                    //inorder.verify(listener, times(2)).onWarning(eq(Warning.EMPTY_BEGIN), isNull(VObjectProperty.class), isNull(Exception.class), any(Context.class));
                    auto callName = listener->calls.front();
                    listener->calls.pop();
                    VERIFY_ARE_EQUAL(callName, "onWarning");
                    
                    callName = listener->calls.front();
                    listener->calls.pop();
                    VERIFY_ARE_EQUAL(callName, "onWarning");
                    
                    //inorder.verify(listener).onProperty(eq(property().name("PROP").value("value").build()), any(Context.class));
                    callName = listener->calls.front();
                    listener->calls.pop();
                    VERIFY_ARE_EQUAL(callName, "onProperty");
                    auto property = listener->properties.front();
                    listener->properties.pop();
                    VERIFY_ARE_EQUAL("PROP" ,property->getName());
                    VERIFY_ARE_EQUAL("value" ,property->getValue());
                    
                    
                    //inorder.verify(listener, times(2)).onWarning(eq(Warning.EMPTY_END), isNull(VObjectProperty.class), isNull(Exception.class), any(Context.class));
                    callName = listener->calls.front();
                    listener->calls.pop();
                    VERIFY_ARE_EQUAL(callName, "onWarning");
                    
                    callName = listener->calls.front();
                    listener->calls.pop();
                    VERIFY_ARE_EQUAL(callName, "onWarning");
                    
                    //                    //@formatter:off
                    //                    String lines[] = string.split("\r\n");
                    //                    int line = 0;
                    //                    assertContexts(listener,
                    //                                   context(lines[line], ++line),
                    //                                   context(lines[line], ++line),
                    //                                   context(lines[line], ++line),
                    //                                   context(lines[line], ++line),
                    //                                   context(lines[line], ++line)
                    //                                   );
                    //                    //@formatter:on
                }
            }
            
            /**
             * Asserts the case-sensitivity of the parts of a vobject.
             */
            TEST(case_insensitivity) {
                //@formatter:off
                std::string string =
                "BEGIN:COMP1\r\n"
                "group.prop;param=param_value:prop_value\r\n"
                "end:comp1\r\n"
                "BEGIN:comp2\r\n"
                "end:COMP2";
                //@formatter:on
                
                for (SyntaxStyle style : styles) {
                    auto reader = new VObjectReader(string, style);
                    VObjectDataListenerMock::Ptr listener = std::make_shared<VObjectDataListenerMock>();
                    reader->parse(listener);
                    
                    //inorder.verify(listener).onComponentBegin(eq("COMP1"), any(Context.class));
                    auto callName = listener->calls.front();
                    listener->calls.pop();
                    VERIFY_ARE_EQUAL(callName, "onComponentBegin");
                    auto name = listener->names.front();
                    listener->names.pop();
                    VERIFY_ARE_EQUAL("COMP1", name);
                    
                    //inorder.verify(listener).onProperty(eq(property().group("group").name("prop").param("PARAM", "param_value").value("prop_value").build())
                    callName = listener->calls.front();
                    listener->calls.pop();
                    VERIFY_ARE_EQUAL(callName, "onProperty");
                    auto property = listener->properties.front();
                    listener->properties.pop();
                    VERIFY_ARE_EQUAL("group" ,property->getGroup());
                    VERIFY_ARE_EQUAL("prop" ,property->getName());
                    auto params = property->getParameters();
                    VERIFY_ARE_EQUAL("prop_value" ,property->getValue());
                    //params->print();
                    
                    //inorder.verify(listener).onComponentEnd(eq("COMP1"), any(Context.class));
                    callName = listener->calls.front();
                    listener->calls.pop();
                    VERIFY_ARE_EQUAL(callName, "onComponentEnd");
                    name = listener->names.front();
                    listener->names.pop();
                    VERIFY_ARE_EQUAL("COMP1", name);
                    
                    //inorder.verify(listener).onComponentBegin(eq("COMP2"), any(Context.class));
                    callName = listener->calls.front();
                    listener->calls.pop();
                    VERIFY_ARE_EQUAL(callName, "onComponentBegin");
                    name = listener->names.front();
                    listener->names.pop();
                    VERIFY_ARE_EQUAL("COMP2", name);
                    
                    //inorder.verify(listener).onComponentEnd(eq("COMP2"), any(Context.class));
                    callName = listener->calls.front();
                    listener->calls.pop();
                    VERIFY_ARE_EQUAL(callName, "onComponentEnd");
                    name = listener->names.front();
                    listener->names.pop();
                    VERIFY_ARE_EQUAL("COMP2", name);
                }
            }
            
            /**
             * When checking for BEGIN and END properties, the property name and value
             * should be trimmed so that any whitespace around the colon ignored.
             * Whitespace around the colon is allowed by old style syntax, though it
             * never happens in practice.
             */
            TEST(whitespace_around_component_names) {
                //@formatter:off
                std::string string =
                "BEGIN:COMP1\r\n"
                "BEGIN:COMP2\r\n"
                "END : COMP2 \r\n"
                "END\t:\tCOMP1\t";
                //@formatter:on
                
                for (SyntaxStyle style : styles) {
                    auto reader = new VObjectReader(string, style);
                    VObjectDataListenerMock::Ptr listener = std::make_shared<VObjectDataListenerMock>();
                    reader->parse(listener);
                    
                    //inorder.verify(listener).onComponentBegin(eq("COMP1"), any(Context.class));
                    auto callName = listener->calls.front();
                    listener->calls.pop();
                    VERIFY_ARE_EQUAL(callName, "onComponentBegin");
                    auto name = listener->names.front();
                    listener->names.pop();
                    VERIFY_ARE_EQUAL("COMP1", name);
                    
                    //inorder.verify(listener).onComponentBegin(eq("COMP2"), any(Context.class));
                    callName = listener->calls.front();
                    listener->calls.pop();
                    VERIFY_ARE_EQUAL(callName, "onComponentBegin");
                    name = listener->names.front();
                    listener->names.pop();
                    VERIFY_ARE_EQUAL("COMP2", name);
                    
                    //inorder.verify(listener).onComponentEnd(eq("COMP2"), any(Context.class));
                    callName = listener->calls.front();
                    listener->calls.pop();
                    VERIFY_ARE_EQUAL(callName, "onComponentEnd");
                    name = listener->names.front();
                    listener->names.pop();
                    VERIFY_ARE_EQUAL("COMP2", name);
                    
                    //inorder.verify(listener).onComponentEnd(eq("COMP1"), any(Context.class));
                    callName = listener->calls.front();
                    listener->calls.pop();
                    VERIFY_ARE_EQUAL(callName, "onComponentEnd");
                    name = listener->names.front();
                    listener->names.pop();
                    VERIFY_ARE_EQUAL("COMP1", name);
                }
            }
            
            /**
             * Incorrect newline sequences should be accepted.
             */
            TEST(wrong_newlines) {
                //@formatter:off
                std::string string =
                "PROP1:value1\r"
                "PROP2:value2\n"
                "PROP3:value3";
                //@formatter:on
                
                for (SyntaxStyle style : styles) {
                    auto reader = new VObjectReader(string, style);
                    VObjectDataListenerMock::Ptr listener = std::make_shared<VObjectDataListenerMock>();
                    reader->parse(listener);
                    
                    //inorder.verify(listener).onProperty(eq(property().name("PROP1").value("value1").build()), any(Context.class));
                    auto callName = listener->calls.front();
                    listener->calls.pop();
                    VERIFY_ARE_EQUAL(callName, "onProperty");
                    auto property = listener->properties.front();
                    listener->properties.pop();
                    VERIFY_ARE_EQUAL("PROP1" ,property->getName());
                    VERIFY_ARE_EQUAL("value1" ,property->getValue());
                    
                    //inorder.verify(listener).onProperty(eq(property().name("PROP2").value("value2").build()), any(Context.class));
                    callName = listener->calls.front();
                    listener->calls.pop();
                    VERIFY_ARE_EQUAL(callName, "onProperty");
                    property = listener->properties.front();
                    listener->properties.pop();
                    VERIFY_ARE_EQUAL("PROP2" ,property->getName());
                    VERIFY_ARE_EQUAL("value2" ,property->getValue());
                    
                    //inorder.verify(listener).onProperty(eq(property().name("PROP3").value("value3").build()), any(Context.class));
                    callName = listener->calls.front();
                    listener->calls.pop();
                    VERIFY_ARE_EQUAL(callName, "onProperty");
                    property = listener->properties.front();
                    listener->properties.pop();
                    VERIFY_ARE_EQUAL("PROP3" ,property->getName());
                    VERIFY_ARE_EQUAL("value3" ,property->getValue());
                    
                    //                    //@formatter:off
                    //                    int line = 0;
                    //                    assertContexts(listener,
                    //                                   context("PROP1:value1", ++line),
                    //                                   context("PROP2:value2", ++line),
                    //                                   context("PROP3:value3", ++line)
                    //                                   );
                    //                    //@formatter:on
                }
            }
            
            /**
             * Empty lines should be ignored.
             */
            TEST(empty_lines) {
                std::string string =
                "PROP1:value1\r\n"
                "\r\n"
                "PROP2:value2\r\n"
                "\r\n"
                "\n"
                "\r"
                "PROP3:value3";
                
                for (SyntaxStyle style : styles) {
                    auto reader = new VObjectReader(string, style);
                    VObjectDataListenerMock::Ptr listener = std::make_shared<VObjectDataListenerMock>();
                    reader->parse(listener);
                    
                    //inorder.verify(listener).onProperty(eq(property().name("PROP1").value("value1").build()), any(Context.class));
                    auto callName = listener->calls.front();
                    listener->calls.pop();
                    VERIFY_ARE_EQUAL(callName, "onProperty");
                    auto property = listener->properties.front();
                    listener->properties.pop();
                    VERIFY_ARE_EQUAL("PROP1" ,property->getName());
                    VERIFY_ARE_EQUAL("value1" ,property->getValue());
                    
                    //inorder.verify(listener).onProperty(eq(property().name("PROP2").value("value2").build()), any(Context.class));
                    callName = listener->calls.front();
                    listener->calls.pop();
                    VERIFY_ARE_EQUAL(callName, "onProperty");
                    property = listener->properties.front();
                    listener->properties.pop();
                    VERIFY_ARE_EQUAL("PROP2" ,property->getName());
                    VERIFY_ARE_EQUAL("value2" ,property->getValue());
                    
                    //inorder.verify(listener).onProperty(eq(property().name("PROP3").value("value3").build()), any(Context.class));
                    callName = listener->calls.front();
                    listener->calls.pop();
                    VERIFY_ARE_EQUAL(callName, "onProperty");
                    property = listener->properties.front();
                    listener->properties.pop();
                    VERIFY_ARE_EQUAL("PROP3" ,property->getName());
                    VERIFY_ARE_EQUAL("value3" ,property->getValue());
                }
            }
            
            /**
             * Tests what happens when the producer did not add whitespace to the
             * beginning of a folded line.
             */
            TEST(badly_folded_line) {
                std::string string =
                "PROP;PARAM=one;PARA\r\n"
                "M=two:value";
                
                for (SyntaxStyle style : styles) {
                    auto reader = new VObjectReader(string, style);
                    VObjectDataListenerMock::Ptr listener = std::make_shared<VObjectDataListenerMock>();
                    reader->parse(listener);
                    
                    //inorder.verify(listener).onWarning(eq(Warning.MALFORMED_LINE), ));
                    auto callName = listener->calls.front();
                    listener->calls.pop();
                    VERIFY_ARE_EQUAL(callName, "onWarning");
                    
                    //inorder.verify(listener).onProperty(eq(property().name("M=two").value("value").build()), any(Context.class));
                    callName = listener->calls.front();
                    listener->calls.pop();
                    VERIFY_ARE_EQUAL(callName, "onProperty");
                    auto property = listener->properties.front();
                    listener->properties.pop();
                    VERIFY_ARE_EQUAL("M=two" ,property->getName());
                    VERIFY_ARE_EQUAL("value" ,property->getValue());
                }
            }
            
            /**
             * When the input stream ends before the property value is reached.
             */
            TEST(property_cut_off) {
                std::string string =
                "PROP;PARAM=one;PARA";
                for (SyntaxStyle style : styles) {
                    auto reader = new VObjectReader(string, style);
                    VObjectDataListenerMock::Ptr listener = std::make_shared<VObjectDataListenerMock>();
                    reader->parse(listener);
                    
                    //inorder.verify(listener).onWarning(eq(Warning.MALFORMED_LINE));
                    auto callName = listener->calls.front();
                    listener->calls.pop();
                    VERIFY_ARE_EQUAL(callName, "onWarning");
                }
            }
            
            /**
             * When the group and/or property names are empty.
             */
            TEST(empty_group_and_property_names) {
                std::string string =
                ":value\r\n"
                ".:value\r\n"
                "group.:value\r\n"
                ".PROP:value";
                
                for (SyntaxStyle style : styles) {
                    auto reader = new VObjectReader(string, style);
                    VObjectDataListenerMock::Ptr listener = std::make_shared<VObjectDataListenerMock>();
                    reader->parse(listener);
                    
                    //inorder.verify(listener).onProperty(eq(property().name("").value("value").build())
                    auto callName = listener->calls.front();
                    listener->calls.pop();
                    VERIFY_ARE_EQUAL(callName, "onProperty");
                    auto property = listener->properties.front();
                    listener->properties.pop();
                    VERIFY_ARE_EQUAL("" ,property->getName());
                    VERIFY_ARE_EQUAL("value" ,property->getValue());
                    
                    //inorder.verify(listener).onProperty(eq(property().group("").name("").value("value").build())
                    callName = listener->calls.front();
                    listener->calls.pop();
                    VERIFY_ARE_EQUAL(callName, "onProperty");
                    property = listener->properties.front();
                    listener->properties.pop();
                    VERIFY_ARE_EQUAL("" ,property->getGroup());
                    VERIFY_ARE_EQUAL("" ,property->getName());
                    VERIFY_ARE_EQUAL("value" ,property->getValue());
                    
                    //inorder.verify(listener).onProperty(eq(property().group("group").name("").value("value").build())
                    callName = listener->calls.front();
                    listener->calls.pop();
                    VERIFY_ARE_EQUAL(callName, "onProperty");
                    property = listener->properties.front();
                    listener->properties.pop();
                    VERIFY_ARE_EQUAL("group" ,property->getGroup());
                    VERIFY_ARE_EQUAL("" ,property->getName());
                    VERIFY_ARE_EQUAL("value" ,property->getValue());
                    
                    //inorder.verify(listener).onProperty(eq(property().group("").name("PROP").value("value").build())
                    callName = listener->calls.front();
                    listener->calls.pop();
                    VERIFY_ARE_EQUAL(callName, "onProperty");
                    property = listener->properties.front();
                    listener->properties.pop();
                    VERIFY_ARE_EQUAL("" ,property->getGroup());
                    VERIFY_ARE_EQUAL("PROP" ,property->getName());
                    VERIFY_ARE_EQUAL("value" ,property->getValue());
                }
            }
            
            /**
             * Escape sequences for parameter values should not be applied to groups,
             * property names, or parameter names.
             */
            TEST(parameter_value_escape_sequences_in_other_places) {
                std::string string =
                "one\\\\two^^three.four\\\\five^^six;seven\\\\eight^^nine=ten:";
                
                auto list_caretDecodingEnabled = std::list<bool> {false, true};
                for (SyntaxStyle style : styles) {
                    for (bool caretDecodingEnabled : list_caretDecodingEnabled) {
                        auto reader = new VObjectReader(string, style);
                        reader->setCaretDecodingEnabled(caretDecodingEnabled);
                        VObjectDataListenerMock::Ptr listener = std::make_shared<VObjectDataListenerMock>();
                        reader->parse(listener);
                        
                        //inorder.verify(listener).onProperty(eq(property().group("one\\\\two^^three").name("four\\\\five^^six").param("seven\\\\eight^^nine", "ten").value("").build())
                        auto callName = listener->calls.front();
                        listener->calls.pop();
                        VERIFY_ARE_EQUAL(callName, "onProperty");
                        auto property = listener->properties.front();
                        listener->properties.pop();
                        VERIFY_ARE_EQUAL("one\\\\two^^three" ,property->getGroup());
                        VERIFY_ARE_EQUAL("four\\\\five^^six" ,property->getName());
                        VERIFY_ARE_EQUAL("" ,property->getValue());
                        auto params = property->getParameters(); //"seven\\\\eight^^nine", "ten"
                        
                        auto v = params->get("seven\\\\eight^^nine");
                        
                        //params->print();
                        //VERIFY_ARE_EQUAL("ten", v);
                    }
                }
            }
            
            /**
             * When there are special characters in the group and property name.
             */
            TEST(special_characters_in_group_and_name) {
                std::string string =
                "g=,\"roup.P.=,\"ROP:value";
                
                for (SyntaxStyle style : styles) {
                    auto reader = new VObjectReader(string, style);
                    VObjectDataListenerMock::Ptr listener = std::make_shared<VObjectDataListenerMock>();
                    reader->parse(listener);
                    
                    //inorder.verify(listener).onProperty(eq(new VObjectProperty("g=,\"roup", "P.=,\"ROP", "value"))
                    auto callName = listener->calls.front();
                    listener->calls.pop();
                    VERIFY_ARE_EQUAL(callName, "onProperty");
                    auto property = listener->properties.front();
                    listener->properties.pop();
                    VERIFY_ARE_EQUAL("g=,\"roup" ,property->getGroup());
                    VERIFY_ARE_EQUAL("P.=,\"ROP" ,property->getName());
                    VERIFY_ARE_EQUAL("value" ,property->getValue());
                }
            }
            
            /**
             * When a parameter name is empty.
             */
            TEST(blank_parameter_name) {
                std::string string =
                "PROP;=value:value";
                
                for (SyntaxStyle style : styles) {
                    auto reader = new VObjectReader(string, style);
                    VObjectDataListenerMock::Ptr listener = std::make_shared<VObjectDataListenerMock>();
                    reader->parse(listener);
                    
                    //inorder.verify(listener).onProperty(eq(property().name("PROP").param("", "value").value("value").build())
                    auto callName = listener->calls.front();
                    listener->calls.pop();
                    VERIFY_ARE_EQUAL(callName, "onProperty");
                    auto property = listener->properties.front();
                    listener->properties.pop();
                    VERIFY_ARE_EQUAL("PROP" ,property->getName());
                    VERIFY_ARE_EQUAL("value" ,property->getValue());
                    auto params = property->getParameters();
                    auto v = params->get("");
                    
                    //params->print();
                    //VERIFY_ARE_EQUAL("value", v);
                }
            }
            
            /**
             * When a parameter value doesn't have a name.
             */
            TEST(no_parameter_name) {
                std::string string =
                "PROP;HOME;WORK:value";
                
                for (SyntaxStyle style : styles) {
                    auto reader = new VObjectReader(string, style);
                    VObjectDataListenerMock::Ptr listener = std::make_shared<VObjectDataListenerMock>();
                    reader->parse(listener);
                    
                    //inorder.verify(listener).onProperty(eq(property().name("PROP").param(null, "HOME", "WORK").value("value").build())
                    auto callName = listener->calls.front();
                    listener->calls.pop();
                    VERIFY_ARE_EQUAL(callName, "onProperty");
                    auto property = listener->properties.front();
                    listener->properties.pop();
                    VERIFY_ARE_EQUAL("PROP" ,property->getName());
                    VERIFY_ARE_EQUAL("value" ,property->getValue());
                    auto params = property->getParameters();
                    auto v = params->get("");
                    //VERIFY_ARE_EQUAL("value", v);
                    
                    //params->print();
                }
            }
            
            /**
             * When a parameter name has special characters.
             */
            TEST(special_chars_in_parameter_name) {
                std::string string =
                "PROP;P,.\"ARAM=value:value";
                
                for (SyntaxStyle style : styles) {
                    auto reader = new VObjectReader(string, style);
                    VObjectDataListenerMock::Ptr listener = std::make_shared<VObjectDataListenerMock>();
                    reader->parse(listener);
                    
                    //inorder.verify(listener).onProperty(eq(property().name("PROP").param("P,.\"ARAM", "value").value("value").build())
                    auto callName = listener->calls.front();
                    listener->calls.pop();
                    VERIFY_ARE_EQUAL(callName, "onProperty");
                    auto property = listener->properties.front();
                    listener->properties.pop();
                    VERIFY_ARE_EQUAL("PROP" ,property->getName());
                    VERIFY_ARE_EQUAL("value" ,property->getValue());
                    auto params = property->getParameters();
                    auto v = params->get("");
                    //VERIFY_ARE_EQUAL("value", v);
                }
            }
            
            /**
             * If there is any whitespace surrounding the equals character in a
             * parameter declaration, it is handled differently depending on the
             * version.
             */
            TEST(parameters_space_around_equals) {
                //@formatter:off
                std::string string =
                "PROP;PARAM = value:value";
                //@formatter:on
                
                SyntaxStyle style = SyntaxStyle::OLD;
                {
                    auto reader = new VObjectReader(string, style);
                    VObjectDataListenerMock::Ptr listener = std::make_shared<VObjectDataListenerMock>();
                    reader->parse(listener);
                    
                    //inorder.verify(listener).onProperty(eq(property().name("PROP").param("PARAM", "value").value("value").build())
                    auto callName = listener->calls.front();
                    listener->calls.pop();
                    VERIFY_ARE_EQUAL(callName, "onProperty");
                    auto property = listener->properties.front();
                    listener->properties.pop();
                    VERIFY_ARE_EQUAL("PROP" ,property->getName());
                    VERIFY_ARE_EQUAL("value" ,property->getValue());
                    auto params = property->getParameters();
                    auto v = params->get("");
                    //VERIFY_ARE_EQUAL("value", v);
                }
                
                style = SyntaxStyle::NEW;
                {
                    auto reader = new VObjectReader(string, style);
                    VObjectDataListenerMock::Ptr listener = std::make_shared<VObjectDataListenerMock>();
                    reader->parse(listener);
                    
                    //inorder.verify(listener).onProperty(eq(property().name("PROP").param("PARAM ", " value").value("value").build())
                    auto callName = listener->calls.front();
                    listener->calls.pop();
                    VERIFY_ARE_EQUAL(callName, "onProperty");
                    auto property = listener->properties.front();
                    listener->properties.pop();
                    VERIFY_ARE_EQUAL("PROP" ,property->getName());
                    VERIFY_ARE_EQUAL("value" ,property->getValue());
                    auto params = property->getParameters();
                    auto v = params->get("");
                    //VERIFY_ARE_EQUAL("value", v);
                }
            }
            
            /**
             * New style syntax has special syntax for defining multi-valued parameters.
             */
            TEST(multi_valued_parameters) {
                std::string string =
                "PROP;PARAM=value1,value2:value";
                
                SyntaxStyle style = SyntaxStyle::OLD;
                {
                    auto reader = new VObjectReader(string, style);
                    VObjectDataListenerMock::Ptr listener = std::make_shared<VObjectDataListenerMock>();
                    reader->parse(listener);
                    
                    //inorder.verify(listener).onProperty(eq(property().name("PROP").param("PARAM", "value1,value2").value("value").build())
                    auto callName = listener->calls.front();
                    listener->calls.pop();
                    VERIFY_ARE_EQUAL(callName, "onProperty");
                    auto property = listener->properties.front();
                    listener->properties.pop();
                    VERIFY_ARE_EQUAL("PROP" ,property->getName());
                    VERIFY_ARE_EQUAL("value" ,property->getValue());
                    auto params = property->getParameters();
                    auto v = params->get("");
                    //VERIFY_ARE_EQUAL("value", v);
                }
                
                style = SyntaxStyle::NEW;
                {
                    auto reader = new VObjectReader(string, style);
                    VObjectDataListenerMock::Ptr listener = std::make_shared<VObjectDataListenerMock>();
                    reader->parse(listener);
                    
                    //inorder.verify(listener).onProperty(eq(property().name("PROP").param("PARAM", "value1", "value2").value("value").build())
                    auto callName = listener->calls.front();
                    listener->calls.pop();
                    VERIFY_ARE_EQUAL(callName, "onProperty");
                    auto property = listener->properties.front();
                    listener->properties.pop();
                    VERIFY_ARE_EQUAL("PROP" ,property->getName());
                    VERIFY_ARE_EQUAL("value" ,property->getValue());
                    auto params = property->getParameters();
                    auto v = params->get("");
                    //VERIFY_ARE_EQUAL("value", v);
                }
            }
            
            /**
             * New style syntax lets you surround parameter values in double quotes.
             * Doing this lets you put special characters like semi-colons in the
             * property value.
             */
            TEST(parameter_values_in_double_quotes) {
                std::string string =
                "PROP;PARAM=\"a;b:c,d\":value";
                SyntaxStyle style = SyntaxStyle::OLD;
                {
                    auto reader = std::make_shared<VObjectReader>(string, style);
                    VObjectDataListenerMock::Ptr listener = std::make_shared<VObjectDataListenerMock>();
                    reader->parse(listener);
                    
                    auto callName = listener->calls.front();
                    listener->calls.pop();
                    VERIFY_ARE_EQUAL(callName, "onProperty");
                    auto property = listener->properties.front();
                    listener->properties.pop();
                    VERIFY_ARE_EQUAL("PROP" ,property->getName());
                    VERIFY_ARE_EQUAL("c,d\":value" ,property->getValue());
                    auto params = property->getParameters();
                    auto v = params->get("PARAM");
                    VERIFY_IS_TRUE(v.size() == 1);
                    VERIFY_ARE_EQUAL("\"a", v.front());
                    v = params->get("");
                    VERIFY_IS_TRUE(v.size() == 1);
                    VERIFY_ARE_EQUAL("b", v.front());
                }
                
                style = SyntaxStyle::NEW;
                {
                    auto reader = std::make_shared<VObjectReader>(string, style);
                    auto listener = std::make_shared<VObjectDataListenerMock>();
                    reader->parse(listener);
                    
                    auto callName = listener->calls.front();
                    listener->calls.pop();
                    VERIFY_ARE_EQUAL(callName, "onProperty");
                    auto property = listener->properties.front();
                    listener->properties.pop();
                    VERIFY_ARE_EQUAL("PROP" ,property->getName());
                    VERIFY_ARE_EQUAL("value" ,property->getValue());
                    auto params = property->getParameters();
                    auto v = params->get("PARAM");
                    VERIFY_IS_TRUE(v.size() == 1);
                    VERIFY_ARE_EQUAL("a;b:c,d", v.front());
                    v = params->get("");
                    VERIFY_IS_TRUE(v.size() == 0);
                }
            }
            
            
            /**
             * Tests the various escaping mechanisms for parameter values.
             */
            TEST(parameter_value_escaping) {
                
                SyntaxStyle style = SyntaxStyle::OLD;
                {
                    //1: backslash that doesn't escape anything
                    //2: caret-escaped caret
                    //3: caret-escaped newline (lowercase n)
                    //4: caret-escaped newline (uppercase N)
                    //5: caret-escaped double quote
                    //6: caret that doesn't escape anything
                    //7: backslash-escaped semi-colon (must be escaped in 2.1)
                    //8: un-escaped double quote (no special meaning in 2.1)
                    //9: backslash-escaped backslash
                    std::string string =
                    "PROP;PARAM=1\\ 2^^ 3^n 4^N 5^' 6^ 7\\; 8\" 9\\\\:";
                    for (auto caretDecodingEnabled :  { false, true }) { //caret decoding has no effect in old style
                        auto reader = std::make_shared<VObjectReader>(string, style);
                        auto listener = std::make_shared<VObjectDataListenerMock>();
                        reader->setCaretDecodingEnabled(caretDecodingEnabled);
                        reader->parse(listener);
                        
                        auto callName = listener->calls.front();
                        listener->calls.pop();
                        VERIFY_ARE_EQUAL(callName, "onProperty");
                        
                        auto property = listener->properties.front();
                        listener->properties.pop();
                        VERIFY_ARE_EQUAL("PROP" ,property->getName());
                        VERIFY_ARE_EQUAL("" ,property->getValue());
                        
                        auto params = property->getParameters();
                        auto v = params->get("PARAM");
                        VERIFY_IS_TRUE(v.size() == 1);
                        VERIFY_ARE_EQUAL("1\\ 2^^ 3^n 4^N 5^' 6^ 7; 8\" 9\\", v.front());
                        v = params->get("");
                        VERIFY_IS_TRUE(v.size() == 0);
                    }
                }
                
                style = SyntaxStyle::NEW;
                {
                    //1: backslash that doesn't escape anything
                    //2: caret-escaped caret
                    //3: caret-escaped newline (lowercase n)
                    //4: caret-escaped newline (uppercase N)
                    //5: backslash-escaped newline (lowercase n)
                    //7: caret-escaped double quote
                    //8: backslash-escaped backslash
                    //9: caret that doesn't escape anything
                    
                    std::string string =
                    "PROP;PARAM=1\\ 2^^ 3^n 4^N 5\\n 7^' 8\\\\ 9^ :";
                    for (auto caretDecodingEnabled :  { false, true }) { //caret decoding has no effect in old style
                        auto reader = std::make_shared<VObjectReader>(string, style);
                        auto listener = std::make_shared<VObjectDataListenerMock>();
                        reader->setCaretDecodingEnabled(caretDecodingEnabled);
                        reader->parse(listener);
                        
                        auto callName = listener->calls.front();
                        listener->calls.pop();
                        VERIFY_ARE_EQUAL(callName, "onProperty");
                        
                        auto property = listener->properties.front();
                        listener->properties.pop();
                        VERIFY_ARE_EQUAL("PROP" ,property->getName());
                        VERIFY_ARE_EQUAL("" ,property->getValue());
                        
                        auto params = property->getParameters();
                        auto v = params->get("PARAM");
                        VERIFY_IS_TRUE(v.size() == 1);
                        auto check = v.front();
                        if (caretDecodingEnabled) {
                            std::string a = "1\\ 2^ 3"  /*NEWLINE"\n\r"*/  " 4^N 5\\n 7\" 8\\\\ 9^ ";
                            VERIFY_ARE_EQUAL(a, check);
                        } else {
                            VERIFY_ARE_EQUAL("1\\ 2^^ 3^n 4^N 5\\n 7^' 8\\\\ 9^ ", check);
                        }
                        
                        v = params->get("");
                        VERIFY_IS_TRUE(v.size() == 0);
                    }
                }
            }
            
            /**
             * Asserts that it can unfold folded lines.
             */
            TEST(folded_lines) {
                std::string string =
                "PROP:fo\r\n"
                " lded\r\n"
                "PROP:fo\r\n"
                "\tlded\r\n"
                "PROP:fo\r\n"
                " \r\n"  //empty folded line
                " lded\r\n"
                "PROP:fo\r\n"
                " \tlded\r\n"
                "PROP:fo\r\n"
                "\t lded\r\n"
                "PROP;ENCODING=QUOTED-PRINTABLE:fo=\r\n"
                " lded\r\n"
                "PROP;QUOTED-PRINTABLE:fo=\r\n"
                " lded\r\n"
                "PROP;ENCODING=QUOTED-PRINTABLE:fo=\r\n"
                "lded\r\n"
                "PROP;P\r\n"
                " ARAM=value:\r\n"
                "PROP:last";
                
                SyntaxStyle style = SyntaxStyle::OLD;
                {
                    auto reader = std::make_shared<VObjectReader>(string, style);
                    auto listener = std::make_shared<VObjectDataListenerMock>();
                    reader->parse(listener);
                    
                    for (int i=0; i<5; i++) {
                        auto property = listener->properties.front();
                        listener->properties.pop();
                        VERIFY_ARE_EQUAL("PROP" ,property->getName());
                        VERIFY_ARE_EQUAL("folded" ,property->getValue());
                    }
                    
                    auto property = listener->properties.front();
                    listener->properties.pop();
                    VERIFY_ARE_EQUAL("PROP" ,property->getName());
                    VERIFY_ARE_EQUAL("folded" ,property->getValue());
                    auto params = property->getParameters();
                    auto v = params->get("ENCODING");
                    VERIFY_IS_TRUE(v.size() == 1);
                    auto check = v.front();
                    VERIFY_ARE_EQUAL("QUOTED-PRINTABLE", check);
                    
                    property = listener->properties.front();
                    listener->properties.pop();
                    VERIFY_ARE_EQUAL("PROP" ,property->getName());
                    VERIFY_ARE_EQUAL("folded" ,property->getValue());
                    params = property->getParameters();
                    v = params->get("");
                    VERIFY_IS_TRUE(v.size() == 1);
                    check = v.front();
                    VERIFY_ARE_EQUAL("QUOTED-PRINTABLE", check);
                    
                    property = listener->properties.front();
                    listener->properties.pop();
                    VERIFY_ARE_EQUAL("PROP" ,property->getName());
                    VERIFY_ARE_EQUAL("folded" ,property->getValue());
                    params = property->getParameters();
                    v = params->get("ENCODING");
                    VERIFY_IS_TRUE(v.size() == 1);
                    check = v.front();
                    VERIFY_ARE_EQUAL("QUOTED-PRINTABLE", check);
                    
                    property = listener->properties.front();
                    listener->properties.pop();
                    VERIFY_ARE_EQUAL("PROP" ,property->getName());
                    VERIFY_ARE_EQUAL("" ,property->getValue());
                    params = property->getParameters();
                    v = params->get("PARAM");
                    VERIFY_IS_TRUE(v.size() == 1);
                    check = v.front();
                    VERIFY_ARE_EQUAL("value", check);
                    
                    property = listener->properties.front();
                    listener->properties.pop();
                    VERIFY_ARE_EQUAL("PROP" ,property->getName());
                    VERIFY_ARE_EQUAL("last" ,property->getValue());
                    params = property->getParameters();
                    v = params->get("PARAM");
                    VERIFY_IS_TRUE(v.size() == 0);
                    
                    const std::map<int, std::string> checklist = {
                        {1, "PROP:folded"},
                        {3, "PROP:folded"},
                        {5, "PROP:folded"},
                        {8, "PROP:folded"},
                        {10, "PROP:folded"},
                        {12, "PROP;ENCODING=QUOTED-PRINTABLE:folded"},
                        {14, "PROP;QUOTED-PRINTABLE:folded"},
                        {16, "PROP;ENCODING=QUOTED-PRINTABLE:folded"},
                        {18, "PROP;PARAM=value:"},
                        {20, "PROP:last"}
                    };
                    auto i = 0;
                    for(auto iterator = checklist.begin(); iterator != checklist.end(); iterator++) {
                        auto key = iterator->first;
                        auto value = iterator->second;
                        VERIFY_IS_TRUE(listener->contexts.size() > i);
                        auto check_ctx = listener->contexts[i];
                        VERIFY_IS_FALSE(check_ctx == nullptr);
                        auto check_value = check_ctx->getUnfoldedLine();
                        VERIFY_ARE_EQUAL(value, check_value);
                        VERIFY_IS_TRUE(key == check_ctx->getLineNumber());
                        i ++;
                    }
                }
                
                style = SyntaxStyle::NEW;
                {
                    auto reader = std::make_shared<VObjectReader>(string, style);
                    auto listener = std::make_shared<VObjectDataListenerMock>();
                    reader->parse(listener);
                    
                    for (int i=0; i<3; i++) {
                        auto property = listener->properties.front();
                        listener->properties.pop();
                        VERIFY_ARE_EQUAL("PROP" ,property->getName());
                        VERIFY_ARE_EQUAL("folded" ,property->getValue());
                    }
                    
                    auto property = listener->properties.front();
                    listener->properties.pop();
                    VERIFY_ARE_EQUAL("PROP" ,property->getName());
                    VERIFY_ARE_EQUAL("fo\tlded" ,property->getValue());
                    auto params = property->getParameters();
                    VERIFY_IS_TRUE(params->getMap().size() == 0);
                    
                    property = listener->properties.front();
                    listener->properties.pop();
                    VERIFY_ARE_EQUAL("PROP" ,property->getName());
                    VERIFY_ARE_EQUAL("fo lded" ,property->getValue());
                    params = property->getParameters();
                    VERIFY_IS_TRUE(params->getMap().size() == 0);
                    
                    property = listener->properties.front();
                    listener->properties.pop();
                    VERIFY_ARE_EQUAL("PROP" ,property->getName());
                    VERIFY_ARE_EQUAL("folded" ,property->getValue());
                    params = property->getParameters();
                    auto v = params->get("ENCODING");
                    VERIFY_IS_TRUE(v.size() == 1);
                    auto check = v.front();
                    VERIFY_ARE_EQUAL("QUOTED-PRINTABLE", check);
                    
                    property = listener->properties.front();
                    listener->properties.pop();
                    VERIFY_ARE_EQUAL("PROP" ,property->getName());
                    VERIFY_ARE_EQUAL("folded" ,property->getValue());
                    params = property->getParameters();
                    v = params->get("");
                    VERIFY_IS_TRUE(v.size() == 1);
                    check = v.front();
                    VERIFY_ARE_EQUAL("QUOTED-PRINTABLE", check);
                    
                    property = listener->properties.front();
                    listener->properties.pop();
                    VERIFY_ARE_EQUAL("PROP" ,property->getName());
                    VERIFY_ARE_EQUAL("folded" ,property->getValue());
                    params = property->getParameters();
                    v = params->get("ENCODING");
                    VERIFY_IS_TRUE(v.size() == 1);
                    check = v.front();
                    VERIFY_ARE_EQUAL("QUOTED-PRINTABLE", check);
                    
                    property = listener->properties.front();
                    listener->properties.pop();
                    VERIFY_ARE_EQUAL("PROP" ,property->getName());
                    VERIFY_ARE_EQUAL("" ,property->getValue());
                    params = property->getParameters();
                    v = params->get("PARAM");
                    VERIFY_IS_TRUE(v.size() == 1);
                    check = v.front();
                    VERIFY_ARE_EQUAL("value", check);
                    
                    property = listener->properties.front();
                    listener->properties.pop();
                    VERIFY_ARE_EQUAL("PROP" ,property->getName());
                    VERIFY_ARE_EQUAL("last" ,property->getValue());
                    params = property->getParameters();
                    v = params->get("PARAM");
                    VERIFY_IS_TRUE(v.size() == 0);
                    
                    const std::map<int, std::string> checklist = {
                        {1, "PROP:folded"},
                        {3, "PROP:folded"},
                        {5, "PROP:folded"},
                        {8, "PROP:fo\tlded"},
                        {10, "PROP:fo lded"},
                        {12, "PROP;ENCODING=QUOTED-PRINTABLE:folded"},
                        {14, "PROP;QUOTED-PRINTABLE:folded"},
                        {16, "PROP;ENCODING=QUOTED-PRINTABLE:folded"},
                        {18, "PROP;PARAM=value:"},
                        {20, "PROP:last"}
                    };
                    auto i = 0;
                    for(auto iterator = checklist.begin(); iterator != checklist.end(); iterator++) {
                        auto key = iterator->first;
                        auto value = iterator->second;
                        VERIFY_IS_TRUE(listener->contexts.size() > i);
                        auto check_ctx = listener->contexts[i];
                        VERIFY_IS_FALSE(check_ctx == nullptr);
                        auto check_value = check_ctx->getUnfoldedLine();
                        VERIFY_ARE_EQUAL(value, check_value);
                        VERIFY_IS_TRUE(key == check_ctx->getLineNumber());
                        i ++;
                    }
                }
            }
            
            /**
             * Tests quoted-printable encoding.
             */
            TEST(quoted_printable) {
                std::string string =
                "PROP;QUOTED-PRINTABLE:one=0D=0Atwo\r\n"
                "PROP;quoted-printable:one=0D=0Atwo\r\n"
                "PROP;ENCODING=QUOTED-PRINTABLE:one=0D=0Atwo\r\n"
                "PROP;ENCODING=quoted-printable:one=0D=0Atwo\r\n"
                "PROP;ENCODING=QUOTED-PRINTABLE:=XX\r\n"
                "PROP;ENCODING=QUOTED-PRINTABLE;CHARSET=UTF-8:one=0D=0Atwo\r\n"
                "PROP;ENCODING=QUOTED-PRINTABLE;CHARSET=invalid:one=0D=0Atwo\r\n"
                "PROP;ENCODING=QUOTED-PRINTABLE;CHARSET=illegal name:one=0D=0Atwo";
                
                for (auto style : styles) {
                    auto reader = std::make_shared<VObjectReader>(string, style);
                    auto listener = std::make_shared<VObjectDataListenerMock>();
                    reader->parse(listener);
                    
                    auto property = listener->properties.front();
                    listener->properties.pop();
                    VERIFY_ARE_EQUAL("PROP" ,property->getName());
                    VERIFY_ARE_EQUAL("one\r\ntwo" ,property->getValue());
                    auto params = property->getParameters();
                    VERIFY_IS_TRUE(params->getMap().size() == 1);
                    auto v = params->get("");
                    VERIFY_IS_TRUE(v.size() == 1);
                    auto check = v.front();
                    VERIFY_ARE_EQUAL("QUOTED-PRINTABLE", check);
                    
                    property = listener->properties.front();
                    listener->properties.pop();
                    VERIFY_ARE_EQUAL("PROP" ,property->getName());
                    VERIFY_ARE_EQUAL("one\r\ntwo" ,property->getValue());
                    params = property->getParameters();
                    VERIFY_IS_TRUE(params->getMap().size() == 1);
                    v = params->get("");
                    VERIFY_IS_TRUE(v.size() == 1);
                    check = v.front();
                    VERIFY_ARE_EQUAL("quoted-printable", check);
                    
                    property = listener->properties.front();
                    listener->properties.pop();
                    VERIFY_ARE_EQUAL("PROP" ,property->getName());
                    VERIFY_ARE_EQUAL("one\r\ntwo" ,property->getValue());
                    params = property->getParameters();
                    VERIFY_IS_TRUE(params->getMap().size() == 1);
                    v = params->get("ENCODING");
                    VERIFY_IS_TRUE(v.size() == 1);
                    check = v.front();
                    VERIFY_ARE_EQUAL("QUOTED-PRINTABLE", check);
                    
                    property = listener->properties.front();
                    listener->properties.pop();
                    VERIFY_ARE_EQUAL("PROP" ,property->getName());
                    VERIFY_ARE_EQUAL("one\r\ntwo" ,property->getValue());
                    params = property->getParameters();
                    VERIFY_IS_TRUE(params->getMap().size() == 1);
                    v = params->get("ENCODING");
                    VERIFY_IS_TRUE(v.size() == 1);
                    check = v.front();
                    VERIFY_ARE_EQUAL("quoted-printable", check);
                    
                    property = listener->properties.front();
                    listener->properties.pop();
                    VERIFY_ARE_EQUAL("PROP" ,property->getName());
                    VERIFY_ARE_EQUAL("=XX" ,property->getValue());
                    params = property->getParameters();
                    v = params->get("ENCODING");
                    VERIFY_IS_TRUE(v.size() == 1);
                    check = v.front();
                    VERIFY_ARE_EQUAL("QUOTED-PRINTABLE", check);
                    
                    auto warning = listener->warnings.front();
                    listener->warnings.pop();
                    VERIFY_ARE_EQUAL("Error: MALFORMED_INPUT.", warning);
                    
                    property = listener->properties.front();
                    listener->properties.pop();
                    VERIFY_ARE_EQUAL("PROP" ,property->getName());
                    VERIFY_ARE_EQUAL("one\r\ntwo" ,property->getValue());
                    params = property->getParameters();
                    v = params->get("ENCODING");
                    VERIFY_IS_TRUE(v.size() == 1);
                    check = v.front();
                    VERIFY_ARE_EQUAL("QUOTED-PRINTABLE", check);
                    v = params->get("CHARSET");
                    VERIFY_IS_TRUE(v.size() == 1);
                    check = v.front();
                    VERIFY_ARE_EQUAL("UTF-8", check);
                    
                    property = listener->properties.front();
                    listener->properties.pop();
                    VERIFY_ARE_EQUAL("PROP" ,property->getName());
                    VERIFY_ARE_EQUAL("one\r\ntwo" ,property->getValue());
                    params = property->getParameters();
                    v = params->get("ENCODING");
                    VERIFY_IS_TRUE(v.size() == 1);
                    check = v.front();
                    VERIFY_ARE_EQUAL("QUOTED-PRINTABLE", check);
                    v = params->get("CHARSET");
                    VERIFY_IS_TRUE(v.size() == 1);
                    check = v.front();
                    VERIFY_ARE_EQUAL("invalid", check);
                    
                    //TODO::need check charset is valid
                    //                    auto warning = listener->warnings.front();
                    //                    listener->warnings.pop();
                    //                    VERIFY_ARE_EQUAL("Error: MALFORMED_INPUT.", warning);
                    //                    inorder.verify(listener).onWarning(eq(Warning.UNKNOWN_CHARSET), eq(invalidCharset), any(UnsupportedCharsetException.class), any(Context.class));
                    
                    property = listener->properties.front();
                    listener->properties.pop();
                    VERIFY_ARE_EQUAL("PROP" ,property->getName());
                    VERIFY_ARE_EQUAL("one\r\ntwo" ,property->getValue());
                    params = property->getParameters();
                    v = params->get("ENCODING");
                    VERIFY_IS_TRUE(v.size() == 1);
                    check = v.front();
                    VERIFY_ARE_EQUAL("QUOTED-PRINTABLE", check);
                    v = params->get("CHARSET");
                    VERIFY_IS_TRUE(v.size() == 1);
                    check = v.front();
                    VERIFY_ARE_EQUAL("illegal name", check);
                    
                    //TODO::need check charset is valid
                    //                    auto warning = listener->warnings.front();
                    //                    listener->warnings.pop();
                    //                    VERIFY_ARE_EQUAL("Error: MALFORMED_INPUT.", warning);
                    //                    inorder.verify(listener).onWarning(eq(Warning.UNKNOWN_CHARSET), eq(illegalName), any(IllegalCharsetNameException.class), any(Context.class));
                    
                    auto lines = ProtonMail::str_split(string,"\r\n");
                    auto line_i = 0;
                    auto ctx_i = 0;
                    for (auto lineValue : lines) {
                        auto check_ctx = listener->contexts[ctx_i++];
                        VERIFY_IS_FALSE(check_ctx == nullptr);
                        auto check_value = check_ctx->getUnfoldedLine();
                        VERIFY_ARE_EQUAL(lineValue, check_value);
                        VERIFY_IS_TRUE((line_i + 1) == check_ctx->getLineNumber());
                        
                        if (ctx_i == 5 /*|| ctx_i == 8 || ctx_i == 10*/ ) {  //TODO:: need to check charset error later
                            auto check_ctx = listener->contexts[ctx_i++];
                            VERIFY_IS_FALSE(check_ctx == nullptr);
                            auto check_value = check_ctx->getUnfoldedLine();
                            VERIFY_ARE_EQUAL(lineValue, check_value);
                            VERIFY_IS_TRUE((line_i + 1) == check_ctx->getLineNumber());
                        }
                        line_i++;
                    }
                }
            }
            
            ////TODO::need finish later
            //            /**
            //             * Verify the logic for choosing a character set to decode a
            //             * quoted-printable value in when the property does not specify a character
            //             * set.
            //             */
            //            @Test
            //            public void quoted_printable_choose_default_encoding() throws Exception {
            //                String decoded = "one=two";
            //
            //                //no default encoding set
            //                //writer doesn't have encoding
            //                //-> use system default
            //                {
            //                    Charset charset = Charset.defaultCharset();
            //                    QuotedPrintableCodec codec = new QuotedPrintableCodec(charset.name());
            //                    String encoded = codec.encode(decoded);
            //
            //                    //@formatter:off
            //                    String string =
            //                    "PROP;QUOTED-PRINTABLE:" + encoded + "\r\n";
            //                    //@formatter:on
            //
            //                    for (SyntaxStyle style : SyntaxStyle.values()) {
            //                        VObjectReader reader = reader(string, style);
            //                        VObjectDataListenerMock listener = spy(new VObjectDataListenerMock());
            //                        reader.parse(listener);
            //
            //                        InOrder inorder = inOrder(listener);
            //                        VObjectProperty invalidCharset = property().name("PROP").param(null, "QUOTED-PRINTABLE").value(decoded).build();
            //                        inorder.verify(listener).onProperty(eq(invalidCharset), any(Context.class));
            //
            //                        //@formatter:off
            //                        String lines[] = string.split("\r\n");
            //                        int line = 0;
            //                        assertContexts(listener,
            //                                       context(lines[line], ++line)
            //                                       );
            //                        //@formatter:on
            //                    }
            //                }
            //
            //                //no default encoding set
            //                //writer has encoding
            //                //-> user writer encoding
            //                {
            //                    Charset charset = Charset.forName("UTF-16");
            //                    QuotedPrintableCodec codec = new QuotedPrintableCodec(charset.name());
            //                    String encoded = codec.encode(decoded);
            //
            //                    //@formatter:off
            //                    String string =
            //                    "PROP;QUOTED-PRINTABLE:" + encoded + "\r\n";
            //                    //@formatter:on
            //
            //                    for (SyntaxStyle style : SyntaxStyle.values()) {
            //                        Reader r = new InputStreamReader(new ByteArrayInputStream(string.getBytes(charset)), charset);
            //                        VObjectReader reader = new VObjectReader(r, new SyntaxRules(style));
            //                        VObjectDataListenerMock listener = spy(new VObjectDataListenerMock());
            //                        reader.parse(listener);
            //
            //                        InOrder inorder = inOrder(listener);
            //                        VObjectProperty invalidCharset = property().name("PROP").param(null, "QUOTED-PRINTABLE").value(decoded).build();
            //                        inorder.verify(listener).onProperty(eq(invalidCharset), any(Context.class));
            //
            //                        //@formatter:off
            //                        String lines[] = string.split("\r\n");
            //                        int line = 0;
            //                        assertContexts(listener,
            //                                       context(lines[line], ++line)
            //                                       );
            //                        //@formatter:on
            //                    }
            //                }
            //
            //                //default encoding set
            //                //-> use it
            //                {
            //                    Charset charset = Charset.forName("UTF-16");
            //                    QuotedPrintableCodec codec = new QuotedPrintableCodec(charset.name());
            //                    String encoded = codec.encode(decoded);
            //
            //                    //@formatter:off
            //                    String string =
            //                    "PROP;QUOTED-PRINTABLE:" + encoded + "\r\n";
            //                    //@formatter:on
            //
            //                    for (SyntaxStyle style : SyntaxStyle.values()) {
            //                        Reader r = new StringReader(string);
            //                        VObjectReader reader = new VObjectReader(r, new SyntaxRules(style));
            //                        reader.setDefaultQuotedPrintableCharset(charset);
            //                        VObjectDataListenerMock listener = spy(new VObjectDataListenerMock());
            //                        reader.parse(listener);
            //
            //                        InOrder inorder = inOrder(listener);
            //                        VObjectProperty invalidCharset = property().name("PROP").param(null, "QUOTED-PRINTABLE").value(decoded).build();
            //                        inorder.verify(listener).onProperty(eq(invalidCharset), any(Context.class));
            //
            //                        //@formatter:off
            //                        String lines[] = string.split("\r\n");
            //                        int line = 0;
            //                        assertContexts(listener,
            //                                       context(lines[line], ++line)
            //                                       );
            //                        //@formatter:on
            //                    }
            //                }
            //            }
            //
            /**
             * When a parameter value doesn't have a name.
             */
            TEST(syntax_style_rules) {
                std::string string =
                "VERSION:1\r\n"
                "BEGIN:COMP1\r\n"
                        "PROP;PARAM=\"value\":\r\n"  //default to OLD style
                "END:COMP1\r\n"
                "BEGIN:COMP1\r\n"
                        "VERSION:2\r\n"  //wrong parent
                        "PROP;PARAM=\"value\":\r\n"
                "END:COMP1\r\n"
                "BEGIN:COMP2\r\n"
                        "VERSION:3\r\n"  //invalid version
                        "PROP;PARAM=\"value\":\r\n"
                "END:COMP2\r\n"
                "BEGIN:COMP2\r\n"
                        "VERSION:2\r\n"
                        "PROP;PARAM=\"value\":\r\n"
                        "BEGIN:COMP3\r\n"//keep syntax of parent
                                "PROP;PARAM=\"value\":\r\n"
                        "END:COMP3\r\n"
                        "BEGIN:COMP2\r\n" //change syntax
                                "VERSION:1\r\n"
                                "PROP;PARAM=\"value\":\r\n"
                        "END:COMP2\r\n"
                        "PROP;PARAM=\"value\":\r\n" //syntax returns
                "END:COMP2\r\n";
                
                SyntaxRules rules = SyntaxRules(SyntaxStyle::OLD);
                rules.addRule("COMP2", "1", SyntaxStyle::OLD);
                rules.addRule("COMP2", "2", SyntaxStyle::NEW);
                
                auto reader = std::make_shared<VObjectReader>(string, rules);
                auto listener = std::make_shared<VObjectDataListenerMock>();
                reader->parse(listener);
                
                auto oldStyleProp = std::make_shared<VObjectProperty>();
                oldStyleProp->setName("PROP");
                oldStyleProp->setValue("");
                oldStyleProp->getParameters()->put("PARAM", "\"value\"");
                auto newStyleProp = std::make_shared<VObjectProperty>();
                newStyleProp->setName("PROP");
                newStyleProp->setValue("");
                newStyleProp->getParameters()->put("PARAM", "value");

                auto callName = listener->calls.front();
                listener->calls.pop();
                VERIFY_ARE_EQUAL(callName, "onProperty");
                callName = listener->calls.front();
                listener->calls.pop();
                VERIFY_ARE_EQUAL(callName, "onComponentBegin");
                auto name = listener->names.front();
                listener->names.pop();
                VERIFY_ARE_EQUAL("COMP1", name);
                callName = listener->calls.front();
                listener->calls.pop();
                VERIFY_ARE_EQUAL(callName, "onProperty");
                callName = listener->calls.front();
                listener->calls.pop();
                VERIFY_ARE_EQUAL(callName, "onComponentEnd");
                name = listener->names.front();
                listener->names.pop();
                VERIFY_ARE_EQUAL("COMP1", name);
                auto property = listener->properties.front();
                listener->properties.pop();
                VERIFY_ARE_EQUAL("VERSION" ,property->getName());
                VERIFY_ARE_EQUAL("1" ,property->getValue());
                auto params = property->getParameters();
                VERIFY_IS_TRUE(params->getMap().size() == 0);
                property = listener->properties.front();
                listener->properties.pop();
                property->equals(oldStyleProp);
                
                callName = listener->calls.front();
                listener->calls.pop();
                VERIFY_ARE_EQUAL(callName, "onComponentBegin");
                name = listener->names.front();
                listener->names.pop();
                VERIFY_ARE_EQUAL("COMP1", name);
                callName = listener->calls.front();
                listener->calls.pop();
                VERIFY_ARE_EQUAL(callName, "onProperty");
                callName = listener->calls.front();
                listener->calls.pop();
                VERIFY_ARE_EQUAL(callName, "onProperty");
                callName = listener->calls.front();
                listener->calls.pop();
                VERIFY_ARE_EQUAL(callName, "onComponentEnd");
                name = listener->names.front();
                listener->names.pop();
                VERIFY_ARE_EQUAL("COMP1", name);
                property = listener->properties.front();
                listener->properties.pop();
                VERIFY_ARE_EQUAL("VERSION" ,property->getName());
                VERIFY_ARE_EQUAL("2" ,property->getValue());
                params = property->getParameters();
                VERIFY_IS_TRUE(params->getMap().size() == 0);
                property = listener->properties.front();
                listener->properties.pop();
                VERIFY_IS_TRUE(property->equals(oldStyleProp));
                

                callName = listener->calls.front();
                listener->calls.pop();
                VERIFY_ARE_EQUAL(callName, "onComponentBegin");
                name = listener->names.front();
                listener->names.pop();
                VERIFY_ARE_EQUAL("COMP2", name);
//                callName = listener->calls.front();
//                listener->calls.pop();
//                VERIFY_ARE_EQUAL(callName, "onWarning");
//                auto warning = listener->warnings.front();
//                listener->warnings.pop();
//                VERIFY_ARE_EQUAL("onWarning", warning);
                
//                callName = listener->calls.front();
//                listener->calls.pop();
//                VERIFY_ARE_EQUAL(callName, "onVersion");
//                callName = listener->calls.front();
//                listener->calls.pop();
//                VERIFY_ARE_EQUAL(callName, "onProperty");
//                callName = listener->calls.front();
//                listener->calls.pop();
//                VERIFY_ARE_EQUAL(callName, "onProperty");
//                callName = listener->calls.front();
//                listener->calls.pop();
//                VERIFY_ARE_EQUAL(callName, "onComponentEnd");
//                name = listener->names.front();
//                listener->names.pop();
//                VERIFY_ARE_EQUAL("COMP2", name);
//                property = listener->properties.front();
//                listener->properties.pop();
//                VERIFY_ARE_EQUAL("VERSION" ,property->getName());
//                VERIFY_ARE_EQUAL("3" ,property->getValue());
//                params = property->getParameters();
//                VERIFY_IS_TRUE(params->getMap().size() == 0);
//                property = listener->properties.front();
//                listener->properties.pop();
//                property->equals(oldStyleProp);
                
                property = listener->properties.front();
                listener->properties.pop();
                VERIFY_ARE_EQUAL("VERSION" ,property->getName());
                VERIFY_ARE_EQUAL("3" ,property->getValue());
                params = property->getParameters();
                VERIFY_IS_TRUE(params->getMap().size() == 0);
                
                property = listener->properties.front();
                listener->properties.pop();
                VERIFY_IS_TRUE(property->equals(oldStyleProp));
                
                property = listener->properties.front();
                listener->properties.pop();
                VERIFY_IS_TRUE(property->equals(newStyleProp));
                
                property = listener->properties.front();
                listener->properties.pop();
                VERIFY_IS_TRUE(property->equals(newStyleProp));
                
                property = listener->properties.front();
                listener->properties.pop();
                VERIFY_IS_TRUE(property->equals(oldStyleProp));
                
                property = listener->properties.front();
                listener->properties.pop();
                VERIFY_IS_TRUE(property->equals(newStyleProp));
            }
            
            TEST(icalendar_rules) {
                std::string string =
                "BEGIN:VCALENDAR\r\n"
                        "PROP;PARAM=\"value\":\r\n"
                "END:VCALENDAR\r\n"
                "BEGIN:VCALENDAR\r\n"
                        "VERSION:10\r\n"
                        "PROP;PARAM=\"value\":\r\n"
                "END:VCALENDAR\r\n"
                "BEGIN:VCALENDAR\r\n"
                        "VERSION:1.0\r\n"
                        "PROP;PARAM=\"value\":\r\n"
                "END:VCALENDAR\r\n"
                "BEGIN:VCALENDAR\r\n"
                        "VERSION:2.0\r\n"
                        "PROP;PARAM=\"value\":\r\n"
                "END:VCALENDAR\r\n";
                
                auto reader = std::make_shared<VObjectReader>(string, SyntaxRules::iCalendar());
                auto listener = std::make_shared<VObjectDataListenerMock>();
                reader->parse(listener);
                
                auto oldStyleProp = std::make_shared<VObjectProperty>();
                oldStyleProp->setName("PROP");
                oldStyleProp->setValue("");
                oldStyleProp->getParameters()->put("PARAM", "\"value\"");
                auto newStyleProp = std::make_shared<VObjectProperty>();
                newStyleProp->setName("PROP");
                newStyleProp->setValue("");
                newStyleProp->getParameters()->put("PARAM", "value");
                
                
                auto callName = listener->calls.front();
                listener->calls.pop();
                VERIFY_ARE_EQUAL(callName, "onComponentBegin");
                auto name = listener->names.front();
                listener->names.pop();
                VERIFY_ARE_EQUAL("VCALENDAR", name);
                callName = listener->calls.front();
                listener->calls.pop();
                VERIFY_ARE_EQUAL(callName, "onProperty");
                auto property = listener->properties.front();
                listener->properties.pop();
                VERIFY_IS_TRUE(property->equals(oldStyleProp));
                callName = listener->calls.front();
                listener->calls.pop();
                VERIFY_ARE_EQUAL(callName, "onComponentEnd");
                name = listener->names.front();
                listener->names.pop();
                VERIFY_ARE_EQUAL("VCALENDAR", name);
                
                callName = listener->calls.front();
                listener->calls.pop();
                VERIFY_ARE_EQUAL(callName, "onComponentBegin");
                name = listener->names.front();
                listener->names.pop();
                VERIFY_ARE_EQUAL("VCALENDAR", name);
                callName = listener->calls.front();
                listener->calls.pop();
                VERIFY_ARE_EQUAL(callName, "onWarning");
                callName = listener->calls.front();
                listener->calls.pop();
                VERIFY_ARE_EQUAL(callName, "onProperty");
                property = listener->properties.front();
                listener->properties.pop();
                VERIFY_ARE_EQUAL("VERSION" ,property->getName());
                VERIFY_ARE_EQUAL("10" ,property->getValue());
                auto params = property->getParameters();
                VERIFY_IS_TRUE(params->getMap().size() == 0);
                callName = listener->calls.front();
                listener->calls.pop();
                VERIFY_ARE_EQUAL(callName, "onProperty");
                property = listener->properties.front();
                listener->properties.pop();
                property->equals(oldStyleProp);
                callName = listener->calls.front();
                listener->calls.pop();
                VERIFY_ARE_EQUAL(callName, "onComponentEnd");
                name = listener->names.front();
                listener->names.pop();
                VERIFY_ARE_EQUAL("VCALENDAR", name);
                
                callName = listener->calls.front();
                listener->calls.pop();
                VERIFY_ARE_EQUAL(callName, "onComponentBegin");
                name = listener->names.front();
                listener->names.pop();
                VERIFY_ARE_EQUAL("VCALENDAR", name);
                callName = listener->calls.front();
                listener->calls.pop();
                VERIFY_ARE_EQUAL(callName, "onVersion");
                callName = listener->calls.front();
                listener->calls.pop();
                VERIFY_ARE_EQUAL(callName, "onProperty");
                property = listener->properties.front();
                listener->properties.pop();
                property->equals(oldStyleProp);
                callName = listener->calls.front();
                listener->calls.pop();
                VERIFY_ARE_EQUAL(callName, "onComponentEnd");
                name = listener->names.front();
                listener->names.pop();
                VERIFY_ARE_EQUAL("VCALENDAR", name);
                
                callName = listener->calls.front();
                listener->calls.pop();
                VERIFY_ARE_EQUAL(callName, "onComponentBegin");
                name = listener->names.front();
                listener->names.pop();
                VERIFY_ARE_EQUAL("VCALENDAR", name);
                callName = listener->calls.front();
                listener->calls.pop();
                VERIFY_ARE_EQUAL(callName, "onVersion");
                callName = listener->calls.front();
                listener->calls.pop();
                VERIFY_ARE_EQUAL(callName, "onProperty");
                property = listener->properties.front();
                listener->properties.pop();
                property->equals(newStyleProp);
                callName = listener->calls.front();
                listener->calls.pop();
                VERIFY_ARE_EQUAL(callName, "onComponentEnd");
                name = listener->names.front();
                listener->names.pop();
                VERIFY_ARE_EQUAL("VCALENDAR", name);
            }
            
            TEST(vcard_rules) {
                std::string string =
                "BEGIN:VCARD\r\n"
                        "PROP;PARAM=\"value\":\r\n"
                "END:VCARD\r\n"
                "BEGIN:VCARD\r\n"
                        "VERSION:10\r\n"
                        "PROP;PARAM=\"value\":\r\n"
                "END:VCARD\r\n"
                "BEGIN:VCARD\r\n"
                        "VERSION:2.1\r\n"
                        "PROP;PARAM=\"value\":\r\n"
                "END:VCARD\r\n"
                "BEGIN:VCARD\r\n"
                        "VERSION:3.0\r\n"
                        "PROP;PARAM=\"value\":\r\n"
                "END:VCARD\r\n"
                "BEGIN:VCARD\r\n"
                        "VERSION:4.0\r\n"
                        "PROP;PARAM=\"value\":\r\n"
                "END:VCARD";
                
                auto reader = std::make_shared<VObjectReader>(string, SyntaxRules::vcard());
                auto listener = std::make_shared<VObjectDataListenerMock>();
                reader->parse(listener);
                
                auto oldStyleProp = std::make_shared<VObjectProperty>();
                oldStyleProp->setName("PROP");
                oldStyleProp->setValue("");
                oldStyleProp->getParameters()->put("PARAM", "\"value\"");
                auto newStyleProp = std::make_shared<VObjectProperty>();
                newStyleProp->setName("PROP");
                newStyleProp->setValue("");
                newStyleProp->getParameters()->put("PARAM", "value");

                auto callName = listener->calls.front();
                listener->calls.pop();
                VERIFY_ARE_EQUAL(callName, "onComponentBegin");
                auto name = listener->names.front();
                listener->names.pop();
                VERIFY_ARE_EQUAL("VCARD", name);
                callName = listener->calls.front();
                listener->calls.pop();
                VERIFY_ARE_EQUAL(callName, "onProperty");
                auto property = listener->properties.front();
                listener->properties.pop();
                VERIFY_IS_TRUE(property->equals(oldStyleProp));
                callName = listener->calls.front();
                listener->calls.pop();
                VERIFY_ARE_EQUAL(callName, "onComponentEnd");
                name = listener->names.front();
                listener->names.pop();
                VERIFY_ARE_EQUAL("VCARD", name);
                
                callName = listener->calls.front();
                listener->calls.pop();
                VERIFY_ARE_EQUAL(callName, "onComponentBegin");
                name = listener->names.front();
                listener->names.pop();
                VERIFY_ARE_EQUAL("VCARD", name);
                callName = listener->calls.front();
                listener->calls.pop();
                VERIFY_ARE_EQUAL(callName, "onWarning");
                callName = listener->calls.front();
                listener->calls.pop();
                VERIFY_ARE_EQUAL(callName, "onProperty");
                property = listener->properties.front();
                listener->properties.pop();
                VERIFY_ARE_EQUAL("VERSION" ,property->getName());
                VERIFY_ARE_EQUAL("10" ,property->getValue());
                auto params = property->getParameters();
                VERIFY_IS_TRUE(params->getMap().size() == 0);
                callName = listener->calls.front();
                listener->calls.pop();
                VERIFY_ARE_EQUAL(callName, "onProperty");
                property = listener->properties.front();
                listener->properties.pop();
                property->equals(oldStyleProp);
                callName = listener->calls.front();
                listener->calls.pop();
                VERIFY_ARE_EQUAL(callName, "onComponentEnd");
                name = listener->names.front();
                listener->names.pop();
                VERIFY_ARE_EQUAL("VCARD", name);

                callName = listener->calls.front();
                listener->calls.pop();
                VERIFY_ARE_EQUAL(callName, "onComponentBegin");
                name = listener->names.front();
                listener->names.pop();
                VERIFY_ARE_EQUAL("VCARD", name);
                callName = listener->calls.front();
                listener->calls.pop();
                VERIFY_ARE_EQUAL(callName, "onVersion");
                callName = listener->calls.front();
                listener->calls.pop();
                VERIFY_ARE_EQUAL(callName, "onProperty");
                property = listener->properties.front();
                listener->properties.pop();
                property->equals(oldStyleProp);
                callName = listener->calls.front();
                listener->calls.pop();
                VERIFY_ARE_EQUAL(callName, "onComponentEnd");
                name = listener->names.front();
                listener->names.pop();
                VERIFY_ARE_EQUAL("VCARD", name);

                callName = listener->calls.front();
                listener->calls.pop();
                VERIFY_ARE_EQUAL(callName, "onComponentBegin");
                name = listener->names.front();
                listener->names.pop();
                VERIFY_ARE_EQUAL("VCARD", name);
                callName = listener->calls.front();
                listener->calls.pop();
                VERIFY_ARE_EQUAL(callName, "onVersion");
                callName = listener->calls.front();
                listener->calls.pop();
                VERIFY_ARE_EQUAL(callName, "onProperty");
                property = listener->properties.front();
                listener->properties.pop();
                property->equals(newStyleProp);
                callName = listener->calls.front();
                listener->calls.pop();
                VERIFY_ARE_EQUAL(callName, "onComponentEnd");
                name = listener->names.front();
                listener->names.pop();
                VERIFY_ARE_EQUAL("VCARD", name);
                
                callName = listener->calls.front();
                listener->calls.pop();
                VERIFY_ARE_EQUAL(callName, "onComponentBegin");
                name = listener->names.front();
                listener->names.pop();
                VERIFY_ARE_EQUAL("VCARD", name);
                callName = listener->calls.front();
                listener->calls.pop();
                VERIFY_ARE_EQUAL(callName, "onVersion");
                callName = listener->calls.front();
                listener->calls.pop();
                VERIFY_ARE_EQUAL(callName, "onProperty");
                property = listener->properties.front();
                listener->properties.pop();
                property->equals(newStyleProp);
                callName = listener->calls.front();
                listener->calls.pop();
                VERIFY_ARE_EQUAL(callName, "onComponentEnd");
                name = listener->names.front();
                listener->names.pop();
                VERIFY_ARE_EQUAL("VCARD", name);
            }
            
            TEST(pause_parsing) {
                std::string string =
                "BEGIN:COMP1\r\n"
                        "PROP:value\r\n"
                "END:COMP1\r\n"
                "BEGIN:COMP2\r\n"
                        "PROP:value\r\n"
                "END:COMP2\r\n"
                "PROP2:value\r\n"
                "PROP:value";
                
                for (SyntaxStyle style : styles) {
                    class AnotherMock : public VObjectDataListenerMock {
                    public:
                        bool noMoreInteractions = false;
                        void onComponentBegin(const std::string& name, const Context::Ptr & context) {
                            VObjectDataListenerMock::onComponentBegin(name, context);
                            noMoreInteractions = false;
                            if (name == "COMP1") {
                                context->stop();
                                noMoreInteractions = true;
                            }
                        }
                        
                        void onComponentEnd(const std::string& name, const Context::Ptr &context) {
                            VObjectDataListenerMock::onComponentEnd(name, context);
                            noMoreInteractions = false;
                            if (name == ("COMP2")) {
                                context->stop();
                                noMoreInteractions = true;
                            }
                        }
                        
                        void onProperty(const VObjectProperty::Ptr& property, const Context::Ptr &context) {
                            VObjectDataListenerMock::onProperty(property, context);
                            noMoreInteractions = false;
                            if (property->getName() == ("PROP2")) {
                                context->stop();
                                noMoreInteractions = true;
                            }
                        }
                        
                        void onVersion(const std::string& value, const Context::Ptr &context) {
                            VObjectDataListenerMock::onVersion(value, context);
                            noMoreInteractions = false;
                        }
                        
                        void onWarning(Warning::TYPE warning, const VObjectProperty::Ptr& property, std::exception* ex, const Context::Ptr &context) {
                            VObjectDataListenerMock::onWarning(warning, property, ex, context);
                            noMoreInteractions = false;
                        }
                    };
                    
                    auto reader = std::make_shared<VObjectReader>(string, style);
                    auto listener = std::make_shared<AnotherMock>();
                    reader->parse(listener);
                    auto callName = listener->calls.front();
                    listener->calls.pop();
                    VERIFY_ARE_EQUAL(callName, "onComponentBegin");
                    auto name = listener->names.front();
                    listener->names.pop();
                    VERIFY_ARE_EQUAL("COMP1", name);
                    VERIFY_IS_TRUE(listener->noMoreInteractions);
                    
                    reader->parse(listener);
                    callName = listener->calls.front();
                    listener->calls.pop();
                    VERIFY_ARE_EQUAL(callName, "onProperty");
                    auto property = listener->properties.front();
                    listener->properties.pop();
                    VERIFY_ARE_EQUAL("PROP" ,property->getName());
                    VERIFY_ARE_EQUAL("value" ,property->getValue());
                    auto params = property->getParameters();
                    VERIFY_IS_TRUE(params->getMap().size() == 0);
                    callName = listener->calls.front();
                    listener->calls.pop();
                    VERIFY_ARE_EQUAL(callName, "onComponentEnd");
                    name = listener->names.front();
                    listener->names.pop();
                    VERIFY_ARE_EQUAL("COMP1", name);
                    callName = listener->calls.front();
                    listener->calls.pop();
                    VERIFY_ARE_EQUAL(callName, "onComponentBegin");
                    name = listener->names.front();
                    listener->names.pop();
                    VERIFY_ARE_EQUAL("COMP2", name);
                    callName = listener->calls.front();
                    listener->calls.pop();
                    VERIFY_ARE_EQUAL(callName, "onProperty");
                    property = listener->properties.front();
                    listener->properties.pop();
                    VERIFY_ARE_EQUAL("PROP" ,property->getName());
                    VERIFY_ARE_EQUAL("value" ,property->getValue());
                    params = property->getParameters();
                    VERIFY_IS_TRUE(params->getMap().size() == 0);
                    callName = listener->calls.front();
                    listener->calls.pop();
                    VERIFY_ARE_EQUAL(callName, "onComponentEnd");
                    name = listener->names.front();
                    listener->names.pop();
                    VERIFY_ARE_EQUAL("COMP2", name);
                    VERIFY_IS_TRUE(listener->noMoreInteractions);
                    
                    reader->parse(listener);
                    callName = listener->calls.front();
                    listener->calls.pop();
                    VERIFY_ARE_EQUAL(callName, "onProperty");
                    property = listener->properties.front();
                    listener->properties.pop();
                    VERIFY_ARE_EQUAL("PROP2" ,property->getName());
                    VERIFY_ARE_EQUAL("value" ,property->getValue());
                    params = property->getParameters();
                    VERIFY_IS_TRUE(params->getMap().size() == 0);
                    VERIFY_IS_TRUE(listener->noMoreInteractions);
                    
                    reader->parse(listener);
                    callName = listener->calls.front();
                    listener->calls.pop();
                    VERIFY_ARE_EQUAL(callName, "onProperty");
                    property = listener->properties.front();
                    listener->properties.pop();
                    VERIFY_ARE_EQUAL("PROP" ,property->getName());
                    VERIFY_ARE_EQUAL("value" ,property->getValue());
                    params = property->getParameters();
                    VERIFY_IS_TRUE(params->getMap().size() == 0);
                }
            }
        }
    }
}
