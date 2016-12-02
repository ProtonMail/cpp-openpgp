//
//  vcard_property.hpp
//  OpenPGP
//
//  Created by Yanfeng Zhang on 12/2/16.
//  Copyright © 2016 Yanfeng Zhang. All rights reserved.
//

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
