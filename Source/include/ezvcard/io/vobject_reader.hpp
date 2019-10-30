//
//  vobject_reader.hpp
//  OpenPGP
//
//  Created by Yanfeng Zhang on 12/2/16.
//  Copyright © 2016 Yanfeng Zhang. All rights reserved.
//

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
