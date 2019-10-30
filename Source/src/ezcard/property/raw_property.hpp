//
//  raw_property.hpp
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


#ifndef raw_property_hpp
#define raw_property_hpp

#include <stdio.h>
#include "text_property.hpp"
#include "vcard_data_type.hpp"

namespace ezvcard {
    

class RawProperty : public TextProperty {
private:
    std::string _propertyName;
    VCardDataType::Ptr _dataType;

public:
    typedef std::shared_ptr<RawProperty> Ptr;
    
    const static std::string CLASSNAME;
    
    RawProperty(const std::string& propertyName, const std::string& value);
    RawProperty(const std::string& propertyName, const std::string& value, const VCardDataType::Ptr& dataType);
//    public RawProperty(RawProperty original);
    
    
//    public void setPropertyName(String propertyName);
    VCardDataType::Ptr getDataType();
    void setDataType(VCardDataType::Ptr dataType);
//
    
    //override
//    protected void _validate(List<Warning> warnings, VCardVersion version, VCard vcard);
//    protected Map<String, Object> toStringValues();
//    public RawProperty copy();
//    public int hashCode();
//    public boolean equals(Object obj);
    
    
protected:
    std::string _className() {
        return CLASSNAME;
    }
    
    std::string _getPropertyName() {
        return _propertyName;
    }
};

}

#endif /* raw_property_hpp */
