//
//  uid_scribe.hpp
//  OpenPGP
//
//  Created by Yanfeng Zhang on 9/6/17.
//  Copyright © 2017 Yanfeng Zhang. All rights reserved.
//

#ifndef uid_scribe_hpp
#define uid_scribe_hpp


#include "uri_property_scribe.hpp"
#include "uid.hpp"

namespace ezvcard {
    
    
    class UidScribe : public UriPropertyScribe<Uid> {
        
    public:
        typedef std::shared_ptr<UidScribe> Ptr;
        
        UidScribe() : UriPropertyScribe<Uid>(Uid::PROPERTYNAME) {
            
        }
        
        
    protected:
        Uid::Ptr _parseValue(const std::string& value) {
            return std::make_shared<Uid>(value);
        }
        std::string _className() {
            return "UidScribe";
        }
    };
    
}
#endif /* uid_scribe_hpp */
