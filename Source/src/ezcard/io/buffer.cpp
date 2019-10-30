//
//  buffer.cpp
//  OpenPGP
//
//  Created by Yanfeng Zhang on 12/6/16.
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

#include <ezvcard/io/buffer.hpp>



void Buffer::clear() {
    ss.str("");
}

/**
 * Gets the buffer's contents.
 * @return the buffer's contents
 */
std::string Buffer::get() {
    return ss.str();
}

/**
 * Gets the buffer's contents, then clears it.
 * @return the buffer's contents
 */
std::string Buffer::getAndClear() {
    std::string string = get();
    clear();
    return string;
}

/**
 * Appends a character to the buffer.
 * @param ch the character to append
 * @return this
 */
void Buffer::append(const char& ch) {
    ss << ch;
}

void Buffer::append(const std::string& str) {
    ss << str;
}

void Buffer::append(const std::string& str, int start, int size) {
    auto len = str.length();
    for (auto i = 0; i < size; i++) {
        auto l = start + i;
        if ( l < len) {
            ss << str[l];
        }
    }
}


/**
 * Removes the last character from the buffer (does nothing if the buffer is
 * empty).
 * @return this
 */
void Buffer::chop() {
    if (size() > 0) {
        auto s = ss.str();
        s.pop_back();
        ss.str("");
        ss << s;
    }
}

/**
 * Gets the number of characters in the buffer.
 * @return the buffer's length
 */
size_t Buffer::size() {
    return ss.str().size();
}
