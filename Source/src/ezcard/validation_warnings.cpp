//
//  validation_warnings.cpp
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


#include "validation_warnings.hpp"
#include <strstream>

/**
 * Creates a new validation warning.
 * @param message the warning message
 */
ValidationWarning:: ValidationWarning(std::string message) {
    _code = 0;
    _message = message;
}


ValidationWarning::ValidationWarning(int code, std::string message) {
    _code = code;
    _message = message;
}

///**
// * Creates a new validation warning.
// * @param code the warning message code
// * @param args the warning message arguments
// */
//public ValidationWarning(int code, std::) {
//    this.code = code;
//    this.message = Messages.INSTANCE.getValidationWarning(code, args);
//}

    /**
     * Gets the validation warning code.
     * @return the warning code or null if no code was specified
     */
 int ValidationWarning::getCode() {
        return _code;
    }
    
    /**
     * Gets the validation warning message
     * @return the warning message
     */
std::string ValidationWarning::getMessage() {
    return _message;
}

std::string ValidationWarning::toString() {
    std::strstream ss;
    if (_code == 0) {
        return _message;
    }
    ss << "(";
    ss << _code;
    ss << ") ";
    ss << _message;
    return ss.str();
}

bool ValidationWarning::operator==(const int& rhs) {
    return  true;
}
bool operator==(const ValidationWarning::Ptr& lhs, const ValidationWarning::Ptr& rhs) {
    return true;
}

bool operator==(const ValidationWarning::Ptr& lhs, const int& rhs) {
    return true;
}
