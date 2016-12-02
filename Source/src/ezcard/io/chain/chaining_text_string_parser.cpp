//
//  chaining_text_string_parser.cpp
//  OpenPGP
//
//  Created by Yanfeng Zhang on 12/2/16.
//  Copyright © 2016 Yanfeng Zhang. All rights reserved.
//

#include "chaining_text_string_parser.hpp"

namespace ezvcard {
    
    
    ChainingTextStringParser::ChainingTextStringParser(std::string str) : ChainingTextParser(str) {
        
    }
    
    
    VCard::Ptr ChainingTextStringParser::first() {
        return ChainingTextParser::first();
    }
    
    std::vector<VCard::Ptr> ChainingTextStringParser::all() {
        return ChainingTextParser::all();
    }
    
}
