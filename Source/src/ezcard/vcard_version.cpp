//
//  vcard_version.cpp
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

#include "vcard_version.hpp"
#include <iostream>
#include <sstream>

VCardVersion::Ptr VCardVersion::Ver2_1 = nullptr;
VCardVersion::Ptr VCardVersion::Ver3_0 = nullptr;
VCardVersion::Ptr VCardVersion::Ver4_0 = nullptr;

std::vector<VCardVersion::Ptr> VCardVersion::values() {
    return std::vector<VCardVersion::Ptr>{
        VCardVersion::V2_1(),
        VCardVersion::V3_0(),
        VCardVersion::V4_0()
    };
}

/**
 * @param version the text representation
 * @param xmlNamespace the xCard namespace or null if not defined
 */
VCardVersion::VCardVersion(std::string version, SyntaxStyle syntaxStyle, std::string xmlNamespace) {
    _version = version;
    _syntaxStyle = syntaxStyle;
    _xmlNamespace = xmlNamespace;
}

/**
 * Gets the text representation of this version.
 * @return the text representation
 */
std::string VCardVersion::getVersion() {
    return _version;
}

/**
 * Gets the syntax style used by this version when writing to a plain-text
 * data stream.
 * @return the syntax style
 */
SyntaxStyle VCardVersion::getSyntaxStyle() {
    return _syntaxStyle;
}

/**
 * Gets the XML namespace used by this version when writing to an xCard.
 * @return the XML namespace or null if this version does not support xCard
 */
std::string VCardVersion::getXmlNamespace() {
    return _xmlNamespace;
}

/**
 * Gets a {@link VCardVersion} instance based on the given text
 * representation.
 * @param value the text representation
 * @return the object or null if not found
 */
VCardVersion::Ptr VCardVersion::valueOfByStr(const std::string& value) {
    for (auto version : values()) {
        if (version->getVersion() == value) {
            return version;
        }
    }
    return nullptr;
}

/**
 * Gets a {@link VCardVersion} instance based on the given XML namespace.
 * @param ns the XML namespace
 * @return the object or null if not found
 */
VCardVersion::Ptr VCardVersion::valueOfByXmlNamespace(const std::string& ns) {
//    for (VCardVersion version : VCardVersion.values()) {
//        String versionNs = version.getXmlNamespace();
//        if (versionNs != null && versionNs.equals(ns)) {
//            return version;
//        }
//    }
//    return null;
    return VCardVersion::V3_0();
}

std::string VCardVersion::toString() {
    return _version;
}

std::vector<VCardVersion::Ptr> VCardVersion::V21_V30() {
    return { VCardVersion::V2_1(), VCardVersion::V3_0() };
}

std::string VCardVersion::toString(std::vector<VCardVersion::Ptr> versions) {
    std::vector<std::string> l;
    for (auto v : versions) {
        l.push_back(v->toString());
    }
    std::stringstream ss("");
    std::ostream_iterator<std::string> output_iterator(ss, ",");
    std::copy(l.begin(), l.end(), output_iterator);
    return ss.str();
}



bool VCardVersion::equals(const Ptr& obj) {
    if (obj == nullptr) {
        return false;
    }
    if (_version != obj->getVersion()) {
        return false;
    }
    if (_syntaxStyle != obj->getSyntaxStyle()) {
        return false;
    }
    
    if (_xmlNamespace != obj->getXmlNamespace()) {
        return false;
    }
    
    return true;
}

bool VCardVersion::equals(const std::shared_ptr<IVCardVersion> & rhs) {
    if (rhs == nullptr) {
        return false;
    }
    
    auto vcardversion = std::dynamic_pointer_cast<VCardVersion>(rhs);
    if(vcardversion == nullptr) {
        return false;
    }
    
    if (!equals(vcardversion)) {
        return false;
    }
    
    return true;
}

bool VCardVersion::operator==(const VCardVersion& rhs) {
    if (rhs._version != _version) {
        return false;
    }
    if (_syntaxStyle != rhs._syntaxStyle) {
        return false;
    }
    
    if (_xmlNamespace != rhs._xmlNamespace) {
        return false;
    }
    return true;
}


VCardVersion::Ptr VCardVersion::V2_1() {
    if (Ver2_1 == nullptr) {
        Ver2_1 = std::shared_ptr<VCardVersion>(new VCardVersion("2.1", OLD, ""));
    }
    return Ver2_1;
}

VCardVersion::Ptr VCardVersion::V3_0() {
    if (Ver3_0 == nullptr) {
        Ver3_0 = std::shared_ptr<VCardVersion>(new VCardVersion("3.0", NEW, ""));
    }
    return Ver3_0;
}

VCardVersion::Ptr VCardVersion::V4_0() {
    if (Ver4_0 == nullptr) {
        Ver4_0 = std::shared_ptr<VCardVersion>(new VCardVersion("4.0", NEW, "urn:ietf:params:xml:ns:vcard-4.0"));
    }
    return Ver4_0;
}

std::shared_ptr<IVCardVersion> IVCardVersion::VCard2_1() {
    return VCardVersion::V2_1();
}

std::shared_ptr<IVCardVersion> IVCardVersion::VCard3_0() {
    return VCardVersion::V3_0();
}

std::shared_ptr<IVCardVersion> IVCardVersion::VCard4_0() {
    return VCardVersion::V4_0();
}


bool operator==(const VCardVersion::Ptr& lhs, const VCardVersion::Ptr& rhs) {
    return lhs->equals(rhs);
}

