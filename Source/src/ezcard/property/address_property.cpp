//
//  address.cpp
//  OpenPGP
//
//  Created by Yanfeng Zhang on 1/10/17.
//  Copyright © 2017 Yanfeng Zhang. All rights reserved.
//

#include "address_property.hpp"



namespace ProtonMail {
    
    std::shared_ptr<IAddress> IAddress::create_instance(const std::string & type,
                                                        const std::string & street,
                                                        const std::string & extendstreet,
                                                        const std::string & locality,
                                                        const std::string & region,
                                                        const std::string & zip,
                                                        const std::string & country,
                                                        const std::string & pobox) {
        auto out = std::make_shared<ezvcard::Address>();
        out->addType(type);
        out->addStreetAddresses({street});
        out->addExtendedAddresses({extendstreet});
        out->addLocalities({locality});
        out->addRegions({region});
        out->addPostalCodes({zip});
        out->addCountries({country});
        out->addBoxes({pobox});
        return out;
    }
}


namespace ezvcard {
    
    
    const std::string Address::PROPERTYNAME = "ADR";
    const std::string Address::CLASSNAME = "Address";
    
    
    Address::Address() {
        
    }
    

    std::string Address::getAltId() {
        return _parameters->getAltId();
    }
    
    void Address::setAltId(const std::string& altId) {
        _parameters->setAltId(altId);
    }

    
    //
    //    public Address() {
    //        poBoxes = new ArrayList<String>(1);
    //        extendedAddresses = new ArrayList<String>(1);
    //        streetAddresses = new ArrayList<String>(1);
    //        localities = new ArrayList<String>(1);
    //        regions = new ArrayList<String>(1);
    //        postalCodes = new ArrayList<String>(1);
    //        countries = new ArrayList<String>(1);
    //    }
    //
    //    /**
    //     * Copy constructor.
    //     * @param original the property to make a copy of
    //     */
    //    public Address(Address original) {
    //        super(original);
    //        poBoxes = new ArrayList<String>(original.poBoxes);
    //        extendedAddresses = new ArrayList<String>(original.extendedAddresses);
    //        streetAddresses = new ArrayList<String>(original.streetAddresses);
    //        localities = new ArrayList<String>(original.localities);
    //        regions = new ArrayList<String>(original.regions);
    //        postalCodes = new ArrayList<String>(original.postalCodes);
    //        countries = new ArrayList<String>(original.countries);
    //    }
    //
    /**
     * Gets the P.O. (post office) box.
     * @return the P.O. box or null if not set
     */
    std::string Address::getPoBox() {
        return first(_poBoxes);
    }
    
    void Address::addBoxes(std::vector<std::string> boxes) {
        for(auto v : boxes) {
            _poBoxes.push_back(v);
        }
    }
    
    /**
     * Gets the list that holds the P.O. (post office) boxes that are assigned
     * to this address. An address is unlikely to have more than one, but it's
     * possible nonetheless.
     * @return the P.O. boxes (this list is mutable)
     */
    std::vector<std::string> Address::getPoBoxes() {
        return _poBoxes;
    }

    //    /**
    //     * Sets the P.O. (post office) box.
    //     * @param poBox the P.O. box or null to remove
    //     */
    //    public void setPoBox(String poBox) {
    //        set(poBoxes, poBox);
    //    }
    
    /**
     * Gets the extended address.
     * @return the extended address (e.g. "Suite 200") or null if not set
     */
    std::string Address::getExtendedAddress() {
        return first(_extendedAddresses);
    }
    
    void Address::addExtendedAddresses(std::vector<std::string> addresses) {
        for(auto v : addresses) {
            _extendedAddresses.push_back(v);
        }
    }
    
    /**
     * Gets the list that holds the extended addresses that are assigned to this
     * address. An address is unlikely to have more than one, but it's possible
     * nonetheless.
     * @return the extended addresses (this list is mutable)
     */
    std::vector<std::string> Address::getExtendedAddresses() {
        return _extendedAddresses;
    }
    
    
    //
    //    /**
    //     * Gets the extended address. Use this method when the ADR property of the
    //     * vCard you are parsing contains unescaped comma characters.
    //     * @return the extended address or null if not set
    //     */
    //    public String getExtendedAddressFull() {
    //        return getAddressFull(extendedAddresses);
    //    }
    //
    //    /**
    //     * Sets the extended address.
    //     * @param extendedAddress the extended address (e.g. "Suite 200") or null to
    //     * remove
    //     */
    //    public void setExtendedAddress(String extendedAddress) {
    //        set(extendedAddresses, extendedAddress);
    //    }
    
    /**
     * Gets the street address
     * @return the street address (e.g. "123 Main St")
     */
    std::string Address::getStreetAddress() {
        return first(_streetAddresses);
    }
    
    void Address::addStreetAddresses(std::vector<std::string> addresses){
        for(auto v : addresses) {
            _streetAddresses.push_back(v);
        }
    }
   
    
    /**
     * Gets the list that holds the street addresses that are assigned to this
     * address. An address is unlikely to have more than one, but it's possible
     * nonetheless.
     * @return the street addresses (this list is mutable)
     */
    std::vector<std::string> Address::getStreetAddresses() {
        return _streetAddresses;
    }
    
    //    /**
    //     * Gets the street address. Use this method when the ADR property of the
    //     * vCard you are parsing contains unescaped comma characters.
    //     * @return the street address or null if not set
    //     */
    //    public String getStreetAddressFull() {
    //        return getAddressFull(streetAddresses);
    //    }
    //
    //    /**
    //     * Sets the street address.
    //     * @param streetAddress the street address (e.g. "123 Main St") or null to
    //     * remove
    //     */
    //    public void setStreetAddress(String streetAddress) {
    //        set(streetAddresses, streetAddress);
    //    }
    
    /**
     * Gets the locality (city)
     * @return the locality (e.g. "Boston") or null if not set
     */
    std::string Address::getLocality() {
        return first(_localities);
    }
    
    void Address::addLocalities(std::vector<std::string> localities){
        for(auto v : localities) {
            _localities.push_back(v);
        }
    }

    /**
     * Gets the list that holds the localities that are assigned to this
     * address. An address is unlikely to have more than one, but it's possible
     * nonetheless.
     * @return the localities (this list is mutable)
     */
    std::vector<std::string> Address::getLocalities() {
        return _localities;
    }
    //
    //    /**
    //     * Sets the locality (city).
    //     * @param locality the locality or null to remove
    //     */
    //    public void setLocality(String locality) {
    //        set(localities, locality);
    //    }
    
    /**
     * Gets the region (state).
     * @return the region (e.g. "Texas") or null if not set
     */
    std::string Address::getRegion() {
        return first(_regions);
    }
    
    void Address::addRegions(std::vector<std::string> regions){
        for(auto v : regions) {
            _regions.push_back(v);
        }
    }

    /**
     * Gets the list that holds the regions that are assigned to this address.
     * An address is unlikely to have more than one, but it's possible
     * nonetheless.
     * @return the regions (this list is mutable)
     */
    std::vector<std::string> Address::getRegions() {
        return _regions;
    }
    
    //    /**
    //     * Sets the region (state).
    //     * @param region the region (e.g. "Texas") or null to remove
    //     */
    //    public void setRegion(String region) {
    //        set(regions, region);
    //    }
    
    /**
     * Gets the postal code (zip code).
     * @return the postal code (e.g. "90210") or null if not set
     */
    std::string Address::getPostalCode() {
        return first(_postalCodes);
    }
    
    void Address::addPostalCodes(std::vector<std::string> codes){
        for(auto v : codes) {
            _postalCodes.push_back(v);
        }
    }
    
    
    /**
     * Gets the list that holds the postal codes that are assigned to this
     * address. An address is unlikely to have more than one, but it's possible
     * nonetheless.
     * @return the postal codes (this list is mutable)
     */
    std::vector<std::string> Address::getPostalCodes() {
        return _postalCodes;
    }
    
    //    /**
    //     * Sets the postal code (zip code).
    //     * @param postalCode the postal code (e.g. "90210") or null to remove
    //     */
    //    public void setPostalCode(String postalCode) {
    //        set(postalCodes, postalCode);
    //    }
    
    /**
     * Gets the country.
     * @return the country (e.g. "USA") or null if not set
     */
    std::string Address::getCountry() {
        return first(_countries);
    }
    
    void Address::addCountries(std::vector<std::string> countries){
        for(auto v : countries) {
            _countries.push_back(v);
        }
    }
    /**
     * Gets the list that holds the countries that are assigned to this address.
     * An address is unlikely to have more than one, but it's possible
     * nonetheless.
     * @return the countries (this list is mutable)
     */
    std::vector<std::string> Address::getCountries() {
        return _countries;
    }
    
    //    /**
    //     * Sets the country.
    //     * @param country the country (e.g. "USA") or null to remove
    //     */
    //    public void setCountry(String country) {
    //        set(countries, country);
    //    }
    //
    //    /**
    //     * Gets the list that stores this property's address types (TYPE
    //     * parameters).
    //     * @return the address types (e.g. "HOME", "WORK") (this list is mutable)
    //     */
    //    public List<AddressType> getTypes() {
    //        return parameters.new TypeParameterList<AddressType>() {
    //            @Override
    //            protected AddressType _asObject(String value) {
    //                return AddressType.get(value);
    //            }
    //        };
    //    }
    std::vector<std::string> Address::getTypes() {
        return _parameters->getTypes();
    }
    
    void Address::addType(const std::string& type) {
        _parameters->addType(type);
    }

    //    @Override
    //    public String getLanguage() {
    //        return super.getLanguage();
    //    }
    //
    //    @Override
    //    public void setLanguage(String language) {
    //        super.setLanguage(language);
    //    }
    //
    //    /**
    //     * Gets the label of the address.
    //     * @return the label or null if not set
    //     */
    //    public String getLabel() {
    //        return parameters.getLabel();
    //    }
    //
    //    /**
    //     * Sets the label of the address.
    //     * @param label the label or null to remove
    //     */
    //    public void setLabel(String label) {
    //        parameters.setLabel(label);
    //    }
    //
    //    /**
    //     * <p>
    //     * Gets the global positioning coordinates that are associated with this
    //     * address.
    //     * </p>
    //     * <p>
    //     * <b>Supported versions:</b> {@code 4.0}
    //     * </p>
    //     * @return the geo URI or not if not found
    //     * @see VCardParameters#getGeo
    //     */
    //    public GeoUri getGeo() {
    //        return parameters.getGeo();
    //    }
    //
    //    /**
    //     * <p>
    //     * Sets the global positioning coordinates that are associated with this
    //     * address.
    //     * </p>
    //     * <p>
    //     * <b>Supported versions:</b> {@code 4.0}
    //     * </p>
    //     * @param uri the geo URI or null to remove
    //     * @see VCardParameters#setGeo
    //     */
    //    public void setGeo(GeoUri uri) {
    //        parameters.setGeo(uri);
    //    }
    //
    //    @Override
    //    public List<Pid> getPids() {
    //        return super.getPids();
    //    }
    //
    //    @Override
    //    public Integer getPref() {
    //        return super.getPref();
    //    }
    //
    //    @Override
    //    public void setPref(Integer pref) {
    //        super.setPref(pref);
    //    }
    //
    //    //@Override
    //    public String getAltId() {
    //        return parameters.getAltId();
    //    }
    //
    //    //@Override
    //    public void setAltId(String altId) {
    //        parameters.setAltId(altId);
    //    }
    //
    //    /**
    //     * Gets the timezone that's associated with this address.
    //     * <p>
    //     * <b>Supported versions:</b> {@code 4.0}
    //     * </p>
    //     * @return the timezone (e.g. "America/New_York") or null if not set
    //     */
    //    public String getTimezone() {
    //        return parameters.getTimezone();
    //    }
    //
    //    /**
    //     * Sets the timezone that's associated with this address.
    //     * <p>
    //     * <b>Supported versions:</b> {@code 4.0}
    //     * </p>
    //     * @param timezone the timezone (e.g. "America/New_York") or null to remove
    //     */
    //    public void setTimezone(String timezone) {
    //        parameters.setTimezone(timezone);
    //    }
    //
    //    @Override
    //    protected void _validate(List<ValidationWarning> warnings, VCardVersion version, VCard vcard) {
    //        for (AddressType type : getTypes()) {
    //            if (type == AddressType.PREF) {
    //                //ignore because it is converted to a PREF parameter for 4.0 vCards
    //                continue;
    //            }
    //
    //            if (!type.isSupportedBy(version)) {
    //                warnings.add(new ValidationWarning(9, type.getValue()));
    //            }
    //        }
    //
    //        /*
    //         * 2.1 does not allow multi-valued components.
    //         */
    //        if (version == VCardVersion.V2_1) {
    //            //@formatter:off
    //            if (poBoxes.size() > 1 ||
    //                extendedAddresses.size() > 1 ||
    //                streetAddresses.size() > 1 ||
    //                localities.size() > 1 ||
    //                regions.size() > 1 ||
    //                postalCodes.size() > 1 ||
    //                countries.size() > 1) {
    //                warnings.add(new ValidationWarning(35));
    //            }
    //            //@formatter:on
    //        }
    //    }
    //
    //    @Override
    //    protected Map<String, Object> toStringValues() {
    //        Map<String, Object> values = new LinkedHashMap<String, Object>();
    //        values.put("poBoxes", poBoxes);
    //        values.put("extendedAddresses", extendedAddresses);
    //        values.put("streetAddresses", streetAddresses);
    //        values.put("localities", localities);
    //        values.put("regions", regions);
    //        values.put("postalCodes", postalCodes);
    //        values.put("countries", countries);
    //        return values;
    //    }
    //
    //    @Override
    //    public Address copy() {
    //        return new Address(this);
    //    }
    //
    //    @Override
    //    public int hashCode() {
    //        final int prime = 31;
    //        int result = super.hashCode();
    //        result = prime * result + countries.hashCode();
    //        result = prime * result + extendedAddresses.hashCode();
    //        result = prime * result + localities.hashCode();
    //        result = prime * result + poBoxes.hashCode();
    //        result = prime * result + postalCodes.hashCode();
    //        result = prime * result + regions.hashCode();
    //        result = prime * result + streetAddresses.hashCode();
    //        return result;
    //    }
    //    
    //    @Override
    //    public boolean equals(Object obj) {
    //        if (this == obj) return true;
    //        if (!super.equals(obj)) return false;
    //        Address other = (Address) obj;
    //        if (!countries.equals(other.countries)) return false;
    //        if (!extendedAddresses.equals(other.extendedAddresses)) return false;
    //        if (!localities.equals(other.localities)) return false;
    //        if (!poBoxes.equals(other.poBoxes)) return false;
    //        if (!postalCodes.equals(other.postalCodes)) return false;
    //        if (!regions.equals(other.regions)) return false;
    //        if (!streetAddresses.equals(other.streetAddresses)) return false;
    //        return true;
    //    }
    //    
    //    private static String first(List<String> list) {
    //        return list.isEmpty() ? null : list.get(0);
    //    }
    //    
    //    private static void set(List<String> list, String value) {
    //        list.clear();
    //        if (value != null) {
    //            list.add(value);
    //        }
    //    }
    //    
//        private static String getAddressFull(List<String> list) {
//            return list.isEmpty() ? null : StringUtils.join(list, ",");
//        }
    //}
}
