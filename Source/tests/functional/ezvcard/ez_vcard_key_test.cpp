//
//  ez_vcard_key_test.cpp
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
#include "key.hpp"
#include "key_type.hpp"
#include "base64.h"
#include <exception>
#include "vcard_version.hpp"

using namespace ezvcard;

namespace tests {
    namespace ez_vcard_tests {
        SUITE(ez_vcard_key_test)
        {
            TEST(constructors) {
                Key::Ptr property = std::make_shared<Key>();
                VERIFY_IS_NULL(property->getContentType());
                VERIFY_IS_TRUE(property->getUrl() == "");
                VERIFY_IS_TRUE(property->getData() == "");
                VERIFY_IS_TRUE(property->getText() == "");
                
                property = std::make_shared<Key>("data", KeyType::GPG, true);
                VERIFY_IS_TRUE( KeyType::GPG == property->getContentType());
                VERIFY_ARE_EQUAL(property->getUrl(), "");
                VERIFY_ARE_EQUAL(property->getData(), "data");
                VERIFY_ARE_EQUAL(property->getText(), "");
                
                property = std::make_shared<Key>("one", KeyType::GPG, false);
                VERIFY_IS_TRUE( KeyType::GPG == property->getContentType());
                VERIFY_ARE_EQUAL("one", property->getUrl());
                VERIFY_ARE_EQUAL(property->getData(), "");
                VERIFY_ARE_EQUAL(property->getText(), "");
                
//                File file = new File("pom.xml");
//                property = new Key(file, KeyType.GPG);
//                assertEquals(KeyType.GPG, property.getContentType());
//                assertNull(property.getUrl());
//                assertEquals(file.length(), property.getData().length);
//                assertNull(property.getText());
//
//                InputStream in = new ByteArrayInputStream("data".getBytes());
//                property = new Key(in, KeyType.GPG);
//                assertEquals(KeyType.GPG, property.getContentType());
//                assertNull(property.getUrl());
//                assertArrayEquals("data".getBytes(), property.getData());
//                assertNull(property.getText());
            }
            
            TEST(set_value) {
                Key::Ptr property = std::make_shared<Key>("url", KeyType::PGP, false);
                VERIFY_ARE_EQUAL("url", property->getUrl());
                VERIFY_ARE_EQUAL(property->getData(), "");
                VERIFY_ARE_EQUAL(KeyType::PGP, property->getContentType());
                VERIFY_ARE_EQUAL(property->getText(), "");

                property->setText("text", KeyType::GPG);
                VERIFY_ARE_EQUAL(property->getUrl(), "");
                VERIFY_ARE_EQUAL(property->getData(), "");
                VERIFY_ARE_EQUAL(KeyType::GPG, property->getContentType());
                VERIFY_ARE_EQUAL("text", property->getText());

                property->setUrl("url", KeyType::PGP);
                VERIFY_ARE_EQUAL("url", property->getUrl());
                VERIFY_ARE_EQUAL(property->getData(), "");
                VERIFY_ARE_EQUAL(KeyType::PGP, property->getContentType());
                VERIFY_ARE_EQUAL(property->getText(), "");

                property->setText("text", KeyType::GPG);
                property->setData("data", KeyType::PGP);
                VERIFY_ARE_EQUAL(property->getUrl(), "");
                VERIFY_ARE_EQUAL("data", property->getData());
                VERIFY_ARE_EQUAL(KeyType::PGP, property->getContentType());
                VERIFY_ARE_EQUAL(property->getText(), "");
            }
            
            TEST(validate) {
                Key::Ptr empty = std::make_shared<Key>();
                ezvcard::PropertySensei::assertValidate(empty)->run({8});

                Key::Ptr withUrl = std::make_shared<Key>("http://example.com", KeyType::PGP, false);
                auto test1 = ezvcard::PropertySensei::assertValidate(withUrl);
                test1->versions({VCardVersion::V2_1(), VCardVersion::V3_0()});
                test1->run({15});
                auto test2 = ezvcard::PropertySensei::assertValidate(withUrl);
                test2->versions({VCardVersion::V4_0()});
                test2->run({});

                Key::Ptr withText = std::make_shared<Key>("", KeyType::PGP, false);
                withText->setText("abc123", KeyType::PGP);
                ezvcard::PropertySensei::assertValidate(withText)->run({});
            }
//            
//           TEST(toStringValues) {
//                Key::Ptr property = std::make_shared<Key>();
//                assertFalse(property.toStringValues().isEmpty());
//            }
//            
            TEST(copy) {
//                Key original = new Key();
//                assertCopy(original);
//
//                original = new Key();
//                original.setText("text", KeyType.GPG);
//                assertCopy(original);
            }
            
            TEST(equals) {
//                List<VCardProperty> properties = new ArrayList<VCardProperty>();
//
//                Key property = new Key();
//                properties.add(property);
//
//                property = new Key();
//                property.setText("text", KeyType.GPG);
//                properties.add(property);
//
//                property = new Key();
//                property.setText("text2", KeyType.GPG);
//                properties.add(property);
//
//                property = new Key();
//                property.setText("text", KeyType.PGP);
//                properties.add(property);
//
//                property = new Key();
//                property.setText("text", null);
//                properties.add(property);
//
//                assertNothingIsEqual(properties);
//
//                //@formatter:off
//                assertEqualsMethod(Key.class)
//                .constructor()
//                .test()
//                .method("setText", "text", KeyType.GPG).test();
//                //@formatter:on
            }
        }
    }
}

