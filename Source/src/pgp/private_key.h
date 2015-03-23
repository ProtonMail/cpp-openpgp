//
//  private_key.h
//  OpenPGP
//
//  Created by Yanfeng Zhang on 1/21/15.
//  Copyright (c) 2015 Yanfeng Zhang. All rights reserved.
//

#ifndef __UNNetPGP__private_key__
#define __UNNetPGP__private_key__

#include <stdio.h>
#include <pgp/PGPKey.h>
#include "Tag2.h"
#include "Tag13.h"
#include "Tag7.h"


namespace pm {
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


