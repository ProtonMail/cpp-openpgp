//
//  photo_scribe.cpp
//  OpenPGP
//
//  Created by Yanfeng Zhang on 5/19/17.
//  Copyright © 2017 Yanfeng Zhang. All rights reserved.
//

#include "photo_scribe.hpp"

namespace ezvcard {
    

PhotoScribe::PhotoScribe() : ImagePropertyScribe(Photo::PROPERTYNAME) {
    
}
//
///**
// * Marshals {@link Photo} properties.
// * @author Michael Angstadt
// */
//public class PhotoScribe extends ImagePropertyScribe<Photo> {
//    public PhotoScribe() {
//        super(Photo.class, "PHOTO");
//    }
//    
//    @Override
//    protected Photo _newInstance(String uri, ImageType contentType) {
//        return new Photo(uri, contentType);
//    }
//    
//    @Override
//    protected Photo _newInstance(byte[] data, ImageType contentType) {
//        return new Photo(data, contentType);
//    }
//}


}
