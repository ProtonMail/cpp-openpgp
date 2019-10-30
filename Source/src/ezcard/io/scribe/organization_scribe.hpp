//
//  organization_scribe.hpp
//  OpenPGP
//
//  Created by Yanfeng Zhang on 6/2/17.
//
//  The MIT License
// 
//  Copyright (c) 2019 Proton Technologies AG
// 
//  Permission is hereby granted, free of charge, to any person obtaining a copy
//  of this software and associated documentation files (the "Software"), to deal
//  in the Software without restriction, including without limitation the rights
//  to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
//  copies of the Software, and to permit persons to whom the Software is
//  furnished to do so, subject to the following conditions:
// 
//  The above copyright notice and this permission notice shall be included in
//  all copies or substantial portions of the Software.
// 
//  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
//  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
//  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
//  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
//  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
//  OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
//  THE SOFTWARE.


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
