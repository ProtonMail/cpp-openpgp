//
//  ez_vcard_structured_name_test.cpp
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


#include "utils_test.h"

#include <ezvcard/ezvcard.hpp>
#include <ezvcard/vcard.hpp>
#include <ezvcard/io/chain/chaining_text_string_parser.hpp>
#include "helper_property_sensei.hpp"
#include "structured_name.hpp"

using namespace ezvcard;

namespace tests {
    namespace ez_vcard_tests {
        SUITE(ez_vcard_structured_name_test)
        {
            TEST(validate) {
                //zero values
                auto checker = PropertySensei::assertValidate(std::make_shared<StructuredName>());
                checker->versions({});
                checker->run({});
                
                //single values
                std::vector<StructuredName::Ptr> properties;
                {
                    auto property = std::make_shared<StructuredName>();
                    property->getAdditionalNames().push_back("one");
                    properties.push_back(property);
                    
                    property = std::make_shared<StructuredName>();
                    property->getPrefixes().push_back("one");
                    properties.push_back(property);
                    
                    property = std::make_shared<StructuredName>();
                    property->getSuffixes().push_back("one");
                    properties.push_back(property);
                }
                
                for (StructuredName::Ptr property : properties) {
                    PropertySensei::assertValidate(property)->run({});
                }
                
                //multiple values
                properties.clear();
                {
                    auto property = std::make_shared<StructuredName>();
                    property->addAdditionalName("one");
                    property->addAdditionalName("two");
                    properties.push_back(property);
                    
                    property = std::make_shared<StructuredName>();
                    property->addPrefix("one");
                    property->addPrefix("two");
                    properties.push_back(property);
                    
                    property = std::make_shared<StructuredName>();
                    property->addSuffix("one");
                    property->addSuffix("two");
                    properties.push_back(property);
                }
                for (auto property : properties) {
                    auto validate1 = PropertySensei::assertValidate(property);
                    validate1->versions({VCardVersion::V2_1()});
                    validate1->run({34});
                    auto validate2 = PropertySensei::assertValidate(property);
                    validate2->versions({VCardVersion::V3_0(), VCardVersion::V4_0()});
                    validate2->run({});
                }
            }
            
            TEST(copy) {
                auto original = std::make_shared<StructuredName>();
                original->addAdditionalName("one");
                original->addPrefix("two");
                original->addSuffix("three");
                
                auto copy = std::make_shared<StructuredName>(original);

                VERIFY_IS_TRUE(copy.get() != original.get());
                
                auto names = copy->getAdditionalNames();
                VERIFY_IS_TRUE(names.size() == 1);
                VERIFY_IS_TRUE(names[0] == "one");
                
                auto prefixes = copy->getPrefixes();
                VERIFY_IS_TRUE(prefixes.size() == 1);
                VERIFY_IS_TRUE(prefixes[0] == "two");
                
                auto suffixes = copy->getSuffixes();
                VERIFY_IS_TRUE(suffixes.size() == 1);
                VERIFY_IS_TRUE(suffixes[0] == "three");
                
            }
        }
    }
}
