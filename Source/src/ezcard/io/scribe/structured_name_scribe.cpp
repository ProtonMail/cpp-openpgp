//
//  structured_name_scribe.cpp
//  OpenPGP
//
//  Created by Yanfeng Zhang on 5/30/17.
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


#include "structured_name_scribe.hpp"


namespace ezvcard {
    

StructuredNameScribe::StructuredNameScribe() : VCardPropertyScribeWrapper(StructuredName::PROPERTYNAME) {

}

//
//
///**
// * Marshals {@link StructuredName} properties.
// * @author Michael Angstadt
// */
//public class StructuredNameScribe extends VCardPropertyScribe<StructuredName> {
//    public StructuredNameScribe() {
//        super(StructuredName.class, "N");
//    }
//    
//    @Override
//    protected VCardDataType _defaultDataType(VCardVersion version) {
//        return VCardDataType.TEXT;
//    }
//    
//    @Override
//    protected String _writeText(StructuredName property, WriteContext context) {
//        /*
//         * StructuredValueBuilder cannot be used with 2.1 because it escapes
//         * comma characters. For example, if someone's last name is "Foo,bar",
//         * the comma character must NOT be escaped when written to a 2.1 vCard.
//         *
//         * The reason commas are not escaped in 2.1 is because 2.1 does not
//         * allow multi-valued components like 3.0 and 4.0 do (for example,
//         * multiple suffixes).
//         *
//         * If a StructuredName object has multi-valued components, and it is
//         * being written to a 2.1 vCard, then ez-vcard will comma-delimit them
//         * to prevent data loss. But this is not part of the 2.1 syntax.
//         */
//        if (context.getVersion() == VCardVersion.V2_1) {
//            SemiStructuredValueBuilder builder = new SemiStructuredValueBuilder();
//            builder.append(property.getFamily());
//            builder.append(property.getGiven());
//            builder.append(join(property.getAdditionalNames(), ","));
//            builder.append(join(property.getPrefixes(), ","));
//            builder.append(join(property.getSuffixes(), ","));
//            return builder.build(false, context.isIncludeTrailingSemicolons());
//        } else {
//            StructuredValueBuilder builder = new StructuredValueBuilder();
//            builder.append(property.getFamily());
//            builder.append(property.getGiven());
//            builder.append(property.getAdditionalNames());
//            builder.append(property.getPrefixes());
//            builder.append(property.getSuffixes());
//            return builder.build(context.isIncludeTrailingSemicolons());
//        }
//    }
//    
//    @Override
//    protected StructuredName _parseText(String value, VCardDataType dataType, VCardParameters parameters, ParseContext context) {
//        StructuredName property = new StructuredName();
//        
//        if (context.getVersion() == VCardVersion.V2_1) {
//            /*
//             * 2.1 does not recognize multi-valued components.
//             */
//            SemiStructuredValueIterator it = new SemiStructuredValueIterator(value);
//            property.setFamily(it.next());
//            property.setGiven(it.next());
//            
//            String next = it.next();
//            if (next != null) {
//                property.getAdditionalNames().add(next);
//            }
//            
//            next = it.next();
//            if (next != null) {
//                property.getPrefixes().add(next);
//            }
//            
//            next = it.next();
//            if (next != null) {
//                property.getSuffixes().add(next);
//            }
//        } else {
//            StructuredValueIterator it = new StructuredValueIterator(value);
//            property.setFamily(it.nextValue());
//            property.setGiven(it.nextValue());
//            property.getAdditionalNames().addAll(it.nextComponent());
//            property.getPrefixes().addAll(it.nextComponent());
//            property.getSuffixes().addAll(it.nextComponent());
//        }
//        
//        return property;
//    }
//    
//    @Override
//    protected void _writeXml(StructuredName property, XCardElement parent) {
//        parent.append("surname", property.getFamily()); //the XML element still needs to be printed if value == null
//        parent.append("given", property.getGiven());
//        parent.append("additional", property.getAdditionalNames());
//        parent.append("prefix", property.getPrefixes());
//        parent.append("suffix", property.getSuffixes());
//    }
//    
//    @Override
//    protected StructuredName _parseXml(XCardElement element, VCardParameters parameters, ParseContext context) {
//        StructuredName property = new StructuredName();
//        
//        property.setFamily(s(element.first("surname")));
//        property.setGiven(s(element.first("given")));
//        property.getAdditionalNames().addAll(element.all("additional"));
//        property.getPrefixes().addAll(element.all("prefix"));
//        property.getSuffixes().addAll(element.all("suffix"));
//        
//        return property;
//    }
//    
//    private static String s(String value) {
//        return (value == null || value.length() == 0) ? null : value;
//    }
//    
//    @Override
//    protected StructuredName _parseHtml(HCardElement element, ParseContext context) {
//        StructuredName property = new StructuredName();
//        
//        property.setFamily(s(element.firstValue("family-name")));
//        property.setGiven(s(element.firstValue("given-name")));
//        property.getAdditionalNames().addAll(element.allValues("additional-name"));
//        property.getPrefixes().addAll(element.allValues("honorific-prefix"));
//        property.getSuffixes().addAll(element.allValues("honorific-suffix"));
//        
//        return property;
//    }
//    
//    @Override
//    protected JCardValue _writeJson(StructuredName property) {
//        return JCardValue.structured(property.getFamily(), property.getGiven(), property.getAdditionalNames(), property.getPrefixes(), property.getSuffixes());
//    }
//    
//    @Override
//    protected StructuredName _parseJson(JCardValue value, VCardDataType dataType, VCardParameters parameters, ParseContext context) {
//        StructuredName property = new StructuredName();
//        StructuredValueIterator it = new StructuredValueIterator(value.asStructured());
//        
//        property.setFamily(it.nextValue());
//        property.setGiven(it.nextValue());
//        property.getAdditionalNames().addAll(it.nextComponent());
//        property.getPrefixes().addAll(it.nextComponent());
//        property.getSuffixes().addAll(it.nextComponent());
//        
//        return property;
//    }
//}
    
}
