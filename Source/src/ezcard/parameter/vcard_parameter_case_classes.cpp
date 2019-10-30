//
//  vcard_parameter_case_classes.cpp
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


#include "vcard_parameter_case_classes.hpp"

#include "calscale.hpp"
#include "encoding.hpp"
#include "email_type.hpp"

template class VCardParameterCaseClasses<Calscale>;
template class VCardParameterCaseClasses<Encoding>;
template class VCardParameterCaseClasses<EmailType>;


template <class T>
std::shared_ptr<T> VCardParameterCaseClasses<T>::create(const std::string& value, std::vector<VCardVersion::Ptr> support) {
    return std::shared_ptr<T>(new T(value, support));
}

template <class T>
std::shared_ptr<T> VCardParameterCaseClasses<T>::create(const std::string& value, std::vector<VCardVersion::Ptr> support, bool preserveCase) {
    return std::shared_ptr<T>(new T(value, support, preserveCase));
}

//public class VCardParameterCaseClasses<T extends VCardParameter> extends CaseClasses<T, String> {
//    public VCardParameterCaseClasses(Class<T> clazz) {
//        super(clazz);
//    }
//    
//    @Override
//    protected T create(String value) {
//        //reflection: return new ClassName(value);
//        try {
//            //try (String) constructor
//            Constructor<T> constructor = clazz.getDeclaredConstructor(String.class);
//            constructor.setAccessible(true);
//            return constructor.newInstance(value);
//        } catch (Exception e) {
//            try {
//                //try (String, VCardVersion...) constructor
//                Constructor<T> constructor = clazz.getDeclaredConstructor(String.class, VCardVersion[].class);
//                constructor.setAccessible(true);
//                return constructor.newInstance(value, new VCardVersion[] {});
//            } catch (Exception e2) {
//                throw new RuntimeException(e2);
//            }
//        }
//    }
//    
//    @Override
//    protected boolean matches(T object, String value) {
//        return object.getValue().equalsIgnoreCase(value);
//    }
//}
