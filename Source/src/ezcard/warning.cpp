//
//  warning.cpp
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
