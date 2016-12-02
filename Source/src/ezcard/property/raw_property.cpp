//
//  raw_property.cpp
//  OpenPGP
//
//  Created by Yanfeng Zhang on 1/10/17.
//  Copyright © 2017 Yanfeng Zhang. All rights reserved.
//

#include "raw_property.hpp"

namespace ezvcard {
    
    
    const std::string RawProperty::CLASSNAME = "RawProperty";
    

/**
 * Creates a raw property.
 * @param propertyName the property name (e.g. "X-GENDER")
 * @param value the property value
 */
RawProperty::RawProperty(const std::string& propertyName, const std::string& value) : TextProperty(value) {
    _propertyName = propertyName;
}

/**
 * Creates a raw property.
 * @param propertyName the property name (e.g. "X-GENDER")
 * @param value the property value
 * @param dataType the value's data type
 */
RawProperty::RawProperty(const std::string& propertyName, const std::string& value, const VCardDataType::Ptr& dataType) : TextProperty(value)  {
    _propertyName = propertyName;
    _dataType = dataType;
}

///**
// * Copy constructor.
// * @param original the property to make a copy of
// */
//public RawProperty(RawProperty original) {
//    super(original);
//    propertyName = original.propertyName;
//    dataType = original.dataType;
//}


//
///**
// * Sets the name of the property.
// * @param propertyName the property name
// */
//public void setPropertyName(String propertyName) {
//    this.propertyName = propertyName;
//}

/**
 * Gets the data type of the property's value.
 * @return the data type or null if unknown
 */
VCardDataType::Ptr RawProperty::getDataType() {
    return _dataType;
}

/**
 * Sets the data type of the property's value.
 * @param dataType the data type or null if unknown
 */
void RawProperty::setDataType(VCardDataType::Ptr dataType) {
    _dataType = dataType;
}

//@Override
//protected void _validate(List<Warning> warnings, VCardVersion version, VCard vcard) {
//    SyntaxStyle syntax = version.getSyntaxStyle();
//    AllowedCharacters allowed = VObjectValidator.allowedCharactersParameterName(syntax, true);
//    if (!allowed.check(propertyName)) {
//        if (syntax == SyntaxStyle.OLD) {
//            AllowedCharacters notAllowed = allowed.flip();
//            warnings.add(new Warning(33, propertyName, notAllowed.toString(true)));
//        } else {
//            warnings.add(new Warning(24, propertyName));
//        }
//    }
//}
//
//@Override
//protected Map<String, Object> toStringValues() {
//    Map<String, Object> values = new LinkedHashMap<String, Object>();
//    values.put("propertyName", propertyName);
//    values.put("dataType", dataType);
//    values.put("value", value);
//    return values;
//}
//
//@Override
//public RawProperty copy() {
//    return new RawProperty(this);
//}
//
//@Override
//public int hashCode() {
//    final int prime = 31;
//    int result = super.hashCode();
//    result = prime * result + ((dataType == null) ? 0 : dataType.hashCode());
//    result = prime * result + ((propertyName == null) ? 0 : propertyName.toLowerCase().hashCode());
//    return result;
//}
//
//@Override
//public boolean equals(Object obj) {
//    if (this == obj) return true;
//    if (!super.equals(obj)) return false;
//    RawProperty other = (RawProperty) obj;
//    if (dataType == null) {
//        if (other.dataType != null) return false;
//    } else if (!dataType.equals(other.dataType)) return false;
//    if (propertyName == null) {
//        if (other.propertyName != null) return false;
//    } else if (!propertyName.equalsIgnoreCase(other.propertyName)) return false;
//    return true;
//}
    
    
}
