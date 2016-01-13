#!/bin/bash
temp_out=${PWD}/out;
pm_namespace=$"ProtonMail";

./run --idl open_pgp.djinni \
	\
	--cpp-out "$temp_out/cpp" \
	--cpp-header-out "$temp_out/cpp/bridge" \
    --cpp-namespace $pm_namespace \
    --ident-cpp-enum-type foo_bar \
    --ident-cpp-type-param fooBar \
    \
	--java-out "$temp_out/java/src" \
	--java-package ch.protonmail.android.utils \
	--java-nullable-annotation "javax.annotation.CheckForNull" \
    --java-nonnull-annotation "javax.annotation.Nonnull" \
    --ident-java-field mFooBar \
	\
	--jni-out "$temp_out/java/jni/generated_cpp" \
	--jni-header-out "$temp_out/java/jni/generated_h" \
	--jni-namespace $pm_namespace \
	--jni-base-lib-include-prefix jni_base/ \
	--jni-include-cpp-prefix bridge/ \
	--ident-jni-class NativeFooBar \
	--ident-jni-file NativeFooBar \
	\
	--objc-out "$temp_out/objc" \
	--objcpp-out "$temp_out/objc" \
	--objcpp-include-cpp-prefix bridge/ \
	--objcpp-namespace OBJ_$pm_namespace \
	--objc-type-prefix PMN \