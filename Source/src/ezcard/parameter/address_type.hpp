//
//  address_type.hpp
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

#ifndef address_type_hpp
#define address_type_hpp

#include <stdio.h>
#include "vcard_parameter.hpp"

class AddressType : public VCardParameter {
protected:
    std::string _className() {
        return "AddressType";
    }
public:
    typedef std::shared_ptr<AddressType> Ptr;
//    private static final VCardParameterCaseClasses<AddressType> enums = new VCardParameterCaseClasses<AddressType>(AddressType.class);
//    
//    public static final AddressType HOME = new AddressType("home");
//    
//    public static final AddressType WORK = new AddressType("work");
//    
//    @SupportedVersions({ V2_1, V3_0 })
//    public static final AddressType DOM = new AddressType("dom");
//    
//    @SupportedVersions({ V2_1, V3_0 })
//    public static final AddressType INTL = new AddressType("intl");
//    
//    @SupportedVersions({ V2_1, V3_0 })
//    public static final AddressType POSTAL = new AddressType("postal");
//    
//    @SupportedVersions({ V2_1, V3_0 })
//    public static final AddressType PARCEL = new AddressType("parcel");
//    
//    @SupportedVersions({ V2_1, V3_0 })
//    public static final AddressType PREF = new AddressType("pref");
//    
//    private AddressType(String value) {
//        super(value);
//    }
//    
//    /**
//     * Searches for a parameter value that is defined as a static constant in
//     * this class.
//     * @param value the parameter value
//     * @return the object or null if not found
//     */
//    public static AddressType find(String value) {
//        return enums.find(value);
//    }
//    
//    /**
//     * Searches for a parameter value and creates one if it cannot be found. All
//     * objects are guaranteed to be unique, so they can be compared with
//     * {@code ==} equality.
//     * @param value the parameter value
//     * @return the object
//     */
//    public static AddressType get(String value) {
//        return enums.get(value);
//    }
//    
//    /**
//     * Gets all of the parameter values that are defined as static constants in
//     * this class.
//     * @return the parameter values
//     */
//    public static Collection<AddressType> all() {
//        return enums.all();
//    }
};



#endif /* address_type_hpp */
