#!/bin/bash

echo "";
printf "\e[0;32mInitial Building scripts. \033[0m\n"
SCRIPT_DIR=${PWD};
SOURCE_DIR=${PWD}/../Source/

PGP_DIR=${SCRIPT_DIR}/OpenPGP.Android/
PGP_ANDROID_WRAPPER_DIR=${SCRIPT_DIR}/OpenPGP.Android.Wrapper/

cd ${PGP_DIR}
printf "\e[0;37mEnterDirectory:\033[0m \e[0;36m ${PGP_DIR} \033[0m\n"
printf "\e[0;32mSetup Project Enviroment \033[0m\n"

export NDK_PROJECT_PATH=${PGP_DIR}
ln -s ${SOURCE_DIR} jni
ndk-build -j6
rm ./jni
unset ${PGP_DIR}
printf "\e[0;37mLeaveDirectory:\033[0m \e[0;36m ${PGP_DIR} \033[0m\n"
echo "";
echo "";
cd ${PGP_ANDROID_WRAPPER_DIR}
printf "\e[0;37mEnterDirectory:\033[0m \e[0;36m ${PGP_ANDROID_WRAPPER_DIR} \033[0m\n"
printf "\e[0;32mSetup Wrapper Project Enviroment \033[0m\n"

export NDK_PROJECT_PATH=${PGP_ANDROID_WRAPPER_DIR}
cp -rf ${PGP_DIR}/libs ${PGP_ANDROID_WRAPPER_DIR}/jni/
ndk-build -j6
unset ${PGP_ANDROID_WRAPPER_DIR}
printf "\e[0;37mLeaveDirectory:\033[0m \e[0;36m ${PGP_ANDROID_WRAPPER_DIR} \033[0m\n"
cd ../

echo "";
printf "\e[0;32mDONE \033[0m\n"

