//
//  raw_property_scribe.hpp
//  OpenPGP
//
//  Created by Yanfeng Zhang on 1/12/17.
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
