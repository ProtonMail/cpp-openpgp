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
	LOCAL_MODULE    := openpgp
	LOCAL_SRC_FILES := libs/x86/libopenpgp.so
	include $(PREBUILT_SHARED_LIBRARY)