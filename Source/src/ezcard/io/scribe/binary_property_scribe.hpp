//
//  binary_property_scribe.hpp
//  OpenPGP
//
//  Created by Yanfeng Zhang on 5/19/17.
//  Copyright © 2017 Yanfeng Zhang. All rights reserved.
//

#ifndef binary_property_scribe_hpp
#define binary_property_scribe_hpp

#include <string>
#include "vcard_property_scribe.hpp"
#include "vobject_property_values.hpp"
#include "base64.h"
#include "data_uri.hpp"

namespace ezvcard {
    
    
    /**
     * Marshals properties that have binary data.
     * @author Michael Angstadt
     * @param <T> the property class
     * @param <U> the media type class
     */
    template <class T, class U>
    class BinaryPropertyScribe : public VCardPropertyScribeWrapper<T> {
        
        static_assert(std::is_base_of<MediaTypeParameter, U>::value, "BinaryPropertyScribe<T, U>: U must be extent of MediaTypeParameter type :-(");
        static_assert(std::is_base_of<BinaryProperty<U>, T>::value, "BinaryPropertyScribe<T, U>: T must be extent of BinaryProperty<U> type :-(");
        
        
    public:
        BinaryPropertyScribe(const std::string& propertyName) : VCardPropertyScribeWrapper<T>(propertyName) {
            
        }
        
    protected:
        
        /**
         * Builds a {@link MediaTypeParameter} object based on the information in
         * the MEDIATYPE parameter or data URI of 4.0 vCards.
         * @param mediaType the media type string (e.g. "image/jpeg")
         * @return the media type object
         */
        virtual std::shared_ptr<U> _mediaTypeFromMediaTypeParameter(const std::string& mediaType) = 0;
        
        /**
         * Builds a {@link MediaTypeParameter} object based on the value of the TYPE
         * parameter in 2.1/3.0 vCards.
         * @param type the TYPE value (e.g. "JPEG")
         * @return the media type object
         */
        virtual std::shared_ptr<U> _mediaTypeFromTypeParameter(const std::string& type) = 0;
        
        /**
         * Searches for a {@link MediaTypeParameter} object, given a file extension.
         * @param extension the file extension (e.g. "jpg")
         * @return the media type object or null if not found
         */
        virtual std::shared_ptr<U>_mediaTypeFromFileExtension(const std::string& extension) = 0;
        
        
        virtual std::shared_ptr<T> _newInstance(const std::string& uri_or_data, const std::shared_ptr<U>& contentType, bool isBinary) = 0;
//        virtual std::shared_ptr<T> _newInstance(byte data[], const std::shared_ptr<U>& contentType) = 0;
        
        /**
         * Gets the file extension from a URL.
         * @param url the URL
         * @return the file extension (e.g. "jpg") or null if not found
         */
        static std::string getFileExtension(const std::string& url) {
            auto dotPos = url.find_last_of(".");
            if (dotPos == std::string::npos || dotPos == url.size() - 1) {
                return "";
            }
            auto slashPos = url.find_last_of("/");
            if (slashPos > dotPos) {
                return "";
            }
            
            return url.substr(dotPos + 1);
        }
        
    protected:
        
        VCardDataType::Ptr _defaultDataType(const VCardVersion::Ptr& version) {
            if (version == VCardVersion::V2_1()) {
                return nullptr;
            }
            
            if (version == VCardVersion::V3_0()) {
                return nullptr;
            }
            
            if (version == VCardVersion::V4_0()) {
                return VCardDataType::URI;
            }
            
            return nullptr;
        }
        
        
        void _prepareParameters(const std::shared_ptr<T>& property, const VCardParameters::Ptr& copy, const VCardVersion::Ptr& version, const VCard::Ptr& vcard) {
            MediaTypeParameter::Ptr contentType = property->getContentType();
            if (contentType == nullptr) {
                contentType = std::make_shared<MediaTypeParameter>("", "", "");
            }
            
            if (!property->getUrl().empty()) {
                copy->setEncoding(nullptr);
                
                if (version == VCardVersion::V2_1()) {
                    copy->setType(contentType->getValue());
                    //copy.setMediaType(null);
                }
                
                if (version == VCardVersion::V3_0()) {
                    copy->setType(contentType->getValue());
                    //copy.setMediaType(null);
                }
                
                if (version == VCardVersion::V4_0()) {
                    copy->setMediaType(contentType->getMediaType());
                }
                return;
            }
            
            if (!property->getData().empty()) {
                //                copy.setMediaType(null);
                
                if (version == VCardVersion::V2_1()) {
                    copy->setEncoding(Encoding::BASE64);
                    copy->setType(contentType->getValue());
                }
                
                if (version == VCardVersion::V3_0()) {
                    copy->setEncoding(Encoding::B);
                    copy->setType(contentType->getValue());
                }
                
                if (version == VCardVersion::V4_0()) {
                    //copy.setEncoding(null);
                    ////don't null out TYPE, it could be set to "home", "work", etc
                }
                return;
            }
        }
        
        VCardDataType::Ptr _dataType(const std::shared_ptr<T>& property, const VCardVersion::Ptr& version) {
            if (!property->getUrl().empty()) {
                if (version == VCardVersion::V2_1())
                    return VCardDataType::URL;
                
                if (version == VCardVersion::V3_0() ||
                    version == VCardVersion::V4_0())
                    return VCardDataType::URI;
            }
            
            if (!property->getData().empty()) {
                if (version == VCardVersion::V2_1() ||
                    version == VCardVersion::V3_0())
                    return nullptr;
                
                if (version == VCardVersion::V4_0())
                    return VCardDataType::URI;
            }
            return _defaultDataType(version);
        }
        
        std::string _writeText(const std::shared_ptr<T> & property, const WriteContext::Ptr& context) {
            return write(property, context->getVersion());
        }
        
        std::shared_ptr<T> _parseText(const std::string& value,
                                      const VCardDataType::Ptr& dataType,
                                      const VCardVersion::Ptr& version,
                                      const VCardParameters::Ptr& parameters,
                                      std::list<std::string> warnings) {
            
            auto escapedValue = VObjectPropertyValues::unescape(value);
            return parse(escapedValue, dataType, parameters, version);
        }
    private:
        std::string write(std::shared_ptr<T> property, VCardVersion::Ptr version) {
            auto url = property->getUrl();
            if (!url.empty()) {
                return url;
            }
            
            auto data = property->getData();
            if (!data.empty()) {
                if (version == VCardVersion::V2_1() ||
                    version == VCardVersion::V3_0()) {
                    return base64_encode(data);
                } else if (version == VCardVersion::V4_0()) {
                    auto contentType = property->getContentType();
                    auto mediaType = (contentType == nullptr || contentType->getMediaType() == "") ? "application/octet-stream" : contentType->getMediaType();
                    return std::make_shared<DataUri>(mediaType, data, false)->toString();
                }
            }
            return "";
        }
        
        std::shared_ptr<T> parse(std::string value, VCardDataType::Ptr dataType, VCardParameters::Ptr parameters, VCardVersion::Ptr version) {
            auto contentType = parseContentType(value, parameters, version);
            
            if (version == VCardVersion::V2_1() || version == VCardVersion::V3_0()) {
                //parse as URL
                if (dataType == VCardDataType::URL || dataType == VCardDataType::URI) {
                    return _newInstance(value, contentType, false);
                }
                
                //parse as binary
                auto encodingSubType = parameters->getEncoding();
                if (encodingSubType == Encoding::BASE64 || encodingSubType == Encoding::B) {
                    return _newInstance(base64_decode(value), contentType, true);
                }
            } else if (version == VCardVersion::V4_0()) {
 //               try {
                    //parse as data URI
                auto uri = DataUri::parse(value);
                contentType = _mediaTypeFromMediaTypeParameter(uri->getContentType());
                return _newInstance(uri->getData(), contentType, true);
//                } catch (IllegalArgumentException e) {
//                    //not a data URI
//                }
            }
        
            return cannotUnmarshalValue(value, version, contentType);
        }
        
        std::shared_ptr<U> parseContentType(const std::string& value, const VCardParameters::Ptr& parameters, const VCardVersion::Ptr& version) {
            if (version == VCardVersion::V2_1() || version == VCardVersion::V3_0()) {
                //get the TYPE parameter
                std::string type = parameters->getType();
                if (type != "") {
                    return _mediaTypeFromTypeParameter(type);
                }
            } else if (version == VCardVersion::V4_0()) {
                //get the MEDIATYPE parameter
                std::string mediaType = parameters->getMediaType();
                if (mediaType != "") {
                    return _mediaTypeFromMediaTypeParameter(mediaType);
                }
            }
            //look for a file extension in the property value
            std::string extension = getFileExtension(value);
            return extension.empty() ? nullptr : _mediaTypeFromFileExtension(extension);
        }
        
        bool startswith(const std::string& prefix, const std::string& text) {
            if (prefix.length() > 0 && text.length() > prefix.length()) {
                int i = 0;
                while (i < prefix.length()) {
                    if (text[i] != prefix[i]) return false;
                    i++;
                }
                return true;
            } else return false;
        }
        
        /**
         * Called if the unmarshalling code cannot determine how to unmarshal the
         * value.
         * @param value the value
         * @param version the version of the vCard
         * @param contentType the content type of the resource of null if unknown
         * @return the unmarshalled property object or null if it cannot be
         * unmarshalled
         */
        std::shared_ptr<T> cannotUnmarshalValue(const std::string& value, const VCardVersion::Ptr& version, const std::shared_ptr<U>& contentType) {
            
            if (version == VCardVersion::V2_1() || version == VCardVersion::V3_0()) {
                if (startswith("http", value)) {
                    return _newInstance(value, contentType, false);
                }
                return _newInstance(base64_decode(value), contentType, true);
            } else if (version == VCardVersion::V4_0()) {
                return _newInstance(value, contentType, false);
            }
            return nullptr;
        }
        
        //
        //    @Override
        //    protected void _writeXml(T property, XCardElement parent) {
        //        parent.append(VCardDataType.URI, write(property, parent.version()));
        //    }
        //
        //    @Override
        //    protected T _parseXml(XCardElement element, VCardParameters parameters, ParseContext context) {
        //        String value = element.first(VCardDataType.URI);
        //        if (value != null) {
        //            return parse(value, VCardDataType.URI, parameters, element.version());
        //        }
        //
        //        throw missingXmlElements(VCardDataType.URI);
        //    }
        //
        //    @Override
        //    protected T _parseHtml(HCardElement element, ParseContext context) {
        //        String elementName = element.tagName();
        //        if (!"object".equals(elementName)) {
        //            throw new CannotParseException(1, elementName);
        //        }
        //
        //        String data = element.absUrl("data");
        //        if (data.length() == 0) {
        //            throw new CannotParseException(2);
        //        }
        //
        //        try {
        //            DataUri uri = DataUri.parse(data);
        //            U mediaType = _mediaTypeFromMediaTypeParameter(uri.getContentType());
        //
        //            return _newInstance(uri.getData(), mediaType);
        //        } catch (IllegalArgumentException e) {
        //            //not a data URI
        //            U mediaType = null;
        //            String type = element.attr("type");
        //            if (type.length() > 0) {
        //                mediaType = _mediaTypeFromMediaTypeParameter(type);
        //            } else {
        //                String extension = getFileExtension(data);
        //                mediaType = (extension == null) ? null : _mediaTypeFromFileExtension(extension);
        //            }
        //
        //            return _newInstance(data, mediaType);
        //        }
        //    }
        //
        //    @Override
        //    protected JCardValue _writeJson(T property) {
        //        return JCardValue.single(write(property, VCardVersion.V4_0));
        //    }
        //
        //    @Override
        //    protected T _parseJson(JCardValue value, VCardDataType dataType, VCardParameters parameters, ParseContext context) {
        //        String valueStr = value.asSingle();
        //        return parse(valueStr, dataType, parameters, VCardVersion.V4_0);
        //    }

        

    };
    
}

#endif /* binary_property_scribe_hpp */
