// AUTOGENERATED FILE - DO NOT MODIFY!
// This file generated by Djinni from open_pgp.djinni

#pragma once

#include "bridge/encrypt_package.hpp"
#include "jni_base_h/djinni_support.hpp"

namespace ProtonMail {

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
    const jfieldID field_mKeyPackage { ::djinni::jniGetFieldID(clazz.get(), "mKeyPackage", "[B") };
    const jfieldID field_mDataPackage { ::djinni::jniGetFieldID(clazz.get(), "mDataPackage", "[B") };
};

}  // namespace ProtonMail
