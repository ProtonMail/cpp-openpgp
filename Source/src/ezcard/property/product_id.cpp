//
//  product_id.cpp
//  OpenPGP
//
//  Created by Yanfeng Zhang on 1/10/17.
//  Copyright © 2017 Yanfeng Zhang. All rights reserved.
//

#include "product_id.hpp"


namespace ezvcard {
    
const std::string ProductId::PROPERTYNAME = "PRODID";

/**
 * Creates a product ID property.
 * @param prodId the prod ID
 */
ProductId::ProductId(std::string prodId) : TextProperty(prodId) {
    
}

//    /**
//     * Copy constructor.
//     * @param original the property to make a copy of
//     */
//    ProductId::ProductId(ProductId original) {
//        super(original);
//    }
//
//    @Override
//    public ProductId copy() {
//        return new ProductId(this);
//    }


}
