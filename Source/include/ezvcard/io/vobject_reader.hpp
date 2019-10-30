//
//  vobject_reader.hpp
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


#ifndef vobject_reader_hpp
#define vobject_reader_hpp

#include <string>
#include <sstream>
#include <iostream>


#include <ezvcard/io/syntax_rules.hpp>
#include <ezvcard/io/vobject_data_listener.hpp>
#include <ezvcard/parameter/vobject_parameters.hpp>
#include <ezvcard/property/vobject_property.hpp>
#include <ezvcard/io/text/component_stack.hpp>
#include <ezvcard/io/context.hpp>


namespace vinnie {
    
    
    class VObjectReader {
        
    private:
        bool _caretDecodingEnabled = true;
        bool _eos = false;
        
        int _leftOver = -1;
        int _lineNumber = 1;
        
        std::istringstream _reader;
        SyntaxRules _syntaxRules;
        ComponentStack::Ptr _stack;
        Buffer::Ptr _buffer;
        Context::Ptr context;
        
        //private final String NEWLINE = System.getProperty("line.separator");
        //private Charset defaultQuotedPrintableCharset;
        
        const VObjectProperty::Ptr parseProperty(const VObjectDataListener::Ptr& listener);
        void decodeQuotedPrintable(const VObjectProperty::Ptr& property, const VObjectDataListener::Ptr& listener);
        int nextChar();
        bool isNewline(char ch);
        bool isWhitespace(char ch);
        
    public:
        typedef std::shared_ptr<VObjectReader> Ptr;
        
        ~VObjectReader();
        VObjectReader(const std::string& str, SyntaxRules syntaxRules);
        bool isCaretDecodingEnabled();
        void setCaretDecodingEnabled(bool enable);
        void parse(const VObjectDataListener::Ptr& listener);
        
        
        //    public Charset getDefaultQuotedPrintableCharset() {
        //        return defaultQuotedPrintableCharset;
        //    }
        //    public void setDefaultQuotedPrintableCharset(Charset charset) {
        //        defaultQuotedPrintableCharset = charset;
        //    }
        //
        //    /**
        //     * Gets the character set the given property is encoded in.
        //     * @param property the property
        //     * @param listener the data listener
        //     * @return the character set or null if the character is not set or could
        //     * not be determined
        //     */
        //    private Charset getCharset(VObjectProperty property, VObjectDataListener listener);
        //    
        //    /**
        //     * Closes the underlying input stream.
        //     */
        //    public void close() throws IOException {
        //        reader.close();
        //    }
    };
    
}

#endif /* vobject_reader_hpp */
