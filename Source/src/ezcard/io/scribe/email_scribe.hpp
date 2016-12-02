//
//  email_scribe.hpp
//  OpenPGP
//
//  Created by Yanfeng Zhang on 5/2/17.
//  Copyright © 2017 Yanfeng Zhang. All rights reserved.
//

#ifndef email_scribe_hpp
#define email_scribe_hpp

#include <stdio.h>
#include "string_property_scribe.hpp"
#include "email.hpp"

namespace ezvcard {
    
class EmailScribe : public StringPropertyScribe<Email> {
    
public:
    EmailScribe();
    
    
protected:
    Email::Ptr _parseValue(const std::string& value) {
        auto name = std::make_shared<Email>(value);
        return name;
    }
    
    std::string _className() {
        return "EmailScribe";
    }
    
//    
//    @Override
//    protected void _prepareParameters(Email property, VCardParameters copy, VCardVersion version, VCard vcard) {
//        handlePrefParam(property, copy, version, vcard);
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
};

}
#endif /* email_scribe_hpp */
