//
//  text_property.hpp
//  OpenPGP
//
//  Created by Yanfeng Zhang on 1/10/17.
//  Copyright © 2017 Yanfeng Zhang. All rights reserved.
//

#ifndef text_property_hpp
#define text_property_hpp

#include <stdio.h>
#include "simple_property.hpp"


namespace ezvcard {
    

class TextProperty : public SimpleProperty<std::string> {
public:
    typedef std::shared_ptr<TextProperty> Ptr;
    
    TextProperty(const std::string& value);
   // TextProperty(const TextProperty::Ptr& original);
};

}

#endif /* text_property_hpp */
