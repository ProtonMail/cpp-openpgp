//
//  pm_custom_property.cpp
//  OpenPGP
//
//  Created by Yanfeng Zhang on 6/26/17.
//  Copyright © 2017 Yanfeng Zhang. All rights reserved.
//

#include "pm_encrypt_property.hpp"
#include "i_p_m_encrypt.hpp"

namespace ProtonMail {

    std::shared_ptr<IPMEncrypt> IPMEncrypt::create_instance(const std::string &type, const std::string &value) {
        auto out = std::make_shared<ezvcard::PMEncrypt>(value);
        out->setType(type);
        return out;
    }
}

namespace ezvcard {
    
    const std::string PMEncrypt::PROPERTYNAME = "X-PM-ENCRYPT";
    const std::string PMEncrypt::CLASSNAME = "PMEncrypt";
    
    std::string PMEncrypt::_className() {
        return CLASSNAME;
    }
    std::string PMEncrypt::_getPropertyName() {
        return PROPERTYNAME;
    }
    
    std::string PMEncrypt::getAltId() {
        return _parameters->getAltId();
    }
    void PMEncrypt::setAltId(const std::string& altId) {
        _parameters->setAltId(altId);
    }
}
