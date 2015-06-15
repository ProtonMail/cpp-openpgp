//
//  OpenPGP.m
//  OpenPGP
//
//  Created by Yanfeng Zhang on 1/29/15.
//  Copyright (c) 2015 Yanfeng Zhang. All rights reserved.
//

#import "OpenPGP.h"
#include <openpgp/PGPKey.h>
#include <openpgp/openpgp.h>
#include <openpgp/PGPMessage.h>
#include <openpgp/encrypt.h>
#include <openpgp/decrypt.h>
#include <exception>
#include <utilities/consts.h>
#include <utilities/base64.h>
#include <openpgp/cfb.h>
#include <utilities/UTF8.h>
#include <utilities/mpi.h>
#include <openssl/bio.h>
#include <openssl/evp.h>

#include <algorithm>
#include <stdexcept>
#include <codecvt>

#include <openpgp/openpgp.h>
#include <openpgp/PMPGPMessage.h>
#include <utilities/utility.h>
#include <utilities/utilities.h>
#include <utilities/UTF8.h>

#include <openpgp/private_key.h>


@implementation OpenPGP
{
    PGPSecretKey* private_key_;
    PGPPublicKey* public_key_;
    BOOL isPrivKeyLoaded;
    BOOL isPubKeyLoaded;
    
    BOOL IsPasspharseRight;
    NSString* Passpharse;
    BOOL isDebugMode;
    
    pm::pgp::openpgp test;
}


- (id)init
{
    self = [super init];
    if ( self )
    {
        private_key_ = new PGPSecretKey();
        private_key_->set_is_debug(false);
        
        public_key_ = new PGPPublicKey();
        public_key_->set_is_debug(false);
        
        isDebugMode = false;
        IsPasspharseRight = false;
        Passpharse = @"";
        
        isPrivKeyLoaded = false;
        isPubKeyLoaded = false;
    }
    return self;
}

- (void)dealloc
{
    delete private_key_;
    delete public_key_;
    //[super dealloc];
}

- (BOOL) SetupKeys:(NSString *)priv_key pubKey:(NSString *)pub_key pass:(NSString*) passphrase error:(NSError **) err;
{
    try
    {
        std::string str_priv_key = [priv_key UTF8String];
        
        if(isDebugMode)
            std::cout << str_priv_key;
        
        private_key_->read(str_priv_key);
        
        //std::cout << "KeyID:" << hexlify(private_key_->keyid()) << std::endl;
        
        std::string tmp = [pub_key UTF8String];
        public_key_->read(tmp);
        
        std::string verifyString = "this is a protonmail encryption test string";
        PGPMessage encrypted = encrypt_pka(*public_key_, verifyString);
        
        std::string clain_txt = decrypt_pka(*private_key_, encrypted, [passphrase UTF8String], false);
        if(verifyString == clain_txt)
        {
            Passpharse = passphrase;
            IsPasspharseRight = YES;
            return true;
        }
    }
    catch (const std::runtime_error& error)
    {
        if (err)
        {
            NSString *domain = @"com.ProtonMail.OpenPGP";
            NSString *desc = NSLocalizedString([NSString stringWithUTF8String:error.what()] , @"");
            NSDictionary *userInfo = @{ NSLocalizedDescriptionKey : desc };
            
            *err = [NSError errorWithDomain:domain code:10001 userInfo:userInfo];
        }
    }
    catch (const std::exception& e)
    {
        if (err)
        {
            NSString *domain = @"com.ProtonMail.OpenPGP";
            NSString *desc = NSLocalizedString([NSString stringWithUTF8String:e.what()] , @"");
            NSDictionary *userInfo = @{ NSLocalizedDescriptionKey : desc };
            
            *err = [NSError errorWithDomain:domain code:10002 userInfo:userInfo];
        }
        
    }
    catch (...)
    {
        if (err)
        {
            NSString *domain = @"com.ProtonMail.OpenPGP";
            NSString *desc = NSLocalizedString(@"Unknow errors", @"");
            NSDictionary *userInfo = @{ NSLocalizedDescriptionKey : desc };
            
            *err = [NSError errorWithDomain:domain code:10003 userInfo:userInfo];
        }
        
    }
    
    return false;
}


//Encrypt for user self
- (NSString *) encrypt_message:(NSString*) unencrypt_message error:(NSError**) err
{
    try
    {
        if(!IsPasspharseRight)
        {
            NSString *domain = @"com.ProtonMail.OpenPGP";
            NSString *desc = NSLocalizedString(@"you need load public key first" , @"");
            NSDictionary *userInfo = @{ NSLocalizedDescriptionKey : desc };
            
            *err = [NSError errorWithDomain:domain code:10004 userInfo:userInfo];
            return nil;
        }
        std::string unencrypt_msg = [unencrypt_message UTF8String];

        PGPMessage encrypted_pgp = encrypt_pka(*public_key_, unencrypt_msg);
        std::string encrypt_message = encrypted_pgp.write();
        return [[NSString alloc] initWithUTF8String:encrypt_message.c_str()];
    }
    catch (const std::runtime_error& error)
    {
        if (err)
        {
            NSString *domain = @"com.ProtonMail.OpenPGP";
            NSString *desc = NSLocalizedString([NSString stringWithUTF8String:error.what()] , @"");
            NSDictionary *userInfo = @{ NSLocalizedDescriptionKey : desc };
            
            *err = [NSError errorWithDomain:domain code:10001 userInfo:userInfo];
        }
    }
    catch (const std::exception& e)
    {
        if (err)
        {
            NSString *domain = @"com.ProtonMail.OpenPGP";
            NSString *desc = NSLocalizedString([NSString stringWithUTF8String:e.what()] , @"");
            NSDictionary *userInfo = @{ NSLocalizedDescriptionKey : desc };
            
            *err = [NSError errorWithDomain:domain code:10002 userInfo:userInfo];
        }
        
    }
    catch (...)
    {
        if (err)
        {
            NSString *domain = @"com.ProtonMail.OpenPGP";
            NSString *desc = NSLocalizedString(@"Unknow errors", @"");
            NSDictionary *userInfo = @{ NSLocalizedDescriptionKey : desc };
            
            *err = [NSError errorWithDomain:domain code:10003 userInfo:userInfo];
        }
        
    }
    return nil;
    
}

- (NSString *) encrypt_message:(NSString*) unencrypt_message pub_key:(NSString *)pub_key error:(NSError**) err;
{
    try
    {
        std::string unencrypt_msg = [unencrypt_message UTF8String];
        std::string user_pub_key = [pub_key UTF8String];
        PGPPublicKey pub(user_pub_key);
        PGPMessage encrypted_pgp = encrypt_pka(pub, unencrypt_msg);
        std::string encrypt_message = encrypted_pgp.write();        
        return [[NSString alloc] initWithUTF8String:encrypt_message.c_str()];
    }
    catch (const std::runtime_error& error)
    {
        if (err)
        {
            NSString *domain = @"com.ProtonMail.OpenPGP";
            NSString *desc = NSLocalizedString([NSString stringWithUTF8String:error.what()] , @"");
            NSDictionary *userInfo = @{ NSLocalizedDescriptionKey : desc };
            
            *err = [NSError errorWithDomain:domain code:10001 userInfo:userInfo];
        }
    }
    catch (const std::exception& e)
    {
        if (err)
        {
            NSString *domain = @"com.ProtonMail.OpenPGP";
            NSString *desc = NSLocalizedString([NSString stringWithUTF8String:e.what()] , @"");
            NSDictionary *userInfo = @{ NSLocalizedDescriptionKey : desc };
            
            *err = [NSError errorWithDomain:domain code:10002 userInfo:userInfo];
        }
        
    }
    catch (...)
    {
        if (err)
        {
            NSString *domain = @"com.ProtonMail.OpenPGP";
            NSString *desc = NSLocalizedString(@"Unknow errors", @"");
            NSDictionary *userInfo = @{ NSLocalizedDescriptionKey : desc };
            
            *err = [NSError errorWithDomain:domain code:10003 userInfo:userInfo];
        }
        
    }
    return nil;
    
}


- (NSString *) decrypt_message:(NSString*) encrypted_message error:(NSError**) err
{
    try
    {
        if(encrypted_message.length <= 0 )
        {
            if (err)
            {
                NSString *domain = @"com.ProtonMail.OpenPGP";
                NSString *desc = NSLocalizedString(@"The input message is not valid" , @"");
                NSDictionary *userInfo = @{ NSLocalizedDescriptionKey : desc };
                
                *err = [NSError errorWithDomain:domain code:10005 userInfo:userInfo];
            }
            return nil;
        }
        
        if(!IsPasspharseRight)
        {
            if (err)
            {
                NSString *domain = @"com.ProtonMail.OpenPGP";
                NSString *desc = NSLocalizedString(@"you need load private key first" , @"");
                NSDictionary *userInfo = @{ NSLocalizedDescriptionKey : desc };
                
                *err = [NSError errorWithDomain:domain code:10004 userInfo:userInfo];
            }
            return nil;
        }
        std::string encrypt_msg = [encrypted_message UTF8String];
        
        pm::PMPGPMessage pm_pgp_msg(encrypt_msg);
        
        std::string test_plain_txt = decrypt_pka(*private_key_, pm_pgp_msg, [self->Passpharse UTF8String], false);
        
        return [[NSString alloc] initWithUTF8String:test_plain_txt.c_str()];
    }
    catch (const std::runtime_error& error)
    {
        if (err)
        {
            NSString *domain = @"com.ProtonMail.OpenPGP";
            NSString *desc = NSLocalizedString([NSString stringWithUTF8String:error.what()] , @"");
            NSDictionary *userInfo = @{ NSLocalizedDescriptionKey : desc };
            
            *err = [NSError errorWithDomain:domain code:10001 userInfo:userInfo];
        }
    }
    catch (const std::exception& e)
    {
        if (err)
        {
            NSString *domain = @"com.ProtonMail.OpenPGP";
            NSString *desc = NSLocalizedString([NSString stringWithUTF8String:e.what()] , @"");
            NSDictionary *userInfo = @{ NSLocalizedDescriptionKey : desc };
            
            *err = [NSError errorWithDomain:domain code:10002 userInfo:userInfo];
        }
        
    }
    catch (...)
    {
        if (err)
        {
            NSString *domain = @"com.ProtonMail.OpenPGP";
            NSString *desc = NSLocalizedString(@"Unknow errors", @"");
            NSDictionary *userInfo = @{ NSLocalizedDescriptionKey : desc };
            
            *err = [NSError errorWithDomain:domain code:10003 userInfo:userInfo];
        }
    }
    return nil;
}



//Encrypt message use aes with pwd
- (NSString *) encrypt_message_aes:(NSString*) unencrypt_message pwd:(NSString *)password error:(NSError**) err
{
    try
    {
        std::string unencrypt_msg = [unencrypt_message UTF8String];
        std::string pwd = [password UTF8String];

        PGPMessage encrypted_sym = encrypt_sym(pwd, unencrypt_msg, "", 9, 0, true, nullptr, "");
        std::string encrypt_message = encrypted_sym.write();
        
        return [[NSString alloc] initWithUTF8String:encrypt_message.c_str()];
    }
    catch (const std::runtime_error& error)
    {
        if (err)
        {
            NSString *domain = @"com.ProtonMail.OpenPGP";
            NSString *desc = NSLocalizedString([NSString stringWithUTF8String:error.what()] , @"");
            NSDictionary *userInfo = @{ NSLocalizedDescriptionKey : desc };
            
            *err = [NSError errorWithDomain:domain code:10001 userInfo:userInfo];
        }
    }
    catch (const std::exception& e)
    {
        if (err)
        {
            NSString *domain = @"com.ProtonMail.OpenPGP";
            NSString *desc = NSLocalizedString([NSString stringWithUTF8String:e.what()] , @"");
            NSDictionary *userInfo = @{ NSLocalizedDescriptionKey : desc };
            
            *err = [NSError errorWithDomain:domain code:10002 userInfo:userInfo];
        }
        
    }
    catch (...)
    {
        if (err)
        {
            NSString *domain = @"com.ProtonMail.OpenPGP";
            NSString *desc = NSLocalizedString(@"Unknow errors", @"");
            NSDictionary *userInfo = @{ NSLocalizedDescriptionKey : desc };
            
            *err = [NSError errorWithDomain:domain code:10003 userInfo:userInfo];
        }
        
    }
    return nil;
}
//Decrypt message use aes with pwd
- (NSString *) decrypt_message_aes:(NSString*) encrypted_message pwd:(NSString *)password error:(NSError**) err
{
    try
    {
        if(encrypted_message.length <= 0 )
        {
            if (err)
            {
                NSString *domain = @"com.ProtonMail.OpenPGP";
                NSString *desc = NSLocalizedString(@"The input message is not valid" , @"");
                NSDictionary *userInfo = @{ NSLocalizedDescriptionKey : desc };
                
                *err = [NSError errorWithDomain:domain code:10005 userInfo:userInfo];
            }
            return nil;
        }
        
        if(password.length <= 0)
        {
            if (err)
            {
                NSString *domain = @"com.ProtonMail.OpenPGP";
                NSString *desc = NSLocalizedString(@"The input password is not valid" , @"");
                NSDictionary *userInfo = @{ NSLocalizedDescriptionKey : desc };
                *err = [NSError errorWithDomain:domain code:10004 userInfo:userInfo];
            }
            return nil;
        }
        std::string encrypt_msg = [encrypted_message UTF8String];
        std::string pwd = [password UTF8String];
        pm::PMPGPMessage pm_pgp_msg(encrypt_msg);
        std::string out_unencrypt_msg = decrypt_sym(pm_pgp_msg, pwd);
        return [[NSString alloc] initWithUTF8String:out_unencrypt_msg.c_str()];
    }
    catch (const std::runtime_error& error)
    {
        if (err)
        {
            NSString *domain = @"com.ProtonMail.OpenPGP";
            NSString *desc = NSLocalizedString([NSString stringWithUTF8String:error.what()] , @"");
            NSDictionary *userInfo = @{ NSLocalizedDescriptionKey : desc };
            
            *err = [NSError errorWithDomain:domain code:10001 userInfo:userInfo];
        }
    }
    catch (const std::exception& e)
    {
        if (err)
        {
            NSString *domain = @"com.ProtonMail.OpenPGP";
            NSString *desc = NSLocalizedString([NSString stringWithUTF8String:e.what()] , @"");
            NSDictionary *userInfo = @{ NSLocalizedDescriptionKey : desc };
            
            *err = [NSError errorWithDomain:domain code:10002 userInfo:userInfo];
        }
        
    }
    catch (...)
    {
        if (err)
        {
            NSString *domain = @"com.ProtonMail.OpenPGP";
            NSString *desc = NSLocalizedString(@"Unknow errors", @"");
            NSDictionary *userInfo = @{ NSLocalizedDescriptionKey : desc };
            
            *err = [NSError errorWithDomain:domain code:10003 userInfo:userInfo];
        }
    }
    return nil;
}




- (NSString *)update_key_password:(NSString*)old_passphrase new_pwd:(NSString*) new_passphrase error:(NSError**) err
{
    try
    {
        if(old_passphrase.length <= 0 )
        {
            if (err)
            {
                NSString *domain = @"com.ProtonMail.OpenPGP";
                NSString *desc = NSLocalizedString(@"The input message is not valid" , @"");
                NSDictionary *userInfo = @{ NSLocalizedDescriptionKey : desc };
                
                *err = [NSError errorWithDomain:domain code:10005 userInfo:userInfo];
            }
            return nil;
        }
        
        if(!IsPasspharseRight)
        {
            if (err)
            {
                NSString *domain = @"com.ProtonMail.OpenPGP";
                NSString *desc = NSLocalizedString(@"you need load private key first" , @"");
                NSDictionary *userInfo = @{ NSLocalizedDescriptionKey : desc };
                
                *err = [NSError errorWithDomain:domain code:10004 userInfo:userInfo];
            }
            return nil;
        }
        
        std::string str_old_passphrase = [old_passphrase UTF8String];
        std::string str_new_passphrase = [new_passphrase UTF8String];
        
//need add more error handling
        std::string new_key = pm::pgp::update_passphrase(*private_key_, str_old_passphrase, str_new_passphrase);
        
        return [[NSString alloc] initWithUTF8String:new_key.c_str()];
    }
    catch (const std::runtime_error& error)
    {
        if (err)
        {
            NSString *domain = @"com.ProtonMail.OpenPGP";
            NSString *desc = NSLocalizedString([NSString stringWithUTF8String:error.what()] , @"");
            NSDictionary *userInfo = @{ NSLocalizedDescriptionKey : desc };
            
            *err = [NSError errorWithDomain:domain code:10001 userInfo:userInfo];
        }
    }
    catch (const std::exception& e)
    {
        if (err)
        {
            NSString *domain = @"com.ProtonMail.OpenPGP";
            NSString *desc = NSLocalizedString([NSString stringWithUTF8String:e.what()] , @"");
            NSDictionary *userInfo = @{ NSLocalizedDescriptionKey : desc };
            
            *err = [NSError errorWithDomain:domain code:10002 userInfo:userInfo];
        }
        
    }
    catch (...)
    {
        if (err)
        {
            NSString *domain = @"com.ProtonMail.OpenPGP";
            NSString *desc = NSLocalizedString(@"Unknow errors", @"");
            NSDictionary *userInfo = @{ NSLocalizedDescriptionKey : desc };
            
            *err = [NSError errorWithDomain:domain code:10003 userInfo:userInfo];
        }
    }

    return [[NSString alloc] initWithUTF8String:""];
}


//Generate new key pair
- (NSMutableDictionary* ) generate_key:(NSString*)passphrase username:(NSString*)user_name error:(NSError**) err
{
    pm::pgp::openpgp p;
    
    
    std::string pwd = [passphrase UTF8String];
    
    std::string name = [user_name UTF8String];
    std::string email = name + "@protonmail.ch";
    std::string comments = "create by ios";
    
    std::string priv_key = "";
    std::string pub_key = "";
    p.generate_new_key(2048, pwd, name, email, comments, pub_key, priv_key);
    
    
    
    NSMutableDictionary *dictX = [[NSMutableDictionary alloc] init];
    
    [dictX setObject:[[NSString alloc] initWithUTF8String:pub_key.c_str()] forKey:@"public"];
    [dictX setObject:[[NSString alloc] initWithUTF8String:priv_key.c_str()] forKey:@"private"];
    
    
    
    return dictX;
}
- (void)Test_Privatekey:(NSString *)priv_key pass:(NSString*) passphrase
{
    std::string str_priv_key = [priv_key UTF8String];
    

    
    private_key_->read(str_priv_key);
    
    
//    //std::cout << "KeyID:" << hexlify(private_key_->keyid()) << std::endl;
//    
//    std::string tmp = [pub_key UTF8String];
//    public_key_->read(tmp);
//    
//    std::string verifyString = "this is a protonmail encryption test string";
//    PGPMessage encrypted = encrypt_pka(*public_key_, verifyString);
//    
//    std::string clain_txt = decrypt_pka(*private_key_, encrypted, [passphrase UTF8String], false);
//    if(verifyString == clain_txt)
//    {
//        Passpharse = passphrase;
//        IsPasspharseRight = YES;
//        return true;
//    }
//
}
- (NSString* ) encrypt_mailbox_pwd:(NSString *)plain slat:(NSString*) value
{
    std::string outString = pm::encrypt_mailbox_password( [plain UTF8String], [value UTF8String]);
    return [[NSString alloc] initWithUTF8String:outString.c_str()];
}

- (NSString* ) decrypt_mailbox_pwd:(NSString *)encrypt_text slat:(NSString*) value
{
    std::string outString = pm::decrypt_mailbox_password([encrypt_text UTF8String], [value UTF8String]);
    
    NSData *decodedData = [[NSData alloc] initWithBase64EncodedString:[[NSString alloc] initWithUTF8String:outString.c_str()] options:0];
    NSString *decodedString = [[NSString alloc] initWithData:decodedData encoding:NSUTF8StringEncoding];
    NSLog(@"%@", decodedString); // foo
    
   // outString
    return decodedString;//[[NSString alloc] initWithUTF8String:outString.c_str()];
}

- (void)EnableDebug:(BOOL) isDebug
{
    isDebugMode = isDebug;
}


- (NSData *) decrypt_attachment:(NSData*) keyPackage data:(NSData*) dataPackage error:(NSError**) err
{
    std::string str_key_package = std::string((char* )[keyPackage bytes], [keyPackage length]);
    std::string str_data_package = std::string((char* )[dataPackage bytes], [dataPackage length]);
    
    
    pm::PMPGPMessage pm_pgp_msg(str_key_package);
    pm_pgp_msg.append(str_data_package);
    
    std::string test_plain_txt = decrypt_pka(*private_key_, pm_pgp_msg, [self->Passpharse UTF8String], false);
    
    //std::cout  << test_plain_txt << std::endl;
    return [NSData dataWithBytes: test_plain_txt.c_str() length:test_plain_txt.length()];
}

- (NSData *) decrypt_attachment_armored:(NSString*) keyPackage data:(NSString*) dataPackage error:(NSError**) err
{
    std::string str_key_package = [keyPackage UTF8String];
    std::string str_data_package = [dataPackage UTF8String];
    
    pm::PMPGPMessage pm_pgp_msg(str_key_package);
    pm_pgp_msg.append(str_data_package);
    
    std::string test_plain_txt = decrypt_pka(*private_key_, pm_pgp_msg, [self->Passpharse UTF8String], false);
    
    //std::cout  << test_plain_txt << std::endl;
    return [NSData dataWithBytes: test_plain_txt.c_str() length:test_plain_txt.length()];
}


//encrypt decrypt attachment
// ["dataPacket"]
// ["keyPacket"]
- (NSMutableDictionary*) encrypt_attachment:(NSData *) unencrypt_att pub_key:(NSString *)pub_key error:(NSError**) err
{
    NSMutableDictionary *dictX = [[NSMutableDictionary alloc] init];
    
    //NSData to string  need error handling here
    std::string unencrypt_msg = std::string((char* )[unencrypt_att bytes], [unencrypt_att length]);
    
   // std::cout << hexlify(unencrypt_msg) << std::endl;
    std::string user_pub_key = [pub_key UTF8String];
    
    PGPPublicKey pub(user_pub_key);
    
    PGPMessage encrypted_pgp = encrypt_pka(pub, unencrypt_msg);
    
    std::string keyPackage = encrypted_pgp.write(0, 0, 1);
    std::string dataPackage = encrypted_pgp.write(0, 0, 18);
    
    
    [dictX setObject:[[NSString alloc] initWithUTF8String:dataPackage.c_str()] forKey:@"DataPacket"];
    [dictX setObject:[[NSString alloc] initWithUTF8String:keyPackage.c_str()] forKey:@"KeyPacket"];

    
    //std::cout << keyPackage << std::endl;
    //std::cout << dataPackage << std::endl;
    
    return dictX;
}


//encrypt decrypt attachment
// ["dataPacket"]
// ["keyPackets"]
//        ["email" : "KeyP"]
//        ["email" : "KeyP"]
- (NSMutableDictionary*) encrypt_attachments:(NSData *) unencrypt_att pub_keys:(NSMutableDictionary*)pub_keys error:(NSError**) err
{
    NSMutableDictionary *dictX = [[NSMutableDictionary alloc] init];
    
    std::string unencrypt_attachment = std::string((char* )[unencrypt_att bytes], [unencrypt_att length]);
    std::string session_key = generat_session_key();
    
    for(id key in pub_keys)
    {
        std::string user_pub_key = [pub_keys[key] UTF8String];
        PGPPublicKey pub(user_pub_key);
        PGPMessage enrypted_session_key = encrypt_pka_only_session(pub, session_key);
        [dictX setObject:[[NSString alloc] initWithUTF8String:enrypted_session_key.write().c_str()] forKey:key];
    }
    
    PGPMessage encrypted_att = encrypt_pka_only_data(session_key, unencrypt_attachment);
    [dictX setObject:[[NSString alloc] initWithUTF8String:encrypted_att.write().c_str()] forKey:@"DataPacket"];

    return dictX;
}


- (NSData * ) Test_Attachment:(NSString*) package data:(NSString*) datapackage
{
    std::string encrypt_msg = "wcBMA9ted+lmZVn8AQf/Q41P+zzGgasmskYRZQ5joeQnDOcqE0jS4+YSkFNZ1sViMf35B6ohO7lu3hqyxehXNxsDZvBDwBPYK5foJn/ozTVGiPNszW6x9qM3dNN0KRzpHgoNYyqGiG2jeWjfztCui7jtEVcYQTH0vD5F4RGFVQ0RjHA2cufuVFpJzlevwdkU2D9tY/U2ZzpoNkkTHR3KcmPmSaZVQKIVnM97AJM1W0MSCVH+Fai9vvd0roobp2NTBZes0bZdQ8c2W7Kx04xU7YMcSvGjSmpdSL/RJM/lr/oZDqtUrmvOmuGB5cncHp4Bw0qxQVciehy4pIceJWSsEObC5RXvnicL4x+nqXpFog==";

    std::string data = [datapackage UTF8String];
    
    data = unhexlify(data);
    
    // std::cout << hexlify(data) << std::endl;
    
    std::string one = base64_decode(encrypt_msg);
   // std::cout << hexlify(one) << std::endl;
    
    
    std::string two = base64_encode(one);
    //std::cout << two << std::endl;
    
    pm::PMPGPMessage pm_pgp_msg(one);
    
    pm_pgp_msg.append(data);
    
    std::string test_plain_txt = decrypt_pka(*private_key_, pm_pgp_msg, [self->Passpharse UTF8String], false);
    
    //std::cout  << test_plain_txt << std::endl;
    
    return [NSData dataWithBytes: test_plain_txt.c_str() length:test_plain_txt.length()];
}

- (void)Test
{
    //test.generate_new_key(2048, "123", "100");
}

- (NSData*)Test_1
{
    
    char * pr = new char(1.56 * 1000 * 1000);
    memset(pr, 1, 1.56 * 1000 * 1000);
    return [[NSData alloc] initWithBytes:pr length:1.56 * 1000 * 1000];
}

- (NSString*)Test_2
{
    std::string test = "";
   // std::cout << pm::decrypt_message_id(test) << std::endl;
    
    return @"";
}


@end
