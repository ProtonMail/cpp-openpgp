//
//  chaining_parser.hpp
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

#ifndef chaining_parser_hpp
#define chaining_parser_hpp


#include <string>
#include <vector>
#include "vcard.hpp"
#include <ezvcard/io/stream_reader.hpp>
#include <ezvcard/io/scribe/scribe_index.hpp>

namespace ezvcard {
    


class ChainingParser {// <T extends ChainingParser<?>> {
    
private:
    //    final InputStream in;
    //    final Reader reader;
    //    final File file;
    ScribeIndex::Ptr _index = nullptr;
    std::list<std::list<std::string>> _warnings = std::list<std::list<std::string>>();
    
    //    @SuppressWarnings("unchecked")
    //    final T this_ = (T) this;
    //    private ChainingParser(String string, InputStream in, Reader reader, File file);
    //    private boolean closeWhenDone();
    
public:
    std::string _str;
    ChainingParser(const std::string& string);
    
    //    ChainingParser(InputStream in);
    //    ChainingParser(Reader reader);
    //    ChainingParser(File file);
    //    ChainingParser();
    //
    //    public T register(VCardPropertyScribe<? extends VCardProperty> scribe);
    //    public T warnings(List<List<String>> warnings);
    
    VCard::Ptr first();
    std::vector<VCard::Ptr> all();
    virtual StreamReader* constructReader() = 0;
};

    
}
#endif /* chaining_parser_hpp */
