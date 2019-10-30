//
//  email.hpp
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

#ifndef email_hpp
#define email_hpp

#include <stdio.h>
#include <string>
#include <vector>

#include "text_property.hpp"
#include "has_alt_Id.hpp"
#include "pid.hpp"
#include "email_type.hpp"
#include <bridge/i_email.hpp>

using namespace ProtonMail;

namespace ezvcard {
    
    class Email : public TextProperty, public IEmail, HasAltId {
        
    public:
        const static std::string PROPERTYNAME;
        const static std::string CLASSNAME;
        
        typedef std::shared_ptr<Email> Ptr;
        ~Email();
        Email(const std::string& email);
        //public Email(Email original)
        
        std::vector<std::string> getTypes();
        std::vector<EmailType::Ptr> emailTypes();
        void addType(const std::string& type);
        void addType(const EmailType::Ptr& type);
        //public List<Pid> getPids();
        //public Integer getPref();
        //public void setPref(Integer pref);
        //public Email copy();
        
    protected:
        void _validate(std::list<ValidationWarning::Ptr>& warnings, const VCardVersion::Ptr& version, const std::shared_ptr<VCard>& vcard);
        
    protected: //override PMObject, HasAltId
        std::string _className() {
            return CLASSNAME;
        }
        
        std::string _getPropertyName() {
            return PROPERTYNAME;
        }
        
        std::string getAltId();
        void setAltId(const std::string& altId);
        
    public:
        std::string getParameter(const std::string & name) final;
        std::string getValue() final;
        std::string getGroup() final;
        void setGroup(const std::string & g) final;
    };
    
    
}

#endif /* email_hpp */
