//
//  vcard_parameter_case_classes.hpp
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


#ifndef vcard_parameter_case_classes_hpp
#define vcard_parameter_case_classes_hpp

#include <stdio.h>
#include <string>
#include "case_classes.hpp"
#include "vcard_parameter.hpp"
#include "string_util.hpp"



template <class T>
class VCardParameterCaseClasses : public CaseClasses<T, std::string> {
    static_assert(std::is_base_of<VCardParameter, T>::value, "VCardParameterCaseClasses<T>: T must be VCardParameter type :-(");
    
public:
    VCardParameterCaseClasses() : CaseClasses<T, std::string>() {
        
    }
    
protected:
    std::shared_ptr<T> create(const std::string& value, std::vector<VCardVersion::Ptr> support);
    std::shared_ptr<T> create(const std::string& value, std::vector<VCardVersion::Ptr> support, bool preserveCase);
    bool matches(const std::shared_ptr<T>& object, const std::string& value) {
        if (VCardParameter::Ptr out = std::dynamic_pointer_cast<VCardParameter>(object)) {
            return str_equals(out->getValue(), value);
        }
        return false;
    }
};

#endif /* vcard_parameter_case_classes_hpp */
