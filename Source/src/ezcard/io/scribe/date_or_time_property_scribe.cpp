//
//  date_or_time_property_scribe.cpp
//  OpenPGP
//
//  Created by Yanfeng Zhang on 6/12/17.
//  Copyright © 2017 Yanfeng Zhang. All rights reserved.
//

#include "date_or_time_property_scribe.hpp"

//
//public DateOrTimePropertyScribe(Class<T> clazz, String propertyName) {
//    super(clazz, propertyName);
//}
//
//@Override
//protected VCardDataType _defaultDataType(VCardVersion version) {
//    switch (version) {
//        case V2_1:
//        case V3_0:
//            return null;
//        case V4_0:
//            return VCardDataType.DATE_AND_OR_TIME;
//    }
//    return null;
//}
//
//@Override
//protected VCardDataType _dataType(T property, VCardVersion version) {
//    switch (version) {
//        case V2_1:
//        case V3_0:
//            return null;
//        case V4_0:
//            if (property.getText() != null) {
//                return VCardDataType.TEXT;
//            }
//            if (property.getDate() != null || property.getPartialDate() != null) {
//                return property.hasTime() ? VCardDataType.DATE_TIME : VCardDataType.DATE;
//            }
//            return VCardDataType.DATE_AND_OR_TIME;
//    }
//    return null;
//}
//
//@Override
//protected String _writeText(T property, WriteContext context) {
//    VCardVersion version = context.getVersion();
//    Date date = property.getDate();
//    if (date != null) {
//        boolean extended = (version == VCardVersion.V3_0);
//        return date(date).time(property.hasTime()).extended(extended).utc(false).write();
//    }
//    
//    if (version == VCardVersion.V4_0) {
//        String text = property.getText();
//        if (text != null) {
//            return VObjectPropertyValues.escape(text);
//        }
//        
//        PartialDate partialDate = property.getPartialDate();
//        if (partialDate != null) {
//            return partialDate.toISO8601(false);
//        }
//    }
//    
//    return "";
//}
//
//@Override
//protected T _parseText(String value, VCardDataType dataType, VCardParameters parameters, ParseContext context) {
//    value = VObjectPropertyValues.unescape(value);
//    if (context.getVersion() == VCardVersion.V4_0 && dataType == VCardDataType.TEXT) {
//        return newInstance(value);
//    }
//    
//    return parse(value, context);
//}
//
//@Override
//protected void _writeXml(T property, XCardElement parent) {
//    Date date = property.getDate();
//    if (date != null) {
//        boolean hasTime = property.hasTime();
//        String value = date(date).time(hasTime).extended(false).utc(false).write();
//        
//        VCardDataType dataType = hasTime ? VCardDataType.DATE_TIME : VCardDataType.DATE;
//        
//        parent.append(dataType, value);
//        return;
//    }
//    
//    PartialDate partialDate = property.getPartialDate();
//    if (partialDate != null) {
//        VCardDataType dataType;
//        if (partialDate.hasTimeComponent() && partialDate.hasDateComponent()) {
//            dataType = VCardDataType.DATE_TIME;
//        } else if (partialDate.hasTimeComponent()) {
//            dataType = VCardDataType.TIME;
//        } else if (partialDate.hasDateComponent()) {
//            dataType = VCardDataType.DATE;
//        } else {
//            dataType = VCardDataType.DATE_AND_OR_TIME;
//        }
//        
//        parent.append(dataType, partialDate.toISO8601(false));
//        return;
//    }
//    
//    String text = property.getText();
//    if (text != null) {
//        parent.append(VCardDataType.TEXT, text);
//        return;
//    }
//    
//    parent.append(VCardDataType.DATE_AND_OR_TIME, "");
//}
//
//@Override
//protected T _parseXml(XCardElement element, VCardParameters parameters, ParseContext context) {
//    String value = element.first(VCardDataType.DATE, VCardDataType.DATE_TIME, VCardDataType.DATE_AND_OR_TIME);
//    if (value != null) {
//        return parse(value, context);
//    }
//    
//    value = element.first(VCardDataType.TEXT);
//    if (value != null) {
//        return newInstance(value);
//    }
//    
//    throw missingXmlElements(VCardDataType.DATE, VCardDataType.DATE_TIME, VCardDataType.DATE_AND_OR_TIME, VCardDataType.TEXT);
//}
//
//@Override
//protected T _parseHtml(HCardElement element, ParseContext context) {
//    String value = null;
//    if ("time".equals(element.tagName())) {
//        String datetime = element.attr("datetime");
//        if (datetime.length() > 0) {
//            value = datetime;
//        }
//    }
//    if (value == null) {
//        value = element.value();
//    }
//    return parse(value, context);
//}
//
//@Override
//protected JCardValue _writeJson(T property) {
//    Date date = property.getDate();
//    if (date != null) {
//        boolean hasTime = property.hasTime();
//        String value = date(date).time(hasTime).extended(true).utc(false).write();
//        return JCardValue.single(value);
//    }
//    
//    PartialDate partialDate = property.getPartialDate();
//    if (partialDate != null) {
//        String value = partialDate.toISO8601(true);
//        return JCardValue.single(value);
//    }
//    
//    String text = property.getText();
//    if (text != null) {
//        return JCardValue.single(text);
//    }
//    
//    return JCardValue.single("");
//}
//
//@Override
//protected T _parseJson(JCardValue value, VCardDataType dataType, VCardParameters parameters, ParseContext context) {
//    String valueStr = value.asSingle();
//    if (dataType == VCardDataType.TEXT) {
//        return newInstance(valueStr);
//    }
//    
//    return parse(valueStr, context);
//}
//
//private T parse(String value, ParseContext context) {
//    try {
//        boolean hasTime = value.contains("T");
//        return newInstance(date(value), hasTime);
//    } catch (IllegalArgumentException e) {
//        if (context.getVersion() == VCardVersion.V2_1 || context.getVersion() == VCardVersion.V3_0) {
//            throw new CannotParseException(5);
//        }
//        
//        try {
//            return newInstance(PartialDate.parse(value));
//        } catch (IllegalArgumentException e2) {
//            context.addWarning(6);
//            return newInstance(value);
//        }
//    }
//}
//
//protected abstract T newInstance(String text);
//
//protected abstract T newInstance(Date date, boolean hasTime);
//
//protected abstract T newInstance(PartialDate partialDate);
