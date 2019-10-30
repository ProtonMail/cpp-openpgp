//
//  chaining_text_writer.hpp
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

#ifndef chaining_text_writer_hpp
#define chaining_text_writer_hpp

#include <stdio.h>
#include "chaining_writer.hpp"
#include "vcard_writer.hpp"

namespace ezvcard {
    

class ChainingTextWriter : public ChainingWriter {
    
public:
    typedef std::shared_ptr<ChainingTextWriter> Ptr;


private:
    VCardVersion::Ptr _version;
    bool _caretEncoding = false;
    bool _includeTrailingSemicolons;
    TargetApplication _targetApplication = TargetApplication::Others;

    void go(const VCardWriter::Ptr& writer);
    VCardVersion::Ptr getVCardWriterConstructorVersion();
    
    
public:
    ChainingTextWriter(std::vector<VCard::Ptr> vcards);
    std::string go();
    
    void go(const std::shared_ptr<std::stringstream>& writer);
    void version(const VCardVersion::Ptr& version);
    void caretEncoding(bool enable);
    void targetApplication(TargetApplication targetApplication);
    
    //public void go(OutputStream out);
    //public void go(File file);
    //public void go(File file, boolean append);
    //void go(Writer writer)

//    public ChainingTextWriter includeTrailingSemicolons(Boolean include);


    
};
    
    
}

#endif /* chaining_text_writer_hpp */
