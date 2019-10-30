//
//  private_key.h
//  OpenPGP
//
//  Created by Yanfeng Zhang on 1/21/15.
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



#ifndef __UNNetPGP__private_key__
#define __UNNetPGP__private_key__

#include <stdio.h>
#include <openpgp/PGPKey.h>
#include <package/Tag2.h>
#include <package/Tag13.h>
#include <package/Tag7.h>

namespace ProtonMail {
    namespace pgp
    {
        
        std::string update_passphrase(PGPSecretKey & pri, const std::string & old_pwd, const std::string & new_pwd);
        
        Tag5::Ptr find_decrypting_key(const PGPSecretKey & k, const std::string & keyid, const bool& find_default = false);
        Tag7::Ptr find_decrypting_sub_key(const PGPSecretKey & k, const std::string & keyid, const bool& find_default = false);
        //Tag2::Ptr find_sign(const PGPSecretKey & k, const std::string & keyid, const bool& find_default = false);
        //Tag2::Ptr find_sub_sign(const PGPSecretKey & k, const std::string & keyid, const bool& find_default = false);
        //Tag13::Ptr find_id(const PGPSecretKey & k, const std::string & keyid, const bool& find_default = false);
        
        std::vector <std::string> decrypt_secret_key(const Tag5::Ptr & pri, const std::string & passphrase);
        //Tag5::Ptr encrypt_secret_key();
        
        
    }
}













#endif /* defined(__UNNetPGP__private_key__) */


