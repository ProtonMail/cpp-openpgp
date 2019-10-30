//
//  nick_name.cpp
//  OpenPGP
//
//  Created by Yanfeng Zhang on 1/10/17.
//  Copyright © 2017 Yanfeng Zhang. All rights reserved.
//

#include "nick_name.hpp"

namespace ProtonMail {
    
    std::shared_ptr<INickname> INickname::create_instance(const std::string &type, const std::string &value) {
        auto out = std::make_shared<ezvcard::Nickname>();
        out->addValue(value);
        out->setType(type);
        return out;
    }
}


namespace ezvcard {
    
    
    
    const std::string Nickname::PROPERTYNAME = "NICKNAME";
    const std::string Nickname::CLASSNAME = "Nickname";
    
    /**
     * Creates a title property.
     * @param title the title (e.g. "Team Lead")
     */
    Nickname::Nickname() : TextListProperty() {
        
    }
    
    
    std::string Nickname::_className() {
        return CLASSNAME;
    }
    
    std::string Nickname::_getPropertyName() {
        return PROPERTYNAME;
    }
    
    std::string Nickname::getAltId() {
        return _parameters->getAltId();
    }
    
    void Nickname::setAltId(const std::string& altId) {
        _parameters->setAltId(altId);
    }
    
    std::vector<VCardVersion::Ptr> Nickname::_getSupportedVersions() {
        return {VCardVersion::V3_0(), VCardVersion::V4_0() };
    }
    
    std::string Nickname::getNickname() {
        auto values = TextListProperty::getValues();
        if (values.size() > 0) {
            return values.front();
        }
        return "";
    }

//    public Nickname() {
//        //empty
//    }
//    
//    /**
//     * Copy constructor.
//     * @param original the property to make a copy of
//     */
//    public Nickname(Nickname original) {
//        super(original);
//    }
    
    /**
     * Gets the TYPE parameter.
     * <p>
     * <b>Supported versions:</b> {@code 4.0}
     * </p>
     * @return the TYPE value (typically, this will be either "work" or "home")
     * or null if it doesn't exist
     */
    std::string Nickname::getType() {
        return _parameters->getType();
    }
    
    std::vector<std::string> Nickname::getValues() {
        return TextListProperty::getValues();
    }
    
    void Nickname::setType(const std::string& type) {
        _parameters->setType(type);
    }
    
//    /**
//     * Sets the TYPE parameter.
//     * <p>
//     * <b>Supported versions:</b> {@code 4.0}
//     * </p>
//     * @param type the TYPE value (this should be either "work" or "home") or
//     * null to remove
//     */
//    public void setType(String type) {
//        parameters.setType(type);
//    }
//    
//    @Override
//    public String getLanguage() {
//        return super.getLanguage();
//    }
//    
//    @Override
//    public void setLanguage(String language) {
//        super.setLanguage(language);
//    }
//    
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
//    //@Override
//    public String getAltId() {
//        return parameters.getAltId();
//    }
//    
//    //@Override
//    public void setAltId(String altId) {
//        parameters.setAltId(altId);
//    }
//    
//    @Override
//    public Nickname copy() {
//        return new Nickname(this);
//    }
//}

}
