//
//  email_type.hpp
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


#ifndef email_type_hpp
#define email_type_hpp


#include <stdio.h>
#include <string>
#include "vcard_version.hpp"
#include "vcard_parameter.hpp"
#include "vcard_parameter_case_classes.hpp"

/**
 * Represents the TYPE parameter of the {@link Email} properties.
 * <p>
 * <b>Supported versions:</b> {@code 2.1, 3.0, 4.0}
 * </p>
 * @author Michael Angstadt
 */
class EmailType : public VCardParameter {
    
public:
    typedef std::shared_ptr<EmailType> Ptr;
    
public:
    const static EmailType::Ptr INTERNET;
    const static EmailType::Ptr X400;
    const static EmailType::Ptr PREF;
    const static EmailType::Ptr AOL;
    const static EmailType::Ptr APPLELINK;
    const static EmailType::Ptr ATTMAIL;
    const static EmailType::Ptr CIS;
    const static EmailType::Ptr EWORLD;
    const static EmailType::Ptr IBMMAIL;
    const static EmailType::Ptr MCIMAIL;
    const static EmailType::Ptr POWERSHARE;
    const static EmailType::Ptr PRODIGY;
    const static EmailType::Ptr TLX;
    const static EmailType::Ptr HOME;
    const static EmailType::Ptr WORK;
    
private:
    template<typename>
    friend class VCardParameterCaseClasses;
    
    static VCardParameterCaseClasses<EmailType> enums;
    EmailType(const std::string& value, std::vector<VCardVersion::Ptr> support);
    EmailType(const std::string& value, std::vector<VCardVersion::Ptr> support, bool preserveCase);
    EmailType(bool predefine, const std::string& value, std::vector<VCardVersion::Ptr> support, bool preserveCase);
    
public:
    static EmailType::Ptr find(const std::string& value);
    static EmailType::Ptr get(const std::string& value);
    static std::vector<EmailType::Ptr> all();
    
protected:
    std::string _className() {
        return "EmailType";
    }
    
    std::string _getPropertyName() {
        return "";
    }
};


bool operator==(const EmailType::Ptr& lhs, const EmailType::Ptr& rhs);


#endif /* email_type_hpp */
