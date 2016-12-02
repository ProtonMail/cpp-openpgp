//
//  SyntaxRules.cpp
//  OpenPGP
//
//  Created by Yanfeng Zhang on 12/5/16.
//  Copyright © 2016 Yanfeng Zhang. All rights reserved.
//

#include "syntax_rules.hpp"

#include <ezvcard/util/string_util.hpp>

/**
 * Creates a new set of syntax rules.
 * @param defaultSyntaxStyle the syntax style to use when it can't be
 * determined what the data stream uses
 */
SyntaxRules::SyntaxRules(SyntaxStyle defaultSyntaxStyle) {
    
    _defaultSyntaxStyle = defaultSyntaxStyle;
}


/**
 * Gets the the syntax style to use when it can't be determined what the
 * data stream uses.
 * @return the default syntax style
 */
SyntaxStyle SyntaxRules::getDefaultSyntaxStyle() {
    return _defaultSyntaxStyle;
}

/**
 * Sets the syntax style to use when it can't be determined what the data
 * stream uses.
 * @param defaultSyntaxStyle the default syntax style (cannot be null)
 */
void SyntaxRules::setDefaultSyntaxStyle(SyntaxStyle defaultSyntaxStyle) {
    _defaultSyntaxStyle = defaultSyntaxStyle;
}

/**
 * Determines if this object contains rules for the given component.
 * @param component the component name (e.g. "VCARD")
 * @return true if this component has syntax rules, false if not
 */
bool SyntaxRules::hasSyntaxRules(const std::string& component) {
    if (!component.empty()) {
        auto comp = str_to_upper(component);
        return _syntaxRules.find(component) != _syntaxRules.end();
    }
    return false;
}

/**
 * Gets the syntax style to use for a given component.
 * @param component the component name (e.g. "VCARD")
 * @param versionValue the value of the component's VERSION property (e.g.
 * "2.1")
 * @return the syntax style or null if none was found
 */
SyntaxStyle SyntaxRules::getSyntaxStyle(std::string component, std::string versionValue) {
    if (!component.empty()) {
        auto comp = str_to_upper(component);
        //need check
        auto rules = _syntaxRules[comp];
        if (rules.find(versionValue) != rules.end()) {
            return rules[versionValue];
        } else {
            return SyntaxStyle::NONE;
        }
    }
    return SyntaxStyle::NONE;
}

/**
 * Adds a rule.
 * @param component the name of the component that contains the VERSION
 * property (e.g. "VCARD"), or null if the VERSION property will not be
 * inside of any components
 * @param version the value of the VERSION property
 * @param syntaxStyle the syntax style to use when a VERSION property with
 * the given value, and under the given component, is encountered
 */
void SyntaxRules::addRule(std::string component, std::string version, SyntaxStyle syntaxStyle) {
    if (!component.empty()) {
        auto comp = str_to_upper(component);
        //Map<String, SyntaxStyle> rules = syntaxRules.get(component);
        auto rules = _syntaxRules[component];
        
        //        //if (rules == null) {
        //        //rules = new HashMap<String, SyntaxStyle>();
        //        rules = std::unordered_map<std::string, SyntaxStyle>();
        //        _syntaxRules[component] = rules;
        //        //}
        
        rules[version] = syntaxStyle;
        _syntaxRules[component] = rules;
    }
}


/**
 * Creates a set of rules for iCalendar data.
 * @return the rules
 */

SyntaxRules SyntaxRules::iCalendar() {
    /*
     * Initialize to the old style syntax because the VERSION property can
     * technically exist anywhere inside the data stream under this version.
     *
     * However, this setting is rarely important in practice because I've
     * never seen an iCalendar object that doesn't put its VERSION property
     * at the very beginning.
     */
    SyntaxRules rules = SyntaxRules(SyntaxStyle::OLD);
    std::string component = "VCALENDAR";
    rules.addRule(component, "1.0", SyntaxStyle::OLD);
    rules.addRule(component, "2.0", SyntaxStyle::NEW);
    return rules;
}

/**
 * Creates a set of rules for vCard data.
 * @return the rules
 */
SyntaxRules SyntaxRules::vcard() {
    /*
     * Initialize to the old style syntax because the VERSION property can
     * technically exist anywhere inside the data stream under this version.
     *
     * However, this setting is rarely important in practice because I've
     * never seen a vCard that doesn't put its VERSION property at the very
     * beginning.
     */
    SyntaxRules rules = SyntaxRules(SyntaxStyle::OLD);
    std::string component = "VCARD";
    rules.addRule(component, "2.1", SyntaxStyle::OLD);
    rules.addRule(component, "3.0", SyntaxStyle::NEW);
    rules.addRule(component, "4.0", SyntaxStyle::NEW);
    return rules;
}
