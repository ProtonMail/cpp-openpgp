//
//  messages.cpp
//  OpenPGP
//
//  Created by Yanfeng Zhang on 1/17/17.
//  Copyright © 2017 Yanfeng Zhang. All rights reserved.
//

#include "messages.hpp"
#include <vector>

Messages::Ptr Messages::single = nullptr;
Messages::Messages() {
    //#==============================================================================
    //#== VALIDATION WARNINGS =======================================================
    //#==============================================================================
    //#vCard warnings
    _error_tempate["validate.0"]  = "A StructuredName property is required for vCard versions 2.1 and 3.0.";
    _error_tempate["validate.1"]  = "A FormattedName property is required for vCard versions 3.0 and 4.0.";
    _error_tempate["validate.23"] = "Group name %s contains one or more invalid characters.  Group names may contain letters (A-Z), numbers (0-9), and dashes (-).";
    _error_tempate["validate.32"] = "Group name %s contains one or more invalid characters.  Group names may contain printable, 7-bit ASCII characters, with the exception of: %s";
    
    //#parameter warnings
    _error_tempate["validate.3"]  = "%s parameter value (\"%s\") is non-standard.  Standard values are: %s";
    _error_tempate["validate.4"]  = "%s parameter value (\"%s\") is not supported by this vCard version.";
    _error_tempate["validate.5"]  = "%s parameter value (\"%s\") is malformed.";
    _error_tempate["validate.6"]  = "%s parameter is not supported in this vCard version.";
    _error_tempate["validate.9"]  = "TYPE parameter value (\"%s\") is not supported by this property in this vCard version.";
    _error_tempate["validate.22"] = "CHARSET parameter value (\"%s\") is not a recognized character set.";
    
    _error_tempate["validate.25"] = "%s parameter value (\"%s\") contains one or more invalid characters.  Parameter values may contain printable characters, with the exception of: %s";
    _error_tempate["validate.31"] = "%s parameter value (\"%s\") contains one or more invalid characters.  Parameter values may contain printable, 7-bit ASCII characters, with the exception of: %s";
    
    _error_tempate["validate.26"] = "%s parameter contains one or more invalid characters in its name.  Parameter names may contain letters (A-Z), numbers (0-9), and dashes (-).";
    _error_tempate["validate.30"] = "%s parameter contains one or more invalid characters in its name.  Parameter names may contain printable, 7-bit ASCII characters, with the exception of: %s";
    _error_tempate["validate.27"] = "PID parameter value (\"%s\") must take the form \"A\" or \"A.B\", where A and B are positive integers.";
    _error_tempate["validate.28"] = "INDEX parameter value (\"%s\") must be greater than zero.";
    _error_tempate["validate.29"] = "PREF parameter value (\"%s\") must be between 1 and 100 inclusive.";
    
    //#generic property warnings
    _error_tempate["validate.2"]  = "Property is not supported in this vCard version.  Supported versions are: %s";
    _error_tempate["validate.8"]  = "Property has no value assigned to it.";
    
    //#Address
    _error_tempate["validate.35"] = "Version 2.1 does not recognize multi-valued address fields (for example, two street addresses).  ez-vcard will output them in a comma-delimited fashion to prevent data loss, but the consuming application may not recognize this.";
    
    //#Agent
    _error_tempate["validate.10"] = "Embedded vCard warning: [%s] - %s: %s";
    
    //#DateOrTimeProperty
    _error_tempate["validate.11"] = "Text values are only supported in vCard version 4.0.";
    _error_tempate["validate.12"] = "Reduced accuracy and truncated dates are only supported in vCard version 4.0.";
    
    //#Geo
    _error_tempate["validate.13"] = "Latitude is missing.";
    _error_tempate["validate.14"] = "Longitude is missing.";
    
    //#Key
    _error_tempate["validate.15"] = "URL values are only permitted in vCard version 4.0.";
    
    //#Member
    _error_tempate["validate.17"] = "The Kind property must be set to \"group\" if the vCard contains any Member properties.";
    
    //#Profile
    _error_tempate["validate.18"] = "The only valid value for this property is \"VCARD\", but it is \"%s\".";
    
    //#StructuredName
    _error_tempate["validate.34"] = "Version 2.1 does not allow more than one additional name, prefix, or suffix to be defined within a structured name property.  ez-vcard will output them in a comma-delimited fashion to prevent data loss, but the consuming application may not recognize this.";
    
    //#Telephone
    _error_tempate["validate.19"] = "Tel URIs are only supported by vCard version 4.0.  ez-vcard will convert the URI to a string, but some of the data in the URI may be lost.";
    
    //#Timezone
    _error_tempate["validate.20"] = "Property value must be a UTC offset in vCard version 2.0.";
    //#validate.21                =Minute offset must be between 0 and 59. #removed in 0.9.7-SNAPSHOT
    
    //#RawProperty
    _error_tempate["validate.24"] = "%s property contains one or more invalid characters in its name.  Property names may contain letters (A-Z), numbers (0-9), and dashes (-).";
    _error_tempate["validate.33"] = "%s property contains one or more invalid characters in its name.  Property names may contain printable, 7-bit ASCII characters, with the exception of: %s";
    
    //#==============================================================================
    //#== PARSE WARNINGS ============================================================
    //#==============================================================================
    //#generic parse errors
    _error_tempate["parse.35"] = "%s property: %s";
    _error_tempate["parse.36"] = "Line %s (%s property): %s";
    _error_tempate["parse.37"] = "Line %s: %s";
    _error_tempate["parse.22"] = "Property has requested that it be skipped: %s";
    _error_tempate["parse.25"] = "Property value could not be parsed: %s";
    //#parse.26                =Problem parsing property in nested vCard: %s #removed in 0.10.2-SNAPSHOT
    //
    //#plain-text
    _error_tempate["parse.23"] = "The property''s character encoding (\"%s\") is not supported by this system.  %s will be used instead.";
    _error_tempate["parse.27"] = "Skipped. %s The entire line is: \"%s\"";
    _error_tempate["parse.28"] = "Ignoring invalid version value: %s";
    _error_tempate["parse.38"] = "Unable to decode quoted-printable value.  Treating as plain-text.  Reason: %s";
    //
    //#generic parse errors (JSON)
    _error_tempate["parse.29"] = "No \"version\" property found.";
    _error_tempate["parse.30"] = "Version must be 4.0.";
    _error_tempate["parse.31"] = "Property will not be parsed because jCard does not support embedded vCards.";
    
    //#HTML
    //#parse.32                =Property value could not be parsed.  It will be saved as an extended property instead.\n  Reason: %s\n  HTML: %s #removed in 0.10.2-SNAPSHOT
    
    //#XML
    _error_tempate["parse.0"]  = "No property value found.  One of the following XML elements were expected: %s";
    //#parse.33                =Property value could not be parsed.  It will be saved as a XML property instead.\n  Reason: %s\n  XML: %s #removed in 0.10.2-SNAPSHOT
    _error_tempate["parse.34"] = "Property will not be parsed because xCard does not support embedded vCards.";
    
    //#BinaryPropertyScribe
    _error_tempate["parse.1"]  = "Cannot parse <%s> tag (<object> tag expected).";
    _error_tempate["parse.2"]  = "<object> tag does not have a \"data\" attribute.";
    
    //#ClientPidMapScrive
    _error_tempate["parse.3"]  = "Value must contain a PID and a URI, separated by a semicolon.";
    _error_tempate["parse.4"]  = "PID component must be an integer.";
    
    //#DateOrTimePropertyScribe, RevisionScribe
    _error_tempate["parse.5"]  = "Could not parse date string.";
    _error_tempate[" parse.6"] = "Could not parse date string. Treating it as a text value.";
    
    //#GeoScribe
    _error_tempate["parse.7"]  = "Latitude missing.";
    _error_tempate["parse.8"]  = "Could not parse latitude: %s";
    _error_tempate["parse.9"]  = "Longitude missing.";
    _error_tempate["parse.10"] = "Could not parse longitude: %s";
    _error_tempate["parse.11"] = "Value must contain a latitude and longitude, separated by a semicolon.";
    _error_tempate["parse.12"] = "Could not parse value as a geo URI.";
    
    //#ImagePropertyScribe
    _error_tempate["parse.13"] = "<img> tag does not have a \"src\" attribute.";
    
    //#ImppScribe
    _error_tempate["parse.14"] = "Could not parse instant messenger information from link: %s";
    _error_tempate["parse.15"] = "Could not parse URI \"%s\": %s";
    
    //#SoundScribe
    _error_tempate["parse.16"] = "No <source> tag found beneath <audio> tag.";
    _error_tempate["parse.17"] = "<source> tag does not have a \"src\" attribute.";
    
    //#TelephoneScribe
    _error_tempate["parse.18"] = "Could not parse property value as a tel URI.  Assuming it''s text.";
    
    //#TimezoneScribe
    _error_tempate["parse.19"] = "Could not parse UTC offset.";
    _error_tempate["parse.20"] = "Could not parse UTC offset.  Treating it as text.";
    
    //#XmlScribe
    _error_tempate["parse.21"] = "Could not parse value as XML.";
    
    //#==============================================================================
    //#== EXCEPTION MESSAGES ========================================================
    //#==============================================================================
    
    _error_tempate["exception.0"]  = "[Error %s] %s";
    
    //#JCardRawWriter
    _error_tempate["exception.1"]  = "The vCard component has not been started yet.  Call \"writeStartVCard()\" first.";
    
    //#FoldedLineWriter
    _error_tempate["exception.2"]  = "Line length must be greater than 0.";
    _error_tempate["exception.3"]  = "The length of the indent string must be less than the max line length.";
    
    //#VCardRawLine
    _error_tempate["exception.4"]  = "Property name required.";
    
    //#VCardRawReader
    //#exception.5                 =Line is malformed--no colon character found. #removed in 0.9.11-SNAPSHOT
    //#exception.6                 =Unknown version number. #removed in 0.9.11-SNAPSHOT
    
    //#VCardRawWriter
    //#exception.7                 =Property "{0}" has its group set to "{1}".  This group name contains one or more invalid characters.  The following characters are not permitted: {2} #removed in 0.9.11-SNAPSHOT
    //#exception.8                 =Property "{0}" has its group set to "{1}".  This group name begins with one or more whitespace characters, which is not permitted. #removed in 0.9.11-SNAPSHOT
    //#exception.9                 =Property name "{0}" contains one or more invalid characters.  The following characters are not permitted: {1} #removed in 0.9.11-SNAPSHOT
    //#exception.10                =Property name "{0}" begins with one or more whitespace characters, which is not permitted. #removed in 0.9.11-SNAPSHOT
    //#exception.11                =Property "{0}" has a parameter named "{1}".  This parameter''s name contains one or more invalid characters.  The following characters are not permitted: {2} #removed in 0.9.11-SNAPSHOT
    //#exception.12                =Property "{0}" has a parameter named "{1}" whose value contains one or more invalid characters.  The following characters are not permitted: {2} #removed in 0.9.11-SNAPSHOT
    
    //#StreamWriter
    _error_tempate["exception.14"] = "No scribes were found for the following property classes: %s";
    
    //#VCardParameters
    _error_tempate["exception.15"] = "%s parameter value is malformed and could not be parsed. Retrieve its raw text values instead by calling property.getParameters().get(\"%s\").";
    //#exception.16                =Preference value must be between 1 and 100 inclusive. #removed in 0.9.10-SNAPSHOT
    //#exception.17                =Index value must be greater than 0. #removed in 0.9.10-SNAPSHOT
    
    //#URI errors
    _error_tempate["exception.18"] = "String does not begin with \"%s\".";
    _error_tempate["exception.23"] = "Parameter names can only contain letters, numbers, and hyphens.";
    
    //#DataUri
    _error_tempate["exception.19"] = "Data URI syntax is invalid.";
    _error_tempate["exception.20"] = "Data portion of data URI is missing.";
    _error_tempate["exception.43"] = "Cannot parse data URI.  Character set \"%s\" is not supported by this JVM.";
    _error_tempate["exception.44"] = "Cannot create data URI.  Character set \"%s\" is not supported by this JVM.";
    
    //#GeoUri
    _error_tempate["exception.21"] = "Coordinate B (longitude) is not present.";
    _error_tempate["exception.22"] = "Cannot parse coordinate %s.";
    _error_tempate["exception.24"] = "CRS can only contain letters, numbers, and hypens.";
    
    //#TelUri
    _error_tempate["exception.25"] = "Global number must contain at least one digit.";
    _error_tempate["exception.26"] = "Global number must start with \"+\".";
    _error_tempate["exception.27"] = "Global number contains invalid characters.  Only digits, hyphens, periods, and parenthesis are allowed.";
    _error_tempate["exception.28"] = "Local number contains invalid characters.  Only digits, hyphens, periods, parenthesis, asterisks, and hashes are allowed.";
    _error_tempate["exception.29"] = "Extension contains invalid characters..  Only digits, hyphens, periods, and parenthesis are allowed.";
    
    //#XCardOutputProperties
    _error_tempate["exception.30"] = "Indent amount cannot be less than zero.";
    
    //#VCardProperty
    _error_tempate["exception.31"] = "A problem occurred attempting to invoke the copy constructor of property class %s.";
    _error_tempate["exception.42"] = "Parameters object cannot be null.";
    
    //#JCardParseException
    _error_tempate["exception.35"] = "Expected %s but was %s.";
    
    //#PartialDate
    _error_tempate["exception.36"] = "Could not parse date: %s";
    _error_tempate["exception.37"] = "%s must be between %s and %s inclusive.";
    _error_tempate["exception.38"] = "Invalid date component combination: year, date";
    _error_tempate["exception.39"] = "Invalid time component combination: hour, second";
    
    //#UtcOffset
    _error_tempate["exception.40"] = "UTC offset string is not in ISO8610 format: %s";
    
    //#VCardDateFormat
    _error_tempate["exception.41"] = "Date string \"%s\" is not in a valid ISO-8601 format.";
}

Messages::~Messages()
{
    
}

Messages::Ptr Messages::getInstance() {
    if(single == nullptr )
        single = std::shared_ptr<Messages>(new Messages());
    
    return single;
}


/**
 * Gets a message.
 * @param key the message key
 * @param args the message arguments
 * @return the message or null if not found
 */
std::string Messages::getMessage(const std::string& key, const std::string& value1, const std::string& value2, const std::string& value3) {
    auto it = _error_tempate.find(key);
    if (it != _error_tempate.end()) {
        auto msg = it->second;
        std::vector<char> buf(1+snprintf(nullptr, 0, msg.c_str(), value1.c_str(), value2.c_str(), value3.c_str()));
        snprintf(buf.data(), buf.size(), msg.c_str(), value1.c_str(), value2.c_str(), value3.c_str());
        return std::string(buf.begin(), buf.end());
    }
    return "";
}
std::string Messages::getMessage(const std::string& key, const std::string& value1, const std::string& value2) {
    auto it = _error_tempate.find(key);
    if (it != _error_tempate.end()) {
        auto msg = it->second;
        std::vector<char> buf(1+snprintf(nullptr, 0, msg.c_str(), value1.c_str(), value2.c_str()));
        snprintf(buf.data(), buf.size(), msg.c_str(), value1.c_str(), value2.c_str());
        return std::string(buf.begin(), buf.end());
    }
    return "";
}

std::string Messages::getMessage(const std::string& key, int value) {
    auto it = _error_tempate.find(key);
    if (it != _error_tempate.end()) {
        auto msg = it->second;
        std::vector<char> buf(1+snprintf(nullptr, 0, msg.c_str(), value));
        snprintf(buf.data(), buf.size(), msg.c_str(), value);
        return std::string(buf.begin(), buf.end());
    }
    return "";
}

std::string Messages::getMessage(const std::string& key, const std::string& value) {
    auto it = _error_tempate.find(key);
    if (it != _error_tempate.end()) {
        auto msg = it->second;
        std::vector<char> buf(1+snprintf(nullptr, 0, msg.c_str(), value.c_str()));
        snprintf(buf.data(), buf.size(), msg.c_str(), value.c_str());
        return std::string(buf.begin(), buf.end());
    }
    return "";
}
std::string Messages::getMessage(const std::string& key) {
    auto it = _error_tempate.find(key);
    if (it != _error_tempate.end()) {
        return it->second;
    }
    return "";
}


//    public String getMessage(String key, Object... args) {
//        try {
//            String message = messages.getString(key);
//            return MessageFormat.format(message, args);
//        } catch (MissingResourceException e) {
//            return null;
//        }
//    }




//    private Messages() {
//        messages = ResourceBundle.getBundle("ezvcard/messages");
//    }
//
//    /**
//     * Gets a validation warning message.
//     * @param code the message code
//     * @param args the message arguments
//     * @return the message or null if not found
//     */
//    public String getValidationWarning(int code, Object... args) {
//        return getMessage("validate." + code, args);
//    }
//
//    /**
//     * Gets a parser warning message.
//     * @param code the message code
//     * @param args the message arguments
//     * @return the message or null if not found
//     */
//    public String getParseMessage(int code, Object... args) {
//        return getMessage("parse." + code, args);
//    }
//
//    /**
//     * Gets an exception message.
//     * @param code the message code
//     * @param args the message arguments
//     * @return the message or null if not found
//     */
//    public String getExceptionMessage(int code, Object... args) {
//        String message = getMessage("exception." + code, args);
//        return (message == null) ? null : getMessage("exception.0", code, message);
//    }
//
//    /**
//     * Builds an {@link IllegalArgumentException} from an exception message.
//     * @param code the message code
//     * @param args the message arguments
//     * @return the exception or null if the message was not found
//     */
//    public IllegalArgumentException getIllegalArgumentException(int code, Object... args) {
//        String message = getExceptionMessage(code, args);
//        return (message == null) ? null : new IllegalArgumentException(message);
//    }
//

//}
