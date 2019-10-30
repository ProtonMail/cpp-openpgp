//
//  stream_writer.hpp
//  OpenPGP
//
//  Created by Yanfeng Zhang on 5/17/17.
//  Copyright © 2017 Yanfeng Zhang. All rights reserved.
//

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
