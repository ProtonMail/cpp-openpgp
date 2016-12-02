//
//  formatted_name_scribe.hpp
//  OpenPGP
//
//  Created by Yanfeng Zhang on 1/11/17.
//  Copyright © 2017 Yanfeng Zhang. All rights reserved.
//

#ifndef formatted_name_scribe_hpp
#define formatted_name_scribe_hpp

#include <stdio.h>
#include "string_property_scribe.hpp"
#include "formatted_name.hpp"

namespace ezvcard {
    
class FormattedNameScribe : public StringPropertyScribe<FormattedName> {
public:
    FormattedNameScribe();

protected:
    FormattedName::Ptr _parseValue(const std::string& value) {
        auto name = std::make_shared<FormattedName>(value);
        return name;
    }
    
    std::string _className() {
        return "FormattedNameScribe";
    }
};

}
#endif /* formatted_name_scribe_hpp */
