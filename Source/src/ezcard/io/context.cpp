//
//  context.cpp
//  OpenPGP
//
//  Created by Yanfeng Zhang on 12/6/16.
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
