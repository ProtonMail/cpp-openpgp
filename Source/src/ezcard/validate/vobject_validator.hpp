//
//  vobject_validator.hpp
//  OpenPGP
//
//  Created by Yanfeng Zhang on 1/13/17.
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
