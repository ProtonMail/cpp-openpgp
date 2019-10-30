//
//  label.hpp
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

#ifndef label_hpp
#define label_hpp

#include <stdio.h>
#include <string>

class Label { //extends TextProperty {
    
    
public:
    typedef std::shared_ptr<Label> Ptr;
//    /**
//     * Creates a label property.
//     * @param label the label value
//     */
//    public Label(String label) {
//        super(label);
//    }
//    
//    /**
//     * Copy constructor.
//     * @param original the property to make a copy of
//     */
//    public Label(Label original) {
//        super(original);
//    }
//    
//    /**
//     * Gets the list that stores this property's address types (TYPE
//     * parameters).
//     * @return the address types (e.g. "HOME", "WORK") (this list is mutable)
//     */
//    public List<AddressType> getTypes() {
//        return parameters.new TypeParameterList<AddressType>() {
//            @Override
//            protected AddressType _asObject(String value) {
//                return AddressType.get(value);
//            }
//        };
//    }
//    
//    @Override
//    public String getLanguage() {
//        return super.getLanguage();
//    }
//    
//    @Override
//    public void setLanguage(String language) {
//        super.setLanguage(language);
//    }
//    
//    @Override
//    public Label copy() {
//        return new Label(this);
//    }
};


#endif /* label_hpp */
