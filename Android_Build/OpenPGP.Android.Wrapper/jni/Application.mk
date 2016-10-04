NDK_TOOLCHAIN_VERSION := 4.9
APP_PLATFORM := android-14
APP_STL	:= gnustl_shared
#APP_CFLAGS := -std=gnu99
APP_CPPFLAGS := -fexceptions -frtti
APP_CPPFLAGS += -std=gnu++11
APP_OPTIM := release
APP_ABI := x86 x86_64 armeabi-v7a armeabi arm64-v8a