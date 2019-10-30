//
//  vcard_data_type.hpp
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
