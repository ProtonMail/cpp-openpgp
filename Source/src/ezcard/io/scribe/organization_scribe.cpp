//
//  organization_scribe.cpp
//  OpenPGP
//
//  Created by Yanfeng Zhang on 6/2/17.
//  Copyright © 2017 Yanfeng Zhang. All rights reserved.
//

#include "organization_scribe.hpp"



//
//
///**
// * Marshals {@link Organization} properties.
// * @author Michael Angstadt
// */
//class OrganizationScribe : public VCardPropertyScribe {
//public:
//    OrganizationScribe() : VCardPropertyScribe(Organization::PROPERTYNAME) {
//        
//    }
//    
//    @Override
//    protected VCardDataType _defaultDataType(VCardVersion version) {
//        return VCardDataType.TEXT;
//    }
//    
//    @Override
//    protected String _writeText(Organization property, WriteContext context) {
//        boolean escapeCommas = (context.getVersion() != VCardVersion.V2_1);
//        return VObjectPropertyValues.writeSemiStructured(property.getValues(), escapeCommas, context.isIncludeTrailingSemicolons());
//    }
//    
//    @Override
//    protected Organization _parseText(String value, VCardDataType dataType, VCardParameters parameters, ParseContext context) {
//        Organization property = new Organization();
//        
//        List<String> values = VObjectPropertyValues.parseSemiStructured(value);
//        property.getValues().addAll(values);
//        
//        return property;
//    }
//    
//    @Override
//    protected void _writeXml(Organization property, XCardElement parent) {
//        parent.append(VCardDataType.TEXT.getName().toLowerCase(), property.getValues());
//    }
//    
//    @Override
//    protected Organization _parseXml(XCardElement element, VCardParameters parameters, ParseContext context) {
//        List<String> values = element.all(VCardDataType.TEXT);
//        if (!values.isEmpty()) {
//            Organization property = new Organization();
//            property.getValues().addAll(values);
//            return property;
//        }
//        
//        throw missingXmlElements(VCardDataType.TEXT);
//    }
//    
//    @Override
//    protected Organization _parseHtml(HCardElement element, ParseContext context) {
//        Organization property = new Organization();
//        
//        String orgName = element.firstValue("organization-name");
//        if (orgName != null) {
//            property.getValues().add(orgName);
//        }
//        
//        String orgUnit = element.firstValue("organization-unit");
//        if (orgUnit != null) {
//            property.getValues().add(orgUnit);
//        }
//        
//        if (property.getValues().isEmpty()) {
//            String value = element.value();
//            if (value.length() > 0) {
//                property.getValues().add(value);
//            }
//        }
//        
//        return property;
//    }
//    
//    @Override
//    protected JCardValue _writeJson(Organization property) {
//        List<String> values = property.getValues();
//        if (values.isEmpty()) {
//            return JCardValue.single("");
//        }
//        
//        if (values.size() == 1) {
//            return JCardValue.single(values.get(0));
//        }
//        
//        return JCardValue.structured(values.toArray(new Object[0]));
//    }
//    
//    @Override
//    protected Organization _parseJson(JCardValue value, VCardDataType dataType, VCardParameters parameters, ParseContext context) {
//        Organization property = new Organization();
//        
//        StructuredValueIterator it = new StructuredValueIterator(value.asStructured());
//        while (it.hasNext()) {
//            String next = it.nextValue();
//            if (next != null) {
//                property.getValues().add(next);
//            }
//        }
//        
//        return property;
//    }
//}
