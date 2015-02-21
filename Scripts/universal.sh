lipo -create SSL_Simulator8.1-i386/libcrypto.a SSL_Simulator8.1-x86_64/libcrypto.a SSL_iOS8.1-arm64/libcrypto.a SSL_iOS8.1-armv7/libcrypto.a SSL_iOS8.1-armv7s/libcrypto.a -o libcrypto.a




lipo -create SSL_Simulator8.1-i386/libssl.a SSL_Simulator8.1-x86_64/libssl.a SSL_iOS8.1-arm64/libssl.a SSL_iOS8.1-armv7/libssl.a SSL_iOS8.1-armv7s/libssl.a -o libssl.a










lipo -create Debug-iphoneos/libOpenPGP.a Debug-iphonesimulator/libOpenPGP.a -o libOpenPGP.a




lipo -create SSL_Simulator8.1-i386/libcrypto.a SSL_Simulator8.1-x86_64/libcrypto.a -o Simulator_OpenSSL/libcrypto.a
lipo -create SSL_iOS8.1-arm64/libcrypto.a SSL_iOS8.1-armv7/libcrypto.a SSL_iOS8.1-armv7s/libcrypto.a  -o iPhoneOS_OpenSSL/libcrypto.a

lipo -create SSL_Simulator8.1-i386/libssl.a SSL_Simulator8.1-x86_64/libssl.a -o Simulator_OpenSSL/libssl.a
lipo -create  SSL_iOS8.1-arm64/libssl.a SSL_iOS8.1-armv7/libssl.a SSL_iOS8.1-armv7s/libssl.a -o iPhoneOS_OpenSSL/libssl.a






lipo -create Simulator/libOpenPGP.a iOS/libOpenPGP.a -o libOpenPGP.a

