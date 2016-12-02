//
//  uid.cpp
//  OpenPGP
//
//  Created by Yanfeng Zhang on 1/10/17.
//  Copyright © 2017 Yanfeng Zhang. All rights reserved.
//

#include "uid.hpp"



namespace ProtonMail {
    
    std::shared_ptr<IUid> IUid::create_instance(const std::string & uuid) {
        return std::make_shared<ezvcard::Uid>(uuid);
    }
}

namespace ezvcard {
    
    const std::string Uid::PROPERTYNAME = "UID";
    const std::string Uid::CLASSNAME = "Uid";
    
    
    std::string Uid::getAltId() {
        return _parameters->getAltId();
    }
    
    void Uid::setAltId(const std::string& altId) {
        _parameters->setAltId(altId);
    }
    
    std::string Uid::getValue() {
        return UriProperty::getValue();
    }
    
    
    
}
