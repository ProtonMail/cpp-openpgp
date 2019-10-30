//
//  gender.hpp
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

#ifndef gender_hpp
#define gender_hpp

#include <stdio.h>
#include <string>
#include <list>

#include "text_property.hpp"
#include "has_alt_Id.hpp"
#include "vcard.hpp"
#include "i_gender.hpp"
/**
 * <p>
 * Defines the person's sex.
 * </p>
 *
 * <p>
 * <b>Code sample (creating)</b>
 * </p>
 *
 * <pre class="brush:java">
 * VCard vcard = new VCard();
 *
 * Gender gender = Gender.male();
 * vcard.setGender(gender);
 * </pre>
 *
 * <p>
 * <b>Code sample (retrieving)</b>
 * </p>
 *
 * <pre class="brush:java">
 * VCard vcard = ...
 * Gender gender = vcard.getGender();
 * if (gender.isMale()) {
 *   //gender is male
 * } else if (gender.isFemale()) {
 *   //gender is female
 * }
 * //etc
 * </pre>
 *
 * <p>
 * <b>Property name:</b> {@code GENDER}
 * </p>
 * <p>
 * <b>Supported versions:</b> {@code 4.0}
 * </p>
 * @author Michael Angstadt
 * @see <a href="http://tools.ietf.org/html/rfc6350#page-32">RFC 6350 p.32</a>
 */
//@SupportedVersions(VCardVersion.V4_0)
namespace ezvcard {
    class Gender : public VCardProperty, public IGender { //, HasAltId {
//        public static final String MALE = "M";
//        public static final String FEMALE = "F";
//        public static final String OTHER = "O";
//        public static final String NONE = "N";
//        public static final String UNKNOWN = "U";
    public:
        const static std::string PROPERTYNAME;
        const static std::string CLASSNAME;
        
        typedef std::shared_ptr<Gender> Ptr;
        
    public:
        
        /**
         * Creates a gender property. Use of this constructor is discouraged. Please
         * use one of the static factory methods to create a new GENDER property.
         * @param gender the gender value (e.g. "F")
         */
        Gender(const std::string& gender) {
            _gender = gender;
        }

        /**
         * Gets the additional text associated with this property.
         * @return the additional text or null if there is no text
         */
        std::string getText() {
            return _text;
        }
        
        /**
         * Sets the additional text associated with this property.
         * @param text additional text or null to remove
         */
        void setText(const std::string& text) {
            _text = text;
        }
        
        /**
         * Gets the gender value.
         * @return the gender value (see static strings for the possible values)
         */
        std::string getGender() {
            return _gender;
        }
        
        /**
         * Sets the gender value.
         * @param gender the gender value (see static strings for the possible
         * values)
         */
        void setGender(const std::string& gender) {
            _gender = gender;
        }
        
    private:
        std::string _gender;
        std::string _text;
        
        
        std::string _className() {
            return Gender::CLASSNAME;
        }
        std::string _getPropertyName() {
            return Gender::PROPERTYNAME;
        }
//        /**
//         * Copy constructor.
//         * @param original the property to make a copy of
//         */
//        public Gender(Gender original) {
//            super(original);
//            gender = original.gender;
//            text = original.text;
//        }
//

//        /**
//         * Determines if the gender is "male" or not.
//         * @return true if the gender is "male", false if not
//         */
//        public boolean isMale() {
//            return MALE.equals(gender);
//        }
//
//        /**
//         * Determines if the gender is "female" or not.
//         * @return true if the gender is "female", false if not
//         */
//        public boolean isFemale() {
//            return FEMALE.equals(gender);
//        }
//
//        /**
//         * Determines if the gender is "other" or not.
//         * @return true if the gender is "other", false if not
//         */
//        public boolean isOther() {
//            return OTHER.equals(gender);
//        }
//
//        /**
//         * Determines if the gender is "none" or not. A group, organization, or
//         * location may have this gender property.
//         * @return true if the gender is "none", false if not
//         */
//        public boolean isNone() {
//            return NONE.equals(gender);
//        }
//
//        /**
//         * Determines if the gender is "unknown" or not.
//         * @return true if the gender is "unknown", false if not
//         */
//        public boolean isUnknown() {
//            return UNKNOWN.equals(gender);
//        }
//
//        /**
//         * Creates a gender property whose value is set to "male".
//         * @return a "male" gender property
//         */
//        public static Gender male() {
//            return new Gender(MALE);
//        }
//
//        /**
//         * Creates a gender property whose value is set to "female".
//         * @return a "female" gender property
//         */
//        public static Gender female() {
//            return new Gender(FEMALE);
//        }
//
//        /**
//         * Creates a gender property whose value is set to "other".
//         * @return an "other" gender property
//         */
//        public static Gender other() {
//            return new Gender(OTHER);
//        }
//
//        /**
//         * Creates a gender property whose value is set to "none". Groups,
//         * organizations, and locations should be given this gender property.
//         * @return a "none" gender property
//         */
//        public static Gender none() {
//            return new Gender(NONE);
//        }
//
//        /**
//         * Creates a gender property whose value is set to "unknown".
//         * @return a "unknown" gender property
//         */
//        public static Gender unknown() {
//            return new Gender(UNKNOWN);
//        }
//
//        @Override
//        protected void _validate(List<ValidationWarning> warnings, VCardVersion version, VCard vcard) {
//            if (gender == null) {
//                warnings.add(new ValidationWarning(8));
//            }
//        }
//
//        @Override
//        protected Map<String, Object> toStringValues() {
//            Map<String, Object> values = new LinkedHashMap<String, Object>();
//            values.put("gender", gender);
//            values.put("text", text);
//            return values;
//        }
//
//        @Override
//        public Gender copy() {
//            return new Gender(this);
//        }
//
//        @Override
//        public int hashCode() {
//            final int prime = 31;
//            int result = super.hashCode();
//            result = prime * result + ((gender == null) ? 0 : gender.hashCode());
//            result = prime * result + ((text == null) ? 0 : text.hashCode());
//            return result;
//        }
//
//        @Override
//        public boolean equals(Object obj) {
//            if (this == obj) return true;
//            if (!super.equals(obj)) return false;
//            Gender other = (Gender) obj;
//            if (gender == null) {
//                if (other.gender != null) return false;
//            } else if (!gender.equals(other.gender)) return false;
//            if (text == null) {
//                if (other.text != null) return false;
//            } else if (!text.equals(other.text)) return false;
//            return true;
//        }
    };
}



#endif /* gender_hpp */

