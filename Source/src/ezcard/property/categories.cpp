//
//  categories.cpp
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


#include "categories.hpp"




namespace ProtonMail {
    std::shared_ptr<ICategories> ICategories::create_instance(const std::string & group,
                                                              const std::vector<std::string> & value) {
        auto out = std::make_shared<ezvcard::Categories>();
        out->setGroup(group);
        out->setValues(value);
        return out;
    }
}


namespace ezvcard {
    
    const std::string Categories::PROPERTYNAME = "CATEGORIES";
    const std::string Categories::CLASSNAME = "Categories";
    
    Categories::Categories() : TextListProperty() {
    }
    
    std::string Categories::_className() {
        return CLASSNAME;
    }
    
    std::string Categories::_getPropertyName() {
        return PROPERTYNAME;
    }
    
    std::string Categories::getAltId() {
        return TextListProperty::_parameters->getAltId();
    }
    
    void Categories::setAltId(const std::string& altId) {
        _parameters->setAltId(altId);
    }
    
    std::vector<VCardVersion::Ptr> Categories::_getSupportedVersions() {
        return {VCardVersion::V3_0(), VCardVersion::V4_0() };
    }
    
//    std::string Categories::getType() {
//        return _parameters->getType();
//    }

    
//    void Categories::setType(const std::string& type) {
//        _parameters->setType(type);
//    }
    
    std::vector<std::string> Categories::getValues() {
        return TextListProperty::getValues();
    }
    
    void Categories::addValue(const std::string & text) {
        TextListProperty::addValue(text);
    }
    
    void Categories::setValues(const std::vector<std::string> & values) {
        TextListProperty::setValues(values);
    }
    
    std::string Categories::getGroup() {
        return TextListProperty::getGroup();
    }
    void Categories::setGroup(const std::string & g) {
        TextListProperty::setGroup(g);
    }
    
}
