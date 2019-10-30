//
//  ez_vcard_ clearable_stringbuilder_test.cpp
//  OpenPGP
//
//  Created by Yanfeng Zhang on 1/18/17.
//  Copyright © 2017 Yanfeng Zhang. All rights reserved.
//

#include "utils_test.h"

#include <ezvcard/ezvcard.hpp>
#include <ezvcard/vcard.hpp>
#include <ezvcard/io/buffer.hpp>


namespace tests {
    namespace ez_vcard_tests {
        SUITE(ez_vcard_clearable_stringbuilder_test)
        {
            
            TEST(get) {
                auto sb = std::make_shared<Buffer>();
                VERIFY_ARE_EQUAL("", sb->get());
                
                sb->append("foo");
                VERIFY_ARE_EQUAL("foo", sb->get());
                
                /*
                 * Internal buffer should not be modified when get() is called.
                 */
                VERIFY_ARE_EQUAL("foo", sb->get());
            }
            
            TEST(clear) {
                auto sb = std::make_shared<Buffer>();
                sb->append("foo");
                VERIFY_ARE_EQUAL("foo", sb->get());
                
                sb->clear();
                VERIFY_ARE_EQUAL("", sb->get());
            }

            TEST(getAndClear) {
                auto sb = std::make_shared<Buffer>();
                sb->append("foo");
                VERIFY_ARE_EQUAL("foo", sb->getAndClear());
                VERIFY_ARE_EQUAL("", sb->get());
            }
            
            TEST(append) {
                auto sb = std::make_shared<Buffer>();
                sb->append('f');
                sb->append("oo");
                sb->append(" bar!", 0, 4);
                VERIFY_ARE_EQUAL("foo bar", sb->get());
            }
            
            TEST(length) {
                auto  sb = std::make_shared<Buffer>();
                VERIFY_ARE_EQUAL(0, sb->size());
                
                sb->append("foo");
                VERIFY_ARE_EQUAL(3, sb->size());
            }
        }
    }
}
