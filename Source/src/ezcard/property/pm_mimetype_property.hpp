//
//  pm_custom_property.hpp
//  OpenPGP
//
//  Created by Yanfeng Zhang on 6/26/17.
//  Copyright © 2017 Yanfeng Zhang. All rights reserved.
//

#ifndef pm_mimetype_property_hpp
#define pm_mimetype_property_hpp

#include <stdio.h>
#include "text_property.hpp"
#include "has_alt_Id.hpp"
#include "i_p_m_mime_type.hpp"

namespace ezvcard {
    class PMMimeType : public TextProperty, public IPMMimeType, HasAltId {
        
    public:
        typedef std::shared_ptr<PMMimeType> Ptr;
        const static std::string PROPERTYNAME;
        const static std::string CLASSNAME;
        
        PMMimeType(const std::string& custom) : TextProperty(custom) {
            
        }
        
        std::string getType() {
            return _parameters->getType();
        }
        
        void setType(const std::string& type) {
            _parameters->setType(type);
        }
        
        std::string getValue() {
            return TextProperty::getValue();
        }
        
        std::string getGroup() final {
            return TextProperty::getGroup();
        }
        
        void setGroup(const std::string & g) final {
            TextProperty::setGroup(g);
        }
        
    protected: //PMObject
        std::string _className();
        std::string _getPropertyName();
        
    protected: //impl HasAltId
        std::string getAltId();
        void setAltId(const std::string& altId);
    };
}

#endif /* pm_scheme_property_hpp */
