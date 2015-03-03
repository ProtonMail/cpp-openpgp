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
#include "PGPKey.h"



namespace pm {
    namespace pgp
    {
        
        std::string update_passphrase(const PGPSecretKey & pri, const std::string & old_pwd, const std::string & new_pwd);
        
        
        
        Tag5::Ptr find_decrypting_key(const PGPSecretKey & k, const std::string & keyid, const bool& find_default = false);
        
        
        
        std::vector <std::string> decrypt_secret_key(const Tag5::Ptr & pri, const std::string & passphrase);
        //Tag5::Ptr encrypt_secret_key();
        
        
    }
}













#endif /* defined(__UNNetPGP__private_key__) */


