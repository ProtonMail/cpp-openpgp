//
//  uid.hpp
//  OpenPGP
//
//  Created by Yanfeng Zhang on 1/10/17.
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
