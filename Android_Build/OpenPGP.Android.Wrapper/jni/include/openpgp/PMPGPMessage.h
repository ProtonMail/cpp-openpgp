//
//  PMPGPMessage.h
//  OpenPGP_OSX_Lib
//
//  Created by Yanfeng Zhang on 2/19/15.
//  Copyright (c) 2015 Yanfeng Zhang. All rights reserved.
//

#ifndef __OpenPGP_OSX_Lib__PMPGPMessage__
#define __OpenPGP_OSX_Lib__PMPGPMessage__

#include "PGPMessage.h"


namespace ProtonMail {
    

class PMPGPMessage : public PGPMessage {
    
private:
    std::string encrypt_message_;
    bool is_pm_encrypt_pka_;
    
    
    void read(std::string &data, bool isRaw);
    
   
public:
    PMPGPMessage();
    PMPGPMessage(std::string& data, bool isRaw);
    ~PMPGPMessage();
    
    
    bool get_is_pm_pka() const;
    std::string get_encrypt_msg() const;

    void append(std::string &data, bool isRaw);
};
    
    
    
    
    
}


#endif /* defined(__OpenPGP_OSX_Lib__PMPGPMessage__) */
