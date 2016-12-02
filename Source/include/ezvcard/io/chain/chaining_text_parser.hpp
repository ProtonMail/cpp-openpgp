//
//  chaining_text_parser.hpp
//  OpenPGP
//
//  Created by Yanfeng Zhang on 12/2/16.
//  Copyright © 2016 Yanfeng Zhang. All rights reserved.
//

#ifndef chaining_text_parser_hpp
#define chaining_text_parser_hpp

#include <string>
#include <ezvcard/io/text/vcard_reader.hpp>
#include <ezvcard/io/chain/chaining_parser.hpp>

namespace ezvcard {
    
    using namespace vinnie;
    
    class ChainingTextParser : public ChainingParser {
        
    private:
        bool _caretDecoding = true;
        VCardReader* newReader();
        
    public:
        
        ChainingTextParser(std::string string);
        StreamReader* constructReader(); //override
        
        //public ChainingTextParser(InputStream in);
        //public ChainingTextParser(Reader reader);
        //public ChainingTextParser(File file);
        //public T caretDecoding(boolean enable);
        
    };
    
}
#endif /* chaining_text_parser_hpp */
