//
//  parse_context.cpp
//  OpenPGP
//
//  Created by Yanfeng Zhang on 5/30/17.
//  Copyright © 2017 Yanfeng Zhang. All rights reserved.
//

#include "parse_context.hpp"


//
///**
// * Stores information used during the parsing of a vCard.
// * @author Michael Angstadt
// */
//public class ParseContext {
//    private VCardVersion version;
//    private List<ParseWarning> warnings = new ArrayList<ParseWarning>();
//    private Integer lineNumber;
//    private String propertyName;
//    
//    /**
//     * Gets the version of the vCard being parsed.
//     * @return the vCard version
//     */
//    public VCardVersion getVersion() {
//        return version;
//    }
//    
//    /**
//     * Sets the version of the vCard being parsed.
//     * @param version the vCard version
//     */
//    public void setVersion(VCardVersion version) {
//        this.version = version;
//    }
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
//}
