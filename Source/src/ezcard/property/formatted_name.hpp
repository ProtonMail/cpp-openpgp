//
//  formatted_name.hpp
//  OpenPGP
//
//  Created by Yanfeng Zhang on 1/10/17.
//  Copyright © 2017 Yanfeng Zhang. All rights reserved.
//

#ifndef formatted_name_hpp
#define formatted_name_hpp

#include <stdio.h>
#include <string>
#include <list>

#include "text_property.hpp"
#include "has_alt_Id.hpp"
#include "pid.hpp"
#include <bridge/i_formatted_name.hpp>

using namespace ProtonMail;

namespace ezvcard {
    

class FormattedName : public TextProperty, HasAltId, public IFormattedName {

public:
    const static std::string PROPERTYNAME;
    const static std::string CLASSNAME;
    
    typedef std::shared_ptr<FormattedName> Ptr;
    ~FormattedName();
    FormattedName(const std::string& name);
    //FormattedName(const FormattedName::Ptr& original);
    //FormattedName(const FormattedName* original);
    std::string getType();
    
    void setType(std::string type);
    //std::string getLanguage();
    //void setLanguage(std::string language);
    std::list<Pid::Ptr> getPids();
    int getPref(); //TODO::could try to use int64_t later
    void setPref(int pref);
    //FormattedName::Ptr copy();
    
protected: //PMObject part
    //override
    std::string _className() {
        return CLASSNAME;
    }
    
    std::string _getPropertyName() {
        return PROPERTYNAME;
    }
    
protected:
    std::string getAltId();
    void setAltId(const std::string& altId);

public://IFormattedName impl
    
    std::string getLanguage() final;
    void setLanguage(const std::string & language) final;
    std::string getValue() final;
    std::string getParameter(const std::string & name) final;
    
};

}

#endif /* formatted_name_hpp */
