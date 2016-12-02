//
//  address_type.hpp
//  OpenPGP
//
//  Created by Yanfeng Zhang on 1/10/17.
//  Copyright © 2017 Yanfeng Zhang. All rights reserved.
//

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
