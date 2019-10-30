//
//  chaining_writer.cpp
//  OpenPGP
//
//  Created by Yanfeng Zhang on 5/8/17.
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

#include "chaining_writer.hpp"

namespace ezvcard {
    

/**
 * @param vcards the vCards to write
 */
ChainingWriter::ChainingWriter(std::vector<VCard::Ptr> vcards) {
    _vcards = vcards;
}


/**
 * Sets whether to exclude properties that do not support the target version
 * from the written vCard.
 * @param versionStrict true to exclude such properties, false not to
 * (defaults to true)
 * @return this
 */
void ChainingWriter::versionStrict(bool versionStrict) {
    _versionStrict = versionStrict;
}

/**
 * Sets whether to add a {@link ProductId} property to each vCard that marks
 * it as having been generated by this library. For 2.1 vCards, the extended
 * property "X-PRODID" will be added, since {@link ProductId} is not
 * supported by that version.
 * @param include true to add the property, false not to (defaults to true)
 * @return this
 */
void ChainingWriter::prodId(bool include) {
    _prodId = include;
}

/**
 * Registers a property scribe.
 * @param scribe the scribe to register
 * @return this
 */
//void register(VCardPropertyScribe<? extends VCardProperty> scribe) {
//    if (index == null) {
//        index = new ScribeIndex();
//    }
//    index.register(scribe);
//    return this_;
//}

    
}
