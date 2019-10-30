//
//  vcard_parameter.hpp
//  OpenPGP
//
//  Created by Yanfeng Zhang on 12/2/16.
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

#ifndef vcard_parameter_hpp
#define vcard_parameter_hpp

#include <iostream>
#include <string>
#include <vector>
#include "object_base.hpp"
#include "vcard_version.hpp"

class VCardParameter : public PMObject {
protected:
    std::string _value;
    VCardParameter(const std::string& value, std::vector<VCardVersion::Ptr> support, bool preserveCase);
    std::vector<VCardVersion::Ptr> _supportedVersions;

    std::string _className() {
        return "VCardParameter";
    }
    
public:
    typedef std::shared_ptr<VCardParameter> Ptr;
    
    VCardParameter(const std::string& value, std::vector<VCardVersion::Ptr> support);
    ~VCardParameter();
    std::string getValue();
    std::vector<VCardVersion::Ptr> getSupportedVersions();
    bool isSupportedBy(const VCardVersion::Ptr& version);
    
    //std::string toString();
    bool equals(const VCardParameter::Ptr & rhs);
};


bool operator==(const VCardParameter::Ptr& lhs, const VCardParameter::Ptr& rhs) ;


#endif /* vcard_parameter_hpp */
