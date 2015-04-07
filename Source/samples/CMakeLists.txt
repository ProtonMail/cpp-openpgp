include_directories(../include)

set(SOURCES
    radix64.cpp)



add_library(${Casablanca_LIBRARY} ${SOURCES})


target_link_libraries(${Casablanca_LIBRARY} ${ANDROID_STL_FLAGS})


  # Portions specific to cpprest binary versioning.
set (CPPREST_VERSION_MAJOR 2)
set (CPPREST_VERSION_MINOR 5)
set (CPPREST_VERSION_REVISION 0)
