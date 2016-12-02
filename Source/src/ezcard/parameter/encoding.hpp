//
//  encoding.hpp
//  OpenPGP
//
//  Created by Yanfeng Zhang on 1/10/17.
//  Copyright © 2017 Yanfeng Zhang. All rights reserved.
//

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
