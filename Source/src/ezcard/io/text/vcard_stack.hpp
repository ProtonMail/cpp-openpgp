//
//  vcard_stack.hpp
//  OpenPGP
//
//  Created by Yanfeng Zhang on 1/11/17.
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

#ifndef vcard_stack_hpp
#define vcard_stack_hpp

#include <stdio.h>
#include <list>

#include "vobject_reader.hpp"
#include "vcard.hpp"

#include "label.hpp"

namespace ezvcard {




class Item {
public:
    typedef std::shared_ptr<Item> Ptr;
    VCard::Ptr _vcard;
    std::list<Label::Ptr> _labels;
    
    Item(const VCard::Ptr& vcard, std::list<Label::Ptr> labels) {
        _vcard = vcard;
        _labels = labels;
    }
};


/**
 * Keeps track of the hierarchy of nested vCards.
 */
class VCardStack {
private:
    std::list<Item::Ptr> _stack;
    
public:
    typedef std::shared_ptr<VCardStack> Ptr;
    
    /**
     * Adds a vCard to the stack.
     * @param vcard the vcard to add
     */
    void push(VCard::Ptr vcard) {
        _stack.push_back(std::make_shared<Item>(vcard, std::list<Label::Ptr>()));
    }
    
    /**
     * Removes the top item from the stack and returns it.
     * @return the last item or null if the stack is empty
     */
    Item::Ptr pop() {
        if(isEmpty()) {
            return nullptr;
        }
        auto item = _stack.back();
        _stack.pop_back();
        return item;
    }
    
    /**
     * Gets the top item of the stack.
     * @return the top item
     */
    Item::Ptr peek() {
        return isEmpty() ? nullptr : _stack.back();
    }
    
    /**
     * Determines if the stack is empty.
     * @return true if it's empty, false if not
     */
    bool isEmpty() {
        return _stack.size() <= 0;
    }
};


}

#endif /* vcard_stack_hpp */
