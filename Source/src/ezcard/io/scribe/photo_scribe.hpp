//
//  photo_scribe.hpp
//  OpenPGP
//
//  Created by Yanfeng Zhang on 5/19/17.
//  Copyright © 2017 Yanfeng Zhang. All rights reserved.
//

#ifndef photo_scribe_hpp
#define photo_scribe_hpp

#include <stdio.h>

#include "image_property_scribe.hpp"
#include "photo.hpp"

namespace ezvcard {
    

/**
 * Marshals {@link Photo} properties.
 * @author Michael Angstadt
 */
class PhotoScribe : public ImagePropertyScribe<Photo> {
    
public:
    PhotoScribe();

    Photo::Ptr _newInstance(const std::string& uri_or_data, const ImageType::Ptr& contentType, bool isBinary) {
        return std::make_shared<Photo>(uri_or_data, contentType, isBinary);
    }
    
//    @Override
//    protected Photo _newInstance(byte[] data, ImageType contentType) {
//        return new Photo(data, contentType);
//    }
    
protected:
    std::string _className() {
        return "PhotoScribe";
    }
};

    
}

#endif /* photo_scribe_hpp */
