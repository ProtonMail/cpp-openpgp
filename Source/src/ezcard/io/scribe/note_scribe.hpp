//
//  note_scribe.hpp
//  OpenPGP
//
//  Created by Yanfeng Zhang on 6/13/17.
//  Copyright © 2017 Yanfeng Zhang. All rights reserved.
//

#ifndef note_scribe_hpp
#define note_scribe_hpp

#include <stdio.h>
#include "note.hpp"
#include "string_property_scribe.hpp"


namespace ezvcard {
    /**
     * Marshals {@link Note} properties.
     * @author Michael Angstadt
     */
    class NoteScribe : public StringPropertyScribe<Note> {
    public:
        NoteScribe() : StringPropertyScribe(Note::PROPERTYNAME) {
        }
        
    protected:
        Note::Ptr _parseValue(const std::string& value) {
            return std::make_shared<Note>(value);
        }
        
        std::string _className() {
            return "NoteScribe";
        }

    };
}

#endif /* note_scribe_hpp */
