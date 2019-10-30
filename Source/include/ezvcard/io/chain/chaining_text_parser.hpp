//
//  chaining_text_parser.hpp
//  OpenPGP
//
//  Created by Yanfeng Zhang on 12/2/16.
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
