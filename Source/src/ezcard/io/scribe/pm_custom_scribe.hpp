//
//  custom_scribe_extended.hpp
//  OpenPGP
//
//  Created by Yanfeng Zhang on 6/26/17.
//  Copyright © 2017 Yanfeng Zhang. All rights reserved.
//

#ifndef pm_custom_scribe_hpp
#define pm_custom_scribe_hpp

#include <stdio.h>
#include "pm_custom_property.hpp"
#include "string_property_scribe.hpp"


namespace ezvcard {
    /**
     * Marshals {@link Note} properties.
     * @author Michael Angstadt
     */
    class PMCustomScribe : public StringPropertyScribe<PMCustom> {
    public:
        PMCustomScribe() : StringPropertyScribe(PMCustom::PROPERTYNAME) {
            
        }
        
    protected:
        PMCustom::Ptr _parseValue(const std::string& value) {
            return std::make_shared<PMCustom>(value);
        }
        
        std::string _className() {
            return "PMCustomScribe";
        }
        
    };
}

#endif /* pm_custom_scribe_hpp */
