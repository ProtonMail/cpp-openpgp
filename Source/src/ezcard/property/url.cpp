//
//  url.cpp
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
