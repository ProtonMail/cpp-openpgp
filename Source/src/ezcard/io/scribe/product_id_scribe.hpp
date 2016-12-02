//
//  product_id_scribe.hpp
//  OpenPGP
//
//  Created by Yanfeng Zhang on 5/17/17.
//  Copyright © 2017 Yanfeng Zhang. All rights reserved.
//

#ifndef product_id_scribe_hpp
#define product_id_scribe_hpp

#include <stdio.h>

#include "string_property_scribe.hpp"
#include "product_id.hpp"

namespace ezvcard {
    

class ProductIdScribe : public StringPropertyScribe<ProductId> {
public:
    ProductIdScribe();
    
protected:
    ProductId::Ptr _parseValue(const std::string& value) {
        auto name = std::make_shared<ProductId>(value);
        return name;
    }
    
    std::string _className() {
        return "ProductIdScribe";
    }

};

    
}

#endif /* product_id_scribe_hpp */

