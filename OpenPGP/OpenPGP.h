//
//  OpenPGP.h
//  OpenPGP
//
//  Created by Yanfeng Zhang on 1/29/15.
//  Copyright (c) 2015 Yanfeng Zhang. All rights reserved.
//

#import <Foundation/Foundation.h>


#if defined __cplusplus
class PGPSecretKey;
class PGPPublicKey;
#else
struct PGPSecretKey;
struct PGPPublicKey;
#endif

@interface OpenPGP : NSObject
{
@private
    BOOL isPrivKeyLoaded;
    BOOL isPubKeyLoaded;
#if defined __cplusplus
    PGPSecretKey* private_key_;
    PGPPublicKey* public_key_;
#else
    struct PGPSecretKey* private_key_;
    struct PGPPublicKey* public_key_;
#endif
    
    
}

@property (nonatomic, assign) BOOL IsPasspharseRight;
@property (nonatomic, strong) NSString* Passpharse;

// self keys setup up for login user
- (BOOL) SetupKeys:(NSString *)priv_key pubKey:(NSString *)pub_key pass:(NSString*) passphrase;


//Encrypt message user public key
- (NSString *) encrypt_message:(NSString*) unencrypt_message pub_key:(NSString *)pub_key;

//
- (NSString *) decrypt_message:(NSString*) encrypted_message;



@end

