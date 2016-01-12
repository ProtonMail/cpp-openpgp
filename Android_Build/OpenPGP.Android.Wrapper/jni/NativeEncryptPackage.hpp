// AUTOGENERATED FILE - DO NOT MODIFY!
// This file generated by Djinni from open_pgp.djinni

#pragma once

#include "djinni_support.hpp"
#include "encrypt_package.hpp"

namespace djinni_generated {

class NativeEncryptPackage final {
public:
    using CppType = ::ProtonMail::EncryptPackage;
    using JniType = jobject;

    using Boxed = NativeEncryptPackage;

    ~NativeEncryptPackage();

    static CppType toCpp(JNIEnv* jniEnv, JniType j);
    static ::djinni::LocalRef<JniType> fromCpp(JNIEnv* jniEnv, const CppType& c);

private:
    NativeEncryptPackage();
    friend ::djinni::JniClass<NativeEncryptPackage>;

    const ::djinni::GlobalRef<jclass> clazz { ::djinni::jniFindClass("ch/protonmail/android/utils/EncryptPackage") };
    const jmethodID jconstructor { ::djinni::jniGetMethodID(clazz.get(), "<init>", "([B[B)V") };
    const jfieldID field_keyPackage { ::djinni::jniGetFieldID(clazz.get(), "keyPackage", "[B") };
    const jfieldID field_dataPackage { ::djinni::jniGetFieldID(clazz.get(), "dataPackage", "[B") };
};

}  // namespace djinni_generated
