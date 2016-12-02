//
//  url_scribe.hpp
//  OpenPGP
//
//  Created by Yanfeng Zhang on 6/4/17.
//  Copyright © 2017 Yanfeng Zhang. All rights reserved.
//

#ifndef url_scribe_hpp
#define url_scribe_hpp

#include "uri_property_scribe.hpp"
#include "url.hpp"

namespace ezvcard {
    

class UrlScribe : public UriPropertyScribe<Url> {
    
public:
    typedef std::shared_ptr<UrlScribe> Ptr;
    
    UrlScribe() : UriPropertyScribe<Url>(Url::PROPERTYNAME) {
        
    }
    
    
protected:
    Url::Ptr _parseValue(const std::string& value) {
        return std::make_shared<Url>(value);
    }
    std::string _className() {
        return "UrlScribe";
    }
};

}
#endif /* url_scribe_hpp */
