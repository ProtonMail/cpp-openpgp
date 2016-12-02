// AUTOGENERATED FILE - DO NOT MODIFY!
// This file generated by Djinni from open_pgp.djinni

#pragma once

#include "bridge/i_v_card_version.hpp"
#include "jni_base_h/djinni_support.hpp"

namespace ProtonMail {

class NativeIVCardVersion final : ::djinni::JniInterface<::ProtonMail::IVCardVersion, NativeIVCardVersion> {
public:
    using CppType = std::shared_ptr<::ProtonMail::IVCardVersion>;
    using CppOptType = std::shared_ptr<::ProtonMail::IVCardVersion>;
    using JniType = jobject;

    using Boxed = NativeIVCardVersion;

    ~NativeIVCardVersion();

    static CppType toCpp(JNIEnv* jniEnv, JniType j) { return ::djinni::JniClass<NativeIVCardVersion>::get()._fromJava(jniEnv, j); }
    static ::djinni::LocalRef<JniType> fromCppOpt(JNIEnv* jniEnv, const CppOptType& c) { return {jniEnv, ::djinni::JniClass<NativeIVCardVersion>::get()._toJava(jniEnv, c)}; }
    static ::djinni::LocalRef<JniType> fromCpp(JNIEnv* jniEnv, const CppType& c) { return fromCppOpt(jniEnv, c); }

private:
    NativeIVCardVersion();
    friend ::djinni::JniClass<NativeIVCardVersion>;
    friend ::djinni::JniInterface<::ProtonMail::IVCardVersion, NativeIVCardVersion>;

};

}  // namespace ProtonMail
