//
//  vobject_property_values.hpp
//  OpenPGP
//
//  Created by Yanfeng Zhang on 1/12/17.
//  Copyright © 2017 Yanfeng Zhang. All rights reserved.
//

#ifndef vobject_property_values_hpp
#define vobject_property_values_hpp

#include <stdio.h>
#include <string>
#include <vector>



class VObjectPropertyValues {
    
private:
    // CR+LF
    const static std::string NEWLINE;
    static std::string unescape(const std::string& string, int start, size_t end);
    static void escape(std::string string, bool escapeCommas, std::stringstream& ss);
    static std::string trimTrailingSemicolons(const std::stringstream& ss);
    
public:
    
    static std::string unescape(const std::string& value);
    static std::string escape(const std::string& value);
    
    static std::vector<std::string> parseList(const std::string& value);
    static std::vector<std::string> parseSemiStructured(const std::string& value);
    static std::vector<std::string> parseSemiStructured(const std::string& value, int limit);
    static std::vector<std::vector<std::string>> parseStructured(const std::string& value);
    static std::string writeSemiStructured(std::vector<std::string> values, bool escapeCommas, bool includeTrailingSemicolons);
    static std::string writeStructured(std::vector<std::vector<std::string>> components, bool includeTrailingSemicolons);
    static std::string writeList(std::vector<std::string> values);
    //       public static Map<String, List<String>> parseMultimap(String value) {
    //           public static String writeMultimap(Map<String, ? extends List<?>> multimap) {
    static std::vector<std::string> split(const std::string& string, char delimiter, int limit);
    
    
};


class SemiStructuredValueIterator {
private:
    std::vector<std::string> parsedList;
    std::vector<std::string>::iterator it;
    bool isFirst = false;
    
    
public:
    /**
     * Constructs a new semi-structured value iterator.
     * @param value the value to parse
     */
    SemiStructuredValueIterator(std::string value) : SemiStructuredValueIterator(value, -1)  {

    }
    
    /**
     * Constructs a new semi-structured value iterator.
     * @param value the value to parse
     * @param limit the number of values to parse, or -1 to parse all values
     */
    SemiStructuredValueIterator(std::string value, int limit) {
        parsedList = VObjectPropertyValues::parseSemiStructured(value, limit);
        it = parsedList.begin();
        isFirst = true;
    }
    
    /**
     * Gets the next value.
     * @return the next value or null if the value is empty or null if there
     * are no more values
     */
    std::string next() {
        std::string out = "";
        if (!hasNext()) {
            return out;
        }
        if (it == parsedList.begin() && isFirst) {
            out = *it;
            isFirst = false;
            return out;
        }
        auto next = std::next(it, 1);
        if (next == parsedList.end()) {
            return out;
        }
        it = next;
        out = *next;
        return out;
    }
    
    /**
     * Determines if there are any more values left.
     * @return true if there are more values, false if not
     */
    bool hasNext() {
        if (parsedList.size() == 0) {
            return false;
        }
        if (parsedList.begin() == it && isFirst == true) {
            return true;
        }
        return std::next(it, 1) != parsedList.end();
    }
};



/**
 * <p>
 * Helper class for iterating over the values in a "structured" property
 * value.
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
 * String value = "one;two,three;;;four";
 * StructuredValueIterator it = new StructuredValueIterator(value);
 *
 * assertEquals(Arrays.asList("one"), it.nextComponent());
 * assertEquals(Arrays.asList("two", "three"), it.nextComponent());
 * assertEquals(Arrays.asList(), it.nextComponent());
 * assertNull(it.nextValue());
 * assertEquals("four", it.nextValue());
 * assertFalse(it.hasNext());
 * </pre>
 */
class StructuredValueIterator {
private:
    std::vector<std::vector<std::string>> parsedList;
    std::vector<std::vector<std::string>>::iterator it;
    bool isFirst = false;
    
public:
    /**
     * Constructs a new structured value iterator.
     * @param string the structured value to parse
     */
    StructuredValueIterator(const std::string& string) {
        auto list = VObjectPropertyValues::parseStructured(string);
        parsedList = list;
        it = parsedList.begin();
        isFirst = true;
    }
    
    /**
     * Constructs a new structured value iterator.
     * @param components the components to iterator over
     */
    StructuredValueIterator(std::vector<std::vector<std::string>> components) {
        parsedList = components;
        it = parsedList.begin();
        isFirst = true;
    }
    
    /**
     * Gets the first value of the next component.
     * @return the value or null if the component is empty or null if there
     * are no more components
     */
    std::string nextValue() {
        if (!hasNext()) {
            return "";
        }
        std::vector<std::string> list = nextComponent();
        return list.empty() ? "" : list[0];
    }
    
    std::vector<std::string> nextComponent() {
        std::vector<std::string> out;
        if (!hasNext()) {
            return out;
        }
        if (it == parsedList.begin() && isFirst) {
            out = *it;
            isFirst = false;
            return out;
        }
        auto next = std::next(it, 1);
        if (next == parsedList.end()) {
            return out;
        }
        it = next;
        out = *next;
        return out;
    }
    
    bool hasNext() {
        if (parsedList.size() == 0) {
            return false;
        }
        if (parsedList.begin() == it && isFirst == true) {
            return true;
        }
        return std::next(it, 1) != parsedList.end();
    }
};


//    /**
//     * <p>
//     * Helper class for iterating over the values in a "structured" property
//     * value.
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
//     * String value = "one;two,three;;;four";
//     * StructuredValueIterator it = new StructuredValueIterator(value);
//     *
//     * assertEquals(Arrays.asList("one"), it.nextComponent());
//     * assertEquals(Arrays.asList("two", "three"), it.nextComponent());
//     * assertEquals(Arrays.asList(), it.nextComponent());
//     * assertNull(it.nextValue());
//     * assertEquals("four", it.nextValue());
//     * assertFalse(it.hasNext());
//     * </pre>
//     */
//    public static class StructuredValueIterator {
//        private final Iterator<List<String>> it;
//
//        /**
//         * Constructs a new structured value iterator.
//         * @param string the structured value to parse
//         */
//        public StructuredValueIterator(String string) {
//            this(parseStructured(string));
//        }
//
//        /**
//         * Constructs a new structured value iterator.
//         * @param components the components to iterator over
//         */
//        public StructuredValueIterator(List<List<String>> components) {
//            it = components.iterator();
//        }
//
//        /**
//         * Gets the first value of the next component.
//         * @return the value or null if the component is empty or null if there
//         * are no more components
//         */
//        public String nextValue() {
//            if (!hasNext()) {
//                return null;
//            }
//
//            List<String> list = it.next();
//            return list.isEmpty() ? null : list.get(0);
//        }
//
//        /**
//         * Gets the next component.
//         * @return the next component or an empty list if there are no more
//         * components
//         */
//        public List<String> nextComponent() {
//            if (!hasNext()) {
//                return new ArrayList<String>(0); //should be mutable
//            }
//
//            return it.next();
//        }
//
//        public boolean hasNext() {
//            return it.hasNext();
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
//    private VObjectPropertyValues() {
//        //hide
//    }
//}


class StructuredValueBuilder {
private:
    std::vector<std::vector<std::string>> _components;
    
    
public:
    /**
     * Appends a single-valued component. The value's {@code toString()}
     * method will be called to generate its string representation. If the
     * value is null, then an empty component will be appended.
     * @param value the value
     * @return this
     */
    void append(const std::string& value) {
        _components.push_back({value});
    }
    
    /**
     * Appends a component. The {@code toString()} method of each component
     * value will be called to generate its string representation. If a
     * value is null, then "null" will be outputted.
     * @param component the component
     * @return this
     */
    void append(const std::vector<std::string>& component) {
        _components.push_back(component);
    }
    
    /**
     * Builds the structured value string. Trailing semicolon delimiters
     * will not be trimmed.
     * @return the structured value string
     */
    std::string build() {
        return build(true);
    }
    
    /**
     * Builds the structured value string.
     * @param includeTrailingSemicolons true to include the semicolon
     * delimiters for empty components at the end of the value string, false
     * to trim them
     * @return the structured value string
     */
    std::string build(bool includeTrailingSemicolons) {
        return VObjectPropertyValues::writeStructured(_components, includeTrailingSemicolons);
    }
};

/**
 * <p>
 * Helper class for building "semi-structured" property values.
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
 * SemiStructuredValueBuilder b = new SemiStructuredValueBuilder();
 * b.append("one").append(null).append("two").append("");
 * assertEquals("one;;two;", b.build());
 * assertEquals("one;;two", b.build(false));
 * </pre>
 */

class SemiStructuredValueBuilder {
private:
    std::vector<std::string> _values = {};
    
    /**
     * Appends a value to the semi-structured value. The value's
     * {@code toString()} method will be called to generate its string
     * representation. If the value is null, then an empty string will be
     * appended.
     * @param value the value
     * @return this
     */
public:
    SemiStructuredValueBuilder() {
        
    }
    
    void append(const std::string& value) {
        _values.push_back(value);
    }
    
    /**
     * Builds the semi-structured value string.
     * @param escapeCommas true to escape comma characters, false not to.
     * Old-style syntax does not expect commas to be escaped in
     * semi-structured values.
     * @param includeTrailingSemicolons true to include the semicolon
     * delimiters of empty values at the end of the value string, false to
     * trim them
     * @return the semi-structured value string
     */
    std::string build(bool escapeCommas, bool includeTrailingSemicolons) {
        return VObjectPropertyValues::writeSemiStructured(_values, escapeCommas, includeTrailingSemicolons);
    }
};


#endif /* vobject_property_values_hpp */
