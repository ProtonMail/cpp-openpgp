//
//  key_scribe.hpp
//  OpenPGP
//
//  Created by Yanfeng Zhang on 4/4/18.
//  Copyright © 2018 Yanfeng Zhang. All rights reserved.
//

#ifndef key_scribe_hpp
#define key_scribe_hpp

#include "binary_property_scribe.hpp"
#include "key.hpp"
#include "key_type.hpp"


namespace ezvcard {
    
    class KeyScribe : public BinaryPropertyScribe<Key, KeyType> {
    public:
        typedef std::shared_ptr<KeyScribe> Ptr;
        
        KeyScribe();
        
        std::string _className() {
            return "KeyScribe";
        }
        
    protected:

        KeyType::Ptr _mediaTypeFromMediaTypeParameter(const std::string& mediaType) {
            return KeyType::get("", mediaType, "");
        }
        
        KeyType::Ptr _mediaTypeFromTypeParameter(const std::string& type)  {
            return KeyType::get(type, "", "");
        }
        
        KeyType::Ptr _mediaTypeFromFileExtension(const std::string& extension) {
            return KeyType::get("", "", extension);
        }

        Key::Ptr _newInstance(const std::string& uri_or_data, const KeyType::Ptr& contentType, bool isBinary) {
            return  std::make_shared<Key>(uri_or_data, contentType, isBinary);
        }
    };
}

#endif /* key_scribe_hpp */
