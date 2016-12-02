//
//  title_scribe.hpp
//  OpenPGP
//
//  Created by Yanfeng Zhang on 6/12/17.
//  Copyright © 2017 Yanfeng Zhang. All rights reserved.
//

#ifndef title_scribe_hpp
#define title_scribe_hpp

#include <stdio.h>
#include "string_property_scribe.hpp"
#include "title.hpp"

namespace ezvcard {
    
    /**
     * Marshals {@link Title} properties.
     * @author Michael Angstadt
     */
    class TitleScribe : public StringPropertyScribe<Title> {
    public:
        typedef std::shared_ptr<TitleScribe> Ptr;
        TitleScribe();
        
        
    protected:
        Title::Ptr _parseValue(const std::string& value);
        
        
    protected://PMObject
        std::string _className() {
            return "TitleScribe";
        }
    };
    
}

#endif /* title_scribe_hpp */
