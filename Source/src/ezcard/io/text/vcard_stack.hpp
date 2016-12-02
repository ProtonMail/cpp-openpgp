//
//  vcard_stack.hpp
//  OpenPGP
//
//  Created by Yanfeng Zhang on 1/11/17.
//  Copyright © 2017 Yanfeng Zhang. All rights reserved.
//

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
