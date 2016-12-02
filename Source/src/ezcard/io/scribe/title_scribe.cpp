//
//  title_scribe.cpp
//  OpenPGP
//
//  Created by Yanfeng Zhang on 6/12/17.
//  Copyright © 2017 Yanfeng Zhang. All rights reserved.
//

#include "title_scribe.hpp"

namespace ezvcard {
    
    TitleScribe::TitleScribe() : StringPropertyScribe(Title::PROPERTYNAME) {

    }
    
    Title::Ptr TitleScribe::_parseValue(const std::string& value) {
        return std::make_shared<Title>(value);
    }
    
}
