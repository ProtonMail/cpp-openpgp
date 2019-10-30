//
//  pgp_exception.cpp
//  OpenPGP_OSX_Lib
//
//  Created by Yanfeng Zhang on 2/19/15.
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

#ifndef __pgp_exception_define__
#define __pgp_exception_define__


#include <string>
#include <iostream>

namespace ProtonMail
{
    enum exception_code : uint32_t {
        PM_EXC_DEC_SIZE_INVALID = 0x1000001,
        
        PM_DECRYPT_PRIVATE_KEY_SUMCHECK_NOT_MATCH = 0x1000002,
        PM_DECRYPT_SESSION_SUMCHECK_NOT_MATCH = 0x1000003,
        
        PM_EXC_UNKNOW = 0xFFFFFFFF
    };

    std::string to_string (const exception_code& val);
    std::ostream& operator << (std::ostream& os, exception_code c);

};


#endif /* defined(__pgp_exception_define__) */
