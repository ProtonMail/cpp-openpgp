//
//  title.cpp
//  OpenPGP
//
//  Created by Yanfeng Zhang on 1/10/17.
//  Copyright © 2017 Yanfeng Zhang. All rights reserved.
//

#include "title.hpp"


namespace ProtonMail {
    
    std::shared_ptr<ITitle> ITitle::create_instance(const std::string &type, const std::string &value) {
        auto out = std::make_shared<ezvcard::Title>(value);
        out->setType(type);
        return out;
    }
}

namespace ezvcard {
    const std::string Title::PROPERTYNAME = "TITLE";
    const std::string Title::CLASSNAME = "Title";

    /**
     * Creates a title property.
     * @param title the title (e.g. "Team Lead")
     */
    Title::Title(const std::string& title) : TextProperty(title) {
        
    }
//
///**
// * Copy constructor.
// * @param original the property to make a copy of
// */
//public Title(Title original) {
//    super(original);
//}
//
//@Override
//public String getLanguage() {
//    return super.getLanguage();
//}
//
//@Override
//public void setLanguage(String language) {
//    super.setLanguage(language);
//}
    
    /**
     * Gets the TYPE parameter.
     * <p>
     * <b>Supported versions:</b> {@code 4.0}
     * </p>
     * @return the TYPE value (typically, this will be either "work" or "home")
     * or null if it doesn't exist
     */
    std::string Title::getType() {
        return _parameters->getType();
    }
    
    void Title::setType(const std::string& type) {
        _parameters->setType(type);
    }
    
    std::string Title::getTitle() {
        return TextProperty::getValue();
    }
    
///**
// * Sets the TYPE parameter.
// * <p>
// * <b>Supported versions:</b> {@code 4.0}
// * </p>
// * @param type the TYPE value (this should be either "work" or "home") or
// * null to remove
// */
//public void setType(String type) {
//    parameters.setType(type);
//}
//
//@Override
//public List<Pid> getPids() {
//    return super.getPids();
//}
//
//@Override
//public Integer getPref() {
//    return super.getPref();
//}
//
//@Override
//public void setPref(Integer pref) {
//    super.setPref(pref);
//}
//
////@Override
//public String getAltId() {
//    return parameters.getAltId();
//}
//
////@Override
//public void setAltId(String altId) {
//    parameters.setAltId(altId);
//}
//
//@Override
//public Title copy() {
//    return new Title(this);
//}
//        //@Override
//        public String getAltId() {
//            return parameters.getAltId();
//        }
//
//        //@Override
//        public void setAltId(String altId) {
//            parameters.setAltId(altId);
//        }
    
    
    std::string Title::_className() {
        return CLASSNAME;
    }
    std::string Title::_getPropertyName() {
        return PROPERTYNAME;
    }
    
    std::string Title::getAltId() {
        return _parameters->getAltId();
    }
    void Title::setAltId(const std::string& altId) {
        _parameters->setAltId(altId);
    }
}
