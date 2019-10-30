//
//  address.hpp
//  OpenPGP
//
//  Created by Yanfeng Zhang on 1/10/17.
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


#ifndef address_hpp
#define address_hpp

#include <stdio.h>
#include <string>
#include <list>

#include "text_property.hpp"
#include "has_alt_Id.hpp"
#include <bridge/i_address.hpp>

using namespace ProtonMail;

namespace ezvcard {

class Address : public VCardProperty, public IAddress, HasAltId {
public:
    typedef std::shared_ptr<Address> Ptr;
    const static std::string PROPERTYNAME;
    const static std::string CLASSNAME;
    
private:
    std::vector<std::string> _poBoxes;
    std::vector<std::string> _extendedAddresses;
    std::vector<std::string> _streetAddresses;
    std::vector<std::string> _localities;
    std::vector<std::string> _regions;
    std::vector<std::string> _postalCodes;
    std::vector<std::string> _countries;
    
public:
    Address();
//    public Address(Address original);

    std::string getPoBox();
    void addBoxes(std::vector<std::string> boxes);
    std::vector<std::string> getPoBoxes() final;
    //    public void setPoBox(String poBox) {
    
    std::string getExtendedAddress();
    std::vector<std::string> getExtendedAddresses();
    void addExtendedAddresses(std::vector<std::string> addresses);
    std::string getExtendedAddressFull();
//    public void setExtendedAddress(String extendedAddress) {
    
    std::string getStreetAddress();
    void addStreetAddresses(std::vector<std::string> addresses);
    std::vector<std::string> getStreetAddresses();
//    public String getStreetAddressFull() {
//    public void setStreetAddress(String streetAddress) {
    
    std::string getLocality();
    void addLocalities(std::vector<std::string> localities);
    std::vector<std::string> getLocalities();
//    public void setLocality(String locality) {
    
    std::string getRegion();
    void addRegions(std::vector<std::string> regions);
    std::vector<std::string> getRegions();
//    public void setRegion(String region) {
    std::string getPostalCode();
    void addPostalCodes(std::vector<std::string> codes);
    std::vector<std::string> getPostalCodes();
    
//    public void setPostalCode(String postalCode) {
    std::string getCountry();
    void addCountries(std::vector<std::string> countries);
    std::vector<std::string> getCountries();
//    public void setCountry(String country) {
    std::vector<std::string> getTypes();
    void addType(const std::string& type);
//    public List<AddressType> getTypes() {
//        return parameters.new TypeParameterList<AddressType>() {
//            @Override
//            protected AddressType _asObject(String value) {
//                return AddressType.get(value);
//            }
//        };
//    }
//    
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
private:
    std::string first(std::vector<std::string>& list) {
        return list.empty() ? "" : list[0];
    }
    
//    private static void set(List<String> list, String value) {
//        list.clear();
//        if (value != null) {
//            list.add(value);
//        }
//    }
//    
//    private static String getAddressFull(List<String> list) {
//        return list.isEmpty() ? null : StringUtils.join(list, ",");
//    }
    
protected:
    std::string _className() {
        return CLASSNAME;
    }
    
    std::string _getPropertyName() {
        return PROPERTYNAME;
    }
    
    std::string getAltId();
    void setAltId(const std::string& altId);    
};

    
}
#endif /* address_hpp */
