//
//  image_property.cpp
//  OpenPGP
//
//  Created by Yanfeng Zhang on 1/10/17.
//  Copyright © 2017 Yanfeng Zhang. All rights reserved.
//

#include "image_property.hpp"

namespace ezvcard {
    
ImageProperty::ImageProperty(const std::string& url_or_data, const ImageType::Ptr& type, bool isBinary) :
BinaryProperty(url_or_data, type, isBinary) {
    
    
    
}
//    /**
//     * Creates an image property.
//     * @param url the URL to the image
//     * @param type the content type (e.g. JPEG)
//     */
//    public ImageProperty(String url, ImageType type) {
//        super(url, type);
//    }
//    
//    /**
//     * Creates an image property.
//     * @param data the binary data of the image
//     * @param type the content type (e.g. JPEG)
//     */
//    public ImageProperty(byte[] data, ImageType type) {
//        super(data, type);
//    }
//    
//    /**
//     * Creates an image property.
//     * @param in an input stream to the binary data (will be closed)
//     * @param type the content type (e.g. JPEG)
//     * @throws IOException if there's a problem reading from the input stream
//     */
//    public ImageProperty(InputStream in, ImageType type) throws IOException {
//        super(in, type);
//    }
//    
//    /**
//     * Creates an image property.
//     * @param file the image file
//     * @param type the content type (e.g. JPEG)
//     * @throws IOException if there's a problem reading from the file
//     */
//    public ImageProperty(File file, ImageType type) throws IOException {
//        super(file, type);
//    }
//    
//    /**
//     * Copy constructor.
//     * @param original the property to make a copy of
//     */
//    public ImageProperty(ImageProperty original) {
//        super(original);
//    }
//}


}
