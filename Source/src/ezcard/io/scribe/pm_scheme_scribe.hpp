//
//  pm_encrypt_scribe.hpp
//  OpenPGP
//
//  Created by Yanfeng Zhang on 4/4/18.
//  Copyright © 2018 Yanfeng Zhang. All rights reserved.
//

#ifndef pm_scheme_scribe_hpp
#define pm_scheme_scribe_hpp


#include <stdio.h>
#include "pm_scheme_property.hpp"
#include "string_property_scribe.hpp"


namespace ezvcard {
    
    class PMSchemeScribe : public StringPropertyScribe<PMScheme> {
    public:
        PMSchemeScribe() : StringPropertyScribe(PMScheme::PROPERTYNAME) {
            
        }
        
    protected:
        PMScheme::Ptr _parseValue(const std::string& value) {
            return std::make_shared<PMScheme>(value);
        }
        
        std::string _className() {
            return "PMEncryptScribe";
        }
        
    };
}

#endif /* pm_scheme_scribe_hpp */
