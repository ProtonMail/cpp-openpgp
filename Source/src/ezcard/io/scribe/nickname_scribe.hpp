//
//  nickname_scribe.hpp
//  OpenPGP
//
//  Created by Yanfeng Zhang on 6/23/17.
//  Copyright © 2017 Yanfeng Zhang. All rights reserved.
//

#ifndef nickname_scribe_hpp
#define nickname_scribe_hpp

#include <stdio.h>
#include "nick_name.hpp"
#include "list_property_scribe.hpp"

namespace ezvcard {
    
    /**
     * Marshals {@link Nickname} properties.
     * @author Michael Angstadt
     */
    class NicknameScribe : public ListPropertyScribe<Nickname> {
    public:
        typedef std::shared_ptr<NicknameScribe> Ptr;
        
        NicknameScribe() : ListPropertyScribe(Nickname::PROPERTYNAME) {
            
        }
        
//        @Override
//        protected Nickname _parseHtml(HCardElement element, ParseContext context) {
//            Nickname property = _newInstance();
//            property.getValues().add(element.value());
//            return property;
//        }
//        
        
    protected:
        Nickname::Ptr _newInstance() {
            return std::make_shared<Nickname>();
        }
        
        std::string _className() {
            return "NicknameScribe";
        }
    };
}




#endif /* nickname_scribe_hpp */
