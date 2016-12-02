//
//  birthday.hpp
//  OpenPGP
//
//  Created by Yanfeng Zhang on 1/10/17.
//  Copyright © 2017 Yanfeng Zhang. All rights reserved.
//

#ifndef birthday_hpp
#define birthday_hpp

#include <stdio.h>
#include "date_or_time_property.hpp"
#include "i_birthday.hpp"

//!!
namespace ezvcard {
    
    
    /**
     * <p>
     * Defines the person's birthday.
     * </p>
     *
     * <p>
     * <b>Code sample (creating)</b>
     * </p>
     *
     * <pre class="brush:java">
     * VCard vcard = new VCard();
     *
     * //date
     * Calendar c = Calendar.getInstance();
     * c.clear();
     * c.set(Calendar.YEAR, 1912);
     * c.set(Calendar.MONTH, Calendar.JUNE);
     * c.set(Calendar.DAY_OF_MONTH, 23);
     * Birthday bday = new Birthday(c.getTime());
     * vcard.setBirthday(bday);
     *
     * //partial date (e.g. just the month and date, vCard 4.0 only)
     * bday = new Birthday(PartialDate.date(null, 6, 23)); //June 23
     * vcard.setBirthday(bday);
     *
     * //plain text value (vCard 4.0 only)
     * bday = new Birthday("Don't even go there, dude...");
     * vcard.setBirthday(bday);
     * </pre>
     *
     * <p>
     * <b>Code sample (retrieving)</b>
     * </p>
     *
     * <pre class="brush:java">
     * VCard vcard = ...
     * Birthday bday = vcard.getBirthday();
     *
     * Date date = bday.getDate();
     * if (date != null) {
     *   //property value is a date
     * }
     *
     * PartialDate partialDate = bday.getPartialDate();
     * if (partialDate != null) {
     *   //property value is a partial date
     *   int year = partialDate.getYear();
     *   int month = partialDate.getMonth();
     * }
     *
     * String text = bday.getText();
     * if (text != null) {
     *   //property value is plain text
     * }
     * </pre>
     *
     * <p>
     * <b>Property name:</b> {@code BDAY}
     * </p>
     * <p>
     * <b>Supported versions:</b> {@code 2.1, 3.0, 4.0}
     * </p>
     * @author Michael Angstadt
     * @see <a href="http://tools.ietf.org/html/rfc6350#page-30">RFC 6350 p.30</a>
     * @see <a href="http://tools.ietf.org/html/rfc2426#page-11">RFC 2426 p.11</a>
     * @see <a href="http://www.imc.org/pdi/vcard-21.doc">vCard 2.1 p.11</a>
     */
    class Birthday : public DateOrTimeProperty, public IBirthday {
    public:
        typedef std::shared_ptr<Birthday> Ptr;
        const static std::string PROPERTYNAME;
        const static std::string CLASSNAME;
        
        //        /**
        //         * Creates a birthday property.
        //         * @param date the birthday
        //         */
        //        public Birthday(Date date) {
        //            super(date);
        //        }
        
        /**
         * Creates a birthday property.
         * @param date the birthday
         * @param hasTime true to include the date's time component, false if it's
         * strictly a date
         */
        Birthday(const std::string& date, bool hasTime) : DateOrTimeProperty(date, hasTime) {
            //super(date, hasTime);
        }
        
        /**
         //         * Creates a birthday property.
         //         * @param partialDate the birthday (vCard 4.0 only)
         //         */
        //        public Birthday(PartialDate partialDate) {
        //            super(partialDate);
        //        }
        //
        /**
         * Creates a birthday property.
         * @param text the text value (vCard 4.0 only)
         */
        Birthday(const std::string& text) : DateOrTimeProperty(text) {
            
        }
        
        //        /**
        //         * Copy constructor.
        //         * @param original the property to make a copy of
        //         */
        //        public Birthday(Birthday original) {
        //            super(original);
        //        }
        //
        //        @Override
        //        public Birthday copy() {
        //            return new Birthday(this);
        //        }
        
        std::string getDate() final;
        std::string getText() final;
        std::vector<std::string> getTypes();
        std::string getType() final;
        void setType(const std::string& type);
    protected:
        std::string _className();
        std::string _getPropertyName();
        
        std::string getAltId();
        void setAltId(const std::string& altId);
    };
    
    
}



#endif /* birthday_hpp */
