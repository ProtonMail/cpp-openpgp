//
//  allowed_characters.cpp
//  OpenPGP
//
//  Created by Yanfeng Zhang on 1/13/17.
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

#include "allowed_characters.hpp"

#include <strstream>

const int AllowedCharacters::LENGTH = 128;

AllowedCharacters::AllowedCharacters() {
    for (int i = 0; i < LENGTH; i++) {
        _bitSet.set(0);
    }
}

/**
 * Creates an allowed character list based on the given {@link BitSet}.
 * @param bitSet the bit set
 * @param allowNonAscii true to allow characters outside of the 7-bit ASCII
 * character set (character codes greater than 127), false to only allow
 * 7-bit ASCII
 */
AllowedCharacters::AllowedCharacters(std::bitset<128> bitSet, bool allowNonAscii) {
    _bitSet = bitSet;
    _allowNonAscii = allowNonAscii;
}

////    /**
////     * Gets the underlying {@link BitSet} object.
////     * @return the {@link BitSet} object
////     */
////    public BitSet bitSet() {
////        return bitSet;
////    }
////    
////    /**
////     * Determines if this allowed character list permits characters that are not
////     * part of 7-bit ASCII (character codes greater than 127).
////     * @return true if non-ASCII characters are allowed, false if not
////     */
////    public boolean isNonAsciiAllowed() {
////        return allowNonAscii;
////    }

/**
 * Determines if a string only contains allowed characters.
 * @param string the string
 * @return true if the string only contains allowed characters, false if not
 */
bool AllowedCharacters::check(const std::string& string) {
    for (int i = 0; i < string.length(); i++) {
        int c = string[i];
        if (c >= LENGTH) {
            if (!_allowNonAscii) {
                return false;
            }
            continue;
        }
        
        if (!_bitSet.test(c)) {
            return false;
        }
    }
    return true;
}

/**
 * Returns an allowed character list that is the opposite of this allowed
 * character list (in other words, characters that are NOT allowed).
 * @return the reverse list
 */
AllowedCharacters::Ptr AllowedCharacters::flip() {
    std::bitset<128> bitset(_bitSet);
    bitset.flip(0);
    return std::make_shared<AllowedCharacters>(bitset, !_allowNonAscii);
}

/**
 * Generates a string representation of this allowed character list.
 * Non-printable characters are represented by their character codes.
 * @return the string
 */
std::string AllowedCharacters::toString() {
    return toString(false);
}

/**
 * Generates a string representation of this allowed character list.
 * Non-printable characters are represented by their character codes.
 * @param printableOnly true to only include printable characters in the
 * string, false to include all characters
 * @return the string
 */
std::string AllowedCharacters::toString(bool printableOnly) {
    std::strstream ss;
    ss << "[";
    for (int i = 0; i < LENGTH; i++) {
        if (!_bitSet.test(i)) {
            continue;
        }
        std::string toPrint = "";
        char c = (char) i;
        switch (c) {
            case ' ':
                toPrint = "<space>";
                break;
            case '\r':
                toPrint = "\\r";
                break;
            case '\n':
                toPrint = "\\n";
                break;
            case '\t':
                toPrint = "\\t";
                break;
            default:
                if (i < 32 || i == 127) {
                    if (printableOnly) {
                        continue;
                    }
                    toPrint = "(" + std::to_string(i) + ")";
                }
        }
        ss << " ";
        if (toPrint.empty()) {
            ss << c;
        } else {
            ss << toPrint;
        }
    }
    ss << " ]";
    return ss.str();
}



////    /**
////     * Builder class for creating new instances of {@link AllowedCharacters}.
////     */
////    public static class Builder {
////        private final BitSet bitSet;
////        private boolean allowNonAscii;
////        
////        /**
////         * Creates a new builder.
////         */
////        public Builder() {
////            bitSet = new BitSet(LENGTH);
////            allowNonAscii = false;
////        }
////        
////        /**
////         * Initializes the builder with an existing {@link AllowedCharacters}
////         * object.
////         * @param original the object to copy
////         */
////        public Builder(AllowedCharacters original) {
////            bitSet = (BitSet) original.bitSet.clone();
////            allowNonAscii = original.allowNonAscii;
////        }
////        
////        /**
////         * Allow all characters.
////         * @return this
////         */
////        public Builder allowAll() {
////            bitSet.set(0, LENGTH);
////            allowNonAscii = true;
////            return this;
////        }
////        
////        /**
////         * Allow characters within the given range.
////         * @param from the character to start at
////         * @param to the character to end at (inclusive)
////         * @return this
////         */
////        public Builder allow(int from, int to) {
////            bitSet.set(from, to + 1);
////            return this;
////        }
////        
////        /**
////         * Allow all the characters in the given string.
////         * @param characters the string containing the allowable characters
////         * @return this
////         */
////        public Builder allow(String characters) {
////            setAll(characters, true);
////            return this;
////        }
////        
////        /**
////         * Allow the given character.
////         * @param c the character
////         * @return this
////         */
////        public Builder allow(char c) {
////            bitSet.set(c);
////            return this;
////        }
////        
////        /**
////         * Allows all characters that are considered "printable" (32-126
////         * inclusive). This does NOT include tabs, carriage returns, or line
////         * feeds. This DOES include spaces.
////         * @return this
////         */
////        public Builder allowPrintable() {
////            return allow(32, 126);
////        }
////        
////        /**
////         * Allows all characters outside the range of 7-bit ASCII.
////         * @return this
////         */
////        public Builder allowNonAscii() {
////            allowNonAscii = true;
////            return this;
////        }
////        
////        /**
////         * Reject all the characters in the given string.
////         * @param characters the string containing the illegal characters
////         * @return this
////         */
////        public Builder except(String characters) {
////            setAll(characters, false);
////            return this;
////        }
////        
////        /**
////         * Reject the given character.
////         * @param c the character
////         * @return this
////         */
////        public Builder except(char c) {
////            bitSet.set(c, false);
////            return this;
////        }
////        
////        /**
////         * Constructs the final {@link AllowedCharacters} object.
////         * @return the object
////         */
////        public AllowedCharacters build() {
////            return new AllowedCharacters(bitSet, allowNonAscii);
////        }
////        
////        private void setAll(String characters, boolean value) {
////            for (int i = 0; i < characters.length(); i++) {
////                char c = characters.charAt(i);
////                bitSet.set(c, value);
////            }
////        }
////    }
//};
