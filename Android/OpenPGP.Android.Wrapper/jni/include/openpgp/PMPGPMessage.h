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


namespace pm {
    

class PMPGPMessage : public PGPMessage {
    
private:
    std::string encrypt_message_;
    bool is_pm_encrypt_pka_;
    
    
    void read(std::string &data);
    
   
public:
    PMPGPMessage();
    PMPGPMessage(std::string& data);
    ~PMPGPMessage();
    
    
    bool get_is_pm_pka() const;
    std::string get_encrypt_msg() const;

};
    
    
    
    
    
}


#endif /* defined(__OpenPGP_OSX_Lib__PMPGPMessage__) */
