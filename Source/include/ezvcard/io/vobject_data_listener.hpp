//
//  vobject_data_listener.hpp
//  OpenPGP
//
//  Created by Yanfeng Zhang on 12/5/16.
//  Copyright © 2016 Yanfeng Zhang. All rights reserved.
//

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
