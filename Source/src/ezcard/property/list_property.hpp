//
//  list_property.hpp
//  OpenPGP
//
//  Created by Yanfeng Zhang on 1/10/17.
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
    
    void setValues(std::vector<T> values) {
        _values = values;
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
