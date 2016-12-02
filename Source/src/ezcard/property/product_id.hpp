//
//  product_id.hpp
//  OpenPGP
//
//  Created by Yanfeng Zhang on 1/10/17.
//  Copyright © 2017 Yanfeng Zhang. All rights reserved.
//

#ifndef product_id_hpp
#define product_id_hpp

#include <stdio.h>
#include "text_property.hpp"

namespace ezvcard {

class ProductId : public TextProperty {

public:
    const static std::string PROPERTYNAME;
    
    typedef std::shared_ptr<ProductId> Ptr;
    
    ProductId(std::string prodId);
//    ProductId(const ProductId* original);
    
    
//    @Override
//    public ProductId copy() {
//        return new ProductId(this);
//    }
protected:
    std::string _className() {
        return "ProductId";
    }
    
    std::string _getPropertyName() {
        return PROPERTYNAME;
    }

    std::vector<VCardVersion::Ptr> _getSupportedVersions()  {
        return std::vector<VCardVersion::Ptr> { VCardVersion::V3_0(), VCardVersion::V4_0() };
    }
};

}

#endif /* product_id_hpp */
