//
//  vcard_parameter.hpp
//  OpenPGP
//
//  Created by Yanfeng Zhang on 12/2/16.
//  Copyright © 2016 Yanfeng Zhang. All rights reserved.
//

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
