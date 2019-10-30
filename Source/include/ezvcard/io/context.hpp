//
//  context.hpp
//  OpenPGP
//
//  Created by Yanfeng Zhang on 12/6/16.
//  Copyright © 2016 Yanfeng Zhang. All rights reserved.
//

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
