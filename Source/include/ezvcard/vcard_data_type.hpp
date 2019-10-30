//
//  vcard_data_type.hpp
//  OpenPGP
//
//  Created by Yanfeng Zhang on 12/2/16.
//  Copyright © 2016 Yanfeng Zhang. All rights reserved.
//

#ifndef vcard_data_type_hpp
#define vcard_data_type_hpp


#include <string>
#include <vector>

#include "vcard_version.hpp"

class VCardDataType {
    
public:
    
    typedef std::shared_ptr<VCardDataType> Ptr;
    
    const static VCardDataType::Ptr URL;
    const static VCardDataType::Ptr CONTENT_ID;
    const static VCardDataType::Ptr BINARY;
    const static VCardDataType::Ptr URI;
    const static VCardDataType::Ptr TEXT;
    const static VCardDataType::Ptr DATE;
    const static VCardDataType::Ptr TIME;
    const static VCardDataType::Ptr DATE_TIME;
    const static VCardDataType::Ptr DATE_AND_OR_TIME;
    const static VCardDataType::Ptr TIMESTAMP;
    const static VCardDataType::Ptr BOOLEAN;
    const static VCardDataType::Ptr INTEGER;
    const static VCardDataType::Ptr FLOAT;
    const static VCardDataType::Ptr UTC_OFFSET;
    const static VCardDataType::Ptr LANGUAGE_TAG;
    
    VCardDataType(const std::string& name, std::vector<VCardVersion::Ptr> supportVersions);
    
private:
    std::string _name;
    std::vector<VCardVersion::Ptr> _supportedVersions;
    const static std::vector<VCardDataType::Ptr> _types;
    
public:
    std::string getName();

    std::vector<VCardVersion::Ptr> getSupportedVersions();
    bool isSupportedBy(const VCardVersion::Ptr& version);
    
    
    //static VCardDataType::Ptr find(String dataType);
    static VCardDataType::Ptr get(const std::string& dataType);
    static std::vector<VCardDataType::Ptr> all();
};


    
#endif /* vcard_data_type_hpp */
