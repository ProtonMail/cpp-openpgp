//
//  chaining_text_string_parser.hpp
//  OpenPGP
//
//  Created by Yanfeng Zhang on 12/2/16.
//  Copyright © 2016 Yanfeng Zhang. All rights reserved.
//

#ifndef chaining_text_string_parser_hpp
#define chaining_text_string_parser_hpp

#include <string>
#include "chaining_text_parser.hpp"

namespace ezvcard {
    
    class ChainingTextStringParser : public ChainingTextParser {
    public:
        typedef std::shared_ptr<ChainingTextStringParser> Ptr;
        
    public:
        ChainingTextStringParser(std::string string);
        VCard::Ptr first();
        std::vector<VCard::Ptr> all();
    };
    
}

#endif /* chaining_text_string_parser_hpp */
