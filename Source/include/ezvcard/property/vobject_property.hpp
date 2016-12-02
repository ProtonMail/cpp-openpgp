//
//  vobject_property.hpp
//  OpenPGP
//
//  Created by Yanfeng Zhang on 12/5/16.
//  Copyright © 2016 Yanfeng Zhang. All rights reserved.
//

#ifndef vobject_property_hpp
#define vobject_property_hpp

#include <string>
#include <ezvcard/parameter/vobject_parameters.hpp>


namespace vinnie {
    
    class VObjectProperty {
    public:
        typedef std::shared_ptr<VObjectProperty> Ptr;
        
    private:
        std::string _group;
        std::string _name;
        VObjectParameters::Ptr _parameters;
        std::string _value;
        
    public:
        
        ~VObjectProperty();
        VObjectProperty();
        VObjectProperty(const std::string& name, const std::string& value);
        VObjectProperty(const std::string& group, const std::string& name, const std::string& value);
        VObjectProperty(const std::string& group, const std::string&, const VObjectParameters::Ptr& parameters, const std::string& value);
        std::string getGroup();
        void setGroup(const std::string& group);
        std::string getName();
        void setName(const std::string& name);
        VObjectParameters::Ptr getParameters();
        void setParameters(const VObjectParameters::Ptr& parameters);
        std::string getValue();
        void setValue(const std::string& value);
        std::string toString();
        
        bool equals(const Ptr& obj);
        
        //public int hashCode();
    };
    
}
#endif /* vobject_property_hpp */
