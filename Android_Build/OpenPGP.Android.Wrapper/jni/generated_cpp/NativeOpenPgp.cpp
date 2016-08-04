// AUTOGENERATED FILE - DO NOT MODIFY!
// This file generated by Djinni from open_pgp.djinni

#include "NativeOpenPgp.hpp"  // my header
#include "NativeAddress.hpp"
#include "NativeEncryptPackage.hpp"
#include "NativeOpenPgp.hpp"
#include "NativeOpenPgpKey.hpp"
#include "jni_base_h/Marshal.hpp"

namespace ProtonMail {

NativeOpenPgp::NativeOpenPgp() : ::djinni::JniInterface<::ProtonMail::OpenPgp, NativeOpenPgp>("ch/protonmail/android/utils/OpenPgp$CppProxy") {}

NativeOpenPgp::~NativeOpenPgp() = default;


CJNIEXPORT void JNICALL Java_ch_protonmail_android_utils_OpenPgp_00024CppProxy_nativeDestroy(JNIEnv* jniEnv, jobject /*this*/, jlong nativeRef)
{
    try {
        DJINNI_FUNCTION_PROLOGUE1(jniEnv, nativeRef);
        delete reinterpret_cast<::djinni::CppProxyHandle<::ProtonMail::OpenPgp>*>(nativeRef);
    } JNI_TRANSLATE_EXCEPTIONS_RETURN(jniEnv, )
}

CJNIEXPORT jobject JNICALL Java_ch_protonmail_android_utils_OpenPgp_createInstance(JNIEnv* jniEnv, jobject /*this*/)
{
    try {
        DJINNI_FUNCTION_PROLOGUE0(jniEnv);
        auto r = ::ProtonMail::OpenPgp::create_instance();
        return ::djinni::release(::ProtonMail::NativeOpenPgp::fromCpp(jniEnv, r));
    } JNI_TRANSLATE_EXCEPTIONS_RETURN(jniEnv, 0 /* value doesn't matter */)
}

CJNIEXPORT jobject JNICALL Java_ch_protonmail_android_utils_OpenPgp_createInstanceWithKeys(JNIEnv* jniEnv, jobject /*this*/, jobject j_address)
{
    try {
        DJINNI_FUNCTION_PROLOGUE0(jniEnv);
        auto r = ::ProtonMail::OpenPgp::create_instance_with_keys(::ProtonMail::NativeAddress::toCpp(jniEnv, j_address));
        return ::djinni::release(::ProtonMail::NativeOpenPgp::fromCpp(jniEnv, r));
    } JNI_TRANSLATE_EXCEPTIONS_RETURN(jniEnv, 0 /* value doesn't matter */)
}

CJNIEXPORT jboolean JNICALL Java_ch_protonmail_android_utils_OpenPgp_00024CppProxy_native_1addAddress(JNIEnv* jniEnv, jobject /*this*/, jlong nativeRef, jobject j_address)
{
    try {
        DJINNI_FUNCTION_PROLOGUE1(jniEnv, nativeRef);
        const auto& ref = ::djinni::objectFromHandleAddress<::ProtonMail::OpenPgp>(nativeRef);
        auto r = ref->add_address(::ProtonMail::NativeAddress::toCpp(jniEnv, j_address));
        return ::djinni::release(::djinni::Bool::fromCpp(jniEnv, r));
    } JNI_TRANSLATE_EXCEPTIONS_RETURN(jniEnv, 0 /* value doesn't matter */)
}

CJNIEXPORT jboolean JNICALL Java_ch_protonmail_android_utils_OpenPgp_00024CppProxy_native_1removeAddress(JNIEnv* jniEnv, jobject /*this*/, jlong nativeRef, jstring j_addressId)
{
    try {
        DJINNI_FUNCTION_PROLOGUE1(jniEnv, nativeRef);
        const auto& ref = ::djinni::objectFromHandleAddress<::ProtonMail::OpenPgp>(nativeRef);
        auto r = ref->remove_address(::djinni::String::toCpp(jniEnv, j_addressId));
        return ::djinni::release(::djinni::Bool::fromCpp(jniEnv, r));
    } JNI_TRANSLATE_EXCEPTIONS_RETURN(jniEnv, 0 /* value doesn't matter */)
}

CJNIEXPORT jboolean JNICALL Java_ch_protonmail_android_utils_OpenPgp_00024CppProxy_native_1cleanAddresses(JNIEnv* jniEnv, jobject /*this*/, jlong nativeRef)
{
    try {
        DJINNI_FUNCTION_PROLOGUE1(jniEnv, nativeRef);
        const auto& ref = ::djinni::objectFromHandleAddress<::ProtonMail::OpenPgp>(nativeRef);
        auto r = ref->clean_addresses();
        return ::djinni::release(::djinni::Bool::fromCpp(jniEnv, r));
    } JNI_TRANSLATE_EXCEPTIONS_RETURN(jniEnv, 0 /* value doesn't matter */)
}

CJNIEXPORT void JNICALL Java_ch_protonmail_android_utils_OpenPgp_00024CppProxy_native_1enableDebug(JNIEnv* jniEnv, jobject /*this*/, jlong nativeRef, jboolean j_isDebug)
{
    try {
        DJINNI_FUNCTION_PROLOGUE1(jniEnv, nativeRef);
        const auto& ref = ::djinni::objectFromHandleAddress<::ProtonMail::OpenPgp>(nativeRef);
        ref->enable_debug(::djinni::Bool::toCpp(jniEnv, j_isDebug));
    } JNI_TRANSLATE_EXCEPTIONS_RETURN(jniEnv, )
}

CJNIEXPORT jobject JNICALL Java_ch_protonmail_android_utils_OpenPgp_00024CppProxy_native_1generateKey(JNIEnv* jniEnv, jobject /*this*/, jlong nativeRef, jstring j_userName, jstring j_domain, jstring j_passphrase)
{
    try {
        DJINNI_FUNCTION_PROLOGUE1(jniEnv, nativeRef);
        const auto& ref = ::djinni::objectFromHandleAddress<::ProtonMail::OpenPgp>(nativeRef);
        auto r = ref->generate_key(::djinni::String::toCpp(jniEnv, j_userName),
                                   ::djinni::String::toCpp(jniEnv, j_domain),
                                   ::djinni::String::toCpp(jniEnv, j_passphrase));
        return ::djinni::release(::ProtonMail::NativeOpenPgpKey::fromCpp(jniEnv, r));
    } JNI_TRANSLATE_EXCEPTIONS_RETURN(jniEnv, 0 /* value doesn't matter */)
}

CJNIEXPORT jboolean JNICALL Java_ch_protonmail_android_utils_OpenPgp_00024CppProxy_native_1checkPassphrase(JNIEnv* jniEnv, jobject /*this*/, jlong nativeRef, jstring j_privateKey, jstring j_passphrase)
{
    try {
        DJINNI_FUNCTION_PROLOGUE1(jniEnv, nativeRef);
        const auto& ref = ::djinni::objectFromHandleAddress<::ProtonMail::OpenPgp>(nativeRef);
        auto r = ref->check_passphrase(::djinni::String::toCpp(jniEnv, j_privateKey),
                                       ::djinni::String::toCpp(jniEnv, j_passphrase));
        return ::djinni::release(::djinni::Bool::fromCpp(jniEnv, r));
    } JNI_TRANSLATE_EXCEPTIONS_RETURN(jniEnv, 0 /* value doesn't matter */)
}

CJNIEXPORT jstring JNICALL Java_ch_protonmail_android_utils_OpenPgp_00024CppProxy_native_1updateSinglePassphrase(JNIEnv* jniEnv, jobject /*this*/, jlong nativeRef, jstring j_privateKey, jstring j_oldPassphrase, jstring j_newPassphrase)
{
    try {
        DJINNI_FUNCTION_PROLOGUE1(jniEnv, nativeRef);
        const auto& ref = ::djinni::objectFromHandleAddress<::ProtonMail::OpenPgp>(nativeRef);
        auto r = ref->update_single_passphrase(::djinni::String::toCpp(jniEnv, j_privateKey),
                                               ::djinni::String::toCpp(jniEnv, j_oldPassphrase),
                                               ::djinni::String::toCpp(jniEnv, j_newPassphrase));
        return ::djinni::release(::djinni::String::fromCpp(jniEnv, r));
    } JNI_TRANSLATE_EXCEPTIONS_RETURN(jniEnv, 0 /* value doesn't matter */)
}

CJNIEXPORT void JNICALL Java_ch_protonmail_android_utils_OpenPgp_00024CppProxy_native_1updatePrivateInfo(JNIEnv* jniEnv, jobject /*this*/, jlong nativeRef, jstring j_privateKey)
{
    try {
        DJINNI_FUNCTION_PROLOGUE1(jniEnv, nativeRef);
        const auto& ref = ::djinni::objectFromHandleAddress<::ProtonMail::OpenPgp>(nativeRef);
        ref->update_private_info(::djinni::String::toCpp(jniEnv, j_privateKey));
    } JNI_TRANSLATE_EXCEPTIONS_RETURN(jniEnv, )
}

CJNIEXPORT jstring JNICALL Java_ch_protonmail_android_utils_OpenPgp_00024CppProxy_native_1encryptMessage(JNIEnv* jniEnv, jobject /*this*/, jlong nativeRef, jstring j_addressId, jstring j_plainText)
{
    try {
        DJINNI_FUNCTION_PROLOGUE1(jniEnv, nativeRef);
        const auto& ref = ::djinni::objectFromHandleAddress<::ProtonMail::OpenPgp>(nativeRef);
        auto r = ref->encrypt_message(::djinni::String::toCpp(jniEnv, j_addressId),
                                      ::djinni::String::toCpp(jniEnv, j_plainText));
        return ::djinni::release(::djinni::String::fromCpp(jniEnv, r));
    } JNI_TRANSLATE_EXCEPTIONS_RETURN(jniEnv, 0 /* value doesn't matter */)
}

CJNIEXPORT jstring JNICALL Java_ch_protonmail_android_utils_OpenPgp_00024CppProxy_native_1encryptMessageSingleKey(JNIEnv* jniEnv, jobject /*this*/, jlong nativeRef, jstring j_publicKey, jstring j_plainText)
{
    try {
        DJINNI_FUNCTION_PROLOGUE1(jniEnv, nativeRef);
        const auto& ref = ::djinni::objectFromHandleAddress<::ProtonMail::OpenPgp>(nativeRef);
        auto r = ref->encrypt_message_single_key(::djinni::String::toCpp(jniEnv, j_publicKey),
                                                 ::djinni::String::toCpp(jniEnv, j_plainText));
        return ::djinni::release(::djinni::String::fromCpp(jniEnv, r));
    } JNI_TRANSLATE_EXCEPTIONS_RETURN(jniEnv, 0 /* value doesn't matter */)
}

CJNIEXPORT jstring JNICALL Java_ch_protonmail_android_utils_OpenPgp_00024CppProxy_native_1decryptMessage(JNIEnv* jniEnv, jobject /*this*/, jlong nativeRef, jstring j_encryptText, jstring j_passphras)
{
    try {
        DJINNI_FUNCTION_PROLOGUE1(jniEnv, nativeRef);
        const auto& ref = ::djinni::objectFromHandleAddress<::ProtonMail::OpenPgp>(nativeRef);
        auto r = ref->decrypt_message(::djinni::String::toCpp(jniEnv, j_encryptText),
                                      ::djinni::String::toCpp(jniEnv, j_passphras));
        return ::djinni::release(::djinni::String::fromCpp(jniEnv, r));
    } JNI_TRANSLATE_EXCEPTIONS_RETURN(jniEnv, 0 /* value doesn't matter */)
}

CJNIEXPORT jstring JNICALL Java_ch_protonmail_android_utils_OpenPgp_00024CppProxy_native_1decryptMessageSingleKey(JNIEnv* jniEnv, jobject /*this*/, jlong nativeRef, jstring j_encryptText, jstring j_privateKey, jstring j_passphras)
{
    try {
        DJINNI_FUNCTION_PROLOGUE1(jniEnv, nativeRef);
        const auto& ref = ::djinni::objectFromHandleAddress<::ProtonMail::OpenPgp>(nativeRef);
        auto r = ref->decrypt_message_single_key(::djinni::String::toCpp(jniEnv, j_encryptText),
                                                 ::djinni::String::toCpp(jniEnv, j_privateKey),
                                                 ::djinni::String::toCpp(jniEnv, j_passphras));
        return ::djinni::release(::djinni::String::fromCpp(jniEnv, r));
    } JNI_TRANSLATE_EXCEPTIONS_RETURN(jniEnv, 0 /* value doesn't matter */)
}

CJNIEXPORT jobject JNICALL Java_ch_protonmail_android_utils_OpenPgp_00024CppProxy_native_1encryptAttachment(JNIEnv* jniEnv, jobject /*this*/, jlong nativeRef, jstring j_addressId, jbyteArray j_unencryptData, jstring j_fileName)
{
    try {
        DJINNI_FUNCTION_PROLOGUE1(jniEnv, nativeRef);
        const auto& ref = ::djinni::objectFromHandleAddress<::ProtonMail::OpenPgp>(nativeRef);
        auto r = ref->encrypt_attachment(::djinni::String::toCpp(jniEnv, j_addressId),
                                         ::djinni::Binary::toCpp(jniEnv, j_unencryptData),
                                         ::djinni::String::toCpp(jniEnv, j_fileName));
        return ::djinni::release(::ProtonMail::NativeEncryptPackage::fromCpp(jniEnv, r));
    } JNI_TRANSLATE_EXCEPTIONS_RETURN(jniEnv, 0 /* value doesn't matter */)
}

CJNIEXPORT jobject JNICALL Java_ch_protonmail_android_utils_OpenPgp_00024CppProxy_native_1encryptAttachmentSingleKey(JNIEnv* jniEnv, jobject /*this*/, jlong nativeRef, jstring j_publicKey, jbyteArray j_unencryptData, jstring j_fileName)
{
    try {
        DJINNI_FUNCTION_PROLOGUE1(jniEnv, nativeRef);
        const auto& ref = ::djinni::objectFromHandleAddress<::ProtonMail::OpenPgp>(nativeRef);
        auto r = ref->encrypt_attachment_single_key(::djinni::String::toCpp(jniEnv, j_publicKey),
                                                    ::djinni::Binary::toCpp(jniEnv, j_unencryptData),
                                                    ::djinni::String::toCpp(jniEnv, j_fileName));
        return ::djinni::release(::ProtonMail::NativeEncryptPackage::fromCpp(jniEnv, r));
    } JNI_TRANSLATE_EXCEPTIONS_RETURN(jniEnv, 0 /* value doesn't matter */)
}

CJNIEXPORT jbyteArray JNICALL Java_ch_protonmail_android_utils_OpenPgp_00024CppProxy_native_1decryptAttachment(JNIEnv* jniEnv, jobject /*this*/, jlong nativeRef, jbyteArray j_key, jbyteArray j_data, jstring j_passphras)
{
    try {
        DJINNI_FUNCTION_PROLOGUE1(jniEnv, nativeRef);
        const auto& ref = ::djinni::objectFromHandleAddress<::ProtonMail::OpenPgp>(nativeRef);
        auto r = ref->decrypt_attachment(::djinni::Binary::toCpp(jniEnv, j_key),
                                         ::djinni::Binary::toCpp(jniEnv, j_data),
                                         ::djinni::String::toCpp(jniEnv, j_passphras));
        return ::djinni::release(::djinni::Binary::fromCpp(jniEnv, r));
    } JNI_TRANSLATE_EXCEPTIONS_RETURN(jniEnv, 0 /* value doesn't matter */)
}

CJNIEXPORT jbyteArray JNICALL Java_ch_protonmail_android_utils_OpenPgp_00024CppProxy_native_1decryptAttachmentSingleKey(JNIEnv* jniEnv, jobject /*this*/, jlong nativeRef, jbyteArray j_key, jbyteArray j_data, jstring j_privateKey, jstring j_passphras)
{
    try {
        DJINNI_FUNCTION_PROLOGUE1(jniEnv, nativeRef);
        const auto& ref = ::djinni::objectFromHandleAddress<::ProtonMail::OpenPgp>(nativeRef);
        auto r = ref->decrypt_attachment_single_key(::djinni::Binary::toCpp(jniEnv, j_key),
                                                    ::djinni::Binary::toCpp(jniEnv, j_data),
                                                    ::djinni::String::toCpp(jniEnv, j_privateKey),
                                                    ::djinni::String::toCpp(jniEnv, j_passphras));
        return ::djinni::release(::djinni::Binary::fromCpp(jniEnv, r));
    } JNI_TRANSLATE_EXCEPTIONS_RETURN(jniEnv, 0 /* value doesn't matter */)
}

CJNIEXPORT jbyteArray JNICALL Java_ch_protonmail_android_utils_OpenPgp_00024CppProxy_native_1decryptAttachmentWithPassword(JNIEnv* jniEnv, jobject /*this*/, jlong nativeRef, jbyteArray j_key, jbyteArray j_data, jstring j_password)
{
    try {
        DJINNI_FUNCTION_PROLOGUE1(jniEnv, nativeRef);
        const auto& ref = ::djinni::objectFromHandleAddress<::ProtonMail::OpenPgp>(nativeRef);
        auto r = ref->decrypt_attachment_with_password(::djinni::Binary::toCpp(jniEnv, j_key),
                                                       ::djinni::Binary::toCpp(jniEnv, j_data),
                                                       ::djinni::String::toCpp(jniEnv, j_password));
        return ::djinni::release(::djinni::Binary::fromCpp(jniEnv, r));
    } JNI_TRANSLATE_EXCEPTIONS_RETURN(jniEnv, 0 /* value doesn't matter */)
}

CJNIEXPORT jbyteArray JNICALL Java_ch_protonmail_android_utils_OpenPgp_00024CppProxy_native_1getPublicKeySessionKey(JNIEnv* jniEnv, jobject /*this*/, jlong nativeRef, jbyteArray j_keyPackage, jstring j_passphrase)
{
    try {
        DJINNI_FUNCTION_PROLOGUE1(jniEnv, nativeRef);
        const auto& ref = ::djinni::objectFromHandleAddress<::ProtonMail::OpenPgp>(nativeRef);
        auto r = ref->get_public_key_session_key(::djinni::Binary::toCpp(jniEnv, j_keyPackage),
                                                 ::djinni::String::toCpp(jniEnv, j_passphrase));
        return ::djinni::release(::djinni::Binary::fromCpp(jniEnv, r));
    } JNI_TRANSLATE_EXCEPTIONS_RETURN(jniEnv, 0 /* value doesn't matter */)
}

CJNIEXPORT jbyteArray JNICALL Java_ch_protonmail_android_utils_OpenPgp_00024CppProxy_native_1getPublicKeySessionKeySingleKey(JNIEnv* jniEnv, jobject /*this*/, jlong nativeRef, jbyteArray j_keyPackage, jstring j_privateKey, jstring j_passphrase)
{
    try {
        DJINNI_FUNCTION_PROLOGUE1(jniEnv, nativeRef);
        const auto& ref = ::djinni::objectFromHandleAddress<::ProtonMail::OpenPgp>(nativeRef);
        auto r = ref->get_public_key_session_key_single_key(::djinni::Binary::toCpp(jniEnv, j_keyPackage),
                                                            ::djinni::String::toCpp(jniEnv, j_privateKey),
                                                            ::djinni::String::toCpp(jniEnv, j_passphrase));
        return ::djinni::release(::djinni::Binary::fromCpp(jniEnv, r));
    } JNI_TRANSLATE_EXCEPTIONS_RETURN(jniEnv, 0 /* value doesn't matter */)
}

CJNIEXPORT jbyteArray JNICALL Java_ch_protonmail_android_utils_OpenPgp_00024CppProxy_native_1getSymmetricSessionKey(JNIEnv* jniEnv, jobject /*this*/, jlong nativeRef, jbyteArray j_keyPackage, jstring j_password)
{
    try {
        DJINNI_FUNCTION_PROLOGUE1(jniEnv, nativeRef);
        const auto& ref = ::djinni::objectFromHandleAddress<::ProtonMail::OpenPgp>(nativeRef);
        auto r = ref->get_symmetric_session_key(::djinni::Binary::toCpp(jniEnv, j_keyPackage),
                                                ::djinni::String::toCpp(jniEnv, j_password));
        return ::djinni::release(::djinni::Binary::fromCpp(jniEnv, r));
    } JNI_TRANSLATE_EXCEPTIONS_RETURN(jniEnv, 0 /* value doesn't matter */)
}

CJNIEXPORT jbyteArray JNICALL Java_ch_protonmail_android_utils_OpenPgp_00024CppProxy_native_1getNewPublicKeyPackage(JNIEnv* jniEnv, jobject /*this*/, jlong nativeRef, jbyteArray j_session, jstring j_publicKey)
{
    try {
        DJINNI_FUNCTION_PROLOGUE1(jniEnv, nativeRef);
        const auto& ref = ::djinni::objectFromHandleAddress<::ProtonMail::OpenPgp>(nativeRef);
        auto r = ref->get_new_public_key_package(::djinni::Binary::toCpp(jniEnv, j_session),
                                                 ::djinni::String::toCpp(jniEnv, j_publicKey));
        return ::djinni::release(::djinni::Binary::fromCpp(jniEnv, r));
    } JNI_TRANSLATE_EXCEPTIONS_RETURN(jniEnv, 0 /* value doesn't matter */)
}

CJNIEXPORT jbyteArray JNICALL Java_ch_protonmail_android_utils_OpenPgp_00024CppProxy_native_1getNewSymmetricKeyPackage(JNIEnv* jniEnv, jobject /*this*/, jlong nativeRef, jbyteArray j_session, jstring j_password)
{
    try {
        DJINNI_FUNCTION_PROLOGUE1(jniEnv, nativeRef);
        const auto& ref = ::djinni::objectFromHandleAddress<::ProtonMail::OpenPgp>(nativeRef);
        auto r = ref->get_new_symmetric_key_package(::djinni::Binary::toCpp(jniEnv, j_session),
                                                    ::djinni::String::toCpp(jniEnv, j_password));
        return ::djinni::release(::djinni::Binary::fromCpp(jniEnv, r));
    } JNI_TRANSLATE_EXCEPTIONS_RETURN(jniEnv, 0 /* value doesn't matter */)
}

CJNIEXPORT jstring JNICALL Java_ch_protonmail_android_utils_OpenPgp_00024CppProxy_native_1encryptMessageAes(JNIEnv* jniEnv, jobject /*this*/, jlong nativeRef, jstring j_plainText, jstring j_password)
{
    try {
        DJINNI_FUNCTION_PROLOGUE1(jniEnv, nativeRef);
        const auto& ref = ::djinni::objectFromHandleAddress<::ProtonMail::OpenPgp>(nativeRef);
        auto r = ref->encrypt_message_aes(::djinni::String::toCpp(jniEnv, j_plainText),
                                          ::djinni::String::toCpp(jniEnv, j_password));
        return ::djinni::release(::djinni::String::fromCpp(jniEnv, r));
    } JNI_TRANSLATE_EXCEPTIONS_RETURN(jniEnv, 0 /* value doesn't matter */)
}

CJNIEXPORT jstring JNICALL Java_ch_protonmail_android_utils_OpenPgp_00024CppProxy_native_1decryptMessageAes(JNIEnv* jniEnv, jobject /*this*/, jlong nativeRef, jstring j_encryptedMessage, jstring j_password)
{
    try {
        DJINNI_FUNCTION_PROLOGUE1(jniEnv, nativeRef);
        const auto& ref = ::djinni::objectFromHandleAddress<::ProtonMail::OpenPgp>(nativeRef);
        auto r = ref->decrypt_message_aes(::djinni::String::toCpp(jniEnv, j_encryptedMessage),
                                          ::djinni::String::toCpp(jniEnv, j_password));
        return ::djinni::release(::djinni::String::fromCpp(jniEnv, r));
    } JNI_TRANSLATE_EXCEPTIONS_RETURN(jniEnv, 0 /* value doesn't matter */)
}

CJNIEXPORT jstring JNICALL Java_ch_protonmail_android_utils_OpenPgp_00024CppProxy_native_1encryptMailboxPwd(JNIEnv* jniEnv, jobject /*this*/, jlong nativeRef, jstring j_unencryptedPwd, jstring j_salt)
{
    try {
        DJINNI_FUNCTION_PROLOGUE1(jniEnv, nativeRef);
        const auto& ref = ::djinni::objectFromHandleAddress<::ProtonMail::OpenPgp>(nativeRef);
        auto r = ref->encrypt_mailbox_pwd(::djinni::String::toCpp(jniEnv, j_unencryptedPwd),
                                          ::djinni::String::toCpp(jniEnv, j_salt));
        return ::djinni::release(::djinni::String::fromCpp(jniEnv, r));
    } JNI_TRANSLATE_EXCEPTIONS_RETURN(jniEnv, 0 /* value doesn't matter */)
}

CJNIEXPORT jstring JNICALL Java_ch_protonmail_android_utils_OpenPgp_00024CppProxy_native_1decryptMailboxPwd(JNIEnv* jniEnv, jobject /*this*/, jlong nativeRef, jstring j_encryptedPwd, jstring j_salt)
{
    try {
        DJINNI_FUNCTION_PROLOGUE1(jniEnv, nativeRef);
        const auto& ref = ::djinni::objectFromHandleAddress<::ProtonMail::OpenPgp>(nativeRef);
        auto r = ref->decrypt_mailbox_pwd(::djinni::String::toCpp(jniEnv, j_encryptedPwd),
                                          ::djinni::String::toCpp(jniEnv, j_salt));
        return ::djinni::release(::djinni::String::fromCpp(jniEnv, r));
    } JNI_TRANSLATE_EXCEPTIONS_RETURN(jniEnv, 0 /* value doesn't matter */)
}

CJNIEXPORT jstring JNICALL Java_ch_protonmail_android_utils_OpenPgp_00024CppProxy_native_1readClearsignedMessage(JNIEnv* jniEnv, jobject /*this*/, jlong nativeRef, jstring j_signedMessage)
{
    try {
        DJINNI_FUNCTION_PROLOGUE1(jniEnv, nativeRef);
        const auto& ref = ::djinni::objectFromHandleAddress<::ProtonMail::OpenPgp>(nativeRef);
        auto r = ref->read_clearsigned_message(::djinni::String::toCpp(jniEnv, j_signedMessage));
        return ::djinni::release(::djinni::String::fromCpp(jniEnv, r));
    } JNI_TRANSLATE_EXCEPTIONS_RETURN(jniEnv, 0 /* value doesn't matter */)
}

CJNIEXPORT jint JNICALL Java_ch_protonmail_android_utils_OpenPgp_00024CppProxy_native_1throwAnException(JNIEnv* jniEnv, jobject /*this*/, jlong nativeRef)
{
    try {
        DJINNI_FUNCTION_PROLOGUE1(jniEnv, nativeRef);
        const auto& ref = ::djinni::objectFromHandleAddress<::ProtonMail::OpenPgp>(nativeRef);
        auto r = ref->throw_an_exception();
        return ::djinni::release(::djinni::I32::fromCpp(jniEnv, r));
    } JNI_TRANSLATE_EXCEPTIONS_RETURN(jniEnv, 0 /* value doesn't matter */)
}

}  // namespace ProtonMail
