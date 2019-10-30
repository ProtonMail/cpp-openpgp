//
//  formatted_name.cpp
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

#include "formatted_name.hpp"




namespace ProtonMail {
    
    std::shared_ptr<IFormattedName> IFormattedName::create_instance(const std::string & name) {
        return std::make_shared<ezvcard::FormattedName>(name);
    }
    

}


namespace ezvcard {


const std::string FormattedName::PROPERTYNAME = "FN";
const std::string FormattedName::CLASSNAME = "FormattedName";

FormattedName::~FormattedName() {
    
}


//FormattedName::FormattedName(const FormattedName* original): TextProperty("") {
//    
//}

/**
 * Creates a formatted name property.
 * @param name the person's name (e.g. "John Doe")
 */
FormattedName::FormattedName(const std::string& name): TextProperty(name) {
    
}

///**
// * Copy constructor.
// * @param original the property to make a copy of
// */
//FormattedName::FormattedName(const FormattedName::Ptr& original) : TextProperty(original) {
//
//}

/**
 * Gets the TYPE parameter.
 * <p>
 * <b>Supported versions:</b> {@code 4.0}
 * </p>
 * @return the TYPE value (typically, this will be either "work" or "home")
 * or null if it doesn't exist
 */
std::string FormattedName::getType() {
    return "";
    //return parameters.getType();
}

/**
 * Sets the TYPE parameter.
 * <p>
 * <b>Supported versions:</b> {@code 4.0}
 * </p>
 * @param type the TYPE value (this should be either "work" or "home") or
 * null to remove
 */
void FormattedName::setType(std::string type) {
    //parameters.setType(type);
}

std::string FormattedName::getLanguage() {
    return "";
    //    return super.getLanguage();
}

void FormattedName::setLanguage(const std::string & language) {
    //super.setLanguage(language);
}


std::list<Pid::Ptr> FormattedName::getPids() {
    return std::list<Pid::Ptr>();
    //return super.getPids();
}

int FormattedName::getPref() {
    return 1;
    //return super.getPref();
}

void FormattedName::setPref(int pref) {
    //super.setPref(pref);
}

std::string FormattedName::getAltId() {
    return _parameters->getAltId();
}

void FormattedName::setAltId(const std::string& altId) {
    _parameters->setAltId(altId);
}

//FormattedName::Ptr FormattedName::copy() {
//    return std::make_shared<FormattedName>(this);
//}

std::string FormattedName::getParameter(const std::string & name) {
    return TextProperty::getParameter(name);
}


std::string FormattedName::getValue() {
    return TextProperty::getValue();
}


}
