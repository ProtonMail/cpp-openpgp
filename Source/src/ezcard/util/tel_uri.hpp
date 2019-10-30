//
//  tel_uri.hpp
//  OpenPGP
//
//  Created by Yanfeng Zhang on 6/3/17.
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

#ifndef tel_uri_hpp
#define tel_uri_hpp

#include <stdio.h>
#include <string>
#include <map>
#include <regex>
#include <iostream>
#include <iomanip>
#include <exception>
#include "string_util.hpp"
#include "clearable_string_builder.hpp"
#include "character_bitset.hpp"
#include <utilities/UTF8.h>
#include "string_util.hpp"
#include <bitset>

namespace ezvcard {
    
    class TelUri;
    namespace Tel {
        class Builder;
        class Builder {
            friend class ezvcard::TelUri;
            
        public:
            typedef std::shared_ptr<Builder> Ptr;
            
        private:
            std::string _number;
            std::string _extension;
            std::string _isdnSubaddress;
            std::string _phoneContext;
            std::map<std::string, std::string> _parameters;
            CharacterBitSet::Ptr validParamNameChars = nullptr;
            
            Builder() {
                validParamNameChars = std::make_shared<CharacterBitSet>("a-zA-Z0-9-");
            }

            
        public:
            //Builder(TelUri original);
            
            Builder(const std::string& global_number) : Builder(){
                globalNumber(global_number);
            }
            
            Builder(const std::string& local_number, const std::string& phoneContext) : Builder(){
                localNumber(local_number, phoneContext);
            }
            
            std::shared_ptr<ezvcard::TelUri> build();

            void globalNumber(const std::string& global_number) {
                if (global_number.find("+") != 0)
                {
                    throw std::invalid_argument("26");
                }
                auto validChars = std::make_shared<CharacterBitSet>("0-9.()-");
                if (!validChars->containsOnly(global_number, 1)) {
                    throw std::invalid_argument("27");
                }
                
                auto requiredChars = std::make_shared<CharacterBitSet>("0-9");
                if (!requiredChars->containsAny(global_number, 1)) {
                    throw std::invalid_argument("25");
                }
                
                _number = global_number;
                _phoneContext = "";
            }
            
            void localNumber(const std::string& local_number, const std::string& phoneContext) {
                auto validChars = std::make_shared<CharacterBitSet>("0-9.()*#-");
                if (!validChars->containsOnly(local_number)) {
                    throw std::invalid_argument("28");
                }
                
                auto requiredChars = std::make_shared<CharacterBitSet>("0-9*#");
                if (!requiredChars->containsAny(local_number)) {
                    throw std::invalid_argument("28");
                }
                
                _number = local_number;
                _phoneContext = phoneContext;
            }

            void extension(const std::string& extension) {
                if (extension != "") {
                    auto validChars = std::make_shared<CharacterBitSet>("0-9.()-");
                    if (!validChars->containsOnly(extension)) {
                        throw std::invalid_argument("29");
                    }
                }
                _extension = extension;
            }
            
            void isdnSubaddress(const std::string& isdnSubaddress) {
                _isdnSubaddress = isdnSubaddress;
            }
            
            void parameter(const std::string& name, const std::string& value) {
                if (!validParamNameChars->containsOnly(name)) {
                    throw std::invalid_argument("23");
                }
                if (value == "") {
                    _parameters.erase(name);
                } else {
                    _parameters[name] = value;
                }
            }
        };
        
    }
    
    /**
     * <p>
     * Represents a URI for encoding telephone numbers.
     * </p>
     * <p>
     * Example tel URI: {@code tel:+1-212-555-0101}
     * </p>
     * <p>
     * This class is immutable. Use the {@link Builder} class to construct a new
     * instance, or the {@link #parse} method to parse a tel URI string.
     * </p>
     * <p>
     * <b>Examples:</b>
     * </p>
     *
     * <pre class="brush:java">
     * TelUri uri = new TelUri.Builder("+1-212-555-0101").extension("123").build();
     * TelUri uri = TelUri.parse("tel:+1-212-555-0101;ext=123");
     * TelUri copy = new TelUri.Builder(uri).extension("124").build();
     * </pre>
     * @see <a href="http://tools.ietf.org/html/rfc3966">RFC 3966</a>
     * @author Michael Angstadt
     */
    class TelUri {
        friend class Tel::Builder;
        
    public:
        typedef std::shared_ptr<TelUri> Ptr;
        
//        TelUri(const Tel::Builder::Ptr& builder) : TelUri() {
//            number = builder->number;
//            extension = builder->extension;
//            isdnSubaddress = builder->isdnSubaddress;
//            phoneContext = builder->phoneContext;
//            parameters = builder->parameters;
//        }
//        
        TelUri(const Tel::Builder& builder) : TelUri() {
            number = builder._number;
            extension = builder._extension;
            isdnSubaddress = builder._isdnSubaddress;
            phoneContext = builder._phoneContext;
            parameters = builder._parameters;
        }
        
        /**
         * Parses a tel URI.
         * @param uri the URI (e.g. "tel:+1-610-555-1234;ext=101")
         * @return the parsed tel URI
         * @throws IllegalArgumentException if the string is not a valid tel URI
         */
        static TelUri::Ptr parse(const std::string& uri) {
            //URI format: tel:number;prop1=value1;prop2=value2
            std::string scheme = "tel:";
            auto sub = uri.substr(0, scheme.size());
            if (uri.size() < scheme.size() || !str_equals(sub, scheme)) { //!uri.substring(0, scheme.length()).equalsIgnoreCase(scheme)) {
                //not a tel URI
                throw std::invalid_argument("18 " + scheme);// Messages.INSTANCE.getIllegalArgumentException(18, scheme);
            }
            auto builder = std::shared_ptr<Tel::Builder>(new Tel::Builder());
            ClearableStringBuilder::Ptr buffer = std::make_shared<ClearableStringBuilder>();
            
            std::string paramName = "";
            for (int i = (int)scheme.size(); i < uri.size(); i++) {
                char c = uri[i];
                if (c == '=' && builder->_number != "" && paramName == "") {
                    paramName = buffer->getAndClear();
                    continue;
                }
                if (c == ';') {
                    handleEndOfParameter(buffer, paramName, builder);
                    paramName = "";
                    continue;
                }
                buffer->append(c);
            }
            handleEndOfParameter(buffer, paramName, builder);
            return builder->build();
        }
    private:
        /**
         * The characters which are allowed to exist unencoded inside of a parameter
         * value.
         */
        static std::bitset<128> validParameterValueCharacters;
        static bool initaled;
        

        const static std::string PARAM_EXTENSION;
        const static std::string PARAM_ISDN_SUBADDRESS;
        const static std::string PARAM_PHONE_CONTEXT;
    
        std::string number;
        std::string extension;
        std::string isdnSubaddress;
        std::string phoneContext;
        std::map<std::string, std::string> parameters;
        
    private:
        TelUri() {
            if (!initaled) {
                initaled = true;
                for (int i = '0'; i <= '9'; i++) {
                    validParameterValueCharacters.set(i);
                }
                for (int i = 'A'; i <= 'Z'; i++) {
                    validParameterValueCharacters.set(i);
                }
                for (int i = 'a'; i <= 'z'; i++) {
                    validParameterValueCharacters.set(i);
                }
                std::string s = "!$&'()*+-.:[]_~/";
                for (int i = 0; i < s.size(); i++) {
                    char c = s[i];
                    validParameterValueCharacters.set(c);
                }
            }
            
        }
        
        static void addParameter(const std::string& name, std::string value_in, const Tel::Builder::Ptr& builder) {
            auto value = decodeParameterValue(value_in);
            if (str_equals(PARAM_EXTENSION, name)) {
                builder->_extension = value;
                return;
            }
            
            if (str_equals(PARAM_ISDN_SUBADDRESS, name)) {
                builder->_isdnSubaddress = value;
                return;
            }
            
            if (str_equals(PARAM_PHONE_CONTEXT, name)) {
                builder->_phoneContext = value;
                return;
            }
            builder->_parameters[name] = value;
        }
        
        static void handleEndOfParameter(const ClearableStringBuilder::Ptr& buffer, const std::string& paramName, const Tel::Builder::Ptr& builder) {
            auto s = buffer->getAndClear();
            if (builder->_number == "") {
                builder->_number = s;
                return;
            }
            if (paramName == "") {
                if (s.length() > 0) {
                    addParameter(s, "", builder);
                }
                return;
            }
            addParameter(paramName, s, builder);
        }
        
        /**
         * Decodes escaped characters in a parameter value.
         * @param value the parameter value
         * @return the decoded value
         */
        static std::string decodeParameterValue(const std::string& value) {
            return decodeURIComponent(value);
        }
        
        /**
         * Writes a parameter to a string.
         * @param name the parameter name
         * @param value the parameter value
         * @param ss the string to write to
         */
        static void writeParameter(const std::string& name, const std::string& value, std::stringstream& ss) {
            ss << ';';
            ss << name;
            ss << '=';
            ss << encodeParameterValue(value);
        }
        
        static std::string encodeParameterValue(const std::string& value) {
            std::stringstream ss;
            bool initaled = false;
            for (int i = 0; i < value.size(); i++) {
                char c = value[i];
                if (c < validParameterValueCharacters.size() && validParameterValueCharacters.test(c)) {
                    if (initaled) {
                        ss << c;
                    }
                } else {
                    if (!initaled) {
                        initaled = true;
                        ss << value.substr(0, i);
                    }
                    ss << str_to_lower(URLEncode(std::string(1, c)));
                }
            }
            return (!initaled) ? value : ss.str();
        }
        
        //    private static String encodeParameterValue(String value) {
        //        StringBuilder sb = null;
        //        for (int i = 0; i < value.length(); i++) {
        //            char c = value.charAt(i);
        //            if (c < validParameterValueCharacters.length && validParameterValueCharacters[c]) {
        //                if (sb != null) {
        //                    sb.append(c);
        //                }
        //            } else {
        //                if (sb == null) {
        //                    sb = new StringBuilder(value.length() * 2);
        //                    sb.append(value.substring(0, i));
        //                }
        //                String hex = Integer.toString(c, 16);
        //                sb.append('%').append(hex);
        //            }
        //        }
        //        return (sb == null) ? value : sb.toString();
        //    }
        
    public:
        /**
         * Gets the phone number.
         * @return the phone number
         */
        std::string getNumber() {
            return number;
        }
        
        /**
         * Gets the phone context.
         * @return the phone context (e.g. "example.com") or null if not set
         */
        std::string getPhoneContext() {
            return phoneContext;
        }
        
        /**
         * Gets the extension.
         * @return the extension (e.g. "101") or null if not set
         */
        std::string getExtension() {
            return extension;
        }
        
        /**
         * Gets the ISDN sub address.
         * @return the ISDN sub address or null if not set
         */
        std::string getIsdnSubaddress() {
            return isdnSubaddress;
        }
        
        /**
         * Gets a parameter value.
         * @param name the parameter name
         * @return the parameter value or null if not found
         */
        std::string getParameter(const std::string& name) {
            auto found = parameters.find(name);
            if (found != parameters.end()) {
                return found->second;
            }
            return "";
        }
        
        /**
         * Gets all parameters.
         * @return all parameters
         */
        std::map<std::string, std::string> getParameters() {
            return parameters;
        }
        
        void put(std::string key, std::string value) {
            parameters[key] = value;
        }
        
        bool equals(const TelUri::Ptr& obj) {
            if (obj == nullptr) return false;
            if (obj.get() == this) return true;
            
            if (!str_equals(extension, obj->getExtension())) return false;

            if (!str_equals(isdnSubaddress, obj->getIsdnSubaddress())) return false;
            
            if (!str_equals(number, obj->getNumber())) return false;

            if (parameters.size() != obj->getParameters().size()) return false;
            
            if (parameters == obj->getParameters()) return false;

            if (!str_equals(phoneContext, obj->getPhoneContext())) return false;

            return true;
        }
        
        std::string toString() {
            std::stringstream ss ("");
            
            ss << "tel:";
            ss << number;
            
            if (extension != "") {
                writeParameter(PARAM_EXTENSION, extension, ss);
            }
            if (isdnSubaddress != "") {
                writeParameter(PARAM_ISDN_SUBADDRESS, isdnSubaddress, ss);
            }
            if (phoneContext != "") {
                writeParameter(PARAM_PHONE_CONTEXT, phoneContext, ss);
            }
            
            for (auto entry : parameters) {
                auto name = entry.first;
                auto value = entry.second;
                writeParameter(name, value, ss);
            }
            return ss.str();
        }


        //    @Override
        //    public int hashCode() {
        //        final int prime = 31;
        //        int result = 1;
        //        result = prime * result + ((extension == null) ? 0 : extension.toLowerCase().hashCode());
        //        result = prime * result + ((isdnSubaddress == null) ? 0 : isdnSubaddress.toLowerCase().hashCode());
        //        result = prime * result + ((number == null) ? 0 : number.toLowerCase().hashCode());
        //        result = prime * result + ((parameters == null) ? 0 : StringUtils.toLowerCase(parameters).hashCode());
        //        result = prime * result + ((phoneContext == null) ? 0 : phoneContext.toLowerCase().hashCode());
        //        return result;
        //    }


    };
    
    
}


#endif /* tel_uri_hpp */
