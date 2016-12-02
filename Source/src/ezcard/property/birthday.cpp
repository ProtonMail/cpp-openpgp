//
//  birthday.cpp
//  OpenPGP
//
//  Created by Yanfeng Zhang on 1/10/17.
//  Copyright © 2017 Yanfeng Zhang. All rights reserved.
//

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
