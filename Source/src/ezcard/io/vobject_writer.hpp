//
//  vobject_writer.hpp
//  OpenPGP
//
//  Created by Yanfeng Zhang on 5/8/17.
//  Copyright © 2017 Yanfeng Zhang. All rights reserved.
//

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
