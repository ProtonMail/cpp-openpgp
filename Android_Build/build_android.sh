#!/bin/bash
printf "\e[0;34m#######################################################\033[0m\n";
printf "\e[0;36m################ \e[0;32mProtonMail OpenPGP\033[0m \e[0;36m###################\033[0m\n";
printf "\e[0;34m#######################################################\033[0m\n";
printf "\e[0;32mInitial Building scripts. \033[0m\n"
SCRIPT_DIR=${PWD};
SOURCE_DIR=${PWD}/../Source/
OUT_PUT_DIR=${SCRIPT_DIR}/../Bin/android_libs/

PGP_DIR=${SCRIPT_DIR}/OpenPGP.Android
PGP_ANDROID_WRAPPER_DIR=${SCRIPT_DIR}/OpenPGP.Android.Wrapper

if [  ! -d $PGP_DIR ]; then
  mkdir $PGP_DIR
fi


cd ${PGP_DIR}
printf "\e[0;37mEnterDirectory:\033[0m \e[0;36m ${PGP_DIR} \033[0m\n"
printf "\e[0;32mSetup Project Enviroment \033[0m\n"

export NDK_PROJECT_PATH=${PGP_DIR}
ln -s ${SOURCE_DIR} jni
ndk-build -j4 #-B -j4
rm ./jni
unset NDK_PROJECT_PATH
printf "\e[0;37mLeaveDirectory:\033[0m \e[0;36m ${PGP_DIR} \033[0m\n"
echo "";
cd ${PGP_ANDROID_WRAPPER_DIR}
printf "\e[0;37mEnterDirectory:\033[0m \e[0;36m ${PGP_ANDROID_WRAPPER_DIR} \033[0m\n"
printf "\e[0;32mSetup Wrapper Project Enviroment \033[0m\n"

export NDK_PROJECT_PATH=${PGP_ANDROID_WRAPPER_DIR}
cp -rf ${PGP_DIR}/libs ${PGP_ANDROID_WRAPPER_DIR}/jni/
rm -rf ${PGP_ANDROID_WRAPPER_DIR}/jni/include
cp -rf ${SOURCE_DIR}/include ${PGP_ANDROID_WRAPPER_DIR}/jni/include
ndk-build -j4 #-B -j4
unset NDK_PROJECT_PATH
printf "\e[0;37mLeaveDirectory:\033[0m \e[0;36m ${PGP_ANDROID_WRAPPER_DIR} \033[0m\n"
cd ../

printf "\e[0;36mCopying files to Bin folder ... \033[0m\n"
cp -rf ${PGP_ANDROID_WRAPPER_DIR}/libs/ ${OUT_PUT_DIR}/
cp -rf ${PGP_ANDROID_WRAPPER_DIR}/libs/ ${PWD}/../Android_Test/app/src/main/jniLibs/



echo "";
printf "\e[0;32mDONE \033[0m\n"

