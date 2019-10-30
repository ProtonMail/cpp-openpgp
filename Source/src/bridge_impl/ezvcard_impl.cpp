//
//  ezvcard_impl.cpp
//  OpenPGP
//
//  Created by Yanfeng Zhang on 5/31/17.
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



#include <stdio.h>

#include <bridge_impl/ezvcard_impl.hpp>

#include <ezvcard/ezvcard.hpp>
#include <ezvcard/vcard.hpp>
#include <ezvcard/io/chain/chaining_text_string_parser.hpp>

namespace ProtonMail {
    
    using namespace ezvcard;
    
    EzvcardImpl::EzvcardImpl() {
        
    }
    
    EzvcardImpl::~EzvcardImpl() {
        
    }
    
    std::shared_ptr<IVCard> IEzvcard::parse_first(const std::string & value) {
        auto vcard = Ezvcard::parse(value).first();
        return vcard;
    }
    
    std::vector<std::shared_ptr<IVCard>> IEzvcard::parse_all(const std::string & value) {
        auto vcards = Ezvcard::parse(value).all();
        return std::vector<std::shared_ptr<IVCard>>(vcards.begin(), vcards.end());
    }
    
    std::string IEzvcard::write(const std::shared_ptr<IVCard> & vcard) {
        
        auto convertedObj = std::dynamic_pointer_cast<VCard>(vcard);
        
        return Ezvcard::write( { convertedObj })->go();
        
    }
    
    std::string IEzvcard::write_all(const std::vector<std::shared_ptr<IVCard>> & vcards) {
//        auto convertedObj = std::dynamic_pointer_cast<VCard>(vcard);
//        return Ezvcard::write( { convertedObj })->go();
        return ""; //TODO:: add later
    }
    

    

}
