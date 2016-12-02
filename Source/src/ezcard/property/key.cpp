//
//  key.cpp
//  OpenPGP
//
//  Created by Yanfeng Zhang on 1/10/17.
//  Copyright © 2017 Yanfeng Zhang. All rights reserved.
//

#include "key.hpp"



namespace ProtonMail {
//    std::shared_ptr<IKey> IKey::create_instance(const std::string & sex, const std::string & text) {
//        auto out = std::make_shared<ezvcard::Key>(sex);
//        out->setText(text);
//        return out;
//    }
}

namespace ezvcard {
    
    const std::string Key::PROPERTYNAME = "KEY";
    const std::string Key::CLASSNAME = "Key";
    

}
