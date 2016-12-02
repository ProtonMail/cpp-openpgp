// AUTOGENERATED FILE - DO NOT MODIFY!
// This file generated by Djinni from open_pgp.djinni

#pragma once

#include "bridge/i_mailer.hpp"
#include "jni_base_h/djinni_support.hpp"

namespace ProtonMail {

class NativeIMailer final : ::djinni::JniInterface<::ProtonMail::IMailer, NativeIMailer> {
public:
    using CppType = std::shared_ptr<::ProtonMail::IMailer>;
    using CppOptType = std::shared_ptr<::ProtonMail::IMailer>;
    using JniType = jobject;

    using Boxed = NativeIMailer;

    ~NativeIMailer();

    static CppType toCpp(JNIEnv* jniEnv, JniType j) { return ::djinni::JniClass<NativeIMailer>::get()._fromJava(jniEnv, j); }
    static ::djinni::LocalRef<JniType> fromCppOpt(JNIEnv* jniEnv, const CppOptType& c) { return {jniEnv, ::djinni::JniClass<NativeIMailer>::get()._toJava(jniEnv, c)}; }
    static ::djinni::LocalRef<JniType> fromCpp(JNIEnv* jniEnv, const CppType& c) { return fromCppOpt(jniEnv, c); }

private:
    NativeIMailer();
    friend ::djinni::JniClass<NativeIMailer>;
    friend ::djinni::JniInterface<::ProtonMail::IMailer, NativeIMailer>;

};

}  // namespace ProtonMail
