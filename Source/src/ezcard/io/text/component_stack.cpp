//
//  component_stack.cpp
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


#include "component_stack.hpp"

#include <iterator>

/**
 * Creates a new stack.
 * @param defaultSyntax the default syntax style
 */
ComponentStack::ComponentStack(SyntaxStyle defaultSyntax) {
    _syntax.push_back(defaultSyntax);
}


/**
 * Pushes a component onto the stack.
 * @param component the component name
 */
void ComponentStack::push(std::string component) {
    _names->push_back(component);
    _syntax.push_back(peekSyntax());
}


/**
 * Removes the top component from the stack.
 * @return the name of the component that was removed
 */
std::string ComponentStack::pop() {
    _syntax.pop_back();
    auto name_ = _names->back();
    _names->pop_back();
    return name_;
}


/**
 * Gets the number of calls to {@link #pop()} it would take to pop the
 * given component name.
 * @param name the component name
 * @return the number of pops or 0 if the name was not found
 */
size_t ComponentStack::popCount(std::string name) {
    size_t i = _names->size() - 1;
    for (auto rit=_names->rbegin(); rit!=_names->rend(); ++rit) {
        if (*rit == name) {
            auto count = _names->size() - i;
            return count;
        }
        i --;
    }
//    std::cout << ' ' << *rit;
//    
//    auto it = std::find(_names.begin(), _names.end(), name);
//    if (it != _names.end()) {
//        auto index = std::distance(it, _names.end());
//        return index;
//    }
    return 0;
}


/**
 * Gets the top component name.
 * @return the top component name or null if the name stack is empty
 */
std::string ComponentStack::peekName() {
    if (_names->size() > 0) {
        return _names->back();
    }
    return "";
}


/**
 * Gets the top syntax style.
 * @return the top syntax style or null if the syntax stack is empty
 */
SyntaxStyle ComponentStack::peekSyntax() {
    if (_syntax.size() > 0) {
        return _syntax.back();
    }
    return SyntaxStyle::NONE;
}

/**
 * Replaces the top syntax style.
 * @param style the syntax style
 */
void ComponentStack::updateSyntax(SyntaxStyle style) {
    _syntax.pop_back();
    _syntax.push_back(style);
}

