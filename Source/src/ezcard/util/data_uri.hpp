//
//  data_uri.hpp
//  OpenPGP
//
//  Created by Yanfeng Zhang on 4/4/18.
//  Copyright © 2018 Yanfeng Zhang. All rights reserved.
//

#ifndef data_uri_hpp
#define data_uri_hpp

#include <string>
#include "messages.hpp"
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
#include "base64.h"
#include "utility.h"


namespace ezvcard {
    
    class DataUri {
    private:
        std::string _data;
        std::string _text;
        std::string _contentType;
        
        
    public:
        typedef std::shared_ptr<DataUri> Ptr;
        
        ~DataUri() {
            _data = "";
            _text = "";
            _contentType = "";
        }
        
        
        /**
         * Creates a data URI.
         * @param contentType the content type of the data (e.g. "image/png")
         * @param data the data
         */
        DataUri(const std::string& contentType, const std::string& data, bool isText) {
            if (isText) {
                Init(contentType, "", data);
            } else {
                Init(contentType, data, "");
            }
        }
        
        /**
         * Creates a data URI with a content type of "text/plain".
         * @param text the text
         */
        DataUri(const std::string& text) {
            Init("text/plain", "", text);
        }
        
        /**
         * Copies a data URI.
         * @param original the data URI to copy
         */
        DataUri(const DataUri::Ptr& original) {
            if(original != nullptr) {
                Init(original->getContentType(), original->getData(), original->getText());
            }
        }
        
//        @Override
//        public int hashCode() {
//            final int prime = 31;
//            int result = 1;
//            result = prime * result + contentType.hashCode();
//            result = prime * result + Arrays.hashCode(data);
//            result = prime * result + ((text == null) ? 0 : text.hashCode());
//            return result;
//        }
        
        bool equals(const DataUri::Ptr& obj) {
            if (this == obj.get()) return true;
            if (obj == nullptr) return false;
            
            if (obj->getContentType() != _contentType) {
                return false;
            }
            
            if (obj->getData() != _data) {
                return false;
            }
            
            if (obj->getText() != _text) {
                return false;
            }
            return true;
        }
        
        
    private:
        DataUri(const std::string& contentType, const std::string& data, const std::string& text) {
            Init(contentType, data, text);
        }

        void Init(const std::string& contentType, const std::string& data, const std::string& text) {
            _contentType = (contentType == "") ? "" : str_to_lower(contentType);
            _data = data;
            _text = text;
        }
        
    public:
        /**
         * Parses a data URI string.
         * @param uri the URI string (e.g. "data:image/jpeg;base64,[base64 string]")
         * @return the parsed data URI
         * @throws IllegalArgumentException if the string is not a valid data URI or
         * it cannot be parsed
         */
        static DataUri::Ptr parse(const std::string& uri) {
            //Syntax: data:[<media type>][;charset=<character set>][;base64],<data>
            const std::string scheme = "data:";
            bool contentTypeSet = false;
            auto scheme_length = scheme.length();
            auto uri_length = uri.length();
            if (uri_length < scheme_length || !str_equals(uri.substr(0, scheme.size()), scheme)) {
                //not a data URI
                Messages::getInstance()->getIllegalArgumentException(18, scheme);
            }
            
            std::string contentType = "";
            std::string charset = "";
            bool base64 = false;
            std::string dataStr = "";
            auto tokenStart = scheme_length;
            for (auto i = scheme_length; i < uri_length; i++) {
                auto c = uri[i];
                if (c == ';') {
                    auto token = uri.substr(tokenStart, i - tokenStart);
                    if (!contentTypeSet) {
                        contentType = str_to_lower(token);
                        contentTypeSet = true;
                    } else {
                        if (startsWith(str_to_lower(token), "charset=")) {
                            auto equals = token.find('=');
                            charset = token.substr(equals + 1);
                        } else if (str_equals("base64", token)) {
                            base64 = true;
                        }
                    }
                    tokenStart = i + 1;
                    continue;
                }
                
                if (c == ',') {
                    auto token = uri.substr(tokenStart, i-tokenStart);
                    if (!contentTypeSet) {
                        contentType = str_to_lower(token);
                        contentTypeSet = true;
                    } else {
                        if (startsWith(str_to_lower(token), "charset=")) {
                            auto equals = token.find("="); //token.indexOf('=');
                            charset = token.substr(equals + 1);
                        } else if (str_equals("base64", token)) {
                            base64 = true;
                        }
                    }
                    
                    dataStr = uri.substr(i + 1);
                    break;
                }
            }
            
            if (dataStr == "") {
                throw Messages::getInstance()->getIllegalArgumentException(20);
            }
            
            std::string text = "";
            std::string data = "";
            if (base64) {
                //std::cout << dataStr << std::endl;
                dataStr = ProtonMail::replaceAll(dataStr, "\\s", "");
                //std::cout << dataStr << std::endl;
                data = base64_decode(dataStr);
                
                auto check = base64_encode(data);
                //std::cout << check << std::endl;
                if (charset != "") {
                    // try {
                    text = data;//new String(data, charset);
                    //  } catch (UnsupportedEncodingException e) {
                    //      throw new IllegalArgumentException(Messages.INSTANCE.getExceptionMessage(43, charset), e);
                    //  }
                    data = "";
                }
            } else {
                text = dataStr;
            }
            
            return std::shared_ptr<DataUri>(new DataUri(contentType, data, text));
        }
        
        /**
         * Gets the binary data.
         * @return the binary data or null if the value was text
         */
        std::string getData() {
            return _data;
        }
        
        /**
         * Gets the content type.
         * @return the content type (e.g. "image/png")
         */
        std::string getContentType() {
            return _contentType;
        }
        
        /**
         * Gets the text value.
         * @return the text value or null if the value was binary
         */
        std::string getText() {
            return _text;
        }
        
        /**
         * Creates a data URI string.
         * @return the data URI (e.g. "data:image/jpeg;base64,[base64 string]")
         */
        std::string toString() {
            return toString("");
        }
        
        /**
         * Creates a data URI string.
         * @param charset only applicable if the data URI's value is text. Defines
         * the character set to encode the text in, or null not to specify a
         * character set
         * @return the data URI (e.g. "data:image/jpeg;base64,[base64 string]")
         * @throws IllegalArgumentException if the given character set is not
         * supported by this JVM
         */
        std::string toString(const std::string& charset) {
            
            if (!str_equals(charset, "UTF-8")) {
                throw std::invalid_argument("unsupported charset:" + charset);
            }
            
            std::stringstream ss ("");
            
            ss << "data:";
            ss << _contentType;
            if (_data != "") {
                ss << ";base64,";
                
                auto check = base64_encode(_data);
                //std::cout << check << std::endl;
                ss << base64_encode(_data);
            } else if (_text != "") {
                if (charset == "") {
                    ss << ',';
                    ss << _text;
                } else {
//                    byte[] data;
//                    try {
//                        data = text.getBytes(charset);
//                    } catch (UnsupportedEncodingException e) {
//                        throw new IllegalArgumentException(Messages.INSTANCE.getExceptionMessage(44, charset), e);
//                    }
                    
                    ss << ";charset=";
                    ss << charset;
                    ss << ";base64,";
                    ss << base64_encode(_text);
                }
            } else {
                ss << ',';
            }
            
            return ss.str();
        }
    };
}

#endif /* data_uri_hpp */
