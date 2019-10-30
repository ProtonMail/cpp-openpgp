//
//  birthday.cpp
//  OpenPGP
//
//  Created by Yanfeng Zhang on 1/10/17.
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


#include "birthday.hpp"

namespace ProtonMail {
    
    std::shared_ptr<IBirthday> IBirthday::create_instance(const std::string &type, const std::string &date) {
        auto out = std::make_shared<ezvcard::Birthday>(date);
        out->setType(type);
        return out;
    }
}

namespace ezvcard {
    
    const std::string Birthday::PROPERTYNAME = "BDAY";
    const std::string Birthday::CLASSNAME = "Birthday";
    
    
    std::string Birthday::_className() {
        return Birthday::CLASSNAME;
    }
    
    std::string Birthday::_getPropertyName() {
        return PROPERTYNAME;
    }
    
    std::string Birthday::getAltId() {
        return _parameters->getAltId();
    }
    void Birthday::setAltId(const std::string& altId) {
        return _parameters->setAltId(altId);
    }
    
    
    std::vector<std::string> Birthday::getTypes() {
        return _parameters->getTypes();
    }
    
    std::string Birthday::getType() {
        return _parameters->getType();
    }
    
    
    void Birthday::setType(const std::string& type) {
        _parameters->setType(type);
    }
    
    std::string Birthday::getDate() {
        return DateOrTimeProperty::getDate();
    }
    
    std::string Birthday::getText() {
        return DateOrTimeProperty::getText();
    }
}

//
//
///**
// * Creates a birthday property.
// * @param date the birthday
// */
//public Birthday(Date date) {
//    super(date);
//}
//
///**
// * Creates a birthday property.
// * @param date the birthday
// * @param hasTime true to include the date's time component, false if it's
// * strictly a date
// */
//public Birthday(Date date, boolean hasTime) {
//    super(date, hasTime);
//}
//
///**
// * Creates a birthday property.
// * @param partialDate the birthday (vCard 4.0 only)
// */
//public Birthday(PartialDate partialDate) {
//    super(partialDate);
//}
//
///**
// * Creates a birthday property.
// * @param text the text value (vCard 4.0 only)
// */
//public Birthday(String text) {
//    super(text);
//}
//
///**
// * Copy constructor.
// * @param original the property to make a copy of
// */
//public Birthday(Birthday original) {
//    super(original);
//}
//
//@Override
//public Birthday copy() {
//    return new Birthday(this);
//}
