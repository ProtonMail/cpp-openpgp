//
//  simple_property.hpp
//  OpenPGP
//
//  Created by Yanfeng Zhang on 1/10/17.
//  Copyright © 2017 Yanfeng Zhang. All rights reserved.
//

#ifndef simple_property_hpp
#define simple_property_hpp

#include <stdio.h>
#include "vcard_property.hpp"

namespace ezvcard {
    

template <typename T>
class SimpleProperty : public VCardProperty {
protected:
    T _value;
    
    
public:
    typedef std::shared_ptr<SimpleProperty> Ptr;
    SimpleProperty(T value) {
        _value = value;
    }
    
//    SimpleProperty(const SimpleProperty<T>::Ptr& original) {
//        
//    }
    
    /**
     * Gets the value of this property.
     * @return the value or null if not set
     */
    T getValue() {
        return _value;
    }
    
    /**
     * Sets the value of this property.
     * @param value the value
     */
    void setValue(T value) {
        _value = value;
    }
    
    
protected:
    void _validate(std::list<ValidationWarning::Ptr>& warnings, const VCardVersion::Ptr& version, const std::shared_ptr<VCard>& vcard) {
        if (_value == T()) {
            warnings.push_back(std::make_shared<ValidationWarning>(8));
        }
    }
//
//    @Override
//    protected Map<String, Object> toStringValues() {
//        Map<String, Object> values = new LinkedHashMap<String, Object>();
//        values.put("value", value);
//        return values;
//    }
//    
//    @Override
//    public int hashCode() {
//        final int prime = 31;
//        int result = super.hashCode();
//        result = prime * result + ((value == null) ? 0 : value.hashCode());
//        return result;
//    }
//    
//    @Override
//    public boolean equals(Object obj) {
//        if (this == obj) return true;
//        if (!super.equals(obj)) return false;
//        SimpleProperty<?> other = (SimpleProperty<?>) obj;
//        if (value == null) {
//            if (other.value != null) return false;
//        } else if (!value.equals(other.value)) return false;
//        return true;
//    }
};
    
}

#endif /* simple_property_hpp */
