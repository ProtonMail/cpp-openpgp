// AUTOGENERATED FILE - DO NOT MODIFY!
// This file generated by Djinni from open_pgp.djinni

#pragma once

#include "djinni_support.hpp"
#include "open_pgp_key.hpp"

namespace djinni_generated {

class NativeOpenPgpKey final {
public:
    using CppType = ::ProtonMail::OpenPgpKey;
    using JniType = jobject;

    using Boxed = NativeOpenPgpKey;

    ~NativeOpenPgpKey();

    static CppType toCpp(JNIEnv* jniEnv, JniType j);
    static ::djinni::LocalRef<JniType> fromCpp(JNIEnv* jniEnv, const CppType& c);

private:
    NativeOpenPgpKey();
    friend ::djinni::JniClass<NativeOpenPgpKey>;

    const ::djinni::GlobalRef<jclass> clazz { ::djinni::jniFindClass("ch/protonmail/android/utils/OpenPgpKey") };
    const jmethodID jconstructor { ::djinni::jniGetMethodID(clazz.get(), "<init>", "(Ljava/lang/String;Ljava/lang/String;)V") };
    const jfieldID field_publicKey { ::djinni::jniGetFieldID(clazz.get(), "publicKey", "Ljava/lang/String;") };
    const jfieldID field_privateKey { ::djinni::jniGetFieldID(clazz.get(), "privateKey", "Ljava/lang/String;") };
};

}  // namespace djinni_generated
