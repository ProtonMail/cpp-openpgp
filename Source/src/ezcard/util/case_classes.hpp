//
//  case_classes.hpp
//  OpenPGP
//
//  Created by Yanfeng Zhang on 1/19/17.
//  Copyright © 2017 Yanfeng Zhang. All rights reserved.
//

#ifndef case_classes_hpp
#define case_classes_hpp

#include <stdio.h>
#include <vector>

#include "vcard_version.hpp"


template <class T, class V>
class CaseClasses {
protected:
    
//    final Class<T> clazz;

//    
//    /**
//     * Creates a new case class collection.
//     * @param clazz the case class
//     */
//    public CaseClasses(Class<T> clazz) {
//        this.clazz = clazz;
//    }

    
    /**
     * Creates a new instance of the case class.
     * @param value the value to give the instance
     * @return the new instance
     */
protected:
    virtual std::shared_ptr<T> create(const V& value, std::vector<VCardVersion::Ptr> support) = 0;
    virtual std::shared_ptr<T> create(const V& value, std::vector<VCardVersion::Ptr> support, bool preserveCase) = 0;
    virtual bool matches(const std::shared_ptr<T>& object, const V& value) = 0;

public:
    CaseClasses() {
        
    }
    
    void setupPredefine(const V& value, std::vector<VCardVersion::Ptr> support) {
        auto created = create(value, support);
        preDefined.push_back(created);
    }
    
    void setupPredefine(const V& value, std::vector<VCardVersion::Ptr> support, bool preserveCase) {
        auto created = create(value, support, preserveCase);
        preDefined.push_back(created);
    }
    
    /**
     * Searches for a case object by value, only looking at the case class'
     * static constants (does not search runtime-defined constants).
     * @param value the value
     * @return the object or null if one wasn't found
     */
    std::shared_ptr<T> find(const V& value) {
        checkInit();
        
        for (auto obj : preDefined) {
            if (matches(obj, value)) {
                return obj;
            }
        }
        return nullptr;
    }
    
    
    /**
     * Searches for a case object by value, creating a new object if one cannot
     * be found.
     * @param value the value
     * @return the object
     */
    std::shared_ptr<T> get(const V& value) {
        auto found = find(value);
        if (found != nullptr) {
            return found;
        }
        
        //TODO::add thread safe later
        for (auto obj : runtimeDefined) {
            if (matches(obj, value)) {
                return obj;
            }
        }
        
        auto created = create(value, {});
        runtimeDefined.push_back(created);
        return created;
    }
    
    std::vector<std::shared_ptr<T>> all() {
        return preDefined;
    }
    
private:
    std::vector<std::shared_ptr<T>> preDefined;
    std::vector<std::shared_ptr<T>> runtimeDefined;
    
    void checkInit() {
//        void CaseClasses::checkInit() {
//            //    if (preDefined == null) {
//            //        synchronized (this) {
//            //            //"double check idiom" (Bloch p.283)
//            //            if (preDefined == null) {
//            //                init();
//            //            }
//            //        }
//            //    }
//        }
    }
    void init();
    
    //bool isPreDefinedField(Field field);

};


#endif /* case_classes_hpp */
