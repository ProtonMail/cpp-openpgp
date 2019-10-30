//
//  key_type.hpp
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


#ifndef key_type_hpp
#define key_type_hpp

#include "media_type_parameter.hpp"
#include "media_type_case_classes.hpp"


class KeyType : public MediaTypeParameter {
public:
    typedef std::shared_ptr<KeyType> Ptr;
    KeyType(const std::string& value, const std::string& mediaType, const std::string& extension);
    KeyType(const std::string& value, const std::string& mediaType, const std::string& extension, bool predefine);
private:
    static MediaTypeCaseClasses<KeyType> enums;

public:
    const static KeyType::Ptr PGP;
    const static KeyType::Ptr GPG;
    const static KeyType::Ptr X509;

    static KeyType::Ptr find(const std::string& type, const std::string& mediaType, const std::string& extension);
    static KeyType::Ptr get(const std::string& type, const std::string& mediaType, const std::string& extension);
    static std::vector<KeyType::Ptr> all();
    
    bool equals(const std::shared_ptr<KeyType> & rhs);
    //bool operator==(const KeyType& rhs);
};

bool operator==(const KeyType::Ptr& lhs, const KeyType::Ptr& rhs);

#endif /* key_type_hpp */
