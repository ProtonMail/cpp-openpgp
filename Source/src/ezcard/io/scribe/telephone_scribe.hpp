//
//  telephone_scribe.hpp
//  OpenPGP
//
//  Created by Yanfeng Zhang on 6/3/17.
//  Copyright © 2017 Yanfeng Zhang. All rights reserved.
//

#ifndef telephone_scribe_hpp
#define telephone_scribe_hpp

#include <stdio.h>
#include "vcard_property_scribe.hpp"
#include "telephone.hpp"
#include "vobject_property_values.hpp"
#include "tel_uri.hpp"
#include "vcard_version.hpp"

namespace ezvcard {
    
    /**
     * Marshals {@link Telephone} properties.
     * @author Michael Angstadt
     */
    class TelephoneScribe : public VCardPropertyScribeWrapper<Telephone> {
        
    public:
        typedef std::shared_ptr<TelephoneScribe> Ptr;
        
        TelephoneScribe() : VCardPropertyScribeWrapper(Telephone::PROPERTYNAME) {
            
        }
        
        
    private:
        Telephone::Ptr parse(const std::string& value, const VCardDataType::Ptr& dataType, std::list<std::string>& warnings) {
            try {
                return std::make_shared<Telephone>(TelUri::parse(value));
            } catch (const std::invalid_argument& e) {
                if (dataType == VCardDataType::URI) {
                    warnings.push_back("18");
                }
            }
            return std::make_shared<Telephone>(value);
        }
        
        
    protected:
        VCardDataType::Ptr _defaultDataType(const VCardVersion::Ptr& version) {
            return VCardDataType::TEXT;
        }
        
        VCardDataType::Ptr _dataType(const Telephone::Ptr& property, const VCardVersion::Ptr& version) {
            if (version == VCardVersion::V4_0()) {
                if (property->getText() != "") {
                    return VCardDataType::TEXT;
                }
                if (property->getUri() != nullptr) {
                    return VCardDataType::URI;
                }
            }
            return VCardDataType::TEXT;
        }
        
        void _prepareParameters(const Telephone::Ptr& property, const VCardParameters::Ptr& copy, const VCardVersion::Ptr& version, const VCard::Ptr& vcard) {
            handlePrefParam(property, copy, version, vcard);
        }
        std::string _writeText(const Telephone::Ptr& property, const WriteContext::Ptr& context) {
            std::string text = property->getText();
            if (text != "") {
                return escape(text, context);
            }
            
            TelUri::Ptr uri = property->getUri();
            if (uri != nullptr) {
                if (context->getVersion() == VCardVersion::V4_0()) {
                    return uri->toString();
                }

                std::string ext = uri->getExtension();
                std::string value = (ext == "") ? uri->getNumber() : uri->getNumber() + " x" + ext;
                return escape(value, context);
            }
            return "";
        }
        
        
        Telephone::Ptr _parseText(const std::string& value,
                                      const VCardDataType::Ptr& dataType,
                                      const VCardVersion::Ptr& version,
                                      const VCardParameters::Ptr& parameters,
                                      std::list<std::string> warnings) {
            auto escapedValue = VObjectPropertyValues::unescape(value);
            return parse(escapedValue, dataType, warnings);
        }
        
        //protected void _writeXml(Telephone property, XCardElement parent) {
        //protected Telephone _parseXml(XCardElement element, VCardParameters parameters, ParseContext context) {
        //protected Telephone _parseHtml(HCardElement element, ParseContext context) {
        //protected JCardValue _writeJson(Telephone property) {
        //protected Telephone _parseJson(JCardValue value, VCardDataType dataType, VCardParameters parameters, ParseContext context) {
        
        
        std::string _className() {
            return "TelephoneScribe";
        }
    };
    
    
    
}

#endif /* telephone_scribe_hpp */
