//
//  ez_vcard_character_bitset_test.cpp
//  OpenPGP
//
//  Created by Yanfeng Zhang on 6/4/17.
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

#include <iostream>
#include <bitset>
#include <functional>

#include <ezvcard/ezvcard.hpp>
#include <ezvcard/vcard.hpp>
#include <ezvcard/io/chain/chaining_text_string_parser.hpp>
#include "character_bitset.hpp"



using namespace ezvcard;

namespace tests {
    namespace ez_vcard_tests {
        SUITE(ez_vcard_character_bitset_test)
        {
            TEST(expandCharacterList) {
                auto actual = CharacterBitSet("abc123").bitSet();
                std::bitset<128> expected;
                CharacterBitSet::setRang(expected, 'a', 'd');
                CharacterBitSet::setRang(expected, '1', '4');
                VERIFY_ARE_EQUAL(expected, actual);
                
                actual = CharacterBitSet("a-f").bitSet();
                expected = std::bitset<128>();
                CharacterBitSet::setRang(expected, 'a', 'g');
                VERIFY_ARE_EQUAL(expected, actual);
                
                actual = CharacterBitSet("a-fa-f").bitSet();
                expected.reset();
                CharacterBitSet::setRang(expected, 'a', 'g');
                VERIFY_ARE_EQUAL(expected, actual);
                
                actual = CharacterBitSet("f-a").bitSet();
                expected.reset();
                CharacterBitSet::setRang(expected, 'a', 'g');
                VERIFY_ARE_EQUAL(expected, actual);
                
                actual = CharacterBitSet("a-fz").bitSet();
                expected.reset();
                CharacterBitSet::setRang(expected, 'a', 'g');
                expected.set('z');
                VERIFY_ARE_EQUAL(expected, actual);
                
                actual = CharacterBitSet("-a-f").bitSet();
                expected.reset();
                CharacterBitSet::setRang(expected, 'a', 'g');
                expected.set('-');
                VERIFY_ARE_EQUAL(expected, actual);
                
                actual = CharacterBitSet("a-f-").bitSet();
                expected.reset();
                CharacterBitSet::setRang(expected, 'a', 'g');
                expected.set('-');
                VERIFY_ARE_EQUAL(expected, actual);
                
                actual = CharacterBitSet("-a-f0-9xyz*").bitSet();
                expected.reset();
                CharacterBitSet::setRang(expected, 'a', 'g');
                expected.set('-');
                CharacterBitSet::setRang(expected, '0', '9' + 1);
                expected.set('x');
                expected.set('y');
                expected.set('z');
                expected.set('*');
                VERIFY_ARE_EQUAL(expected, actual);
                
                actual = CharacterBitSet("").bitSet();
                expected.reset();
                VERIFY_ARE_EQUAL(expected, actual);
            }
            
            TEST(characters) {
                CharacterBitSet bitSet("a-z");
                VERIFY_ARE_EQUAL("a-z", bitSet.characters());
            }
            
            TEST(containsOnly_empty) {
                CharacterBitSet bitSet("");
                VERIFY_IS_FALSE(bitSet.containsOnly("anything"));
                VERIFY_IS_TRUE(bitSet.containsOnly(""));
            }
            
            TEST(containsOnly) {
                CharacterBitSet bitSet("b-f0-9");
                VERIFY_IS_TRUE(bitSet.containsOnly("bf3"));
                VERIFY_IS_FALSE(bitSet.containsOnly("af3"));
                VERIFY_IS_TRUE(bitSet.containsOnly("bf3", 1));
                VERIFY_IS_TRUE(bitSet.containsOnly("af3", 1));
                VERIFY_IS_TRUE(bitSet.containsOnly(""));
            }
            
            TEST(containsAny_empty) {
                CharacterBitSet bitSet("");
                VERIFY_IS_FALSE(bitSet.containsAny("anything"));
                VERIFY_IS_FALSE(bitSet.containsAny(""));
            }
            
            TEST(containsAny) {
                CharacterBitSet bitSet("b-f0-9");
                VERIFY_IS_TRUE(bitSet.containsAny("bxx"));
                VERIFY_IS_FALSE(bitSet.containsAny("aaa"));
                VERIFY_IS_FALSE(bitSet.containsAny("bxx", 1));
                VERIFY_IS_FALSE(bitSet.containsAny(""));
            }
            
            TEST(equals_contract) {
                CharacterBitSet one("b-f0-9");
                CharacterBitSet two("0-9f-b");
                VERIFY_IS_TRUE( one.hashCode() == two.hashCode());
                
                one = CharacterBitSet("b-f0-9");
                two = CharacterBitSet("bcfed9786452310");
                VERIFY_IS_TRUE( one.hashCode() == two.hashCode());
                
                one = CharacterBitSet("a-f0-9");
                two = CharacterBitSet("0-9f-b");
                VERIFY_IS_FALSE(one == two);
                VERIFY_IS_FALSE(two == one);
            }
        }
    }
}
