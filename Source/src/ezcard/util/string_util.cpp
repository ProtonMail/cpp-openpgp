//
//  string_util.cpp
//  OpenPGP
//
//  Created by Yanfeng Zhang on 12/2/16.
//  Copyright © 2016 Yanfeng Zhang. All rights reserved.
//

#include "string_util.hpp"
#include <string>
#include <sstream>
#include <algorithm>



bool charIsWhitespace(char ch) {
    return ch == ' ' || ch == '\t' || ch == '\n';
}


/**
 * Trims the whitespace off the left side of a string.
 * @param string the string to trim
 * @return the trimmed string
 */
std::string ltrim(std::string string) {
    int i;
    size_t size = string.size();
    for (i = 0; i < size && charIsWhitespace(string[i]); i++) {
        //do nothing
    }
    return string.substr(i, size - i);
}

/**
 * Trims the whitespace off the right side of a string.
 * @param string the string to trim
 * @return the trimmed string
 */
std::string rtrim(std::string string) {
    int i;
    int size = (int)string.size();
    for (i = size - 1; (i >= 0 && charIsWhitespace(string[i])); i--) {
        //do nothing
    }
    return string.substr(0, i + 1);
}

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
std::string escapeNewlines(std::string string) {
    std::stringstream ss;
    bool set = false;
    char prev = 0;
    for (int i = 0; i < string.size(); i++) {
        char c = string[i];
        if (c == '\r' || c == '\n') {
            if (set == false) {
                set = true;
                ss << string.substr(0, i);
            }
            
            if (c == '\n' && prev == '\r') {
                /*
                 * Do not write a second newline escape sequence if the
                 * newline sequence is "\r\n".
                 */
            } else {
                ss << "\\n";
            }
        } else if (set) {
            ss << c;
        }
        
        prev = c;
    }
    return (set) ? ss.str() : string;
}


std::string str_to_lower(const std::string &str)
{
    std::string retVal;
    retVal.resize(str.size());
    std::transform(str.begin(), str.end(), retVal.begin(), ::tolower);
    return retVal;
}

std::string str_to_upper(const std::string &str)
{
    std::string retVal;
    retVal.resize(str.size());
    std::transform(str.begin(), str.end(), retVal.begin(), ::toupper);
    return retVal;
}

bool startsWith(const std::string& mainStr, const std::string& toMatch)
{
    // std::string::find returns 0 if toMatch is found at starting
    if(mainStr.find(toMatch) == 0)
        return true;
    else
        return false;
}

void replaceAll(std::string &s, const std::string &search, const std::string &replace ) {
    for( size_t pos = 0; ; pos += replace.length() ) {
        // Locate the substring to replace
        pos = s.find( search, pos );
        if( pos == std::string::npos ) break;
        // Replace by erasing and inserting
        s.erase( pos, search.length() );
        s.insert( pos, replace );
    }
}

/**
 * Joins a collection of values into a delimited list.
 * @param collection the collection of values
 * @param delimiter the delimiter (e.g. ",")
 * @return the delimited string
 */
std::string join(const std::vector<std::string>& list, const std::string& delimiter) {
    std::stringstream ss("");
    
    bool first = true;
    for (const auto& value : list) {
        if (!first) {
            ss << delimiter;
        }
        ss << value;
        first = false;
    }
    
    return ss.str();
}

///**
// * Creates a copy of the given map, converting its keys and values to
// * lowercase.
// * @param map the map
// * @return the copy with lowercase keys and values
// */
//public static Map<String, String> toLowerCase(Map<String, String> map) {
//    Map<String, String> lowerCaseMap = new HashMap<String, String>(map.size());
//    for (Map.Entry<String, String> entry : map.entrySet()) {
//        String key = entry.getKey();
//        key = (key == null) ? null : key.toLowerCase();
//        
//        String value = entry.getValue();
//        value = (value == null) ? null : value.toLowerCase();
//        
//        lowerCaseMap.put(key, value);
//    }
//    return lowerCaseMap;
//}




struct iequal
{
    bool operator()(int c1, int c2) const
    {
        return std::toupper(c1) == std::toupper(c2);
    }
};

bool str_equals(const std::string& str1, const std::string& str2)
{
    return std::equal(str1.begin(), str1.end(), str2.begin(), iequal());
}
