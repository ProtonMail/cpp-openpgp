//
//  OpenPGP.h
//  OpenPGP
//
//  Created by Yanfeng Zhang on 1/29/15.
//  Copyright (c) 2015 Yanfeng Zhang. All rights reserved.
//

#import <Foundation/Foundation.h>



@interface OpenPGP : NSObject


// self keys setup up for login user
- (BOOL) SetupKeys:(NSString *)priv_key pubKey:(NSString *)pub_key pass:(NSString*) passphrase error:(NSError* *) err;

//Encrypt for user self
- (NSString *) encrypt_message:(NSString*) unencrypt_message error:(NSError**) err;

//Encrypt message use public key(other people's key)
- (NSString *) encrypt_message:(NSString*) unencrypt_message pub_key:(NSString *)pub_key error:(NSError**) err;

//Decrypt message user Private key
- (NSString *) decrypt_message:(NSString*) encrypted_message error:(NSError**) err;


- (void)EnableDebug:(BOOL) isDebug;


@end

