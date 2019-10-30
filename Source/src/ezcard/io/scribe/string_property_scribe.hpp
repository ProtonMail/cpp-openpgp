//
//  string_property_scribe.hpp
//  OpenPGP
//
//  Created by Yanfeng Zhang on 1/11/17.
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
