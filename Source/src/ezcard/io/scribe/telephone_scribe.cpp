//
//  telephone_scribe.cpp
//  OpenPGP
//
//  Created by Yanfeng Zhang on 6/3/17.
//  Copyright © 2017 Yanfeng Zhang. All rights reserved.
//

#include "telephone_scribe.hpp"

//
//
//
///**
// * Marshals {@link Telephone} properties.
// * @author Michael Angstadt
// */
//public class TelephoneScribe extends VCardPropertyScribe<Telephone> {
//    public TelephoneScribe() {
//        super(Telephone.class, "TEL");
//    }
//    
//    @Override
//    protected VCardDataType _defaultDataType(VCardVersion version) {
//        return VCardDataType.TEXT;
//    }
//    
//    @Override
//    protected VCardDataType _dataType(Telephone property, VCardVersion version) {
//        if (version == VCardVersion.V4_0) {
//            if (property.getText() != null) {
//                return VCardDataType.TEXT;
//            }
//            if (property.getUri() != null) {
//                return VCardDataType.URI;
//            }
//        }
//        
//        return VCardDataType.TEXT;
//    }
//    
//    @Override
//    protected void _prepareParameters(Telephone property, VCardParameters copy, VCardVersion version, VCard vcard) {
//        handlePrefParam(property, copy, version, vcard);
//    }
//    
//    @Override
//    protected String _writeText(Telephone property, WriteContext context) {
//        String text = property.getText();
//        if (text != null) {
//            return escape(text, context);
//        }
//        
//        TelUri uri = property.getUri();
//        if (uri != null) {
//            if (context.getVersion() == VCardVersion.V4_0) {
//                return uri.toString();
//            }
//            
//            String ext = uri.getExtension();
//            String value = (ext == null) ? uri.getNumber() : uri.getNumber() + " x" + ext;
//            return escape(value, context);
//        }
//        
//        return "";
//    }
//    
//    @Override
//    protected Telephone _parseText(String value, VCardDataType dataType, VCardParameters parameters, ParseContext context) {
//        value = VObjectPropertyValues.unescape(value);
//        return parse(value, dataType, context);
//    }
//    
//    @Override
//    protected void _writeXml(Telephone property, XCardElement parent) {
//        String text = property.getText();
//        if (text != null) {
//            parent.append(VCardDataType.TEXT, text);
//            return;
//        }
//        
//        TelUri uri = property.getUri();
//        if (uri != null) {
//            parent.append(VCardDataType.URI, uri.toString());
//            return;
//        }
//        
//        parent.append(VCardDataType.TEXT, "");
//    }
//    
//    @Override
//    protected Telephone _parseXml(XCardElement element, VCardParameters parameters, ParseContext context) {
//        String text = element.first(VCardDataType.TEXT);
//        if (text != null) {
//            return new Telephone(text);
//        }
//        
//        String uri = element.first(VCardDataType.URI);
//        if (uri != null) {
//            try {
//                return new Telephone(TelUri.parse(uri));
//            } catch (IllegalArgumentException e) {
//                context.addWarning(18);
//                return new Telephone(uri);
//            }
//        }
//        
//        throw missingXmlElements(VCardDataType.TEXT, VCardDataType.URI);
//    }
//    
//    @Override
//    protected Telephone _parseHtml(HCardElement element, ParseContext context) {
//        Telephone property;
//        String href = element.attr("href");
//        try {
//            property = new Telephone(TelUri.parse(href));
//        } catch (IllegalArgumentException e) {
//            //not a tel URI
//            property = new Telephone(element.value());
//        }
//        
//        List<String> types = element.types();
//        property.getParameters().putAll(VCardParameters.TYPE, types);
//        
//        return property;
//    }
//    
//    @Override
//    protected JCardValue _writeJson(Telephone property) {
//        String text = property.getText();
//        if (text != null) {
//            return JCardValue.single(text);
//        }
//        
//        TelUri uri = property.getUri();
//        if (uri != null) {
//            return JCardValue.single(uri.toString());
//        }
//        
//        return JCardValue.single("");
//    }
//    
//    @Override
//    protected Telephone _parseJson(JCardValue value, VCardDataType dataType, VCardParameters parameters, ParseContext context) {
//        String valueStr = value.asSingle();
//        return parse(valueStr, dataType, context);
//    }
//    
//    private Telephone parse(String value, VCardDataType dataType, ParseContext context) {
//        try {
//            return new Telephone(TelUri.parse(value));
//        } catch (IllegalArgumentException e) {
//            if (dataType == VCardDataType.URI) {
//                context.addWarning(18);
//            }
//        }
//        
//        return new Telephone(value);
//    }
//}
