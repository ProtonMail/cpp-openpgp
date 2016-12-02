//
//  warning.cpp
//  OpenPGP
//
//  Created by Yanfeng Zhang on 12/2/16.
//  Copyright © 2016 Yanfeng Zhang. All rights reserved.
//

#include "warning.hpp"

/**
 * Creates a new warning.
 * @param message the warning message
 * @param code the message code
 */
Warning::Warning(std::string message, int code) {
    _code = code;
    _message = message;
}


Warning::Warning(std::string message) {
    Warning(message, _code);
}

/**
 * Gets the warning code.
 * @return the warning code or null if no code was specified
 */
int Warning::getCode() {
    return _code;
}

/**
 * Gets the warning message
 * @return the warning message
 */
std::string Warning::getMessage() {
    return _message;
}




//    /**
//     * Creates a new warning whose message text is defined in the resource
//     * bundle.
//     * @param code the message code
//     * @param args the message arguments
//     */
//    public Warning(int code, Object... args) {
//        this(Messages.INSTANCE.getValidationWarning(code, args), code);
//    }
//
//    @Override
//    public String toString() {
//        if (code == null) {
//            return message;
//        }
//        return "(" + code + ") " + message;
//    }
//}
