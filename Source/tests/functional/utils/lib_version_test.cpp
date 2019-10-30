//
//  lib_version_test.cpp
//  OpenPGP
//
//  Created by Yanfeng Zhang on 12/13/16.
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
