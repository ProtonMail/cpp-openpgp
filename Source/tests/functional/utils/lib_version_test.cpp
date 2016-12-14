//
//  lib_version_test.cpp
//  OpenPGP
//
//  Created by Yanfeng Zhang on 12/13/16.
//  Copyright © 2016 Yanfeng Zhang. All rights reserved.
//

#include <stdio.h>

#include "utils_test.h"
#include "lib_version.hpp"


namespace tests {
    namespace open_pgp_tests {
        
        SUITE(version_test_suite)
        {
            TEST(version) {
                auto lib_version = ProtonMail::LibVersion::get_lib_version();
                
                auto pgp_version = ProtonMail::LibVersion::get_pgp_version();
                
                auto vcard_version = ProtonMail::LibVersion::get_vcard_version();
                
                
                std::cout << lib_version << std::endl;
                
            }

        }
    }
}
