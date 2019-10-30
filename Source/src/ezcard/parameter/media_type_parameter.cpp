//
//  media_type_parameter.cpp
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


#include "media_type_parameter.hpp"

/**
 * @param value the TYPE parameter value (e.g. "JPEG")
 * @param mediaType the media type (e.g. "image/jpeg")
 * @param extension the file extension (e.g. "jpg")
 */
MediaTypeParameter::MediaTypeParameter(const std::string& value, const std::string& mediaType, const std::string& extension) :
VCardParameter(value, VCardVersion::values()) {
    _mediaType = mediaType;
    _extension = extension;
    
}

std::string MediaTypeParameter::getMediaType() {
    return _mediaType;
}

std::string MediaTypeParameter::getExtension() {
    return _extension;
}

bool operator==(const MediaTypeParameter::Ptr& lhs, const MediaTypeParameter::Ptr& rhs) {
    return false;
}



//    @Override
//    public int hashCode() {
//        final int prime = 31;
//        int result = super.hashCode();
//        result = prime * result + ((extension == null) ? 0 : extension.hashCode());
//        result = prime * result + ((mediaType == null) ? 0 : mediaType.hashCode());
//        return result;
//    }
//    
//    @Override
//    public boolean equals(Object obj) {
//        if (this == obj)
//            return true;
//        if (!super.equals(obj))
//            return false;
//        if (getClass() != obj.getClass())
//            return false;
//        MediaTypeParameter other = (MediaTypeParameter) obj;
//        if (extension == null) {
//            if (other.extension != null)
//                return false;
//        } else if (!extension.equals(other.extension))
//            return false;
//        if (mediaType == null) {
//            if (other.mediaType != null)
//                return false;
//        } else if (!mediaType.equals(other.mediaType))
//            return false;
//        return true;
//    }
//}
