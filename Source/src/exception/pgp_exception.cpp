//
//  pgp_exception.cpp
//  OpenPGP
//
//  Created by Yanfeng Zhang on 1/31/15.
//  Copyright (c) 2015 Yanfeng Zhang. All rights reserved.
//

#include "pgp_exception.h"


namespace pm {
   
    
    
    pgp_exception::pgp_exception(const int code, const std::string& error) : runtime_error(error), pm_exception_code_( code )
    {
    }
    
    pgp_exception::pgp_exception(const int code, const char* error) : runtime_error(error), pm_exception_code_( code )
    {
    }
    
    pgp_exception::pgp_exception() : pm_exception_code_( -1 ), runtime_error("unknow error")
    {
    }
    
    pgp_exception::~pgp_exception() _NOEXCEPT {};
    
    
    
    
    int pgp_exception::get_error_code() const
    {
        return pm_exception_code_;
    }
    
    //        virtual const char* what() const throw()
    //        {
    //
    //        }    
    
}

