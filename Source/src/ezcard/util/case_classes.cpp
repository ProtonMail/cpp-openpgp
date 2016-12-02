//
//  case_classes.cpp
//  OpenPGP
//
//  Created by Yanfeng Zhang on 1/19/17.
//  Copyright © 2017 Yanfeng Zhang. All rights reserved.
//

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




