//
//  vobject_data_listener.hpp
//  OpenPGP
//
//  Created by Yanfeng Zhang on 12/5/16.
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

#ifndef vobject_data_listener_hpp
#define vobject_data_listener_hpp

#include <string>
#include <ezvcard/io/context.hpp>
#include <ezvcard/property/vobject_property.hpp>
#include <ezvcard/io/warning.hpp>


namespace vinnie {
    
    
    class VObjectDataListener {
    public:
        typedef std::shared_ptr<VObjectDataListener> Ptr;
        
        virtual void onComponentBegin(const std::string& name, const Context::Ptr &context) = 0;
        
        virtual void onComponentEnd(const std::string& name, const Context::Ptr &context) = 0;
        
        virtual void onProperty(const VObjectProperty::Ptr& property, const Context::Ptr &context) = 0;
        
        virtual void onVersion(const std::string& value, const Context::Ptr &context) = 0;
        
        virtual void onWarning( Warning::TYPE warning, const VObjectProperty::Ptr& property, std::exception* thrown, const Context::Ptr &context) = 0;
    };
    
}

#endif /* vobject_data_listener_hpp */
