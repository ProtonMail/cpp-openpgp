//
//  simple_property.cpp
//  OpenPGP
//
//  Created by Yanfeng Zhang on 1/10/17.
//  Copyright © 2017 Yanfeng Zhang. All rights reserved.
//

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
