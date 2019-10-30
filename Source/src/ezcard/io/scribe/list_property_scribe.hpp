//
//  list_property_scribe.hpp
//  OpenPGP
//
//  Created by Yanfeng Zhang on 6/23/17.
//  Copyright © 2017 Yanfeng Zhang. All rights reserved.
//

#ifndef list_property_scribe_hpp
#define list_property_scribe_hpp

#include <stdio.h>
#include "vcard_property_scribe.hpp"
#include "vobject_property_values.hpp"


namespace ezvcard {
    
    
    /**
     * Marshals properties that contain a list of values.
     * @param <T> the property class
     * @author Michael Angstadt
     */
    template <class T>
    class ListPropertyScribe : public VCardPropertyScribeWrapper<T> {
        static_assert(std::is_base_of<TextListProperty, T>::value, "ListPropertyScribe<T>: T must be extent of TextListProperty type :-(");
        
    public:
        ListPropertyScribe(const std::string& propertyName) : VCardPropertyScribeWrapper<T>(propertyName) {
            
        }
        
    protected:
        virtual std::shared_ptr<T> _newInstance() = 0;
        
        VCardDataType::Ptr _defaultDataType(const VCardVersion::Ptr& version) {
            return VCardDataType::TEXT;
        }
        
        std::string _writeText(const std::shared_ptr<T>& property, const WriteContext::Ptr& context) {
            return VObjectPropertyValues::writeList(property->getValues());
        }
        
        std::shared_ptr<T> _parseText(const std::string& value,
                                      const VCardDataType::Ptr& dataType,
                                      const VCardVersion::Ptr& version,
                                      const VCardParameters::Ptr& parameters,
                                      std::list<std::string> warnings) {
            auto values = VObjectPropertyValues::parseList(value);
            return parse(values);
        }
        
        //        @Override
        //        protected void _writeXml(T property, XCardElement parent) {
        //            parent.append(VCardDataType.TEXT.getName().toLowerCase(), property.getValues());
        //        }
        //
        //        @Override
        //        protected T _parseXml(XCardElement element, VCardParameters parameters, ParseContext context) {
        //            List<String> values = element.all(VCardDataType.TEXT);
        //            if (!values.isEmpty()) {
        //                return parse(values);
        //            }
        //
        //            throw missingXmlElements(VCardDataType.TEXT);
        //        }
        //
        //        @Override
        //        protected JCardValue _writeJson(T property) {
        //            List<String> values = property.getValues();
        //            if (values.isEmpty()) {
        //                return JCardValue.single("");
        //            }
        //
        //            return JCardValue.multi(values);
        //        }
        //
        //        @Override
        //        protected T _parseJson(JCardValue value, VCardDataType dataType, VCardParameters parameters, ParseContext context) {
        //            List<String> values = value.asMulti();
        //            return parse(values);
        //        }
        
        
    private:
        std::shared_ptr<T> parse(const std::vector<std::string>& values) {
            auto property = _newInstance();
            property->addValues(values);
            return property;
        }
        
    };
    
}



#endif /* list_property_scribe_hpp */
