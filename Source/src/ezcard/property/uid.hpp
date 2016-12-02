//
//  uid.hpp
//  OpenPGP
//
//  Created by Yanfeng Zhang on 1/10/17.
//  Copyright © 2017 Yanfeng Zhang. All rights reserved.
//

#ifndef uid_hpp
#define uid_hpp

#include "uri_property.hpp"
#include "has_alt_Id.hpp"

#include <bridge/i_uid.hpp>

using namespace ProtonMail;

namespace ezvcard {
    
    
    class Uid : public UriProperty, public IUid, HasAltId {
    public:
        const static std::string PROPERTYNAME;
        const static std::string CLASSNAME;
        
        typedef std::shared_ptr<Uid> Ptr;
        
    public:
        /**
         * Creates a UID property.
         * @param uuid the URL (e.g. "http://example.com")
         */
        Uid(const std::string& uuid) : UriProperty(uuid) {
            
        }
        
        
    protected:
        std::string _className() {
            return CLASSNAME;
        }
        
        std::string _getPropertyName() {
            return PROPERTYNAME;
        }
        
        std::string getAltId();
        void setAltId(const std::string& altId);
        
    public: // bridge IUid impl
        std::string getValue();
        
    };
    
}


#endif /* uid_hpp */
