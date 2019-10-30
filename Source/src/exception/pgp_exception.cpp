//
//  pgp_exception.cpp
//  OpenPGP
//
//  Created by Yanfeng Zhang on 1/31/15.
//
//  The MIT License
// 
//  Copyright (c) 2019 Proton Technologies AG
// 
//  Permission is hereby granted, free of charge, to any person obtaining a copy
//  of this software and associated documentation files (the "Software"), to deal
//  in the Software without restriction, including without limitation the rights
//  to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
//  copies of the Software, and to permit persons to whom the Software is
//  furnished to do so, subject to the following conditions:
// 
//  The above copyright notice and this permission notice shall be included in
//  all copies or substantial portions of the Software.
// 
//  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
//  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
//  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
//  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
//  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
//  OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
//  THE SOFTWARE.


#include <exception/pgp_exception.h>


namespace ProtonMail {
   
    
    
    pgp_exception::pgp_exception(const int code, const std::string& error) : runtime_error(error), pm_exception_code_( code )
    {
    }
    
    pgp_exception::pgp_exception(const int code, const char* error) : runtime_error(error), pm_exception_code_( code )
    {
    }
    
    pgp_exception::pgp_exception() : pm_exception_code_( -1 ), runtime_error("unknow error")
    {
    }
    
    pgp_exception::~pgp_exception() noexcept {};
    

    exception_code pgp_exception::get_error_code() const
    {
        return (exception_code)pm_exception_code_;
    }
    
    //        virtual const char* what() const throw()
    //        {
    //
    //        }    
    
}

