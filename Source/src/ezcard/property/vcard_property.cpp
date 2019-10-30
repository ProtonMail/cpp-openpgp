//
//  vcard_property.cpp
//  OpenPGP
//
//  Created by Yanfeng Zhang on 12/2/16.
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


#include "vcard_property.hpp"
#include "vobject_validator.hpp"


namespace ezvcard {
    

VCardProperty::VCardProperty() {
    _parameters = std::make_shared<VCardParameters>();
}

VCardProperty::~VCardProperty() {
    
}

//    /**
//     * Copy constructor.
//     * @param original the property to make a copy of
//     */
//    protected VCardProperty(VCardProperty original) {
//        group = original.group;
//        parameters = new VCardParameters(original.parameters);
//    }
//
/**
 * <p>
 * Gets the vCard versions that support this property.
 * </p>
 * <p>
 * The supported versions are defined by assigning a
 * {@link SupportedVersions @SupportedVersions} annotation to the property
 * class. Property classes without this annotation are considered to be
 * supported by all versions.
 * </p>
 * @return the vCard versions that support this property.
 */
std::vector<VCardVersion::Ptr> VCardProperty::getSupportedVersions() {
    return _getSupportedVersions();
}

/**
 * <p>
 * Determines if this property is supported by the given vCard version.
 * </p>
 * <p>
 * The supported versions are defined by assigning a
 * {@link SupportedVersions} annotation to the property class. Property
 * classes without this annotation are considered to be supported by all
 * versions.
 * </p>
 * @param version the vCard version
 * @return true if it is supported, false if not
 */
bool VCardProperty::isSupportedBy(VCardVersion::Ptr version) {
    auto supportedVersions = getSupportedVersions();
    for (auto supportedVersion : supportedVersions) {
        if (supportedVersion == version) {
            return true;
        }
    }
    return false;
}

/**
 * Checks the property for data consistency problems or deviations from the
 * spec. These problems will not prevent the property from being written to
 * a data stream, but may prevent it from being parsed correctly by the
 * consuming application. These problems can largely be avoided by reading
 * the Javadocs of the property class, or by being familiar with the vCard
 * standard.
 * @param version the version to check the property against (use 4.0 for
 * xCard and jCard)
 * @param vcard the vCard this property belongs to
 * @see VCard#validate
 * @return a list of warnings or an empty list if no problems were found
 */
std::list<ValidationWarning::Ptr> VCardProperty::validate(const VCardVersion::Ptr& version, const std::shared_ptr<VCard>& vcard) {
    std::list<ValidationWarning::Ptr> warnings;
    
    //check the supported versions
    if (!isSupportedBy(version)) {
        warnings.push_back(std::make_shared<ValidationWarning>(2, VCardVersion::toString(getSupportedVersions())));
    }
    
    //check parameters
    auto wl = _parameters->validate(version);
    for (auto w : wl ) {
        warnings.push_back(w);
    }
    
    //check group
    if (_group != "") {
        auto syntax = version->getSyntaxStyle();
        auto allowed = VObjectValidator::get()->allowedCharactersGroup(syntax, true);
        if (!allowed->check(_group)) {
            if (syntax == SyntaxStyle::OLD) {
                auto notAllowed = allowed->flip();
                warnings.push_back(std::make_shared<ValidationWarning>(32, _group, notAllowed->toString(true)));
            } else {
                warnings.push_back(std::make_shared<ValidationWarning>(23, _group));
            }
        }
    }
    
    _validate(warnings, version, vcard);
    
    return warnings;

}

/**
 * Checks the property for data consistency problems or deviations from the
 * spec. Meant to be overridden by child classes that wish to provide
 * validation logic.
 * @param warnings the list to add the warnings to
 * @param version the version to check the property against
 * @param vcard the vCard this property belongs to
 */


void VCardProperty::_validate(std::list<ValidationWarning::Ptr>& warnings, const VCardVersion::Ptr& version, const std::shared_ptr<VCard>& vcard) {
    //empty
}

/**
 * Gets all of the property's parameters.
 * @return the property's parameters
 */
VCardParameters::Ptr VCardProperty::getParameters() {
    return _parameters;
}

/**
 * Sets the property's parameters.
 * @param parameters the parameters (cannot be null)
 */
void VCardProperty::setParameters(VCardParameters::Ptr parameters) {
    if (parameters == nullptr) {
        return;
        // throw new NullPointerException(Messages.INSTANCE.getExceptionMessage(42));
    }
    _parameters = parameters;
}


/**
 * Gets the first value of a parameter.
 * @param name the parameter name (case insensitive, e.g. "LANGUAGE")
 * @return the parameter value or null if not found
 */
std::string VCardProperty::getParameter(const std::string& name) {
    return _parameters->first(name);
}

/**
 * Gets all values of a parameter.
 * @param name the parameter name (case insensitive, e.g. "LANGUAGE")
 * @return the parameter values (this list is immutable)
 */
std::vector<std::string> VCardProperty::getParameters(const std::string& name) {
    return _parameters->get(name);
}

/**
 * Replaces all existing values of a parameter with the given value.
 * @param name the parameter name (case insensitive, e.g. "LANGUAGE")
 * @param value the parameter value
 */
void VCardProperty::setParameter(std::string name, std::string value) {
    //parameters.replace(name, value);
}

/**
 * Adds a value to a parameter.
 * @param name the parameter name (case insensitive, e.g. "LANGUAGE")
 * @param value the parameter value
 */
void VCardProperty::addParameter(std::string name, std::string value) {
   //parameters.put(name, value);
}

/**
 * Removes a parameter from the property.
 * @param name the parameter name (case insensitive, e.g. "LANGUAGE")
 */
void VCardProperty::removeParameter(std::string name) {
    //parameters->removeAll(name);
}

/**
 * Gets this property's group.
 * @return the group or null if it does not belong to a group
 */
std::string VCardProperty::getGroup() {
    return _group;
}

/**
 * Sets this property's group.
 * @param group the group or null to remove the property's group
 */
void VCardProperty::setGroup(std::string group) {
    _group = group;
}

//    /**
//     * Sorts by PREF parameter ascending. Properties that do not have a PREF
//     * parameter are pushed to the end of the list.
//     */
//    public int compareTo(VCardProperty that) {
//        Integer pref0 = this.getParameters().getPref();
//        Integer pref1 = that.getParameters().getPref();
//        if (pref0 == null && pref1 == null) {
//            return 0;
//        }
//        if (pref0 == null) {
//            return 1;
//        }
//        if (pref1 == null) {
//            return -1;
//        }
//        return pref1.compareTo(pref0);
//    }
//
//    /**
//     * <p>
//     * Gets string representations of the class's fields for the
//     * {@link #toString} method.
//     * </p>
//     * <p>
//     * Meant to be overridden by child classes. The default implementation
//     * returns an empty map.
//     * </p>
//     * @return the values of the class's fields (key = field name, value = field
//     * value)
//     */
//    protected Map<String, Object> toStringValues() {
//        return Collections.emptyMap();
//    }
//
//    @Override
//    public String toString() {
//        StringBuilder sb = new StringBuilder();
//        sb.append(getClass().getName());
//        sb.append(" [ group=").append(group);
//        sb.append(" | parameters=").append(parameters);
//        for (Map.Entry<String, Object> field : toStringValues().entrySet()) {
//            String fieldName = field.getKey();
//            Object fieldValue = field.getValue();
//            sb.append(" | ").append(fieldName).append('=').append(fieldValue);
//        }
//        sb.append(" ]");
//        return sb.toString();
//    }
//
//    /**
//     * <p>
//     * Creates a copy of this property object.
//     * </p>
//     * <p>
//     * The default implementation of this method uses reflection to look for a
//     * copy constructor. Child classes SHOULD override this method to avoid the
//     * performance overhead involved in using reflection.
//     * </p>
//     * <p>
//     * The child class's copy constructor, if present, MUST invoke the
//     * {@link #VCardProperty(VCardProperty)} super constructor to ensure that
//     * the group name and parameters are also copied.
//     * </p>
//     * <p>
//     * This method MUST be overridden by the child class if the child class does
//     * not have a copy constructor. Otherwise, an
//     * {@link UnsupportedOperationException} will be thrown when an attempt is
//     * made to copy the property (such as in the {@link VCard#VCard(VCard) VCard
//     * class's copy constructor}).
//     * </p>
//     * @return the copy
//     * @throws UnsupportedOperationException if the class does not have a copy
//     * constructor or there is a problem invoking it
//     */
//    public VCardProperty copy() {
//        Class<? extends VCardProperty> clazz = getClass();
//
//        try {
//            Constructor<? extends VCardProperty> copyConstructor = clazz.getConstructor(clazz);
//            return copyConstructor.newInstance(this);
//        } catch (Exception e) {
//            throw new UnsupportedOperationException(Messages.INSTANCE.getExceptionMessage(31, clazz.getName()), e);
//        }
//    }
//
//    @Override
//    public int hashCode() {
//        final int prime = 31;
//        int result = 1;
//        result = prime * result + ((group == null) ? 0 : group.toLowerCase().hashCode());
//        result = prime * result + parameters.hashCode();
//        return result;
//    }
//
//    @Override
//    public boolean equals(Object obj) {
//        if (this == obj) return true;
//        if (obj == null) return false;
//        if (getClass() != obj.getClass()) return false;
//        VCardProperty other = (VCardProperty) obj;
//        if (group == null) {
//            if (other.group != null) return false;
//        } else if (!group.equalsIgnoreCase(other.group)) return false;
//        if (!parameters.equals(other.parameters)) return false;
//        return true;
//    }
//
//    /*
//     * Note: The following parameter helper methods are package-scoped so they
//     * don't clutter up the Javadocs for the VCardProperty class. They are
//     * defined here instead of in the child classes that use them, so that their
//     * Javadocs don't have to be repeated.
//     */
//
//    /**
//     * <p>
//     * Gets the list that stores this property's PID (property ID) parameter
//     * values.
//     * </p>
//     * <p>
//     * PIDs can exist on any property where multiple instances are allowed (such
//     * as {@link Email} or {@link Address}, but not {@link StructuredName}
//     * because only 1 instance of this property is allowed per vCard).
//     * </p>
//     * <p>
//     * When used in conjunction with the {@link ClientPidMap} property, it
//     * allows an individual property instance to be uniquely identifiable. This
//     * feature is made use of when two different versions of the same vCard have
//     * to be merged together (called "synchronizing").
//     * </p>
//     * <p>
//     * <b>Supported versions:</b> {@code 4.0}
//     * </p>
//     * @return the PID parameter values (this list is mutable)
//     * @see <a href="http://tools.ietf.org/html/rfc6350#page-19">RFC 6350
//     * p.19</a>
//     */
//    List<Pid> getPids() {
//        return parameters.getPids();
//    }
//
//    /**
//     * <p>
//     * Gets this property's preference value. The lower this number is, the more
//     * "preferred" the property instance is compared with other properties of
//     * the same type. If a property doesn't have a preference value, then it is
//     * considered the least preferred.
//     * </p>
//     * <p>
//     * In the vCard below, the {@link Address} on the second row is the most
//     * preferred because it has the lowest PREF value.
//     * </p>
//     *
//     * <pre>
//     * ADR;TYPE=work;PREF=2:;;1600 Amphitheatre Parkway;Mountain View;CA;94043
//     * ADR;TYPE=work;PREF=1:;;One Microsoft Way;Redmond;WA;98052
//     * ADR;TYPE=home:;;123 Maple St;Hometown;KS;12345
//     * </pre>
//     *
//     * <p>
//     * <b>Supported versions:</b> {@code 4.0}
//     * </p>
//     * @return the preference value or null if not set
//     * @see <a href="http://tools.ietf.org/html/rfc6350#page-17">RFC 6350
//     * p.17</a>
//     */
//    Integer getPref() {
//        return parameters.getPref();
//    }
//
//    /**
//     * <p>
//     * Sets this property's preference value. The lower this number is, the more
//     * "preferred" the property instance is compared with other properties of
//     * the same type. If a property doesn't have a preference value, then it is
//     * considered the least preferred.
//     * </p>
//     * <p>
//     * In the vCard below, the {@link Address} on the second row is the most
//     * preferred because it has the lowest PREF value.
//     * </p>
//     *
//     * <pre>
//     * ADR;TYPE=work;PREF=2:;;1600 Amphitheatre Parkway;Mountain View;CA;94043
//     * ADR;TYPE=work;PREF=1:;;One Microsoft Way;Redmond;WA;98052
//     * ADR;TYPE=home:;;123 Maple St;Hometown;KS;12345
//     * </pre>
//     *
//     * <p>
//     * <b>Supported versions:</b> {@code 4.0}
//     * </p>
//     * @param pref the preference value or null to remove
//     * @see <a href="http://tools.ietf.org/html/rfc6350#page-17">RFC 6350
//     * p.17</a>
//     */
//    void setPref(Integer pref) {
//        parameters.setPref(pref);
//    }
//
//    /**
//     * Gets the language that the property value is written in.
//     * @return the language or null if not set
//     */
//    String getLanguage() {
//        return parameters.getLanguage();
//    }
//
//    /**
//     * Sets the language that the property value is written in.
//     * @param language the language or null to remove
//     */
//    void setLanguage(String language) {
//        parameters.setLanguage(language);
//    }
//
//    /**
//     * <p>
//     * Gets the sorted position of this property when it is grouped together
//     * with other properties of the same type. Properties with low index values
//     * are put at the beginning of the sorted list. Properties with high index
//     * values are put at the end of the list.
//     * </p>
//     * <p>
//     * <b>Supported versions:</b> {@code 4.0}
//     * </p>
//     * @return the index or null if not set
//     * @throws IllegalStateException if the parameter value is malformed and
//     * cannot be parsed. If this happens, you may use the
//     * {@link #getParameter(String)} method to retrieve its raw value.
//     * @see <a href="https://tools.ietf.org/html/rfc6715#page-7">RFC 6715
//     * p.7</a>
//     */
//    Integer getIndex() {
//        return parameters.getIndex();
//    }
//
//    /**
//     * <p>
//     * Sets the sorted position of this property when it is grouped together
//     * with other properties of the same type. Properties with low index values
//     * are put at the beginning of the sorted list. Properties with high index
//     * values are put at the end of the list.
//     * </p>
//     * <p>
//     * <b>Supported versions:</b> {@code 4.0}
//     * </p>
//     * @param index the index or null to remove
//     * @throws IllegalStateException if the parameter value is malformed and
//     * cannot be parsed. If this happens, you may use the
//     * {@link #getParameter(String)} method to retrieve its raw value.
//     * @see <a href="https://tools.ietf.org/html/rfc6715#page-7">RFC 6715
//     * p.7</a>
//     */
//    void setIndex(Integer index) {
//        parameters.setIndex(index);
//    }
//}

bool VCardProperty::equals(const VCardProperty::Ptr& obj) {
    if (_group != obj->_group) {
        return false;
    }
    
    if (!_parameters->equals(obj->getParameters())) {
        return false;
    }
    
    return true;
}


void VCardProperty::Print() {
    std::cout << "group name: " << _group << std::endl;
    _parameters->Print();
}



}
