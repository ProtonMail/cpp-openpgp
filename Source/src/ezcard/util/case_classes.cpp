//
//  case_classes.cpp
//  OpenPGP
//
//  Created by Yanfeng Zhang on 1/19/17.
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


#include "case_classes.hpp"
//
//template class CaseClasses<int>;
//template class myclass<long>;
//
//template <class T, class V>
//CaseClasses<T, V>::CaseClasses() {
//    
//}
//
//template <class T, class V>
//CaseClasses<T, V>::~CaseClasses() {
//    
//}
//
//
//template <class T, class V>
//std::shared_ptr<T> CaseClasses<T, V>::find(const V& value)
//{
//    //checkInit();
//    
//    for (auto obj : preDefined) {
//        if (matches(obj, value)) {
//            return obj;
//        }
//    }
//    return nullptr;
//}
//
//template <class T, class V>
//std::shared_ptr<T> CaseClasses<T, V>::get(const V& value) {
//    auto found = find(value);
//    if (found != nullptr) {
//        return found;
//    }
//    
//    //TODO::add thread safe later
//    for (auto obj : runtimeDefined) {
//        if (matches(obj, value)) {
//            return obj;
//        }
//    }
//    
//    auto created = create(value);
//    runtimeDefined.push_back(created);
//    return created;
//}

//
//void checkInit() {
//    //        void CaseClasses::checkInit() {
//    //            //    if (preDefined == null) {
//    //            //        synchronized (this) {
//    //            //            //"double check idiom" (Bloch p.283)
//    //            //            if (preDefined == null) {
//    //            //                init();
//    //            //            }
//    //            //        }
//    //            //    }
//    //        }
//}
//void init() {
//    
//}


//    /**
//     * Gets all the static constants of the case class (does not include
//     * runtime-defined constants).
//     * @return all static constants
//     */
//    public Collection<T> all() {
//        checkInit();
//        return preDefined;
//    }
//    
/**
 * Checks to see if this class's fields were initialized yet, and
 * initializes them if they haven't been initialized. This method is
 * thread-safe.
 */

//
//    /**
//     * Initializes this class's fields.
//     */
//    private void init() {
//        Collection<T> preDefined = new ArrayList<T>();
//        for (Field field : clazz.getFields()) {
//            if (!isPreDefinedField(field)) {
//                continue;
//            }
//            
//            try {
//                Object obj = field.get(null);
//                if (obj != null) {
//                    T c = clazz.cast(obj);
//                    preDefined.add(c);
//                }
//            } catch (Exception e) {
//                //reflection error
//                //should never be thrown because we check for "public static" and the correct type
//                throw new RuntimeException(e);
//            }
//        }
//        
//        runtimeDefined = new ArrayList<T>(0);
//        this.preDefined = Collections.unmodifiableCollection(preDefined);
//    }
//    
//    /**
//     * Determines if a field should be treated as a predefined case object.
//     * @param field the field
//     * @return true if it's a predefined case object, false if not
//     */
//    private boolean isPreDefinedField(Field field) {
//        int modifiers = field.getModifiers();
//        
//        //@formatter:off
//        return
//        Modifier.isStatic(modifiers) &&
//        Modifier.isPublic(modifiers) &&
//        field.getDeclaringClass() == clazz &&
//        field.getType() == clazz;
//        //@formatter:on
//    }




