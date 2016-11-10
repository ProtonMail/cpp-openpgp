//
//  pgp_exception.cpp
//  OpenPGP
//
//  Created by Yanfeng Zhang on 1/31/15.
//  Copyright (c) 2015 Yanfeng Zhang. All rights reserved.
//

#include <exception/pgp_exception_define.h>

namespace ProtonMail {
    
    std::string to_string (const exception_code& val)
    {
        std::string os = "";
        switch(val) {
            case PM_EXC_DEC_SIZE_INVALID: os = "The input size is not valid"; break;
            case PM_EXC_UNKNOW: default: os = "UNKnow exception"; break;
        }
        return os;
    }
    
    std::ostream& operator<<(std::ostream& os, exception_code c)
    {
        os<< to_string(c);
        return os;
    }
}

