//
//  vcard_data_type.cpp
//  OpenPGP
//
//  Created by Yanfeng Zhang on 12/2/16.
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

#include "vcard_data_type.hpp"



/**
 * A uniform resource locator (e.g. "http://www.example.com/image.jpg").
 * This data type is only used in 2.1 vCards. All other vCard versions use
 * {@link #URI}.
 * @SupportedVersions(V2_1)
 */
const VCardDataType::Ptr VCardDataType::URL = std::make_shared<VCardDataType>("url", std::vector<VCardVersion::Ptr> { VCardVersion::V2_1() });

/**
 * Refers to a MIME entity within an email.
 * @SupportedVersions(V2_1)
 */
const VCardDataType::Ptr VCardDataType::CONTENT_ID = std::make_shared<VCardDataType>("content-id", std::vector<VCardVersion::Ptr> { VCardVersion::V2_1() });

/**
 * A non-textual value, such as a picture or sound file.
 * @SupportedVersions(V3_0)
 */
const VCardDataType::Ptr VCardDataType::BINARY = std::make_shared<VCardDataType>("binary", std::vector<VCardVersion::Ptr> { VCardVersion::V3_0() });

/**
 * A uniform resource identifier (e.g. "http://www.example.com/image.jpg").
 * 2.1 vCards use {@link #URL} instead.
 * @SupportedVersions({ V3_0, V4_0 })
 */
const VCardDataType::Ptr VCardDataType::URI = std::make_shared<VCardDataType>("uri", std::vector<VCardVersion::Ptr> { VCardVersion::V3_0(), VCardVersion::V4_0() });

/**
 * A plain text value.
 */
const VCardDataType::Ptr VCardDataType::TEXT = std::make_shared<VCardDataType>("text", VCardVersion::values());

/**
 * A date that does not have a time component (e.g. "2015-02-16").
 * @SupportedVersions({ V3_0, V4_0 })
 */

const VCardDataType::Ptr VCardDataType::DATE             = std::make_shared<VCardDataType>("date", std::vector<VCardVersion::Ptr> { VCardVersion::V3_0(), VCardVersion::V4_0() });

/**
 * A time that does not have a date component (e.g. "08:34:00").
 * @SupportedVersions({ V3_0, V4_0 })
 */
const VCardDataType::Ptr VCardDataType::TIME             = std::make_shared<VCardDataType>("time", std::vector<VCardVersion::Ptr> { VCardVersion::V3_0(), VCardVersion::V4_0() });

/**
 * A date with a time component (e.g. "2015-02-16 08:34:00").
 * @SupportedVersions({ V3_0, V4_0 })
 */
const VCardDataType::Ptr VCardDataType::DATE_TIME        = std::make_shared<VCardDataType>("date-time", std::vector<VCardVersion::Ptr> { VCardVersion::V3_0(), VCardVersion::V4_0() });

/**
 * Any sort of date/time combination. The value can be a date (e.g.
 * "2015-02-16"), a time (e.g. "08:34:00"), or a date with a time component
 * (e.g. "2015-02-16 08:34:00").
 * @SupportedVersions(V4_0)
 */
const VCardDataType::Ptr VCardDataType::DATE_AND_OR_TIME = std::make_shared<VCardDataType>("date-and-or-time", std::vector<VCardVersion::Ptr> { VCardVersion::V4_0() });

/**
 * A specific moment in time. Timestamps should be in UTC time.
 * @SupportedVersions(V4_0)
 */
const VCardDataType::Ptr VCardDataType::TIMESTAMP = std::make_shared<VCardDataType>("timestamp", std::vector<VCardVersion::Ptr> { VCardVersion::V4_0() });

/**
 * A boolean value ("true" or "false").
 * @SupportedVersions(V4_0)
 */
const VCardDataType::Ptr VCardDataType::BOOLEAN = std::make_shared<VCardDataType>("boolean", std::vector<VCardVersion::Ptr> { VCardVersion::V4_0() });

/**
 * An integer value (e.g. "42").
 * @SupportedVersions(V4_0)
 */
const VCardDataType::Ptr VCardDataType::INTEGER = std::make_shared<VCardDataType>("integer", std::vector<VCardVersion::Ptr> { VCardVersion::V4_0() });

/**
 * A floating-point value (e.g. "3.14").
 * @SupportedVersions(V4_0)
 */
const VCardDataType::Ptr VCardDataType::FLOAT = std::make_shared<VCardDataType>("float", std::vector<VCardVersion::Ptr> { VCardVersion::V4_0() });

/**
 * An offset from UTC time, in hours and minutes (e.g. "-0500").
 * @SupportedVersions(V4_0)
 */
const VCardDataType::Ptr VCardDataType::UTC_OFFSET = std::make_shared<VCardDataType>("utc-offset", std::vector<VCardVersion::Ptr> { VCardVersion::V4_0() });

/**
 * A standardized abbreviation for a language (e.g. "en-us" for American
 * English).
 * @see <a href="http://tools.ietf.org/html/rfc5646">RFC 5646</a>
 * @SupportedVersions(V4_0)
 */
const VCardDataType::Ptr VCardDataType::LANGUAGE_TAG = std::make_shared<VCardDataType>("language-tag", std::vector<VCardVersion::Ptr> { VCardVersion::V4_0() });




const std::vector<VCardDataType::Ptr> VCardDataType::_types = {
    VCardDataType::URL,
    VCardDataType::CONTENT_ID,
    VCardDataType::BINARY,
    VCardDataType::URI,
    
    VCardDataType::TEXT,
    VCardDataType::DATE,
    VCardDataType::TIME,
    VCardDataType::DATE_TIME,
    VCardDataType::DATE_AND_OR_TIME,
    
    VCardDataType::TIMESTAMP,
    VCardDataType::BOOLEAN,
    VCardDataType::INTEGER,
    VCardDataType::FLOAT,
    VCardDataType::UTC_OFFSET,
    VCardDataType::LANGUAGE_TAG
};

/**
 * @param name the data type name
 */
VCardDataType::VCardDataType(const std::string& name, std::vector<VCardVersion::Ptr> supportVersions) {
    _name = name;
    _supportedVersions = supportVersions;
}

/**
 * Gets the name of the data type.
 * @return the name of the data type (e.g. "text")
 */
std::string VCardDataType::getName() {
    return _name;
}






//    private static final CaseClasses<VCardDataType, String> enums = new CaseClasses<VCardDataType, String>(VCardDataType.class) {
//        @Override
//        protected VCardDataType create(String value) {
//            return new VCardDataType(value);
//        }
//
//        @Override
//        protected boolean matches(VCardDataType dataType, String value) {
//            return dataType.name.equalsIgnoreCase(value);
//        }
//    };//
//    /**
//     * <p>
//     * Gets the vCard versions that support this data type.
//     * </p>
//     * <p>
//     * The supported versions are defined by assigning a
//     * {@link SupportedVersions} annotation to the data type's static field (for
//     * example, {@link VCardDataType#CONTENT_ID}). Dynamically-created data
//     * types (i.e. non-standard data types) are considered to be supported by
//     * all versions.
//     * </p>
//     * @return the vCard versions that support this data type
//     */
//    public VCardVersion[] getSupportedVersions() {
//        for (Field field : getClass().getFields()) {
//            if (!Modifier.isStatic(field.getModifiers())) {
//                continue;
//            }
//
//            Object fieldValue;
//            try {
//                fieldValue = field.get(null);
//            } catch (IllegalArgumentException e) {
//                //should never be thrown because we check for the static modified
//                continue;
//            } catch (IllegalAccessException e) {
//                continue;
//            }
//
//            if (fieldValue == this) {
//                SupportedVersions supportedVersionsAnnotation = field.getAnnotation(SupportedVersions.class);
//                return (supportedVersionsAnnotation == null) ? VCardVersion.values() : supportedVersionsAnnotation.value();
//            }
//        }
//
//        return VCardVersion.values();
//    }
//
//    /**
//     * <p>
//     * Determines if this data type is supported by the given vCard version.
//     * </p>
//     * <p>
//     * The supported versions are defined by assigning a
//     * {@link SupportedVersions} annotation to the data type's static field (for
//     * example, {@link VCardDataType#CONTENT_ID}). Dynamically-created data
//     * types (i.e. non-standard data types) are considered to be supported by
//     * all versions.
//     * </p>
//     * @param version the vCard version
//     * @return true if it is supported, false if not
//     */
//    public boolean isSupportedBy(VCardVersion version) {
//        for (VCardVersion supportedVersion : getSupportedVersions()) {
//            if (supportedVersion == version) {
//                return true;
//            }
//        }
//        return false;
//    }
//
//    @Override
//    public String toString() {
//        return name;
//    }
//
//    /**
//     * Searches for a data type that is defined as a static constant in this
//     * class.
//     * @param dataType the data type name (e.g. "text")
//     * @return the data type or null if not found
//     */
//    public static VCardDataType find(String dataType) {
//        return enums.find(dataType);
//    }

/**
 * Searches for a data type and creates one if it cannot be found. All
 * objects are guaranteed to be unique, so they can be compared with
 * {@code ==} equality.
 * @param dataType data type name (e.g. "text")
 * @return the data type
 */
VCardDataType::Ptr VCardDataType::get(const std::string& dataType) {
    for (auto type : _types) {
        if (type->getName() == dataType) {
            return type;
        }
    }
    return nullptr;
}
//
//    /**
//     * Gets all of the data types that are defined as static constants in this
//     * class.
//     * @return the data types
//     */
//    public static Collection<VCardDataType> all() {
//        return enums.all();
//    }
//
//    /*
//     * Note: This class doesn't need equals() or hashCode() because the
//     * CaseClasses object enforces reference equality.
//     */
//
//    @Override
//    public int hashCode() {
//        return super.hashCode();
//    }
//
//    @Override
//    public boolean equals(Object obj) {
//        return super.equals(obj);
//    }
