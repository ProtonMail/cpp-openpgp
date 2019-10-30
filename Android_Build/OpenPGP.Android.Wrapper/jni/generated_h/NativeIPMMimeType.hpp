// AUTOGENERATED FILE - DO NOT MODIFY!
// This file generated by Djinni from open_pgp.djinni

#pragma once

#include "bridge/i_p_m_mime_type.hpp"
#include "jni_base_h/djinni_support.hpp"

namespace ProtonMail {

class NativeIPMMimeType final : ::djinni::JniInterface<::ProtonMail::IPMMimeType, NativeIPMMimeType> {
public:
    using CppType = std::shared_ptr<::ProtonMail::IPMMimeType>;
    using CppOptType = std::shared_ptr<::ProtonMail::IPMMimeType>;
    using JniType = jobject;

    using Boxed = NativeIPMMimeType;

    ~NativeIPMMimeType();

    static CppType toCpp(JNIEnv* jniEnv, JniType j) { return ::djinni::JniClass<NativeIPMMimeType>::get()._fromJava(jniEnv, j); }
    static ::djinni::LocalRef<JniType> fromCppOpt(JNIEnv* jniEnv, const CppOptType& c) { return {jniEnv, ::djinni::JniClass<NativeIPMMimeType>::get()._toJava(jniEnv, c)}; }
    static ::djinni::LocalRef<JniType> fromCpp(JNIEnv* jniEnv, const CppType& c) { return fromCppOpt(jniEnv, c); }

private:
    NativeIPMMimeType();
    friend ::djinni::JniClass<NativeIPMMimeType>;
    friend ::djinni::JniInterface<::ProtonMail::IPMMimeType, NativeIPMMimeType>;

};

}  // namespace ProtonMail