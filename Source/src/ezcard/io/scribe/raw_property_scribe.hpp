//
//  raw_property_scribe.hpp
//  OpenPGP
//
//  Created by Yanfeng Zhang on 1/12/17.
//  Copyright © 2017 Yanfeng Zhang. All rights reserved.
//

#ifndef raw_property_scribe_hpp
#define raw_property_scribe_hpp

#include <stdio.h>

#include "vcard_property_scribe.hpp"
#include "raw_property.hpp"


namespace ezvcard {
    

class RawPropertyScribe : public VCardPropertyScribeWrapper<RawProperty> {
    
public:
    typedef std::shared_ptr<RawPropertyScribe> Ptr;
    
    RawPropertyScribe(const std::string& propertyName) : VCardPropertyScribeWrapper(propertyName)  {
    }

    
protected:
    VCardDataType::Ptr _defaultDataType(const VCardVersion::Ptr& version) {
        return nullptr;
    }

    std::string _writeText(const RawProperty::Ptr& property, const WriteContext::Ptr& context) {
        auto value = property->getValue();
        return value;
    }

    RawProperty::Ptr _parseText(const std::string& value,
                                const VCardDataType::Ptr& dataType,
                                const VCardVersion::Ptr& version,
                                const VCardParameters::Ptr& parameters,
                                std::list<std::string> warnings) {
        auto property = std::make_shared<RawProperty>(_getPropertyName(), value);
        property->setDataType(dataType);
        return property;
    }
//
//    @Override
//    protected RawProperty _parseXml(XCardElement element, VCardParameters parameters, List<String> warnings) {
//    @Override
//    protected RawProperty _parseJson(JCardValue value, VCardDataType dataType, VCardParameters parameters, List<String> warnings) {
//    @Override
//    protected RawProperty _parseHtml(HCardElement element, List<String> warnings) {
//    private static String jcardValueToString(JCardValue value) {

    
    std::string _className() {
        return "RawPropertyScribe";
    }
};

}
    
#endif /* raw_property_scribe_hpp */
