//
//  chaining_writer.hpp
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


#ifndef chaining_writer_hpp
#define chaining_writer_hpp

#include <stdio.h>
#include <vector>
#include "vcard.hpp"
#include "scribe_index.hpp"

namespace ezvcard {
    

class ChainingWriter {
    
protected:
    
    std::vector<VCard::Ptr> _vcards;
    
    ScribeIndex::Ptr _index;
    bool _prodId = true;
    bool _versionStrict = true;
    
public:
    
    ChainingWriter(std::vector<VCard::Ptr> vcards);
    
    void versionStrict(bool versionStrict);
    void prodId(bool include);
    
    //void register(VCardPropertyScribe<? extends VCardProperty> scribe);
};

}
#endif /* chaining_writer_hpp */
