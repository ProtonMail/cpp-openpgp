//
//  telephone.cpp
//  OpenPGP
//
//  Created by Yanfeng Zhang on 1/10/17.
//  Copyright © 2017 Yanfeng Zhang. All rights reserved.
//

#include "telephone.hpp"


namespace ProtonMail {
    
    std::shared_ptr<ITelephone> ITelephone::create_instance(const std::string & type, const std::string & number) {
        return std::make_shared<ezvcard::Telephone>(number, type);
    }
}


namespace ezvcard {
    
    
    const std::string Telephone::PROPERTYNAME = "TEL";
    const std::string Telephone::CLASSNAME = "Telephone";
    
    std::string Telephone::getAltId() {
        return _parameters->getAltId();
    }
    
    void Telephone::setAltId(const std::string& altId) {
        _parameters->setAltId(altId);
    }
    
    /**
     * Creates a telephone property.
     * @param text the telephone number (e.g. "(123) 555-6789")
     */
    Telephone::Telephone(const std::string& text) {
        setText(text);
    }
    
    Telephone::Telephone(const std::string& text, const std::string& type) {
        setText(text);
        _parameters->setType(type);
    }

    
    /**
     * Creates a telephone property.
     * @param uri a "tel" URI representing the telephone number (vCard 4.0 only)
     */
    Telephone::Telephone(const TelUri::Ptr& uri) {
        setUri(uri);
    }
    
    //    /**
    //     * Copy constructor.
    //     * @param original the property to make a copy of
    //     */
    //    public Telephone(Telephone original) {
    //        super(original);
    //        text = original.text;
    //        uri = original.uri;
    //    }
    
    /**
     * Gets the telephone number as a text value.
     * @return the telephone number or null if the text value is not set
     */
    std::string Telephone::getText() {
        return _text;
    }
    
    /**
     * Sets the telephone number as a text value.
     * @param text the telephone number
     */
    void Telephone::setText(const std::string& text) {
        _text = text;
        _uri = nullptr;
    }
    
    /**
     * Gets a "tel" URI representing the phone number.
     * <p>
     * <b>Supported versions:</b> {@code 4.0}
     * </p>
     * @return the "tel" URI or null if it is not set
     */
    TelUri::Ptr Telephone::getUri() {
        return _uri;
    }
    
    /**
     * Sets a "tel" URI representing the phone number.
     * <p>
     * <b>Supported versions:</b> {@code 4.0}
     * </p>
     * @param uri the "tel" URI
     */
    void Telephone::setUri(const TelUri::Ptr& uri) {
        _text = "";
        _uri = uri;
    }
    
    /**
     * Gets the list that stores this property's telephone types (TYPE
     * parameters).
     * @return the telephone types (e.g. "HOME", "WORK") (this list is mutable)
     */
    std::vector<std::string> Telephone::getTypes() {
        return _parameters->getTypes();
    }
    //    /**
    //     * Gets the list that stores this property's telephone types (TYPE
    //     * parameters).
    //     * @return the telephone types (e.g. "HOME", "WORK") (this list is mutable)
    //     */
    //    public List<TelephoneType> getTypes() {
    //        return parameters.new TypeParameterList<TelephoneType>() {
    //            @Override
    //            protected TelephoneType _asObject(String value) {
    //                return TelephoneType.get(value);
    //            }
    //        };
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
    //    @Override
    //    protected void _validate(List<ValidationWarning> warnings, VCardVersion version, VCard vcard) {
    //        if (uri == null && text == null) {
    //            warnings.add(new ValidationWarning(8));
    //        }
    //
    //        if (uri != null && (version == VCardVersion.V2_1 || version == VCardVersion.V3_0)) {
    //            warnings.add(new ValidationWarning(19));
    //        }
    //
    //        for (TelephoneType type : getTypes()) {
    //            if (type == TelephoneType.PREF) {
    //                //ignore because it is converted to a PREF parameter for 4.0 vCards
    //                continue;
    //            }
    //
    //            if (!type.isSupportedBy(version)) {
    //                warnings.add(new ValidationWarning(9, type.getValue()));
    //            }
    //        }
    //    }
    //
    //    @Override
    //    protected Map<String, Object> toStringValues() {
    //        Map<String, Object> values = new LinkedHashMap<String, Object>();
    //        values.put("uri", uri);
    //        values.put("text", text);
    //        return values;
    //    }
    //
    //    @Override
    //    public Telephone copy() {
    //        return new Telephone(this);
    //    }
    //
    //    @Override
    //    public int hashCode() {
    //        final int prime = 31;
    //        int result = super.hashCode();
    //        result = prime * result + ((text == null) ? 0 : text.hashCode());
    //        result = prime * result + ((uri == null) ? 0 : uri.hashCode());
    //        return result;
    //    }
    //
    //    @Override
    //    public boolean equals(Object obj) {
    //        if (this == obj) return true;
    //        if (!super.equals(obj)) return false;
    //        Telephone other = (Telephone) obj;
    //        if (text == null) {
    //            if (other.text != null) return false;
    //        } else if (!text.equals(other.text)) return false;
    //        if (uri == null) {
    //            if (other.uri != null) return false;
    //        } else if (!uri.equals(other.uri)) return false;
    //        return true;
    //    }
    //}
    
}
