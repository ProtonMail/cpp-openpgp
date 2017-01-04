//
//  lib_version_impl.cpp
//  OpenPGP
//
//  Created by Yanfeng Zhang on 12/13/16.
//  Copyright © 2016 Yanfeng Zhang. All rights reserved.
//


#include "bridge_impl/lib_version_impl.hpp"
#include "version.hpp"
#include <sstream>

namespace ProtonMail {
    
    
    
    std::string LibVersion::get_lib_version() {
        return PM_LIB_VERSION;
    }

    std::string LibVersion::get_pgp_version() {
        return PM_OPENPGP_VERSION;
    }
    
    std::string LibVersion::get_vcard_version(){
        return PM_VCARD_VERSION;
    }
}
