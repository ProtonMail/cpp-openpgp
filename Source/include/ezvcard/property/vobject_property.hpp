//
//  vobject_property.hpp
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
