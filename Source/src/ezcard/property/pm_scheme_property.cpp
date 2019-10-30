//
//  pm_custom_property.cpp
//  OpenPGP
//
//  Created by Yanfeng Zhang on 6/26/17.
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

#include "pm_scheme_property.hpp"

namespace ProtonMail {

    std::shared_ptr<IPMScheme> IPMScheme::create_instance(const std::string &type, const std::string &value) {
        auto out = std::make_shared<ezvcard::PMScheme>(value);
        out->setType(type);
        return out;
    }
}

namespace ezvcard {
    
    const std::string PMScheme::PROPERTYNAME = "X-PM-SCHEME";
    const std::string PMScheme::CLASSNAME = "PMScheme";
    
    std::string PMScheme::_className() {
        return CLASSNAME;
    }
    std::string PMScheme::_getPropertyName() {
        return PROPERTYNAME;
    }
    
    std::string PMScheme::getAltId() {
        return _parameters->getAltId();
    }
    void PMScheme::setAltId(const std::string& altId) {
        _parameters->setAltId(altId);
    }
}
