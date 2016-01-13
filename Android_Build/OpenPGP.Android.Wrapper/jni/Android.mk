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

ifeq ($(TARGET_ARCH_ABI),x86_64)
   	$(info "start build x86_64")
	include $(CLEAR_VARS)
	LOCAL_MODULE    := openpgp
	LOCAL_SRC_FILES := libs/x86_64/libopenpgp.so
	include $(PREBUILT_SHARED_LIBRARY)
endif # TARGET_ARCH_ABI == x86_64

ifeq ($(TARGET_ARCH_ABI),armeabi-v7a)
   	$(info "start build armeabi-v7a")
	include $(CLEAR_VARS)
	LOCAL_MODULE    := openpgp
	LOCAL_SRC_FILES := libs/armeabi-v7a/libopenpgp.so
	include $(PREBUILT_SHARED_LIBRARY)
endif # TARGET_ARCH_ABI == armeabi-v7a

ifeq ($(TARGET_ARCH_ABI),arm64-v8a)
   	$(info "start build arm64-v8a")
	include $(CLEAR_VARS)
	LOCAL_MODULE    := openpgp
	LOCAL_SRC_FILES := libs/arm64-v8a/libopenpgp.so
	include $(PREBUILT_SHARED_LIBRARY)
endif # TARGET_ARCH_ABI == arm64-v8a

ifeq ($(TARGET_ARCH_ABI),armeabi)
   	$(info "start build armeabi")
	include $(CLEAR_VARS)
	LOCAL_MODULE    := openpgp
	LOCAL_SRC_FILES := libs/armeabi/libopenpgp.so
	include $(PREBUILT_SHARED_LIBRARY)
endif # TARGET_ARCH_ABI == armeabi

include $(CLEAR_VARS)
base_class1 := $(shell find $(LOCAL_PATH)/jni_base_cpp -type d)
base_class2 := $(shell find $(base_class1) -name *.cpp)
base_class3 := $(sort $(base_class2))
base_class := $(subst $(LOCAL_PATH)/,,$(base_class3))

generated_cpp1 := $(shell find $(LOCAL_PATH)/generated_cpp -type d)
generated_cpp2 := $(shell find $(generated_cpp1) -name *.cpp)
generated_cpp3 := $(sort $(generated_cpp2))
generated_cpp := $(subst $(LOCAL_PATH)/,,$(generated_cpp3))

LOCAL_C_INCLUDES := $(LOCAL_PATH)/include/ $(LOCAL_PATH)/jni_base $(LOCAL_PATH) $(LOCAL_PATH)/generated_h $(LOCAL_PATH)/include/bzlib/
LOCAL_MODULE := openpgp_android
LOCAL_SRC_FILES := $(base_class) \
$(generated_cpp) \
\
openpgp_wrapper.cpp \
Stdafx.cpp \
\

#GlobalInterface.cpp \


LOCAL_SHARED_LIBRARIES := openpgp
LOCAL_LDLIBS += -llog
# LOCAL_CFLAGS += -O3
include $(BUILD_SHARED_LIBRARY)
include $(CLEAR_VARS)

