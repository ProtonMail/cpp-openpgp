//
//  structured_name.cpp
//  OpenPGP
//
//  Created by Yanfeng Zhang on 1/10/17.
//  Copyright © 2017 Yanfeng Zhang. All rights reserved.
//

#include "structured_name.hpp"

namespace ProtonMail {
    
    std::shared_ptr<IStructuredName> IStructuredName::create_instance() {
        return nullptr;
    }
}

namespace ezvcard {


const std::string StructuredName::PROPERTYNAME = "N";
const std::string StructuredName::CLASSNAME = "StructuredName";


/**
 * Copy constructor.
 * @param original the property to make a copy of
 */
StructuredName::StructuredName(const StructuredName::Ptr& original) {
    _family = original->getFamily();
    _given = original->getGiven();
    _additional = original->getAdditionalNames();
    _prefixes = original->getPrefixes();
    _suffixes = original->getSuffixes();
}


StructuredName::StructuredName() {
}



/**
 * Gets the family name (aka "surname" or "last name").
 * @return the family name or null if not set
 */
std::string StructuredName::getFamily() {
    return _family;
}

/**
 * Sets the family name (aka "surname" or "last name").
 * @param family the family name or null to remove
 */
void StructuredName::setFamily(const std::string& family) {
    _family = family;
}

/**
 * Gets the given name (aka "first name").
 * @return the given name or null if not set
 */
std::string StructuredName::getGiven() {
    return _given;
}

/**
 * Sets the given name (aka "first name").
 * @param given the given name or null to remove
 */
void StructuredName::setGiven(const std::string& given) {
    _given = given;
}


/**
 * Gets the list that stores additional names the person goes by (for
 * example, a middle name).
 * @return the additional names (this list is mutable)
 */
std::vector<std::string> StructuredName::getAdditionalNames() {
    return _additional;
}

/**
 * Gets the list that stores the person's honorific prefixes.
 * @return the prefixes (e.g. "Dr.", "Mr.") (this list is mutable)
 */
std::vector<std::string> StructuredName::getPrefixes() {
    return _prefixes;
}

/**
 * Gets the list that stores the person's honorary suffixes.
 * @return the suffixes (e.g. "M.D.", "Jr.") (this list is mutable)
 */
std::vector<std::string> StructuredName::getSuffixes() {
    return _suffixes;
}

void StructuredName::addAdditionalName(const std::string& name) {
    _additional.push_back(name);
}

void StructuredName::addPrefix(const std::string& prefix) {
    _prefixes.push_back(prefix);
}

void StructuredName::addSuffix(const std::string& suffix) {
    _suffixes.push_back(suffix);
}

void StructuredName::clearNames() {
    _additional.clear();
}
void StructuredName::clearPrefixes() {
    _prefixes.clear();
}
void StructuredName::clearSuffixes() {
    _suffixes.clear();
}


void StructuredName::addAdditionalNames(const std::vector<std::string>& names) {
    for (auto n : names) {
        _additional.push_back(n);
    }
}
void StructuredName::addPrefixes(const std::vector<std::string>& prefixes) {
    for (auto p : prefixes) {
        _prefixes.push_back(p);
    }
}

void StructuredName::addSuffixes(const std::vector<std::string>& suffixes) {
    for (auto s : suffixes) {
        _suffixes.push_back(s);
    }
}


//    /**
//     * <p>
//     * Gets the list that holds string(s) which define how to sort the vCard.
//     * </p>
//     * <p>
//     * 2.1 and 3.0 vCards should use the {@link SortString} property instead.
//     * </p>
//     * <p>
//     * <b>Supported versions:</b> {@code 4.0}
//     * </p>
//     * @return the sort string(s) (this list is mutable). For example, if the
//     * family name is "d'Aboville" and the given name is "Christine", the sort
//     * strings might be ["Aboville", "Christine"].
//     */
//    public List<String> getSortAs() {
//        return parameters.getSortAs();
//    }
//
//    /**
//     * <p>
//     * Defines a sortable version of the person's name.
//     * </p>
//     * <p>
//     * 2.1 and 3.0 vCards should use the {@link SortString} property instead.
//     * </p>
//     * <p>
//     * <b>Supported versions:</b> {@code 4.0}
//     * </p>
//     * @param family the sortable version of the family name (for example,
//     * "Adboville" if the family name is "d'Aboville") or null to remove
//     */
//    public void setSortAs(String family) {
//        parameters.setSortAs(family);
//    }
//
//    /**
//     * <p>
//     * Defines a sortable version of the person's name.
//     * </p>
//     * <p>
//     * 2.1 and 3.0 vCards should use the {@link SortString} property instead.
//     * </p>
//     * <p>
//     * <b>Supported versions:</b> {@code 4.0}
//     * </p>
//     * @param family the sortable version of the family name (for example,
//     * "Adboville" if the family name is "d'Aboville")
//     * @param given the sortable version of the given name
//     */
//    public void setSortAs(String family, String given) {
//        parameters.setSortAs(family, given);
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

std::string StructuredName::getAltId() {
    return _parameters->getAltId();
}

void StructuredName::setAltId(const std::string& altId) {
    _parameters->setAltId(altId);
}

void StructuredName::_validate(std::list<ValidationWarning::Ptr>& warnings, const VCardVersion::Ptr& version, const std::shared_ptr<VCard>& vcard) {
    /*
     * 2.1 does not allow multi-valued components.
     */
    if (version == VCardVersion::V2_1()) {
        if (_additional.size() > 1 ||
            _prefixes.size() > 1 ||
            _suffixes.size() > 1) {
            warnings.push_back(std::make_shared<ValidationWarning>(34));
        }
    }
}


//    @Override
//    protected Map<String, Object> toStringValues() {
//        Map<String, Object> values = new LinkedHashMap<String, Object>();
//        values.put("family", family);
//        values.put("given", given);
//        values.put("additional", additional);
//        values.put("prefixes", prefixes);
//        values.put("suffixes", suffixes);
//        return values;
//    }
//    @Override
//    public StructuredName copy() {
//        return new StructuredName(this);
//    }
//
//    @Override
//    public int hashCode() {
//        final int prime = 31;
//        int result = super.hashCode();
//        result = prime * result + additional.hashCode();
//        result = prime * result + ((family == null) ? 0 : family.hashCode());
//        result = prime * result + ((given == null) ? 0 : given.hashCode());
//        result = prime * result + prefixes.hashCode();
//        result = prime * result + suffixes.hashCode();
//        return result;
//    }
//
//    @Override
//    public boolean equals(Object obj) {
//        if (this == obj) return true;
//        if (!super.equals(obj)) return false;
//        StructuredName other = (StructuredName) obj;
//        if (!additional.equals(other.additional)) return false;
//        if (family == null) {
//            if (other.family != null) return false;
//        } else if (!family.equals(other.family)) return false;
//        if (given == null) {
//            if (other.given != null) return false;
//        } else if (!given.equals(other.given)) return false;
//        if (!prefixes.equals(other.prefixes)) return false;
//        if (!suffixes.equals(other.suffixes)) return false;
//        return true;
//    }

}
