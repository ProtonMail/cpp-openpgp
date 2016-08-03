// AUTOGENERATED FILE - DO NOT MODIFY!
// This file generated by Djinni from open_pgp.djinni

#import "PMNOpenPgp+Private.h"
#import "PMNOpenPgp.h"
#import "DJICppWrapperCache+Private.h"
#import "DJIError.h"
#import "DJIMarshal+Private.h"
#import "PMNAddress+Private.h"
#import "PMNEncryptPackage+Private.h"
#import "PMNOpenPgp+Private.h"
#import "PMNOpenPgpKey+Private.h"
#include <exception>
#include <utility>

static_assert(__has_feature(objc_arc), "Djinni requires ARC to be enabled for this file");

@interface PMNOpenPgp ()

- (id)initWithCpp:(const std::shared_ptr<::ProtonMail::OpenPgp>&)cppRef;

@end

@implementation PMNOpenPgp {
    ::djinni::CppProxyCache::Handle<std::shared_ptr<::ProtonMail::OpenPgp>> _cppRefHandle;
}

- (id)initWithCpp:(const std::shared_ptr<::ProtonMail::OpenPgp>&)cppRef
{
    if (self = [super init]) {
        _cppRefHandle.assign(cppRef);
    }
    return self;
}

+ (nullable PMNOpenPgp *)createInstance {
    try {
        auto r = ::ProtonMail::OpenPgp::create_instance();
        return ::OBJ_ProtonMail::OpenPgp::fromCpp(r);
    } DJINNI_TRANSLATE_EXCEPTIONS()
}

+ (nullable PMNOpenPgp *)createInstanceWithKeys:(nonnull PMNAddress *)address {
    try {
        auto r = ::ProtonMail::OpenPgp::create_instance_with_keys(::OBJ_ProtonMail::Address::toCpp(address));
        return ::OBJ_ProtonMail::OpenPgp::fromCpp(r);
    } DJINNI_TRANSLATE_EXCEPTIONS()
}

- (BOOL)addAddress:(nonnull PMNAddress *)address {
    try {
        auto r = _cppRefHandle.get()->add_address(::OBJ_ProtonMail::Address::toCpp(address));
        return ::djinni::Bool::fromCpp(r);
    } DJINNI_TRANSLATE_EXCEPTIONS()
}

- (BOOL)removeAddress:(nonnull NSString *)addressId {
    try {
        auto r = _cppRefHandle.get()->remove_address(::djinni::String::toCpp(addressId));
        return ::djinni::Bool::fromCpp(r);
    } DJINNI_TRANSLATE_EXCEPTIONS()
}

- (BOOL)cleanAddresses {
    try {
        auto r = _cppRefHandle.get()->clean_addresses();
        return ::djinni::Bool::fromCpp(r);
    } DJINNI_TRANSLATE_EXCEPTIONS()
}

- (void)enableDebug:(BOOL)isDebug {
    try {
        _cppRefHandle.get()->enable_debug(::djinni::Bool::toCpp(isDebug));
    } DJINNI_TRANSLATE_EXCEPTIONS()
}

- (nonnull PMNOpenPgpKey *)generateKey:(nonnull NSString *)userName
                                domain:(nonnull NSString *)domain
                            passphrase:(nonnull NSString *)passphrase {
    try {
        auto r = _cppRefHandle.get()->generate_key(::djinni::String::toCpp(userName),
                                                   ::djinni::String::toCpp(domain),
                                                   ::djinni::String::toCpp(passphrase));
        return ::OBJ_ProtonMail::OpenPgpKey::fromCpp(r);
    } DJINNI_TRANSLATE_EXCEPTIONS()
}

- (BOOL)checkPassphrase:(nonnull NSString *)privateKey
             passphrase:(nonnull NSString *)passphrase {
    try {
        auto r = _cppRefHandle.get()->check_passphrase(::djinni::String::toCpp(privateKey),
                                                       ::djinni::String::toCpp(passphrase));
        return ::djinni::Bool::fromCpp(r);
    } DJINNI_TRANSLATE_EXCEPTIONS()
}

- (nonnull NSString *)updateSinglePassphrase:(nonnull NSString *)privateKey
                               oldPassphrase:(nonnull NSString *)oldPassphrase
                               newPassphrase:(nonnull NSString *)newPassphrase {
    try {
        auto r = _cppRefHandle.get()->update_single_passphrase(::djinni::String::toCpp(privateKey),
                                                               ::djinni::String::toCpp(oldPassphrase),
                                                               ::djinni::String::toCpp(newPassphrase));
        return ::djinni::String::fromCpp(r);
    } DJINNI_TRANSLATE_EXCEPTIONS()
}

- (void)updatePrivateInfo:(nonnull NSString *)privateKey {
    try {
        _cppRefHandle.get()->update_private_info(::djinni::String::toCpp(privateKey));
    } DJINNI_TRANSLATE_EXCEPTIONS()
}

- (nonnull NSString *)encryptMessage:(nonnull NSString *)addressId
                           plainText:(nonnull NSString *)plainText {
    try {
        auto r = _cppRefHandle.get()->encrypt_message(::djinni::String::toCpp(addressId),
                                                      ::djinni::String::toCpp(plainText));
        return ::djinni::String::fromCpp(r);
    } DJINNI_TRANSLATE_EXCEPTIONS()
}

- (nonnull NSString *)encryptMessageSingleKey:(nonnull NSString *)publicKey
                                    plainText:(nonnull NSString *)plainText {
    try {
        auto r = _cppRefHandle.get()->encrypt_message_single_key(::djinni::String::toCpp(publicKey),
                                                                 ::djinni::String::toCpp(plainText));
        return ::djinni::String::fromCpp(r);
    } DJINNI_TRANSLATE_EXCEPTIONS()
}

- (nonnull NSString *)decryptMessage:(nonnull NSString *)encryptText
                           passphras:(nonnull NSString *)passphras {
    try {
        auto r = _cppRefHandle.get()->decrypt_message(::djinni::String::toCpp(encryptText),
                                                      ::djinni::String::toCpp(passphras));
        return ::djinni::String::fromCpp(r);
    } DJINNI_TRANSLATE_EXCEPTIONS()
}

- (nonnull NSString *)decryptMessageSingleKey:(nonnull NSString *)encryptText
                                   privateKey:(nonnull NSString *)privateKey
                                    passphras:(nonnull NSString *)passphras {
    try {
        auto r = _cppRefHandle.get()->decrypt_message_single_key(::djinni::String::toCpp(encryptText),
                                                                 ::djinni::String::toCpp(privateKey),
                                                                 ::djinni::String::toCpp(passphras));
        return ::djinni::String::fromCpp(r);
    } DJINNI_TRANSLATE_EXCEPTIONS()
}

- (nonnull PMNEncryptPackage *)encryptAttachment:(nonnull NSString *)addressId
                                   unencryptData:(nonnull NSData *)unencryptData
                                        fileName:(nonnull NSString *)fileName {
    try {
        auto r = _cppRefHandle.get()->encrypt_attachment(::djinni::String::toCpp(addressId),
                                                         ::djinni::Binary::toCpp(unencryptData),
                                                         ::djinni::String::toCpp(fileName));
        return ::OBJ_ProtonMail::EncryptPackage::fromCpp(r);
    } DJINNI_TRANSLATE_EXCEPTIONS()
}

- (nonnull PMNEncryptPackage *)encryptAttachmentSingleKey:(nonnull NSString *)publicKey
                                            unencryptData:(nonnull NSData *)unencryptData
                                                 fileName:(nonnull NSString *)fileName {
    try {
        auto r = _cppRefHandle.get()->encrypt_attachment_single_key(::djinni::String::toCpp(publicKey),
                                                                    ::djinni::Binary::toCpp(unencryptData),
                                                                    ::djinni::String::toCpp(fileName));
        return ::OBJ_ProtonMail::EncryptPackage::fromCpp(r);
    } DJINNI_TRANSLATE_EXCEPTIONS()
}

- (nonnull NSData *)decryptAttachment:(nonnull NSData *)key
                                 data:(nonnull NSData *)data
                            passphras:(nonnull NSString *)passphras {
    try {
        auto r = _cppRefHandle.get()->decrypt_attachment(::djinni::Binary::toCpp(key),
                                                         ::djinni::Binary::toCpp(data),
                                                         ::djinni::String::toCpp(passphras));
        return ::djinni::Binary::fromCpp(r);
    } DJINNI_TRANSLATE_EXCEPTIONS()
}

- (nonnull NSData *)decryptAttachmentSingleKey:(nonnull NSData *)key
                                          data:(nonnull NSData *)data
                                    privateKey:(nonnull NSString *)privateKey
                                     passphras:(nonnull NSString *)passphras {
    try {
        auto r = _cppRefHandle.get()->decrypt_attachment_single_key(::djinni::Binary::toCpp(key),
                                                                    ::djinni::Binary::toCpp(data),
                                                                    ::djinni::String::toCpp(privateKey),
                                                                    ::djinni::String::toCpp(passphras));
        return ::djinni::Binary::fromCpp(r);
    } DJINNI_TRANSLATE_EXCEPTIONS()
}

- (nonnull NSData *)decryptAttachmentWithPassword:(nonnull NSData *)key
                                             data:(nonnull NSData *)data
                                         password:(nonnull NSString *)password {
    try {
        auto r = _cppRefHandle.get()->decrypt_attachment_with_password(::djinni::Binary::toCpp(key),
                                                                       ::djinni::Binary::toCpp(data),
                                                                       ::djinni::String::toCpp(password));
        return ::djinni::Binary::fromCpp(r);
    } DJINNI_TRANSLATE_EXCEPTIONS()
}

- (nonnull NSData *)getPublicKeySessionKey:(nonnull NSData *)keyPackage
                                passphrase:(nonnull NSString *)passphrase {
    try {
        auto r = _cppRefHandle.get()->get_public_key_session_key(::djinni::Binary::toCpp(keyPackage),
                                                                 ::djinni::String::toCpp(passphrase));
        return ::djinni::Binary::fromCpp(r);
    } DJINNI_TRANSLATE_EXCEPTIONS()
}

- (nonnull NSData *)getPublicKeySessionKeySingleKey:(nonnull NSData *)keyPackage
                                         privateKey:(nonnull NSString *)privateKey
                                         passphrase:(nonnull NSString *)passphrase {
    try {
        auto r = _cppRefHandle.get()->get_public_key_session_key_single_key(::djinni::Binary::toCpp(keyPackage),
                                                                            ::djinni::String::toCpp(privateKey),
                                                                            ::djinni::String::toCpp(passphrase));
        return ::djinni::Binary::fromCpp(r);
    } DJINNI_TRANSLATE_EXCEPTIONS()
}

- (nonnull NSData *)getSymmetricSessionKey:(nonnull NSData *)keyPackage
                                  password:(nonnull NSString *)password {
    try {
        auto r = _cppRefHandle.get()->get_symmetric_session_key(::djinni::Binary::toCpp(keyPackage),
                                                                ::djinni::String::toCpp(password));
        return ::djinni::Binary::fromCpp(r);
    } DJINNI_TRANSLATE_EXCEPTIONS()
}

- (nonnull NSData *)getNewPublicKeyPackage:(nonnull NSData *)session
                                 publicKey:(nonnull NSString *)publicKey {
    try {
        auto r = _cppRefHandle.get()->get_new_public_key_package(::djinni::Binary::toCpp(session),
                                                                 ::djinni::String::toCpp(publicKey));
        return ::djinni::Binary::fromCpp(r);
    } DJINNI_TRANSLATE_EXCEPTIONS()
}

- (nonnull NSData *)getNewSymmetricKeyPackage:(nonnull NSData *)session
                                     password:(nonnull NSString *)password {
    try {
        auto r = _cppRefHandle.get()->get_new_symmetric_key_package(::djinni::Binary::toCpp(session),
                                                                    ::djinni::String::toCpp(password));
        return ::djinni::Binary::fromCpp(r);
    } DJINNI_TRANSLATE_EXCEPTIONS()
}

- (nonnull NSString *)encryptMessageAes:(nonnull NSString *)plainText
                               password:(nonnull NSString *)password {
    try {
        auto r = _cppRefHandle.get()->encrypt_message_aes(::djinni::String::toCpp(plainText),
                                                          ::djinni::String::toCpp(password));
        return ::djinni::String::fromCpp(r);
    } DJINNI_TRANSLATE_EXCEPTIONS()
}

- (nonnull NSString *)decryptMessageAes:(nonnull NSString *)encryptedMessage
                               password:(nonnull NSString *)password {
    try {
        auto r = _cppRefHandle.get()->decrypt_message_aes(::djinni::String::toCpp(encryptedMessage),
                                                          ::djinni::String::toCpp(password));
        return ::djinni::String::fromCpp(r);
    } DJINNI_TRANSLATE_EXCEPTIONS()
}

- (nonnull NSString *)encryptMailboxPwd:(nonnull NSString *)unencryptedPwd
                                   salt:(nonnull NSString *)salt {
    try {
        auto r = _cppRefHandle.get()->encrypt_mailbox_pwd(::djinni::String::toCpp(unencryptedPwd),
                                                          ::djinni::String::toCpp(salt));
        return ::djinni::String::fromCpp(r);
    } DJINNI_TRANSLATE_EXCEPTIONS()
}

- (nonnull NSString *)decryptMailboxPwd:(nonnull NSString *)encryptedPwd
                                   salt:(nonnull NSString *)salt {
    try {
        auto r = _cppRefHandle.get()->decrypt_mailbox_pwd(::djinni::String::toCpp(encryptedPwd),
                                                          ::djinni::String::toCpp(salt));
        return ::djinni::String::fromCpp(r);
    } DJINNI_TRANSLATE_EXCEPTIONS()
}

- (nonnull NSString *)readClearsignedMessage:(nonnull NSString *)signedMessage {
    try {
        auto r = _cppRefHandle.get()->read_clearsigned_message(::djinni::String::toCpp(signedMessage));
        return ::djinni::String::fromCpp(r);
    } DJINNI_TRANSLATE_EXCEPTIONS()
}

- (int32_t)throwAnException {
    try {
        auto r = _cppRefHandle.get()->throw_an_exception();
        return ::djinni::I32::fromCpp(r);
    } DJINNI_TRANSLATE_EXCEPTIONS()
}

namespace OBJ_ProtonMail {

auto OpenPgp::toCpp(ObjcType objc) -> CppType
{
    if (!objc) {
        return nullptr;
    }
    return objc->_cppRefHandle.get();
}

auto OpenPgp::fromCppOpt(const CppOptType& cpp) -> ObjcType
{
    if (!cpp) {
        return nil;
    }
    return ::djinni::get_cpp_proxy<PMNOpenPgp>(cpp);
}

}  // namespace OBJ_ProtonMail

@end
