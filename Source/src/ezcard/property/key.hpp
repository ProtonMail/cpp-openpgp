//
//  key.hpp
//  OpenPGP
//
//  Created by Yanfeng Zhang on 1/10/17.
//  Copyright © 2017 Yanfeng Zhang. All rights reserved.
//

#ifndef key_hpp
#define key_hpp


#include <stdio.h>
#include <string>
#include <list>

#include "binary_property.hpp"
#include "key_type.hpp"
#include "has_alt_Id.hpp"
#include "vcard.hpp"
#include "i_key.hpp"
#include "vcard_version.hpp"

//@SupportedVersions(VCardVersion.V4_0)
namespace ezvcard {
    
    class Key : public BinaryProperty<KeyType>, public IKey {
        
    public:
        const static std::string PROPERTYNAME;
        const static std::string CLASSNAME;
        
        typedef std::shared_ptr<Key> Ptr;
        
        Key() : BinaryProperty("", nullptr, false) {
            
        }
       
        //Key(InputStream in, KeyType type);
        //Key(File file, KeyType type);
        //Key(Key original);
        Key(const std::string& url, const KeyType::Ptr& type, bool isBinary) : BinaryProperty(url, type, isBinary) {
           
        }
        
        /**
         * Sets a plain text representation of the key.
         * @param text the key in plain text
         * @param type the key type
         */
        void setText(const std::string& text, const KeyType::Ptr& type) {
            _text = text;
            _data = "";
            _url = "";
            setContentType(type);
        }
        

       
        void setUrl(const std::string& url, const KeyType::Ptr& type) {
            BinaryProperty::setUrl(url, type);
            _text = "";
        }

        void setData(const std::string& data, const KeyType::Ptr& type) {
            BinaryProperty::setData(data, type);
            _text = "";
        }
        
    protected:
        
        void _validate(std::list<ValidationWarning::Ptr>& warnings, const VCardVersion::Ptr& version, const std::shared_ptr<VCard>& vcard) {
            if (_url == "" && _data == "" && _text == "") {
                warnings.push_back(std::make_shared<ValidationWarning>(8));
            }
            if (_url != "" && (version == VCardVersion::V2_1() || version == VCardVersion::V3_0())) {
                warnings.push_back(std::make_shared<ValidationWarning>(15));
            }
        }

//        @Override
//        protected Map<String, Object> toStringValues() {
//            Map<String, Object> values = super.toStringValues();
//            values.put("text", text);
//            return values;
//        }
//
//        @Override
//        public Key copy() {
//            return new Key(this);
//        }
//
//        @Override
//        public int hashCode() {
//            final int prime = 31;
//            int result = super.hashCode();
//            result = prime * result + ((text == null) ? 0 : text.hashCode());
//            return result;
//        }
//
//        @Override
//        public boolean equals(Object obj) {
//            if (this == obj) return true;
//            if (!super.equals(obj)) return false;
//            Key other = (Key) obj;
//            if (text == null) {
//                if (other.text != null) return false;
//            } else if (!text.equals(other.text)) return false;
//            return true;
//        }
        
    private:
        std::string _text = "";
        
        std::string _className() {
            return Key::CLASSNAME;
        }
        std::string _getPropertyName() {
            return Key::PROPERTYNAME;
        }
        
    public:
        /**
         * Gets the plain text representation of the key.
         * @return the key in plain text
         */
        std::string getText() final {
            return _text;
        }
        
        void setText(const std::string & text) final {
            setText(text, KeyType::PGP);
        }
        
        std::vector<uint8_t> getBinary() final {
            auto data = BinaryProperty::getData();
            std::vector<uint8_t> out_vector(data.begin(), data.end());
            return out_vector;
        }
        
        void setBinary(const std::vector<uint8_t> & data) final {
            std::string key = std::string(data.begin(), data.end());
            setData(key, KeyType::PGP);
        }
        
        std::string getGroup() final {
            return BinaryProperty::getGroup();
        }
        
        void setGroup(const std::string & g) final {
            BinaryProperty::setGroup(g);
        }
        
        int32_t getPref() final {
            return _parameters->getPref();
        }
        
        void setPref(int32_t pref) final {
            _parameters->setPref(pref);
        }
        
        
    };
}


#endif /* key_hpp */
