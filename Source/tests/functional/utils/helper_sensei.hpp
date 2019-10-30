//
//  helper_sensei.hpp
//  OpenPGP
//
//  Created by Yanfeng Zhang on 5/30/17.
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


#ifndef helper_sensei_hpp
#define helper_sensei_hpp

#include <stdio.h>
#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>
#include <list>
#include "utils_test.h"
#include "vcard_property.hpp"
#include "vcard_property_scribe.hpp"
#include "parse_context.hpp"

namespace ezvcard {
    
/**
 * Used for validating the contents of a parsed property object.
 * T is the property class
 */
template <class T>
class Check {
    static_assert(std::is_base_of<VCardProperty, T>::value, "Check<T>: T must be extent of VCardProperty<T> type :-(");

public:
    /**
     * Validates the contents of the parsed property object.
     * @param property the parsed property object
     */
    virtual void check(const std::shared_ptr<T>& property) = 0;
};

template <class T>
class DefaultCheck : public Check<T> {
    static_assert(std::is_base_of<VCardProperty, T>::value, "DefaultCheck<T>: T must be extent of VCardProperty<T> type :-(");
public:
    DefaultCheck(std::shared_ptr<T> p) {
        expected = p;
    }
private:
    std::shared_ptr<T> expected;
    
protected:
    
    void check(const std::shared_ptr<T>& actual) {
        VERIFY_IS_TRUE(expected->equals(actual));
    }
};


/**
 * Parent class for the parser testers.
 */
template <class T>
class ParseTest {
    static_assert(std::is_base_of<VCardProperty, T>::value, "ParseTest<T>: T must be extent of ParseTest<T> type :-(");
    
public:
    
    VCardParameters::Ptr _parameters = nullptr;
    
protected:
    std::list<int> parseWarningCodes;
    
    virtual void run(std::shared_ptr<Check<T>> check, int cannotParseExceptionCode) = 0;
    
public:
    //
    //    @SuppressWarnings("unchecked")
    //    private final U this_ = (U) this;
    //
    //    /**
    //     * Adds an expected parameter.
    //     * @param name the parameter name
    //     * @param value the parameter value
    //     * @return this
    //     */
    //    public U param(String name, String value) {
    //        parameters.put(name, value);
    //        return this_;
    //    }
    //
    //    /**
    //     * Sets the expected parameters.
    //     * @param parameters the parameters
    //     * @return this
    //     */
    //    public U params(VCardParameters parameters) {
    //        this.parameters = parameters;
    //        return this_;
    //    }
    //
    //    /**
    //     * Sets the expected parse warning codes (by default, the scribe is not
    //     * expected to return any parse warnings).
    //     * @param codes the expected parse warning codes (order does not matter)
    //     * @return this
    //     */
    //    public U warnings(Integer... codes) {
    //        parseWarningCodes = codes;
    //        return this_;
    //    }
    //
    //    /**
    //     * Runs the test, without testing the returned property object.
    //     */
    //    void run() {
    //        run(nullptr, -1);
    //    }
    //
    //    /**
    //     * Runs the test.
    //     * @param check object for validating the parsed property object
    //     */
    //    public void run(Check<T> check) {
    //        run(check, -1);
    //    }
    //
    /**
     * Runs the test.
     * @param expected the expected property. Expected and actual property
     * objects will be compared with the {@code equals()} method.
     */
    void run(std::shared_ptr<T> expected) {
        run(std::make_shared<DefaultCheck<T>>(expected), -1);
    }
    
    //    /**
    //     * Runs the test, expecting a {@link CannotParseException} to be thrown.
    //     * @param expectedCode the expected warning code of the exception, or
    //     * null if the exception shouldn't have a warning code
    //     */
    //    public void cannotParse(Integer expectedCode) {
    //        run(null, expectedCode);
    //    }
    //
};


/**
 * Tester class used for testing the {@link VCardPropertyScribe#parseText}
 * method.
 */
template <class T>
class ParseTextTest : public ParseTest<T> {
    static_assert(std::is_base_of<VCardProperty, T>::value, "ParseTextTest<T>: T must be VCardProperty type :-(");
public:
    typedef std::shared_ptr<ParseTextTest<T>> Ptr;
    
    /**
     * @param value the text to parse
     */
    ParseTextTest(const std::string& value, VCardPropertyScribe::Ptr scribe) {
        _value = value;
        _scribe = scribe;
    }
private:
    std::string _value;
    std::vector<VCardVersion::Ptr> _versions = VCardVersion::values();
    VCardDataType::Ptr _dataType = nullptr;
    VCardPropertyScribe::Ptr _scribe;
    
public:
    void dataType(const VCardDataType::Ptr& dataType) {
        _dataType = dataType;
    }
    
    void versions(std::vector<VCardVersion::Ptr> versions) {
        _versions = versions;
    }
    
protected:
    void run(std::shared_ptr<Check<T>> check, int cannotParseExceptionCode) {
        for (auto version : _versions) {
            auto dataType = _dataType;
            if (dataType == nullptr) {
                dataType = _scribe->defaultDataType(version);
            }
            ParseContext context;
            context.setVersion(version);

            try {
                Result::Ptr res = _scribe->parseText(_value, dataType, version, ParseTest<T>::_parameters);
                auto property =std::dynamic_pointer_cast<T>(res->getProperty());
                if (cannotParseExceptionCode >= 0) {
                    std::stringstream ss;
                    ss << "Expected a CannotParseException with code <";
                    ss << cannotParseExceptionCode;
                    ss << "> to be thrown.";
                    throw std::runtime_error(ss.str());
                }
                
                if (check != nullptr) {
                    check->check(property);
                }
                
               // assertParseWarnings(context.getWarnings(), parseWarningCodes);
            } catch (const std::exception& e) {
                if (cannotParseExceptionCode == -1) {
                    /*
                     * Throw the exception to fail the test, since it was
                     * not expected to be thrown.
                     */
                    throw e;
                }
                //TODO::fix later
//                assertEquals("CannotParseException's parse warning code was wrong.", cannotParseExceptionCode, e.getCode());
            }
        }
    }
};



/**
 * Tester class used for testing the {@link VCardPropertyScribe#writeText}
 * method.
 */
template <class T>
class WriteTextTest {
    static_assert(std::is_base_of<VCardProperty, T>::value, "WriteTextTest<T>: T must be VCardProperty type :-(");
public:
    typedef std::shared_ptr<WriteTextTest<T>> Ptr;
protected:
    std::shared_ptr<T> _property;

private:
    std::vector<VCardVersion::Ptr> _versions = VCardVersion::values();
    bool _includeTrailingSemicolons = false;
    VCardPropertyScribe::Ptr _scribe;
    
public:
    WriteTextTest(const std::shared_ptr<T>& property, VCardPropertyScribe::Ptr scribe) {
        _property = property;
        _scribe = scribe;
    }
    
    /**
     * Sets the versions to run this test under (defaults to all versions).
     * @param versions the versions
     */
    void versions(std::vector<VCardVersion::Ptr> versions) {
        _versions = versions;
    }
    
    /**
     * Sets whether to include trailing semicolons for structured property
     * values whose list of values end with null or empty values
     * @param include true to include them, false not to (defaults to false)
     */
    void includeTrailingSemicolons(bool include) {
        _includeTrailingSemicolons = include;
    }
    
//    /**
//     * Runs the test, expecting a {@link SkipMeException} to be thrown.
//     */
//    public void skipMe() {
//        run(SkipMeException.class);
//    }
    
    /**
     * Runs the test.
     * @param expected the expected property value
     */
    void run(const std::string& expected) {
        for (auto version : _versions) {
            auto actual = _scribe->writeText(_property, std::make_shared<WriteContext>(version, TargetApplication::Others, _includeTrailingSemicolons));
            VERIFY_ARE_EQUAL(expected, actual);
        }
    }
//
//    public void run(Class<? extends RuntimeException> expected) {
//        for (VCardVersion version : versions) {
//            try {
//                scribe.writeText(property, new WriteContext(version, null, false));
//                fail("Expected " + expected.getSimpleName());
//            } catch (RuntimeException t) {
//                assertEquals("Expected " + expected.getSimpleName() + ", but was " + t.getClass().getSimpleName(), expected, t.getClass());
//            }
//        }
//    }
};



template <class T>
class Sensei {
    static_assert(std::is_base_of<VCardProperty, T>::value, "Sensei<T>: T must be VCardProperty type :-(");
    
public:
    typedef std::shared_ptr<Sensei<T>> Ptr;
    
    Sensei() {
        
    }
    
    /**
     * Creates a new sensei.
     * @param scribe the property scribe
     */
    Sensei(const VCardPropertyScribe::Ptr& scribe) {
        _scribe = scribe;
    }
    
private:
    VCardPropertyScribe::Ptr _scribe;
    //
    //    /**
    //     * Shorthand for creating a new instance of this class.
    //     * @param scribe the property scribe
    //     * @return the new instance
    //     */
    //    public static <T extends VCardProperty> Sensei<T> create(VCardPropertyScribe<T> scribe) {
    //        return new Sensei<T>(scribe);
    //    }
    
public:
    /**
     * Asserts the {@link VCardPropertyScribe#parseText} method.
     * @param value the value to parse
     * @return the tester object
     */
    std::shared_ptr<ParseTextTest<T>> assertParseText(const std::string& value) {
        return std::make_shared<ParseTextTest<T>>(value, _scribe);
    }
    
    /**
     * Asserts the {@link VCardPropertyScribe#writeText} method.
     * @param property the property to marshal
     * @return the tester object
     */
    std::shared_ptr<WriteTextTest<T>> assertWriteText(std::shared_ptr<T> property) {
        return std::make_shared<WriteTextTest<T>>(property, _scribe);
    }
    
    //    /**
    //     * Asserts the {@link VCardPropertyScribe#parseXml} method.
    //     * @param innerXml the inner XML of the xCal element to parse
    //     * @return the tester object
    //     */
    //    public ParseXmlTest assertParseXml(String innerXml) {
    //        return new ParseXmlTest(innerXml);
    //    }
    //
    //    /**
    //     * Asserts the {@link VCardPropertyScribe#parseHtml} method.
    //     * @param html the HTML element to parse
    //     * @return the tester object
    //     */
    //    public ParseHtmlTest assertParseHtml(String html) {
    //        return new ParseHtmlTest(html);
    //    }
    //
    //    /**
    //     * Asserts the {@link VCardPropertyScribe#parseJson} method.
    //     * @param value the jCal value to parse
    //     * @return the tester object
    //     */
    //    public ParseJsonTest assertParseJson(String value) {
    //        return assertParseJson(JCardValue.single(value));
    //    }
    //
    //    /**
    //     * Asserts the {@link VCardPropertyScribe#parseJson} method.
    //     * @param value the jCal value to parse
    //     * @return the tester object
    //     */
    //    public ParseJsonTest assertParseJson(JCardValue value) {
    //        return new ParseJsonTest(value);
    //    }
    //
    //    /**
    //     * Asserts the {@link VCardPropertyScribe#dataType} method.
    //     * @param property the property to marshal
    //     * @return the tester object
    //     */
    //    public DataTypeTest assertDataType(T property) {
    //        return new DataTypeTest(property);
    //    }
    //
    //    /**
    //     * Asserts the {@link VCardPropertyScribe#prepareParameters} method.
    //     * @param property the property to marshal
    //     * @return the tester object
    //     */
    //    public PrepareParamsTest assertPrepareParams(T property) {
    //        return new PrepareParamsTest(property);
    //    }
    //
    //    /**
    //     * Asserts the {@link VCardPropertyScribe#writeXml} method.
    //     * @param property the property to marshal
    //     * @return the tester object
    //     */
    //    public WriteXmlTest assertWriteXml(T property) {
    //        return new WriteXmlTest(property);
    //    }
    //
    //    /**
    //     * Asserts the {@link VCardPropertyScribe#writeJson} method.
    //     * @param property the property to marshal
    //     * @return the tester object
    //     */
    //    public WriteJsonTest assertWriteJson(T property) {
    //        return new WriteJsonTest(property);
    //    }
    //
    //    /**
    //     * Tester class used for testing the {@link VCardPropertyScribe#dataType}
    //     * method.
    //     */
    //    public class DataTypeTest {
    //        protected final T property;
    //        private VCardVersion version[] = VCardVersion.values();
    //
    //        public DataTypeTest(T property) {
    //            this.property = property;
    //        }
    //
    //        /**
    //         * Sets the versions to run this test under (defaults to all versions).
    //         * @param version the versions
    //         * @return this
    //         */
    //        public DataTypeTest versions(VCardVersion... version) {
    //            this.version = version;
    //            return this;
    //        }
    //
    //        /**
    //         * Runs the test.
    //         * @param expected the expected data type
    //         */
    //        public void run(VCardDataType expected) {
    //            for (VCardVersion version : this.version) {
    //                VCardDataType actual = scribe.dataType(property, version);
    //                assertEquals("Version " + version, expected, actual);
    //            }
    //        }
    //    }
    //
    //    /**
    //     * Tester class used for testing the
    //     * {@link VCardPropertyScribe#prepareParameters} method.
    //     */
    //    public class PrepareParamsTest {
    //        protected final T property;
    //        private VCardVersion versions[] = VCardVersion.values();
    //        private VCard vcard = new VCard();
    //        private VCardParameters expected = new VCardParameters();
    //
    //        public PrepareParamsTest(T property) {
    //            this.property = property;
    //        }
    //
    //        /**
    //         * Sets the versions to run this test under (defaults to all versions).
    //         * @param versions the versions
    //         * @return this
    //         */
    //        public PrepareParamsTest versions(VCardVersion... versions) {
    //            this.versions = versions;
    //            return this;
    //        }
    //
    //        /**
    //         * Sets the {@link VCard} object to use (defaults to an empty vCard).
    //         * @param vcard the vCard
    //         * @return this
    //         */
    //        public PrepareParamsTest vcard(VCard vcard) {
    //            this.vcard = vcard;
    //            return this;
    //        }
    //
    //        /**
    //         * Adds an expected parameter.
    //         * @param name the parameter name
    //         * @param values the parameter value
    //         * @return this
    //         */
    //        public PrepareParamsTest expected(String name, String... values) {
    //            for (String value : values) {
    //                expected.put(name, value);
    //            }
    //            return this;
    //        }
    //
    //        /**
    //         * Runs the test.
    //         */
    //        public void run() {
    //            for (VCardVersion version : versions) {
    //                VCardParameters actual = scribe.prepareParameters(property, version, vcard);
    //                assertEquals("Actual: " + actual, expected.size(), actual.size());
    //
    //                for (Map.Entry<String, List<String>> entry : expected) {
    //                    String expectedKey = entry.getKey();
    //                    List<String> expectedValues = entry.getValue();
    //
    //                    List<String> actualValues = actual.get(expectedKey);
    //                    assertEquals("Actual: " + actual, expectedValues.size(), actualValues.size());
    //                    for (String expectedValue : expectedValues) {
    //                        assertTrue("Actual: " + actual, actualValues.contains(expectedValue));
    //                    }
    //                }
    //            }
    //        }
    //    }
   
    //
    //    /**
    //     * Tester class used for testing the {@link VCardPropertyScribe#writeXml}
    //     * method.
    //     */
    //    public class WriteXmlTest {
    //        protected final T property;
    //
    //        public WriteXmlTest(T property) {
    //            this.property = property;
    //        }
    //
    //        /**
    //         * Runs the test.
    //         * @param expectedInnerXml the expected inner XML of the xCard property
    //         * element
    //         */
    //        public void run(String expectedInnerXml) {
    //            Document actual = createXCardElement();
    //            scribe.writeXml(property, actual.getDocumentElement());
    //
    //            Document expected = createXCardElement(expectedInnerXml);
    //
    //            assertXMLEqual(XmlUtils.toString(actual), expected, actual);
    //        }
    //    }
    //
    //    /**
    //     * Tester class used for testing the {@link VCardPropertyScribe#writeJson}
    //     * method.
    //     */
    //    public class WriteJsonTest {
    //        protected final T property;
    //
    //        public WriteJsonTest(T property) {
    //            this.property = property;
    //        }
    //
    //        /**
    //         * Runs the test.
    //         * @return the marshalled value
    //         */
    //        public JCardValue run() {
    //            return scribe.writeJson(property);
    //        }
    //
    //        /**
    //         * Runs the test.
    //         * @param expected the expected jCard value
    //         */
    //        public void run(JCardValue expected) {
    //            JCardValue value = run();
    //            assertEquals(expected.getValues(), value.getValues());
    //        }
    //
    //        /**
    //         * Runs the test.
    //         * @param expected the expected jCard value
    //         */
    //        public void run(String expected) {
    //            JCardValue value = run();
    //            assertEquals(1, value.getValues().size());
    //            assertEquals(expected, value.getValues().get(0).getValue());
    //        }
    //    }
    //
    //    /**
    //     * Tester class used for testing the {@link VCardPropertyScribe#parseXml}
    //     * method.
    //     */
    //    public class ParseXmlTest extends ParseTest<ParseXmlTest> {
    //        private final String innerXml;
    //
    //        /**
    //         * @param innerXml the inner XML of the xCard property element
    //         */
    //        public ParseXmlTest(String innerXml) {
    //            this.innerXml = innerXml;
    //        }
    //
    //        @Override
    //        protected void run(Check<T> check, Integer cannotParseExceptionCode) {
    //            try {
    //                ParseContext context = new ParseContext();
    //                context.setVersion(VCardVersion.V4_0);
    //                Document document = createXCardElement(innerXml);
    //                Element element = document.getDocumentElement();
    //                T property = scribe.parseXml(element, parameters, context);
    //
    //                if (cannotParseExceptionCode == null || cannotParseExceptionCode >= 0) {
    //                    fail("Expected a CannotParseException with code <" + cannotParseExceptionCode + "> to be thrown.");
    //                }
    //
    //                if (check != null) {
    //                    check.check(property);
    //                }
    //
    //                assertParseWarnings(context.getWarnings(), parseWarningCodes);
    //            } catch (CannotParseException e) {
    //                if (cannotParseExceptionCode == -1) {
    //                    /*
    //                     * Throw the exception to fail the test, since it was not
    //                     * expected to be thrown.
    //                     */
    //                    throw e;
    //                }
    //
    //                assertEquals("CannotParseException's parse warning code was wrong.", cannotParseExceptionCode, e.getCode());
    //            }
    //        }
    //    }
    //
    //    /**
    //     * Tester class used for testing the {@link VCardPropertyScribe#parseHtml}
    //     * method.
    //     */
    //    public class ParseHtmlTest extends ParseTest<ParseHtmlTest> {
    //        private final String html;
    //
    //        /**
    //         * @param html the HTML of the hCard property element
    //         */
    //        public ParseHtmlTest(String html) {
    //            this.html = html;
    //        }
    //
    //        @Override
    //        public ParseHtmlTest param(String name, String value) {
    //            throw new UnsupportedOperationException();
    //        }
    //
    //        @Override
    //        public ParseHtmlTest params(VCardParameters parameters) {
    //            throw new UnsupportedOperationException();
    //        }
    //
    //        @Override
    //        protected void run(Check<T> check, Integer cannotParseExceptionCode) {
    //            try {
    //                ParseContext context = new ParseContext();
    //                context.setVersion(VCardVersion.V3_0);
    //                org.jsoup.nodes.Element element = HtmlUtils.toElement(html);
    //                T property = scribe.parseHtml(new HCardElement(element), context);
    //
    //                if (cannotParseExceptionCode == null || cannotParseExceptionCode >= 0) {
    //                    fail("Expected a CannotParseException with code <" + cannotParseExceptionCode + "> to be thrown.");
    //                }
    //
    //                if (check != null) {
    //                    check.check(property);
    //                }
    //
    //                assertParseWarnings(context.getWarnings(), parseWarningCodes);
    //            } catch (CannotParseException e) {
    //                if (cannotParseExceptionCode == -1) {
    //                    /*
    //                     * Throw the exception to fail the test, since it was not
    //                     * expected to be thrown.
    //                     */
    //                    throw e;
    //                }
    //
    //                assertEquals("CannotParseException's parse warning code was wrong.", cannotParseExceptionCode, e.getCode());
    //            }
    //        }
    //    }
    //
    //    /**
    //     * Tester class used for testing the {@link VCardPropertyScribe#parseJson}
    //     * method.
    //     */
    //    public class ParseJsonTest extends ParseTest<ParseJsonTest> {
    //        private final JCardValue value;
    //        private VCardDataType dataType = scribe.defaultDataType(VCardVersion.V4_0);
    //
    //        /**
    //         * @param value the value
    //         */
    //        public ParseJsonTest(JCardValue value) {
    //            this.value = value;
    //        }
    //        
    //        /**
    //         * Sets the data type (defaults to the property's default data type)
    //         * @param dataType the data type
    //         * @return this
    //         */
    //        public ParseJsonTest dataType(VCardDataType dataType) {
    //            this.dataType = dataType;
    //            return this;
    //        }
    //        
    //        @Override
    //        protected void run(Check<T> check, Integer cannotParseExceptionCode) {
    //            try {
    //                ParseContext context = new ParseContext();
    //                context.setVersion(VCardVersion.V4_0);
    //                T property = scribe.parseJson(value, dataType, parameters, context);
    //                
    //                if (cannotParseExceptionCode == null || cannotParseExceptionCode >= 0) {
    //                    fail("Expected a CannotParseException with code <" + cannotParseExceptionCode + "> to be thrown.");
    //                }
    //                
    //                if (check != null) {
    //                    check.check(property);
    //                }
    //                
    //                assertParseWarnings(context.getWarnings(), parseWarningCodes);
    //            } catch (CannotParseException e) {
    //                if (cannotParseExceptionCode == -1) {
    //                    /*
    //                     * Throw the exception to fail the test, since it was not
    //                     * expected to be thrown.
    //                     */
    //                    throw e;
    //                }
    //                
    //                assertEquals("CannotParseException's parse warning code was wrong.", cannotParseExceptionCode, e.getCode());
    //            }
    //        }
    //    }
    
    //    
    //    private Document createXCardElement() {
    //        return createXCardElement("");
    //    }
    //    
    //    private Document createXCardElement(String innerXml) {
    //        QName qname = scribe.getQName();
    //        String localName = qname.getLocalPart();
    //        String ns = qname.getNamespaceURI();
    //        
    //        try {
    //            return XmlUtils.toDocument("<" + localName + " xmlns=\"" + ns + "\">" + innerXml + "</" + localName + ">");
    //        } catch (SAXException e) {
    //            throw new RuntimeException(e);
    //        }
    //    }
};

}

#endif /* helper_sensei_hpp */
