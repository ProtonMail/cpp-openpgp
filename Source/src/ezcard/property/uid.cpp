//
//  uid.cpp
//  OpenPGP
//
//  Created by Yanfeng Zhang on 1/10/17.
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


#include "uid.hpp"



namespace ProtonMail {
    
    std::shared_ptr<IUid> IUid::create_instance(const std::string & uuid) {
        return std::make_shared<ezvcard::Uid>(uuid);
    }
}

namespace ezvcard {
    
    const std::string Uid::PROPERTYNAME = "UID";
    const std::string Uid::CLASSNAME = "Uid";
    
    
    std::string Uid::getAltId() {
        return _parameters->getAltId();
    }
    
    void Uid::setAltId(const std::string& altId) {
        _parameters->setAltId(altId);
    }
    
    std::string Uid::getValue() {
        return UriProperty::getValue();
    }
    
    
    
}
