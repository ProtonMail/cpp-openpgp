set(CMAKE_LEGACY_CYGWIN_WIN32 0)
cmake_minimum_required(VERSION 2.6)
project(pmopenpgp)

set(LIBCXX_STL "${ANDROID_NDK}/sources/cxx-stl/gnu-libstdc++/4.8/libs/armeabi-v7a/thumb/libgnustl_static.a")

set(ANDROID_STL_FLAGS
    ${LIBCXX_STL}
    atomic
    dl
    gcc
    c
    m
    -nodefaultlibs
    )


add_subdirectory(samples)


option(BUILD_SHARED_LIBS "Build shared Libraries." OFF)

set(Casablanca_LIBRARY ${LIB}cpprest)


set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -fno-strict-aliasing")
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-pedantic")
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-attributes -Wno-pointer-arith")
  include_directories(
    "${ANDROID_NDK}/sources/cxx-stl/gnu-libstdc++/4.8/include"
    "${ANDROID_NDK}/sources/cxx-stl/gnu-libstdc++/4.8/libs/armeabi-v7a/include"
    "${ANDROID_NDK}/sources/cxx-stl/gnu-libstdc++/4.8/include/backward"
    )



# Reconfigure final output directory
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/Binaries)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/Binaries)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/Binaries)