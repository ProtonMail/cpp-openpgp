//
//  email_type.cpp
//  OpenPGP
//
//  Created by Yanfeng Zhang on 1/10/17.
//  Copyright © 2017 Yanfeng Zhang. All rights reserved.
//
#include "vcard_version.hpp"
#include "email_type.hpp"

VCardParameterCaseClasses<EmailType> EmailType::enums;

const EmailType::Ptr EmailType::INTERNET = std::shared_ptr<EmailType>(new EmailType(true, "internet", { VCardVersion::V21_V30() }, false));
const EmailType::Ptr EmailType::X400 = std::shared_ptr<EmailType>(new EmailType(true, "x400", { VCardVersion::V21_V30() }, false));
const EmailType::Ptr EmailType::PREF = std::shared_ptr<EmailType>(new EmailType(true, "pref", { VCardVersion::V21_V30() }, false));
const EmailType::Ptr EmailType::AOL = std::shared_ptr<EmailType>(new EmailType(true, "aol", { VCardVersion::V2_1() }, false));
const EmailType::Ptr EmailType::APPLELINK = std::shared_ptr<EmailType>(new EmailType(true, "applelink", { VCardVersion::V2_1() }, false));
const EmailType::Ptr EmailType::ATTMAIL = std::shared_ptr<EmailType>(new EmailType(true, "attmail", { VCardVersion::V2_1() }, false));
const EmailType::Ptr EmailType::CIS = std::shared_ptr<EmailType>(new EmailType(true, "cis", { VCardVersion::V2_1() }, false));
const EmailType::Ptr EmailType::EWORLD = std::shared_ptr<EmailType>(new EmailType(true, "eworld", { VCardVersion::V2_1() }, false));
const EmailType::Ptr EmailType::IBMMAIL = std::shared_ptr<EmailType>(new EmailType(true, "ibmmail", { VCardVersion::V2_1() }, false));
const EmailType::Ptr EmailType::MCIMAIL = std::shared_ptr<EmailType>(new EmailType(true, "mcimail", { VCardVersion::V2_1() }, false));
const EmailType::Ptr EmailType::POWERSHARE = std::shared_ptr<EmailType>(new EmailType(true, "powershare", { VCardVersion::V2_1() }, false));
const EmailType::Ptr EmailType::PRODIGY = std::shared_ptr<EmailType>(new EmailType(true, "prodigy", { VCardVersion::V2_1() }, false));
const EmailType::Ptr EmailType::TLX = std::shared_ptr<EmailType>(new EmailType(true, "tlx", { VCardVersion::V2_1() }, false));
const EmailType::Ptr EmailType::HOME = std::shared_ptr<EmailType>(new EmailType(true, "home", { VCardVersion::V4_0() }, false));
const EmailType::Ptr EmailType::WORK = std::shared_ptr<EmailType>(new EmailType(true, "work", { VCardVersion::V4_0() }, false));

EmailType::EmailType(const std::string& value, std::vector<VCardVersion::Ptr> support) : VCardParameter(value, support) {
    
}

EmailType::EmailType(const std::string& value, std::vector<VCardVersion::Ptr> support, bool preserveCase): VCardParameter(value, support, preserveCase) {
    
}

EmailType::EmailType(bool predefine, const std::string& value, std::vector<VCardVersion::Ptr> support, bool preserveCase) : VCardParameter(value, support, preserveCase) {
    if (predefine) {
        enums.setupPredefine(value, support, preserveCase);
    }
}

/**
 * Searches for a parameter value that is defined as a static constant in
 * this class.
 * @param value the parameter value
 * @return the object or null if not found
 */
EmailType::Ptr EmailType::find(const std::string& value) {
    return enums.find(value);
}

/**
 * Searches for a parameter value and creates one if it cannot be found. All
 * objects are guaranteed to be unique, so they can be compared with
 * {@code ==} equality.
 * @param value the parameter value
 * @return the object
 */
EmailType::Ptr EmailType::get(const std::string& value) {
    return enums.get(value);
}

/**
 * Gets all of the parameter values that are defined as static constants in
 * this class.
 * @return the parameter values
 */
std::vector<EmailType::Ptr> EmailType::all() {
    return enums.all();
}

bool operator==(const EmailType::Ptr& lhs, const EmailType::Ptr& rhs) {
    if (lhs == nullptr && lhs != rhs) {
        return false;
    }
    
    if (lhs->getValue() != rhs->getValue()) {
        return false;
    }
    return true;
}
