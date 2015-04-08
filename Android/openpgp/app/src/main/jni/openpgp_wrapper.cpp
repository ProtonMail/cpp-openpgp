#include "openpgp_wrapper.h"
#include <stdio.h>
#include <stdlib.h>
extern "C" {

JNIEXPORT jint JNICALL
Java_ch_protonmail_android_utils_OpenPGP_test1(JNIEnv* env, jobject o, jint x, jint y)
{
	return 100000;
}
//

JNIEXPORT jstring JNICALL
Java_ch_protonmail_android_utils_OpenPGP_test2(JNIEnv* env, jobject o, jint x)
{
	const char *str = "This is a hello word from native through jni";


	int len = strlen(str);

	return (*env).NewString((jchar*) str, len);
}


}