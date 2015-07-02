#ifndef OPENPGP_WRAPPER_H
#define OPENPGP_WRAPPER_H

#include "jni.h"

#ifdef __cplusplus
extern "C"
{
#endif
//this class only for test.
//
JNIEXPORT jint JNICALL
Java_ch_protonmail_android_utils_OpenPGP_test1(JNIEnv* env, jobject o, jint x, jint y);
//

JNIEXPORT jstring JNICALL
Java_ch_protonmail_android_utils_OpenPGP_test2(JNIEnv* env, jobject o, jint x);


// openpgp functions

JNIEXPORT jint JNICALL
Java_ch_protonmail_android_utils_OpenPGP_SetupKeys(JNIEnv* env, jobject o, jstring priv_key, jstring pub_key, jstring passphrase);

JNIEXPORT jstring JNICALL
Java_ch_protonmail_android_utils_OpenPGP_EncryptMessage(JNIEnv* env, jobject o, jstring unencrypt_message, jstring pub_key);
JNIEXPORT jstring JNICALL
Java_ch_protonmail_android_utils_OpenPGP_DecryptMessage(JNIEnv* env, jobject o, jstring encrypted_message, jstring priv_key, jstring passphrase);

JNIEXPORT jstring JNICALL
Java_ch_protonmail_android_utils_OpenPGP_EncryptMessageAES(JNIEnv* env, jobject o, jstring unencrypt_message, jstring password);
JNIEXPORT jstring JNICALL
Java_ch_protonmail_android_utils_OpenPGP_DecryptMessageAES(JNIEnv* env, jobject o, jstring encrypted_message, jstring password);

JNIEXPORT jstring JNICALL
Java_ch_protonmail_android_utils_OpenPGP_EncryptMailboxPWD(JNIEnv* env, jobject o, jstring unencrypt_pwd, jstring salt);
JNIEXPORT jstring JNICALL
Java_ch_protonmail_android_utils_OpenPGP_DecryptMailboxPWD(JNIEnv* env, jobject o, jstring encrypted_pwd, jstring salt);



/// this function save as DecryptAttachment
JNIEXPORT jbyteArray JNICALL
Java_ch_protonmail_android_utils_OpenPGP_DecryptAttachmentArmored(JNIEnv* env, jobject o, jstring key_package, jstring data_package, jstring priv_key, jstring passphrase);
JNIEXPORT jbyteArray JNICALL
Java_ch_protonmail_android_utils_OpenPGP_DecryptAttachment(JNIEnv* env, jobject o, jbyteArray key, jbyteArray data, jstring private_key, jstring passphrase);
JNIEXPORT jobject JNICALL
Java_ch_protonmail_android_utils_OpenPGP_EncryptAttachment(JNIEnv* env, jobject o, jbyteArray unecnrypt_data, jstring public_key);


JNIEXPORT jbyteArray JNICALL
Java_ch_protonmail_android_utils_OpenPGP_GetPublicKeySessionKey(JNIEnv* env, jobject o, jbyteArray key_package, jstring priv_key, jstring passphrase);
JNIEXPORT jbyteArray JNICALL
Java_ch_protonmail_android_utils_OpenPGP_GetSymmetricSessionKey(JNIEnv* env, jobject o, jbyteArray key_package, jstring password);


JNIEXPORT jbyteArray JNICALL
Java_ch_protonmail_android_utils_OpenPGP_GetNewPublicKeyPackage(JNIEnv* env, jobject o, jbyteArray sessionKey, jstring publicKey);
JNIEXPORT jbyteArray JNICALL
Java_ch_protonmail_android_utils_OpenPGP_GetNewSymmetricKeyPackage(JNIEnv* env, jobject o, jbyteArray sessionKey, jstring password);





// TODO :: need add blow functions

//JNIEXPORT jstring JNICALL
//Java_ch_protonmail_android_utils_OpenPGP_UpdateKeyPassphrase(JNIEnv* env, jobject o, jstring encrypted_message, jstring password);

// //Update Private Key password
// - (NSString *) update_key_password:(NSString*)old_passphrase new_pwd:(NSString*) new_passphrase error:(NSError**) err;

// // //Generate new key pair
// // - (NSMutableDictionary*) generate_key:(NSString*)passphrase username:(NSString*)user_name error:(NSError**) err;

////binary attachment
//- (NSData *) decrypt_message_aes:(NSData*) keyPackage data:(NSData*) dataPackage pwd:(NSString *)password error:(NSError**) err;


#ifdef __cplusplus
}
#endif

#endif /* OPENPGP_WRAPPER_H */