//
//  pm_encrypt_scribe.hpp
//  OpenPGP
//
//  Created by Yanfeng Zhang on 4/4/18.
//  Copyright © 2018 Yanfeng Zhang. All rights reserved.
//

#ifndef pm_encrypt_scribe_hpp
#define pm_encrypt_scribe_hpp


#include <stdio.h>
#include "pm_encrypt_property.hpp"
#include "string_property_scribe.hpp"


namespace ezvcard {
    
    class PMEncryptScribe : public StringPropertyScribe<PMEncrypt> {
    public:
        PMEncryptScribe() : StringPropertyScribe(PMEncrypt::PROPERTYNAME) {
            
        }
        
    protected:
        PMEncrypt::Ptr _parseValue(const std::string& value) {
            return std::make_shared<PMEncrypt>(value);
        }
        
        std::string _className() {
            return "PMEncryptScribe";
        }
        
    };
}

#endif /* pm_encrypt_scribe_hpp */
