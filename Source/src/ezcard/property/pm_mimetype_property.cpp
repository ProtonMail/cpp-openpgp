//
//  pm_custom_property.cpp
//  OpenPGP
//
//  Created by Yanfeng Zhang on 6/26/17.
//  Copyright © 2017 Yanfeng Zhang. All rights reserved.
//

#include "pm_mimetype_property.hpp"

namespace ProtonMail {

    std::shared_ptr<IPMMimeType> IPMMimeType::create_instance(const std::string &type, const std::string &value) {
        auto out = std::make_shared<ezvcard::PMMimeType>(value);
        out->setType(type);
        return out;
    }
}

namespace ezvcard {
    
    const std::string PMMimeType::PROPERTYNAME = "X-PM-MIMETYPE";
    const std::string PMMimeType::CLASSNAME = "PMScheme";
    
    std::string PMMimeType::_className() {
        return CLASSNAME;
    }
    std::string PMMimeType::_getPropertyName() {
        return PROPERTYNAME;
    }
    
    std::string PMMimeType::getAltId() {
        return _parameters->getAltId();
    }
    void PMMimeType::setAltId(const std::string& altId) {
        _parameters->setAltId(altId);
    }
}
