//
//  photo.hpp
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

#ifndef photo_hpp
#define photo_hpp

#include <stdio.h>
#include "image_property.hpp"
#include "i_photo.hpp"

namespace ezvcard {
    

/**
 * <p>
 * Defines a photo, such as the person's portrait.
 * </p>
 *
 * <p>
 * <b>Code sample (creating)</b>
 * </p>
 *
 * <pre class="brush:java">
 * VCard vcard = new VCard();
 *
 * //URL
 * Photo photo = new Photo("http://www.mywebsite.com/my-photo.jpg", ImageType.JPEG);
 * vcard.addPhoto(photo);
 *
 * //binary data
 * byte data[] = ...
 * photo = new Photo(data, ImageType.JPEG);
 * vcard.addPhoto(photo);
 * </pre>
 *
 * <p>
 * <b>Code sample (retrieving)</b>
 * </p>
 *
 * <pre class="brush:java">
 * VCard vcard = ...
 * for (Photo photo : vcard.getPhotos()) {
 *   PhotoType contentType = photo.getContentType(); //e.g. "image/jpeg"
 *
 *   String url = photo.getUrl();
 *   if (url != null) {
 *     //property value is a URL
 *     continue;
 *   }
 *
 *   byte[] data = photo.getData();
 *   if (data != null) {
 *     //property value is binary data
 *     continue;
 *   }
 * }
 * </pre>
 *
 * <p>
 * <b>Property name:</b> {@code PHOTO}
 * </p>
 * <p>
 * <b>Supported versions:</b> {@code 2.1, 3.0, 4.0}
 * </p>
 * @author Michael Angstadt
 * @see <a href="http://tools.ietf.org/html/rfc6350#page-30">RFC 6350 p.30</a>
 * @see <a href="http://tools.ietf.org/html/rfc2426#page-10">RFC 2426 p.10</a>
 * @see <a href="http://www.imc.org/pdi/vcard-21.doc">vCard 2.1 p.10</a>
 */
class Photo: public ImageProperty, public IPhoto {
    
public:
    typedef std::shared_ptr<Photo> Ptr;
    
    const static std::string PROPERTYNAME;
    const static std::string CLASSNAME;
    
    Photo(const std::string& url_or_data, const ImageType::Ptr& type, bool isBinary);
    
    //public Photo(InputStream in, ImageType type);
    //public Photo(File file, ImageType type);
    
    //public Photo(Photo original);
    //public Photo copy();
    
    
protected:
    std::string _className() {
        return CLASSNAME;
    }
    
    std::string _getPropertyName() {
        return PROPERTYNAME;
    }
    
    std::string getAltId() {
        return "";
    }
    
    void setAltId(const std::string& altId) {
        
    }
    
public:
    // from IPhoto
    std::string getEncodedData() final;
    std::vector<uint8_t> getRawData() final;
    std::string getURL() final;
    std::string getImageType() final;
    bool getIsBinary() final;
    void setPhoto(const std::vector<uint8_t> & rawData, const std::string & type, bool isBinary) final;
};
    
}

#endif /* photo_hpp */
