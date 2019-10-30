//
//  gender.cpp
//  OpenPGP
//
//  Created by Yanfeng Zhang on 1/10/17.
//  Copyright © 2017 Yanfeng Zhang. All rights reserved.
//

#include "gender.hpp"


namespace ProtonMail {
    std::shared_ptr<IGender> IGender::create_instance(const std::string & sex, const std::string & text) {
        auto out = std::make_shared<ezvcard::Gender>(sex);
        out->setText(text);
        return out;
    }
}

namespace ezvcard {
    
    const std::string Gender::PROPERTYNAME = "GENDER";
    const std::string Gender::CLASSNAME = "Gender";
}
