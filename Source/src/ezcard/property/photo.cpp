//
//  photo.cpp
//  OpenPGP
//
//  Created by Yanfeng Zhang on 1/10/17.
//  Copyright © 2017 Yanfeng Zhang. All rights reserved.
//

#include "photo.hpp"
#include "i_photo.hpp"
#include "base64.h"

namespace ProtonMail {
    std::shared_ptr<ImageType> getImageTypeFromString(std::string type)
    {
        auto imageType = ImageType::GIF;
        if(str_equals("GIF", type))
            imageType = ImageType::GIF;
        else if(str_equals("PNG", type))
            imageType = ImageType::PNG;
        else if(str_equals("JPEG", type))
            imageType = ImageType::JPEG;
        else
            imageType = nullptr;
        
        return imageType;
    }
    
    // static can only be specified in definition
    // shared_ptr<CLASSNAME>(constructor arguments like usual)
    std::shared_ptr<IPhoto> IPhoto::create_instance(const std::vector<uint8_t> & rawData,
                                                    const std::string & type,
                                                    bool isBinary) {
        auto imageType = getImageTypeFromString(type);
        auto out = std::make_shared<ezvcard::Photo>(std::string(rawData.begin(), rawData.end()), imageType, isBinary);
        return out;
    }
}


namespace ezvcard {
    

const std::string Photo::PROPERTYNAME = "PHOTO";
const std::string Photo::CLASSNAME = "Photo";

Photo::Photo(const std::string& url_or_data,
             const ImageType::Ptr& type,
             bool isBinary) : ImageProperty(url_or_data, type, isBinary) { }

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

    // from IPhoto
    
    
    std::string Photo::getEncodedData()
    {
        return base64_encode(BinaryProperty::getData());
    }
    
    std::vector<uint8_t> Photo::getRawData()
    {
        auto str = BinaryProperty::getData();
        return std::vector<uint8_t>(str.begin(), str.end());
    }
    
    std::string Photo::getURL()
    {
        return BinaryProperty::getUrl();
    }
    
    std::string Photo::getImageType()
    {
        if(auto type = BinaryProperty::getContentType()) {
            if(type->getMediaType() == ImageType::JPEG->getMediaType())
                return "JPEG";
            else if(type->getMediaType() == ImageType::PNG->getMediaType())
                return "PNG";
            else if(type->getMediaType() == ImageType::GIF->getMediaType())
                return "GIF";
        }
        
        return "";
    }
    
    bool Photo::getIsBinary()
    {
        return BinaryProperty::isDataNull() == false;
    }
    
    void Photo::setPhoto(const std::vector<uint8_t> & data, const std::string & type, bool isBinary)
    {
        auto imageType = getImageTypeFromString(type);
        
        if (isBinary) {
            BinaryProperty::_data = std::string(data.begin(), data.end());
        } else {
            BinaryProperty::_url = std::string(data.begin(), data.end());
        }
        BinaryProperty::_contentType = imageType;
    }

}
