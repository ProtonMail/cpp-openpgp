//
//  string_property_scribe.hpp
//  OpenPGP
//
//  Created by Yanfeng Zhang on 1/11/17.
//  Copyright © 2017 Yanfeng Zhang. All rights reserved.
//

#ifndef string_property_scribe_hpp
#define string_property_scribe_hpp

#include <stdio.h>
#include "simple_property_scribe.hpp"

namespace ezvcard {
    

template <class T>
class StringPropertyScribe : public SimplePropertyScribe<T> {
    static_assert(std::is_base_of<VCardProperty, T>::value, "StringPropertyScribe<T>: T must be extent of VCardProperty type :-(");
    
public:
    StringPropertyScribe(const std::string& propertyName) : SimplePropertyScribe<T>(propertyName, VCardDataType::TEXT)  {
    
    }
    
    StringPropertyScribe(const std::string& propertyName, const VCardDataType::Ptr& dataType) : SimplePropertyScribe<T>(propertyName, dataType)  {
        
    }


protected:
    std::string _writeValue(const std::shared_ptr<T>& property) {
        return property->getValue();
    }
};

}

#endif /* string_property_scribe_hpp */
