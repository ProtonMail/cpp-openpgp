



cp -L ../Bin/libs/Release-iphoneos/libOpenPGP.a ../out/OpenPGP/iOS/libOpenPGP.a
cp -L ../Bin/libs/Release/libOpenPGP_x86_64.a  ../out/OpenPGP/Simulator/libOpenPGP.a



lipo -create ../out/OpenPGP/Simulator/libOpenPGP.a ../out/OpenPGP/iOS/libOpenPGP.a -o ../out/OpenPGP/libOpenPGP.a


cp -L ../Bin/include/OpenPGP_IOS/OpenPGP.h ../out/include/openpgp/OpenPGP.h