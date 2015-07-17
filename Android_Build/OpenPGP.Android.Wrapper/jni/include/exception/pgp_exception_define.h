//
//  pgp_exception.cpp
//  OpenPGP_OSX_Lib
//
//  Created by Yanfeng Zhang on 2/19/15.
//  Copyright (c) 2015 Yanfeng Zhang. All rights reserved.
//


#ifndef __OpenPGP_OSX_Lib__pgp_exception_define__
#define __OpenPGP_OSX_Lib__pgp_exception_define__


#include <string>
#include <iostream>

namespace pm
{
    enum exception_code : uint32_t {
        PM_EXC_DEC_SIZE_INVALID = 1000001,
        
        PM_DECRYPT_PRIVATE_KEY_SUMCHECK_NOT_MATCH = 1000002,
        PM_DECRYPT_SESSION_SUMCHECK_NOT_MATCH = 1000003,
        
        PM_EXC_UNKNOW = 0xFFFFFFFF
    };

    std::string to_string (const exception_code& val);
    std::ostream& operator << (std::ostream& os, exception_code c);

};


#endif /* defined(__OpenPGP_OSX_Lib__pgp_exception_define__) */
