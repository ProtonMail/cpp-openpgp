//
//  string_util.hpp
//  OpenPGP
//
//  Created by Yanfeng Zhang on 12/2/16.
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

#ifndef string_util_hpp
#define string_util_hpp

#include <stdio.h>
#include <string>

#include <algorithm>
#include <cstring>
#include <vector>


/**
 * Trims the whitespace off the left side of a string.
 * @param string the string to trim
 * @return the trimmed string
 */
std::string ltrim(std::string string);

/**
 * Trims the whitespace off the right side of a string.
 * @param string the string to trim
 * @return the trimmed string
 */
std::string rtrim(std::string string);

/**
 * <p>
 * Escapes all newline sequences in a string with "\n".
 * </p>
 * <p>
 * This method is 3x faster than a regex when the string has newlines to
 * escape and 6x faster when it doesn't have newlines to escape.
 * </p>
 * @param string the string
 * @return the escaped string
 */
std::string escapeNewlines(std::string string);

std::string str_to_lower(const std::string &str);
std::string str_to_upper(const std::string &str);
bool startsWith(const std::string& mainStr, const std::string& toMatch);
bool str_equals(const std::string& str1, const std::string& str2);


void replaceAll(std::string &s, const std::string &search, const std::string &replace );


/**
 * Joins a collection of values into a delimited list.
 * @param list the collection of values
 * @param delimiter the delimiter (e.g. ",")
 * @return the delimited string
 */
std::string join(const std::vector<std::string>& list, const std::string& delimiter);

/**
 * Creates a copy of the given map, converting its keys and values to
 * lowercase.
 * @param map the map
 * @return the copy with lowercase keys and values
 */
// Map<String, String> toLowerCase(Map<String, String> map) ;


#endif /* string_util_hpp */
