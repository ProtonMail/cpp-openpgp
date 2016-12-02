//
//  media_type_case_classes.hpp
//  OpenPGP
//
//  Created by Yanfeng Zhang on 1/10/17.
//  Copyright © 2017 Yanfeng Zhang. All rights reserved.
//

#ifndef media_type_case_classes_hpp
#define media_type_case_classes_hpp



/*
 Copyright (c) 2012-2017, Michael Angstadt
 All rights reserved.
 Redistribution and use in source and binary forms, with or without
 modification, are permitted provided that the following conditions are met:
 1. Redistributions of source code must retain the above copyright notice, this
 list of conditions and the following disclaimer.
 2. Redistributions in binary form must reproduce the above copyright notice,
 this list of conditions and the following disclaimer in the documentation
 and/or other materials provided with the distribution.
 THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR
 ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

/**
 * Manages the list of pre-defined values for a media type parameter.
 * @author Michael Angstadt
 * @param <T> the parameter class
 */


#include <stdio.h>
#include <string>
#include "case_classes.hpp"
#include "string_util.hpp"
#include "media_type_parameter.hpp"

template <class T>
class MediaTypeCaseClasses : public CaseClasses<T, std::vector<std::string>> {
        static_assert(std::is_base_of<MediaTypeParameter, T>::value, "MediaTypeCaseClasses<T>: T must be MediaTypeParameter type :-(");
   

public:
    MediaTypeCaseClasses() : CaseClasses<T, std::vector<std::string>>() {
        
    }
    
protected:
    
    
    std::shared_ptr<T> create(const std::vector<std::string>& value, std::vector<VCardVersion::Ptr> support) {
        return std::shared_ptr<T>(new T(value[0],value[1],value[2]));
    }
    std::shared_ptr<T> create(const std::vector<std::string>& value, std::vector<VCardVersion::Ptr> support, bool preserveCase) {
         return std::shared_ptr<T>(new T(value[0],value[1],value[2]));
    }
    
    bool matches(const std::shared_ptr<T>& object, const std::vector<std::string>& value) {
        if (auto out = std::dynamic_pointer_cast<MediaTypeParameter>(object)) {
            
            
            auto lvalue = out->getValue();
            auto lmedia = out->getMediaType();
            auto lext = out->getExtension();
            
            auto rvalue = value[0];
            auto rmedia = value[1];
            auto rext = value[2];
            
            int found = 0;
            if (!rvalue.empty()) {
                if (str_equals(lvalue, rvalue)) {
                    found ++;
                } else {
                    return false;
                }
            }
            
            if (!rmedia.empty()) {
                if (str_equals(lmedia, rmedia)) {
                    found ++;
                } else {
                    return false;
                }
            }
            
            if (!rext.empty()) {
                if (str_equals(lext, rext)) {
                    found ++;
                } else {
                    return false;
                }
            }
            
            if (found > 0) {
                return true;
            }
        }
        return false;
    }
    
//    std::shared_ptr<T> create(const std::string& value, std::vector<VCardVersion::Ptr> support, bool preserveCase);
//    bool matches(const std::shared_ptr<T>& object, const std::string& value) {
//        if (VCardParameter::Ptr out = std::dynamic_pointer_cast<VCardParameter>(object)) {
//            return str_equals(out->getValue(), value);
//        }
//        return false;
//    }
//    @Override
//    protected T create(String[] value) {
//        try {
//            //reflection: return new ClassName(value, mediaType, extension);
//            Constructor<T> constructor = clazz.getDeclaredConstructor(String.class, String.class, String.class);
//            constructor.setAccessible(true);
//            return constructor.newInstance(value[0], value[1], value[2]);
//        } catch (Exception e) {
//            throw new RuntimeException(e);
//        }
//    }
//
//    @Override
//    protected boolean matches(T object, String[] value) {
//        String objectValues[] = new String[] { object.getValue(), object.getMediaType(), object.getExtension() };
//        for (int i = 0; i < value.length; i++) {
//            String v = value[i];
//            if (v != null && !v.equalsIgnoreCase(objectValues[i])) {
//                return false;
//            }
//        }
//        return true;
//    }
};

#endif /* media_type_case_classes_hpp */
