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




//JNIEXPORT jstring JNICALL
//Java_ch_protonmail_android_utils_OpenPGP_UpdateKeyPassphrase(JNIEnv* env, jobject o, jstring encrypted_message, jstring password);

// //Update Private Key password
// - (NSString *) update_key_password:(NSString*)old_passphrase new_pwd:(NSString*) new_passphrase error:(NSError**) err;

// // //Generate new key pair
// // - (NSMutableDictionary*) generate_key:(NSString*)passphrase username:(NSString*)user_name error:(NSError**) err;


#ifdef __cplusplus
}
#endif

#endif /* OPENPGP_WRAPPER_H */