//
//  pm_sign_scribe.hpp
//  OpenPGP
//
//  Created by Yanfeng Zhang on 4/4/18.
//  Copyright © 2018 Yanfeng Zhang. All rights reserved.
//

#ifndef pm_sign_scribe_hpp
#define pm_sign_scribe_hpp


#include <stdio.h>
#include "pm_sign_property.hpp"
#include "string_property_scribe.hpp"


namespace ezvcard {
    
    class PMSignScribe : public StringPropertyScribe<PMSign> {
    public:
        PMSignScribe() : StringPropertyScribe(PMSign::PROPERTYNAME) {
            
        }
        
    protected:
        PMSign::Ptr _parseValue(const std::string& value) {
            return std::make_shared<PMSign>(value);
        }
        
        std::string _className() {
            return "PMSignScribe";
        }
        
    };
}

#endif /* pm_sign_scribe_hpp */
