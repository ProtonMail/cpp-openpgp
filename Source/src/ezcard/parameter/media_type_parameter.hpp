//
//  media_type_parameter.hpp
//  OpenPGP
//
//  Created by Yanfeng Zhang on 1/10/17.
//  Copyright © 2017 Yanfeng Zhang. All rights reserved.
//

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
