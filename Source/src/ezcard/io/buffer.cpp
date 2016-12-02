//
//  buffer.cpp
//  OpenPGP
//
//  Created by Yanfeng Zhang on 12/6/16.
//  Copyright © 2016 Yanfeng Zhang. All rights reserved.
//

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
