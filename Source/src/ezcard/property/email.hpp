//
//  email.hpp
//  OpenPGP
//
//  Created by Yanfeng Zhang on 1/10/17.
//  Copyright © 2017 Yanfeng Zhang. All rights reserved.
//

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
