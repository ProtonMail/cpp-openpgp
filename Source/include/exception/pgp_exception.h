//
//  pgp_exception.h
//  OpenPGP_OSX_Lib
//
//  Created by Yanfeng Zhang on 2/19/15.
//  Copyright (c) 2015 Yanfeng Zhang. All rights reserved.
//

#ifndef __pgp_exception__
#define __pgp_exception__

#include <stdexcept>
#include "pgp_exception_define.h"

namespace ProtonMail {
    
    class pgp_exception: public std::runtime_error {
    public:
        explicit pgp_exception();
        explicit pgp_exception(const int code, const std::string& error);
        explicit pgp_exception(const int code, const char* error);
        
        virtual ~pgp_exception() noexcept;
        exception_code get_error_code() const;
    private:
        int pm_exception_code_;
    };
}

#endif /* defined(__pgp_exception__) */
