//
//  media_type_parameter.hpp
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


#ifndef media_type_parameter_hpp
#define media_type_parameter_hpp

#include <stdio.h>


#include "vcard_parameter.hpp"


/**
 * Represents a TYPE parameter that also has a media type associated with it.
 * The TYPE parameter value is used in 2.1 and 3.0 vCards, while the media type
 * value is used in 4.0 vCards.
 * @author Michael Angstadt
 */
class MediaTypeParameter : public VCardParameter {
    
public:
    typedef std::shared_ptr<MediaTypeParameter> Ptr;
    
protected:
    std::string _mediaType;
    std::string _extension;
    
    std::string _className() {
        return "Encoding";
    }
    
    std::string _getPropertyName() {
        return "";
    }
    
public:
    MediaTypeParameter(const std::string& value, const std::string& mediaType, const std::string& extension);
    
    std::string getMediaType();
    
    std::string getExtension();

};

bool operator==(const MediaTypeParameter::Ptr& lhs, const MediaTypeParameter::Ptr& rhs);

#endif /* media_type_parameter_hpp */
