//
//  vcard_parameter_case_classes.hpp
//  OpenPGP
//
//  Created by Yanfeng Zhang on 1/10/17.
//  Copyright © 2017 Yanfeng Zhang. All rights reserved.
//

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
