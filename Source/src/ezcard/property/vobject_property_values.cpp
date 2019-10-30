//
//  vobject_property_values.cpp
//  OpenPGP
//
//  Created by Yanfeng Zhang on 1/12/17.
//  Copyright © 2017 Yanfeng Zhang. All rights reserved.
//

#include "vobject_property_values.hpp"
#include <ezvcard/io/buffer.hpp>


//inital static vars
const std::string VObjectPropertyValues::NEWLINE = "\r\n";//System.getProperty("line.separator");



/**
 * <p>
 * Unescapes all escaped characters in a property value. Escaped newlines
 * are replaced with the local system's newline character sequence.
 * </p>
 * <p>
 * <b>Example:</b>
 * </p>
 *
 * <pre class="brush:java">
 * String value = "one\\,two\\;three\\nfour";
 * String unescaped = VObjectPropertyValues.unescape(value);
 * assertEquals("one,two;three\nfour", unescaped);
 * </pre>
 *
 * @param value the value to unescape
 * @return the unescaped value
 */
std::string VObjectPropertyValues::unescape(const std::string& value) {
    return unescape(value, 0, value.length());
}


/**
 * Unescapes all escaped characters in a substring.
 * @param string the entire string
 * @param start the start index of the substring to unescape
 * @param end the end index (exclusive) of the substring to unescape
 * @return the unescaped substring
 */
std::string VObjectPropertyValues::unescape(const std::string& string, int start, size_t end) {
    Buffer::Ptr sb     = nullptr;
    bool escaped       = false;
    for (int i = start; i < end; i++) {
        char c = string[i];
        if (escaped) {
            escaped = false;
            
            if (sb == nullptr) {
                sb = std::make_shared<Buffer>();
                sb->append(string.substr(start, (i - 1 - start)));
            }
            
            switch (c) {
                case 'n':
                case 'N':
                    sb->append(NEWLINE);
                    continue;
            }
            
            sb->append(c);
            continue;
        }
        
        switch (c) {
            case '\\':
                escaped = true;
                continue;
        }
        
        if (sb != nullptr) {
            sb->append(c);
        }
    }
    
    if (sb != nullptr) {
        return sb->get();
    }
    
    /*
     * The "String#substring" method makes no guarantee that the same String
     * object will be returned if the entire string length is passed into
     * the method.
     */
    if (start == 0 && end == string.length()) {
        return string;
    }
    
    return string.substr(start, end - start);
}

/**
 * <p>
 * Escapes all special characters within a property value. These characters
 * are:
 * </p>
 * <ul>
 * <li>backslashes ({@code \})</li>
 * <li>commas ({@code ,})</li>
 * <li>semi-colons ({@code ;})</li>
 * </ul>
 * <p>
 * Newlines are not escaped by this method. They are automatically escaped
 * by {@link VObjectWriter} when the data is serialized.
 * </p>
 * <p>
 * <b>Example:</b>
 * </p>
 *
 * <pre class="brush:java">
 * String value = "one,two;three\nfour";
 * String escaped = VObjectPropertyValues.escape(value);
 * assertEquals("one\\,two\\;three\nfour", escaped);
 * </pre>
 *
 * @param value the value to escape
 * @return the escaped value
 */
std::string VObjectPropertyValues::escape(const std::string& value) {
    std::stringstream ss("");
    bool set = false;
    for (int i = 0; i < value.size(); i++) {
        char c = value[i];
        switch (c) {
            case '\\':
            case ',':
            case ';':
                if (set == false) {
                    set = true;
                    ss << value.substr(0, i);
                }
                ss << '\\';
                ss << c;
                
                break;
            default:
                if (set != false) {
                    ss << c;
                }
                break;
        }
    }
    return (set != false) ? ss.str() : value;
}

/**
 * Escapes all special characters within the given string.
 * @param string the string to escape
 * @param escapeCommas true to escape comma characters, false not to.
 * Old-style syntax does not expect commas to be escaped in semi-structured
 * values.
 * @param sb the buffer on which to append the escaped string
 */

void VObjectPropertyValues::escape(std::string string, bool escapeCommas, std::stringstream& ss) {
    for (int i = 0; i < string.size(); i++) {
        char c = string[i];
        if (c == '\\' || c == ';' || (escapeCommas && c == ',')) {
            ss << '\\';
        }
        ss << c;
    }
}

/**
 * <p>
 * Parses a "list" property value.
 * </p>
 * <p>
 * List values contain multiple values separated by commas. The order that
 * the values are in usually doesn't matter.
 * </p>
 * <p>
 * <b>Example:</b>
 * </p>
 *
 * <pre class="brush:java">
 * String value = "one,two\\,three";
 * List&lt;String&gt; list = VObjectPropertyValues.parseList(value);
 * assertEquals(Arrays.asList("one", "two,three"), list);
 * </pre>
 *
 * @param value the value to parse
 * @return the parsed list
 */
std::vector<std::string> VObjectPropertyValues::parseList(const std::string& value) {
    return split(value, ',', -1);
}

/**
 * <p>
 * Generates a "list" property value.
 * </p>
 * <p>
 * List values contain multiple values separated by commas. The order that
 * the values are in usually doesn't matter.
 * </p>
 * <p>
 * Each list item's {@code toString()} method is called to generate its
 * string representation. If a list item is null, then "null" will be
 * outputted.
 * </p>
 * <p>
 * <b>Example:</b>
 * </p>
 *
 * <pre class="brush:java">
 * List&lt;String&gt; list = Arrays.asList("one", "two", null, "three,four");
 * String value = VObjectPropertyValues.writeList(list);
 * assertEquals("one,two,null,three\\,four", value);
 * </pre>
 *
 * @param values the values to write
 * @return the list value string
 */
std::string VObjectPropertyValues::writeList(std::vector<std::string> values) {
    std::stringstream ss("");
    
    bool first = true;
    for (auto value : values) {
        if (!first) {
            ss << ',';
        }
        
        //            if (value == null) {
        //                sb.append("null");
        if (value == "") {
            ss << ("");
        } else {
            escape(value, true, ss);
        }
        
        first = false;
    }
    
    return ss.str();
}

/**
 * <p>
 * Parses a "semi-structured" property value.
 * </p>
 * <p>
 * Semi-structured values contain multiple values separate by semicolons.
 * Unlike structured values, each value cannot have their own
 * comma-delimited list of sub-values. The order that the values are in
 * usually matters.
 * </p>
 * <p>
 * <b>Example:</b>
 * </p>
 *
 * <pre class="brush:java">
 * String value = "one;two\\;three,four";
 * List&lt;String&gt; values = VObjectPropertyValues.parseSemiStructured(value);
 * assertEquals(Arrays.asList("one", "two;three,four"), values);
 * </pre>
 *
 * @param value the value to parse
 * @return the parsed values
 */
std::vector<std::string> VObjectPropertyValues::parseSemiStructured(const std::string& value) {
    return parseSemiStructured(value, -1);
}

/**
 * <p>
 * Parses a "semi-structured" property value.
 * </p>
 * <p>
 * Semi-structured values contain multiple values separate by semicolons.
 * Unlike structured values, each value cannot have their own
 * comma-delimited list of sub-values. The order that the values are in
 * usually matters.
 * </p>
 * <p>
 * <b>Example:</b>
 * </p>
 *
 * <pre class="brush:java">
 * String value = "one;two;three";
 * List&lt;String&gt; values = VObjectPropertyValues.parseSemiStructured(value, 2);
 * assertEquals(Arrays.asList("one", "two;three"), values);
 * </pre>
 *
 * @param value the value to parse
 * @param limit the max number of items to parse
 * @return the parsed values
 */
std::vector<std::string> VObjectPropertyValues::parseSemiStructured(const std::string& value, int limit) {
    return split(value, ';', limit);
}

/**
 * <p>
 * Writes a "semi-structured" property value.
 * </p>
 * <p>
 * Semi-structured values contain multiple values separate by semicolons.
 * Unlike structured values, each value cannot have their own
 * comma-delimited list of sub-values. The order that the values are in
 * usually matters.
 * <p>
 * <b>Example:</b>
 * </p>
 *
 * <pre class="brush:java">
 * List&lt;String&gt; list = Arrays.asList("one", null, "two;three", "");
 *
 * String value = VObjectPropertyValues.writeSemiStructured(list, false);
 * assertEquals("one;null;two\\;three", value);
 *
 * value = VObjectPropertyValues.writeSemiStructured(list, true);
 * assertEquals("one;null;two\\;three;", value);
 * </pre>
 *
 * @param values the values to write
 * @param escapeCommas true to escape comma characters, false not to.
 * Old-style syntax does not expect commas to be escaped in semi-structured
 * values.
 * @param includeTrailingSemicolons true to include the semicolon delimiters
 * for empty values at the end of the values list, false to trim them
 * @return the semi-structured value string
 */
std::string VObjectPropertyValues::writeSemiStructured(std::vector<std::string> values, bool escapeCommas, bool includeTrailingSemicolons) {
    std::stringstream ss("");
    
    bool first = true;
    for (auto value : values) {
        if (!first) {
            ss << ';';
        }
        
        if (value == "") {
            ss << "";
        } else {
            escape(value, escapeCommas, ss);
        }
        
        first = false;
    }
    
    if (!includeTrailingSemicolons) {
        return trimTrailingSemicolons(ss);
    }
    
    return ss.str();
}


/**
 * <p>
 * Parses a "structured" property value.
 * </p>
 * <p>
 * Structured values are essentially 2-D arrays. They contain multiple
 * components separated by semicolons, and each component can have multiple
 * values separated by commas. The order that the components are in matters,
 * but the order that each component's list of values are in usually doesn't
 * matter.
 * </p>
 * <p>
 * <b>Example:</b>
 * </p>
 *
 * <pre class="brush:java">
 * String value = "one;two,three;four\\,five\\;six";
 * List&lt;List&lt;String&gt;&gt; values = VObjectPropertyValues.parseStructured(value);
 * assertEquals(Arrays.asList(
 *   Arrays.asList("one"),
 *   Arrays.asList("two", "three"),
 *   Arrays.asList("four,five;six")
 * ), values);
 * </pre>
 * @param value the value to parse
 * @return the parsed values
 */

std::vector<std::vector<std::string>> VObjectPropertyValues::parseStructured(const std::string& value) {
    std::vector<std::vector<std::string>> components;
    if (value.size() == 0) {
        return components; //return a mutable list
    }
    
    std::vector<std::string> curComponent;
    
    bool escaped = false;
    int cursor = 0;
    for (int i = 0; i < value.length(); i++) {
        if (escaped) {
            escaped = false;
            continue;
        }
        char c = value[i];
        switch (c) {
            case ';':
            {
                auto v = unescape(value, cursor, i);
                if (curComponent.empty() && v.length() == 0) {
                    /*
                     * If the component is empty, do not add an empty string to
                     * the list.
                     */
                } else {
                    curComponent.push_back(v);
                }
                
                components.push_back(curComponent);
                curComponent = std::vector<std::string>();
                //components.push_back(curComponent);
                cursor = i + 1;
                continue;
            }
            case ',':
            {
                auto v = unescape(value, cursor, i);
                curComponent.push_back(v);
                cursor = i + 1;
                continue;
            }
            case '\\':
            {
                escaped = true;
                continue;
            }
        }
    }
    
    auto v = unescape(value, cursor, value.size());
    if (curComponent.empty() && v.size() == 0) {
        /*
         * If the component is empty, do not add an empty string to the
         * list.
         */
    } else {
        curComponent.push_back(v);
        components.push_back(curComponent);
    }
    
    return components;
}


/**
 * <p>
 * Writes a "structured" property value.
 * </p>
 * <p>
 * Structured values are essentially 2-D arrays. They contain multiple
 * components separated by semicolons, and each component can have multiple
 * values separated by commas. The order that the components are in matters,
 * but the order that each component's list of values are in usually doesn't
 * matter.
 * </p>
 * <p>
 * The {@code toString()} method of each component value is called to
 * generate its string representation. If a value is null, then "null" will
 * be outputted.
 * </p>
 * <p>
 * <b>Example:</b>
 * </p>
 *
 * <pre class="brush:java">
 * List&lt;List&lt;?&gt;&gt; values = Arrays.asList(
 *   Arrays.asList("one"),
 *   Arrays.asList("two", "three", null),
 *   Arrays.asList("four,five;six"),
 *   Arrays.asList()
 * );
 *
 * String value = VObjectPropertyValues.writeStructured(values, false);
 * assertEquals("one;two,three,null;four\\,five\\;six", value);
 *
 * value = VObjectPropertyValues.writeStructured(values, true);
 * assertEquals("one;two,three,null;four\\,five\\;six;", value);
 * </pre>
 * @param components the components to write
 * @param includeTrailingSemicolons true to include the semicolon delimiters
 * for empty components at the end of the written value, false to trim them
 * @return the structured value string
 */
std::string VObjectPropertyValues::writeStructured(std::vector<std::vector<std::string>> components, bool includeTrailingSemicolons) {
    std::stringstream ss("");
    bool firstComponent = true;
    for (auto component : components) {
        if (!firstComponent) {
            ss << ';';
        }
        
        bool firstValue = true;
        for (std::string value : component) {
            if (!firstValue) {
                ss << ',';
            }
            if (value == "") {
                ss << "";
            } else {
                escape(value, true, ss);
            }
            firstValue = false;
        }
        
        firstComponent = false;
    }
    
    if (!includeTrailingSemicolons) {
        return trimTrailingSemicolons(ss);
    }
    return ss.str();
}

//    /**
//     * <p>
//     * Parses a "multimap" property value.
//     * </p>
//     * <p>
//     * Multimap values are collections of key/value pairs whose keys can be
//     * multi-valued. Key/value pairs are separated by semicolons. Values are
//     * separated by commas. Keys are converted to uppercase.
//     * </p>
//     * <p>
//     * <b>Example:</b>
//     * </p>
//     *
//     * <pre class="brush:java">
//     * String value = "one=two;THREE=four,five\\,six\\;seven";
//     * Map&lt;String, List&lt;String&gt;&gt; multimap = VObjectPropertyValues.parseMultimap(value);
//     * Map&lt;String, List&lt;String&gt;&gt; expected = new HashMap&lt;String, List&lt;String&gt;&gt;();
//     * expected.put("ONE", Arrays.asList("two"));
//     * expected.put("THREE", Arrays.asList("four", "five,six;seven"));
//     * assertEquals(expected, multimap);
//     * </pre>
//     *
//     * @param value the value to parse
//     * @return the parsed values
//     */
//    public static Map<String, List<String>> parseMultimap(String value) {
//        if (value.length() == 0) {
//            return new HashMap<String, List<String>>(0); //return a mutable map
//        }
//
//        Map<String, List<String>> multimap = new LinkedHashMap<String, List<String>>();
//        String curName = null;
//        List<String> curValues = new ArrayList<String>();
//
//        boolean escaped = false;
//        int cursor = 0;
//        for (int i = 0; i < value.length(); i++) {
//            if (escaped) {
//                escaped = false;
//                continue;
//            }
//
//            char c = value.charAt(i);
//
//            switch (c) {
//                case ';':
//                    if (curName == null) {
//                        curName = unescape(value, cursor, i).toUpperCase();
//                    } else {
//                        curValues.add(unescape(value, cursor, i));
//                    }
//
//                    if (curName.length() > 0) {
//                        if (curValues.isEmpty()) {
//                            curValues.add("");
//                        }
//                        List<String> existing = multimap.get(curName);
//                        if (existing == null) {
//                            multimap.put(curName, curValues);
//                        } else {
//                            existing.addAll(curValues);
//                        }
//                    }
//
//                    curName = null;
//                    curValues = new ArrayList<String>();
//                    cursor = i + 1;
//                    break;
//                case '=':
//                    if (curName == null) {
//                        curName = unescape(value, cursor, i).toUpperCase();
//                        cursor = i + 1;
//                    }
//                    break;
//                case ',':
//                    curValues.add(unescape(value, cursor, i));
//                    cursor = i + 1;
//                    break;
//                case '\\':
//                    escaped = true;
//                    break;
//            }
//        }
//
//        if (curName == null) {
//            curName = unescape(value, cursor, value.length()).toUpperCase();
//        } else {
//            curValues.add(unescape(value, cursor, value.length()));
//        }
//
//        if (curName.length() > 0) {
//            if (curValues.isEmpty()) {
//                curValues.add("");
//            }
//            List<String> existing = multimap.get(curName);
//            if (existing == null) {
//                multimap.put(curName, curValues);
//            } else {
//                existing.addAll(curValues);
//            }
//        }
//
//        return multimap;
//    }
//
//    /**
//     * <p>
//     * Writes a "multimap" property value.
//     * </p>
//     * <p>
//     * Multimap values are collections of key/value pairs whose keys can be
//     * multi-valued. Key/value pairs are separated by semicolons. Values are
//     * separated by commas. Keys are converted to uppercase.
//     * </p>
//     * <p>
//     * Each value's {@code toString()} method is called to generate its string
//     * representation. If a value is null, then "null" will be outputted.
//     * </p>
//     * <p>
//     * <b>Example:</b>
//     * </p>
//     *
//     * <pre class="brush:java">
//     * Map&lt;String, List&lt;?&gt;&gt; input = new LinkedHashMap&lt;String, List&lt;?&gt;&gt;();
//     * input.put("one", Arrays.asList("two"));
//     * input.put("THREE", Arrays.asList("four", "five,six;seven"));
//     *
//     * String value = VObjectPropertyValues.writeMultimap(input);
//     * assertEquals("ONE=two;THREE=four,five\\,six\\;seven", value);
//     * </pre>
//     *
//     * @param multimap the multimap to write
//     * @return the multimap value string
//     */
//    public static String writeMultimap(Map<String, ? extends List<?>> multimap) {
//        StringBuilder sb = new StringBuilder();
//        boolean firstKey = true;
//        for (Map.Entry<String, ? extends List<?>> entry : multimap.entrySet()) {
//            if (!firstKey) {
//                sb.append(';');
//            }
//
//            String key = entry.getKey().toUpperCase();
//            escape(key, true, sb);
//
//            List<?> values = entry.getValue();
//            if (values.isEmpty()) {
//                continue;
//            }
//
//            sb.append('=');
//
//            boolean firstValue = true;
//            for (Object value : values) {
//                if (!firstValue) {
//                    sb.append(',');
//                }
//
//                if (value == null) {
//                    sb.append("null");
//                } else {
//                    escape(value.toString(), true, sb);
//                }
//
//                firstValue = false;
//            }
//
//            firstKey = false;
//        }
//
//        return sb.toString();
//    }

/**
 * Removes trailing semicolon characters from the end of the given buffer.
 * @param sb the buffer
 */
std::string VObjectPropertyValues::trimTrailingSemicolons(const std::stringstream& ss) {
    auto value = ss.str();
    int index = -1;
    int size = (int)value.size();
    for (int i = size - 1; i >= 0; i--) {
        char c = value[i];
        if (c != ';') {
            index = i;
            break;
        }
    }
    return std::string(value, 0, index+1);
    //    sb.setLength(index + 1);
}

/**
 * Splits a string.
 * @param string the string to split
 * @param delimiter the delimiter to split by
 * @param limit the number of split values to parse or -1 to parse them all
 * @return the split values
 */
std::vector<std::string> VObjectPropertyValues::split(const std::string& string, char delimiter, int limit) {
    if (string.size() == 0) {
        return {}; //return a mutable list
    }
    
    std::vector<std::string> list;
    bool escaped = false;
    int cursor = 0;
    for (int i = 0; i < string.length(); i++) {
        char ch = string[i];
        
        if (escaped) {
            escaped = false;
            continue;
        }
        
        if (ch == delimiter) {
            auto value = unescape(string, cursor, i);
            list.push_back(value);
            
            cursor = i + 1;
            if (limit > 0 && list.size() == limit - 1) {
                break;
            }
            
            continue;
        }
        
        switch (ch) {
            case '\\':
                escaped = true;
                continue;
        }
    }
    
    auto value = unescape(string, cursor, string.length());
    list.push_back(value);
    
    return list;
}

//
//    /**
//     * <p>
//     * Helper class for building "semi-structured" property values.
//     * </p>
//     * <p>
//     * Semi-structured values contain multiple values separate by semicolons.
//     * Unlike structured values, each value cannot have their own
//     * comma-delimited list of sub-values. The order that the values are in
//     * usually matters.
//     * </p>
//     * <p>
//     * <b>Example:</b>
//     * </p>
//     *
//     * <pre class="brush:java">
//     * SemiStructuredValueBuilder b = new SemiStructuredValueBuilder();
//     * b.append("one").append(null).append("two").append("");
//     * assertEquals("one;;two;", b.build());
//     * assertEquals("one;;two", b.build(false));
//     * </pre>
//     */
//    public static class SemiStructuredValueBuilder {
//        private final List<Object> values = new ArrayList<Object>();
//
//        /**
//         * Appends a value to the semi-structured value. The value's
//         * {@code toString()} method will be called to generate its string
//         * representation. If the value is null, then an empty string will be
//         * appended.
//         * @param value the value
//         * @return this
//         */
//        public SemiStructuredValueBuilder append(Object value) {
//            if (value == null) {
//                value = "";
//            }
//            values.add(value);
//            return this;
//        }
//
//        /**
//         * Builds the semi-structured value string.
//         * @param escapeCommas true to escape comma characters, false not to.
//         * Old-style syntax does not expect commas to be escaped in
//         * semi-structured values.
//         * @param includeTrailingSemicolons true to include the semicolon
//         * delimiters of empty values at the end of the value string, false to
//         * trim them
//         * @return the semi-structured value string
//         */
//        public String build(boolean escapeCommas, boolean includeTrailingSemicolons) {
//            return writeSemiStructured(values, escapeCommas, includeTrailingSemicolons);
//        }
//    }
//
//    /**
//     * <p>
//     * Helper class for building "structured" property values.
//     * </p>
//     * <p>
//     * Structured values are essentially 2-D arrays. They contain multiple
//     * components separated by semicolons, and each component can have multiple
//     * values separated by commas. The order that the components are in matters,
//     * but the order that each component's list of values are in usually doesn't
//     * matter.
//     * </p>
//     * <p>
//     * <b>Example:</b>
//     * </p>
//     *
//     * <pre class="brush:java">
//     * StructuredValueBuilder b = new StructuredValueBuilder();
//     * b.append("one").append(Arrays.asList("two", "three")).append("");
//     * assertEquals("one;two,three;", b.build());
//     * assertEquals("one;two,three", b.build(false));
//     * </pre>
//     */
//    public static class StructuredValueBuilder {
//        private final List<List<?>> components = new ArrayList<List<?>>();
//
//        /**
//         * Appends a single-valued component. The value's {@code toString()}
//         * method will be called to generate its string representation. If the
//         * value is null, then an empty component will be appended.
//         * @param value the value
//         * @return this
//         */
//        public StructuredValueBuilder append(Object value) {
//            List<Object> component = (value == null) ? Arrays.<Object> asList() : Arrays.asList(value);
//            return append(component);
//        }
//
//        /**
//         * Appends a component. The {@code toString()} method of each component
//         * value will be called to generate its string representation. If a
//         * value is null, then "null" will be outputted.
//         * @param component the component
//         * @return this
//         */
//        public StructuredValueBuilder append(List<?> component) {
//            if (component == null) {
//                component = Arrays.<Object> asList();
//            }
//            components.add(component);
//            return this;
//        }
//
//        /**
//         * Builds the structured value string. Trailing semicolon delimiters
//         * will not be trimmed.
//         * @return the structured value string
//         */
//        public String build() {
//            return build(true);
//        }
//
//        /**
//         * Builds the structured value string.
//         * @param includeTrailingSemicolons true to include the semicolon
//         * delimiters for empty components at the end of the value string, false
//         * to trim them
//         * @return the structured value string
//         */
//        public String build(boolean includeTrailingSemicolons) {
//            return writeStructured(components, includeTrailingSemicolons);
//        }
//    }
//
//    private VObjectPropertyValues() {
//        //hide
//    }
//}
