//
//  key_scribe.hpp
//  OpenPGP
//
//  Created by Yanfeng Zhang on 4/4/18.
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
