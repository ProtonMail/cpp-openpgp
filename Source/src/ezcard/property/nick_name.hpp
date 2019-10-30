//
//  nick_name.hpp
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


#ifndef nick_name_hpp
#define nick_name_hpp

#include <stdio.h>
#include "text_list_property.hpp"
#include "has_alt_Id.hpp"
#include "i_nickname.hpp"

namespace ezvcard {
    
    /**
     * <p>
     * Defines the person's nicknames.
     * </p>
     *
     * <p>
     * <b>Code sample</b>
     * </p>
     *
     * <pre class="brush:java">
     * VCard vcard = new VCard();
     *
     * Nickname nickname = new Nickname();
     * nickname.getValues().add("Ricky");
     * nickname.getValues().add("Bobby");
     * nickname.getValues().add("Ricky Bobby");
     * vcard.setNickname(nickname);
     * </pre>
     *
     * <p>
     * <b>Property name:</b> {@code NICKNAME}
     * </p>
     * <p>
     * <b>Supported versions:</b> {@code 3.0, 4.0}
     * </p>
     * @author Michael Angstadt
     * @see <a href="http://tools.ietf.org/html/rfc6350#page-29">RFC 6350 p.29</a>
     * @see <a href="http://tools.ietf.org/html/rfc2426#page-9">RFC 2426 p.9</a>
     */
//    @SupportedVersions({ VCardVersion.V3_0, VCardVersion.V4_0 })
    class Nickname : public TextListProperty, public INickname, HasAltId {
    public:
        typedef std::shared_ptr<Nickname> Ptr;
        const static std::string PROPERTYNAME;
        const static std::string CLASSNAME;
        
        Nickname();
        std::string getType();
        void setType(const std::string& type);
        std::string getNickname();
        
    protected: //PMObject
        std::string _className();
        std::string _getPropertyName();
        
    protected: //impl HasAltId
        std::string getAltId();
        void setAltId(const std::string& altId);
        
    protected: //TextListProperty : VCardProperty
        std::vector<VCardVersion::Ptr> _getSupportedVersions();
        
    public: //INickname
        std::vector<std::string> getValues();
        
        
//        /**
//         * Copy constructor.
//         * @param original the property to make a copy of
//         */
//        public Nickname(Nickname original) {
//            super(original);
//        }

//        
//        /**
//         * Sets the TYPE parameter.
//         * <p>
//         * <b>Supported versions:</b> {@code 4.0}
//         * </p>
//         * @param type the TYPE value (this should be either "work" or "home") or
//         * null to remove
//         */
//        public void setType(String type) {
//            parameters.setType(type);
//        }
//        
//        @Override
//        public String getLanguage() {
//            return super.getLanguage();
//        }
//        
//        @Override
//        public void setLanguage(String language) {
//            super.setLanguage(language);
//        }
//        
//        @Override
//        public List<Pid> getPids() {
//            return super.getPids();
//        }
//        
//        @Override
//        public Integer getPref() {
//            return super.getPref();
//        }
//        
//        @Override
//        public void setPref(Integer pref) {
//            super.setPref(pref);
//        }
//        
//        //@Override
//        public String getAltId() {
//            return parameters.getAltId();
//        }
//        
//        //@Override
//        public void setAltId(String altId) {
//            parameters.setAltId(altId);
//        }
//        
//        @Override
//        public Nickname copy() {
//            return new Nickname(this);
//        }
    };
}


#endif /* nick_name_hpp */
