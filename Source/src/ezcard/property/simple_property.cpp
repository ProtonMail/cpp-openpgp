//
//  simple_property.cpp
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


#include "simple_property.hpp"

/**
 * Creates a valued property
 * @param value the value
 */
//SimpleProperty: SimpleProperty(T value) {
//    this.value = value;
//}

/**
//     * Copy constructor.
//     * @param original the property to make a copy of
//     */
//    public SimpleProperty(SimpleProperty<T> original) {
//        super(original);
//        value = original.value;
//    }
//    
//    /**
//     * Gets the value of this property.
//     * @return the value or null if not set
//     */
//    public T getValue() {
//        return value;
//    }
//    
//    /**
//     * Sets the value of this property.
//     * @param value the value
//     */
//    public void setValue(T value) {
//        this.value = value;
//    }
//    
//    @Override
//    protected void _validate(List<Warning> warnings, VCardVersion version, VCard vcard) {
//        if (value == null) {
//            warnings.add(new Warning(8));
//        }
//    }
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
//}
