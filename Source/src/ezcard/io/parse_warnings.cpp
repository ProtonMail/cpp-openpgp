//
//  parse_warnings.cpp
//  OpenPGP
//
//  Created by Yanfeng Zhang on 12/5/16.
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


#include "parse_warnings.hpp"

//    /**
//     * Adds a parse warning.
//     * @param line the line number or null if unknown
//     * @param propertyName the property name or null if N/A
//     * @param code the message code from the resource bundle
//     * @param args the message arguments
//     */
//    public void add(Integer line, String propertyName, int code, Object... args) {
//        String message = Messages.INSTANCE.getParseMessage(code, args);
//        add(line, propertyName, message);
//    }

/**
 * Adds a parse warning.
 * @param line the line number or null if unknown
 * @param propertyName the property name or null if N/A
 * @param message the warning message
 */
void ParseWarnings::add(int line, std::string propertyName, std::string message) {
    if (line == 0 && propertyName.empty()) {
        _warnings.push_back(message);
        return;
    }
    //TODO:://line need change to file line
    int code;
    if (line == 0 && !propertyName.empty()) {
        code = 35;
    } else if ((line =! 0 && propertyName.empty())) {
        code = 37;
    } else {
        code = 36;
    }
    
    // std::string warning = Messages.INSTANCE.getParseMessage(code, line, propertyName, message);
    _warnings.push_back(message);
}

/**
 * Creates a copy of this warnings list.
 * @return the copy
 */
std::list<std::string>  ParseWarnings::copy() {
    return _warnings;
}

/**
 * Clears the warnings list.
 */
void ParseWarnings::clear() {
    _warnings.clear();
}
