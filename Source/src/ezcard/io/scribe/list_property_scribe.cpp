//
//  list_property_scribe.cpp
//  OpenPGP
//
//  Created by Yanfeng Zhang on 6/23/17.
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


#include "list_property_scribe.hpp"



namespace ezvcard {
    
//    
//    /**
//     * Marshals properties that contain a list of values.
//     * @param <T> the property class
//     * @author Michael Angstadt
//     */
//    public abstract class ListPropertyScribe<T extends TextListProperty> extends VCardPropertyScribe<T> {
//        public ListPropertyScribe(Class<T> clazz, String propertyName) {
//            super(clazz, propertyName);
//        }
//        
//        @Override
//        protected VCardDataType _defaultDataType(VCardVersion version) {
//            return VCardDataType.TEXT;
//        }
//        
//        @Override
//        protected String _writeText(T property, WriteContext context) {
//            return VObjectPropertyValues.writeList(property.getValues());
//        }
//        
//        @Override
//        protected T _parseText(String value, VCardDataType dataType, VCardParameters parameters, ParseContext context) {
//            List<String> values = VObjectPropertyValues.parseList(value);
//            return parse(values);
//        }
//        
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
//        
//        private T parse(List<String> values) {
//            T property = _newInstance();
//            property.getValues().addAll(values);
//            return property;
//        }
//        
//        protected abstract T _newInstance();
//    }
//    
}
