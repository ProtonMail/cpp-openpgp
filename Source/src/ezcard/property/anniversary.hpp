//
//  anniversary.hpp
//  OpenPGP
//
//  Created by Yanfeng Zhang on 1/10/17.
//
//  The MIT License
// 
//  Copyright (c) 2019 Proton Technologies AG
// 
//  Permission is hereby granted, free of charge, to any person obtaining a copy
//  of this software and associated documentation files (the "Software"), to deal
//  in the Software without restriction, including without limitation the rights
//  to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
//  copies of the Software, and to permit persons to whom the Software is
//  furnished to do so, subject to the following conditions:
// 
//  The above copyright notice and this permission notice shall be included in
//  all copies or substantial portions of the Software.
// 
//  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
//  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
//  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
//  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
//  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
//  OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
//  THE SOFTWARE.


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
