//
//  ez_vcard_ email_test.cpp
//  OpenPGP
//
//  Created by Yanfeng Zhang on 6/2/17.
//  Copyright © 2017 Yanfeng Zhang. All rights reserved.
//

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
