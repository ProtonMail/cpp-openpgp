//
//  image_type.hpp
//  OpenPGP
//
//  Created by Yanfeng Zhang on 1/10/17.
//  Copyright © 2017 Yanfeng Zhang. All rights reserved.
//

#ifndef image_type_hpp
#define image_type_hpp

#include <stdio.h>
#include "media_type_case_classes.hpp"


/**
 * Represents an image media type used in the TYPE parameter, MEDIATYPE
 * parameter, and data URIs of the {@link Photo} and {@link Logo}
 * properties.
 * <p>
 * <b>Supported versions:</b> {@code 2.1, 3.0, 4.0}
 * </p>
 * @author George El-Haddadt Mar 10, 2010
 * @author Michael Angstadt
 */
class ImageType : public MediaTypeParameter {
public:
    typedef std::shared_ptr<ImageType> Ptr;
    
    ImageType(const std::string& value, const std::string& mediaType, const std::string& extension);
private:
    static MediaTypeCaseClasses<ImageType> enums;
    
public:
    const static ImageType::Ptr GIF;
    const static ImageType::Ptr JPEG;
    const static ImageType::Ptr PNG;
    
    static ImageType::Ptr find(const std::string& type, const std::string& mediaType, const std::string& extension);
    static ImageType::Ptr get(const std::string& type, const std::string& mediaType, const std::string& extension);
    static std::vector<ImageType::Ptr> all();
    
};





#endif /* image_type_hpp */
