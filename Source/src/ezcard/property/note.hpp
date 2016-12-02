//
//  note.hpp
//  OpenPGP
//
//  Created by Yanfeng Zhang on 1/10/17.
//  Copyright © 2017 Yanfeng Zhang. All rights reserved.
//

#ifndef note_hpp
#define note_hpp

#include <stdio.h>
#include "text_property.hpp"
#include "has_alt_Id.hpp"
#include "i_note.hpp"

namespace ezvcard {
    /**
     * <p>
     * Defines a free-form text field that contains miscellaneous information.
     * </p>
     *
     * <p>
     * <b>Code sample</b>
     * </p>
     *
     * <pre class="brush:java">
     * VCard vcard = new VCard();
     *
     * Note note = new Note("This is a\nnote property.");
     * vcard.addNote(note);
     * </pre>
     *
     * <p>
     * <b>Property name:</b> {@code NOTE}
     * </p>
     * <p>
     * <b>Supported versions:</b> {@code 2.1, 3.0, 4.0}
     * </p>
     * @author Michael Angstadt
     * @see <a href="http://tools.ietf.org/html/rfc6350#page-44">RFC 6350 p.44</a>
     * @see <a href="http://tools.ietf.org/html/rfc2426#page-21">RFC 2426 p.21</a>
     * @see <a href="http://www.imc.org/pdi/vcard-21.doc">vCard 2.1 p.19</a>
     */
    class Note : public TextProperty, public INote, HasAltId {
        
    public:
        typedef std::shared_ptr<Note> Ptr;
        const static std::string PROPERTYNAME;
        const static std::string CLASSNAME;
        
        /**
         * Creates a note property.
         * @param note the note text
         */
        Note(const std::string& note) : TextProperty(note) {
            
        }
        
        /**
         * Gets the TYPE parameter.
         * <p>
         * <b>Supported versions:</b> {@code 4.0}
         * </p>
         * @return the TYPE value (typically, this will be either "work" or "home")
         * or null if it doesn't exist
         */
        std::string getType() {
            return _parameters->getType();
        }
        
        /**
         * Sets the TYPE parameter.
         * <p>
         * <b>Supported versions:</b> {@code 4.0}
         * </p>
         * @param type the TYPE value (this should be either "work" or "home") or
         * null to remove
         */
        void setType(const std::string& type) {
            _parameters->setType(type);
        }
        
        std::string getNote() {
            return TextProperty::getValue();
        }
        
    protected:
        
        //
        //        /**
        //         * Copy constructor.
        //         * @param original the property to make a copy of
        //         */
        //        public Note(Note original) {
        //            super(original);
        //        }
        //
        //        @Override
        //        public List<Pid> getPids() {
        //            return super.getPids();
        //        }
        //
        //        @Override
        //        public Integer getPref() {
        //            return super.getPref();
        //        }
        //
        //        @Override
        //        public void setPref(Integer pref) {
        //            super.setPref(pref);
        //        }
        //
        //        //@Override
        //        public String getAltId() {
        //            return parameters.getAltId();
        //        }
        //
        //        //@Override
        //        public void setAltId(String altId) {
        //            parameters.setAltId(altId);
        //        }

        //        @Override
        //        public String getLanguage() {
        //            return super.getLanguage();
        //        }
        //
        //        @Override
        //        public void setLanguage(String language) {
        //            super.setLanguage(language);
        //        }
        //        
        //        @Override
        //        public Note copy() {
        //            return new Note(this);
        //        }
        
    protected: //PMObject
        std::string _className();
        std::string _getPropertyName();
        
    protected: //impl HasAltId
        std::string getAltId();
        void setAltId(const std::string& altId);
    };
}


#endif /* note_hpp */
