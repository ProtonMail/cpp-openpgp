//
//  component_stack.hpp
//  OpenPGP
//
//  Created by Yanfeng Zhang on 12/5/16.
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

#ifndef component_stack_hpp
#define component_stack_hpp

#include <string>
#include <list>

#include <ezvcard/vcard_version.hpp>


/**
 * Keeps track of the hierarchy of nested components and their syntax
 * styles.
 */
class ComponentStack {
    /**
     * The hierarchy of components the parser is currently inside of.
     */
private:
    std::list<SyntaxStyle> _syntax = std::list<SyntaxStyle>();
    
    
public:
    typedef std::shared_ptr<ComponentStack> Ptr;
    
    std::shared_ptr<std::list<std::string>> _names = std::make_shared<std::list<std::string>>();
    
    ComponentStack(SyntaxStyle defaultSyntax);
    
    void push(std::string component);
    std::string pop();
    size_t popCount(std::string name);
    std::string peekName();
    SyntaxStyle peekSyntax();
    void updateSyntax(SyntaxStyle style);

};



#endif /* component_stack_hpp */
