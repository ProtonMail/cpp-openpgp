//
//  chaining_writer.hpp
//  OpenPGP
//
//  Created by Yanfeng Zhang on 5/8/17.
//  Copyright © 2017 Yanfeng Zhang. All rights reserved.
//

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
