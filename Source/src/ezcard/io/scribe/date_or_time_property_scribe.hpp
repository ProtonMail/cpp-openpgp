//
//  date_or_time_property_scribe.hpp
//  OpenPGP
//
//  Created by Yanfeng Zhang on 6/12/17.
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


#ifndef date_or_time_property_scribe_hpp
#define date_or_time_property_scribe_hpp

#include <stdio.h>
#include "vcard_property_scribe.hpp"
#include "date_or_time_property.hpp"
#include "vobject_property_values.hpp"

namespace ezvcard {
    
    
    /**
     * Marshals properties with date-time values.
     * @author Michael Angstadt
     * @param <T> the property class
     */
//    <T extends DateOrTimeProperty>
    template <class T>
    class DateOrTimePropertyScribe : public VCardPropertyScribeWrapper<T> {
        static_assert(std::is_base_of<DateOrTimeProperty, T>::value, "DateOrTimePropertyScribe<T>: T must be extent of DateOrTimeProperty type :-(");
    
    public:
        DateOrTimePropertyScribe(const std::string& propertyName) : VCardPropertyScribeWrapper<T>(propertyName) {

        }
        
    protected:
        virtual std::shared_ptr<T> _newInstance(const std::string& text) = 0;
        
        virtual std::shared_ptr<T> _newInstance(const std::string& date, bool hasTime) = 0;
//
//        virtual std::shared_ptr<T> _newInstance(PartialDate partialDate) = 0;
        
        
    private:
        std::shared_ptr<T> parse(const std::string& value, std::list<std::string>& warnings) {
            try {
                bool hasTime = false;
                std::size_t found = value.find("T");
                if (found!=std::string::npos)
                    hasTime = true;
                return _newInstance(value, hasTime);
            } catch (const std::exception& e) {
//                if (context.getVersion() == VCardVersion.V2_1 || context.getVersion() == VCardVersion.V3_0) {
//                    throw new CannotParseException(5);
//                }
//                
//                try {
//                    return newInstance(PartialDate.parse(value));
//                } catch (IllegalArgumentException e2) {
//                    context.addWarning(6);
//                    return newInstance(value);
//                }
            }
            return nullptr;
        }
        

    protected:
        
        virtual std::string _writeText(const std::shared_ptr<T>& property,
                                       const WriteContext::Ptr& context) final {
            auto version = context->getVersion();
            auto date = property->getDate();
            if (date != "") {
                return date;
            }
//            Date date = property->getDate(); //TODO::fix the date type later
//            if (date != null) {
//                boolean extended = (version == VCardVersion.V3_0);
//                return date(date).time(property.hasTime()).extended(extended).utc(false).write();
//            }
            
            if (version == VCardVersion::V4_0()) {
                auto text = property->getText();
                if (text != "") { //text != null
                    return VObjectPropertyValues::escape(text);
                }
                
                auto partialDate = property->getPartialDate();
                if (partialDate != "") {
                    return partialDate;
                }
                //TODO:: add partial date later
//                PartialDate partialDate = property.getPartialDate();
//                if (partialDate != null) { //partialDate != null
//                    return partialDate.toISO8601(false);
//                }
            }
            
            return "";
        }
        
        VCardDataType::Ptr _defaultDataType(const VCardVersion::Ptr& version) final {
            if (version == VCardVersion::V2_1() ||
                version == VCardVersion::V3_0()) {
                return nullptr;
            } else if (version == VCardVersion::V4_0()) {
                return VCardDataType::DATE_AND_OR_TIME;
            }
            return nullptr;
        }
        
        std::shared_ptr<T> _parseText(const std::string& value,
                                      const VCardDataType::Ptr& dataType,
                                      const VCardVersion::Ptr& version,
                                      const VCardParameters::Ptr& parameters,
                                      std::list<std::string> warnings) final {
            auto parsedValue = VObjectPropertyValues::unescape(value);
            if (version == VCardVersion::V4_0() && dataType == VCardDataType::TEXT) {
                return _newInstance(value);
            }
            return parse(value, warnings);
        }
        
  
        VCardDataType::Ptr _dataType(const std::shared_ptr<T>& property, const VCardVersion::Ptr& version) final {
            if (version == VCardVersion::V2_1() ||
                version == VCardVersion::V3_0()) {
                return nullptr;
            } else if (version == VCardVersion::V4_0()) {
                if (property->getText() != "") {
                    return VCardDataType::TEXT;
                }
                if (property->getDate() != "" || property->getPartialDate() != "") {
                    return property->hasTime() ? VCardDataType::DATE_TIME : VCardDataType::DATE;
                }
                return VCardDataType::DATE_AND_OR_TIME;
            }
            return nullptr;
        }
 



        
//        protected void _writeXml(T property, XCardElement parent);
//        protected T _parseXml(XCardElement element, VCardParameters parameters, ParseContext context);
//        protected T _parseHtml(HCardElement element, ParseContext context);
//        protected JCardValue _writeJson(T property);
//        protected T _parseJson(JCardValue value, VCardDataType dataType, VCardParameters parameters, ParseContext context);

    };
    
    
}


#endif /* date_or_time_property_scribe_hpp */
