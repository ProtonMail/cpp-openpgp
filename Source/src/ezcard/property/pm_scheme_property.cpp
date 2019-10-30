//
//  pm_custom_property.cpp
//  OpenPGP
//
//  Created by Yanfeng Zhang on 6/26/17.
//  Copyright © 2017 Yanfeng Zhang. All rights reserved.
//

#include "pm_scheme_property.hpp"

namespace ProtonMail {

    std::shared_ptr<IPMScheme> IPMScheme::create_instance(const std::string &type, const std::string &value) {
        auto out = std::make_shared<ezvcard::PMScheme>(value);
        out->setType(type);
        return out;
    }
}

namespace ezvcard {
    
    const std::string PMScheme::PROPERTYNAME = "X-PM-SCHEME";
    const std::string PMScheme::CLASSNAME = "PMScheme";
    
    std::string PMScheme::_className() {
        return CLASSNAME;
    }
    std::string PMScheme::_getPropertyName() {
        return PROPERTYNAME;
    }
    
    std::string PMScheme::getAltId() {
        return _parameters->getAltId();
    }
    void PMScheme::setAltId(const std::string& altId) {
        _parameters->setAltId(altId);
    }
}
