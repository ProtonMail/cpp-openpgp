//
//  key_type.cpp
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

#include "key_type.hpp"


MediaTypeCaseClasses<KeyType> KeyType::enums;

const KeyType::Ptr KeyType::PGP = std::make_shared<KeyType>("PGP", "application/pgp-keys", "pgp", true);
const KeyType::Ptr KeyType::GPG = std::make_shared<KeyType>("GPG", "application/gpg", "gpg", true);
const KeyType::Ptr KeyType::X509 = std::make_shared<KeyType>("X509", "application/x509", "", true);


KeyType::KeyType(const std::string& value, const std::string& mediaType, const std::string& extension) :
MediaTypeParameter(value, mediaType, extension) {
    
}


KeyType::KeyType(const std::string& value, const std::string& mediaType, const std::string& extension, bool predefine) :
MediaTypeParameter(value, mediaType, extension) {
    
    if (predefine) {
        enums.setupPredefine({value, mediaType, extension}, {});
    }
    
}

/**
 * Searches for a parameter value that is defined as a static constant in
 * this class.
 * @param type the TYPE parameter value to search for (e.g. "JPEG") or null
 * to not search by this value
 * @param mediaType the media type to search for (e.g. "image/png") or null
 * to not search by this value
 * @param extension the file extension to search for (excluding the ".",
 * e.g. "jpg") or null to not search by this value
 * @return the object or null if not found
 */
KeyType::Ptr KeyType::find(const std::string& type, const std::string& mediaType, const std::string& extension) {
    return enums.find({type, mediaType, extension});
}

/**
 * Searches for a parameter value and creates one if it cannot be found. All
 * objects are guaranteed to be unique, so they can be compared with
 * {@code ==} equality.
 * @param type the TYPE parameter value to search for (e.g. "JPEG") or null
 * to not search by this value
 * @param mediaType the media type to search for (e.g. "image/png") or null
 * to not search by this value
 * @param extension the file extension to search for (excluding the ".",
 * e.g. "jpg") or null to not search by this value
 * @return the object
 */
KeyType::Ptr KeyType::get(const std::string& type, const std::string& mediaType, const std::string& extension) {
    return enums.get({type, mediaType, extension});
}
//
//    /**
//     * Gets all of the parameter values that are defined as static constants in
//     * this class.
//     * @return the parameter values
//     */
//    public static Collection<ImageType> all() {
//        return enums.all();
//    }
//}





bool KeyType::equals(const std::shared_ptr<KeyType> & rhs) {
    if (rhs == nullptr) {
        return false;
    }
    
    if (rhs->getMediaType() != getMediaType()) {
        return false;
    }
    
    
    if (rhs->getExtension() != getExtension()) {
        return false;
    }
    
    if (rhs->getValue() != getValue()) {
        return false;
    }
    
    return true;
}

//bool KeyType::operator==(const KeyType& rhs) {
////    if (rhs._version != _version) {
////        return false;
////    }
////    if (_syntaxStyle != rhs._syntaxStyle) {
////        return false;
////    }
////    
////    if (_xmlNamespace != rhs._xmlNamespace) {
////        return false;
////    }
//    return true;
//}


bool operator==(const KeyType::Ptr& lhs, const KeyType::Ptr& rhs) {
    return lhs->equals(rhs);
}
