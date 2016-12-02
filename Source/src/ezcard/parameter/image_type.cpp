//
//  image_type.cpp
//  OpenPGP
//
//  Created by Yanfeng Zhang on 1/10/17.
//  Copyright © 2017 Yanfeng Zhang. All rights reserved.
//

#include "image_type.hpp"
#include "string_util.hpp"

MediaTypeCaseClasses<ImageType> ImageType::enums;

const ImageType::Ptr ImageType::GIF = std::make_shared<ImageType>("GIF", "image/gif", "gif");
const ImageType::Ptr ImageType::JPEG = std::make_shared<ImageType>("JPEG", "image/jpeg", "jpg");
const ImageType::Ptr ImageType::PNG = std::make_shared<ImageType>("PNG", "image/png", "png");

ImageType::ImageType(const std::string& value, const std::string& mediaType, const std::string& extension) :
MediaTypeParameter(value, mediaType, extension) {
    
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
ImageType::Ptr ImageType::find(const std::string& type, const std::string& mediaType, const std::string& extension) {
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
ImageType::Ptr ImageType::get(const std::string& type, const std::string& mediaType, const std::string& extension) {
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
