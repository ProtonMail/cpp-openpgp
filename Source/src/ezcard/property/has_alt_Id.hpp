//
//  has_alt_Id.hpp
//  OpenPGP
//
//  Created by Yanfeng Zhang on 1/10/17.
//  Copyright © 2017 Yanfeng Zhang. All rights reserved.
//

#ifndef has_alt_Id_hpp
#define has_alt_Id_hpp

#include <stdio.h>
#include <string>


class HasAltId {
    /**
     * Gets the property's ALTID parameter.
     * <p>
     * <b>Supported versions:</b> {@code 4.0}
     * </p>
     * @return the ALTID or null if it doesn't exist
     * @see VCardParameters#getAltId
     */
    virtual std::string getAltId() = 0;
    
    /**
     * Sets the property's ALTID parameter.
     * <p>
     * <b>Supported versions:</b> {@code 4.0}
     * </p>
     * @param altId the ALTID or null to remove
     * @see VCardParameters#setAltId
     */
    virtual void setAltId(const std::string& altId) = 0;
};



#endif /* has_alt_Id_hpp */
