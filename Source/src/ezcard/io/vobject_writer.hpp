//
//  vobject_writer.hpp
//  OpenPGP
//
//  Created by Yanfeng Zhang on 5/8/17.
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


#ifndef vobject_writer_hpp
#define vobject_writer_hpp

#include <stdio.h>
#include <sstream>
#include "syntax_rules.hpp"
#include "allowed_characters.hpp"
#include "vobject_property.hpp"
#include "vobject_parameters.hpp"
#include "folded_line_writer.hpp"


namespace vinnie {
    
    
    class VObjectWriter {
    public:
        typedef std::shared_ptr<VObjectWriter> Ptr;
        
    private:
        const static std::string NEWLINE;
        
        bool _caretEncodingEnabled = false;
        SyntaxStyle _syntaxStyle;
        
        AllowedCharacters::Ptr allowedPropertyNameChars;
        AllowedCharacters::Ptr allowedGroupChars;
        AllowedCharacters::Ptr allowedParameterNameChars;
        AllowedCharacters::Ptr allowedParameterValueChars;
        
        bool _parametersCopied;
        
        FoldedLineWriter::Ptr _writer;
        
        //private Charset defaultQuotedPrintableCharset;
        
        bool containsNewlines(const std::string& string);
        bool shouldQuoteParameterValue(const std::string& value);
        bool beginsWithWhitespace(const std::string& string);
        
        void validate(const std::string& group, const std::string& name, const VObjectParameters::Ptr& parameters);
        std::string sanitizeNewStyleParameterValue(const std::string& value);
        std::string sanitizeOldStyleParameterValue(const std::string& value);
        std::string applyCaretEncoding(const std::string& value);
        VObjectParameters::Ptr copyParameters(const VObjectParameters::Ptr& parameters);
        
    public:
        
        VObjectWriter(const std::shared_ptr<std::stringstream>& writer, SyntaxStyle syntaxStyle);
        
        FoldedLineWriter::Ptr getFoldedLineWriter();
        bool isCaretEncodingEnabled();
        void setCaretEncodingEnabled(bool enable);
        SyntaxStyle getSyntaxStyle();
        void setSyntaxStyle(SyntaxStyle syntaxStyle);
        void writeBeginComponent(const std::string& componentName);
        void writeEndComponent(const std::string& componentName);
        void writeVersion(const std::string& version);
        void writeProperty(const std::string& name, const std::string& value);
        void writeProperty(const VObjectProperty::Ptr& property);
        void writeProperty(const std::string& group, const std::string& name, VObjectParameters::Ptr parameters, std::string value);
        
    };
    
}
#endif /* vobject_writer_hpp */
