//
//  PMPGPMessage.h
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
