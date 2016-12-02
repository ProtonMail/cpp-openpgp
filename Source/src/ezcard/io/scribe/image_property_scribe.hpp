//
//  image_property_scribe.hpp
//  OpenPGP
//
//  Created by Yanfeng Zhang on 5/19/17.
//  Copyright © 2017 Yanfeng Zhang. All rights reserved.
//

#ifndef image_property_scribe_hpp
#define image_property_scribe_hpp

#include <stdio.h>
#include "image_property.hpp"
#include "binary_property_scribe.hpp"
#include "binary_property.hpp"

namespace ezvcard {
    

/**
 * Marshals properties that contain images.
 * @param <T> the property class
 * @author Michael Angstadt
 */
template <class T>
class ImagePropertyScribe : public BinaryPropertyScribe<T, ImageType> {    
    static_assert(std::is_base_of<ImageProperty, T>::value, "ImagePropertyScribe<T>: T must be extent of ImageProperty type :-(");

    
public:
    ImagePropertyScribe(const std::string& propertyName) : BinaryPropertyScribe<T, ImageType>(propertyName) {
        
    }
    
protected:
    
    
    ImageType::Ptr _mediaTypeFromTypeParameter(const std::string& type) {
        return ImageType::get(type, "", "");
    }
    
    ImageType::Ptr _mediaTypeFromMediaTypeParameter(const std::string& mediaType) {
        return ImageType::get("", mediaType, "");
    }
    
    ImageType::Ptr _mediaTypeFromFileExtension(const std::string& extension) {
        return ImageType::find("", "", extension);
    }
    
//    @Override
//    protected T _parseHtml(HCardElement element, ParseContext context)
};

}

#endif /* image_property_scribe_hpp */
