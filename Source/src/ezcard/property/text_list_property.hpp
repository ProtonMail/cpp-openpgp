//
//  text_list_property.hpp
//  OpenPGP
//
//  Created by Yanfeng Zhang on 1/10/17.
//  Copyright © 2017 Yanfeng Zhang. All rights reserved.
//

#ifndef text_list_property_hpp
#define text_list_property_hpp

#include <string>

#include "list_property.hpp"

namespace ezvcard {
    

/**
 * Represents a property whose value is a list of textual values.
 * @author Michael Angstadt
 */
class TextListProperty : public ListProperty<std::string> {
public:
    TextListProperty() {
        //empty
    }
    
//    /**
//     * Copy constructor.
//     * @param original the property to make a copy of
//     */
//    public TextListProperty(TextListProperty original) {
//        super(original);
//    }
};

}

#endif /* text_list_property_hpp */
