//
//  validation_warnings.cpp
//  OpenPGP
//
//  Created by Yanfeng Zhang on 12/2/16.
//  Copyright © 2016 Yanfeng Zhang. All rights reserved.
//

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
