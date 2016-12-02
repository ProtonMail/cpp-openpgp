//
//  calscale.hpp
//  OpenPGP
//
//  Created by Yanfeng Zhang on 1/10/17.
//  Copyright © 2017 Yanfeng Zhang. All rights reserved.
//

#ifndef calscale_hpp
#define calscale_hpp

#include <stdio.h>
#include "vcard_parameter.hpp"
#include "vcard_parameter_case_classes.hpp"

class Calscale : public VCardParameter {
private:
    static VCardParameterCaseClasses<Calscale> enums;
    
    Calscale(bool predefine, const std::string& value, std::vector<VCardVersion::Ptr> support);
    
protected:
    std::string _className() {
        return "Calscale";
    }
    
    std::string _getPropertyName() {
        return "";
    }
    
public:
    typedef std::shared_ptr<Calscale> Ptr;
    
    static Calscale::Ptr GREGORIAN;// = new Calscale("gregorian");
    
    Calscale(const std::string& value, std::vector<VCardVersion::Ptr> support);
    Calscale(const std::string& value, std::vector<VCardVersion::Ptr> support, bool preserveCase);
    
    static Calscale::Ptr find(const std::string& value);
    static Calscale::Ptr get(const std::string& value);
    static std::vector<Calscale::Ptr> all();
    static std::string all_to_string();
    

    
};



#endif /* calscale_hpp */
