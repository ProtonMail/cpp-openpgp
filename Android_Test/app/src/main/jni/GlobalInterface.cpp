/*
 * GlobalInterface.cpp
 *
 *  Created on: Jun 21, 2013
 *      Author: Yanfeng
 */


#include "GlobalInterface.h"

JNIEXPORT JNICALL jint JNI_OnLoad(JavaVM* aVm, void* aReserved)
{
	return JNI_VERSION_1_6;
}

JNIEXPORT JNICALL void
JNI_OnUnload(JavaVM* vm, void* reserved)
{
}

