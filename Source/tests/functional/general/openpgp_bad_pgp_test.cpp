//
//  openpgp_bad_pgp_test.cpp
//  OpenPGP
//
//  Created by Yanfeng Zhang on 11/16/16.
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


#include "openpgp_bad_pgp_test.hpp"
#include "utils_test.h"

#include <openpgp/PGPKey.h>
#include <openpgp/encrypt.h>
#include <openpgp/decrypt.h>
#include <algorithm>
#include <string>
#include <openpgp/pgptime.h>

#include "bridge_impl/open_pgp_impl.hpp"
#include "bridge/open_pgp_key.hpp"
#include <openpgp/private_key.h>
#include <openpgp/pgptime.h>

using namespace ProtonMail::pgp;

namespace tests {
    namespace open_pgp_tests {
        SUITE(openpgo_bad_pgp_testcases)
        {
            TEST(bad_pgp_tests) {
                { //issus to update key
                    ProtonMail::OpenPgp::update_single_passphrase(private_key_dino_nov_16_2016, "123", "xq1Su2WaUFv7pqvj8m0MCnZDUXg/Xce");
                }
                
                
                {
                    auto pgp = ProtonMail::OpenPgpImpl::create_instance();
                    auto decrypted = pgp->decrypt_message_single_key(feng30_bad_message_from_outside,
                                                                    feng30_private_key,
                                                                    feng30_passphrase);
                    VERIFY_ARE_NOT_EQUAL(decrypted, "");
                }
            }
            
            TEST(test_from_user_test_one) {
                std::string in = from_user_test_one;
                PGPMessage pgp(in);
                auto out = pgp.show();
                
                std::cout << out << std::endl;
//                std::string keyin = private_key_dino_nov_16_2016;
//                PGPSecretKey pgp_pri(keyin);
//                std::string message = decrypt_pka(pgp_pri, pgp, "123", false);
//                
//  
//                std::cout << message << std::endl;
                
            }
        }
        
    }
}
