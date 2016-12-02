//
//  agent.cpp
//  OpenPGP
//
//  Created by Yanfeng Zhang on 1/10/17.
//  Copyright © 2017 Yanfeng Zhang. All rights reserved.
//

#include "agent.hpp"



namespace ezvcard {
    
    
    const std::string Agent::PROPERTYNAME = "AGENT";
    const std::string Agent::CLASSNAME = "Agent";
    
    
    std::vector<VCardVersion::Ptr> Agent::_getSupportedVersions() {
        return VCardVersion::V21_V30();
    }
    
    void Agent::_validate(std::list<ValidationWarning::Ptr>& warnings, const VCardVersion::Ptr& version, const std::shared_ptr<VCard>& vcard) {
        //    if (url == null && this.vcard == null) {
        //        warnings.add(new ValidationWarning(8));
        //    }
        //
        //    if (this.vcard != null) {
        //        NumberFormat nf = NumberFormat.getIntegerInstance();
        //        nf.setMinimumIntegerDigits(2);
        //
        //        ValidationWarnings validationWarnings = this.vcard.validate(version);
        //        for (Map.Entry<VCardProperty, List<ValidationWarning>> entry : validationWarnings) {
        //            VCardProperty property = entry.getKey();
        //            List<ValidationWarning> propViolations = entry.getValue();
        //
        //            for (ValidationWarning propViolation : propViolations) {
        //                String className = (property == null) ? "" : property.getClass().getSimpleName();
        //
        //                int code = propViolation.getCode();
        //                String codeStr = (code >= 0) ? "W" + nf.format(code) : "";
        //                String message = propViolation.getMessage();
        //                warnings.add(new ValidationWarning(10, className, codeStr, message));
        //            }
        //        }
        //    }
    }
    
    ///**
    // * Creates an empty agent property.
    // */
    //public Agent() {
    //    //empty
    //}
    //
    ///**
    // * Creates an agent property.
    // * @param url a URL pointing to the agent's information
    // */
    //public Agent(String url) {
    //    setUrl(url);
    //}
    //
    ///**
    // * Creates an agent property.
    // * @param vcard a vCard containing the agent's information
    // */
    //public Agent(VCard vcard) {
    //    setVCard(vcard);
    //}
    //
    ///**
    // * Copy constructor.
    // * @param original the property to make a copy of
    // */
    //public Agent(Agent original) {
    //    super(original);
    //    url = original.url;
    //    vcard = (original.vcard == null) ? null : new VCard(original.vcard);
    //}
    //
    ///**
    // * Gets the URL to the agent's information.
    // * @return the URL or null if not set
    // */
    //public String getUrl() {
    //    return url;
    //}
    //
    ///**
    // * Sets the URL to the agent's information.
    // * @param url the URL
    // */
    //public void setUrl(String url) {
    //    this.url = url;
    //    vcard = null;
    //}
    //
    ///**
    // * Gets an embedded vCard with the agent's information.
    // * @return the vCard or null if not set
    // */
    //public VCard getVCard() {
    //    return vcard;
    //}
    //
    ///**
    // * Sets an embedded vCard with the agent's information.
    // * @param vcard the vCard
    // */
    //public void setVCard(VCard vcard) {
    //    this.vcard = vcard;
    //    url = null;
    //}
    //@Override
    //protected Map<String, Object> toStringValues() {
    //    Map<String, Object> values = new LinkedHashMap<String, Object>();
    //    values.put("url", url);
    //    values.put("vcard", vcard);
    //    return values;
    //}
    //
    //@Override
    //public Agent copy() {
    //    return new Agent(this);
    //}
    //
    //@Override
    //public int hashCode() {
    //    final int prime = 31;
    //    int result = super.hashCode();
    //    result = prime * result + ((url == null) ? 0 : url.hashCode());
    //    result = prime * result + ((vcard == null) ? 0 : vcard.hashCode());
    //    return result;
    //}
    //
    //@Override
    //public boolean equals(Object obj) {
    //    if (this == obj) return true;
    //    if (!super.equals(obj)) return false;
    //    Agent other = (Agent) obj;
    //    if (url == null) {
    //        if (other.url != null) return false;
    //    } else if (!url.equals(other.url)) return false;
    //    if (vcard == null) {
    //        if (other.vcard != null) return false;
    //    } else if (!vcard.equals(other.vcard)) return false;
    //    return true;
    //}
    
    
}
