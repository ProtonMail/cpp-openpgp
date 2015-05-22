# A simple test for the minimal standard C++ library
#

LOCAL_PATH := $(call my-dir)


include $(CLEAR_VARS)

$(info ARCH Check: $(TARGET_ARCH_ABI))

ifeq ($(TARGET_ARCH_ABI),x86)
   	$(info "start build x86")
	include $(CLEAR_VARS)
	LOCAL_MODULE    := openpgp
	LOCAL_SRC_FILES := libs/x86/libopenpgp.so
	include $(PREBUILT_SHARED_LIBRARY)
endif # TARGET_ARCH_ABI == x86

ifeq ($(TARGET_ARCH_ABI),armeabi-v7a)
   	$(info "start build armeabi-v7a")
	include $(CLEAR_VARS)
	LOCAL_MODULE    := openpgp
	LOCAL_SRC_FILES := libs/armeabi-v7a/libopenpgp.so
	include $(PREBUILT_SHARED_LIBRARY)
endif # TARGET_ARCH_ABI == armeabi-v7a

ifeq ($(TARGET_ARCH_ABI),armeabi)
   	$(info "start build armeabi")
	include $(CLEAR_VARS)
	LOCAL_MODULE    := openpgp
	LOCAL_SRC_FILES := libs/armeabi/libopenpgp.so
	include $(PREBUILT_SHARED_LIBRARY)
endif # TARGET_ARCH_ABI == armeabi

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
