//
//  vobject_writer.cpp
//  OpenPGP
//
//  Created by Yanfeng Zhang on 5/8/17.
//  Copyright © 2017 Yanfeng Zhang. All rights reserved.
//

#include "vobject_writer.hpp"
#include <exception>
#include "string_util.hpp"
#include "vobject_validator.hpp"
#include "vobject_property_values.hpp"


namespace vinnie {
    
    
    const std::string VObjectWriter::NEWLINE = "\r\n";
    
    /**
     * Creates a new vobject writer.
     * @param writer the output stream
     * @param syntaxStyle the syntax style to use
     */
    VObjectWriter::VObjectWriter(const std::shared_ptr<std::stringstream>& writer, SyntaxStyle syntaxStyle) {
        _writer = std::make_shared<FoldedLineWriter>(writer);
        _syntaxStyle = syntaxStyle;
        
        allowedGroupChars = VObjectValidator::get()->allowedCharactersGroup(syntaxStyle, false);
        allowedPropertyNameChars = VObjectValidator::get()->allowedCharactersPropertyName(syntaxStyle, false);
        allowedParameterNameChars = VObjectValidator::get()->allowedCharactersParameterName(syntaxStyle, false);
        allowedParameterValueChars = VObjectValidator::get()->allowedCharactersParameterValue(syntaxStyle, false, false);
    }
    
    /**
     * Gets the writer that is used to write data to the output stream.
     * @return the folded line writer
     */
    FoldedLineWriter::Ptr VObjectWriter::getFoldedLineWriter() {
        return _writer;
    }
    
    
    bool VObjectWriter::isCaretEncodingEnabled() {
        return _caretEncodingEnabled;
    }
    
    void VObjectWriter::setCaretEncodingEnabled(bool enable) {
        _caretEncodingEnabled = enable;
        allowedParameterValueChars = VObjectValidator::get()->allowedCharactersParameterValue(_syntaxStyle, enable, false);
    }
    
    
    /**
     * Gets the syntax style the writer is using.
     * @return the syntax style
     */
    SyntaxStyle VObjectWriter::getSyntaxStyle() {
        return _syntaxStyle;
    }
    
    /**
     * Sets the syntax style that the writer should use.
     * @param syntaxStyle the syntax style
     */
    void VObjectWriter::setSyntaxStyle(SyntaxStyle syntaxStyle) {
        _syntaxStyle = syntaxStyle;
    }
    
    /**
     * Writes a property marking the beginning of a component.
     * @param componentName the component name (e.g. "VCARD")
     * @throws IllegalArgumentException if the component name is null or empty
     * @throws IOException if there's a problem writing to the data stream
     */
    void VObjectWriter::writeBeginComponent(const std::string& componentName) {
        if (componentName.empty()) {
            throw std::invalid_argument("Component name cannot be null or empty.");
        }
        writeProperty("BEGIN", componentName);
    }
    
    /**
     * Writes a property marking the end of a component.
     * @param componentName the component name (e.g. "VCARD")
     * @throws IllegalArgumentException if the component name is null or empty
     * @throws IOException if there's a problem writing to the data stream
     */
    void VObjectWriter::writeEndComponent(const std::string& componentName) {
        if (componentName.empty()) {
            throw std::invalid_argument("Component name cannot be null or empty.");
        }
        writeProperty("END", componentName);
    }
    
    /**
     * Writes a "VERSION" property.
     * @param version the version string (e.g. "2.1")
     * @throws IllegalArgumentException if the version string is null or empty
     * @throws IOException if there's a problem writing to the data stream
     */
    void VObjectWriter::writeVersion(const std::string& version) {
        if (version.empty()) {
            throw std::invalid_argument("Version string cannot be null or empty.");
        }
        writeProperty("VERSION", version);
    }
    
    /**
     * Writes a property to the data stream.
     * @param name the property name (e.g. "FN")
     * @param value the property value
     * @throws IllegalArgumentException if the given data contains one or more
     * characters which would break the syntax and cannot be written
     * @throws IOException if there's a problem writing to the data stream
     */
    void VObjectWriter::writeProperty(const std::string& name, const std::string& value) {
        writeProperty("", name, std::make_shared<VObjectParameters>(), value);
    }
    
    /**
     * Writes a property to the data stream.
     * @param property the property to write
     * @throws IllegalArgumentException if the given data contains one or more
     * characters which would break the syntax and cannot be written
     * @throws IOException if there's a problem writing to the data stream
     */
    void VObjectWriter::writeProperty(const VObjectProperty::Ptr& property) {
        writeProperty(property->getGroup(), property->getName(), property->getParameters(), property->getValue());
    }
    
    /**
     * Writes a property to the data stream.
     * @param group the group or null if there is no group
     * @param name the property name (e.g. "FN")
     * @param parameters the property parameters
     * @param value the property value (will be converted to "quoted-printable"
     * encoding if the ENCODING parameter is set to "QUOTED-PRINTABLE")
     * @throws IllegalArgumentException if the given data contains one or more
     * characters which would break the syntax and cannot be written
     * @throws IOException if there's a problem writing to the data stream
     */
    void VObjectWriter::writeProperty(const std::string& group,
                                      const std::string& name,
                                      VObjectParameters::Ptr parameters,
                                      std::string value) {
        /*
         * Ensure that the property is safe to write before writing it.
         */
        validate(group, name, parameters);
        
        _parametersCopied = false;
        
        //sanitize value
        switch (_syntaxStyle) {
            case OLD:
                /*
                 * Old style does not support the "\n" escape sequence so encode the
                 * value in quoted-printable encoding if any newline characters
                 * exist.
                 */
                if (containsNewlines(value) && !parameters->isQuotedPrintable()) {
                    parameters = copyParameters(parameters);
                    parameters->put("ENCODING", "QUOTED-PRINTABLE");
                }
                break;
            case NEW:
                value = escapeNewlines(value);
                break;
            default:
                break;
        }
        
        /*
         * Determine if the property value must be encoded in quoted printable
         * encoding. If so, then determine what character set to use for the
         * encoding.
         */
        bool useQuotedPrintable = parameters->isQuotedPrintable();
        Charset::Ptr quotedPrintableCharset = nullptr;
        if (useQuotedPrintable) {
            try {
                quotedPrintableCharset = parameters->getCharset();
            } catch (const std::exception& e) {
                //character set not recognized
            }
            
            if (quotedPrintableCharset == nullptr) {
                quotedPrintableCharset = Charset::forName("UTF-8");
                parameters = copyParameters(parameters);
                parameters->replace("CHARSET", quotedPrintableCharset->name());
            }
        }
        
        //write the group
        if (!group.empty()) {
            _writer->write(group);
            _writer->write('.');
        }
        
        //write the property name
        _writer->write(name);
        
        //write the parameters
        auto paraMap = parameters->getMap();
        for (auto parameter : paraMap) {
            auto parameterName = parameter.first;
            auto parameterValues = parameter.second;
            if (parameterValues.empty()) {
                continue;
            }
            
            if (_syntaxStyle == SyntaxStyle::OLD) {
                //e.g. ADR;TYPE=home;TYPE=work;TYPE=another,value:
                for (auto parameterValue : parameterValues) {
                    parameterValue = sanitizeOldStyleParameterValue(parameterValue);
                    
                    _writer->write(';');
                    if (!parameterName.empty()) {
                        _writer->write(parameterName);
                        _writer->write('=');
                    }
                    _writer->write(parameterValue);
                }
            } else {
                //e.g. ADR;TYPE=home,work,"another,value":
                _writer->write(';');
                if (!parameterName.empty()) {
                    _writer->write(parameterName);
                    _writer->write('=');
                }
                bool first = true;
                for (auto parameterValue : parameterValues) {
                    parameterValue = sanitizeNewStyleParameterValue(parameterValue);
                    
                    if (!first) {
                        _writer->write(',');
                    }
                    
                    if (shouldQuoteParameterValue(parameterValue)) {
                        _writer->write('"');
                        _writer->write(parameterValue);
                        _writer->write('"');
                    } else {
                        _writer->write(parameterValue);
                    }
                    first = false;
                }
            }
        }
        _writer->write(':');
        _writer->write(value, useQuotedPrintable, quotedPrintableCharset);
        _writer->writeln();
    }
    
    
    
    /**
     * Checks to make sure the given property data is safe to write (does not
     * contain illegal characters, etc).
     * @param group the property group or null if not set
     * @param name the property name
     * @param parameters the property parameters
     * @throws IllegalArgumentException if there is a validation error
     */
    
    void VObjectWriter::validate(const std::string& group, const std::string& name, const VObjectParameters::Ptr& parameters) {
        //validate the group name
        if (!group.empty()) {
            if (!allowedGroupChars->check(group)) {
                auto errorstring = "Property \"" + name + "\" has its group set to \"" + group + "\".  This group name contains one or more invalid characters.  The following characters are not permitted: " + allowedGroupChars->flip()->toString();
                throw std::invalid_argument(errorstring);
            }
            if (beginsWithWhitespace(group)) {
                throw std::invalid_argument("Property \"" + name + "\" has its group set to \"" + group + "\".  This group name begins with one or more whitespace characters, which is not permitted.");
            }
        }
        
        //validate the property name
        if (name.empty()) {
            throw std::invalid_argument("Property name cannot be empty.");
        }
        if (!allowedPropertyNameChars->check(name)) {
            throw std::invalid_argument("Property name \"" + name + "\" contains one or more invalid characters.  The following characters are not permitted: " + allowedPropertyNameChars->flip()->toString());
        }
        if (beginsWithWhitespace(name)) {
            throw std::invalid_argument("Property name \"" + name + "\" begins with one or more whitespace characters, which is not permitted.");
        }
        
        //validate the parameter names and values
        auto paraMap = parameters->getMap();
        for (auto parameter : paraMap) {
            //validate the parameter name
            auto parameterName = parameter.first;
            if (parameterName.empty() && _syntaxStyle == NEW) {
                throw std::invalid_argument("Property \"" + name + "\" has a parameter whose name is null. This is not permitted with new style syntax.");
            }
            if (!parameterName.empty() && !allowedParameterNameChars->check(parameterName)) {
                throw std::invalid_argument("Property \"" + name + "\" has a parameter named \"" + parameterName + "\".  This parameter's name contains one or more invalid characters.  The following characters are not permitted: " + allowedParameterNameChars->flip()->toString());
            }
            
            //validate the parameter values
            auto parameterValues = parameter.second;
            for (auto parameterValue : parameterValues) {
                if (!allowedParameterValueChars->check(parameterValue)) {
                    throw std::invalid_argument("Property \"" + name + "\" has a parameter named \"" + parameterName + "\" whose value contains one or more invalid characters.  The following characters are not permitted: " + allowedParameterValueChars->flip()->toString());
                }
            }
        }
    }
    
    /**
     * Determines if a string contains at least one newline character.
     * @param string the string
     * @return true if it contains at least one newline character, false if not
     */
    bool VObjectWriter::containsNewlines(const std::string& string) {
        for (int i = 0; i < string.length(); i++) {
            char c = string[i];
            switch (c) {
                case '\r':
                case '\n':
                    return true;
            }
        }
        return false;
    }
    
    /**
     * Determines if a parameter value should be enclosed in double quotes.
     * @param value the parameter value
     * @return true if it should be enclosed in double quotes, false if not
     */
    bool VObjectWriter::shouldQuoteParameterValue(const std::string& value) {
        for (int i = 0; i < value.length(); i++) {
            char c = value[i];
            switch (c) {
                case ',':
                case ':':
                case ';':
                    return true;
            }
        }
        return false;
    }
    
    /**
     * Determines if a string starts with whitespace.
     * @param string the string
     * @return true if it starts with whitespace, false if not
     */
    bool VObjectWriter::beginsWithWhitespace(const std::string& string) {
        if (string.length() == 0) {
            return false;
        }
        char first = string[0];
        return (first == ' ' || first == '\t');
    }
    
    /**
     * <p>
     * Sanitizes a parameter value for new style syntax.
     * </p>
     * <p>
     * This method applies circumflex accent encoding, if it's enabled.
     * Otherwise, it returns the value unchanged.
     * </p>
     * @param value the parameter value
     * @return the sanitized parameter value
     */
    std::string VObjectWriter::sanitizeNewStyleParameterValue(const std::string& value) {
        if (_caretEncodingEnabled) {
            return applyCaretEncoding(value);
        }
        
        return value;
    }
    
    /**
     * <p>
     * Sanitizes a parameter value for old style syntax.
     * </p>
     * <p>
     * This method escapes backslashes and semicolons.
     * </p>
     * @param value the parameter value
     * @return the sanitized parameter value
     */
    std::string VObjectWriter::sanitizeOldStyleParameterValue(const std::string& value) {
        std::stringstream sb("");
        bool set = false;
        for (int i = 0; i < value.length(); i++) {
            char c = value[i];
            if (c == '\\' || c == ';') {
                if (set == false) {
                    set = true;
                    sb << value.substr(0, i);
                }
                sb << "\\";
            }
            if (set) {
                sb << c;
            }
        }
        return (set) ? sb.str() : value;
    }
    
    /**
     * Applies circumflex accent encoding to a parameter value.
     * @param value the parameter value
     * @return the encoded value
     */
    std::string VObjectWriter::applyCaretEncoding(const std::string& value){
        std::stringstream sb("");
        bool set = false;
        char prev = 0;
        for (int i = 0; i < value.length(); i++) {
            char c = value[i];
            
            if (c == '^' || c == '"' || c == '\r' || c == '\n') {
                if (c == '\n' && prev == '\r') {
                    /*
                     * Do not write a second newline escape sequence if the
                     * newline sequence is "\r\n".
                     */
                } else {
                    if (set == false) {
                        set = true;
                        sb << value.substr(0, i);
                    }
                    sb << '^';
                    
                    switch (c) {
                        case '\r':
                        case '\n':
                            sb << 'n';
                            break;
                        case '"':
                            sb << '\'';
                            break;
                        default:
                            sb << c;
                    }
                }
            } else if (set) {
                sb << c;
            }
            
            prev = c;
        }
        return (set) ? sb.str() : value;
    }
    
    
    /**
     * Copies the given list of parameters if it hasn't been copied before.
     * @param parameters the parameters
     * @return the copy or the same object if the parameters were copied before
     */
    VObjectParameters::Ptr VObjectWriter::copyParameters(const VObjectParameters::Ptr& parameters) {
        if (_parametersCopied) {
            return parameters;
        }
        VObjectParameters::Ptr copy = std::make_shared<VObjectParameters>(parameters);
        _parametersCopied = true;
        return copy;
    }
    
}
