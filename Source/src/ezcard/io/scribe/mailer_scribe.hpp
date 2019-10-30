//
//  mailer_scribe.hpp
//  OpenPGP
//
//  Created by Yanfeng Zhang on 5/19/17.
//  Copyright © 2017 Yanfeng Zhang. All rights reserved.
//

#ifndef mailer_scribe_hpp
#define mailer_scribe_hpp

#include <stdio.h>
#include "string_property_scribe.hpp"
#include "mailer.hpp"

namespace ezvcard {
    

/**
 * Marshals {@link Mailer} properties.
 * @author Michael Angstadt
 */
class MailerScribe : public StringPropertyScribe<Mailer> {
public:
    typedef std::shared_ptr<MailerScribe> Ptr;
    
    MailerScribe();
    
protected:
    Mailer::Ptr _parseValue(const std::string& value) {
        auto mailer = std::make_shared<Mailer>(value);
        return mailer;
    }
    
    std::string _className() {
        return "MailerScribe";
    }
};

    
}


#endif /* mailer_scribe_hpp */
