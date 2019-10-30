//
//  character_bitset.cpp
//  OpenPGP
//
//  Created by Yanfeng Zhang on 1/18/17.
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


#include "character_bitset.hpp"
#include <iostream>


void CharacterBitSet::setRang(std::bitset<128>& bits, int from, int end) {
    for (int i = from; i < end; i++ )
    {
        bits.set(i);
    }
}

/**
 * @param characters the list of characters to check for. Ranges of
 * characters are represented using a hyphen. Therefore, to include a raw
 * hyphen in the character list, it must come at the very beginning or very
 * end of the given string. In this example, "a-f_:-", the following
 * characters are included in the final character list: lowercase letters a
 * through f, underscores, colons, and hyphens
 */
CharacterBitSet::CharacterBitSet(const std::string& characters) {
    _characters = characters;
    for (int i = 0; i < _characters.size(); i++) {
        char c = _characters[i];
        char next = (i < _characters.size() - 2) ? _characters[i + 1] : 0;
        
        if (next == '-') {
            char start = c;
            char end = _characters[i + 2];
            if (start > end) {
                //swap them
                char temp = start;
                start = end;
                end = temp;
            }
            setRang(_bitSet, start, end + 1);
            i += 2;
            continue;
        }
        _bitSet.set(c);
    }
}

/**
 * Gets the character list that was originally passed into this object.
 * @return the character list
 */
std::string CharacterBitSet::characters() {
    return _characters;
}

/**
 * Gets the underlying {@link BitSet} object.
 * @return the {@link BitSet} object
 */
std::bitset<128> CharacterBitSet::bitSet() {
    return _bitSet;
}

/**
 * Determines if the given string contains *only* the characters in this bit
 * set.
 * @param string the string
 * @return true if the string contains only the specified characters, false
 * if not
 */
bool CharacterBitSet::containsOnly(const std::string& string) {
    return containsOnly(string, 0);
}

/**
 * Determines if the given string contains *only* the characters in this bit
 * set.
 * @param string the string
 * @param startIndex the index to start at in the string
 * @return true if the string contains only the specified characters, false
 * if not
 */
bool CharacterBitSet::containsOnly(const std::string& string, int startIndex) {
    for (int i = startIndex; i < string.length(); i++) {
        char c = string[i];
        if (!_bitSet.test(c)) {
            return false;
        }
    }
    return true;
}

/**
 * Determines if the given string contains at least one of the characters in
 * this bit set.
 * @param string the string
 * @return true if the string contains at least one of the characters, false
 * if not
 */
bool CharacterBitSet::containsAny(const std::string& string) {
    return containsAny(string, 0);
}

/**
 * Determines if the given string contains at least one of the characters in
 * this bit set.
 * @param string the string
 * @param startIndex the index to start at in the string
 * @return true if the string contains at least one of the characters, false
 * if not
 */
bool CharacterBitSet::containsAny(const std::string& string, int startIndex) {
    for (int i = startIndex; i < string.length(); i++) {
        char c = string[i];
        if (_bitSet.test(c)) {
            return true;
        }
    }
    return false;
}

size_t CharacterBitSet::hashCode()  {
    return hash_fn(_bitSet);
}

//    @Override
//    public boolean equals(Object obj) {
//        if (this == obj) return true;
//        if (obj == null) return false;
//        if (getClass() != obj.getClass()) return false;
//        CharacterBitSet other = (CharacterBitSet) obj;
//        return bitSet.equals(other.bitSet);
//    }
//    
//    @Override
//    public String toString() {
//        return characters;
//    }
//}

bool CharacterBitSet::operator==(const CharacterBitSet& rhs) {
    return _bitSet == rhs._bitSet;
}
