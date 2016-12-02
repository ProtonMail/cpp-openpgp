//
//  birthday_scribe.hpp
//  OpenPGP
//
//  Created by Yanfeng Zhang on 6/12/17.
//  Copyright © 2017 Yanfeng Zhang. All rights reserved.
//

#ifndef birthday_scribe_hpp
#define birthday_scribe_hpp

#include <stdio.h>
#include "date_or_time_property_scribe.hpp"
#include "birthday.hpp"

namespace ezvcard {
    
    /**
     * Marshals {@link Birthday} properties.
     * @author Michael Angstadt
     */
    class BirthdayScribe : public DateOrTimePropertyScribe<Birthday> {
    public:
        typedef std::shared_ptr<BirthdayScribe> Ptr;
        BirthdayScribe() : DateOrTimePropertyScribe(Birthday::PROPERTYNAME) {
            
        }
        
    protected:
        Birthday::Ptr _newInstance(const std::string& text) {
            return std::make_shared<Birthday>(text);
        }
        
        
        Birthday::Ptr _newInstance(const std::string& date, bool hasTime) {
            return std::make_shared<Birthday>(date, hasTime);
        }
        //
        //        @Override
        //        protected Birthday newInstance(PartialDate partialDate) {
        //            return new Birthday(partialDate);
        //        }
        
        std::string _className() final {
            return "BirthdayScribe";
        }
        
    };
    
}

#endif /* birthday_scribe_hpp */
