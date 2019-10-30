//
//  parse_warnings.cpp
//  OpenPGP
//
//  Created by Yanfeng Zhang on 12/5/16.
//  Copyright © 2016 Yanfeng Zhang. All rights reserved.
//

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
