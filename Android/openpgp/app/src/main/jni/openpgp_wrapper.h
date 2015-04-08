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


#ifdef __cplusplus
}
#endif

#endif /* OPENPGP_WRAPPER_H */
