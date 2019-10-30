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
#include <vector>


namespace ProtonMail {
    
    std::string &str_trim(std::string &s);
    void optimized_trim(std::string& s);
    
    
    std::vector<std::string> str_split(const std::string &s, const std::string &delim);
    
    std::string replaceAll(std::string& str, const std::string& from, const std::string& to);
    
    
    std::string decrypt_message_id(std::string& enc_msg);
    
   //std::string aes_cfb_256_encrypt();
   // void aes_cfb_256_decrypt();
    
    
    std::string quote_printable_decode(const std::string &s);
    
    std::string quote_printable_encode(const std::string &s);
    
}


#endif /* defined(__OpenPGP__utility__) */
