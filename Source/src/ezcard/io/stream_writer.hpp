//
//  stream_writer.hpp
//  OpenPGP
//
//  Created by Yanfeng Zhang on 5/17/17.
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

#ifndef stream_writer_hpp
#define stream_writer_hpp

#include <stdio.h>
#include "scribe_index.hpp"
#include "vcard.hpp"

namespace ezvcard {
    
class StreamWriter {
    
protected:
    ScribeIndex::Ptr _index = std::make_shared<ScribeIndex>();
    bool _addProdId = true;
    bool _versionStrict = true;
    
    /**
     * Writes a vCard to the stream.
     * @param vcard the vCard that is being written
     * @param properties the properties to write
     * @throws IOException if there's a problem writing to the output stream
     */
    virtual void _write(VCard::Ptr vcard, std::vector<VCardProperty::Ptr> properties) = 0;
    
    /**
     * Gets the version that the next vCard will be written as.
     * @return the version
     */
    virtual VCardVersion::Ptr getTargetVersion() = 0;
    
public:
    void write(VCard::Ptr vcard);
    
    bool isAddProdId();
    
    void setAddProdId(bool addProdId);
    bool isVersionStrict();
    void setVersionStrict(bool versionStrict);
    ScribeIndex::Ptr getScribeIndex();
    void setScribeIndex(ScribeIndex::Ptr index);
    
    //void registerScribe(VCardPropertyScribe<? extends VCardProperty> scribe);
    
private:
    std::vector<VCardProperty::Ptr> prepare(VCard::Ptr vcard);
    
};

    
}

#endif /* stream_writer_hpp */
