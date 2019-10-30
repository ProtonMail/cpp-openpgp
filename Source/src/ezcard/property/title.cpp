//
//  title.cpp
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


#include "title.hpp"


namespace ProtonMail {
    
    std::shared_ptr<ITitle> ITitle::create_instance(const std::string &type, const std::string &value) {
        auto out = std::make_shared<ezvcard::Title>(value);
        out->setType(type);
        return out;
    }
}

namespace ezvcard {
    const std::string Title::PROPERTYNAME = "TITLE";
    const std::string Title::CLASSNAME = "Title";

    /**
     * Creates a title property.
     * @param title the title (e.g. "Team Lead")
     */
    Title::Title(const std::string& title) : TextProperty(title) {
        
    }
//
///**
// * Copy constructor.
// * @param original the property to make a copy of
// */
//public Title(Title original) {
//    super(original);
//}
//
//@Override
//public String getLanguage() {
//    return super.getLanguage();
//}
//
//@Override
//public void setLanguage(String language) {
//    super.setLanguage(language);
//}
    
    /**
     * Gets the TYPE parameter.
     * <p>
     * <b>Supported versions:</b> {@code 4.0}
     * </p>
     * @return the TYPE value (typically, this will be either "work" or "home")
     * or null if it doesn't exist
     */
    std::string Title::getType() {
        return _parameters->getType();
    }
    
    void Title::setType(const std::string& type) {
        _parameters->setType(type);
    }
    
    std::string Title::getTitle() {
        return TextProperty::getValue();
    }
    
///**
// * Sets the TYPE parameter.
// * <p>
// * <b>Supported versions:</b> {@code 4.0}
// * </p>
// * @param type the TYPE value (this should be either "work" or "home") or
// * null to remove
// */
//public void setType(String type) {
//    parameters.setType(type);
//}
//
//@Override
//public List<Pid> getPids() {
//    return super.getPids();
//}
//
//@Override
//public Integer getPref() {
//    return super.getPref();
//}
//
//@Override
//public void setPref(Integer pref) {
//    super.setPref(pref);
//}
//
////@Override
//public String getAltId() {
//    return parameters.getAltId();
//}
//
////@Override
//public void setAltId(String altId) {
//    parameters.setAltId(altId);
//}
//
//@Override
//public Title copy() {
//    return new Title(this);
//}
//        //@Override
//        public String getAltId() {
//            return parameters.getAltId();
//        }
//
//        //@Override
//        public void setAltId(String altId) {
//            parameters.setAltId(altId);
//        }
    
    
    std::string Title::_className() {
        return CLASSNAME;
    }
    std::string Title::_getPropertyName() {
        return PROPERTYNAME;
    }
    
    std::string Title::getAltId() {
        return _parameters->getAltId();
    }
    void Title::setAltId(const std::string& altId) {
        _parameters->setAltId(altId);
    }
}
