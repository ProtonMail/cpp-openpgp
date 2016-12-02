//
//  key_scribe.cpp
//  OpenPGP
//
//  Created by Yanfeng Zhang on 4/4/18.
//  Copyright © 2018 Yanfeng Zhang. All rights reserved.
//

#include "key_scribe.hpp"
#include "vcard_property_scribe.hpp"

namespace ezvcard {
    
    KeyScribe::KeyScribe() : BinaryPropertyScribe(Key::PROPERTYNAME) {
        
    }
}
