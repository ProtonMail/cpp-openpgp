//
//  image_property_scribe.hpp
//  OpenPGP
//
//  Created by Yanfeng Zhang on 5/19/17.
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
