//
//  organization.hpp
//  OpenPGP
//
//  Created by Yanfeng Zhang on 1/10/17.
//  Copyright © 2017 Yanfeng Zhang. All rights reserved.
//

#ifndef organization_hpp
#define organization_hpp

#include "text_list_property.hpp"
#include "has_alt_Id.hpp"
#include <bridge/i_organization.hpp>

using namespace ProtonMail;
namespace ezvcard {
    

/**
 * <p>
 * Defines a list of organizations the person belongs to. The list is ordered.
 * It begins with the broadest organization and ends with the most specific.
 * </p>
 *
 * <p>
 * <b>Code sample</b>
 * </p>
 *
 * <pre class="brush:java">
 * VCard vcard = new VCard();
 *
 * Organization org = new Organization();
 * org.getValues().add("Google");
 * org.getValues().add("GMail Team");
 * org.getValues().add("Spam Detection Team");
 * vcard.setOrganization(org);
 * </pre>
 *
 * <p>
 * <b>Property name:</b> {@code ORG}
 * </p>
 * <p>
 * <b>Supported versions:</b> {@code 2.1, 3.0, 4.0}
 * </p>
 * @author Michael Angstadt
 * @see <a href="http://tools.ietf.org/html/rfc6350#page-40">RFC 6350 p.40</a>
 * @see <a href="http://tools.ietf.org/html/rfc2426#page-20">RFC 2426 p.20</a>
 * @see <a href="http://www.imc.org/pdi/vcard-21.doc">vCard 2.1 p.19</a>
 */
class Organization : public TextListProperty, public IOrganization, HasAltId {
public:
    typedef std::shared_ptr<Organization> Ptr;
    const static std::string PROPERTYNAME;
    const static std::string CLASSNAME;
    
public:
    Organization() {
        //empty
    }
    
//    /**
//     * Copy constructor.
//     * @param original the property to make a copy of
//     */
//    public Organization(Organization original) {
//        super(original);
//    }
    
//    @Override
//    public String getLanguage() {
//        return super.getLanguage();
//    }
//    
//    @Override
//    public void setLanguage(String language) {
//        super.setLanguage(language);
//    }
    
    /**
     * Gets the TYPE parameter.
     * <p>
     * <b>Supported versions:</b> {@code 4.0}
     * </p>
     * @return the TYPE value (typically, this will be either "work" or "home")
     * or null if it doesn't exist
     */
    std::string getType() {
        return _parameters->getType();
    }
    
    /**
     * Sets the TYPE parameter.
     * <p>
     * <b>Supported versions:</b> {@code 4.0}
     * </p>
     * @param type the TYPE value (this should be either "work" or "home") or
     * null to remove
     */
    void setType(const std::string& type) {
        _parameters->setType(type);
    }
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
//     * <p>
//     * Gets the list that holds string(s) which define how to sort the vCard.
//     * </p>
//     * <p>
//     * 2.1 and 3.0 vCards should use the {@link SortString} property instead.
//     * </p>
//     * <p>
//     * <b>Supported versions:</b> {@code 4.0}
//     * </p>
//     * @return the sort string(s) (this list is mutable)
//     */
//    public List<String> getSortAs() {
//        return parameters.getSortAs();
//    }
//    
//    /**
//     * <p>
//     * Sets the sort string for this property.
//     * </p>
//     * <p>
//     * 2.1 and 3.0 vCards should use the {@link SortString} property instead.
//     * </p>
//     * <p>
//     * <b>Supported versions:</b> {@code 4.0}
//     * </p>
//     * @param sortString the sort string or null to remove
//     */
//    public void setSortAs(String sortString) {
//        parameters.setSortAs(sortString);
//    }
//    
//    @Override
//    public Organization copy() {
//        return new Organization(this);
//    }
    
    std::string getValue() final {
        auto values = TextListProperty::getValues();
        if (values.size() > 0) {
            return values.front();
        }
        return "";
    }
    
protected:
    std::string _className() {
        return CLASSNAME;
    }
    
    std::string _getPropertyName() {
        return PROPERTYNAME;
    }
    
    
    std::string getAltId();
    void setAltId(const std::string& altId);
    
public:
    std::vector<std::string> getValues();
};


}
#endif /* organization_hpp */
