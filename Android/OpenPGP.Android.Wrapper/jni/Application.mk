NDK_TOOLCHAIN_VERSION := 4.8
APP_PLATFORM := android-14
APP_STL	:= gnustl_static
PP_CFLAGS := -O3 -std=gnu99
APP_CPPFLAGS := -fexceptions -frtti
APP_CPPFLAGS += -O3 -std=gnu++11
APP_ABI := armeabi armeabi-v7a #all #arm64-v8a
APP_OPTIM := release