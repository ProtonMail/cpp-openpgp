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
#include "Tag2Sub16.h"
#include "Tag7.h"
#include "Tag2.h"
#include "PGPKey.h"


/*
 * return 1 if OK, otherwise 0
 */
static unsigned
base_write(char *out, const void *src, unsigned len)
{
    return 1;//out->writer.writer(src, len, &out->errors, &out->writer);
}
unsigned
__ops_write(char *output, const void *src, unsigned len)
{
    return base_write(output, src, len);
}

unsigned
write_scalar(char *output, unsigned n, unsigned len)
{
    uint8_t   c;
    
    while (len-- > 0) {
        c = n >> (len * 8);
        if (!base_write(output, &c, 1)) {
            return 0;
        }
    }
    return 1;
}


unsigned
write_mpi(char *output, const BIGNUM *bn)
{
    unsigned	bits;
    uint8_t		buf[NETPGP_BUFSIZ];
    
    bits = (unsigned)BN_num_bits(bn);
    if (bits > 65535) {
        (void) fprintf(stderr, "__ops_write_mpi: too large %u\n", bits);
        return 0;
    }
    BN_bn2bin(bn, buf);
    return write_scalar(output, bits, 2) &&
    __ops_write(output, buf, (bits + 7) / 8);
}


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
//    //    BBS(static_cast <PGPMPI> (static_cast <uint32_t> (now()))); // seed just in case not seeded
//    //
//    //    if (((/*DSA_bits*/bits < 512)) || (/*ElGamal_bits*/ bits < 512)){
//    //        throw std::runtime_error("Error: Keysize must be at least 512 bits.");
//    //    }
//    //
//    //    if (DSA_bits & 1023){
//    //        throw std::runtime_error("Error: DSA keysize should be 1024, 2048, or 3072 bits.");
//    //    }
//    //
//  //  std::cout << bits << std::endl;
//  //  std::cout << passphrase << std::endl;
//  //  std::cout << userid << std::endl;
//    
//    uint16_t size = 2047;// (static_cast <uint8_t> (data[0]) << 8) + static_cast <uint8_t> (data[1]); // get bits
//    while (size & 7){
//        size++;                                                                     // pad to nearest octet
//    }
//    size >>= 3;
//    
//    
//    size <<=3;
//    while (size & 7) {
//        size --;
//    }
//    
//    
//    
//    RSA *myRSA;
//    unsigned char cleartext[2560] = "A";
//    unsigned char encrypted[2560] = { 0 };
//    unsigned char decrypted[2560] = { 0 };
//    int resultEncrypt = 0;
//    int resultDecrypt = 0;
//    
//    myRSA = RSA_generate_key ( 2048, 65537, NULL, NULL );
//    resultEncrypt = RSA_public_encrypt ( 1 /* strlen(cleartext) */, cleartext, encrypted, myRSA, RSA_PKCS1_OAEP_PADDING );
//    printf("%d from encrypt.\n", resultEncrypt);
//    resultDecrypt = RSA_private_decrypt( 128 /* resultEncrypt */, encrypted, decrypted, myRSA, RSA_PKCS1_OAEP_PADDING);
//    printf("%d from decrypt: '%s'\n", resultDecrypt, decrypted);
//    RSA_free ( myRSA );
//
//    
   

    
    //RSA            *rsa;
    BN_CTX *ctx= BN_CTX_new();
    BIGNUM* e = BN_new();
    RSA *rsaKeypair = RSA_new();
    int iRet = BN_set_word(e, 65537);
    if(!iRet)
    {
      //  std::cout<<"BN_set_word error "<< std::endl;
        return ;
    }
    
    iRet =	RSA_generate_key_ex(rsaKeypair, 2048, e, NULL);
    if(!iRet)
    {
      //  std::cout<<"RSA_generate_key_ex error "<< std::endl;
        return ;
    }
    
//    std::string hex ="010001";
//    std::string hex_1 = "75c2b19fd6edf9f0ccc6e413eacc525a35f8a6d7fa5b441bb9c0c0ff90f0daf085bc219a90376c73376e149db7408ee26471e2839172a79336315fb50ccfc426cf4e67130aea4d08e0ce2b8ae7127f62f65cfbfc9b6439fe79fbfa076f1fa98ef0f3ac0eeefae80d1f30d84ddfa7876b9ef7d1d6a126521160ffb03ae9d4910df0cd33c4e0c661f3bf1e0af91a79e94c4cc3cd9d0bbd38d83157268ef061b4f4cd2e242c55a90e8f5c132d61207276b614b1c01e1d0aeb7b27c408d3e86d681745a7d3c1fb64fe7f5a188ccb562bf8ce8dfa1b0ba4ec9cc2dc01763c037162eb3a10008f724c2c8e96cc54ba48a52be30c6765620f413ed364d05778a99b76cf";
//    iRet = BN_hex2bn(&e, hex.c_str());
//    
//    iRet = BN_hex2bn(&e, hex_1.c_str());
//    
//    
//    unsigned n = (unsigned)BN_num_bits(e);
//    
//    
//    uint8_t   c;
//    int len = 2;
//    
//    while (len-- > 0) {
//        c = n >> (len * 8);
//    }
//
//    
//    int ln;
//    ln = BN_bn2mpi(e, NULL);
//
//    
//    char bn[ln];
//    iRet = BN_bn2mpi(e, (unsigned char*)bn);
//    
//    std::string v(bn, ln);
//    
//   // std::cout<< v << std::endl;
//    
//    
//    ln = v.size();
//    BIGNUM* eRet = BN_new();
//    e = BN_mpi2bn((const unsigned char *)v.c_str(), ln, eRet);
//    
//    hex = BN_bn2hex(e);
//    
//    std::transform(hex.begin(), hex.end(), hex.begin(), ::tolower);
//    
//    if(hex == hex_1)
//    {
//    //    std::cout << "ok"   << std::endl;
//    }
    

    
    rsa_key rsa;
    //Key creation time
    time_t time = now();
    
    // Secret Key Packet
    Tag5::Ptr sec = std::make_shared<Tag5>();
    sec -> set_version(RFC4880_V4);
    sec -> set_time(time);
    sec -> set_pka(RFC4880_PKA_RSA);//RSA
    
    
    rsa.d = BN_dup(rsaKeypair->d);
    rsa.p = BN_dup(rsaKeypair->p);
    rsa.q = BN_dup(rsaKeypair->q);
    rsa.u = BN_mod_inverse(NULL, rsaKeypair->p, rsaKeypair->q, ctx);
    
    int ln;
    std::vector <std::string> rsa_key_mpi;
    
    size_t length = 8192;
    uint8_t out[length];
    
    ln = BN_bn2mpi(rsa.d, out);
    rsa_key_mpi.push_back(std::string((char*)out, ln));

    ln = BN_bn2mpi(rsa.p, out);
    rsa_key_mpi.push_back(std::string((char*)out, ln));
    

    ln = BN_bn2mpi(rsa.q, out);
    rsa_key_mpi.push_back(std::string((char*)out, ln));

    ln = BN_bn2mpi(rsa.u, out);
    rsa_key_mpi.push_back(std::string((char*)out, ln));
    
    
    sec -> set_mpi(rsa_key_mpi);
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
   // std::string secret = write_MPI(dsa_pri[0]);
   // sec -> set_secret(use_normal_CFB_encrypt(9, secret + use_hash(2, secret), key, sec -> get_IV()));
    
    std::string keyid = sec -> get_keyid();
    Tag13::Ptr uid = std::make_shared<Tag13>();
    uid -> set_name(userid);
    uid -> set_comment("this is protonmail test");
    uid -> set_email("zhj4478@gmail.com");
    
    
    Tag2::Ptr sig = std::make_shared<Tag2>();
    sig -> set_version(RFC4880_V4);
    sig -> set_type(RFC4880_CERT_GENERIC);
    sig -> set_pka(RFC4880_PKA_RSA);
    sig -> set_hash(RFC4880_HASH_SHA256);
    Tag2Sub2::Ptr tag2sub2 = std::make_shared<Tag2Sub2>(); tag2sub2 -> set_time(time);
    sig -> set_hashed_subpackets({tag2sub2});
    Tag2Sub16::Ptr tag2sub16 = std::make_shared<Tag2Sub16>(); tag2sub16 -> set_keyid(keyid);
    sig -> set_unhashed_subpackets({tag2sub16});
 //   std::string sig_hash = to_sign_13(sec, uid, sig);
  //  sig -> set_left16(sig_hash.substr(0, 2));
 //   sig -> set_mpi(DSA_sign(sig_hash, dsa_pri, dsa_pub));
    
    // Secret Subkey Packet
    Tag7::Ptr ssb = std::make_shared<Tag7>();
    ssb -> set_version(RFC4880_V4);
    ssb -> set_time(time);
    ssb -> set_pka(RFC4880_PKA_RSA);// ElGamal
    
    ssb -> set_mpi(rsa_key_mpi);
    ssb -> set_s2k_con(RFC4880_S2KU_ENCRYPTED_AND_HASHED);
    ssb -> set_sym(RFC4880_SA_AES_256);// AES256
    
//    std::vector <std::string> rsa_key_mpi;
//    rsa_key_mpi.push_back(BN_bn2hex(rsa.d));
//    rsa_key_mpi.push_back(BN_bn2hex(rsa.p));
//    rsa_key_mpi.push_back(BN_bn2hex(rsa.q));
//    rsa_key_mpi.push_back(BN_bn2hex(rsa.u));
//    sec -> set_mpi(rsa_key_mpi);

    
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
    //secret = write_MPI(elgamal_pri);
   // ssb -> set_secret(use_normal_CFB_encrypt(9, secret + use_hash(2, secret), key, ssb -> get_IV()));
    
    // Subkey Binding Signature
    Tag2::Ptr subsig = std::make_shared<Tag2>();
    subsig -> set_version(RFC4880_V4);
    subsig -> set_type(RFC4880_SIG_SUBKEY);
    subsig -> set_pka(RFC4880_PKA_RSA);
    subsig -> set_hash(RFC4880_HASH_SHA256);
    subsig -> set_hashed_subpackets({tag2sub2});
    subsig -> set_unhashed_subpackets({tag2sub16});
   // sig_hash = to_sign_18(sec, ssb, subsig);
   // subsig -> set_left16(sig_hash.substr(0, 2));
   // subsig -> set_mpi(DSA_sign(sig_hash, dsa_pri, dsa_pub));
    //RSA_sign(int type, const unsigned char *m, unsigned int m_length, unsigned char *sigret, unsigned int *siglen, RSA *rsa)
    
    PGPSecretKey private_key;
    private_key.set_ASCII_Armor(2);
    
    private_key.set_Armor_Header(std::vector <std::pair <std::string, std::string> > ({
        std::pair <std::string, std::string> ("Version", "v0.1.0"),
        std::pair <std::string, std::string> ("Comment", "https://protonmail.com")
    }));
    private_key.set_packets({sec, uid, sig, ssb, subsig});
    
    std::string private_key_s = private_key.write(2, 2);

    PGPPublicKey public_key = PGPPublicKey(private_key);
    
    //std::cout<< private_key_s << std::endl;
    
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
