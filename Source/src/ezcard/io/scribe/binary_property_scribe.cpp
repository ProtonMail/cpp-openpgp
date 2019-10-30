//
//  binary_property_scribe.cpp
//  OpenPGP
//
//  Created by Yanfeng Zhang on 5/19/17.
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

#include "binary_property_scribe.hpp"



//    public BinaryPropertyScribe(Class<T> clazz, String propertyName) {
//        super(clazz, propertyName);
//    }


//    @Override
//    protected void _prepareParameters(T property, VCardParameters copy, VCardVersion version, VCard vcard) {
//        MediaTypeParameter contentType = property.getContentType();
//        if (contentType == null) {
//            contentType = new MediaTypeParameter(null, null, null);
//        }
//        
//        if (property.getUrl() != null) {
//            copy.setEncoding(null);
//            
//            switch (version) {
//                case V2_1:
//                    copy.setType(contentType.getValue());
//                    copy.setMediaType(null);
//                    break;
//                case V3_0:
//                    copy.setType(contentType.getValue());
//                    copy.setMediaType(null);
//                    break;
//                case V4_0:
//                    copy.setMediaType(contentType.getMediaType());
//                    break;
//            }
//            
//            return;
//        }
//        
//        if (property.getData() != null) {
//            copy.setMediaType(null);
//            
//            switch (version) {
//                case V2_1:
//                    copy.setEncoding(Encoding.BASE64);
//                    copy.setType(contentType.getValue());
//                    break;
//                case V3_0:
//                    copy.setEncoding(Encoding.B);
//                    copy.setType(contentType.getValue());
//                    break;
//                case V4_0:
//                    copy.setEncoding(null);
//                    //don't null out TYPE, it could be set to "home", "work", etc
//                    break;
//            }
//            
//            return;
//        }
//    }
//    
//    @Override
//    protected String _writeText(T property, WriteContext context) {
//        return write(property, context.getVersion());
//    }
//    
//    @Override
//    protected T _parseText(String value, VCardDataType dataType, VCardParameters parameters, ParseContext context) {
//        value = VObjectPropertyValues.unescape(value);
//        return parse(value, dataType, parameters, context.getVersion());
//    }
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
//    
//    /**
//     * Called if the unmarshalling code cannot determine how to unmarshal the
//     * value.
//     * @param value the value
//     * @param version the version of the vCard
//     * @param contentType the content type of the resource of null if unknown
//     * @return the unmarshalled property object or null if it cannot be
//     * unmarshalled
//     */
//    protected T cannotUnmarshalValue(String value, VCardVersion version, U contentType) {
//        switch (version) {
//            case V2_1:
//            case V3_0:
//                if (value.startsWith("http")) {
//                    return _newInstance(value, contentType);
//                }
//                return _newInstance(Base64.decodeBase64(value), contentType);
//            case V4_0:
//                return _newInstance(value, contentType);
//        }
//        return null;
//    }
//    
//    /**
//     * Builds a {@link MediaTypeParameter} object based on the information in
//     * the MEDIATYPE parameter or data URI of 4.0 vCards.
//     * @param mediaType the media type string (e.g. "image/jpeg")
//     * @return the media type object
//     */
//    protected abstract U _mediaTypeFromMediaTypeParameter(String mediaType);
//    
//    /**
//     * Builds a {@link MediaTypeParameter} object based on the value of the TYPE
//     * parameter in 2.1/3.0 vCards.
//     * @param type the TYPE value (e.g. "JPEG")
//     * @return the media type object
//     */
//    protected abstract U _mediaTypeFromTypeParameter(String type);
//    
//    /**
//     * Searches for a {@link MediaTypeParameter} object, given a file extension.
//     * @param extension the file extension (e.g. "jpg")
//     * @return the media type object or null if not found
//     */
//    protected abstract U _mediaTypeFromFileExtension(String extension);
//    
//    protected abstract T _newInstance(String uri, U contentType);
//    
//    protected abstract T _newInstance(byte data[], U contentType);
//    
//    private U parseContentType(String value, VCardParameters parameters, VCardVersion version) {
//        switch (version) {
//            case V2_1:
//            case V3_0:
//                //get the TYPE parameter
//                String type = parameters.getType();
//                if (type != null) {
//                    return _mediaTypeFromTypeParameter(type);
//                }
//                break;
//            case V4_0:
//                //get the MEDIATYPE parameter
//                String mediaType = parameters.getMediaType();
//                if (mediaType != null) {
//                    return _mediaTypeFromMediaTypeParameter(mediaType);
//                }
//                break;
//        }
//        
//        //look for a file extension in the property value
//        String extension = getFileExtension(value);
//        return (extension == null) ? null : _mediaTypeFromFileExtension(extension);
//    }
//    
//    private T parse(String value, VCardDataType dataType, VCardParameters parameters, VCardVersion version) {
//        U contentType = parseContentType(value, parameters, version);
//        
//        switch (version) {
//            case V2_1:
//            case V3_0:
//                //parse as URL
//                if (dataType == VCardDataType.URL || dataType == VCardDataType.URI) {
//                    return _newInstance(value, contentType);
//                }
//                
//                //parse as binary
//                Encoding encodingSubType = parameters.getEncoding();
//                if (encodingSubType == Encoding.BASE64 || encodingSubType == Encoding.B) {
//                    return _newInstance(Base64.decodeBase64(value), contentType);
//                }
//                
//                break;
//            case V4_0:
//                try {
//                    //parse as data URI
//                    DataUri uri = DataUri.parse(value);
//                    contentType = _mediaTypeFromMediaTypeParameter(uri.getContentType());
//                    return _newInstance(uri.getData(), contentType);
//                } catch (IllegalArgumentException e) {
//                    //not a data URI
//                }
//                break;
//        }
//        
//        return cannotUnmarshalValue(value, version, contentType);
//    }
//    
//    private String write(T property, VCardVersion version) {
//        String url = property.getUrl();
//        if (url != null) {
//            return url;
//        }
//        
//        byte data[] = property.getData();
//        if (data != null) {
//            switch (version) {
//                case V2_1:
//                case V3_0:
//                    return Base64.encodeBase64String(data);
//                case V4_0:
//                    U contentType = property.getContentType();
//                    String mediaType = (contentType == null || contentType.getMediaType() == null) ? "application/octet-stream" : contentType.getMediaType();
//                    return new DataUri(mediaType, data).toString();
//            }
//        }
//        
//        return "";
//    }
//    
//    /**
//     * Gets the file extension from a URL.
//     * @param url the URL
//     * @return the file extension (e.g. "jpg") or null if not found
//     */
//    protected static String getFileExtension(String url) {
//        int dotPos = url.lastIndexOf('.');
//        if (dotPos < 0 || dotPos == url.length() - 1) {
//            return null;
//        }
//        
//        int slashPos = url.lastIndexOf('/');
//        if (slashPos > dotPos) {
//            return null;
//        }
//        
//        return url.substring(dotPos + 1);
//    }
//}
