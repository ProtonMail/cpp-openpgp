# A simple test for the minimal standard C++ library
#

LOCAL_PATH := $(call my-dir)


include $(CLEAR_VARS)


ifeq ($(TARGET_ARCH),armeabi)
	include $(CLEAR_VARS)
	LOCAL_MODULE    := openpgp
	LOCAL_SRC_FILES := libs/armeabi/libopenpgp.so
	include $(PREBUILT_SHARED_LIBRARY)
else
	include $(CLEAR_VARS)
	LOCAL_MODULE    := openpgp
	LOCAL_SRC_FILES := libs/armeabi-v7a/libopenpgp.so
	include $(PREBUILT_SHARED_LIBRARY)
endif


include $(CLEAR_VARS)
LOCAL_C_INCLUDES := $(LOCAL_PATH)/include/ $(LOCAL_PATH)/include/bzlib/
LOCAL_MODULE := openpgp_android
LOCAL_SRC_FILES := openpgp_wrapper.cpp \
GlobalInterface.cpp \
Stdafx.cpp


LOCAL_SHARED_LIBRARIES := openpgp
LOCAL_LDLIBS += -llog

include $(BUILD_SHARED_LIBRARY)
include $(CLEAR_VARS)