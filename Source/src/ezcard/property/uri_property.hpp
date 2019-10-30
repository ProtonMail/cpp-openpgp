//
//  uri_property.hpp
//  OpenPGP
//
//  Created by Yanfeng Zhang on 1/10/17.
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

#ifndef uri_property_hpp
#define uri_property_hpp

#include "text_property.hpp"

namespace ezvcard {
    

/**
 * Represents a property whose value is a URI.
 * @author Michael Angstadt
 */
class UriProperty : public TextProperty {
    /**
     * Creates a property whose value is a URI.
     * @param uri the property value
     */
public:
    UriProperty(const std::string& uri) : TextProperty(uri) {
        
    }
//
//    /**
//     * Copy constructor.
//     * @param original the property to make a copy of
//     */
//    public UriProperty(UriProperty original) {
//        super(original);
//    }
};
    
    
}

#endif /* uri_property_hpp */
