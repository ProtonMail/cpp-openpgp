//
//  chaining_parser.hpp
//  OpenPGP
//
//  Created by Yanfeng Zhang on 12/2/16.
//  Copyright © 2016 Yanfeng Zhang. All rights reserved.
//

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
