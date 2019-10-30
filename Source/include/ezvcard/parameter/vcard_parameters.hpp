//
//  vcard_parameters.hpp
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

#ifndef vcard_parameters_hpp
#define vcard_parameters_hpp

#include <stdio.h>
#include <unordered_map>
#include <string>
#include <map>
#include <vector>
#include "vcard_version.hpp"
#include "validation_warnings.hpp"
#include "geo_uri.hpp"
#include <set>
#include "calscale.hpp"
#include "list_multi_map.hpp"
#include "encoding.hpp"
#include "vcard_data_type.hpp"

namespace ezvcard {


class VCardParameters : public ListMultimap<std::string, std::string> {
    
private:
    std::map<std::string, std::set<VCardVersion::Ptr>> _supportedVersions;
    
    bool isPidValid(const std::string& pid);
    
    bool _equals(const VCardParameters& obj);

public:
    typedef std::shared_ptr<VCardParameters> Ptr;
    
    const static std::string ALTID;
    const static std::string CALSCALE;
    const static std::string CHARSET;
    const static std::string ENCODING;
    const static std::string GEO;
    const static std::string INDEX;
    const static std::string LABEL;
    const static std::string LANGUAGE;
    const static std::string LEVEL;
    const static std::string MEDIATYPE;
    const static std::string PID;
    const static std::string PREF;
    const static std::string SORT_AS;
    const static std::string TYPE;
    const static std::string TZ;
    const static std::string VALUE;
    

    /**
     * Creates a list of parameters.
     */
    VCardParameters();
    
    /**
     * Creates a copy of an existing parameter list.
     * @param origMap the object to copy
     */
    VCardParameters(const std::unordered_map<std::string, std::vector<std::string>>& origMap);
    VCardParameters(const VCardParameters::Ptr& orig);
    
    
    std::list<ValidationWarning::Ptr> validate(const VCardVersion::Ptr& version);
    
    GeoUri::Ptr getGeo();    
    int getIndex();
    void setIndex(int index);
    //std::list<Pid> getPids();
    int getPref();
    void setPref(int pref);

    Calscale::Ptr getCalscale();
    void setCalscale(const Calscale::Ptr& calscale);
    void setEncoding(const Encoding::Ptr& encoding);
    Encoding::Ptr getEncoding();

    VCardDataType::Ptr getValue();
    void setValue(const VCardDataType::Ptr& dataType);
    
    std::string getLabel();
    void setLabel(std::string label);
    
    
    void Print();
    
    std::string getAltId();
    void setAltId(const std::string& altId);

    std::string getCharset();
    void setCharset(const std::string& charset);

    
//    public void setGeo(GeoUri uri) {
//        replace(GEO, (uri == null) ? null : uri.toString());
//    }
    

//    
//    public String getLanguage() {
//        return first(LANGUAGE);
//    }
//    
//    public void setLanguage(String language) {
//        replace(LANGUAGE, language);
//    }
//    public String getLevel() {
//        return first(LEVEL);
//    }
//    
//    public void setLevel(String level) {
//        replace(LEVEL, level);
//    }

//    public void addPid(Pid pid) {
//        put(PID, pid.toString());
//    }
//
//    public void removePid(Pid pid) {
//        String value = pid.toString();
//        remove(PID, value);
//    }
//
//    public void removePids() {
//        removeAll(PID);
//    }
//
//    public List<String> getSortAs() {
//        return get(SORT_AS);
//    }
    
//    public void setSortAs(String... sortStrings) {
//        removeAll(SORT_AS);
//        putAll(SORT_AS, Arrays.asList(sortStrings));
//    }


//
//    public void removeType(String type) {
//        remove(TYPE, type);
//    }
    void addType(const std::string& type);
    void setType(const std::string& type);
    std::vector<std::string> getTypes();
    std::string getType();
    std::string getMediaType();
    void setMediaType(const std::string& mediaType);
    
    
//
//    public String getTimezone() {
//        return first(TZ);
//    }
//
//    public void setTimezone(String timezone) {
//        replace(TZ, timezone);
//    }

//    @Override
//    protected String sanitizeKey(String key) {
//        return (key == null) ? null : key.toUpperCase();
//    }
//    
//    @Override
//    public int hashCode() {
//        /*
//         * Remember: Keys are case-insensitive, key order does not matter, and
//         * value order does not matter
//         */
//        final int prime = 31;
//        int result = 1;
//        
//        for (Map.Entry<String, List<String>> entry : this) {
//            String key = entry.getKey();
//            List<String> value = entry.getValue();
//            
//            int valueHash = 1;
//            for (String v : value) {
//                valueHash += v.toLowerCase().hashCode();
//            }
//            
//            int entryHash = 1;
//            entryHash += prime * entryHash + ((key == null) ? 0 : key.toLowerCase().hashCode());
//            entryHash += prime * entryHash + valueHash;
//            
//            result += entryHash;
//        }
//        
//        return result;
//    }
//    
//    /**
//     * <p>
//     * Determines whether the given object is logically equivalent to this list
//     * of vCard parameters.
//     * </p>
//     * <p>
//     * vCard parameters are case-insensitive. Also, the order in which they are
//     * defined does not matter.
//     * </p>
//     * @param obj the object to compare to
//     * @return true if the objects are equal, false if not
//     */
//    @Override
//    public boolean equals(Object obj) {
//        /*
//         * Remember: Keys are case-insensitive, key order does not matter, and
//         * value order does not matter
//         */
//        if (this == obj) return true;
//        if (obj == null) return false;
//        if (getClass() != obj.getClass()) return false;
//        
//        VCardParameters other = (VCardParameters) obj;
//        if (size() != other.size()) return false;
//        
//        for (Map.Entry<String, List<String>> entry : this) {
//            String key = entry.getKey();
//            List<String> value = entry.getValue();
//            List<String> otherValue = other.get(key);
//            
//            if (value.size() != otherValue.size()) {
//                return false;
//            }
//            
//            List<String> valueLower = new ArrayList<String>(value.size());
//            for (String v : value) {
//                valueLower.add(v.toLowerCase());
//            }
//            Collections.sort(valueLower);
//            
//            List<String> otherValueLower = new ArrayList<String>(otherValue.size());
//            for (String v : otherValue) {
//                otherValueLower.add(v.toLowerCase());
//            }
//            Collections.sort(otherValueLower);
//            
//            if (!valueLower.equals(otherValueLower)) {
//                return false;
//            }
//        }
//        
//        return true;
//    }
//    
//    /**
//     * <p>
//     * A list that converts the raw string values of a TYPE parameter to the
//     * appropriate {@link VCardParameter} object that some parameters use.
//     * </p>
//     * <p>
//     * This list is backed by the {@link VCardParameters} object. Any changes
//     * made to the list will affect the {@link VCardParameters} object and vice
//     * versa.
//     * </p>
//     * @param <T> the parameter class
//     */
//    public abstract class TypeParameterList<T extends VCardParameter> extends EnumParameterList<T> {
//        public TypeParameterList() {
//            super(TYPE);
//        }
//    }
//    
//    /**
//     * <p>
//     * A list that converts the raw string values of a parameter to the
//     * appropriate {@link VCardParameter} object that some parameters use.
//     * </p>
//     * <p>
//     * This list is backed by the {@link VCardParameters} object. Any changes
//     * made to the list will affect the {@link VCardParameters} object and vice
//     * versa.
//     * </p>
//     * @param <T> the parameter class
//     */
//    public abstract class EnumParameterList<T extends VCardParameter> extends VCardParameterList<T> {
//        public EnumParameterList(String parameterName) {
//            super(parameterName);
//        }
//        
//        @Override
//        protected String _asString(T value) {
//            return value.getValue();
//        }
//    }
//    
//    /**
//     * <p>
//     * A list that converts the raw string values of a parameter to another kind
//     * of value (for example, Integers).
//     * </p>
//     * <p>
//     * This list is backed by the {@link VCardParameters} object. Any changes
//     * made to the list will affect the {@link VCardParameters} object and vice
//     * versa.
//     * </p>
//     * <p>
//     * If a String value cannot be converted to the appropriate data type, an
//     * {@link IllegalStateException} is thrown.
//     * </p>
//     */
//    public abstract class VCardParameterList<T> extends AbstractList<T> {
//        protected final String parameterName;
//        protected final List<String> parameterValues;
//        
//        /**
//         * @param parameterName the name of the parameter (case insensitive)
//         */
//        public VCardParameterList(String parameterName) {
//            this.parameterName = parameterName;
//            parameterValues = VCardParameters.this.get(parameterName);
//        }
//        
//        @Override
//        public void add(int index, T value) {
//            String valueStr = _asString(value);
//            parameterValues.add(index, valueStr);
//        }
//        
//        @Override
//        public T remove(int index) {
//            String removed = parameterValues.remove(index);
//            return asObject(removed);
//        }
//        
//        @Override
//        public T get(int index) {
//            String value = parameterValues.get(index);
//            return asObject(value);
//        }
//        
//        @Override
//        public T set(int index, T value) {
//            String valueStr = _asString(value);
//            String replaced = parameterValues.set(index, valueStr);
//            return asObject(replaced);
//        }
//        
//        @Override
//        public int size() {
//            return parameterValues.size();
//        }
//        
//        private T asObject(String value) {
//            try {
//                return _asObject(value);
//            } catch (Exception e) {
//                throw _exception(value, e);
//            }
//        }
//        
//        /**
//         * Converts the object to a String value for storing in the
//         * {@link VCardParameters} object.
//         * @param value the value
//         * @return the string value
//         */
//        protected abstract String _asString(T value);
//        
//        /**
//         * Converts a String value to its object form.
//         * @param value the string value
//         * @return the object
//         * @throws Exception if there is a problem parsing the string
//         */
//        protected abstract T _asObject(String value) throws Exception;
//        
//        /**
//         * Creates the exception that is thrown when the raw string value cannot
//         * be parsed into its object form.
//         * @param value the raw string value
//         * @param thrown the thrown exception
//         * @return the exception to throw
//         */
//        protected IllegalStateException _exception(String value, Exception thrown) {
//            return new IllegalStateException(Messages.INSTANCE.getExceptionMessage(26, parameterName), thrown);
//        }
    //    }
    
    bool operator==(const VCardParameters& rhs);
    bool equals(const Ptr& obj);
};

bool operator==(const VCardParameters::Ptr& lhs, const VCardParameters::Ptr& rhs);


}

#endif /* vcard_parameters_hpp */
