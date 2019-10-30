//
//  gender_scribe.hpp
//  OpenPGP
//
//  Created by Yanfeng Zhang on 1/12/18.
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


#ifndef gender_scribe_hpp
#define gender_scribe_hpp

#include <stdio.h>
#include "string_property_scribe.hpp"
#include "gender.hpp"


namespace ezvcard {
    
    /**
     * Marshals {@link Gender} properties.
     * @author Michael Angstadt
     */
    class GenderScribe : public VCardPropertyScribeWrapper<Gender> {
    public:
        typedef std::shared_ptr<GenderScribe> Ptr;
        
        GenderScribe();
        
        std::string _className() {
            return "GenderScribe";
        }
        
    protected:
        std::string _writeText(const Gender::Ptr& property, const WriteContext::Ptr& context) {
            StructuredValueBuilder builder;
            builder.append(property->getGender());
            builder.append(property->getText());
            return builder.build(false);
        }
        
        Gender::Ptr _parseText(const std::string& value,
                               const VCardDataType::Ptr& dataType,
                               const VCardVersion::Ptr& version,
                               const VCardParameters::Ptr& parameters,
                               std::list<std::string> warnings) {
            SemiStructuredValueIterator it(value, 2);
            std::string sex = it.next();
            if (!sex.empty()) {
                sex = str_to_upper(sex);
            }
            std::string text = it.next();
            
            auto gender = std::make_shared<Gender>(sex);
            gender->setText(text);
            return gender;
        }
        
        VCardDataType::Ptr _defaultDataType(const VCardVersion::Ptr& version) {
            return VCardDataType::TEXT;
        }


//
//        @Override
//        protected void _writeXml(Gender property, XCardElement parent) {
//            parent.append("sex", property.getGender());
//
//            String text = property.getText();
//            if (text != null) {
//                parent.append("identity", text);
//            }
//        }
//
//        @Override
//        protected Gender _parseXml(XCardElement element, VCardParameters parameters, ParseContext context) {
//            String sex = element.first("sex");
//            if (sex != null) {
//                Gender property = new Gender(sex);
//                property.setText(element.first("identity")); //optional field
//                return property;
//            }
//
//            throw missingXmlElements("sex");
//        }
//
//        @Override
//        protected JCardValue _writeJson(Gender property) {
//            String gender = property.getGender();
//            String text = property.getText();
//
//            if (text == null) {
//                return JCardValue.single(gender);
//            }
//            return JCardValue.structured(gender, text);
//        }
//
//        @Override
//        protected Gender _parseJson(JCardValue value, VCardDataType dataType, VCardParameters parameters, ParseContext context) {
//            StructuredValueIterator it = new StructuredValueIterator(value.asStructured());
//
//            String sex = it.nextValue();
//            if (sex != null) {
//                sex = sex.toUpperCase();
//            }
//            String text = it.nextValue();
//
//            Gender property = new Gender(sex);
//            property.setText(text);
//            return property;
//        }
    };
}

#endif /* gender_scribe_hpp */
