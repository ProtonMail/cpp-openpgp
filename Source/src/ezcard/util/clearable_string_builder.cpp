//
//  clearable_string_builder.cpp
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


#include "clearable_string_builder.hpp"


namespace ezvcard {
    
    /**
     * Clears the buffer.
     * @return this
     */
    void ClearableStringBuilder::clear() {
        ss.str("");
    }
    
    /**
     * Gets the buffer's contents.
     * @return the buffer's contents
     */
    std::string ClearableStringBuilder::get() {
        return ss.str();
    }
    
    /**
     * Gets the buffer's contents, then clears it.
     * @return the buffer's contents
     */
    std::string ClearableStringBuilder::getAndClear() {
        std::string string = get();
        clear();
        return string;
    }
    
    /**
     * Appends a character to the buffer.
     * @param ch the character to append
     * @return this
     */
    void ClearableStringBuilder::append(char ch) {
        ss << ch;
    }
    
    /**
     * Appends a character sequence to the buffer.
     * @param string the character sequence to append
     * @return this
     */
    void ClearableStringBuilder::append(const std::string& str) {
        ss << str;
    }
    
    /**
     * Appends a character array to the buffer.
     * @param buffer the characters to append
     * @param start the index of the first char to append
     * @param length the number of chars to append
     * @return this
     */
    void ClearableStringBuilder::append(const std::string& str, int start, int length) {
        auto len = str.length();
        for (auto i = 0; i < length; i++) {
            auto l = start + i;
            if ( l < len) {
                ss << str[l];
            }
        }
    }
    
    /**
     * Removes the last character from the buffer.
     * @return this
     */
    void ClearableStringBuilder::chop() {
        if (length() > 0) {
            auto s = ss.str();
            s.pop_back();
            ss.str("");
            ss << s;
        }
    }
    
    /**
     * Gets the length of the buffer.
     * @return the buffer's length
     */
    size_t ClearableStringBuilder::length() {
        return ss.str().size();
    }
    
}
