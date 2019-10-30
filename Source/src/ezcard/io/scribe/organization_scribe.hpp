//
//  organization_scribe.hpp
//  OpenPGP
//
//  Created by Yanfeng Zhang on 6/2/17.
//  Copyright © 2017 Yanfeng Zhang. All rights reserved.
//

#ifndef organization_scribe_hpp
#define organization_scribe_hpp

#include <stdio.h>

#include "vcard_property_scribe.hpp"
#include "vobject_property_values.hpp"
#include "organization.hpp"
#include <ezvcard/util/string_util.hpp>


namespace ezvcard {
    
    
    /**
     * Marshals {@link Organization} properties.
     * @author Michael Angstadt
     */
    class OrganizationScribe : public VCardPropertyScribeWrapper<Organization> {
    public:
        
        OrganizationScribe() : VCardPropertyScribeWrapper(Organization::PROPERTYNAME) {
            
        }
        
    protected:
        std::string _writeText(const Organization::Ptr& property, const WriteContext::Ptr& context) {
            bool escapeCommas = (context->getVersion() != VCardVersion::V2_1());
            return VObjectPropertyValues::writeSemiStructured(property->getValues(), escapeCommas, context->isIncludeTrailingSemicolons());
        }
        Organization::Ptr _parseText(const std::string& value,
                                     const VCardDataType::Ptr& dataType,
                                     const VCardVersion::Ptr& version,
                                     const VCardParameters::Ptr& parameters,
                                     std::list<std::string> warnings) {
            auto property = std::make_shared<Organization>();
            
            std::vector<std::string> values = VObjectPropertyValues::parseSemiStructured(value);
            property->addValues(values);
            return property;
        }
        
        VCardDataType::Ptr _defaultDataType(const VCardVersion::Ptr& version) {
            return VCardDataType::TEXT;
        }
        
        std::string _className() {
            return "OrganizationScribe";
        }
    };
    
}


#endif /* organization_scribe_hpp */
