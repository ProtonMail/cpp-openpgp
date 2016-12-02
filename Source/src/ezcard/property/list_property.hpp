//
//  list_property.hpp
//  OpenPGP
//
//  Created by Yanfeng Zhang on 1/10/17.
//  Copyright © 2017 Yanfeng Zhang. All rights reserved.
//

#ifndef list_property_hpp
#define list_property_hpp

#include <stdio.h>
#include "vcard_property.hpp"
#include <string>
#include <vector>


namespace ezvcard {
    
/**
 * Represents a property whose value is a list of textual values.
 * @author Michael Angstadt
 */
template <typename T>
class ListProperty : public VCardProperty {
protected:
    std::vector<T> _values;
    
    ListProperty() {
    }
    
    //    /**
    //     * Copy constructor.
    //     * @param original the property to make a copy of
    //     */
    //    public ListProperty(ListProperty<T> original) {
    //        super(original);
    //        values = new original.getVlaues
    //    }
    
    /**
     * Gets the list that stores this property's values.
     * @return the list of values (this list is mutable)
     */
public:
    std::vector<T> getValues() {
        return _values;
    }
    
    void addValues(std::vector<T> values) {
        for (auto v : values) {
            _values.push_back(v);
        }
    }
    
    void addValue(T value) {
        _values.push_back(value);
    }
    
protected:
    void _validate(std::list<ValidationWarning::Ptr>& warnings, const VCardVersion::Ptr& version, const std::shared_ptr<VCard>& vcard) {
        if (_values.size() == 0) {
            warnings.push_back(std::make_shared<ValidationWarning>(8));
        }
    }
    
    //    @Override
    //    protected Map<String, Object> toStringValues() {
    //        Map<String, Object> values = new LinkedHashMap<String, Object>();
    //        values.put("values", this.values);
    //        return values;
    //    }
    //
    //    @Override
    //    public int hashCode() {
    //        final int prime = 31;
    //        int result = super.hashCode();
    //        result = prime * result + values.hashCode();
    //        return result;
    //    }
    //
    //    @Override
    //    public boolean equals(Object obj) {
    //        if (this == obj) return true;
    //        if (!super.equals(obj)) return false;
    //        ListProperty<?> other = (ListProperty<?>) obj;
    //        if (!values.equals(other.values)) return false;
    //        return true;
    //    }
};
    
}

#endif /* list_property_hpp */
