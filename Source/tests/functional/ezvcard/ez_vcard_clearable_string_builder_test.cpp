//
//  ez_vcard_clearable_string_builder_test.cpp
//  OpenPGP
//
//  Created by Yanfeng Zhang on 6/3/17.
//  Copyright © 2017 Yanfeng Zhang. All rights reserved.
//

#include "utils_test.h"

#include <ezvcard/ezvcard.hpp>
#include <ezvcard/vcard.hpp>
#include <ezvcard/io/chain/chaining_text_string_parser.hpp>
#include "helper_property_sensei.hpp"
#include "clearable_string_builder.hpp"

using namespace ezvcard;

namespace tests {
    namespace ez_vcard_tests {
        SUITE(ez_vcard_clearable_string_builder_test)
        {
            TEST(get) {
                ClearableStringBuilder sb;
                VERIFY_ARE_EQUAL("", sb.get());
                
                sb.append("foo");
                VERIFY_ARE_EQUAL("foo", sb.get());
                
                /*
                 * Internal buffer should not be modified when get() is called.
                 */
                VERIFY_ARE_EQUAL("foo", sb.get());
            }
            
            TEST(clear) {
                ClearableStringBuilder sb;
                sb.append("foo");
                VERIFY_ARE_EQUAL("foo", sb.get());
                
                sb.clear();
                VERIFY_ARE_EQUAL("", sb.get());
            }
            
            TEST(getAndClear) {
                ClearableStringBuilder sb;
                sb.append("foo");
                VERIFY_ARE_EQUAL("foo", sb.getAndClear());
                VERIFY_ARE_EQUAL("", sb.get());
            }
            
            TEST(append) {
                ClearableStringBuilder sb;
                sb.append('f');
                sb.append("oo");
                sb.append(" bar!", 0, 4);
                VERIFY_ARE_EQUAL("foo bar", sb.get());
            }
            
            TEST(length) {
                ClearableStringBuilder sb;
                VERIFY_ARE_EQUAL(0, sb.length());
                
                sb.append("foo");
                VERIFY_ARE_EQUAL(3, sb.length());
            }
        }
    }
}
