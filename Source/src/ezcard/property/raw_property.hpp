//
//  raw_property.hpp
//  OpenPGP
//
//  Created by Yanfeng Zhang on 1/10/17.
//  Copyright © 2017 Yanfeng Zhang. All rights reserved.
//

#ifndef raw_property_hpp
#define raw_property_hpp

#include <stdio.h>
#include "text_property.hpp"
#include "vcard_data_type.hpp"

namespace ezvcard {
    

class RawProperty : public TextProperty {
private:
    std::string _propertyName;
    VCardDataType::Ptr _dataType;

public:
    typedef std::shared_ptr<RawProperty> Ptr;
    
    const static std::string CLASSNAME;
    
    RawProperty(const std::string& propertyName, const std::string& value);
    RawProperty(const std::string& propertyName, const std::string& value, const VCardDataType::Ptr& dataType);
//    public RawProperty(RawProperty original);
    
    
//    public void setPropertyName(String propertyName);
    VCardDataType::Ptr getDataType();
    void setDataType(VCardDataType::Ptr dataType);
//
    
    //override
//    protected void _validate(List<Warning> warnings, VCardVersion version, VCard vcard);
//    protected Map<String, Object> toStringValues();
//    public RawProperty copy();
//    public int hashCode();
//    public boolean equals(Object obj);
    
    
protected:
    std::string _className() {
        return CLASSNAME;
    }
    
    std::string _getPropertyName() {
        return _propertyName;
    }
};

}

#endif /* raw_property_hpp */
