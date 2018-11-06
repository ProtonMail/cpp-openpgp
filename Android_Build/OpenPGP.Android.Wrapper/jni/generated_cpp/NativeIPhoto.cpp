// AUTOGENERATED FILE - DO NOT MODIFY!
// This file generated by Djinni from open_pgp.djinni

#include "NativeIPhoto.hpp"  // my header
#include "jni_base_h/Marshal.hpp"

namespace ProtonMail {

NativeIPhoto::NativeIPhoto() : ::djinni::JniInterface<::ProtonMail::IPhoto, NativeIPhoto>("ch/protonmail/android/utils/nativelib/IPhoto$CppProxy") {}

NativeIPhoto::~NativeIPhoto() = default;


CJNIEXPORT void JNICALL Java_ch_protonmail_android_utils_nativelib_IPhoto_00024CppProxy_nativeDestroy(JNIEnv* jniEnv, jobject /*this*/, jlong nativeRef)
{
    try {
        DJINNI_FUNCTION_PROLOGUE1(jniEnv, nativeRef);
        delete reinterpret_cast<::djinni::CppProxyHandle<::ProtonMail::IPhoto>*>(nativeRef);
    } JNI_TRANSLATE_EXCEPTIONS_RETURN(jniEnv, )
}

CJNIEXPORT jobject JNICALL Java_ch_protonmail_android_utils_nativelib_IPhoto_00024CppProxy_createInstance(JNIEnv* jniEnv, jobject /*this*/, jbyteArray j_rawData, jstring j_type, jboolean j_isBinary)
{
    try {
        DJINNI_FUNCTION_PROLOGUE0(jniEnv);
        auto r = ::ProtonMail::IPhoto::create_instance(::djinni::Binary::toCpp(jniEnv, j_rawData),
                                                       ::djinni::String::toCpp(jniEnv, j_type),
                                                       ::djinni::Bool::toCpp(jniEnv, j_isBinary));
        return ::djinni::release(::ProtonMail::NativeIPhoto::fromCpp(jniEnv, r));
    } JNI_TRANSLATE_EXCEPTIONS_RETURN(jniEnv, 0 /* value doesn't matter */)
}

CJNIEXPORT jstring JNICALL Java_ch_protonmail_android_utils_nativelib_IPhoto_00024CppProxy_native_1getEncodedData(JNIEnv* jniEnv, jobject /*this*/, jlong nativeRef)
{
    try {
        DJINNI_FUNCTION_PROLOGUE1(jniEnv, nativeRef);
        const auto& ref = ::djinni::objectFromHandleAddress<::ProtonMail::IPhoto>(nativeRef);
        auto r = ref->getEncodedData();
        return ::djinni::release(::djinni::String::fromCpp(jniEnv, r));
    } JNI_TRANSLATE_EXCEPTIONS_RETURN(jniEnv, 0 /* value doesn't matter */)
}

CJNIEXPORT jbyteArray JNICALL Java_ch_protonmail_android_utils_nativelib_IPhoto_00024CppProxy_native_1getRawData(JNIEnv* jniEnv, jobject /*this*/, jlong nativeRef)
{
    try {
        DJINNI_FUNCTION_PROLOGUE1(jniEnv, nativeRef);
        const auto& ref = ::djinni::objectFromHandleAddress<::ProtonMail::IPhoto>(nativeRef);
        auto r = ref->getRawData();
        return ::djinni::release(::djinni::Binary::fromCpp(jniEnv, r));
    } JNI_TRANSLATE_EXCEPTIONS_RETURN(jniEnv, 0 /* value doesn't matter */)
}

CJNIEXPORT jstring JNICALL Java_ch_protonmail_android_utils_nativelib_IPhoto_00024CppProxy_native_1getURL(JNIEnv* jniEnv, jobject /*this*/, jlong nativeRef)
{
    try {
        DJINNI_FUNCTION_PROLOGUE1(jniEnv, nativeRef);
        const auto& ref = ::djinni::objectFromHandleAddress<::ProtonMail::IPhoto>(nativeRef);
        auto r = ref->getURL();
        return ::djinni::release(::djinni::String::fromCpp(jniEnv, r));
    } JNI_TRANSLATE_EXCEPTIONS_RETURN(jniEnv, 0 /* value doesn't matter */)
}

CJNIEXPORT jstring JNICALL Java_ch_protonmail_android_utils_nativelib_IPhoto_00024CppProxy_native_1getImageType(JNIEnv* jniEnv, jobject /*this*/, jlong nativeRef)
{
    try {
        DJINNI_FUNCTION_PROLOGUE1(jniEnv, nativeRef);
        const auto& ref = ::djinni::objectFromHandleAddress<::ProtonMail::IPhoto>(nativeRef);
        auto r = ref->getImageType();
        return ::djinni::release(::djinni::String::fromCpp(jniEnv, r));
    } JNI_TRANSLATE_EXCEPTIONS_RETURN(jniEnv, 0 /* value doesn't matter */)
}

CJNIEXPORT jboolean JNICALL Java_ch_protonmail_android_utils_nativelib_IPhoto_00024CppProxy_native_1getIsBinary(JNIEnv* jniEnv, jobject /*this*/, jlong nativeRef)
{
    try {
        DJINNI_FUNCTION_PROLOGUE1(jniEnv, nativeRef);
        const auto& ref = ::djinni::objectFromHandleAddress<::ProtonMail::IPhoto>(nativeRef);
        auto r = ref->getIsBinary();
        return ::djinni::release(::djinni::Bool::fromCpp(jniEnv, r));
    } JNI_TRANSLATE_EXCEPTIONS_RETURN(jniEnv, 0 /* value doesn't matter */)
}

CJNIEXPORT void JNICALL Java_ch_protonmail_android_utils_nativelib_IPhoto_00024CppProxy_native_1setPhoto(JNIEnv* jniEnv, jobject /*this*/, jlong nativeRef, jbyteArray j_rawData, jstring j_type, jboolean j_isBinary)
{
    try {
        DJINNI_FUNCTION_PROLOGUE1(jniEnv, nativeRef);
        const auto& ref = ::djinni::objectFromHandleAddress<::ProtonMail::IPhoto>(nativeRef);
        ref->setPhoto(::djinni::Binary::toCpp(jniEnv, j_rawData),
                      ::djinni::String::toCpp(jniEnv, j_type),
                      ::djinni::Bool::toCpp(jniEnv, j_isBinary));
    } JNI_TRANSLATE_EXCEPTIONS_RETURN(jniEnv, )
}

}  // namespace ProtonMail
