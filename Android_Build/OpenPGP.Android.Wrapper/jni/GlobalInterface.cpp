/*
 * GlobalInterface.cpp
 *
 *  Created on: Jun 21, 2013
 *      Author: Yanfeng
 */


#include "StdAfx.h"
#include "GlobalInterface.h"

JNIEXPORT JNICALL jint JNI_OnLoad(JavaVM* aVm, void* aReserved)
{
	LOG_E("JNI_Onload");
	return JNI_VERSION_1_6;
}

JNIEXPORT JNICALL void
JNI_OnUnload(JavaVM* vm, void* reserved)
{
	LOG_E("JNI_OnUnload");
}

