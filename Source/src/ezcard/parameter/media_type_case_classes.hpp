//
//  media_type_case_classes.hpp
//  OpenPGP
//
//  Created by Yanfeng Zhang on 1/10/17.
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

#ifndef media_type_case_classes_hpp
#define media_type_case_classes_hpp

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
