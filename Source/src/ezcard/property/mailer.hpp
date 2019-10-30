//
//  mailer.hpp
//  OpenPGP
//
//  Created by Yanfeng Zhang on 1/10/17.
//  Copyright © 2017 Yanfeng Zhang. All rights reserved.
//

#ifndef mailer_hpp
#define mailer_hpp

#include <stdio.h>

#include "text_property.hpp"

namespace ezvcard {
    

class Mailer : public TextProperty {
public:
    
    const static std::string CLASSNAME;
    const static std::string PROPERTYNAME;
    
    
public:
    typedef std::shared_ptr<Mailer> Ptr;
    
    Mailer(const std::string& emailClient);
    

protected:
    std::vector<VCardVersion::Ptr> _getSupportedVersions();
    
    std::string _className() {
        return CLASSNAME;
    }
    
    std::string _getPropertyName() {
        return PROPERTYNAME;
    }

};

    
}

#endif /* mailer_hpp */
