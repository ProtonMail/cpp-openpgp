//
//  image_property_scribe.cpp
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


#include "image_property_scribe.hpp"

namespace ezvcard {
    
//
//
///**
// * Marshals properties that contain images.
// * @param <T> the property class
// * @author Michael Angstadt
// */
//public abstract class ImagePropertyScribe<T extends ImageProperty> extends BinaryPropertyScribe<T, ImageType> {
//    public ImagePropertyScribe(Class<T> clazz, String propertyName) {
//        super(clazz, propertyName);
//    }



//    @Override
//    protected T _parseHtml(HCardElement element, ParseContext context) {
//        String elementName = element.tagName();
//        if (!"img".equals(elementName)) {
//            return super._parseHtml(element, context);
//        }
//        
//        String src = element.absUrl("src");
//        if (src.length() == 0) {
//            throw new CannotParseException(13);
//        }
//        
//        try {
//            DataUri uri = DataUri.parse(src);
//            ImageType mediaType = _mediaTypeFromMediaTypeParameter(uri.getContentType());
//            return _newInstance(uri.getData(), mediaType);
//        } catch (IllegalArgumentException e) {
//            //not a data URI
//            String extension = getFileExtension(src);
//            ImageType mediaType = (extension == null) ? null : _mediaTypeFromFileExtension(extension);
//            return _newInstance(src, mediaType);
//        }
//    }
//}

}
