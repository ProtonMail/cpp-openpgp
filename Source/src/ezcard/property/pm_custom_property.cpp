//
//  pm_custom_property.cpp
//  OpenPGP
//
//  Created by Yanfeng Zhang on 6/26/17.
//  Copyright © 2017 Yanfeng Zhang. All rights reserved.
//

#include "pm_custom_property.hpp"

namespace ProtonMail {
    
    std::shared_ptr<IPMCustom> IPMCustom::create_instance(const std::string &type, const std::string &value) {
        auto out = std::make_shared<ezvcard::PMCustom>(value);
        out->setType(type);
        return out;
    }
}

namespace ezvcard {
    
    const std::string PMCustom::PROPERTYNAME = "CUSTOM";
    const std::string PMCustom::CLASSNAME = "PMCustom";
    
    std::string PMCustom::_className() {
        return CLASSNAME;
    }
    std::string PMCustom::_getPropertyName() {
        return PROPERTYNAME;
    }
    
    std::string PMCustom::getAltId() {
        return _parameters->getAltId();
    }
    void PMCustom::setAltId(const std::string& altId) {
        _parameters->setAltId(altId);
    }
}
