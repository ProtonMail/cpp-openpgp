//
//  pm_custom_property.hpp
//  OpenPGP
//
//  Created by Yanfeng Zhang on 6/26/17.
//  Copyright © 2017 Yanfeng Zhang. All rights reserved.
//

#ifndef pm_encrypt_property_hpp
#define pm_encrypt_property_hpp

#include <stdio.h>
#include "text_property.hpp"
#include "has_alt_Id.hpp"
#include "i_p_m_encrypt.hpp"

namespace ezvcard {
    class PMEncrypt : public TextProperty, public IPMEncrypt, HasAltId {
        
    public:
        typedef std::shared_ptr<PMEncrypt> Ptr;
        const static std::string PROPERTYNAME;
        const static std::string CLASSNAME;
        
        /**
         * Creates a note property.
         * @param custom the note text
         */
        PMEncrypt(const std::string& custom) : TextProperty(custom) {
            
        }
        
        /**
         * Gets the TYPE parameter.
         * <p>
         * <b>Supported versions:</b> {@code 4.0}
         * </p>
         * @return the TYPE value (typically, this will be either "work" or "home")
         * or null if it doesn't exist
         */
        std::string getType() {
            return _parameters->getType();
        }
        
        
        
        /**
         * Sets the TYPE parameter.
         * <p>
         * <b>Supported versions:</b> {@code 4.0}
         * </p>
         * @param type the TYPE value (this should be either "work" or "home") or
         * null to remove
         */
        void setType(const std::string& type) {
            _parameters->setType(type);
        }
        
        std::string getValue() {
            return TextProperty::getValue();
        }
        
        std::string getGroup() final {
            return TextProperty::getGroup();
        }
        
        void setGroup(const std::string & g) final {
            TextProperty::setGroup(g);
        }
    protected:
        
        //
        //        /**
        //         * Copy constructor.
        //         * @param original the property to make a copy of
        //         */
        //        public Note(Note original) {
        //            super(original);
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
        //        public Note copy() {
        //            return new Note(this);
        //        }
        
    protected: //PMObject
        std::string _className();
        std::string _getPropertyName();
        
    protected: //impl HasAltId
        std::string getAltId();
        void setAltId(const std::string& altId);
    };
}

#endif /* pm_encrypt_property_hpp */
