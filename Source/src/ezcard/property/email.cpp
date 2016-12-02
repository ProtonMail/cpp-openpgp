//
//  email.cpp
//  OpenPGP
//
//  Created by Yanfeng Zhang on 1/10/17.
//  Copyright © 2017 Yanfeng Zhang. All rights reserved.
//

#include "email.hpp"


namespace ProtonMail {
    
    std::shared_ptr<IEmail> IEmail::create_instance(const std::string & type, const std::string & email, const std::string& group) {
        auto out = std::make_shared<ezvcard::Email>(email);
        out->addType(type);
        out->setGroup(group);
        return out;
    }
}


namespace ezvcard {
    
    
    const std::string Email::PROPERTYNAME = "EMAIL";
    const std::string Email::CLASSNAME = "Email";
    
    Email::~Email() {
        
    }

    /**
     * Creates an email property.
     * @param email the email (e.g. "johndoe@example.com")
     */
    Email::Email(const std::string& name): TextProperty(name) {
        
    }

    //    /**
    //     * Copy constructor.
    //     * @param original the property to make a copy of
    //     */
    //    public Email(Email original) {
    //        super(original);
    //    }
    //
    
    std::vector<std::string> Email::getTypes() {
        return _parameters->getTypes();
    }
    
    
    void Email::addType(const std::string& type) {
        _parameters->addType(type);
    }
    
    
    void Email::addType(const EmailType::Ptr& type) {
        _parameters->addType(type->getValue());
    }
    
    /**
     * Gets the list that stores this property's email types (TYPE parameters).
     * @return the email types (this list is mutable) (e.g. "INTERNET", "WORK")
     */
    std::vector<EmailType::Ptr> Email::emailTypes() {
        std::vector<EmailType::Ptr> out;
        auto types = getTypes();
        for (auto t : types) {
            out.push_back(EmailType::get(t));
        }
        return out;
    }
    
    std::string Email::getGroup() {
        return TextProperty::getGroup();
    }
    
    void Email::setGroup(const std::string &g) {
        TextProperty::setGroup(g);
    }
    
    
    //    @Override
    //    public List<Pid> getPids() {
    //        return super.getPids();
    //    }
    //
    //    @Override
    //    public Integer getPref() {
    //        return super.getPref();
    //    }
    //
    //    @Override
    //    public void setPref(Integer pref) {
    //        super.setPref(pref);
    //    }
    //
    //    @Override
    //    protected void _validate(List<ValidationWarning> warnings, VCardVersion version, VCard vcard) {
    //        super._validate(warnings, version, vcard);
    //
    //        for (EmailType type : getTypes()) {
    //            if (type == EmailType.PREF) {
    //                //ignore because it is converted to a PREF parameter for 4.0 vCards
    //                continue;
    //            }
    //            if (!type.isSupportedBy(version)) {
    //                warnings.add(new ValidationWarning(9, type.getValue()));
    //            }
    //        }
    //    }
    //
    //    @Override
    //    public Email copy() {
    //        return new Email(this);
    //    }
    
    
    void Email::_validate(std::list<ValidationWarning::Ptr>& warnings, const VCardVersion::Ptr& version, const std::shared_ptr<VCard>& vcard) {
        TextProperty::_validate(warnings, version, vcard);
        for (auto type : emailTypes()) {
            if (type == EmailType::PREF) {
                //ignore because it is converted to a PREF parameter for 4.0 vCards
                continue;
            }
            if (!type->isSupportedBy(version)) {
                warnings.push_back(std::make_shared<ValidationWarning>(9, type->getValue()));
            }
        }
    }
    
    //
    std::string Email::getAltId() {
        return _parameters->getAltId();
    }
    
    void Email::setAltId(const std::string& altId) {
        return _parameters->setAltId(altId);
    }
    
    std::string Email::getParameter(const std::string & name) {
        return TextProperty::getParameter(name);
    }
    
    std::string Email::getValue() {
        return TextProperty::getValue();
    }
}
