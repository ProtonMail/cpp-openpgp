//
//  key_type.hpp
//  OpenPGP
//
//  Created by Yanfeng Zhang on 1/10/17.
//  Copyright © 2017 Yanfeng Zhang. All rights reserved.
//

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
