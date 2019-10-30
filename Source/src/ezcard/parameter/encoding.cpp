//
//  encoding.cpp
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

#include "encoding.hpp"
#include <sstream>
#include <iostream>


VCardParameterCaseClasses<Encoding> Encoding::enums;

Encoding::Ptr Encoding::QUOTED_PRINTABLE = std::shared_ptr<Encoding>(new Encoding(true, "QUOTED-PRINTABLE", { VCardVersion::V2_1() }, true));
Encoding::Ptr Encoding::BASE64           = std::shared_ptr<Encoding>(new Encoding(true, "BASE64", { VCardVersion::V2_1() }, true));
Encoding::Ptr Encoding::_8BIT            = std::shared_ptr<Encoding>(new Encoding(true, "8BIT", { VCardVersion::V2_1() }, true ));
Encoding::Ptr Encoding::_7BIT            = std::shared_ptr<Encoding>(new Encoding(true, "7BIT", { VCardVersion::V2_1() }, true));
Encoding::Ptr Encoding::B                = std::shared_ptr<Encoding>(new Encoding(true, "b", { VCardVersion::V3_0() }, false));


Encoding::Encoding(const std::string& value, std::vector<VCardVersion::Ptr> support) : VCardParameter(value, support) {
    
}

Encoding::Encoding(const std::string& value, std::vector<VCardVersion::Ptr> support, bool preserveCase): VCardParameter(value, support, preserveCase) {

}

Encoding::Encoding(bool predefine, const std::string& value, std::vector<VCardVersion::Ptr> support, bool preserveCase) : VCardParameter(value, support, preserveCase) {
    if (predefine) {
        enums.setupPredefine(value, support, preserveCase);
    }
}

/**
 * Searches for a parameter value that is defined as a static constant in
 * this class.
 * @param value the parameter value
 * @return the object or null if not found
 */
Encoding::Ptr Encoding::find(const std::string& value) {
    return enums.find(value);
}

/**
 * Searches for a parameter value and creates one if it cannot be found. All
 * objects are guaranteed to be unique, so they can be compared with
 * {@code ==} equality.
 * @param value the parameter value
 * @return the object
 */
Encoding::Ptr Encoding::get(const std::string& value) {
    return enums.get(value);
}

/**
 * Gets all of the parameter values that are defined as static constants in
 * this class.
 * @return the parameter values
 */
std::vector<Encoding::Ptr> Encoding::all() {
    return enums.all();
}

std::string Encoding::all_to_string() {
    std::stringstream ss;
    ss << "";
    auto all = enums.all();
    for(auto i : all) {
        ss << i;
    }
    
    return ss.str();
}

bool operator==(const Encoding::Ptr& lhs, const Encoding::Ptr& rhs) {
    if (lhs == nullptr) {
        if (rhs == nullptr)
            return true;
        return false;
    }
    return lhs->equals(rhs);
}
