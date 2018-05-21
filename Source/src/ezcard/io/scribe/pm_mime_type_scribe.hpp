//
//  pm_encrypt_scribe.hpp
//  OpenPGP
//
//  Created by Yanfeng Zhang on 4/4/18.
//  Copyright © 2018 Yanfeng Zhang. All rights reserved.
//

#ifndef pm_mime_type_scribe_hpp
#define pm_mime_type_scribe_hpp


#include <stdio.h>
#include "pm_mimetype_property.hpp"
#include "string_property_scribe.hpp"


namespace ezvcard {
    
    class PMMimeTypeScribe : public StringPropertyScribe<PMMimeType> {
    public:
        PMMimeTypeScribe() : StringPropertyScribe(PMMimeType::PROPERTYNAME) {
            
        }
        
    protected:
        PMMimeType::Ptr _parseValue(const std::string& value) {
            return std::make_shared<PMMimeType>(value);
        }
        
        std::string _className() {
            return "PMEncryptScribe";
        }
        
    };
}

#endif /* pm_mime_type_scribe_hpp */
