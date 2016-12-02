//
//  vcard_parameter_case_classes.cpp
//  OpenPGP
//
//  Created by Yanfeng Zhang on 1/10/17.
//  Copyright © 2017 Yanfeng Zhang. All rights reserved.
//

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
