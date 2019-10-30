//
//  calscale.cpp
//  OpenPGP
//
//  Created by Yanfeng Zhang on 1/10/17.
//  Copyright © 2017 Yanfeng Zhang. All rights reserved.
//

#include "calscale.hpp"
#include <sstream>
#include <iostream>

VCardParameterCaseClasses<Calscale> Calscale::enums;// = new VCardParameterCaseClasses<Calscale>(Calscale.class);

Calscale::Ptr Calscale::GREGORIAN = std::shared_ptr<Calscale>(new Calscale(true, "gregorian", {}));

Calscale::Calscale(bool predefine, const std::string& value, std::vector<VCardVersion::Ptr> support) : VCardParameter(value, support) {
    if (predefine)
        enums.setupPredefine(value, support);
}

Calscale::Calscale(const std::string& value, std::vector<VCardVersion::Ptr> support) : VCardParameter(value, support) {
    
}


Calscale::Calscale(const std::string& value, std::vector<VCardVersion::Ptr> support, bool preserveCase) : VCardParameter(value, support, preserveCase) {
    
}

/**
 * Searches for a parameter value that is defined as a static constant in
 * this class.
 * @param value the parameter value
 * @return the object or null if not found
 */
Calscale::Ptr Calscale::find(const std::string& value) {
    return enums.find(value);
}

/**
 * Searches for a parameter value and creates one if it cannot be found. All
 * objects are guaranteed to be unique, so they can be compared with
 * {@code ==} equality.
 * @param value the parameter value
 * @return the object
 */
Calscale::Ptr Calscale::get(const std::string& value) {
    return enums.get(value);
}

/**
 * Gets all of the parameter values that are defined as static constants in
 * this class.
 * @return the parameter values
 */
std::vector<Calscale::Ptr> Calscale::all() {
    return enums.all();
}


std::ostream& operator<<(std::ostream& stream, const Calscale::Ptr& base)
{
    stream << base->getValue() << "\t";
    return stream;
}

std::string Calscale::all_to_string() {
    std::stringstream ss;
    ss << "";
    auto all = enums.all();
    for(auto i : all) {
        ss << i;
    }
    
    return ss.str();
}
