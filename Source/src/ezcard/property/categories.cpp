//
//  categories.cpp
//  OpenPGP
//
//  Created by Yanfeng Zhang on 1/10/17.
//  Copyright © 2017 Yanfeng Zhang. All rights reserved.
//

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
