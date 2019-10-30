//
//  label.hpp
//  OpenPGP
//
//  Created by Yanfeng Zhang on 1/10/17.
//  Copyright © 2017 Yanfeng Zhang. All rights reserved.
//

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
