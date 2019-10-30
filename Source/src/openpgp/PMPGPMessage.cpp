//
//  PMPGPMessage.cpp
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



#include <openpgp/PMPGPMessage.h>
#include <base/BaseObject.h>
#include <utilities/utility.h>
#include <exception/pgp_exception.h>
#include <exception/pgp_exception_define.h>
#include <utilities/consts.h>
#include <utilities/base64.h>

namespace ProtonMail {
    
    PMPGPMessage::PMPGPMessage() : PGPMessage()
    {
        encrypt_message_ = "";
        is_pm_encrypt_pka_ = true;
        set_is_debug(false);
    }
    
    PMPGPMessage::PMPGPMessage(std::string & data, bool isRaw): PMPGPMessage()
    {
        read(data, isRaw);
    }
    
    PMPGPMessage::~PMPGPMessage()
    {
        
    }
    
    void PMPGPMessage::read(std::string &data, bool isRaw)
    {
        if (!isRaw)
            optimized_trim(data);
        size_t data_size = data.length();
        
        if(data_size <= 0)
        {
            throw pgp_exception(PM_EXC_DEC_SIZE_INVALID, to_string(PM_EXC_DEC_SIZE_INVALID));
        }
        
        //detatct header check protonmail header.
        std::string::size_type count = 29;
        std::size_t start_enc_msg = data.find(protonmail_cryoto_headerMessage.c_str(), 0, count);
        if(start_enc_msg == std::string::npos)
        {
            is_pm_encrypt_pka_ = false;
        }
        if(is_pm_encrypt_pka_)
        {
            start_enc_msg += protonmail_cryoto_headerMessage.length();
            std::size_t end_enc_msg = data.find(protonmail_cryoto_tailMessage);
            if(end_enc_msg == std::string::npos)
            {
                is_pm_encrypt_pka_ = false;
            }
            end_enc_msg -= start_enc_msg;
            
            encrypt_message_ = data.substr(start_enc_msg, end_enc_msg);
            if(get_is_debug())
                std::cout << encrypt_message_ << std::endl;
            
            std::size_t start_rk = data.find(protonmail_cryoto_headerRandomKey.c_str(), end_enc_msg, count) + protonmail_cryoto_headerRandomKey.length();
            if(start_rk == std::string::npos)
            {
                //TODO:: need update exception type
                throw pgp_exception(PM_EXC_DEC_SIZE_INVALID, to_string(PM_EXC_DEC_SIZE_INVALID));
            }
            std::size_t end_rk = data_size - protonmail_cryoto_tailRandomKey.length();
            if(end_rk == std::string::npos)
            {
                //TODO:: need update exception type
                throw pgp_exception(PM_EXC_DEC_SIZE_INVALID, to_string(PM_EXC_DEC_SIZE_INVALID));
            }
            end_rk -= start_rk;

            std::string encrypt_random_key = data.substr(start_rk, end_rk);
            encrypt_message_ = decode_utf8_base64(encrypt_message_);
            if(get_is_debug())
                std::cout << encrypt_random_key << std::endl;
            
            PGPMessage::read(encrypt_random_key);
            PGPMessage::done_load();
        }
        else
        {
            PGPMessage::read(data);
            PGPMessage::done_load();
        }
    }
    
    void PMPGPMessage::append(std::string &data, bool isRaw)
    {
        read(data, isRaw);
    }
    
    bool PMPGPMessage::get_is_pm_pka() const
    {
        return is_pm_encrypt_pka_;
    }
    
    std::string PMPGPMessage::get_encrypt_msg() const
    {
        return encrypt_message_;
    }
    
}
