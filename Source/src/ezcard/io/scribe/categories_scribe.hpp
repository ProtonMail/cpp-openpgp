//
//  categories_scribe.hpp
//  OpenPGP
//
//  Created by Yanfeng Zhang on 6/23/17.
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
