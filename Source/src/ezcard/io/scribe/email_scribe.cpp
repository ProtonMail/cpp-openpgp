//
//  email_scribe.cpp
//  OpenPGP
//
//  Created by Yanfeng Zhang on 5/2/17.
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


#include "email_scribe.hpp"

namespace ezvcard {
    
EmailScribe::EmailScribe() : StringPropertyScribe(Email::PROPERTYNAME) {
    
}


//    @Override
//    protected void _prepareParameters(Email property, VCardParameters copy, VCardVersion version, VCard vcard) {
//        handlePrefParam(property, copy, version, vcard);
//    }
//    
//    @Override
//    protected Email _parseValue(String value) {
//        return new Email(value);
//    }
//    
//    @Override
//    protected Email _parseHtml(HCardElement element, ParseContext context) {
//        String href = element.attr("href");
//        String email = extractEmailFromHrefAttribute(href);
//        if (email == null) {
//            email = element.value();
//        }
//        
//        Email property = new Email(email);
//        
//        List<String> types = element.types();
//        property.getParameters().putAll(VCardParameters.TYPE, types);
//        
//        return property;
//    }
//    
//    private static String extractEmailFromHrefAttribute(String value) {
//        int colon = value.indexOf(':');
//        if (colon < 0) {
//            return null;
//        }
//        
//        String scheme = value.substring(0, colon);
//        return scheme.equalsIgnoreCase("mailto") ? value.substring(colon + 1) : null;
//    }

}
