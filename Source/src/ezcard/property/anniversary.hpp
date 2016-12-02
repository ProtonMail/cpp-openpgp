//
//  anniversary.hpp
//  OpenPGP
//
//  Created by Yanfeng Zhang on 1/10/17.
//  Copyright © 2017 Yanfeng Zhang. All rights reserved.
//

#ifndef anniversary_hpp
#define anniversary_hpp

#include "i_anniversary.hpp"


namespace ezvcard {
    
    
//    /**
//     * <p>
//     * Defines the person's anniversary (marital or work-related).
//     * </p>
//     *
//     * <p>
//     * <b>Code sample (creating)</b>
//     * </p>
//     *
//     * <pre class="brush:java">
//     * VCard vcard = new VCard();
//     *
//     * //date
//     * Calendar c = Calendar.getInstance();
//     * c.clear();
//     * c.set(Calendar.YEAR, 1970);
//     * c.set(Calendar.MONTH, Calendar.MARCH);
//     * c.set(Calendar.DAY_OF_MONTH, 21);
//     * Anniversary anniversary = new Anniversary(c.getTime());
//     * vcard.setAnniversary(anniversary);
//     *
//     * //partial date (e.g. just the month and date)
//     * PartialDate date = PartialDate.date(null, 3, 21);
//     * anniversary = new Anniversary(date); //March 21
//     * vcard.setAnniversary(anniversary);
//     *
//     * //plain text value
//     * anniversary = new Anniversary("Over 20 years ago!");
//     * vcard.setAnniversary(anniversary);
//     * </pre>
//     *
//     * <p>
//     * <b>Code sample (retrieving)</b>
//     * </p>
//     *
//     * <pre class="brush:java">
//     * VCard vcard = ...
//     * Anniversary anniversary = vcard.getAnniversary();
//     *
//     * Date date = anniversary.getDate();
//     * if (date != null) {
//     *   //property value is a date
//     * }
//     *
//     * PartialDate partialDate = anniversary.getPartialDate();
//     * if (partialDate != null) {
//     *   //property value is a partial date
//     *   int year = partialDate.getYear();
//     *   int month = partialDate.getMonth();
//     * }
//     *
//     * String text = anniversary.getText();
//     * if (text != null) {
//     *   //property value is plain text
//     * }
//     * </pre>
//     *
//     * <p>
//     * <b>Property name:</b> {@code ANNIVERSARY}
//     * </p>
//     * <p>
//     * <b>Supported versions:</b> {@code 4.0}
//     * </p>
//     * @author Michael Angstadt
//     * @see <a href="http://tools.ietf.org/html/rfc6350#page-31">RFC 6350 p.31</a>
//     */
//    @SupportedVersions(VCardVersion.V4_0)
    
    
//    class Anniversary : public IAnniversary {
//        Anniversary() {
//            
//        }
//    };
    
//    public class Anniversary extends DateOrTimeProperty {
//        /**
//         * Creates an anniversary property.
//         * @param date the anniversary date
//         */
//        public Anniversary(Date date) {
//            super(date);
//        }
//        
//        /**
//         * Creates an anniversary property.
//         * @param date the anniversary date
//         * @param hasTime true to include the date's time component, false if it's
//         * strictly a date
//         */
//        public Anniversary(Date date, boolean hasTime) {
//            super(date, hasTime);
//        }
//        
//        /**
//         * Creates an anniversary property.
//         * @param partialDate the partial anniversary date (vCard 4.0 only)
//         */
//        public Anniversary(PartialDate partialDate) {
//            super(partialDate);
//        }
//        
//        /**
//         * Creates an anniversary property.
//         * @param text the text value (vCard 4.0 only)
//         */
//        public Anniversary(String text) {
//            super(text);
//        }
//        
//        /**
//         * Copy constructor.
//         * @param original the property to make a copy of
//         */
//        public Anniversary(Anniversary original) {
//            super(original);
//        }
//        
//        @Override
//        public Anniversary copy() {
//            return new Anniversary(this);
//        }
//    }
}


#endif /* anniversary_hpp */
