//
//  utility.h
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
