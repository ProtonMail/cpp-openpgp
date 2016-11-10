//
//  utility.h
//  OpenPGP
//
//  Created by Yanfeng Zhang on 1/31/15.
//  Copyright (c) 2015 Yanfeng Zhang. All rights reserved.
//

#ifndef __OpenPGP__utility__
#define __OpenPGP__utility__

#include <stdio.h>
#include <string>


namespace ProtonMail {
    
    void optimized_trim(std::string& s);
    
    
    std::string decrypt_message_id(std::string& enc_msg);
    
   //std::string aes_cfb_256_encrypt();
   // void aes_cfb_256_decrypt();
}


#endif /* defined(__OpenPGP__utility__) */
