//
//  url.cpp
//  OpenPGP
//
//  Created by Yanfeng Zhang on 1/10/17.
//  Copyright © 2017 Yanfeng Zhang. All rights reserved.
//

#include "url.hpp"


namespace ProtonMail {
    
    std::shared_ptr<IUrl> IUrl::create_instance(const std::string & type, const std::string & value) {
        auto out = std::make_shared<ezvcard::Url>(value);
        out->setType(type);
        return out;
    }
}

namespace ezvcard {
    
    const std::string Url::PROPERTYNAME = "URL";
    const std::string Url::CLASSNAME = "Url";
    
    
    std::string Url::getAltId() {
        return _parameters->getAltId();
    }
    
    void Url::setAltId(const std::string& altId) {
        _parameters->setAltId(altId);
    }
    
    std::string Url::getValue() {
        return UriProperty::getValue();
    }
    
    std::string Url::getType() {
        return _parameters->getType();
    }
    
    void Url::setType(const std::string& type) {
        _parameters->setType(type);
    }
    
}




//    /**
//     * Copy constructor.
//     * @param original the property to make a copy of
//     */
//    public Url(Url original) {
//        super(original);
//    }
//
//    /**
//     * Gets the MEDIATYPE parameter.
//     * <p>
//     * <b>Supported versions:</b> {@code 4.0}
//     * </p>
//     * @return the media type or null if not set
//     */
//    public String getMediaType() {
//        return parameters.getMediaType();
//    }
//
//    /**
//     * Sets the MEDIATYPE parameter.
//     * <p>
//     * <b>Supported versions:</b> {@code 4.0}
//     * </p>
//     * @param mediaType the media type or null to remove
//     */
//    public void setMediaType(String mediaType) {
//        parameters.setMediaType(mediaType);
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

//
//    /**
//     * Gets the TYPE parameter.
//     * <p>
//     * <b>Supported versions:</b> {@code 4.0*}
//     * </p>
//     *
//     * <p>
//     * <i>* Some mail clients will add this parameter to URL properties in 2.1
//     * and 3.0 vCards, however.</i>
//     * </p>
//     *
//     * @return the TYPE value (typically, this will be either "work" or "home")
//     * or null if it doesn't exist
//     */
//    public String getType() {
//        return parameters.getType();
//    }
//
//    /**
//     * Sets the TYPE parameter.
//     * <p>
//     * <b>Supported versions:</b> {@code 4.0*}
//     * </p>
//     *
//     * <p>
//     * <i>* Some mail clients will add this parameter to URL properties in 2.1
//     * and 3.0 vCards, however.</i>
//     * </p>
//     * @param type the TYPE value (this should be either "work" or "home") or
//     * null to remove
//     */
//    public void setType(String type) {
//        parameters.setType(type);
//    }
//
//    @Override
//    public Url copy() {
//        return new Url(this);
//    }
