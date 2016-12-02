//
//  vobject_validator.hpp
//  OpenPGP
//
//  Created by Yanfeng Zhang on 1/13/17.
//  Copyright © 2017 Yanfeng Zhang. All rights reserved.
//

#ifndef vobject_validator_hpp
#define vobject_validator_hpp

#include <stdio.h>
#include <map>

#include "vcard_version.hpp"
#include "allowed_characters.hpp"

class VObjectValidator {
public:
    typedef std::shared_ptr<VObjectValidator> Ptr;
    
private:
    std::map<SyntaxStyle, std::map<bool, AllowedCharacters::Ptr>> propertyName;
    std::map<SyntaxStyle, std::map<bool, AllowedCharacters::Ptr>> group;
    std::map<SyntaxStyle, std::map<bool, AllowedCharacters::Ptr>> parameterName;
    std::map<SyntaxStyle, std::map<bool, std::map<bool, AllowedCharacters::Ptr>>> parameterValue;
    static VObjectValidator::Ptr single;
    VObjectValidator();
public:
    static VObjectValidator::Ptr get();
    ~VObjectValidator();
    
    bool validateParameterName(const std::string& name, SyntaxStyle syntax, bool strict);
    AllowedCharacters::Ptr allowedCharactersParameterName(SyntaxStyle syntax, bool strict);
    bool validateParameterValue(const std::string& value, SyntaxStyle syntax, bool caretEncoding, bool strict);
    AllowedCharacters::Ptr allowedCharactersParameterValue(SyntaxStyle syntax, bool caretEncoding, bool strict);
    
//    public static boolean validatePropertyName(String name, SyntaxStyle syntax, boolean strict);
    AllowedCharacters::Ptr allowedCharactersPropertyName(SyntaxStyle syntax, bool strict);

    //public static boolean validateGroupName(String group, SyntaxStyle syntax, boolean strict);
    AllowedCharacters::Ptr allowedCharactersGroup(SyntaxStyle syntax, bool strict);
    
};

#endif /* vobject_validator_hpp */
