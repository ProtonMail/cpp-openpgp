//
//  categories_scribe.hpp
//  OpenPGP
//
//  Created by Yanfeng Zhang on 6/23/17.
//  Copyright © 2017 Yanfeng Zhang. All rights reserved.
//

#ifndef categories_scribe_hpp
#define categories_scribe_hpp

#include <stdio.h>
#include "categories.hpp"
#include "list_property_scribe.hpp"

namespace ezvcard {
    
    class CategoriesScribe : public ListPropertyScribe<Categories> {
    public:
        typedef std::shared_ptr<CategoriesScribe> Ptr;
        
        CategoriesScribe() : ListPropertyScribe(Categories::PROPERTYNAME) {
            
        }
        
    protected:
        
        Categories::Ptr _newInstance() {
            return std::make_shared<Categories>();
        }
        
        std::string _className() {
            return "CategoriesScribe";
        }
    };
}




#endif /* categories_scribe_hpp */
