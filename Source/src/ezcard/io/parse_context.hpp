//
//  parse_context.hpp
//  OpenPGP
//
//  Created by Yanfeng Zhang on 5/30/17.
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

#ifndef parse_context_hpp
#define parse_context_hpp

#include <stdio.h>
#include <string>

#include <ezvcard/ezvcard.hpp>
#include <ezvcard/vcard.hpp>

/**
 * Stores information used during the parsing of a vCard.
 * @author Michael Angstadt
 */
class ParseContext {
public:
    typedef std::shared_ptr<ParseContext> Ptr;
    
private:
    VCardVersion::Ptr _version;
    //    private List<ParseWarning> warnings = new ArrayList<ParseWarning>();
    //    private Integer lineNumber;
    //    private String propertyName;

public:
    ParseContext() {
        
    }
    /**
     * Gets the version of the vCard being parsed.
     * @return the vCard version
     */
    VCardVersion::Ptr getVersion() {
        return _version;
    }

    /**
     * Sets the version of the vCard being parsed.
     * @param version the vCard version
     */
    void setVersion(const VCardVersion::Ptr& version) {
        _version = version;
    }
//
//    /**
//     * Gets the line number the parser is currently on.
//     * @return the line number or null if not applicable
//     */
//    public Integer getLineNumber() {
//        return lineNumber;
//    }
//    
//    /**
//     * Sets the line number the parser is currently on.
//     * @param line the line number or null if not applicable
//     */
//    public void setLineNumber(Integer lineNumber) {
//        this.lineNumber = lineNumber;
//    }
//    
//    /**
//     * Gets the name of the property that the parser is currently parsing.
//     * @return the property name (e.g. "FN") or null if not applicable
//     */
//    public String getPropertyName() {
//        return propertyName;
//    }
//    
//    /**
//     * Sets the name of the property that the parser is currently parsing.
//     * @param propertyName the property name (e.g. "FN") or null if not
//     * applicable
//     */
//    public void setPropertyName(String propertyName) {
//        this.propertyName = propertyName;
//    }
//    
//    /**
//     * Adds a parse warning.
//     * @param code the warning code
//     * @param args the warning message arguments
//     */
//    public void addWarning(int code, Object... args) {
//        //@formatter:off
//        warnings.add(new ParseWarning.Builder(this)
//                     .message(code, args)
//                     .build());
//        //@formatter:on
//    }
//    
//    /**
//     * Adds a parse warning.
//     * @param message the warning message
//     */
//    public void addWarning(String message) {
//        //@formatter:off
//        warnings.add(new ParseWarning.Builder(this)
//                     .message(message)
//                     .build());
//        //@formatter:on
//    }
//    
//    /**
//     * Gets the parse warnings.
//     * @return the parse warnings
//     */
//    public List<ParseWarning> getWarnings() {
//        return warnings;
//    }
};



#endif /* parse_context_hpp */
