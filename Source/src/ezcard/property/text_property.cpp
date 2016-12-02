//
//  text_property.cpp
//  OpenPGP
//
//  Created by Yanfeng Zhang on 1/10/17.
//  Copyright © 2017 Yanfeng Zhang. All rights reserved.
//

#include "text_property.hpp"

namespace ezvcard {
    
/**
 * Creates a property that contains text.
 * @param value the property value
 */
TextProperty::TextProperty(const std::string& value) : SimpleProperty(value) {
    
}

/**
 * Copy constructor.
 * @param original the property to make a copy of
 */
//TextProperty::TextProperty(const TextProperty::Ptr& original) : SimpleProperty(original) {
//    //super(original);
//    //value = original.value;
//}


}
