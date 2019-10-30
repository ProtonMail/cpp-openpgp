//
//  vcard_parameter.cpp
//  OpenPGP
//
//  Created by Yanfeng Zhang on 12/2/16.
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
