//
//  uri_property_scribe.hpp
//  OpenPGP
//
//  Created by Yanfeng Zhang on 6/4/17.
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
