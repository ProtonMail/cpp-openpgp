//
//  component_stack.hpp
//  OpenPGP
//
//  Created by Yanfeng Zhang on 12/5/16.
//  Copyright © 2016 Yanfeng Zhang. All rights reserved.
//

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
