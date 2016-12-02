//
//  context.cpp
//  OpenPGP
//
//  Created by Yanfeng Zhang on 12/6/16.
//  Copyright © 2016 Yanfeng Zhang. All rights reserved.
//

#include "context.hpp"
Context::Context() {
    unfoldedLine = std::make_shared<Buffer>();
    _parentComponents = std::make_shared<std::list<std::string>>();
}

Context::Context(std::shared_ptr<std::list<std::string>> parentComponents) {
    unfoldedLine = std::make_shared<Buffer>();
    _parentComponents = parentComponents;
}

Context::~Context() {
    
}

/**
 * Gets the hierarchy of parent components the parser is currently inside
 * of, starting with the outer-most component.
 * @return the component names (in uppercase; this list is immutable)
 */
const std::shared_ptr<std::list<std::string>> Context::getParentComponents() {
    return _parentComponents;
}

/**
 * Gets the raw, unfolded line that was parsed.
 * @return the raw, unfolded line
 */
std::string Context::getUnfoldedLine() {
    return unfoldedLine->get();
}

/**
 * Gets the line number of the parsed line. If the line was folded, this
 * will be the line number of the first line.
 * @return the line number
 */
int Context::getLineNumber() {
    return _lineNumber;
}

/**
 * Instructs the parser to stop parsing and return from the call to
 * {@link VObjectReader#parse}.
 */
void Context::stop() {
    _stop = true;
}

//    @Override
//    public String toString() {
//        return "Context [parentComponents=" + parentComponents + ", unfoldedLine=" + unfoldedLine.get() + ", lineNumber=" + lineNumber + ", stop=" + stop + "]";
//    }
