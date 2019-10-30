//
//  image_type.cpp
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
