//
//  vcard_parameter.cpp
//  OpenPGP
//
//  Created by Yanfeng Zhang on 12/2/16.
//  Copyright © 2016 Yanfeng Zhang. All rights reserved.
//

#include "vcard_parameter.hpp"
#include "string_util.hpp"




VCardParameter::VCardParameter(const std::string &value, std::vector<VCardVersion::Ptr> support, bool preserveCase) {
    _value = preserveCase ? value : str_to_lower(value);
    _supportedVersions = support;
}


std::string VCardParameter::getValue() {
    return _value;
}

VCardParameter::VCardParameter(const std::string& value, std::vector<VCardVersion::Ptr> support) : VCardParameter(value, support, false) {

}

VCardParameter::~VCardParameter() {
    
}

std::vector<VCardVersion::Ptr> VCardParameter::getSupportedVersions() {
    if (_supportedVersions.size() > 0) {
        return _supportedVersions;
    }
    return VCardVersion::values();
}


/**
 * <p>
 * Determines if this parameter value is supported by the given vCard
 * version.
 * </p>
 * <p>
 * The supported versions are defined by assigning a
 * {@link SupportedVersions} annotation to the parameter value's static
 * field (for example, {@link AddressType#DOM}). Dynamically-created
 * parameter values (i.e. non-standard values) are considered to be
 * supported by all versions.
 * </p>
 * @param version the vCard version
 * @return true if it is supported, false if not
 */
bool VCardParameter::isSupportedBy(const VCardVersion::Ptr& version) {
    for (auto supportedVersion : getSupportedVersions()) {
        if (supportedVersion == version) {
            return true;
        }
    }
    return false;
}





//
//    @Override
//    public String toString() {
//        return value;
//    }
//
//    @Override
//    public int hashCode() {
//        final int prime = 31;
//        int result = 1;
//        result = prime * result + ((value == null) ? 0 : value.hashCode());
//        return result;
//    }
//    

bool VCardParameter::equals( const VCardParameter::Ptr & rhs) {
    
    if (rhs == nullptr) {
        return false;
    }
    
    if (_value == rhs->getValue()) {
        return true;
    }
 
    return false;
}



bool operator==(const VCardParameter::Ptr& lhs, const VCardParameter::Ptr& rhs) {
    return lhs->equals(rhs);
}
