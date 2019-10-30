//
//  vcard_property.hpp
//  OpenPGP
//
//  Created by Yanfeng Zhang on 12/2/16.
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

#ifndef vcard_property_hpp
#define vcard_property_hpp

#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>
#include <list>

#include "vcard_parameters.hpp"
#include "vcard_version.hpp"
#include "warning.hpp"
#include "object_base.hpp"

namespace ezvcard {



class VCard;

class VCardProperty : public PMObject {
    
public:
    typedef std::shared_ptr<VCardProperty> Ptr;
    
protected:
    /**
     * The group that this property belongs to or null if it doesn't belong to a
     * group.
     */
    std::string _group;
    
    /**
     * The property's parameters.
     */
    VCardParameters::Ptr _parameters;
    
    //VCardProperty(VCardProperty original);
    virtual void _validate(std::list<ValidationWarning::Ptr>& warnings, const VCardVersion::Ptr& version, const std::shared_ptr<VCard>& vcard);
    //Map<String, Object> toStringValues()
    
    virtual std::vector<VCardVersion::Ptr> _getSupportedVersions() {
        return VCardVersion::values();
    }
    
public:
    
    VCardProperty();
    ~VCardProperty();
    std::vector<VCardVersion::Ptr> getSupportedVersions();
    bool isSupportedBy(VCardVersion::Ptr version);//
    VCardParameters::Ptr getParameters();
    void setParameters(VCardParameters::Ptr parameters);
    
    std::string getParameter(const std::string& name);
    std::vector<std::string> getParameters(const std::string& name);
    
    void setParameter(std::string name, std::string value);
    void addParameter(std::string name, std::string value);
    void removeParameter(std::string name);
    std::string getGroup();
    void setGroup(std::string group);
    //int compareTo(VCardProperty that) ;
    

    std::list<ValidationWarning::Ptr> validate(const VCardVersion::Ptr& version, const std::shared_ptr<VCard>& vcard);
    
    
//    public String toString() ;
//    public VCardProperty copy();
//    public int hashCode();
//    List<Pid> getPids();
//    Integer getPref();
//    void setPref(Integer pref);
//    String getLanguage();
//    void setLanguage(String language);
//    Integer getIndex();
//    void setIndex(Integer index);
    
public:
    virtual void Print();
    virtual bool isBinaryProperty() {
        return false;
    }
    virtual bool isDataNull() {
        return false;
    }
    
    virtual bool equals(const VCardProperty::Ptr& obj);
};


}

#endif /* vcard_property_hpp */
