//
//  address_scribe.hpp
//  OpenPGP
//
//  Created by Yanfeng Zhang on 1/11/17.
//  Copyright © 2017 Yanfeng Zhang. All rights reserved.
//

#ifndef address_scribe_hpp
#define address_scribe_hpp

#include <stdio.h>

#include "vcard_property_scribe.hpp"
#include "vobject_property_values.hpp"
#include "address_property.hpp"
#include <ezvcard/util/string_util.hpp>


namespace ezvcard {
    

/**
 * Marshals {@link Address} properties.
 * @author Michael Angstadt
 */
class AddressScribe : public VCardPropertyScribeWrapper<Address> {
public:
    AddressScribe() : VCardPropertyScribeWrapper(Address::PROPERTYNAME) {
        
    }
    
protected:

    VCardDataType::Ptr _defaultDataType(const VCardVersion::Ptr& version) {
        return VCardDataType::TEXT;
    }
    
    void _prepareParameters(const Address::Ptr& property, const VCardParameters::Ptr& copy, const VCardVersion::Ptr& version, const VCard::Ptr& vcard) {
        handlePrefParam(property, copy, version, vcard);
        
        if (version == VCardVersion::V2_1() || version == VCardVersion::V3_0()) {
            /*
             * Remove the LABEL parameter. By the time this line of code is
             * reached, VCardWriter will have created a LABEL property from this
             * property's LABEL parameter
             */
            copy->setLabel("");
        }
    }
    
    std::string _writeText(const Address::Ptr& property, const WriteContext::Ptr& context) {
        /*
         * StructuredValueBuilder cannot be used with 2.1 because it escapes
         * comma characters. For example, if someone's street address is
         * "Foo,bar Lane", the comma character must NOT be escaped when written
         * to a 2.1 vCard.
         *
         * The reason commas are not escaped in 2.1 is because 2.1 does not
         * allow multi-valued components like 3.0 and 4.0 do (for example,
         * multiple street addresses).
         *
         * If an Address object has multi-valued components, and it is being
         * written to a 2.1 vCard, then ez-vcard will comma-delimit them to
         * prevent data loss. But this is not part of the 2.1 syntax.
         */
        if (context->getVersion() == VCardVersion::V2_1()) {
            SemiStructuredValueBuilder builder;
            builder.append(join(property->getPoBoxes(), ","));
            builder.append(join(property->getExtendedAddresses(), ","));
            builder.append(join(property->getStreetAddresses(), ","));
            builder.append(join(property->getLocalities(), ","));
            builder.append(join(property->getRegions(), ","));
            builder.append(join(property->getPostalCodes(), ","));
            builder.append(join(property->getCountries(), ","));
            return builder.build(false, context->isIncludeTrailingSemicolons());
        } else {
            StructuredValueBuilder builder;
            builder.append(property->getPoBoxes());
            builder.append(property->getExtendedAddresses());
            builder.append(property->getStreetAddresses());
            builder.append(property->getLocalities());
            builder.append(property->getRegions());
            builder.append(property->getPostalCodes());
            builder.append(property->getCountries());
            return builder.build(context->isIncludeTrailingSemicolons());
        }
    }
    
    Address::Ptr _parseText(const std::string& value,
                                const VCardDataType::Ptr& dataType,
                                const VCardVersion::Ptr& version,
                                const VCardParameters::Ptr& parameters,
                                std::list<std::string> warnings) {
        if (version == VCardVersion::V2_1()) {
            /*
             * 2.1 does not recognize multi-valued components.
             */
            SemiStructuredValueIterator it(value);
            return parseSemiStructuredValue(it);
        } else {
            StructuredValueIterator it(value);
            return parseStructuredValue(it);
        }
    }
    
    std::string _className() {
        return "AddressScribe";
    }

    
    
private:
    Address::Ptr parseStructuredValue(StructuredValueIterator& it) {
        Address::Ptr property = std::make_shared<Address>();
        property->addBoxes(it.nextComponent());
        property->addExtendedAddresses(it.nextComponent());
        property->addStreetAddresses(it.nextComponent());
        property->addLocalities(it.nextComponent());
        property->addRegions(it.nextComponent());
        property->addPostalCodes(it.nextComponent());
        property->addCountries(it.nextComponent());
        return property;
    }
    
    Address::Ptr parseSemiStructuredValue(SemiStructuredValueIterator& it) {
        Address::Ptr property = std::make_shared<Address>();
        
        std::string next = it.next();
        if (next != "") {
            property->addBoxes({next});
        }
        
        next = it.next();
        if (next != "") {
            property->addExtendedAddresses({next});
        }
        
        next = it.next();
        if (next != "") {
            property->addStreetAddresses({next});
        }
        
        next = it.next();
        if (next != "") {
            property->addLocalities({next});
        }
        
        next = it.next();
        if (next != "") {
            property->addRegions({next});
        }
        
        next = it.next();
        if (next != "") {
            property->addPostalCodes({next});
        }
        
        next = it.next();
        if (next != "") {
            property->addCountries({next});
        }
        
        return property;
    }
    
    
//    protected void _writeXml(Address property, XCardElement parent);
//    protected Address _parseXml(XCardElement element, VCardParameters parameters, ParseContext context);
//    private List<String> sanitizeXml(XCardElement element, String name);
//    protected Address _parseHtml(HCardElement element, ParseContext context);
//    protected JCardValue _writeJson(Address property);
//    protected Address _parseJson(JCardValue value, VCardDataType dataType, VCardParameters parameters, ParseContext context);
};
    
}

#endif /* address_scribe_hpp */
