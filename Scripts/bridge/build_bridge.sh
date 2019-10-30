#!/bin/bash

#    The MIT License
#
#    Copyright (c) 2019 Proton Technologies AG
#
#    Permission is hereby granted, free of charge, to any person obtaining a copy
#    of this software and associated documentation files (the "Software"), to deal
#    in the Software without restriction, including without limitation the rights
#    to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
#    copies of the Software, and to permit persons to whom the Software is
#    furnished to do so, subject to the following conditions:
#
#    The above copyright notice and this permission notice shall be included in
#    all copies or substantial portions of the Software.
#
#    THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
#    IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
#    FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
#    AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
#    LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
#    OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
#    THE SOFTWARE.

SCRIPT_LOCATION=$(cd $(dirname $0);echo $PWD)

temp_out=${SCRIPT_LOCATION}/out

cpp_pm_namespace="ProtonMail"
jni_pm_namespace="ProtonMail"
obj_pm_namespace="OBJ_ProtonMail"
java_package="ch.protonmail.android.utils.nativelib"

cpp_out_location=${SCRIPT_LOCATION}/../../Source/src/bridge
cpp_header_out_location=${SCRIPT_LOCATION}/../../Source/include/bridge

java_out_location=${SCRIPT_LOCATION}/../../Android_Test/app/src/main/java/ch/protonmail/android/utils/nativelib

jni_cpp_out_location=${SCRIPT_LOCATION}/../../Android_Build/OpenPGP.Android.Wrapper/jni/generated_cpp
jni_cpp_header_out_location=${SCRIPT_LOCATION}/../../Android_Build/OpenPGP.Android.Wrapper/jni/generated_h

objc_out=${SCRIPT_LOCATION}/../../OpenPGP/OpenPGPLib
objc_cpp_out=${SCRIPT_LOCATION}/../../OpenPGP/OpenPGPLib

rm -rf $java_out_location
rm -rf $jni_cpp_out_location
rm -rf $jni_cpp_header_out_location

${SCRIPT_LOCATION}/../../../djinni/src/run --idl ${SCRIPT_LOCATION}/open_pgp.djinni \
	\
	--cpp-out $cpp_out_location \
	--cpp-header-out $cpp_header_out_location \
    --cpp-namespace $cpp_pm_namespace \
    --ident-cpp-enum-type foo_bar \
    --ident-cpp-type-param fooBar \
    \
	--java-out $java_out_location \
	--java-package $java_package \
	--java-nullable-annotation "javax.annotation.CheckForNull" \
    --java-nonnull-annotation "javax.annotation.Nonnull" \
    --ident-java-field mFooBar \
	\
	--jni-out $jni_cpp_out_location \
	--jni-header-out $jni_cpp_header_out_location \
	--jni-namespace $jni_pm_namespace \
	--jni-base-lib-include-prefix jni_base_h/ \
	--jni-include-cpp-prefix bridge/ \
	--ident-jni-class NativeFooBar \
	--ident-jni-file NativeFooBar \
	\
	--objc-out $objc_out \
	--objcpp-out $objc_cpp_out \
	--objcpp-include-cpp-prefix bridge/ \
	--objcpp-namespace $obj_pm_namespace \
	--objc-type-prefix PMN \
