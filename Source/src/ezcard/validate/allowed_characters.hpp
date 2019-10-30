//
//  allowed_characters.hpp
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


#ifndef allowed_characters_hpp
#define allowed_characters_hpp

#include <stdio.h>
#include <string>
#include <bitset>

class AllowedCharacters {
    
private:
    static const int LENGTH;// = 128;
    
    
public:
    typedef std::shared_ptr<AllowedCharacters> Ptr;

    std::bitset<128> _bitSet;
    bool _allowNonAscii = false;
    
    AllowedCharacters();
    AllowedCharacters(std::bitset<128> bitSet, bool allowNonAscii);
    
    //
    //    /**
    //     * Gets the underlying {@link BitSet} object.
    //     * @return the {@link BitSet} object
    //     */
    //    public BitSet bitSet() {
    //        return bitSet;
    //    }
    //
    //    /**
    //     * Determines if this allowed character list permits characters that are not
    //     * part of 7-bit ASCII (character codes greater than 127).
    //     * @return true if non-ASCII characters are allowed, false if not
    //     */
    //    public boolean isNonAsciiAllowed() {
    //        return allowNonAscii;
    //    }
    
    bool check(const std::string& string);
    AllowedCharacters::Ptr flip();
    
    std::string toString();
    std::string toString(bool printableOnly);
};

/**
 * Builder class for creating new instances of {@link AllowedCharacters}.
 */
class AllowedCharactersBuilder {
private:
    std::bitset<128> _bitSet;
    bool _allowNonAscii;
    
    
    void setAll(std::string characters, bool value) {
        for (int i = 0; i < characters.length(); i++) {
            char c = characters[i];
            _bitSet.set(c, value);
        }
    }
    
public:
    AllowedCharactersBuilder() {
        _allowNonAscii = false;
    }
    
    AllowedCharactersBuilder(AllowedCharacters::Ptr original) {
        _bitSet = std::bitset<128>(original->_bitSet);
        _allowNonAscii = original->_allowNonAscii;
    }
    
    void allowAll() {
        _bitSet.set();
        _allowNonAscii = true;
    }
    
    void allow(int from, int to) {
        for (int i = from; i <= to; i++) {
            _bitSet.set(i, true);
        }
    }
    
    void allow(std::string characters) {
        setAll(characters, true);
    }
    
    void allow(char c) {
        _bitSet.set(c);
    }
    
    void allowPrintable() {
        allow(32, 126);
    }
    
    void allowNonAscii() {
        _allowNonAscii = true;
    }
    
    void except(std::string characters) {
        setAll(characters, false);
    }
    
    void except(char c) {
        _bitSet.reset(c);
    }
    
    AllowedCharacters::Ptr build() {
        return std::make_shared<AllowedCharacters>(_bitSet, _allowNonAscii);
    }
    
};




#endif /* allowed_characters_hpp */
