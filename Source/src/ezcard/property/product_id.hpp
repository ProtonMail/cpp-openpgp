//
//  product_id.hpp
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
