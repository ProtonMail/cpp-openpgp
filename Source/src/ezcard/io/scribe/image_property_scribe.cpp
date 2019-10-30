//
//  image_property_scribe.cpp
//  OpenPGP
//
//  Created by Yanfeng Zhang on 5/19/17.
//  Copyright © 2017 Yanfeng Zhang. All rights reserved.
//

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
