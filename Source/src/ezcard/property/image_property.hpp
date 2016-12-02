//
//  image_property.hpp
//  OpenPGP
//
//  Created by Yanfeng Zhang on 1/10/17.
//  Copyright © 2017 Yanfeng Zhang. All rights reserved.
//

#ifndef image_property_hpp
#define image_property_hpp

#include <stdio.h>
#include "image_type.hpp"

#include "binary_property.hpp"


namespace ezvcard {
    
/**
 * Represents a vCard property that stores image data.
 * @author Michael Angstadt
 */
class ImageProperty : public BinaryProperty<ImageType> {

public:
    ImageProperty(const std::string& url_or_data, const ImageType::Ptr& type, bool isBinary);
    
    
    
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
};

}

#endif /* image_property_hpp */
