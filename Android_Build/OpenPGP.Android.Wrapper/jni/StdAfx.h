/*
 * StdAfx.h
 *
 *  Created on: Apr 29, 2013
 *      Author: Yanfeng
 */

#ifndef STDAFX_H_
#define STDAFX_H_

#include <android/log.h>
#include "stddef.h"
#include "string"
#include <string>
#include <sstream>
#define LOG_TAG "AndroidInterface"
#define LOG_E(...) __android_log_print(ANDROID_LOG_ERROR,LOG_TAG,__VA_ARGS__)


#define JNI(X) JNIEXPORT Java_std_string_##X
#define CAST(X) reinterpret_cast(X)



#endif /* STDAFX_H_ */
