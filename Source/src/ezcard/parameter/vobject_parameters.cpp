//
//  vobject_parameters.cpp
//  OpenPGP
//
//  Created by Yanfeng Zhang on 12/5/16.
//  Copyright © 2016 Yanfeng Zhang. All rights reserved.
//

#include "vobject_parameters.hpp"
#include <ezvcard/util/string_util.hpp>
#include <iostream>


namespace vinnie {
    
    /**
     * Creates an empty list of parameters.
     */
    VObjectParameters::VObjectParameters() {
        
    }
    
    /**
     * Copies an existing list of parameters.
     * @param original the existing list
     */
    VObjectParameters::VObjectParameters(const VObjectParameters::Ptr& original) {
        _multipmap = original->getMap();
    }
    
    /**
     * <p>
     * Creates a list of parameters backed by the given map. Any changes made to
     * the given map will effect the parameter list and vice versa.
     * </p>
     * <p>
     * If the given map is not empty, care should be taken to ensure that all of
     * its keys are in uppercase before passing it into this constructor.
     * </p>
     * @param map the map
     */
    VObjectParameters::VObjectParameters(std::unordered_map<std::string, std::vector<std::string>> map) {
        _multipmap = map;
    }
    
    /**
     * Gets the values that are assigned to a key.
     * @param key the key
     * @return the values or null if the key does not exist
     */
    std::vector<std::string> VObjectParameters::get(const std::string& key) {
        auto newKey = sanitizeKey(key);
        return _get(newKey);
    }
    
    /**
     * @param key assumed to already be in uppercase
     */
    std::vector<std::string> VObjectParameters::_get(const std::string& key) {
        auto search = _multipmap.find(key);
        if(search != _multipmap.end()) {
            return search->second;
        }
        return std::vector<std::string>();
    }
    
    /**
     * Inserts a value.
     * @param key the key
     * @param value the value to add
     */
    void VObjectParameters::put(std::string key, std::string value) {
        key = sanitizeKey(key);
        _put(key, value);
    }
    
    /**
     * @param key assumed to already be in uppercase
     * @param value the value to add
     */
    void VObjectParameters::_put(std::string key, std::string value) {
        auto list = _get(key);
        list.push_back(value);
        _multipmap[key] = list;
    }
    
    /**
     * Inserts multiple values.
     * @param key the key
     * @param values the values to add
     */
    void VObjectParameters::putAll(std::string key, std::vector<std::string> values) {
        if (values.size() == 0) {
            return;
        }
        auto newKey = sanitizeKey(key);
        _putAll(newKey, values);
    }
    
    /**
     * @param key assumed to already be in uppercase
     * @param values the values to add
     */
    void VObjectParameters::_putAll(std::string key, std::vector<std::string> values) {
        auto list = _get(key);
        list.insert(list.end(), values.begin(), values.end());
        _multipmap[key] = list;
    }
    
    /**
     * Replaces all the values of the given key with the given value.
     * @param key the key
     * @param value the value
     * @return the replaced values or null if the key didn't exist
     */
    std::vector<std::string> VObjectParameters::replace(std::string key, std::string value) {
        auto newKey = sanitizeKey(key);
        auto replaced = _removeAll(newKey);
        _put(newKey, value);
        return replaced;
    }
    
    /**
     * Replaces all the values of the given key with the given values.
     * @param key the key
     * @param values the values
     * @return the replaced values or null if the key didn't exist
     */
    std::vector<std::string> VObjectParameters::replaceAll(std::string key, std::vector<std::string> values) {
        auto newKey = sanitizeKey(key);
        auto replaced = _removeAll(newKey);
        if (values.size() > 0) {
            _putAll(newKey, values);
        }
        return replaced;
    }
    
    /**
     * Removes a value.
     * @param key the key
     * @param value the value to remove
     * @return true if the value was found, false if not
     */
    bool VObjectParameters::remove(std::string key, std::string value) {
        auto newKey = sanitizeKey(key);
        auto values = _get(newKey);
        auto old_size = values.size();
        
        auto it = std::find(values.begin(), values.end(), value);
        if(it != values.end())
            values.erase(it);
        
        auto search = _multipmap.find(newKey);
        if(search != _multipmap.end()) {
            _multipmap[newKey] = values;
        }
        auto new_size = values.size();
        
        return old_size != new_size;
        
    }
    
    /**
     * Removes all values associated with a key, along with the key itself.
     * @param key the key
     * @return the removed values or null if the key didn't exist
     */
    std::vector<std::string> VObjectParameters::removeAll(std::string key) {
        auto newkey = sanitizeKey(key);
        return _removeAll(newkey);
    }
    
    /**
     * @param key assumed to already be in uppercase
     */
    std::vector<std::string> VObjectParameters::_removeAll(std::string key) {
        auto old_list = _get(key);
        _multipmap.erase (key);
        return old_list;
    }
    
    /**
     * Clears the multimap.
     */
    void VObjectParameters::clear() {
        _multipmap.clear();
    }
    
    void VObjectParameters::clear(std::string key) {
        auto newkey = sanitizeKey(key);
        removeAll(newkey);
    }
    
    /**
     * Gets the first value assigned to the given key.
     * @param key the key
     * @return the value or null if the given key does not have any values
     */
    std::string VObjectParameters::first(std::string key) {
        std::vector<std::string> values = get(key);
        return (values.size() == 0) ? "" : values.front();
    }
    
    
    /**
     * Determines if a "quoted-printable encoding" parameter exists.
     * @return true if the parameter exists, false if not
     */
    bool VObjectParameters::isQuotedPrintable() {
        const std::string encoding[] {"ENCODING", ""};
        for (auto key : encoding) {
            std::vector<std::string> values = _get(key);
            if (values.empty()) {
                continue;
            }
            for (std::string value : values) {
                if (str_equals("QUOTED-PRINTABLE", value)) {
                    return true;
                }
            }
        }
        return false;
    }
    
    /**
     * Gets the CHARSET parameter.
     * @return the character set or null if a character set is not defined
     * @throws IllegalCharsetNameException if the character set name contains
     * illegal characters
     * @throws UnsupportedCharsetException if the local JVM does not recognized
     * the character set
     */
    Charset::Ptr VObjectParameters::getCharset() {
        auto charsetStr = first("CHARSET");
        return (charsetStr.empty()) ? nullptr : Charset::forName(charsetStr);
    }
    
    /**
     * Gets the map that backs this parameters list.
     * @return the map
     */
    std::unordered_map<std::string, std::vector<std::string>> VObjectParameters::getMap() const {
        return _multipmap;
    }
    
    //
    ///**
    // * Converts the given key to uppercase. Call this method before passing a
    // * key to the multimap.
    // * @param key the key
    // * @return the sanitized key
    // */
    std::string VObjectParameters::sanitizeKey(std::string key) {
        return str_to_upper(key);
    }
    
    
    
    void VObjectParameters::print() {
        
        for(auto elem : _multipmap)
        {
            std::cout << elem.first << " " << std::endl;
            auto list = elem.second;
            for (auto e : list) {
                std::cout << e << std::endl;
            }
        }
        
    }
    
    bool VObjectParameters::equals(const Ptr &obj) {
        if (obj == nullptr)
            return false;
        if (this == obj.get())
            return true;
        
        return _equals(*obj.get());
    }
    
    bool VObjectParameters::_equals(const VObjectParameters &rhs) {
        auto rmap = rhs.getMap();
        return _multipmap == rmap;
    }
    
    bool VObjectParameters::operator==(const VObjectParameters& rhs) {
        return _equals(rhs);
    }
    
    bool operator==(const VObjectParameters::Ptr& lhs, const VObjectParameters::Ptr& rhs) {
        return lhs->equals(rhs);
    }
    
    bool operator==(const std::vector<std::string>& lhs, const std::vector<std::string>& rhs) {
        return std::distance(lhs.begin(), lhs.end()) == std::distance(rhs.begin(), rhs.end()) && std::equal(lhs.begin(), lhs.end(), rhs.begin());
    }
    
    bool operator==(const std::unordered_map<std::string, std::vector<std::string>>& lhs,
                    const std::unordered_map<std::string, std::vector<std::string>>& rhs) {
        if (lhs.size() != rhs.size()) {
            return false;
        }
        
        auto pred = [] (decltype(*lhs.begin()) a, decltype(a) b)
        {
            if (a.first != b.first) {
                return false;
            }
            
            auto a_value = a.second;
            auto b_value = b.second;
            
            if (a_value.size() != b_value.size()) {
                return false;
            }
            
            auto pred_list = [] (decltype(*a_value.begin()) c, decltype(c) d)
            {
                return c == d;
            };
            
            if (!std::equal(a_value.begin(), a_value.end(), b_value.begin(), pred_list)) {
                return false;
            }
            
            return true;
        };
        
        if (!std::equal(lhs.begin(), lhs.end(), rhs.begin(), pred)) {
            return false;
        }
        
        return true;
    }
    
    
    //@Override
    //public String toString() {
    //    return multimap.toString();
    //}
    
    //@Override
    //public int hashCode() {
    //    return multimap.hashCode();
    //}
    //
    
}
