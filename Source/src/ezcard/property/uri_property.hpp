//
//  uri_property.hpp
//  OpenPGP
//
//  Created by Yanfeng Zhang on 1/10/17.
//  Copyright © 2017 Yanfeng Zhang. All rights reserved.
//

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
