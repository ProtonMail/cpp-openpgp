// AUTOGENERATED FILE - DO NOT MODIFY!
// This file generated by Djinni from open_pgp.djinni

#include "NativeIProductId.hpp"  // my header

namespace ProtonMail {

NativeIProductId::NativeIProductId() : ::djinni::JniInterface<::ProtonMail::IProductId, NativeIProductId>("ch/protonmail/android/utils/nativelib/IProductId$CppProxy") {}

NativeIProductId::~NativeIProductId() = default;


CJNIEXPORT void JNICALL Java_ch_protonmail_android_utils_nativelib_IProductId_00024CppProxy_nativeDestroy(JNIEnv* jniEnv, jobject /*this*/, jlong nativeRef)
{
    try {
        DJINNI_FUNCTION_PROLOGUE1(jniEnv, nativeRef);
        delete reinterpret_cast<::djinni::CppProxyHandle<::ProtonMail::IProductId>*>(nativeRef);
    } JNI_TRANSLATE_EXCEPTIONS_RETURN(jniEnv, )
}

}  // namespace ProtonMail
