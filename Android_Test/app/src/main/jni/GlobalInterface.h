/*
 * GlobalInterface.h
 *
 *  Created on: Jun 21, 2013
 *      Author: Yanfeng
 */

#ifndef GLOBALINTERFACE_H_
#define GLOBALINTERFACE_H_

#include "jni.h"


#ifdef __cplusplus
extern "C"
{
#endif

JNIEXPORT JNICALL jint
JNI_OnLoad(JavaVM* aVm, void* aReserved);


JNIEXPORT JNICALL void
JNI_OnUnload(JavaVM* vm, void* reserved);

#ifdef __cplusplus
}
#endif



#endif /* GLOBALINTERFACE_H_ */

