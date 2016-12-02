//
//  pm_custom_property.cpp
//  OpenPGP
//
//  Created by Yanfeng Zhang on 6/26/17.
//  Copyright © 2017 Yanfeng Zhang. All rights reserved.
//

#include "pm_sign_property.hpp"
#include "i_p_m_sign.hpp"

namespace ProtonMail {
    
    std::shared_ptr<IPMSign> IPMSign::create_instance(const std::string &type, const std::string &value) {
        auto out = std::make_shared<ezvcard::PMSign>(value);
        out->setType(type);
        return out;
    }
}

namespace ezvcard {
    
    const std::string PMSign::PROPERTYNAME = "X-PM-SIGN";
    const std::string PMSign::CLASSNAME = "PMSign";
    
    std::string PMSign::_className() {
        return CLASSNAME;
    }
    std::string PMSign::_getPropertyName() {
        return PROPERTYNAME;
    }
    
    std::string PMSign::getAltId() {
        return _parameters->getAltId();
    }
    void PMSign::setAltId(const std::string& altId) {
        _parameters->setAltId(altId);
    }
}
