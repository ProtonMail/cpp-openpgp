//
//  helper_property_sensei.hpp
//  OpenPGP
//
//  Created by Yanfeng Zhang on 5/30/17.
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



#ifndef helper_property_sensei_hpp
#define helper_property_sensei_hpp


#include <ezvcard/ezvcard.hpp>
#include <ezvcard/vcard.hpp>

#include "helper_test_utils.hpp"

namespace ezvcard {
    

class PropertyValidateAsserter {
public:
    typedef std::shared_ptr<PropertyValidateAsserter> Ptr;
    
private:
    VCardProperty::Ptr _property;
    VCard::Ptr _vcard;
    std::vector<VCardVersion::Ptr> _versions = VCardVersion::values();
    
public:
    PropertyValidateAsserter(const VCardProperty::Ptr& property) {
        _property = property;
        _vcard = std::make_shared<VCard>();
    }
    
    void vcard(VCard::Ptr vcard) {
        _vcard = vcard;
        vcard->addProperty(_property);
    }

    void versions(std::vector<VCardVersion::Ptr> versions) {
        _versions = versions;
    }

    void run(std::list<int> expectedCodes) {
        for (VCardVersion::Ptr version : _versions) {
            auto warnings = _property->validate(version, _vcard);
            bool passed = TestUtils::checkCodes(warnings, expectedCodes);
            if (!passed) {
                throw std::runtime_error("For version " + version->toString() + ", expected codes were ");
                // + Arrays.toString(expectedCodes) + " but were actually:\n" + warnings);
            }
        }
    }
};


class CopyAsserter {
public:
    typedef std::shared_ptr<CopyAsserter> Ptr;
    
private:
    VCardProperty::Ptr _original, _copyFromConstructor, _copyFromMethod;
    
public:
    CopyAsserter(const VCardProperty::Ptr& original) {
        _original = original;
        
        //make sure it checks group and parameters
        original->setGroup("group");
        original->addParameter("PARAM", "value");
        
//        try {
//            Constructor<? extends VCardProperty> constructor = original.getClass().getConstructor(original.getClass());
//            this.copyFromConstructor = constructor.newInstance(original);
//            assertEqualsAndHash(original, copyFromConstructor);
//        } catch (Exception e) {
//            throw new RuntimeException(e);
//        }
//        
//        this.copyFromMethod = original.copy();
//        assertNotSame(original, copyFromMethod);
//        assertEqualsAndHash(original, copyFromMethod);
//        
//        assertEqualsAndHash(copyFromMethod, copyFromConstructor);
    }

    void notSame(const std::string& methodName) {
//        try {
//            Method method = original.getClass().getMethod(methodName);
//            Object fromOriginal = method.invoke(original);
//            String message = "Object returned by \"" + methodName + "\" is the same object, but it shouldn't be.";
//            assertNotSame(message, fromOriginal, method.invoke(copyFromConstructor));
//            assertNotSame(message, fromOriginal, method.invoke(copyFromMethod));
//        } catch (Exception e) {
//            throw new RuntimeException(e);
//        }
    }
};


/**
 * Contains methods for testing property classes.
 * @author Michael Angstadt
 */
class PropertySensei {
public:
    
    static PropertyValidateAsserter::Ptr assertValidate(const VCardProperty::Ptr& property);
    static CopyAsserter::Ptr assertCopy(const VCardProperty::Ptr& original);
//
//
//    /**
//     * <p>
//     * Asserts some essential behaviors of the equals method (see
//     * {@link TestUtils#assertEqualsMethodEssentials}). Also asserts that the
//     * fields in the {@link VCardProperty} base class are checked.
//     * </p>
//     * <p>
//     * Calling the chaining methods of the object that this method returns will
//     * create identical instances of the given property and assert that the
//     * instances are equal and have identical hash codes.
//     * </p>
//     * @param clazz the property class
//     * @param constructorValues values to pass into the constructor for creating
//     * instances that test the equals method essentials
//     * @return a chainer object to perform the test
//     */
//    public static EqualsMethodAsserter assertEqualsMethod(Class<? extends VCardProperty> clazz, Object... constructorValues) {
//        return new EqualsMethodAsserter(clazz, constructorValues);
//    }
//    
//    public static class EqualsMethodAsserter {
//        private final Class<? extends VCardProperty> clazz;
//        private Constructor<? extends VCardProperty> constructor;
//        private Object[] constructorValues;
//        private List<Method> methods = new ArrayList<Method>();
//        private List<Object[]> methodValues = new ArrayList<Object[]>();
//        
//        public EqualsMethodAsserter(Class<? extends VCardProperty> clazz, Object... constructorValues) {
//            this.clazz = clazz;
//            
//            try {
//                Constructor<? extends VCardProperty> constructor;
//                VCardProperty instance1, instance2;
//                constructor = clazz.getConstructor(toTypes(constructorValues));
//                instance1 = constructor.newInstance(constructorValues);
//                instance2 = constructor.newInstance(constructorValues);
//                
//                assertEqualsMethodEssentials(instance1);
//                assertEqualsBaseClassFields(instance1, instance2);
//            } catch (Exception e) {
//                throw new RuntimeException(e);
//            }
//        }
//        
//        /**
//         * Defines what constructor to use to create the objects.
//         * @param values the values to pass into the constructor
//         * @return this
//         */
//        public EqualsMethodAsserter constructor(Object... values) {
//            Class<?> parameterTypes[] = new Class<?>[values.length];
//            for (int i = 0; i < values.length; i++) {
//                parameterTypes[i] = values[i].getClass();
//            }
//            
//            return constructor(parameterTypes, values);
//        }
//        
//        /**
//         * Defines what constructor to use to create the objects.
//         * @param parameterTypes the constructor's parameter types
//         * @param values the values to pass into the constructor
//         * @return this
//         */
//        public EqualsMethodAsserter constructor(Class<?> parameterTypes[], Object... values) {
//            if (parameterTypes.length != values.length) {
//                throw new IllegalArgumentException("Number of parameter types must match number of values.");
//            }
//            
//            try {
//                constructor = clazz.getConstructor(parameterTypes);
//                constructorValues = values;
//            } catch (Exception e) {
//                throw new RuntimeException(e);
//            }
//            return this;
//        }
//        
//        /**
//         * Defines a method that should be called after creating each object.
//         * @param name the method name
//         * @param values the values to pass into the method
//         * @return this
//         */
//        public EqualsMethodAsserter method(String name, Object... values) {
//            Class<?> parameterTypes[] = new Class<?>[values.length];
//            for (int i = 0; i < values.length; i++) {
//                parameterTypes[i] = values[i].getClass();
//            }
//            
//            return method(name, parameterTypes, values);
//        }
//        
//        /**
//         * Defines a method that should be called after creating each object.
//         * @param name the method name
//         * @param parameterTypes the parameter types of the method (required if
//         * you're passing null values)
//         * @param values the values to pass into the method
//         * @return this
//         */
//        public EqualsMethodAsserter method(String name, Class<?> parameterTypes[], Object... values) {
//            if (parameterTypes.length != values.length) {
//                throw new IllegalArgumentException("Number of parameter types must match number of values.");
//            }
//            
//            try {
//                Method method = clazz.getMethod(name, parameterTypes);
//                methods.add(method);
//                methodValues.add(values);
//            } catch (Exception e) {
//                throw new RuntimeException(e);
//            }
//            
//            return this;
//        }
//        
//        /**
//         * Executes the test using the specified constructor and methods.
//         * @return this
//         */
//        public EqualsMethodAsserter test() {
//            try {
//                VCardProperty instance1 = createInstance();
//                VCardProperty instance2 = createInstance();
//                methods.clear();
//                methodValues.clear();
//                return test(instance1, instance2);
//            } catch (Exception e) {
//                throw new RuntimeException(e);
//            }
//        }
//        
//        public EqualsMethodAsserter test(VCardProperty instance1, VCardProperty instance2) {
//            assertEqualsAndHash(instance1, instance2);
//            return this;
//        }
//        
//        private VCardProperty createInstance() throws Exception {
//            VCardProperty instance = constructor.newInstance(constructorValues);
//            for (int i = 0; i < methods.size(); i++) {
//                Method method = methods.get(i);
//                Object[] values = methodValues.get(i);
//                method.invoke(instance, values);
//            }
//            return instance;
//        }
//        
//        private Class<?>[] toTypes(Object... values) {
//            Class<?> parameterTypes[] = new Class<?>[values.length];
//            for (int i = 0; i < values.length; i++) {
//                parameterTypes[i] = values[i].getClass();
//            }
//            return parameterTypes;
//        }
//    }
//    
//    /**
//     * Asserts that none of the given property instances are equal to each
//     * other. Also creates copies of the first property, setting the fields in
//     * {@link VCardProperty} to assert that these fields are checked too.
//     * @param properties the properties
//     */
//    public static void assertNothingIsEqual(VCardProperty... properties) {
//        assertNothingIsEqual(Arrays.asList(properties));
//    }
//    
//    /**
//     * Asserts that none of the given property instances are equal to each
//     * other. Also creates copies of the first property, setting the fields in
//     * {@link VCardProperty} to assert that these fields are checked too.
//     * @param properties the properties
//     */
//    public static void assertNothingIsEqual(Iterable<VCardProperty> properties) {
//        for (VCardProperty property : properties) {
//            for (VCardProperty property2 : properties) {
//                if (property != property2) {
//                    assertNotEquals(property, property2);
//                }
//            }
//        }
//        
//        VCardProperty first = properties.iterator().next();
//        VCardProperty copy = first.copy();
//        copy.setGroup("group");
//        assertNotEqualsBothWays(first, copy);
//        
//        copy = first.copy();
//        copy.addParameter("PARAM", "value");
//        assertNotEqualsBothWays(first, copy);
//    }
//    
//    /**
//     * Asserts that the fields in the parent {@link VCardProperty} class are
//     * checked for equality by the property class's "equals" method. Note that
//     * the property instances passed into this method will be modified as part
//     * of the test.
//     * @param instance1 the first property instance
//     * @param instance2 the second property instance
//     */
//    public static <T extends VCardProperty> void assertEqualsBaseClassFields(T instance1, T instance2) {
//        assertNotSame("You must pass two separate object instances into this method.", instance1, instance2);
//        assertEqualsAndHash(instance1, instance2);
//        
//        instance1.setGroup("group");
//        assertNotEqualsBothWays(instance1, instance2);
//        instance2.setGroup("group");
//        assertEqualsAndHash(instance1, instance2);
//        
//        instance1.setGroup("group2");
//        assertNotEqualsBothWays(instance1, instance2);
//        instance2.setGroup("group2");
//        assertEqualsAndHash(instance1, instance2);
//        
//        instance1.setParameter("PARAM", "value");
//        assertNotEqualsBothWays(instance1, instance2);
//        instance2.setParameter("PARAM", "value");
//        assertEqualsAndHash(instance1, instance2);
//        
//        instance1.setParameter("PARAM", "value2");
//        assertNotEqualsBothWays(instance1, instance2);
//        instance2.setParameter("PARAM", "value2");
//        assertEqualsAndHash(instance1, instance2);
//    }
};

}
#endif /* helper_property_sensei_hpp */
