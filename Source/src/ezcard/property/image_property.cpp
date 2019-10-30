//
//  image_property.cpp
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
