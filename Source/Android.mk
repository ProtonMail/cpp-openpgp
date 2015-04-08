# A simple test for the minimal standard C++ library
#

LOCAL_PATH := $(call my-dir)


include $(CLEAR_VARS)


utilities_1 := $(shell find $(LOCAL_PATH)/src/utilities -type d)
utilities_2 := $(shell find $(utilities_1) -name *.cpp)
utilities_3 := $(sort $(utilities_2))
utilities := $(subst $(LOCAL_PATH)/,,$(utilities_3))


LOCAL_C_INCLUDES := $(LOCAL_PATH)/include/
LOCAL_MODULE := libopenpgp
LOCAL_SRC_FILES :=  \
$(utilities)


include $(BUILD_SHARED_LIBRARY)
include $(CLEAR_VARS)