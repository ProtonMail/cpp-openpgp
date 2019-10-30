//
//  pm_custom_property.hpp
//  OpenPGP
//
//  Created by Yanfeng Zhang on 6/26/17.
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

#ifndef pm_mimetype_property_hpp
#define pm_mimetype_property_hpp

#include <stdio.h>
#include "text_property.hpp"
#include "has_alt_Id.hpp"
#include "i_p_m_mime_type.hpp"

namespace ezvcard {
    class PMMimeType : public TextProperty, public IPMMimeType, HasAltId {
        
    public:
        typedef std::shared_ptr<PMMimeType> Ptr;
        const static std::string PROPERTYNAME;
        const static std::string CLASSNAME;
        
        PMMimeType(const std::string& custom) : TextProperty(custom) {
            
        }
        
        std::string getType() {
            return _parameters->getType();
        }
        
        void setType(const std::string& type) {
            _parameters->setType(type);
        }
        
        std::string getValue() {
            return TextProperty::getValue();
        }
        
        std::string getGroup() final {
            return TextProperty::getGroup();
        }
        
        void setGroup(const std::string & g) final {
            TextProperty::setGroup(g);
        }
        
    protected: //PMObject
        std::string _className();
        std::string _getPropertyName();
        
    protected: //impl HasAltId
        std::string getAltId();
        void setAltId(const std::string& altId);
    };
}

#endif /* pm_scheme_property_hpp */
