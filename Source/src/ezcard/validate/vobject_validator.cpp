//
//  vobject_validator.cpp
//  OpenPGP
//
//  Created by Yanfeng Zhang on 1/13/17.
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


#include "vobject_validator.hpp"


VObjectValidator::Ptr VObjectValidator::single = nullptr;
VObjectValidator::VObjectValidator() {

    
    //old
    {
        auto syntax = SyntaxStyle::OLD;
        std::map<bool, AllowedCharacters::Ptr> map;
        {
            AllowedCharactersBuilder builder;
            builder.allowAll();
            builder.except("\r\n:.;");
            map.insert(std::make_pair(false, builder.build()));
        }
        {
            AllowedCharactersBuilder builder;
            builder.allowPrintable();
            builder.except("[]=:.,");
            /*
             * Note: The specification's formal grammar allows semicolons to
             * be present in property name. This may be a mistake because
             * this would break the syntax. This validator will treat
             * semicolons as invalid in this context.
             *
             * The specifications state that semicolons can be included in
             * parameter values by escaping them with a backslash--however,
             * the specification is not clear as to whether this is also
             * permitted in property names.
             *
             * vCard 2.1: Section 2.1.2
             * vCal 1.0: Section 2, "Property" sub-heading
             */
            builder.except(';');
            map.insert(std::make_pair(true, builder.build()));
        }
        VObjectValidator::propertyName.insert(std::make_pair(syntax, map));
    }
    
    //new
    {
        auto syntax = SyntaxStyle::NEW;
        std::map<bool, AllowedCharacters::Ptr> map;
        {
            AllowedCharactersBuilder builder;
            map.insert(std::make_pair(false, VObjectValidator::propertyName.at(SyntaxStyle::OLD).at(false)));
        }
        {
            AllowedCharactersBuilder builder;
            builder.allow('A', 'Z');
            builder.allow('a', 'z');
            builder.allow('0', '9');
            builder.allow('-');
            map.insert(std::make_pair(true, builder.build()));
        }
        VObjectValidator::propertyName.insert(std::make_pair(syntax, map));
    }
    group = propertyName;
    
    //old
    {
        auto syntax = SyntaxStyle::OLD;
        std::map<bool, AllowedCharacters::Ptr> map;
        {
            AllowedCharactersBuilder builder;
            builder.allowAll();
            builder.except("\r\n:;=");
            map.insert(std::make_pair(false, builder.build()));
        }
        {
            //same as property name
            map.insert(std::make_pair(true, VObjectValidator::propertyName.at(syntax).at(true)));
        }
        VObjectValidator::parameterName.insert(std::make_pair(syntax, map));
    }
    //new
    {
        auto syntax = SyntaxStyle::NEW;
        std::map<bool, AllowedCharacters::Ptr> map;
        {
            //same as old style syntax
            map.insert(std::make_pair(false, VObjectValidator::parameterName.at(SyntaxStyle::OLD).at(false)));
        }
        {
            //same as property name
            map.insert(std::make_pair(true, propertyName.at(syntax).at(false)));
        }
        VObjectValidator::parameterName.insert(std::make_pair(syntax, map));
    }
    
    
    //old
    {
        auto syntax = SyntaxStyle::OLD;
        std::map<bool, std::map<bool, AllowedCharacters::Ptr>> map;
        auto caretEncoding = false;
        {
            std::map<bool, AllowedCharacters::Ptr> map2;
            auto strict = false;
            {
                AllowedCharactersBuilder builder;
                builder.allowAll();
                builder.except("\r\n:");
                map2.insert(std::make_pair(strict, builder.build()));
            }
            strict = true;
            {
                //same as parameter name, except semicolons are allowed
                AllowedCharacters::Ptr paramName = parameterName.at(syntax).at(strict);
                
                AllowedCharactersBuilder builder(paramName);
                builder.allow(';');
                map2.insert(std::make_pair(strict, builder.build()));
            }
            map.insert(std::make_pair(caretEncoding, map2));
        }
        caretEncoding = true;
        {
            /*
             * Same as when caret encoding is disabled because
             * old style syntax does not support caret encoding.
             */
            map.insert(std::make_pair(caretEncoding, map.at(false)));
        }
        parameterValue.insert(std::make_pair(syntax, map));
    }

    {
        auto syntax = SyntaxStyle::NEW;
        std::map<bool, std::map<bool, AllowedCharacters::Ptr>> map;
        auto caretEncoding = false;
        {
            std::map<bool, AllowedCharacters::Ptr> map2;
            auto strict = false;
            {
                AllowedCharactersBuilder builder;
                builder.allowAll();
                builder.except("\r\n\"");
                map2.insert(std::make_pair(strict, builder.build()));
            }
            strict = true;
            {
                AllowedCharactersBuilder builder;
                builder.allowPrintable();
                builder.allowNonAscii();
                builder.allow('\t');
                builder.except('"');
                map2.insert(std::make_pair(strict, builder.build()));
            }
            map.insert(std::make_pair(caretEncoding, map2));
        }
        caretEncoding = true;
        {
            std::map<bool, AllowedCharacters::Ptr> map2;
            auto strict = false;
            {
                AllowedCharactersBuilder builder;
                builder.allowAll();
                map2.insert(std::make_pair(strict, builder.build()));
            }
            strict = true;
            {
                AllowedCharactersBuilder builder;
                builder.allowPrintable();
                builder.allowNonAscii();
                builder.allow("\r\n\t");
                map2.insert(std::make_pair(strict, builder.build()));
            }
            map.insert(std::make_pair(caretEncoding, map2));
        }
        parameterValue.insert(std::make_pair(syntax, map));
    }
}

VObjectValidator::~VObjectValidator() {
    
}

VObjectValidator::Ptr VObjectValidator::get() {
    if(single == nullptr )
        single = std::shared_ptr<VObjectValidator>(new VObjectValidator());
    
    return single;
}

//
//public class VObjectValidator {
//
//    private static final Map<SyntaxStyle, Map<Boolean, AllowedCharacters>> group = propertyName;
//
//    private static final Map<SyntaxStyle, Map<Boolean, AllowedCharacters>> parameterName = new EnumMap<SyntaxStyle, Map<Boolean, AllowedCharacters>>(SyntaxStyle.class);
//    static {
//        boolean strict;
//        SyntaxStyle syntax;
//        
//        syntax = SyntaxStyle.OLD;
//        {
//            Map<Boolean, AllowedCharacters> map = new HashMap<Boolean, AllowedCharacters>();
//            strict = false;
//            {
//                //@formatter:off
//                map.put(strict, new AllowedCharacters.Builder()
//                        .allowAll()
//                        .except("\r\n:;=")
//                        .build());
//                //@formatter:on
//            }
//            
//            strict = true;
//            {
//                //same as property name
//                map.put(strict, propertyName.get(syntax).get(strict));
//            }
//            
//            parameterName.put(syntax, map);
//        }
//        
//        syntax = SyntaxStyle.NEW;
//        {
//            Map<Boolean, AllowedCharacters> map = new HashMap<Boolean, AllowedCharacters>();
//            strict = false;
//            {
//                //same as old style syntax
//                map.put(strict, parameterName.get(SyntaxStyle.OLD).get(strict));
//            }
//            
//            strict = true;
//            {
//                //same as property name
//                map.put(strict, propertyName.get(syntax).get(strict));
//            }
//            
//            parameterName.put(syntax, map);
//        }
//    }
//    
//    private static final Map<SyntaxStyle, Map<Boolean, Map<Boolean, AllowedCharacters>>> parameterValue = new EnumMap<SyntaxStyle, Map<Boolean, Map<Boolean, AllowedCharacters>>>(SyntaxStyle.class);
//    static {
//        boolean strict, caretEncoding;
//        SyntaxStyle syntax;
//        
//        syntax = SyntaxStyle.OLD;
//        {
//            Map<Boolean, Map<Boolean, AllowedCharacters>> map = new HashMap<Boolean, Map<Boolean, AllowedCharacters>>();
//            caretEncoding = false;
//            {
//                Map<Boolean, AllowedCharacters> map2 = new HashMap<Boolean, AllowedCharacters>();
//                strict = false;
//                {
//                    //@formatter:off
//                    map2.put(strict, new AllowedCharacters.Builder()
//                             .allowAll()
//                             .except("\r\n:")
//                             .build());
//                    //@formatter:on
//                }
//                
//                strict = true;
//                {
//                    //same as parameter name, except semicolons are allowed
//                    //@formatter:off
//                    AllowedCharacters paramName = parameterName.get(syntax).get(strict);
//                    map2.put(strict, new AllowedCharacters.Builder(paramName)
//                             .allow(';')
//                             .build());
//                    //@formatter::on
//                }
//                map.put(caretEncoding, map2);
//            }
//            
//            caretEncoding = true;
//            {
//                /*
//                 * Same as when caret encoding is disabled because
//                 * old style syntax does not support caret encoding.
//                 */
//                map.put(caretEncoding, map.get(false));
//            }
//            
//            parameterValue.put(syntax, map);
//        }
//        
//        syntax = SyntaxStyle.NEW;
//        {
//            Map<Boolean, Map<Boolean, AllowedCharacters>> map = new HashMap<Boolean, Map<Boolean, AllowedCharacters>>();
//            caretEncoding = false;
//            {
//                Map<Boolean, AllowedCharacters> map2 = new HashMap<Boolean, AllowedCharacters>();
//                strict = false;
//                {
//                    //@formatter:off
//                    map2.put(strict, new AllowedCharacters.Builder()
//                             .allowAll()
//                             .except("\r\n\"")
//                             .build());
//                    //@formatter:on
//                }
//                
//                strict = true;
//                {
//                    //@formatter:off
//                    map2.put(strict, new AllowedCharacters.Builder()
//                             .allowPrintable()
//                             .allowNonAscii()
//                             .allow('\t')
//                             .except('"')
//                             .build());
//                    //@formatter:on
//                }
//                
//                map.put(caretEncoding, map2);
//            }
//            
//            caretEncoding = true;
//            {
//                Map<Boolean, AllowedCharacters> map2 = new HashMap<Boolean, AllowedCharacters>();
//                strict = false;
//                {
//                    //@formatter:off
//                    map2.put(strict, new AllowedCharacters.Builder()
//                             .allowAll()
//                             .build());
//                    //@formatter:on
//                }
//                
//                strict = true;
//                {
//                    //@formatter:off
//                    map2.put(strict, new AllowedCharacters.Builder()
//                             .allowPrintable()
//                             .allowNonAscii()
//                             .allow("\r\n\t")
//                             .build());
//                    //@formatter:on
//                }
//                
//                map.put(caretEncoding, map2);
//            }
//            
//            parameterValue.put(syntax, map);
//        }
//    }
//    
//    /**
//     * Validates a property name.
//     * @param name the property name
//     * @param syntax the syntax style to validate against
//     * @param strict false to allow all characters as long as they don't break
//     * the syntax, true for spec-compliant validation
//     * @return true if the property name is valid, false if not
//     */
//    public static boolean validatePropertyName(String name, SyntaxStyle syntax, boolean strict) {
//        return allowedCharactersPropertyName(syntax, strict).check(name);
//    }
//    
/**
 * Gets the list of allowed characters for property names.
 * @param syntax the syntax style
 * @param strict false for the non-strict list, true for the spec-compliant
 * list
 * @return the character list
 */
AllowedCharacters::Ptr VObjectValidator::allowedCharactersPropertyName(SyntaxStyle syntax, bool strict) {
    auto found = propertyName.find(syntax);
    if (found != propertyName.end()) {
        auto found_strict = found->second.find(strict);
        if (found_strict != found->second.end()) {
            return found_strict->second;
        }
    }
    return nullptr;
}

//    /**
//     * Validates a group name.
//     * @param group the group name
//     * @param syntax the syntax style to validate against
//     * @param strict false to allow all characters as long as they don't break
//     * the syntax, true for spec-compliant validation
//     * @return true if the group name is valid, false if not
//     */
//    public static boolean validateGroupName(String group, SyntaxStyle syntax, boolean strict) {
//        return allowedCharactersGroup(syntax, strict).check(group);
//    }
//    
/**
 * Gets the list of allowed characters for group names.
 * @param syntax the syntax style
 * @param strict false for the non-strict list, true for the spec-compliant
 * list
 * @return the character list
 */
AllowedCharacters::Ptr VObjectValidator::allowedCharactersGroup(SyntaxStyle syntax, bool strict) {
    auto found = group.find(syntax);
    if (found != group.end()) {
        auto found_strict = found->second.find(strict);
        if (found_strict != found->second.end()) {
            return found_strict->second;
        }
    }
    return nullptr;
}

/**
 * Validates a parameter name.
 * @param name the parameter name
 * @param syntax the syntax style to validate against
 * @param strict false to allow all characters as long as they don't break
 * the syntax, true for spec-compliant validation
 * @return true if the parameter name is valid, false if not
 */
bool VObjectValidator::validateParameterName(const std::string& name, SyntaxStyle syntax, bool strict) {
    if (auto allowed = allowedCharactersParameterName(syntax, strict)) {
        return allowed->check(name);
    }
    return false;
}

/**
 * Gets the list of allowed characters for parameter names.
 * @param syntax the syntax style
 * @param strict false for the non-strict list, true for the spec-compliant
 * list
 * @return the character list
 */
AllowedCharacters::Ptr VObjectValidator::allowedCharactersParameterName(SyntaxStyle syntax, bool strict) {
    auto found = parameterName.find(syntax);
    if (found != parameterName.end()) {
        auto found_strict = found->second.find(strict);
        if (found_strict != found->second.end()) {
            return found_strict->second;
        }
    }
    return nullptr;
}

/**
 * Validates a parameter value.
 * @param value the parameter value
 * @param syntax the syntax style to validate against
 * @param caretEncoding true if caret encoding is enabled, false if not
 * @param strict false to allow all characters as long as they don't break
 * the syntax, true for spec-compliant validation
 * @return true if the parameter value is valid, false if not
 */
bool VObjectValidator::validateParameterValue(const std::string& value, SyntaxStyle syntax, bool caretEncoding, bool strict) {
    if (auto allow = allowedCharactersParameterValue(syntax, caretEncoding, strict))
        return allow->check(value);
    return false;
}

/**
 * Gets the list of allowed characters for parameter values.
 * @param syntax the syntax style
 * @param caretEncoding true if caret encoding is enabled, false if not
 * @param strict false for the non-strict list, true for the spec-compliant
 * list
 * @return the character list
 */
AllowedCharacters::Ptr VObjectValidator::allowedCharactersParameterValue(SyntaxStyle syntax, bool caretEncoding, bool strict) {
    auto found_syntax = parameterValue.find(syntax);
    if (found_syntax != parameterValue.end()) {
        auto syntex_obj = found_syntax->second;
        auto found_ce = syntex_obj.find(caretEncoding);
        if (found_ce != syntex_obj.end()) {
            auto ce_obj = found_ce->second;
            auto found_strict = ce_obj.find(strict);
            if (found_strict != ce_obj.end()) {
                auto strict_obj = found_strict->second;
                return strict_obj;
            }
        }
    }
    return nullptr;
}
//
//    private VObjectValidator() {
//        //hide
//    }
//}
