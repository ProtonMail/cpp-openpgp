//
//  chaining_text_writer.hpp
//  OpenPGP
//
//  Created by Yanfeng Zhang on 5/8/17.
//  Copyright © 2017 Yanfeng Zhang. All rights reserved.
//

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
