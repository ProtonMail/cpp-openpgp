//
//  clearable_string_builder.cpp
//  OpenPGP
//
//  Created by Yanfeng Zhang on 1/18/17.
//  Copyright © 2017 Yanfeng Zhang. All rights reserved.
//

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
