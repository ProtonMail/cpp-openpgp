//
//  media_type_parameter.cpp
//  OpenPGP
//
//  Created by Yanfeng Zhang on 1/10/17.
//  Copyright © 2017 Yanfeng Zhang. All rights reserved.
//

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
