//
//  ezvcard_impl.cpp
//  OpenPGP
//
//  Created by Yanfeng Zhang on 5/31/17.
//  Copyright © 2017 Yanfeng Zhang. All rights reserved.
//

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
