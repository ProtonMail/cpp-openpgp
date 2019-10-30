//
//  encoding.hpp
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

#ifndef encoding_hpp
#define encoding_hpp

#include <stdio.h>
#include <string>
#include "vcard_parameter.hpp"
#include "vcard_parameter_case_classes.hpp"


class Encoding : public VCardParameter {
    
public:
    typedef std::shared_ptr<Encoding> Ptr;
    
    static Encoding::Ptr QUOTED_PRINTABLE;
    static Encoding::Ptr BASE64;
    static Encoding::Ptr _8BIT;
    static Encoding::Ptr _7BIT;
    static Encoding::Ptr B;
    
private:
    static VCardParameterCaseClasses<Encoding> enums;
    Encoding(bool predefine, const std::string& value, std::vector<VCardVersion::Ptr> support, bool preserveCase);
    
protected:
    std::string _className() {
        return "Encoding";
    }
    
    std::string _getPropertyName() {
        return "";
    }
    
public:

    Encoding(const std::string& value, std::vector<VCardVersion::Ptr> support);
    Encoding(const std::string& value, std::vector<VCardVersion::Ptr> support, bool preserveCase);
    static Encoding::Ptr find(const std::string& value);
    static Encoding::Ptr get(const std::string& value);
    static std::vector<Encoding::Ptr> all();
    static std::string all_to_string();
};


bool operator==(const Encoding::Ptr& lhs, const Encoding::Ptr& rhs) ;



#endif /* encoding_hpp */
