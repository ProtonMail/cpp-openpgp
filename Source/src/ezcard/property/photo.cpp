//
//  photo.cpp
//  OpenPGP
//
//  Created by Yanfeng Zhang on 1/10/17.
//  Copyright © 2017 Yanfeng Zhang. All rights reserved.
//

#include "photo.hpp"



namespace ezvcard {
    

const std::string Photo::PROPERTYNAME = "PHOTO";
const std::string Photo::CLASSNAME = "Photo";

Photo::Photo(const std::string& url_or_data, const ImageType::Ptr& type, bool isBinary) : ImageProperty(url_or_data, type, isBinary) {
    
}





//    /**
//     * Creates a photo property.
//     * @param url the URL to the photo
//     * @param type the content type (e.g. JPEG)
//     */
//    public Photo(String url, ImageType type) {
//        super(url, type);
//    }
//    
//    /**
//     * Creates a photo property.
//     * @param data the binary data of the photo
//     * @param type the content type (e.g. JPEG)
//     */
//    public Photo(byte[] data, ImageType type) {
//        super(data, type);
//    }
//    
//    /**
//     * Creates a photo property.
//     * @param in an input stream to the binary data (will be closed)
//     * @param type the content type (e.g. JPEG)
//     * @throws IOException if there's a problem reading from the input stream
//     */
//    public Photo(InputStream in, ImageType type) throws IOException {
//        super(in, type);
//    }
//    
//    /**
//     * Creates a photo property.
//     * @param file the image file
//     * @param type the content type (e.g. JPEG)
//     * @throws IOException if there's a problem reading from the file
//     */
//    public Photo(File file, ImageType type) throws IOException {
//        super(file, type);
//    }
//    
//    /**
//     * Copy constructor.
//     * @param original the property to make a copy of
//     */
//    public Photo(Photo original) {
//        super(original);
//    }
//    
//    @Override
//    public Photo copy() {
//        return new Photo(this);
//    }
//}


}
