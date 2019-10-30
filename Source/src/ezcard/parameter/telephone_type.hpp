//
//  telephone_type.hpp
//  OpenPGP
//
//  Created by Yanfeng Zhang on 1/10/17.
//  Copyright © 2017 Yanfeng Zhang. All rights reserved.
//

#ifndef telephone_type_hpp
#define telephone_type_hpp

#include <stdio.h>


//
//
///**
// * Represents the TYPE parameter of the {@link Telephone} property.
// * <p>
// * <b>Supported versions:</b> {@code 2.1, 3.0, 4.0}
// * </p>
// * @author Michael Angstadt
// */
//public class TelephoneType extends VCardParameter {
//    private static final VCardParameterCaseClasses<TelephoneType> enums = new VCardParameterCaseClasses<TelephoneType>(TelephoneType.class);
//    
//    @SupportedVersions({ V2_1, V3_0 })
//    public static final TelephoneType BBS = new TelephoneType("bbs");
//    
//    @SupportedVersions({ V2_1, V3_0 })
//    public static final TelephoneType CAR = new TelephoneType("car");
//    
//    public static final TelephoneType CELL = new TelephoneType("cell");
//    
//    public static final TelephoneType FAX = new TelephoneType("fax");
//    
//    public static final TelephoneType HOME = new TelephoneType("home");
//    
//    @SupportedVersions({ V2_1, V3_0 })
//    public static final TelephoneType ISDN = new TelephoneType("isdn");
//    
//    @SupportedVersions({ V2_1, V3_0 })
//    public static final TelephoneType MODEM = new TelephoneType("modem");
//    
//    @SupportedVersions({ V2_1, V3_0 })
//    public static final TelephoneType MSG = new TelephoneType("msg");
//    
//    public static final TelephoneType PAGER = new TelephoneType("pager");
//    
//    @SupportedVersions(V3_0)
//    public static final TelephoneType PCS = new TelephoneType("pcs");
//    
//    @SupportedVersions({ V2_1, V3_0 })
//    public static final TelephoneType PREF = new TelephoneType("pref");
//    
//    @SupportedVersions(V4_0)
//    public static final TelephoneType TEXT = new TelephoneType("text");
//    
//    @SupportedVersions(V4_0)
//    public static final TelephoneType TEXTPHONE = new TelephoneType("textphone");
//    
//    public static final TelephoneType VIDEO = new TelephoneType("video");
//    
//    public static final TelephoneType VOICE = new TelephoneType("voice");
//    
//    public static final TelephoneType WORK = new TelephoneType("work");
//    
//    private TelephoneType(String value) {
//        super(value);
//    }
//    
//    /**
//     * Searches for a parameter value that is defined as a static constant in
//     * this class.
//     * @param value the parameter value
//     * @return the object or null if not found
//     */
//    public static TelephoneType find(String value) {
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
//    public static TelephoneType get(String value) {
//        return enums.get(value);
//    }
//    
//    /**
//     * Gets all of the parameter values that are defined as static constants in
//     * this class.
//     * @return the parameter values
//     */
//    public static Collection<TelephoneType> all() {
//        return enums.all();
//    }
//}

#endif /* telephone_type_hpp */
