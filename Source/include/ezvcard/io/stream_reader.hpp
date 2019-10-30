//
//  StreamReader.hpp
//  OpenPGP
//
//  Created by Yanfeng Zhang on 12/2/16.
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

#ifndef StreamReader_hpp
#define StreamReader_hpp


#include <ezvcard/io/scribe/scribe_index.hpp>
#include <ezvcard/vcard.hpp>
#include <list>

#include <ezvcard/io/parse_warnings.hpp>

namespace ezvcard {
    

class StreamReader {
protected:
    ParseWarnings _warnings = ParseWarnings();
    ScribeIndex::Ptr _index = std::make_shared<ScribeIndex>();
    virtual VCard::Ptr _readNext() = 0;
    //
    //    /**
    //     * Matches up a list of {@link Label} properties with their corresponding
    //     * {@link Address} properties. If no match can be found, then the LABEL
    //     * property itself is assigned to the vCard.
    //     * @param vcard the vCard that the properties belong to
    //     * @param labels the LABEL properties
    //     */
    //    protected void assignLabels(VCard vcard, List<Label> labels);
    
public:
    typedef std::shared_ptr<StreamReader> Ptr;
    
    void setScribeIndex(ScribeIndex::Ptr index);
    ScribeIndex::Ptr getScribeIndex();
    VCard::Ptr readNext();
    std::list<VCard::Ptr> readAll();
    //void registerScribe(VCardPropertyScribe<? extends VCardProperty> scribe)
    std::list<std::string> getWarnings();
};

}
#endif /* StreamReader_hpp */
