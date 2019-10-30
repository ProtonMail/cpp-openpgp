//
//  simple_property_scribe.hpp
//  OpenPGP
//
//  Created by Yanfeng Zhang on 1/11/17.
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


#ifndef simple_property_scribe_hpp
#define simple_property_scribe_hpp

#include <stdio.h>
#include "vcard_property_scribe.hpp"
#include "vcard_data_type.hpp"
#include "vobject_property_values.hpp"

namespace ezvcard {


template <class T>
class SimplePropertyScribe : public VCardPropertyScribeWrapper<T> {
    static_assert(std::is_base_of<VCardProperty, T>::value, "SimplePropertyScribe<T>: T must be extent of VCardProperty type :-(");
protected:
    VCardDataType::Ptr _dataType;
    virtual std::shared_ptr<T> _parseValue(const std::string& value) = 0;
    virtual std::string _writeValue(const std::shared_ptr<T>& property) = 0;
    
public:
    SimplePropertyScribe(const std::string& propertyName, const VCardDataType::Ptr& dataType) : VCardPropertyScribeWrapper<T>(propertyName) {
        _dataType = dataType;
    }
    
protected:
    VCardDataType::Ptr _defaultDataType(const VCardVersion::Ptr& version) {
            return _dataType;
    }
    std::string _writeText(const std::shared_ptr<T>& property, const WriteContext::Ptr& context) {
        std::string value = _writeValue(property);
        return VCardPropertyScribe::escape(value, context);
    }

    std::shared_ptr<T> _parseText(const std::string& value,
                            const VCardDataType::Ptr& dataType,
                            const VCardVersion::Ptr& version,
                            const VCardParameters::Ptr& parameters,
                            std::list<std::string> warnings) {
        auto post_value = VObjectPropertyValues::unescape(value);
        auto obj = _parseValue(post_value);
        return obj;
    }
    
    //    @Override
    //    protected void _writeXml(T property, XCardElement parent) {
    //        parent.append(dataType, _writeValue(property));
    //    }
    //
    //    @Override
    //    protected T _parseXml(XCardElement element, VCardParameters parameters, List<String> warnings) {
    //        String value = element.first(dataType);
    //        if (value != null) {
    //            return _parseValue(value);
    //        }
    //
    //        throw super.missingXmlElements(dataType);
    //    }
    //
    //    @Override
    //    protected T _parseHtml(HCardElement element, List<String> warnings) {
    //        String value = element.value();
    //        return _parseValue(value);
    //    }
    //
    //    @Override
    //    protected JCardValue _writeJson(T property) {
    //        String value = _writeValue(property);
    //        if (value == null) {
    //            value = "";
    //        }
    //
    //        return JCardValue.single(value);
    //    }
    //
    //    @Override
    //    protected T _parseJson(JCardValue value, VCardDataType dataType, VCardParameters parameters, List<String> warnings) {
    //        String valueStr = value.asSingle();
    //        return _parseValue(valueStr);
    //    }
    //
    //    /**
    //     * Writes the property value to a string.
    //     * @param property the property to write
    //     * @return the property value
    //     */
    //    protected abstract String _writeValue(T property);
    //    

};

}
#endif /* simple_property_scribe_hpp */
