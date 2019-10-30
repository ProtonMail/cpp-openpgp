//
//  image_type.hpp
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
