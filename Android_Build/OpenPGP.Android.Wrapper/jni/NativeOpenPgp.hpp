// AUTOGENERATED FILE - DO NOT MODIFY!
// This file generated by Djinni from open_pgp.djinni

#pragma once

#include "djinni_support.hpp"
#include "open_pgp.hpp"

namespace djinni_generated {

class NativeOpenPgp final : ::djinni::JniInterface<::ProtonMail::OpenPgp, NativeOpenPgp> {
public:
    using CppType = std::shared_ptr<::ProtonMail::OpenPgp>;
    using CppOptType = std::shared_ptr<::ProtonMail::OpenPgp>;
    using JniType = jobject;

    using Boxed = NativeOpenPgp;

    ~NativeOpenPgp();

    static CppType toCpp(JNIEnv* jniEnv, JniType j) { return ::djinni::JniClass<NativeOpenPgp>::get()._fromJava(jniEnv, j); }
    static ::djinni::LocalRef<JniType> fromCppOpt(JNIEnv* jniEnv, const CppOptType& c) { return {jniEnv, ::djinni::JniClass<NativeOpenPgp>::get()._toJava(jniEnv, c)}; }
    static ::djinni::LocalRef<JniType> fromCpp(JNIEnv* jniEnv, const CppType& c) { return fromCppOpt(jniEnv, c); }

private:
    NativeOpenPgp();
    friend ::djinni::JniClass<NativeOpenPgp>;
    friend ::djinni::JniInterface<::ProtonMail::OpenPgp, NativeOpenPgp>;

};

}  // namespace djinni_generated
