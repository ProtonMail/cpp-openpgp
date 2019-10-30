//
//  uri_property_scribe.hpp
//  OpenPGP
//
//  Created by Yanfeng Zhang on 6/4/17.
//  Copyright © 2017 Yanfeng Zhang. All rights reserved.
//

#ifndef uri_property_scribe_hpp
#define uri_property_scribe_hpp


#include "string_property_scribe.hpp"

namespace ezvcard {
    
/**
 * Marshals properties that have URI values.
 * @param <T> the property class
 * @author Michael Angstadt
 */
template <class T>
class UriPropertyScribe : public StringPropertyScribe<T> {
    static_assert(std::is_base_of<VCardProperty, T>::value, "UriPropertyScribe<T>: T must be extent of VCardProperty type :-(");
    
public:
    UriPropertyScribe(const std::string& propertyName) : StringPropertyScribe<T>(propertyName, VCardDataType::URI) {
        
    }
    
//    @Override
//    protected T _parseHtml(HCardElement element, ParseContext context) {
//        String href = element.absUrl("href");
//        if (href.length() == 0) {
//            return super._parseHtml(element, context);
//        }
//        return _parseValue(href);
//    }
};

}
#endif /* uri_property_scribe_hpp */
