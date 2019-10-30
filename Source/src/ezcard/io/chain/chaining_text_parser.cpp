//
//  chaining_text_parser.cpp
//  OpenPGP
//
//  Created by Yanfeng Zhang on 12/2/16.
//  Copyright © 2016 Yanfeng Zhang. All rights reserved.
//

#include "chaining_text_parser.hpp"

namespace ezvcard {
    
    ChainingTextParser::ChainingTextParser(std::string string) : ChainingParser(string) {
        //
    }
    
    
    StreamReader* ChainingTextParser::constructReader() {
        auto reader = newReader();
        reader->setCaretDecodingEnabled(_caretDecoding);
        return reader;
    }
    
    VCardReader* ChainingTextParser::newReader() {
        //    if (!_str.empty()) {
        return new VCardReader(_str);
        //    }
        //    if (in != null) {
        //        return new VCardReader(in);
        //    }
        //    if (reader != null) {
        //        return new VCardReader(reader);
        //    }
        //    return new VCardReader(file);
    }
    
    
    //    public ChainingTextParser(InputStream in) {
    //        super(in);
    //    }
    //
    //    public ChainingTextParser(Reader reader) {
    //        super(reader);
    //    }
    //
    //    public ChainingTextParser(File file) {
    //        super(file);
    //    }
    //
    //    /**
    //     * Sets whether the reader will decode characters in parameter values that
    //     * use circumflex accent encoding (enabled by default).
    //     *
    //     * @param enable true to use circumflex accent decoding, false not to
    //     * @return this
    //     * @see VCardReader#setCaretDecodingEnabled(boolean)
    //     * @see <a href="http://tools.ietf.org/html/rfc6868">RFC 6868</a>
    //     */
    //    public T caretDecoding(boolean enable) {
    //        caretDecoding = enable;
    //        return this_;
    //    }
    //
    //
    
    //}
    
}
