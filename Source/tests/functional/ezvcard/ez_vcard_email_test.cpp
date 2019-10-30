//
//  ez_vcard_ email_test.cpp
//  OpenPGP
//
//  Created by Yanfeng Zhang on 6/2/17.
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
#include "email.hpp"
#include "email_type.hpp"

using namespace ezvcard;

namespace tests {
    namespace ez_vcard_tests {
        SUITE(ez_vcard_email_test)
        {
            TEST(validate) {
                auto property = std::make_shared<Email>("");
                PropertySensei::assertValidate(property)->run({8});
                property->setValue("johndoe@example.com");
                PropertySensei::assertValidate(property)->run({});

                property->addType(EmailType::AOL);
                property->addType(EmailType::INTERNET);
                property->addType(EmailType::HOME);
                property->addType(EmailType::PREF);
                
                auto validator = PropertySensei::assertValidate(property);
                validator->versions({VCardVersion::V2_1()});
                validator->run({9});
                
                validator = PropertySensei::assertValidate(property);
                validator->versions({VCardVersion::V3_0(), VCardVersion::V4_0()});
                validator->run({9, 9});
            }
        }
    }
}
