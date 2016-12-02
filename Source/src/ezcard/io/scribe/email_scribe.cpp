//
//  email_scribe.cpp
//  OpenPGP
//
//  Created by Yanfeng Zhang on 5/2/17.
//  Copyright © 2017 Yanfeng Zhang. All rights reserved.
//

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
