//
//  photo_scribe.hpp
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
