//
//  context.hpp
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

#ifndef context_hpp
#define context_hpp

#include <list>
#include <string>

#include <ezvcard/io/buffer.hpp>

class Context {
public:
    typedef std::shared_ptr<Context> Ptr;
    
public:
    Buffer::Ptr unfoldedLine;
    std::shared_ptr<std::list<std::string>> _parentComponents;
    int _lineNumber = 1;
    bool _stop = false;
    Context();
    Context(std::shared_ptr<std::list<std::string>> parentComponents);
    ~Context();
    const std::shared_ptr<std::list<std::string>> getParentComponents();
    std::string getUnfoldedLine();
    int getLineNumber();
    void stop();

};

#endif /* context_hpp */
