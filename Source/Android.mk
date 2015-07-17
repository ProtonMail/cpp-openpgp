# A simple test for the minimal standard C++ library
#

LOCAL_PATH := $(call my-dir)

$(info ARCH Check: $(TARGET_ARCH_ABI))
include $(CLEAR_VARS)
ifeq ($(TARGET_ARCH_ABI),x86)
	include $(CLEAR_VARS)
	LOCAL_MODULE    := crypto
	LOCAL_SRC_FILES := libs/x86/libcrypto.a
	include $(PREBUILT_STATIC_LIBRARY)

	include $(CLEAR_VARS)
	LOCAL_MODULE    := ssl
	LOCAL_SRC_FILES := libs/x86/libssl.a
	include $(PREBUILT_STATIC_LIBRARY)
endif # TARGET_ARCH_ABI == x86

ifeq ($(TARGET_ARCH_ABI),armeabi)
	include $(CLEAR_VARS)
    LOCAL_MODULE    := crypto
	LOCAL_SRC_FILES := libs/armeabi/libcrypto.a
	include $(PREBUILT_STATIC_LIBRARY)

	include $(CLEAR_VARS)
	LOCAL_MODULE    := ssl
	LOCAL_SRC_FILES := libs/armeabi/libssl.a
	include $(PREBUILT_STATIC_LIBRARY)
endif # TARGET_ARCH_ABI == armeabi

ifeq ($(TARGET_ARCH_ABI),armeabi-v7a)
	include $(CLEAR_VARS)
	LOCAL_MODULE    := crypto
	LOCAL_SRC_FILES := libs/armeabi-v7a/libcrypto.a
	include $(PREBUILT_STATIC_LIBRARY)

    include $(CLEAR_VARS)
	LOCAL_MODULE    := ssl
	LOCAL_SRC_FILES := libs/armeabi-v7a/libssl.a
	include $(PREBUILT_STATIC_LIBRARY)
endif # TARGET_ARCH_ABI == armeabi-v7a


include $(CLEAR_VARS)
bzlib_1 := $(shell find $(LOCAL_PATH)/src/bzlib -type d)
bzlib_2 := $(shell find $(bzlib_1) -name *.c)
bzlib_3 := $(sort $(bzlib_2))
bzlib := $(subst $(LOCAL_PATH)/,,$(bzlib_3))

base_1 := $(shell find $(LOCAL_PATH)/src/base -type d)
base_2 := $(shell find $(base_1) -name *.cpp)
base_3 := $(sort $(base_2))
base := $(subst $(LOCAL_PATH)/,,$(base_3))

compress_1 := $(shell find $(LOCAL_PATH)/src/compress -type d)
compress_2 := $(shell find $(compress_1) -name *.cpp)
compress_3 := $(sort $(compress_2))
compress := $(subst $(LOCAL_PATH)/,,$(compress_3))

utilities_1 := $(shell find $(LOCAL_PATH)/src/utilities -type d)
utilities_2 := $(shell find $(utilities_1) -name *.cpp)
utilities_3 := $(sort $(utilities_2))
utilities := $(subst $(LOCAL_PATH)/,,$(utilities_3))

hash_1 := $(shell find $(LOCAL_PATH)/src/hash -type d)
hash_2 := $(shell find $(hash_1) -name *.cpp)
hash_3 := $(sort $(hash_2))
hash := $(subst $(LOCAL_PATH)/,,$(hash_3))

openpgp_1 := $(shell find $(LOCAL_PATH)/src/openpgp -type d)
openpgp_2 := $(shell find $(openpgp_1) -name *.cpp)
openpgp_3 := $(sort $(openpgp_2))
openpgp := $(subst $(LOCAL_PATH)/,,$(openpgp_3))

exception_1 := $(shell find $(LOCAL_PATH)/src/exception -type d)
exception_2 := $(shell find $(exception_1) -name *.cpp)
exception_3 := $(sort $(exception_2))
exception := $(subst $(LOCAL_PATH)/,,$(exception_3))

encrypt_1 := $(shell find $(LOCAL_PATH)/src/encryption -type d)
encrypt_2 := $(shell find $(encrypt_1) -name *.cpp)
encrypt_3 := $(sort $(encrypt_2))
encrypt := $(subst $(LOCAL_PATH)/,,$(encrypt_3))

sub_package_1 := $(shell find $(LOCAL_PATH)/src/package/subpackage -type d)
sub_package_2 := $(shell find $(sub_package_1) -name *.cpp)
sub_package_3 := $(sort $(sub_package_2))
sub_package := $(subst $(LOCAL_PATH)/,,$(sub_package_3))

LOCAL_C_INCLUDES := $(LOCAL_PATH)/include/ $(LOCAL_PATH)/include/bzlib/
LOCAL_MODULE := libopenpgp
LOCAL_SRC_FILES := $(bzlib) \
$(openpgp) \
$(base) \
$(exception) \
$(utilities) \
$(compress) \
$(hash) \
$(package) \
$(sub_package) \
src/package/packet.cpp \
src/package/packets.cpp \
src/package/Partial.cpp \
src/package/s2k.cpp \
src/package/Tag0.cpp \
src/package/Tag1.cpp \
src/package/Tag10.cpp \
src/package/Tag11.cpp \
src/package/Tag12.cpp \
src/package/Tag13.cpp \
src/package/Tag14.cpp \
src/package/Tag17.cpp \
src/package/Tag18.cpp \
src/package/Tag19.cpp \
src/package/Tag2.cpp \
src/package/Tag3.cpp \
src/package/Tag4.cpp \
src/package/Tag5.cpp \
src/package/Tag6.cpp \
src/package/Tag60.cpp \
src/package/Tag61.cpp \
src/package/Tag62.cpp \
src/package/Tag63.cpp \
src/package/Tag7.cpp \
src/package/Tag8.cpp \
src/package/Tag9.cpp \
$(encrypt) \

LOCAL_SHARED_LIBRARIES := ssl crypto

LOCAL_LDLIBS := -lz
LOCAL_CFLAGS := -Wnarrowing
#LOCAL_CFLAGS += -O3
include $(BUILD_SHARED_LIBRARY)
include $(CLEAR_VARS)



