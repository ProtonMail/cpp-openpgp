//
//  vcard_parameters.cpp
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


#include "vcard_parameters.hpp"
#include "string_util.hpp"
#include "vobject_validator.hpp"
#include "utility.h"
#include "vcard_data_type.hpp"
#include "geo_uri.hpp"
#include "std_extension.hpp"
#include "charset.hpp"


namespace ezvcard {
    

const std::string VCardParameters::ALTID     = "ALTID";
const std::string VCardParameters::CALSCALE  = "CALSCALE";
const std::string VCardParameters::CHARSET   = "CHARSET";
const std::string VCardParameters::ENCODING  = "ENCODING";
const std::string VCardParameters::GEO       = "GEO";
const std::string VCardParameters::INDEX     = "INDEX";
const std::string VCardParameters::LABEL     = "LABEL";
const std::string VCardParameters::LANGUAGE  = "LANGUAGE";
const std::string VCardParameters::LEVEL     = "LEVEL";
const std::string VCardParameters::MEDIATYPE = "MEDIATYPE";
const std::string VCardParameters::PID       = "PID";
const std::string VCardParameters::PREF      = "PREF";
const std::string VCardParameters::SORT_AS   = "SORT-AS";
const std::string VCardParameters::TYPE      = "TYPE";
const std::string VCardParameters::TZ        = "TZ";
const std::string VCardParameters::VALUE     = "VALUE";



void VCardParameters::Print() {
    auto map = getMap();
    std::cout << "Map Size: " << map.size() << std::endl;
    for (auto k : map) {
        std::cout << "  K: " << k.first << std::endl;
        auto vlist = k.second;
        for (auto v : vlist) {
            std::cout << "   V: " << v << std::endl;
        }
    }
}

VCardParameters::VCardParameters() {
    _supportedVersions.insert(std::make_pair(ALTID, std::set<VCardVersion::Ptr>{VCardVersion::V4_0()}));
    _supportedVersions.insert(std::make_pair(CALSCALE, std::set<VCardVersion::Ptr>{VCardVersion::V4_0()}));
    _supportedVersions.insert(std::make_pair(CHARSET, std::set<VCardVersion::Ptr>{VCardVersion::V2_1()}));
    _supportedVersions.insert(std::make_pair(GEO, std::set<VCardVersion::Ptr>{VCardVersion::V4_0()}));
    _supportedVersions.insert(std::make_pair(INDEX, std::set<VCardVersion::Ptr>{VCardVersion::V4_0()}));
    
    /*
     * Don't check LABEL because this is removed and converted to LABEL
     * properties for 2.1 and 3.0 vCards.
     */
    //m.put(LABEL, EnumSet.of(VCardVersion.V4_0));
    
    _supportedVersions.insert(std::make_pair(LEVEL, std::set<VCardVersion::Ptr>{VCardVersion::V4_0()}));
    _supportedVersions.insert(std::make_pair(MEDIATYPE, std::set<VCardVersion::Ptr>{VCardVersion::V4_0()}));
    _supportedVersions.insert(std::make_pair(PID, std::set<VCardVersion::Ptr>{VCardVersion::V4_0()}));
    
    /*
     * Don't check PREF because this is removed and converted to "TYPE=PREF"
     * for 2.1 and 3.0 vCards.
     */
    //m.put(PREF, EnumSet.of(VCardVersion.V4_0));
    _supportedVersions.insert(std::make_pair(SORT_AS, std::set<VCardVersion::Ptr>{VCardVersion::V4_0()}));
    _supportedVersions.insert(std::make_pair(TZ, std::set<VCardVersion::Ptr>{VCardVersion::V4_0()}));
}

VCardParameters::VCardParameters(const std::unordered_map<std::string, std::vector<std::string>>& origMap) : VCardParameters() {
    for(auto elem : origMap)
    {
        auto key = elem.first;
        auto list = elem.second;
        auto v = std::vector<std::string>(std::begin(list), std::end(list));
        putAll(key, v);
    }
}

VCardParameters::VCardParameters(const VCardParameters::Ptr& orig) : VCardParameters() {
    if (orig != nullptr) {
        for(auto elem : orig->getMap())
        {
            auto key = elem.first;
            auto list = elem.second;
            auto v = std::vector<std::string>(std::begin(list), std::end(list));
            putAll(key, v);
        }
    }
}



//
//    /**
//     * <p>
//     * Creates a parameter list that is backed by the given map. Any changes
//     * made to the given map will effect the parameter list and vice versa.
//     * </p>
//     * <p>
//     * Care must be taken to ensure that the given map's keys are all in
//     * uppercase.
//     * </p>
//     * <p>
//     * To avoid problems, it is highly recommended that the given map NOT be
//     * modified by anything other than this {@link VCardParameters} class after
//     * being passed into this constructor.
//     * </p>
//     * @param map the map
//     */
//    public VCardParameters(Map<String, List<String>> map) {
//        super(map);
//    }

/**
 * <p>
 * Gets the ALTID parameter value.
 * </p>
 * <p>
 * This parameter is used to specify that the property value is an
 * alternative representation of another property value.
 * </p>
 * <p>
 * In the example below, the first three {@link Note} properties have the
 * same ALTID. This means that they each contain the same value, but in
 * different forms. In this case, each property value is written in a
 * different language. The other {@link Note} properties in the example have
 * different (or absent) ALTID values, which means they are not associated
 * with the top three.
 * </p>
 *
 * <pre>
 * NOTE;ALTID=1;LANGUAGE=en:Hello world!
 * NOTE;ALTID=1;LANGUAGE=fr:Bonjour tout le monde!
 * NOTE;ALTID=1;LANGUAGE=es:¡Hola, mundo!
 * NOTE;ALTID=2;LANGUAGE=de:Meine Lieblingsfarbe ist blau.
 * NOTE;ALTID=2;LANGUAGE=en:My favorite color is blue.
 * NOTE:This vCard will self-destruct in 5 seconds.
 * </pre>
 *
 * <p>
 * <b>Supported versions:</b> {@code 4.0}
 * </p>
 * @return the ALTID or null if not set
 * @see <a href="http://tools.ietf.org/html/rfc6350#page-18">RFC 6350
 * p.18</a>
 */
std::string VCardParameters::getAltId() {
    return first(ALTID);
}

/**
 * <p>
 * Sets the ALTID parameter value.
 * </p>
 * <p>
 * This parameter is used to specify that the property value is an
 * alternative representation of another property value.
 * </p>
 * <p>
 * In the example below, the first three {@link Note} properties have the
 * same ALTID. This means that they each contain the same value, but in
 * different forms. In this case, each property value is written in a
 * different language. The other {@link Note} properties in the example have
 * different (or absent) ALTID values, which means they are not associated
 * with the top three.
 * </p>
 *
 * <pre>
 * NOTE;ALTID=1;LANGUAGE=en:Hello world!
 * NOTE;ALTID=1;LANGUAGE=fr:Bonjour tout le monde!
 * NOTE;ALTID=1;LANGUAGE=es:¡Hola, mundo!
 * NOTE;ALTID=2;LANGUAGE=de:Meine Lieblingsfarbe ist blau.
 * NOTE;ALTID=2;LANGUAGE=en:My favorite color is blue.
 * NOTE:This vCard will self-destruct in 5 seconds.
 * </pre>
 *
 * <p>
 * <b>Supported versions:</b> {@code 4.0}
 * </p>
 * @param altId the ALTID or null to remove
 * @see <a href="http://tools.ietf.org/html/rfc6350#page-18">RFC 6350
 * p.18</a>
 */
void VCardParameters::setAltId(const std::string& altId) {
    replace(ALTID, altId);
}

/**
 * <p>
 * Gets the CALSCALE (calendar scale) parameter value.
 * </p>
 * <p>
 * This parameter defines the type of calendar that is used in a date or
 * date-time property value (for example, "gregorian").
 * </p>
 * <p>
 * <b>Supported versions:</b> {@code 4.0}
 * </p>
 * @return the type of calendar or null if not set
 * @see <a href="http://tools.ietf.org/html/rfc6350#page-20">RFC 6350
 * p.20</a>
 */
Calscale::Ptr VCardParameters::getCalscale() {
    auto value = first(CALSCALE);
    return (value.empty()) ? nullptr : Calscale::get(value);
}

/**
 * <p>
 * Sets the CALSCALE (calendar scale) parameter value.
 * </p>
 * <p>
 * This parameter defines the type of calendar that is used in a date or
 * date-time property value (for example, "gregorian").
 * </p>
 * <p>
 * <b>Supported versions:</b> {@code 4.0}
 * </p>
 * @param calscale the type of calendar or null to remove
 * @see <a href="http://tools.ietf.org/html/rfc6350#page-20">RFC 6350
 * p.20</a>
 */
void VCardParameters::setCalscale(const Calscale::Ptr& calscale) {
    replace(CALSCALE, (calscale == nullptr) ? "" : calscale->getValue());
}

/**
 * <p>
 * Gets the CHARSET (character set) parameter value.
 * </p>
 * <p>
 * This parameter defines the character set that the property value is
 * encoded in (for example, "UTF-8"). Typically, this is only used in 2.1
 * vCards when the property value is encoded in quoted-printable encoding.
 * </p>
 * <p>
 * <b>Supported versions:</b> {@code 2.1}
 * </p>
 * @return the character set or null if not set
 * @see <a href="http://www.imc.org/pdi/vcard-21.doc">vCard 2.1 p.20</a>
 */
std::string VCardParameters::getCharset() {
    return first(CHARSET);
}

/**
 * <p>
 * Sets the CHARSET (character set) parameter value.
 * </p>
 * <p>
 * This parameter defines the character set that the property value is
 * encoded in (for example, "UTF-8"). Typically, this is only used in 2.1
 * vCards when the property value is encoded in quoted-printable encoding.
 * </p>
 * <p>
 * <b>Supported versions:</b> {@code 2.1}
 * </p>
 * @param charset the character set or null to remove
 * @see <a href="http://www.imc.org/pdi/vcard-21.doc">vCard 2.1 p.20</a>
 */
void VCardParameters::setCharset(const std::string& charset) {
    replace(CHARSET, charset);
}
    
    /**
     * <p>
     * Gets the ENCODING parameter value.
     * </p>
     * <p>
     * This parameter is used when the property value is encoded in a form other
     * than plain text (for example, "base64").
     * </p>
     * <p>
     * <b>Supported versions:</b> {@code 2.1, 3.0}
     * </p>
     * @return the encoding or null if not set
     * @see <a href="http://tools.ietf.org/html/rfc2426">RFC 2426</a>
     * @see <a href="http://www.imc.org/pdi/vcard-21.doc">vCard 2.1 p.19</a>
     */
    Encoding::Ptr VCardParameters::getEncoding() {
        auto value = first(ENCODING);
        return (value.empty()) ? nullptr : Encoding::get(value);
    }
    
/**
 * <p>
 * Sets the ENCODING parameter value.
 * </p>
 * <p>
 * This parameter is used when the property value is encoded in a form other
 * than plain text (for example, "base64").
 * </p>
 * <p>
 * <b>Supported versions:</b> {@code 2.1, 3.0}
 * </p>
 * @param encoding the encoding or null to remove
 * @see <a href="http://tools.ietf.org/html/rfc2426">RFC 2426</a>
 * @see <a href="http://www.imc.org/pdi/vcard-21.doc">vCard 2.1 p.19</a>
 */
void VCardParameters::setEncoding(const Encoding::Ptr& encoding) {
    replace(ENCODING, (encoding == nullptr) ? "" : encoding->getValue());
}

/**
 * <p>
 * Gets the GEO parameter value.
 * </p>
 * <p>
 * This parameter is used to associate global positioning information with
 * the property. It can be used with the {@link Address} property.
 * </p>
 * <p>
 * <b>Supported versions:</b> {@code 4.0}
 * </p>
 * @return the geo URI or null if not set
 * @throws IllegalStateException if the parameter value is malformed and
 * cannot be parsed into a geo URI. If this happens, you may use the
 * {@link ListMultimap#get(Object) get()} method to retrieve its raw value.
 * @see <a href="http://tools.ietf.org/html/rfc6350#page-22">RFC 6350
 * p.22</a>
 */
GeoUri::Ptr VCardParameters::getGeo() {
    std::string value = first(GEO);
    if (value.empty()) {
        return nullptr;
    }
    
    try {
        return GeoUri::parse(value);
    } catch (std::exception& e) {
        throw std::logic_error( Messages::getInstance()->getExceptionMessage(15, GEO, GEO) );
        //throw new IllegalStateException(Messages.INSTANCE.getExceptionMessage(15, GEO), e);
    }
    
    return nullptr;
}

//    /**
//     * <p>
//     * Sets the GEO parameter value.
//     * </p>
//     * <p>
//     * This parameter is used to associate global positioning information with
//     * the property. It can be used with the {@link Address} property.
//     * </p>
//     * <p>
//     * <b>Supported versions:</b> {@code 4.0}
//     * </p>
//     * @param uri the geo URI or null to remove
//     * @see <a href="http://tools.ietf.org/html/rfc6350#page-22">RFC 6350
//     * p.22</a>
//     */
//    public void setGeo(GeoUri uri) {
//        replace(GEO, (uri == null) ? null : uri.toString());
//    }
//    
/**
 * <p>
 * Gets the INDEX parameter value.
 * </p>
 * <p>
 * This parameter defines the sorted position of this property when it is
 * grouped together with other properties of the same type. Properties with
 * low INDEX values are put at the beginning of the sorted list. Properties
 * with high INDEX values are put at the end of the list.
 * </p>
 * <p>
 * <b>Supported versions:</b> {@code 4.0}
 * </p>
 * @return the index or null if not set
 * @throws IllegalStateException if the parameter value is malformed and
 * cannot be parsed. If this happens, you may use the
 * {@link ListMultimap#get(Object) get()} method to retrieve its raw value.
 * @see <a href="https://tools.ietf.org/html/rfc6715#page-7">RFC 6715
 * p.7</a>
 */
int VCardParameters::getIndex() {
    int out_index = -1;
    std::string index = first(INDEX);
    if (index.empty()) {
        return INT32_MIN;
    }
    try {
        out_index = std::stoi(index);
    } catch (std::exception& ex) {
        //throw new IllegalStateException(Messages.INSTANCE.getExceptionMessage(15, INDEX), e);
        throw std::logic_error( Messages::getInstance()->getExceptionMessage(15, INDEX, INDEX) );
        
    }
    return out_index;
}

/**
 * <p>
 * Sets the INDEX parameter value.
 * </p>
 * <p>
 * This parameter defines the sorted position of this property when it is
 * grouped together with other properties of the same type. Properties with
 * low INDEX values are put at the beginning of the sorted list. Properties
 * with high INDEX values are put at the end of the list.
 * </p>
 * <p>
 * <b>Supported versions:</b> {@code 4.0}
 * </p>
 * @param index the index or null to remove
 * @see <a href="https://tools.ietf.org/html/rfc6715#page-7">RFC 6715
 * p.7</a>
 */
void VCardParameters::setIndex(int index) {
    replace(INDEX, (index == INT32_MIN) ? "" : std::to_string(index));
}

/**
 * <p>
 * Gets the LABEL parameter value.
 * </p>
 * <p>
 * This parameter is used by the {@link Address} property to define a
 * mailing label for the address.
 * </p>
 * <p>
 * <b>Supported versions:</b> {@code 4.0}
 * </p>
 * @return the label or null if not set
 * @see <a href="http://tools.ietf.org/html/rfc6350#page-33">RFC 6350
 * p.33</a>
 */
std::string VCardParameters::getLabel() {
    return first(LABEL);
}

/**
 * <p>
 * Sets the LABEL parameter value.
 * </p>
 * <p>
 * This parameter is used by the {@link Address} property to define a
 * mailing label for the address.
 * </p>
 * <p>
 * <b>Supported versions:</b> {@code 4.0}
 * </p>
 * @param label the label or null to remove
 * @see <a href="http://tools.ietf.org/html/rfc6350#page-33">RFC 6350
 * p.33</a>
 */
void VCardParameters::setLabel(std::string label) {
    replace(LABEL, label);
}
//
//    /**
//     * <p>
//     * Gets the LANGUAGE parameter value.
//     * </p>
//     * <p>
//     * This parameter defines the language that the property value is written in
//     * (for example, "en" for English").
//     * </p>
//     * <p>
//     * <b>Supported versions:</b> {@code 2.1, 3.0, 4.0}
//     * </p>
//     * @return the language or null if not set
//     * @see <a href="http://tools.ietf.org/html/rfc6350#page-16">RFC 6350
//     * p.16</a>
//     * @see <a href="http://tools.ietf.org/html/rfc2426#page-6">RFC 2426 p.6</a>
//     * @see <a href="http://www.imc.org/pdi/vcard-21.doc">vCard 2.1 p.20</a>
//     */
//    public String getLanguage() {
//        return first(LANGUAGE);
//    }
//    
//    /**
//     * <p>
//     * Sets the LANGUAGE parameter value.
//     * </p>
//     * <p>
//     * This parameter defines the language that the property value is written in
//     * (for example, "en" for English").
//     * </p>
//     * <p>
//     * <b>Supported versions:</b> {@code 2.1, 3.0, 4.0}
//     * </p>
//     * @param language the language or null to remove
//     * @see <a href="http://tools.ietf.org/html/rfc6350#page-16">RFC 6350
//     * p.16</a>
//     * @see <a href="http://tools.ietf.org/html/rfc2426#page-6">RFC 2426 p.6</a>
//     * @see <a href="http://www.imc.org/pdi/vcard-21.doc">vCard 2.1 p.20</a>
//     */
//    public void setLanguage(String language) {
//        replace(LANGUAGE, language);
//    }
//    
//    /**
//     * <p>
//     * Gets the LEVEL parameter value.
//     * </p>
//     * <p>
//     * This parameter is used to define the skill or interest level the person
//     * has towards the topic defined by the property (for example, "beginner").
//     * Its value varies depending on the property.
//     * </p>
//     * <p>
//     * <b>Supported versions:</b> {@code 4.0}
//     * </p>
//     * @return the level or null if not set
//     * @see <a href="https://tools.ietf.org/html/rfc6715#page-8">RFC 6715
//     * p.8</a>
//     */
//    public String getLevel() {
//        return first(LEVEL);
//    }
//    
//    /**
//     * <p>
//     * Sets the LEVEL parameter value.
//     * </p>
//     * <p>
//     * This parameter is used to define the skill or interest level the person
//     * has towards the topic defined by the property (for example, "beginner").
//     * Its value varies depending on the property.
//     * </p>
//     * <p>
//     * <b>Supported versions:</b> {@code 4.0}
//     * </p>
//     * @param level the level or null to remove
//     * @see <a href="https://tools.ietf.org/html/rfc6715#page-8">RFC 6715
//     * p.8</a>
//     */
//    public void setLevel(String level) {
//        replace(LEVEL, level);
//    }
//    
    /**
     * <p>
     * Gets the MEDIATYPE parameter value.
     * </p>
     * <p>
     * This parameter is used in properties that have a URL as a value, such as
     * {@link Photo} and {@link Sound}. It defines the content type of the
     * referenced resource (for example, "image/png" for a PNG image).
     * </p>
     * <p>
     * <b>Supported versions:</b> {@code 4.0}
     * </p>
     * @return the media type or null if not set
     * @see <a href="http://tools.ietf.org/html/rfc6350#page-20">RFC 6350
     * p.20</a>
     */
    std::string VCardParameters::getMediaType() {
        return first(MEDIATYPE);
    }
    
    /**
     * <p>
     * Sets the MEDIATYPE parameter value.
     * </p>
     * <p>
     * This parameter is used in properties that have a URL as a value, such as
     * {@link Photo} and {@link Sound}. It defines the content type of the
     * referenced resource (for example, "image/png" for a PNG image).
     * </p>
     * <p>
     * <b>Supported versions:</b> {@code 4.0}
     * </p>
     * @param mediaType the media type or null to remove
     * @see <a href="http://tools.ietf.org/html/rfc6350#page-20">RFC 6350
     * p.20</a>
     */
    // TODO:: check for empty string
    void VCardParameters::setMediaType(const std::string& mediaType) {
        replace(MEDIATYPE, mediaType);
    }
    
//    /**
//     * <p>
//     * Gets the PID (property ID) parameter values.
//     * </p>
//     * <p>
//     * PIDs can exist on any property where multiple instances are allowed (such
//     * as {@link Email} or {@link Address}, but not {@link StructuredName}
//     * because only 1 instance of this property is allowed per vCard).
//     * </p>
//     * <p>
//     * When used in conjunction with the {@link ClientPidMap} property, it
//     * allows an individual property instance to be uniquely identifiable. This
//     * feature is made use of when two different versions of the same vCard have
//     * to be merged together (called "synchronizing").
//     * </p>
//     * <p>
//     * Changes to the returned list will update the {@link VCardParameters}
//     * object, and vice versa.
//     * </p>
//     * <p>
//     * <b>Supported versions:</b> {@code 4.0}
//     * </p>
//     * @return the PIDs
//     * @throws IllegalStateException if one or more parameter values are
//     * malformed and cannot be parsed. If this happens, you may use the
//     * {@link ListMultimap#get(Object) get()} method to retrieve its raw values.
//     * @see <a href="http://tools.ietf.org/html/rfc6350#page-19">RFC 6350
//     * p.19</a>
//     */
//    public List<Pid> getPids() {
//        return new VCardParameterList<Pid>(PID) {
//            @Override
//            protected String _asString(Pid value) {
//                return value.toString();
//            }
//            
//            @Override
//            protected Pid _asObject(String value) {
//                return Pid.valueOf(value);
//            }
//            
//            @Override
//            protected IllegalStateException _exception(String value, Exception thrown) {
//                return new IllegalStateException(Messages.INSTANCE.getExceptionMessage(15, PID), thrown);
//            }
//        };
//    }
//    
//    /**
//     * <p>
//     * Adds a PID (property ID) parameter value.
//     * </p>
//     * <p>
//     * PIDs can exist on any property where multiple instances are allowed (such
//     * as {@link Email} or {@link Address}, but not {@link StructuredName}
//     * because only 1 instance of this property is allowed per vCard).
//     * </p>
//     * <p>
//     * When used in conjunction with the {@link ClientPidMap} property, it
//     * allows an individual property instance to be uniquely identifiable. This
//     * feature is made use of when two different versions of the same vCard have
//     * to be merged together (called "synchronizing").
//     * </p>
//     * <p>
//     * <b>Supported versions:</b> {@code 4.0}
//     * </p>
//     * @param pid the PID to add
//     * @see <a href="http://tools.ietf.org/html/rfc6350#page-19">RFC 6350
//     * p.19</a>
//     */
//    public void addPid(Pid pid) {
//        put(PID, pid.toString());
//    }
//    
//    /**
//     * <p>
//     * Removes a PID (property ID) parameter value.
//     * </p>
//     * <p>
//     * PIDs can exist on any property where multiple instances are allowed (such
//     * as {@link Email} or {@link Address}, but not {@link StructuredName}
//     * because only 1 instance of this property is allowed per vCard).
//     * </p>
//     * <p>
//     * When used in conjunction with the {@link ClientPidMap} property, it
//     * allows an individual property instance to be uniquely identifiable. This
//     * feature is made use of when two different versions of the same vCard have
//     * to be merged together (called "synchronizing").
//     * </p>
//     * <p>
//     * <b>Supported versions:</b> {@code 4.0}
//     * </p>
//     * @param pid the PID to remove
//     * @see <a href="http://tools.ietf.org/html/rfc6350#page-19">RFC 6350
//     * p.19</a>
//     */
//    public void removePid(Pid pid) {
//        String value = pid.toString();
//        remove(PID, value);
//    }
//    
//    /**
//     * <p>
//     * Removes all PID (property ID) parameter values.
//     * </p>
//     * <p>
//     * PIDs can exist on any property where multiple instances are allowed (such
//     * as {@link Email} or {@link Address}, but not {@link StructuredName}
//     * because only 1 instance of this property is allowed per vCard).
//     * </p>
//     * <p>
//     * When used in conjunction with the {@link ClientPidMap} property, it
//     * allows an individual property instance to be uniquely identifiable. This
//     * feature is made use of when two different versions of the same vCard have
//     * to be merged together (called "synchronizing").
//     * </p>
//     * <p>
//     * <b>Supported versions:</b> {@code 4.0}
//     * </p>
//     * @see <a href="http://tools.ietf.org/html/rfc6350#page-19">RFC 6350
//     * p.19</a>
//     */
//    public void removePids() {
//        removeAll(PID);
//    }

/**
 * <p>
 * Gets the PREF (preference) parameter value.
 * </p>
 * <p>
 * The lower this number is, the more "preferred" the property instance is
 * compared with other properties of the same type. If a property doesn't
 * have a preference value, then it is considered the least preferred.
 * </p>
 * <p>
 * In the vCard below, the {@link Address} on the second row is the most
 * preferred because it has the lowest PREF value.
 * </p>
 *
 * <pre>
 * ADR;TYPE=work;PREF=2:;;1600 Amphitheatre Parkway;Mountain View;CA;94043
 * ADR;TYPE=work;PREF=1:;;One Microsoft Way;Redmond;WA;98052
 * ADR;TYPE=home:;;123 Maple St;Hometown;KS;12345
 * </pre>
 *
 * <p>
 * <b>Supported versions:</b> {@code 4.0}
 * </p>
 * @return the preference value or null if not set
 * @throws IllegalStateException if the parameter value is malformed and
 * cannot be parsed. If this happens, you may use the
 * {@link ListMultimap#get(Object) get()} method to retrieve its raw value.
 * @see <a href="http://tools.ietf.org/html/rfc6350#page-17">RFC 6350
 * p.17</a>
 */
int VCardParameters::getPref() {
    auto pref = first(PREF);
    int out_index = -1;
    if (pref.empty()) {
        return INT32_MIN;
    }
    
    try {
        out_index = std::stoi(pref);
    } catch (std::exception& ex) {
        //throw new IllegalStateException(Messages.INSTANCE.getExceptionMessage(15, PREF), e);
        throw std::logic_error( Messages::getInstance()->getExceptionMessage(15, PREF, PREF) );
    }
    return out_index;
}

/**
 * <p>
 * Sets the PREF (preference) parameter value.
 * </p>
 * <p>
 * The lower this number is, the more "preferred" the property instance is
 * compared with other properties of the same type. If a property doesn't
 * have a preference value, then it is considered the least preferred.
 * </p>
 * <p>
 * In the vCard below, the {@link Address} on the second row is the most
 * preferred because it has the lowest PREF value.
 * </p>
 *
 * <pre>
 * ADR;TYPE=work;PREF=2:;;1600 Amphitheatre Parkway;Mountain View;CA;94043
 * ADR;TYPE=work;PREF=1:;;One Microsoft Way;Redmond;WA;98052
 * ADR;TYPE=home:;;123 Maple St;Hometown;KS;12345
 * </pre>
 *
 * <p>
 * <b>Supported versions:</b> {@code 4.0}
 * </p>
 * @param pref the preference value or null to remove
 * @see <a href="http://tools.ietf.org/html/rfc6350#page-17">RFC 6350
 * p.17</a>
 */
void VCardParameters::setPref(int pref) {
    replace(PREF, (pref == INT32_MIN) ? "" : std::to_string(pref));
}

//    /**
//     * <p>
//     * Gets the SORT-AS parameter values.
//     * </p>
//     * <p>
//     * This parameter defines how the vCard should be sorted amongst other
//     * vCards. For example, this can be used if the person's last name (defined
//     * in the {@link StructuredName} property) starts with characters that
//     * should be ignored during sorting (such as "d'Aboville").
//     * </p>
//     * <p>
//     * This parameter can be used with the {@link StructuredName} and
//     * {@link Organization} properties. 2.1 and 3.0 vCards should use the
//     * {@link SortString} property instead.
//     * </p>
//     * <p>
//     * This parameter can be multi-valued. The first value is the primary sort
//     * keyword (such as the person's last name), the second value is the
//     * secondary sort keyword (such as the person's first name), etc.
//     * </p>
//     * <p>
//     * Changes to the returned list will update the {@link VCardParameters}
//     * object, and vice versa.
//     * </p>
//     * <p>
//     * <b>Supported versions:</b> {@code 4.0}
//     * </p>
//     * @return the sort strings
//     * @see <a href="http://tools.ietf.org/html/rfc6350#page-21">RFC 6350
//     * p.21</a>
//     */
//    public List<String> getSortAs() {
//        return get(SORT_AS);
//    }
//    
//    /**
//     * <p>
//     * Sets the SORT-AS parameter values.
//     * </p>
//     * <p>
//     * This parameter defines how the vCard should be sorted amongst other
//     * vCards. For example, this can be used if the person's last name (defined
//     * in the {@link StructuredName} property) starts with characters that
//     * should be ignored during sorting (such as "d'Aboville").
//     * </p>
//     * <p>
//     * This parameter can be used with the {@link StructuredName} and
//     * {@link Organization} properties. 2.1 and 3.0 vCards should use the
//     * {@link SortString} property instead.
//     * </p>
//     * <p>
//     * This parameter can be multi-valued. The first value is the primary sort
//     * keyword (such as the person's last name), the second value is the
//     * secondary sort keyword (such as the person's first name), etc.
//     * </p>
//     * <p>
//     * <b>Supported versions:</b> {@code 4.0}
//     * </p>
//     * @param sortStrings the sort strings or an empty parameter list to remove
//     * @see <a href="http://tools.ietf.org/html/rfc6350#page-21">RFC 6350
//     * p.21</a>
//     */
//    public void setSortAs(String... sortStrings) {
//        removeAll(SORT_AS);
//        putAll(SORT_AS, Arrays.asList(sortStrings));
//    }
    
    
    /**
     * <p>
     * Adds a TYPE parameter value.
     * </p>
     * <p>
     * The meaning of this parameter varies depending on the property.
     * </p>
     * <p>
     * <b>Supported versions:</b> {@code 2.1, 3.0, 4.0}
     * </p>
     * @param type the type to add
     * @see <a href="http://tools.ietf.org/html/rfc6350#page-19">RFC 6350
     * p.19</a>
     * @see <a href="http://tools.ietf.org/html/rfc2426#page-6">RFC 2426 p.6</a>
     * @see <a href="http://www.imc.org/pdi/vcard-21.doc">vCard 2.1</a>
     */
    void VCardParameters::addType(const std::string& type) {
        put(TYPE, type);
    }
//
//    /**
//     * <p>
//     * Removes a TYPE parameter value.
//     * </p>
//     * <p>
//     * The meaning of this parameter varies depending on the property.
//     * </p>
//     * <p>
//     * <b>Supported versions:</b> {@code 2.1, 3.0, 4.0}
//     * </p>
//     * @param type the type to remove
//     * @see <a href="http://tools.ietf.org/html/rfc6350#page-19">RFC 6350
//     * p.19</a>
//     * @see <a href="http://tools.ietf.org/html/rfc2426#page-6">RFC 2426 p.6</a>
//     * @see <a href="http://www.imc.org/pdi/vcard-21.doc">vCard 2.1</a>
//     */
//    public void removeType(String type) {
//        remove(TYPE, type);
//    }

/**
 * <p>
 * Sets the TYPE parameter value.
 * </p>
 * <p>
 * The meaning of this parameter varies depending on the property.
 * </p>
 * <p>
 * <b>Supported versions:</b> {@code 2.1, 3.0, 4.0}
 * </p>
 * @param type the type or null to remove
 * @see <a href="http://tools.ietf.org/html/rfc6350#page-19">RFC 6350
 * p.19</a>
 * @see <a href="http://tools.ietf.org/html/rfc2426#page-6">RFC 2426 p.6</a>
 * @see <a href="http://www.imc.org/pdi/vcard-21.doc">vCard 2.1</a>
 */
void VCardParameters::setType(const std::string& type) {
    replace(TYPE, type);
}
    
    /**
     * <p>
     * Gets the TYPE parameter values.
     * </p>
     * <p>
     * The meaning of this parameter varies depending on the property.
     * </p>
     * <p>
     * Changes to the returned list will update the {@link VCardParameters}
     * object, and vice versa.
     * </p>
     * <p>
     * <b>Supported versions:</b> {@code 2.1, 3.0, 4.0}
     * </p>
     * @return the types
     * @see <a href="http://tools.ietf.org/html/rfc6350#page-19">RFC 6350
     * p.19</a>
     * @see <a href="http://tools.ietf.org/html/rfc2426#page-6">RFC 2426 p.6</a>
     * @see <a href="http://www.imc.org/pdi/vcard-21.doc">vCard 2.1</a>
     */
    std::vector<std::string> VCardParameters::getTypes() {
        return get(TYPE);
    }
    
    /**
     * <p>
     * Gets the first TYPE parameter value.
     * </p>
     * <p>
     * The meaning of this parameter varies depending on the property.
     * </p>
     * <p>
     * <b>Supported versions:</b> {@code 2.1, 3.0, 4.0}
     * </p>
     * @return the type or null if not set
     * @see <a href="http://tools.ietf.org/html/rfc6350#page-19">RFC 6350
     * p.19</a>
     * @see <a href="http://tools.ietf.org/html/rfc2426#page-6">RFC 2426 p.6</a>
     * @see <a href="http://www.imc.org/pdi/vcard-21.doc">vCard 2.1</a>
     */
    std::string VCardParameters::getType() {
        return first(TYPE);
    }
    
    
//    /**
//     * <p>
//     * Gets the TZ (timezone) parameter value.
//     * </p>
//     * <p>
//     * This parameter is used to associate timezone information with an
//     * {@link Address} property (for example, "America/New_York" to indicate
//     * that an address adheres to that timezone).
//     * </p>
//     * <p>
//     * <b>Supported versions:</b> {@code 4.0}
//     * </p>
//     * @return the timezone or null if not set
//     * @see <a href="http://tools.ietf.org/html/rfc6350#page-22">RFC 6350
//     * p.22</a>
//     */
//    public String getTimezone() {
//        return first(TZ);
//    }
//    
//    /**
//     * <p>
//     * Sets the TZ (timezone) parameter value.
//     * </p>
//     * <p>
//     * This parameter is used to associate timezone information with an
//     * {@link Address} property (for example, "America/New_York" to indicate
//     * that an address adheres to that timezone).
//     * </p>
//     * <p>
//     * <b>Supported versions:</b> {@code 4.0}
//     * </p>
//     * @param timezone the timezone or null to remove
//     * @see <a href="http://tools.ietf.org/html/rfc6350#page-22">RFC 6350
//     * p.22</a>
//     */
//    public void setTimezone(String timezone) {
//        replace(TZ, timezone);
//    }
//    
/**
 * <p>
 * Gets the VALUE parameter value.
 * </p>
 * <p>
 * This parameter defines the data type of the property value (for example,
 * "date" if the property value is a date without a time component). It is
 * used if the property accepts multiple values that have different data
 * types.
 * </p>
 * <p>
 * <b>Supported versions:</b> {@code 2.1, 3.0, 4.0}
 * </p>
 * @return the data type or null if not set
 * @see <a href="http://tools.ietf.org/html/rfc6350#page-16">RFC 6350
 * p.16</a>
 * @see <a href="http://tools.ietf.org/html/rfc2426#page-6">RFC 2426 p.6</a>
 * @see <a href="http://www.imc.org/pdi/vcard-21.doc">vCard 2.1 p.20</a>
 */
VCardDataType::Ptr VCardParameters::getValue() {
    auto value = first(VALUE);
    return value.empty() ? nullptr : VCardDataType::get(value);
}

/**
 * <p>
 * Sets the VALUE parameter value.
 * </p>
 * <p>
 * This parameter defines the data type of the property value (for example,
 * "date" if the property value is a date without a time component). It is
 * used if the property accepts multiple values that have different data
 * types.
 * </p>
 * <p>
 * <b>Supported versions:</b> {@code 2.1, 3.0, 4.0}
 * </p>
 * @param dataType the data type or null to remove
 * @see <a href="http://tools.ietf.org/html/rfc6350#page-16">RFC 6350
 * p.16</a>
 * @see <a href="http://tools.ietf.org/html/rfc2426#page-6">RFC 2426 p.6</a>
 * @see <a href="http://www.imc.org/pdi/vcard-21.doc">vCard 2.1 p.20</a>
 */
void VCardParameters::setValue(const VCardDataType::Ptr& dataType) {
    replace(VALUE, (dataType == nullptr) ? "" : dataType->getName());
}

/**
 * <p>
 * Checks the parameters for data consistency problems or deviations from
 * the specification.
 * </p>
 * <p>
 * These problems will not prevent the vCard from being written to a data
 * stream*, but may prevent it from being parsed correctly by the consuming
 * application.
 * </p>
 * <p>
 * *With a few exceptions: One thing this method does is check for illegal
 * characters. There are certain characters that will break the vCard syntax
 * if written (such as a newline character in a parameter name). If one of
 * these characters is present, it WILL prevent the vCard from being
 * written.
 * </p>
 * @param version the vCard version to validate against
 * @return a list of warnings or an empty list if no problems were found
 */
std::list<ValidationWarning::Ptr> VCardParameters::validate(const VCardVersion::Ptr& version) {
    std::list<ValidationWarning::Ptr> warnings = std::list<ValidationWarning::Ptr>();
    
    /*
     * Check for invalid characters in names and values.
     */
    SyntaxStyle syntax = version->getSyntaxStyle();
    auto map = getMap();
    for (auto it = map.begin(); it != map.end(); ++it) {
        auto name = it->first;
        
        /*
         * Don't check LABEL parameter for 2.1 and 3.0 because this
         * parameter is converted to a property in those versions.
         */
        if (version != VCardVersion::V4_0() && str_equals(LABEL, name)) {
            continue;
        }
        
        //check the parameter name
        if (!VObjectValidator::get()->validateParameterName(name, syntax, true)) {
            if (syntax == SyntaxStyle::OLD) {
                auto validator = VObjectValidator::get()->allowedCharactersParameterName(syntax, true);
                AllowedCharacters::Ptr notAllowed = validator->flip();
                warnings.push_back(std::make_shared<ValidationWarning>(30, name, notAllowed->toString(true)));
            } else {
                warnings.push_back(std::make_shared<ValidationWarning>(26, name));
            }
        }
        
        //check the parameter value(s)
        auto values = it->second;
        for (auto value : values) {
            /*
             * Newlines are allowed in LABEL parameters, but are not allowed
             * by vobject, so remove them from the value before validating.
             */
            if (str_equals(LABEL,name)) {
                value = ProtonMail::replaceAll(value, "\r\n|\r|\n", "");
            }
            
            if (!VObjectValidator::get()->validateParameterValue(value, syntax, false, true)) {
                AllowedCharacters::Ptr notAllowed = VObjectValidator::get()->allowedCharactersParameterValue(syntax, false, true)->flip();
                int code = (syntax == SyntaxStyle::OLD) ? 31 : 25;
                warnings.push_back(std::make_shared<ValidationWarning>(code, name, value, notAllowed->toString(true)));
            }
        }
    }
    
    /*
     * Check for invalid or unsupported values (e.g. "ENCODING=foo").
     */
    {
        const int nonStandardValueCode = 3;
        const int unsupportedValueCode = 4;
        
        std::string value = first(CALSCALE);
        if (!value.empty() && Calscale::find(value) == nullptr) {
            auto m = Calscale::all_to_string();
            warnings.push_back(std::make_shared<ValidationWarning>(nonStandardValueCode, CALSCALE, value, m));
        }
        
        value = first(ENCODING);
        if (!value.empty()) {
            auto encoding = Encoding::find(value);
            if (encoding == nullptr) {
                auto m = Encoding::all_to_string();
                warnings.push_back(std::make_shared<ValidationWarning>(nonStandardValueCode, ENCODING, value, m));
            } else if (!encoding->isSupportedBy(version)) {
               warnings.push_back(std::make_shared<ValidationWarning>(unsupportedValueCode, ENCODING, value));
            }
        }
        
        value = first(VALUE);
//        if (value != null) {
//            VCardDataType dataType = VCardDataType.find(value);
//            if (dataType == null) {
//                warnings.add(new Warning(nonStandardValueCode, VALUE, value, VCardDataType.all()));
//            } else if (!dataType.isSupportedBy(version)) {
//                warnings.add(new Warning(unsupportedValueCode, VALUE, value));
//            }
//        }
    }
    
    /*
     * Check for parameters with malformed values.
     */
    {
        const int malformedValueCode = 5;
        try {
            getGeo();
        } catch (std::exception& e) {
            warnings.push_back(std::make_shared<ValidationWarning>(malformedValueCode, GEO, first(GEO)));
        }
        
        try {
            int index = getIndex();
            if (index != INT32_MIN && index <= 0) {
                warnings.push_back(std::make_shared<ValidationWarning>(28, "null(" + std::to_string(index) + ")"));
            }
        } catch (std::exception& e) {
            warnings.push_back(std::make_shared<ValidationWarning>(malformedValueCode, INDEX, first(INDEX)));
        }
        
        auto pids = get(PID);
        for (auto pid : pids) {
            if (!isPidValid(pid)) {
                warnings.push_back(std::make_shared<ValidationWarning>(27, pid));
            }
        }

        try {
            int pref = getPref();
            if (pref != INT32_MIN && (pref < 1 || pref > 100)) {
                warnings.push_back(std::make_shared<ValidationWarning>(29, std::to_string(pref)));
            }
        } catch (std::exception& e) {
            warnings.push_back(std::make_shared<ValidationWarning>(malformedValueCode, PREF, first(PREF)));
        }
    }
    
    /*
     * Check that each parameter is supported by the given vCard version.
     */
    {
        const int paramNotSupportedCode = 6;
        
        for (auto it=_supportedVersions.begin(); it!=_supportedVersions.end(); ++it) {
            auto name = it->first;
            auto value = first(name);
            if (value.empty()) {
                continue;
            }
            auto versions = it->second;
            
            auto comp_version_obj = [&version](const VCardVersion::Ptr& ver){
                return ver->equals(version);
            };
            auto found = std::find_if(versions.begin(),
                                     versions.end(),
                                     comp_version_obj);
            if (found == versions.end()) {
                warnings.push_back(std::make_shared<ValidationWarning>(paramNotSupportedCode, name));
            }
            
        }
    }
    
    /*
     * Check that the CHARSET parameter has a character set that is
     * supported by this JVM.
     */
    {
        const int invalidCharsetCode = 22;
        
        std::string charsetStr = getCharset();
        if (!charsetStr.empty()) {
            try {
                Charset::forName(charsetStr);
            } catch (const std::exception& e) {
                warnings.push_back(std::make_shared<ValidationWarning>(invalidCharsetCode, charsetStr));
            }
        }
    }
    
    return warnings;
}

bool VCardParameters::isPidValid(const std::string& pid) {
    bool dotFound = false;
    for (int i = 0; i < pid.length(); i++) {
        char c = pid[i];
        
        if (c == '.') {
            if (i == 0 || i == pid.length() - 1) {
                return false;
            }
            if (dotFound) {
                return false;
            }
            dotFound = true;
            continue;
        }
        
        if (c >= '0' && c <= '9') {
            continue;
        }
        
        return false;
    }
    
    return true;
}
//
//    @Override
//    protected String sanitizeKey(String key) {
//        return (key == null) ? null : key.toUpperCase();
//    }
//    
//    @Override
//    public int hashCode() {
//        /*
//         * Remember: Keys are case-insensitive, key order does not matter, and
//         * value order does not matter
//         */
//        final int prime = 31;
//        int result = 1;
//        
//        for (Map.Entry<String, List<String>> entry : this) {
//            String key = entry.getKey();
//            List<String> value = entry.getValue();
//            
//            int valueHash = 1;
//            for (String v : value) {
//                valueHash += v.toLowerCase().hashCode();
//            }
//            
//            int entryHash = 1;
//            entryHash += prime * entryHash + ((key == null) ? 0 : key.toLowerCase().hashCode());
//            entryHash += prime * entryHash + valueHash;
//            
//            result += entryHash;
//        }
//        
//        return result;
//    }
//    
//    /**
//     * <p>
//     * Determines whether the given object is logically equivalent to this list
//     * of vCard parameters.
//     * </p>
//     * <p>
//     * vCard parameters are case-insensitive. Also, the order in which they are
//     * defined does not matter.
//     * </p>
//     * @param obj the object to compare to
//     * @return true if the objects are equal, false if not
//     */
//    @Override
//    public boolean equals(Object obj) {
//        /*
//         * Remember: Keys are case-insensitive, key order does not matter, and
//         * value order does not matter
//         */
//        if (this == obj) return true;
//        if (obj == null) return false;
//        if (getClass() != obj.getClass()) return false;
//        
//        VCardParameters other = (VCardParameters) obj;
//        if (size() != other.size()) return false;
//        
//        for (Map.Entry<String, List<String>> entry : this) {
//            String key = entry.getKey();
//            List<String> value = entry.getValue();
//            List<String> otherValue = other.get(key);
//            
//            if (value.size() != otherValue.size()) {
//                return false;
//            }
//            
//            List<String> valueLower = new ArrayList<String>(value.size());
//            for (String v : value) {
//                valueLower.add(v.toLowerCase());
//            }
//            Collections.sort(valueLower);
//            
//            List<String> otherValueLower = new ArrayList<String>(otherValue.size());
//            for (String v : otherValue) {
//                otherValueLower.add(v.toLowerCase());
//            }
//            Collections.sort(otherValueLower);
//            
//            if (!valueLower.equals(otherValueLower)) {
//                return false;
//            }
//        }
//        
//        return true;
//    }
//    
//    /**
//     * <p>
//     * A list that converts the raw string values of a TYPE parameter to the
//     * appropriate {@link VCardParameter} object that some parameters use.
//     * </p>
//     * <p>
//     * This list is backed by the {@link VCardParameters} object. Any changes
//     * made to the list will affect the {@link VCardParameters} object and vice
//     * versa.
//     * </p>
//     * @param <T> the parameter class
//     */
//    public abstract class TypeParameterList<T extends VCardParameter> extends EnumParameterList<T> {
//        public TypeParameterList() {
//            super(TYPE);
//        }
//    }
//    
//    /**
//     * <p>
//     * A list that converts the raw string values of a parameter to the
//     * appropriate {@link VCardParameter} object that some parameters use.
//     * </p>
//     * <p>
//     * This list is backed by the {@link VCardParameters} object. Any changes
//     * made to the list will affect the {@link VCardParameters} object and vice
//     * versa.
//     * </p>
//     * @param <T> the parameter class
//     */
//    public abstract class EnumParameterList<T extends VCardParameter> extends VCardParameterList<T> {
//        public EnumParameterList(String parameterName) {
//            super(parameterName);
//        }
//        
//        @Override
//        protected String _asString(T value) {
//            return value.getValue();
//        }
//    }
//    
//    /**
//     * <p>
//     * A list that converts the raw string values of a parameter to another kind
//     * of value (for example, Integers).
//     * </p>
//     * <p>
//     * This list is backed by the {@link VCardParameters} object. Any changes
//     * made to the list will affect the {@link VCardParameters} object and vice
//     * versa.
//     * </p>
//     * <p>
//     * If a String value cannot be converted to the appropriate data type, an
//     * {@link IllegalStateException} is thrown.
//     * </p>
//     */
//    public abstract class VCardParameterList<T> extends AbstractList<T> {
//        protected final String parameterName;
//        protected final List<String> parameterValues;
//        
//        /**
//         * @param parameterName the name of the parameter (case insensitive)
//         */
//        public VCardParameterList(String parameterName) {
//            this.parameterName = parameterName;
//            parameterValues = VCardParameters.this.get(parameterName);
//        }
//        
//        @Override
//        public void add(int index, T value) {
//            String valueStr = _asString(value);
//            parameterValues.add(index, valueStr);
//        }
//        
//        @Override
//        public T remove(int index) {
//            String removed = parameterValues.remove(index);
//            return asObject(removed);
//        }
//        
//        @Override
//        public T get(int index) {
//            String value = parameterValues.get(index);
//            return asObject(value);
//        }
//        
//        @Override
//        public T set(int index, T value) {
//            String valueStr = _asString(value);
//            String replaced = parameterValues.set(index, valueStr);
//            return asObject(replaced);
//        }
//        
//        @Override
//        public int size() {
//            return parameterValues.size();
//        }
//        
//        private T asObject(String value) {
//            try {
//                return _asObject(value);
//            } catch (Exception e) {
//                throw _exception(value, e);
//            }
//        }
//        
//        /**
//         * Converts the object to a String value for storing in the
//         * {@link VCardParameters} object.
//         * @param value the value
//         * @return the string value
//         */
//        protected abstract String _asString(T value);
//        
//        /**
//         * Converts a String value to its object form.
//         * @param value the string value
//         * @return the object
//         * @throws Exception if there is a problem parsing the string
//         */
//        protected abstract T _asObject(String value) throws Exception;
//        
//        /**
//         * Creates the exception that is thrown when the raw string value cannot
//         * be parsed into its object form.
//         * @param value the raw string value
//         * @param thrown the thrown exception
//         * @return the exception to throw
//         */
//        protected IllegalStateException _exception(String value, Exception thrown) {
//            return new IllegalStateException(Messages.INSTANCE.getExceptionMessage(26, parameterName), thrown);
//        }
//    }
//}


bool VCardParameters::equals(const Ptr &obj) {
    if (obj == nullptr)
        return false;
    if (this == obj.get())
        return true;
    
    return _equals(*obj.get());
}

bool VCardParameters::_equals(const VCardParameters &rhs) {
    auto l_m = getMap();
    auto r_m = rhs.getMap();
    
    if (l_m.size() != r_m.size()) {
        return false;
    }
    
    auto pred = [] (decltype(*l_m.begin()) a, decltype(a) b)
    {
        if (a.first != b.first) {
            return false;
        }
        
        auto a_value = a.second;
        auto b_value = b.second;
        
        if (a_value.size() != b_value.size()) {
            return false;
        }
        
        auto pred_list = [] (decltype(*a_value.begin()) c, decltype(c) d)
        {
            return c == d;
        };
        
        if (!std::equal(a_value.begin(), a_value.end(), b_value.begin(), pred_list)) {
            return false;
        }
        
        return true;
    };
    
    if (!std::equal(l_m.begin(),l_m.end(), r_m.begin(), pred)) {
        return false;
    }
    
    return true;
}

bool VCardParameters::operator==(const VCardParameters& rhs) {
    return _equals(rhs);
}

bool operator==(const VCardParameters::Ptr& lhs, const VCardParameters::Ptr& rhs) {
    return lhs->equals(rhs);
}

}
