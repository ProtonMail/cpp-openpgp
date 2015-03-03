//
//  openpgp.cpp
//  UNNetPGP
//
//  Created by Yanfeng Zhang on 1/21/15.
//  Copyright (c) 2015 UP-NEXT. All rights reserved.
//

#include "openpgp.h"

#include <iostream>
#include <algorithm>
#include <string>


#include "config.h"
#include "RFC4880.h"


#ifdef HAVE_SYS_CDEFS_H
#include <sys/cdefs.h>
#endif

#if defined(__NetBSD__)
__COPYRIGHT("@(#) Copyright (c) 2009 The NetBSD Foundation, Inc. All rights reserved.");
__RCSID("$NetBSD: openssl_crypto.c,v 1.32 2010/11/07 06:56:52 agc Exp $");
#endif

#ifdef HAVE_OPENSSL_DSA_H
#include <openssl/dsa.h>
#endif

#ifdef HAVE_OPENSSL_RSA_H
#include <openssl/rsa.h>
#endif

#ifdef HAVE_OPENSSL_ERR_H
#include <openssl/err.h>
#endif

#include <openssl/pem.h>
#include <openssl/evp.h>

#include <stdlib.h>
#include <string.h>

#ifdef HAVE_UNISTD_H
#include <unistd.h>
#endif


#include "Tag5.h"
#include "rsa_key.h"
#include "BBS.h"
#include "Tag13.h"
#include "Tag2Sub2.h"
#include "Tag2Sub11.h"
#include "Tag2Sub16.h"
#include "Tag2Sub21.h"
#include "Tag2Sub22.h"
#include "Tag2Sub27.h"
#include "Tag2Sub30.h"
#include "Tag7.h"
#include "Tag2.h"
#include "PGPKey.h"
#include "cfb.h"
#include "sigcalc.h"


namespace pgp {

openpgp::openpgp()
{
    
}
openpgp::~openpgp()
{
    
}

void openpgp::encrypt_message()
{
   std::string n =  "6c9413c636b1c031b613ef5027c45e1ad16fdf72bcc23f6ef27759ed7be894286ca1caec77c46411207af007dcf26013c53915d7c1a4080376031fbdd89c4d053df8e1f9f05610d59728190e571d5179f3d3cad188c804c5b4bbe63750fae5692f9c87c175c39cec55a3e8de30e7239a8e92f7bbfe3a3deef7ca989c85ed745eec0ee35f7cabff186a61a94c5810563e07ed06edb88c6857eba62007fdea9f4f08c0318a917ea626a80fc2d85835022bfc2bd6d49722434a2fe642cae098c880273a58bbc6022528d096bc2f1cb2e24461c66599fe36fe21f2ad67aeb32ba62de04f8510018a413678f4a8f9723b2f39c3fc222b2e1124e91253df5f89474365";
    std::string e = "010001";
    
    
}

void openpgp::generate_new_key(int bits, std::string passphrase, std::string userid)
{
    BN_CTX *ctx= BN_CTX_new();
    BIGNUM* e = BN_new();
    RSA *rsa_key = RSA_new();
    RSA *rsa_sub_key = RSA_new();
    int iRet = BN_set_word(e, 65537);
    if(!iRet)
    {
        std::cout<<"BN_set_word error "<< std::endl;
        return ;
    }
    
    iRet =RSA_generate_key_ex(rsa_key, 2048, e, NULL);
    if(!iRet)
    {
        std::cout<<"RSA_generate_key_ex key error "<< std::endl;
        return ;
    }
    
    iRet =RSA_generate_key_ex(rsa_sub_key, 2048, e, NULL);
    if(!iRet)
    {
        std::cout<<"RSA_generate_key_ex sub_key error "<< std::endl;
        return ;
    }

    
    int ln;
    std::vector <std::string> rsa_pub_mpi;
    std::vector <std::string> rsa_priv_mpi;
    
    size_t length = 8192;
    uint8_t out[length];
    
    //public key part
//    ln = BN_bn2mpi(rsa_key->n, out);
//    rsa_pub_mpi.push_back(std::string((char*)out, ln));
//    ln = BN_bn2mpi(rsa_key->e, out);
//    rsa_pub_mpi.push_back(std::string((char*)out, ln));
    
    
    std::string pub_n = "000001006c9413c636b1c031b613ef5027c45e1ad16fdf72bcc23f6ef27759ed7be894286ca1caec77c46411207af007dcf26013c53915d7c1a4080376031fbdd89c4d053df8e1f9f05610d59728190e571d5179f3d3cad188c804c5b4bbe63750fae5692f9c87c175c39cec55a3e8de30e7239a8e92f7bbfe3a3deef7ca989c85ed745eec0ee35f7cabff186a61a94c5810563e07ed06edb88c6857eba62007fdea9f4f08c0318a917ea626a80fc2d85835022bfc2bd6d49722434a2fe642cae098c880273a58bbc6022528d096bc2f1cb2e24461c66599fe36fe21f2ad67aeb32ba62de04f8510018a413678f4a8f9723b2f39c3fc222b2e1124e91253df5f89474365";
    std::string pub_e = "00000003010001";
    rsa_pub_mpi.push_back(unhexlify(pub_n));
    rsa_pub_mpi.push_back(unhexlify(pub_e));
    
    
//D: 0000010011c751519465188e4b3d0a637a8f79c53463f8178676dc0223ab8d4b088df5ac84d51d3009105c3e3dae439d55fd4de40ed8210e7a038cd85c3b78b8123ecd91bd2b027d756ff243b70376ced54ed4a77e58408e7cb21badefc1109a202564e90b45bb28df4a8f6857418680d34b15965a20107674d33e8ee17e07ed2134d767f80dc756450bfa1f26957cb566fc7477f018b227b042c7e468811a74e7d8d71ea71fc372d00a6de6c0f17fed581d6a414d3f034dff4a665df75376f04ca7165d83648da646875306e186a0f6d8635dbc9b362cb298c09608208f31992331f02eb1e93fba9075cf81dab8f8409e1aa54c1e584fd824b8568292a2b6ea84603125
//P: 0000008100c786785df5ef37fdf0f9ff5f2e6aa1b78d2b457889ed713c7b0e0e2be361a2f059ede569509df48d0c175cd20f0983fbc239a21b91dc75ad459c62a4d87f06afa779abab414e3db0da75eeb7588821cd775d3d14a1872d3da0e64a4e609778467cfe795bf852487bedfe0d970289feadc1c15411933ca4d8f65d513e5d6d0ea3
//Q: 00000081008b4fa19051e3e5d3b95914a94c9faebe256ea8a97d18acef1b0ec13fef2bb58d9a20d788038fcc8d96e821ba6c1ff62ae4fcaa679bfc742aea0410f6bc15f6aa4fa838f5fc72370c36ca37918bdc8c693f51e6968d34ad04e48e8c52bac1b62dc2e2b226dff66453e887fc9ba89b47b781c7319debd57f289506ab3464722e57
//U: 00000080296ebe38400198771d0125a9c5768df98cab22743e57cfe0726c35cc2280f5598b2cbdeca3fa1100073710ba6f15e9d206174a59b19c631287c85b9b4bb88d806b88ed2e50ad3f885040fab3bb2adb952d135e629215ea17a68913575c4e88477b0babb8c5e7c0fcc2468f39e8f0152a380e0543c05884a545dcc079e1a911ef

    
    //private key part
    ln = BN_bn2mpi(rsa_key->d, out);
    rsa_priv_mpi.push_back(std::string((char*)out, ln));
    ln = BN_bn2mpi(rsa_key->p, out);
    rsa_priv_mpi.push_back(std::string((char*)out, ln));
    ln = BN_bn2mpi(rsa_key->q, out);
    rsa_priv_mpi.push_back(std::string((char*)out, ln));
    ln = BN_bn2mpi(BN_mod_inverse(NULL, rsa_key->p, rsa_key->q, ctx), out);
    rsa_priv_mpi.push_back(std::string((char*)out, ln));
    
    
    //Key creation time
    time_t time = now();
    time = 1419998489;
    
    
    
    // Secret Key Packet
    Tag5::Ptr sec = std::make_shared<Tag5>();
    sec -> set_version(RFC4880_V4);
    sec -> set_time(time);
    sec -> set_pka(RFC4880_PKA_RSA);//RSA
    sec -> set_mpi(rsa_pub_mpi);
    sec -> set_s2k_con(RFC4880_S2KU_ENCRYPTED_AND_HASHED);
    sec -> set_sym(RFC4880_SA_AES_256);// AES256
    

    // Secret Key Packet S2K
    S2K3::Ptr sec_s2k3 = std::make_shared<S2K3>();
    sec_s2k3 -> set_hash(RFC4880_HASH_SHA1);
    std::string salt_s = "vegAbuFronCachmAhavdadqUetetnoadcaryosaClmQYczXKRVyosaClmQYczXKR";
    sec_s2k3 -> set_salt(unhexlify(bintohex(salt_s)));
    sec_s2k3 -> set_count(96);
    
       // calculate the key from the passphrase
    std::string key = sec_s2k3 -> run(passphrase, Symmetric_Algorithm_Key_Length.at(Symmetric_Algorithms.at(sec -> get_sym())) >> 3);
    // encrypt private key value
    sec -> set_s2k(sec_s2k3);
   // uint16_t p_bits = Symmetric_Algorithm_Block_Length.at(Symmetric_Algorithms.at(sec -> get_sym()));
    std::string IV_S = "vegAbuFronCachmAhavdadqUetetnovegAbuFronCachmAhavdadqUetetnoadcaryosaClmQYczXKRVyosaClmQYczXKRadcaryosaClmQYczXKRVyosaClmQYczXKR";
    sec -> set_IV(unhexlify(bintohex(IV_S)));
    std::string secret = write_MPI(rsa_priv_mpi[0]) + write_MPI(rsa_priv_mpi[1]) + write_MPI(rsa_priv_mpi[2]) + write_MPI(rsa_priv_mpi[3]);
    sec -> set_secret(use_normal_CFB_encrypt(9, secret + use_hash(2, secret), key, sec -> get_IV()));
    
    std::string keyid = sec -> get_keyid();
    
    if(get_is_debug())
        std::cout << "KeyID:" << hexlify(keyid) << std::endl;
    
    Tag13::Ptr uid = std::make_shared<Tag13>();
    uid -> set_name(userid);
    uid -> set_comment("this is protonmail test");
    uid -> set_email("zhj4478@gmail.com");
    
    Tag2::Ptr sig = std::make_shared<Tag2>();
    sig -> set_version(RFC4880_V4);
    sig -> set_type(RFC4880_CERT_GENERIC);
    sig -> set_pka(RFC4880_PKA_RSA);
    sig -> set_hash(RFC4880_HASH_SHA256);
    
    Tag2Sub2::Ptr tag2sub2 = std::make_shared<Tag2Sub2>();
    tag2sub2 -> set_time(time);
    
    Tag2Sub11::Ptr tag2sub11 = std::make_shared<Tag2Sub11>();
    tag2sub11 -> set_psa(unhexlify("0908070302"));
    
    Tag2Sub16::Ptr tag2sub16 = std::make_shared<Tag2Sub16>();
    tag2sub16 -> set_keyid(keyid);
    
    Tag2Sub21::Ptr tag2sub21 = std::make_shared<Tag2Sub21>();
    tag2sub21 -> set_pha(unhexlify("08020a"));
    
    Tag2Sub22::Ptr tag2sub22 = std::make_shared<Tag2Sub22>();
    tag2sub22 -> set_pca(unhexlify("0201"));
    
    Tag2Sub27::Ptr tag2sub27 = std::make_shared<Tag2Sub27>();
    tag2sub27->set_flags( 0x01 | 0x02);
    
    Tag2Sub30::Ptr tag2sub30 = std::make_shared<Tag2Sub30>();
    tag2sub30 -> set_flags(0x01);
    
    //    sub 2 time :1419998489
    //    sub 11 : 0908070302 size:5
    //    sub 16 : Tag2Sub16-KeyID:7d2d53de4bcfb404
//    sub 21 : Tag2Sub21-Pha: 08020a
//    sub 22 : Tag2Sub22-Pca: 0201 size: 3
//    sub 27 : Tag2Sub27-Flags: 03  size: 1
//    sub 30
    //sig -> set_unhashed_subpackets({tag2sub16});
    sig->set_hashed_subpackets({tag2sub2 , tag2sub11, tag2sub16, tag2sub21, tag2sub22, tag2sub27, tag2sub30});
    
    std::string sig_hash = to_sign_13(sec, uid, sig);
    sig -> set_left16(sig_hash.substr(0, 2));
    //sig -> set_mpi(DSA_sign(sig_hash, dsa_pri, dsa_pub));


    
    if(get_is_debug())
        std::cout << "sig_hash:" << hexlify(sig_hash) << std::endl;
    
    // Secret Subkey Packet
    Tag7::Ptr ssb = std::make_shared<Tag7>();
    ssb -> set_version(RFC4880_V4);
    ssb -> set_time(time);
    ssb -> set_pka(RFC4880_PKA_RSA);
    ssb -> set_mpi(rsa_pub_mpi);
    ssb -> set_s2k_con(RFC4880_S2KU_ENCRYPTED_AND_HASHED);
    ssb -> set_sym(RFC4880_SA_AES_256);// AES256
    
    // Secret Subkey S2K
    S2K3::Ptr ssb_s2k3 = std::make_shared<S2K3>();
    ssb_s2k3 -> set_hash(RFC4880_HASH_SHA1);
    std::string salt_sub = "vegAbuFronCachmAhavdadqUetetnoadcaryosaClmQYczXKRVyosaClmQYczXKR";
    ssb_s2k3 -> set_salt(unhexlify(bintohex(salt_sub))); // new salt value
    ssb_s2k3 -> set_count(96);
    key = ssb_s2k3 -> run(passphrase, Symmetric_Algorithm_Key_Length.at(Symmetric_Algorithms.at(ssb -> get_sym())) >> 3);
    std::string IV_sub = "vegAbuFronCacvegAbuFronCachmAhavdadqUetetnoadcaryosaClmQYczXKRVyosaClmQYczXKRhmAhavdadqUetetnoadcaryosaClmQYczXKRVyosaClmQYczXKR";
    ssb -> set_s2k(ssb_s2k3);
    ssb -> set_IV(unhexlify(bintohex(IV_sub)));
    secret = write_MPI(rsa_priv_mpi[0]) + write_MPI(rsa_priv_mpi[1]) + write_MPI(rsa_priv_mpi[2]) + write_MPI(rsa_priv_mpi[3]);
    ssb -> set_secret(use_normal_CFB_encrypt(9, secret + use_hash(2, secret), key, ssb -> get_IV()));
    
    // Subkey Binding Signature
    Tag2::Ptr subsig = std::make_shared<Tag2>();
    subsig -> set_version(RFC4880_V4);
    subsig -> set_type(RFC4880_SIG_SUBKEY);
    subsig -> set_pka(RFC4880_PKA_RSA);
    subsig -> set_hash(RFC4880_HASH_SHA256);
    subsig -> set_hashed_subpackets({tag2sub2});
    subsig -> set_unhashed_subpackets({tag2sub16});
    sig_hash = to_sign_18(sec, ssb, subsig);
    subsig -> set_left16(sig_hash.substr(0, 2));
    //subsig -> set_mpi(DSA_sign(sig_hash, dsa_pri, dsa_pub));
    //RSA_sign(int type, const unsigned char *m, unsigned int m_length, unsigned char *sigret, unsigned int *siglen, RSA *rsa)
    
    PGPSecretKey private_key;
    private_key.set_ASCII_Armor(2);
    
    private_key.set_Armor_Header(std::vector <std::pair <std::string, std::string> > ({
        std::pair <std::string, std::string> ("Version", "ProtonMail v0.1.0"),
        std::pair <std::string, std::string> ("Comment", "https://protonmail.com")
    }));
    private_key.set_packets({sec, uid, sig, ssb, subsig});
    
    std::string private_key_s = private_key.write(2, 2);

    PGPPublicKey public_key = PGPPublicKey(private_key);
    
    std::cout<< private_key_s << std::endl;
    std::cout<< public_key.write() << std::endl;
    
    sec.reset();
    sec_s2k3.reset();
    uid.reset();
    sig.reset();
    tag2sub2.reset();
    tag2sub16.reset();
    ssb.reset();
    ssb_s2k3.reset();
    subsig.reset();
    
}


}
