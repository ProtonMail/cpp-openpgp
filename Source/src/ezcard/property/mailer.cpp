//
//  mailer.cpp
//  OpenPGP
//
//  Created by Yanfeng Zhang on 1/10/17.
//  Copyright © 2017 Yanfeng Zhang. All rights reserved.
//

#include "mailer.hpp"

namespace ezvcard {
    

const std::string Mailer::CLASSNAME = "Mailer";
const std::string Mailer::PROPERTYNAME = "MAILER";


//    /**
//     * Copy constructor.
//     * @param original the property to make a copy of
//     */
//    public Mailer(Mailer original) {
//        super(original);
//    }
//
//    @Override
//    public Mailer copy() {
//        return new Mailer(this);
//    }
//}



/**
 * Creates a mailer property.
 * @param emailClient the name of the email client (e.g. "Thunderbird")
 */
Mailer::Mailer(const std::string& emailClient) : TextProperty(emailClient) {
    
}

std::vector<VCardVersion::Ptr> Mailer::_getSupportedVersions() {
    return { VCardVersion::V2_1(), VCardVersion::V3_0() };
}


}
