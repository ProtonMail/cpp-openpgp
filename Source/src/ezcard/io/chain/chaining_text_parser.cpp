//
//  chaining_text_parser.cpp
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
