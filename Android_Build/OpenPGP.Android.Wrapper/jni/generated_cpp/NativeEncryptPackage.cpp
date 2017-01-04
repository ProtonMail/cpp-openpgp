// AUTOGENERATED FILE - DO NOT MODIFY!
// This file generated by Djinni from open_pgp.djinni

#include "NativeEncryptPackage.hpp"  // my header
#include "jni_base_h/Marshal.hpp"

namespace ProtonMail {

NativeEncryptPackage::NativeEncryptPackage() = default;

NativeEncryptPackage::~NativeEncryptPackage() = default;

auto NativeEncryptPackage::fromCpp(JNIEnv* jniEnv, const CppType& c) -> ::djinni::LocalRef<JniType> {
    const auto& data = ::djinni::JniClass<NativeEncryptPackage>::get();
    auto r = ::djinni::LocalRef<JniType>{jniEnv->NewObject(data.clazz.get(), data.jconstructor,
                                                           ::djinni::get(::djinni::Binary::fromCpp(jniEnv, c.key_package)),
                                                           ::djinni::get(::djinni::Binary::fromCpp(jniEnv, c.data_package)))};
    ::djinni::jniExceptionCheck(jniEnv);
    return r;
}

auto NativeEncryptPackage::toCpp(JNIEnv* jniEnv, JniType j) -> CppType {
    ::djinni::JniLocalScope jscope(jniEnv, 3);
    assert(j != nullptr);
    const auto& data = ::djinni::JniClass<NativeEncryptPackage>::get();
    return {::djinni::Binary::toCpp(jniEnv, (jbyteArray)jniEnv->GetObjectField(j, data.field_mKeyPackage)),
            ::djinni::Binary::toCpp(jniEnv, (jbyteArray)jniEnv->GetObjectField(j, data.field_mDataPackage))};
}

}  // namespace ProtonMail