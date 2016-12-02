//
//  organization.cpp
//  OpenPGP
//
//  Created by Yanfeng Zhang on 1/10/17.
//  Copyright © 2017 Yanfeng Zhang. All rights reserved.
//

#include "organization.hpp"

namespace ProtonMail {
    
    std::shared_ptr<IOrganization> IOrganization::create_instance(const std::string &type, const std::string &value) {
        auto out = std::make_shared<ezvcard::Organization>();
        out->addValue(value);
        out->setType(type);
        return out;
    }
}

namespace ezvcard {
    
    const std::string Organization::PROPERTYNAME = "ORG";
    const std::string Organization::CLASSNAME = "Organization";
    
    
    std::string Organization::getAltId() {
        return _parameters->getAltId();
    }
    
    void Organization::setAltId(const std::string& altId) {
        _parameters->setAltId(altId);
    }
    
    std::vector<std::string> Organization::getValues() {
        return TextListProperty::getValues();
    }
}
