//
//  openpgp.cpp
//  UNNetPGP
//
//  Created by Yanfeng Zhang on 1/21/15.
//
//  The MIT License
// 
//  Copyright (c) 2019 Proton Technologies AG
// 
//  Permission is hereby granted, free of charge, to any person obtaining a copy
//  of this software and associated documentation files (the "Software"), to deal
//  in the Software without restriction, including without limitation the rights
//  to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
//  copies of the Software, and to permit persons to whom the Software is
//  furnished to do so, subject to the following conditions:
// 
//  The above copyright notice and this permission notice shall be included in
//  all copies or substantial portions of the Software.
// 
//  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
//  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
//  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
//  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
//  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
//  OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
//  THE SOFTWARE.



#include <openpgp/openpgp.h>

#include <iostream>
#include <algorithm>
#include <string>


#include <config/config.h>
#include <config/RFC4880.h>


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


#include <package/Tag5.h>
#include <base/rsa_key.h>
#include <utilities/BBS.h>
#include <package/Tag13.h>
#include <package/subpackage/Tag2Sub2.h>
#include <package/subpackage/Tag2Sub11.h>
#include <package/subpackage/Tag2Sub16.h>
#include <package/subpackage/Tag2Sub21.h>
#include <package/subpackage/Tag2Sub22.h>
#include <package/subpackage/Tag2Sub27.h>
#include <package/subpackage/Tag2Sub30.h>
#include <package/Tag7.h>
#include <package/Tag2.h>
#include <openpgp/PGPKey.h>
#include <openpgp/cfb.h>
#include <openpgp/sigcalc.h>
#include <encryption/RSA.h>
#include <openpgp/sign.h>

#include <version.hpp>

namespace ProtonMail {
    namespace pgp {
        
        openpgp::openpgp()
        {
            
        }
        openpgp::~openpgp()
        {
            
        }
        
        void openpgp::encrypt_message()
        {
            //   std::string n =  "6c9413c636b1c031b613ef5027c45e1ad16fdf72bcc23f6ef27759ed7be894286ca1caec77c46411207af007dcf26013c53915d7c1a4080376031fbdd89c4d053df8e1f9f05610d59728190e571d5179f3d3cad188c804c5b4bbe63750fae5692f9c87c175c39cec55a3e8de30e7239a8e92f7bbfe3a3deef7ca989c85ed745eec0ee35f7cabff186a61a94c5810563e07ed06edb88c6857eba62007fdea9f4f08c0318a917ea626a80fc2d85835022bfc2bd6d49722434a2fe642cae098c880273a58bbc6022528d096bc2f1cb2e24461c66599fe36fe21f2ad67aeb32ba62de04f8510018a413678f4a8f9723b2f39c3fc222b2e1124e91253df5f89474365";
            //    std::string e = "010001";
        }
        
        bool openpgp::generate_new_key(int bits, std::string passphrase, std::string user_name, std::string email, std::string comments, std::string& pub, std::string& priv, int32_t time_custom)
        {
            BN_CTX *ctx= BN_CTX_new();
            BIGNUM* e = BN_new();
            RSA *rsa_key = RSA_new();
            RSA *rsa_sub_key = RSA_new();
            int iRet = BN_set_word(e, 65537);
            if(!iRet)
            {
                std::cout<<"BN_set_word error "<< std::endl;
                return false;
            }
            
            iRet =RSA_generate_key_ex(rsa_key, bits, e, NULL);
            if(!iRet)
            {
                std::cout<<"RSA_generate_key_ex key error "<< std::endl;
                return false;
            }
            
            iRet = RSA_generate_key_ex(rsa_sub_key, bits, e, NULL);
            if(!iRet)
            {
                std::cout<<"RSA_generate_key_ex sub_key error "<< std::endl;
                return false;
            }
            
            size_t length = 8192;
            uint8_t out[length];
            
            int ln = 0;
            std::vector <std::string> rsa_pub_mpi;
            std::vector <std::string> rsa_priv_mpi;
            std::vector <std::string> rsa_sub_pub_mpi;
            std::vector <std::string> rsa_sub_priv_mpi;
            
            //private key part
            ln = BN_bn2mpi(rsa_key->d, out);
            rsa_priv_mpi.push_back(std::string((char*)out, ln));
            ln = BN_bn2mpi(rsa_key->p, out);
            rsa_priv_mpi.push_back(std::string((char*)out, ln));
            ln = BN_bn2mpi(rsa_key->q, out);
            rsa_priv_mpi.push_back(std::string((char*)out, ln));
            
            BIGNUM * rsa_inverse = BN_mod_inverse(NULL, rsa_key->p, rsa_key->q, ctx);
            ln = BN_bn2mpi(rsa_inverse, out);
            BN_free(rsa_inverse);
            
            rsa_priv_mpi.push_back(std::string((char*)out, ln));
            //pub key part
            ln = BN_bn2mpi(rsa_key->n, out);
            rsa_pub_mpi.push_back(std::string((char*)out, ln));
            ln = BN_bn2mpi(rsa_key->e, out);
            rsa_pub_mpi.push_back(std::string((char*)out, ln));
            
            
            //sub private key part
            ln = BN_bn2mpi(rsa_sub_key->d, out);
            rsa_sub_priv_mpi.push_back(std::string((char*)out, ln));
            ln = BN_bn2mpi(rsa_sub_key->p, out);
            rsa_sub_priv_mpi.push_back(std::string((char*)out, ln));
            ln = BN_bn2mpi(rsa_sub_key->q, out);
            rsa_sub_priv_mpi.push_back(std::string((char*)out, ln));
            
            BIGNUM * rsa_sub_inverse = BN_mod_inverse(NULL, rsa_sub_key->p, rsa_sub_key->q, ctx);
            ln = BN_bn2mpi(rsa_sub_inverse, out);
            BN_free(rsa_sub_inverse);
            
            rsa_sub_priv_mpi.push_back(std::string((char*)out, ln));
            //sub public key part
            ln = BN_bn2mpi(rsa_sub_key->n, out);
            rsa_sub_pub_mpi.push_back(std::string((char*)out, ln));
            ln = BN_bn2mpi(rsa_sub_key->e, out);
            rsa_sub_pub_mpi.push_back(std::string((char*)out, ln));

            
            //Key creation time
            time_t time = time_custom > 0 ? time_custom : now();
            
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
            sec_s2k3 -> set_hash(RFC4880_HASH_SHA256);
            sec_s2k3 -> set_salt(unhexlify(bintohex(BBS().rand_b(64))));
            sec_s2k3 -> set_count(96);
            
            // calculate the key from the passphrase
            std::string key = sec_s2k3 -> run(passphrase, Symmetric_Algorithm_Key_Length.at(Symmetric_Algorithms.at(sec -> get_sym())) >> 3);
            // encrypt private key value
            sec -> set_s2k(sec_s2k3);
            sec -> set_IV(unhexlify(bintohex(BBS().rand_b(Symmetric_Algorithm_Block_Length.at(Symmetric_Algorithms.at(sec -> get_sym()))))));
            std::string secret = write_MPI(rsa_priv_mpi[0]) + write_MPI(rsa_priv_mpi[1]) + write_MPI(rsa_priv_mpi[2]) + write_MPI(rsa_priv_mpi[3]);
            sec -> set_secret(use_normal_CFB_encrypt(9, secret + use_hash(2, secret), key, sec -> get_IV()));
            
            std::string keyid = sec -> get_keyid();
            
            if(get_is_debug())
                std::cout << "KeyID:" << hexlify(keyid) << std::endl;
            
            Tag13::Ptr uid = std::make_shared<Tag13>();
            uid -> set_name(user_name);
            uid -> set_comment(comments);
            uid -> set_email(email);
        
            
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
            
            sig->set_unhashed_subpackets({tag2sub16});
            sig->set_hashed_subpackets({tag2sub2, tag2sub11, tag2sub21, tag2sub22, tag2sub27, tag2sub30});
            
            std::string sig_hash = to_sign_10(sec, uid, sig);
            if(get_is_debug())
                std::cout << hexlify(sig_hash) << std::endl;
            sig -> set_left16(sig_hash.substr(0, 2));
            
            std::string str_sign = RSA_sign(sig_hash, rsa_priv_mpi, rsa_pub_mpi);
            if(get_is_debug())
                std::cout << hexlify(str_sign) << std::endl;
            sig -> set_mpi({str_sign});
            
            if(get_is_debug())
                std::cout << "sig_hash:" << hexlify(sig_hash) << std::endl;
            
            // Secret Subkey Packet
            Tag7::Ptr ssb = std::make_shared<Tag7>();
            ssb -> set_version(RFC4880_V4);
            ssb -> set_time(time);
            ssb -> set_pka(RFC4880_PKA_RSA);
            ssb -> set_mpi(rsa_sub_pub_mpi);
            ssb -> set_s2k_con(RFC4880_S2KU_ENCRYPTED_AND_HASHED);
            ssb -> set_sym(RFC4880_SA_AES_256);// AES256
            
            // Secret Subkey S2K
            S2K3::Ptr ssb_s2k3 = std::make_shared<S2K3>();
            ssb_s2k3 -> set_hash(RFC4880_HASH_SHA256);
            ssb_s2k3 -> set_salt(unhexlify(bintohex(BBS().rand_b(64)))); // new salt value
            ssb_s2k3 -> set_count(96);
            std::string subkey = ssb_s2k3 -> run(passphrase, Symmetric_Algorithm_Key_Length.at(Symmetric_Algorithms.at(ssb -> get_sym())) >> 3);
            ssb -> set_s2k(ssb_s2k3);
            ssb -> set_IV(unhexlify(bintohex(BBS().rand_b(Symmetric_Algorithm_Block_Length.at(Symmetric_Algorithms.at(ssb -> get_sym()))))));
            std::string sub_secret = write_MPI(rsa_sub_priv_mpi[0]) + write_MPI(rsa_sub_priv_mpi[1]) + write_MPI(rsa_sub_priv_mpi[2]) + write_MPI(rsa_sub_priv_mpi[3]);
            ssb -> set_secret(use_normal_CFB_encrypt(9, sub_secret + use_hash(2, sub_secret), subkey, ssb -> get_IV()));
  
            // Subkey Binding Signature
            Tag2::Ptr subsig = std::make_shared<Tag2>();
            subsig -> set_version(RFC4880_V4);
            subsig -> set_type(RFC4880_SIG_SUBKEY);
            subsig -> set_pka(RFC4880_PKA_RSA);
            subsig -> set_hash(RFC4880_HASH_SHA256);
            
            Tag2Sub27::Ptr sb_tag2sub27 = std::make_shared<Tag2Sub27>();
            sb_tag2sub27->set_flags( 12);
            
            subsig -> set_hashed_subpackets({tag2sub2, sb_tag2sub27});
            subsig -> set_unhashed_subpackets({tag2sub16});
            sig_hash = to_sign_18(sec, ssb, subsig);
            subsig -> set_left16(sig_hash.substr(0, 2));
            subsig -> set_mpi({RSA_sign(sig_hash, rsa_priv_mpi, rsa_pub_mpi)});
            
            PGPSecretKey private_key;
            private_key.set_ASCII_Armor(2);
            const std::string str_version = std::string("ProtonMail v") + std::string(PM_OPENPGP_VERSION);
            private_key.set_Armor_Header(std::vector <std::pair <std::string, std::string> > ({
                std::pair <std::string, std::string> ("Version", str_version),
                std::pair <std::string, std::string> ("Comment", "https://protonmail.com")
            }));
            private_key.set_packets({sec, uid, sig, ssb, subsig});
            
            priv = private_key.write(2, 2);
            PGPPublicKey public_key = PGPPublicKey(private_key);
            
            pub = public_key.write();
            if(get_is_debug())
                std::cout<< priv << std::endl;
            
            if(get_is_debug())
                std::cout<< pub << std::endl;
            
            sec.reset();
            sec_s2k3.reset();
            uid.reset();
            sig.reset();
            tag2sub2.reset();
            tag2sub16.reset();
            ssb.reset();
            ssb_s2k3.reset();
            subsig.reset();
            
            BN_CTX_free(ctx);
            BN_free(e);
            //rsa_key->n = rsa_key->e = rsa_key->d = rsa_key->p = rsa_key->q = NULL;
            RSA_free(rsa_key);
            //rsa_sub_key->n = rsa_sub_key->e = rsa_sub_key->d = rsa_sub_key->p = rsa_sub_key->q = NULL;
            RSA_free(rsa_sub_key);
            
            {
                std::string datakey =
                "-----BEGIN PGP PUBLIC KEY BLOCK-----\r\n"
                "Version: Pmcrypto Golang 0.0.1 (ddacebe0)\r\n"
                "Comment: https://protonmail.com\r\n"
                "\r\n"
                "xsFNBFomLW8BEADU8JWF/GpsMT3YsAXaJQ0VIMqRi9p3TXIdyzW2y7Pk4c/UMr/T\r\n"
                "A6Rtqrj71vrAKK/43whNb6ibUkSslJGUNUjYOV1lBwB0+X86Eq8PvhdAF4uqGFRR\r\n"
                "UOfworW8ZiEgCOjBcr+xo1CiCd5MfxGoDN4YRRkdijPuRB8FfdreSPUBYeBhNQPN\r\n"
                "Md6n7/odzGa3PgbrGT2y0+jiCx/+uHB0BwNoXE66RdfH0eYZQMK7jhb536g7hfOu\r\n"
                "Iaakw1uLuMWEcjgIQKvN5WA/pIU1vLhHjOlStZC9LKrkCQ0mQFuxTfYuEL/r7f6x\r\n"
                "/Ojt2TWgW0x0AfV9/29i1JUtWyazrkPJcrM55yUF8/8u03IYLSdfncCFCt/kiQZs\r\n"
                "pyBHZsHEfT/j8rB8Qw6SsGjxFWCJHL9zU4WbP8Jjg8etw4tlRCfoIladUWHJomSM\r\n"
                "35gSHi+StLyvkTLhvWlYaKRnbVzVmpxgmnyfriKpigwNjjnQfLX97l18RJxoxU8R\r\n"
                "QfXqPRuTvh3Vqa2EaqZuxBUp+lJT3bU8eGAr+g69osHd0KKPJia2HJimoaNwQNOX\r\n"
                "IPEVDuO+l5vEPmtoKq5z9fo9Px+6BSRJvdxZsBpszEBTaXxlfHM/lqQyD4tABICY\r\n"
                "5wGJMQh1/CClF+DccoSFfAtQGVfeeGue0pvDr2xC63D74Tm5oBmIvA/56QARAQAB\r\n"
                "zStKb2huIEJyZWVzZSAocGhvbmUpIDxqZWJyZWVzZTJAaG90bWFpbC5jb20+wsF1\r\n"
                "BBMBCAAfBQJaJi1vAhsDBAsJCAcGFQgCCQoLAxYBAgIeAQIXgAAKCRABUoLbaNH+\r\n"
                "UgABD/9wUDYkulOCtX4jpRRCaAtm6T+moclhOUvxPV5vj7jP5GYkNRHrlSD3NUpj\r\n"
                "yTROfZbtetryAcnoCoh2aeIwTA3Tnirt/xj7h8ho2GQYLzfPWWBwobF+5UYvZcwG\r\n"
                "CZXbVIw1UiVVPdBy8jWM1MNnSHNfWY8sqZvRIH2SiRFk745Lif9w+ENmiODqfYiX\r\n"
                "sUqQZDjDVDFORJqlXacPB3kJ7WyUnzyA02D0zSGS36VK6jKtRbfotcxshjeWB/EQ\r\n"
                "YEasDtoif/5xtaaiofUWcoazOTbN/QKonQuECW1OQTMazo8RCeQ7gOaT3z51HHMO\r\n"
                "SB/booXM/xXSscSXcNYo5UfPfYt2hJQESFbgtJTnxCKaJxKgUXMi+qukjuNhJIrQ\r\n"
                "DFF39CEPYQmMtLqe84gIvCVj2lL1imRtW9Jm3/GHH7g+JrB1MRyO1Z9oAl7EX27J\r\n"
                "pq1yH1l05JT5ZrXyq7/iVGUGjGjT1IWhv5ICRuEvZd0KLi7E3IgwiA1zp1fQxBP3\r\n"
                "/ZzidApKDVquBqelb1CnDzJHqbcbi5W32S1DSp0c4KUlMUPPT+bmvYLSLWUB35xu\r\n"
                "kh3iNY5Q2I8rD17ZP26XzoYjfcfbRkEQgKRBIITTkYZNvN6yL6rS/ZkMCYhjxTcS\r\n"
                "enbPM8ym2scBZFF4lmxVsLH2QiPu1qCBTHbW52p/D/a/uWJEYc7BTQRaJi1wARAA\r\n"
                "wrsTYTkhBzk0BdE2N8Qy8EdKBPKNzfepPLFLfxVkyKINOBP7i7lJCtcz/6VhIdL1\r\n"
                "NHNRuvvX0lGdmGaY21yial0MIRdTYl9EG4DbHXxb3XW5EHIb/Nt9Ywj2MvwCKZjq\r\n"
                "lRMFNL22J4EreFrcitKnRNRxtATGKyEmsQtZgB9brm/uy96Z+M3yyhvCGq/WRiEc\r\n"
                "8+qSRGPAR+E6teBhMZ0/gX6a3MvnViA5qbPd5O4eVtfceYW1m25Ll3VYbapzu0Bg\r\n"
                "sWi02yDzRWpx7sIIK2ysFuVXzfNiBSVsntjEgkGcSVFWUEvX1Mk8jB78T9rmW499\r\n"
                "CWnUPI3tUbBtVbvFUDpZxTH6oYCuKlQpwx/BGAXWd+yXpb7Zbm7N2ozwXianPWYQ\r\n"
                "OpYWfRIU3lRHnNJwVt9l/Y+D3YA2YZWjOKMBbyvKJuEPAqohaxVGIJP3ynBoArLT\r\n"
                "mx8lxWcn9qWw8WgFoxHPaR8XzS85lELXQky2u6mLfN5psYkzcHTaAp/8B/Ny+RGn\r\n"
                "WjkrBs090ychK0fjQnep+uJv842rlrIUT1eU81nsmmoyagmTgIznRkgvH0vrKRaf\r\n"
                "2no1qXtavS6+3eNai+wbGsCyztcT4E2FzWA2xgJSI3zeT55IE3xhYXyrfJUL+c+x\r\n"
                "Xkxjf3I7OJZkvIZMwBz6QqZDFQ0qUcSHCeIqp879tEkAEQEAAcLBagQYAQgAFAUC\r\n"
                "WiYtcAIbDAUJBaOagAQLCQgHAAoJEAFSgtto0f5SAAEP/RsBvjAo9m7DEWahQTq2\r\n"
                "QBpJ6DBsWjjgg8OcbSqtCrzR/J29NAJ2yO3Q34dpUVwswFKSB3JnkU/5Vehe2/zF\r\n"
                "I1T/JECy8JopWBqJk8n8mqZZtmbA4nalvSenZg8MTkmEfT7XlqE3iGkbWZebZZdP\r\n"
                "vLrOiScyCiDBmzNTEiRBxTrfxFGudJxLyIHAF4EdKPVu/m93449MHXThQxF8yxPN\r\n"
                "yIoBKOsh7IXsw1WbKrz2poUVdZWOle+ICk7N9PQ1Jd83HGncWP3HDAWI9LM/q/hi\r\n"
                "LHgC5uMafUxP0CkLVMHzFBaq17lqivXWZ6u+4dCURgYOe+OfqlkhOWyUTcB8On81\r\n"
                "5XEpsnodY+ddWgQJjrsVbu0pPJNDpT8me/mpJT2SbPdLRjfvsKY0DvDNvLcfIWYZ\r\n"
                "vzPTpsE68yMPIAqUYVcfnBIQCJZT8zYlSmTWzMIBLRicfrK1+eWP5dBTBz8ajeUs\r\n"
                "neWeh/0V2gcCnJA69krnp759+3kjg3KKxKG12Ny7gE9OsHDg/TXaoBomInv/OSBp\r\n"
                "3/kr6oVqYj4ogQ7AnuG3kakgEnrPblimKixebm8Col0QQkZqZWNPekN453VVSwJD\r\n"
                "sJUbA8UIyzH0Gblrm53z8hpUIU8OicTdPcVdtDV9LoP4HJS8xTvUEu4YuYY1jOV6\r\n"
                "DBY2sED/ZLd7CLReEeMNdiGf\r\n"
                "=lgls\r\n"
                "-----END PGP PUBLIC KEY BLOCK-----\r\n";
                Tag13::Ptr id;
                Tag2::Ptr sig;
                Tag6::Ptr sec;
                
                PGPPublicKey pbkey = PGPPublicKey(datakey);
                for(auto packet : pbkey.get_packets()) {
                    if (packet->get_tag() == 2) {
                        std::string raw = packet -> raw();
                        sig = std::make_shared<Tag2>(raw);
                        break;
                    }
                }
                
                for(auto packet : pbkey.get_packets()) {
                    if (packet->get_tag() == 6) {
                        
                        std::string raw = packet -> raw();
                        sec = std::make_shared<Tag6>(raw);
                        break;
                    }
                }
                
                for(auto packet : pbkey.get_packets()) {
                    if (packet->get_tag() == 13) {
                        std::string raw = packet -> raw();
                        id = std::make_shared<Tag13>(raw);
                        break;
                    }
                }
                
                std::string sig_hash = to_sign_10(sec, id, sig);
                std::cout << hexlify(sig_hash) << std::endl;
                std::cout << hexlify(sig->get_mpi()[0]) << std::endl;
                
                auto test = sig_hash.substr(0, 2);
                std::cout << hexlify(test) << std::endl;
                
                
               std::cout << hexlify( sig->get_left16()) << std::endl;
                
                auto signing = sec->get_mpi();
                
                ProtonMail::crypto::rsa key(signing[0], signing[1]);
                auto hash = sig -> get_hash();
                
                std::string encoded = EMSA_PKCS1_v1_5(hash, sig_hash, bitsize(signing[0]) >> 3);
                auto verify = key.verify(rawtompi(encoded), sig->get_mpi()[0]);
                
                
                
//                auto ISOK = RSA_verify(sig_hash, sig->get_mpi(), sec->get_mpi());
                std::cout << verify << std::endl;
                
            }
            return true;
            
        }
        
        
        
        //    void openpgp::generate_new_key(int bits, std::string passphrase, std::string userid)
        //    {
        //        BN_CTX *ctx= BN_CTX_new();
        //        BIGNUM* e = BN_new();
        //        RSA *rsa_key = RSA_new();
        //        RSA *rsa_sub_key = RSA_new();
        //        int iRet = BN_set_word(e, 65537);
        //        if(!iRet)
        //        {
        //            std::cout<<"BN_set_word error "<< std::endl;
        //            return ;
        //        }
        //
        //        iRet =RSA_generate_key_ex(rsa_key, 2048, e, NULL);
        //        if(!iRet)
        //        {
        //            std::cout<<"RSA_generate_key_ex key error "<< std::endl;
        //            return ;
        //        }
        //
        //        iRet = RSA_generate_key_ex(rsa_sub_key, 2048, e, NULL);
        //        if(!iRet)
        //        {
        //            std::cout<<"RSA_generate_key_ex sub_key error "<< std::endl;
        //            return ;
        //        }
        //
        //
        //        int ln;
        //        std::vector <std::string> rsa_pub_mpi;
        //        std::vector <std::string> rsa_priv_mpi;
        //
        //        size_t length = 8192;
        //        uint8_t out[length];
        //
        //        //public key part
        //        //    ln = BN_bn2mpi(rsa_key->n, out);
        //        //    rsa_pub_mpi.push_back(std::string((char*)out, ln));
        //        //    ln = BN_bn2mpi(rsa_key->e, out);
        //        //    rsa_pub_mpi.push_back(std::string((char*)out, ln));
        //
        //
        //        std::string pub_n = "000001006c9413c636b1c031b613ef5027c45e1ad16fdf72bcc23f6ef27759ed7be894286ca1caec77c46411207af007dcf26013c53915d7c1a4080376031fbdd89c4d053df8e1f9f05610d59728190e571d5179f3d3cad188c804c5b4bbe63750fae5692f9c87c175c39cec55a3e8de30e7239a8e92f7bbfe3a3deef7ca989c85ed745eec0ee35f7cabff186a61a94c5810563e07ed06edb88c6857eba62007fdea9f4f08c0318a917ea626a80fc2d85835022bfc2bd6d49722434a2fe642cae098c880273a58bbc6022528d096bc2f1cb2e24461c66599fe36fe21f2ad67aeb32ba62de04f8510018a413678f4a8f9723b2f39c3fc222b2e1124e91253df5f89474365";
        //        std::string pub_e = "00000003010001";
        //        rsa_pub_mpi.push_back(unhexlify(pub_n));
        //        rsa_pub_mpi.push_back(unhexlify(pub_e));
        //
        //        //D:
        //        std::string priv_d = "0000010011c751519465188e4b3d0a637a8f79c53463f8178676dc0223ab8d4b088df5ac84d51d3009105c3e3dae439d55fd4de40ed8210e7a038cd85c3b78b8123ecd91bd2b027d756ff243b70376ced54ed4a77e58408e7cb21badefc1109a202564e90b45bb28df4a8f6857418680d34b15965a20107674d33e8ee17e07ed2134d767f80dc756450bfa1f26957cb566fc7477f018b227b042c7e468811a74e7d8d71ea71fc372d00a6de6c0f17fed581d6a414d3f034dff4a665df75376f04ca7165d83648da646875306e186a0f6d8635dbc9b362cb298c09608208f31992331f02eb1e93fba9075cf81dab8f8409e1aa54c1e584fd824b8568292a2b6ea84603125";
        //        rsa_priv_mpi.push_back(unhexlify(priv_d));
        //        //P:
        //        std::string priv_p = "0000008100c786785df5ef37fdf0f9ff5f2e6aa1b78d2b457889ed713c7b0e0e2be361a2f059ede569509df48d0c175cd20f0983fbc239a21b91dc75ad459c62a4d87f06afa779abab414e3db0da75eeb7588821cd775d3d14a1872d3da0e64a4e609778467cfe795bf852487bedfe0d970289feadc1c15411933ca4d8f65d513e5d6d0ea3";
        //        rsa_priv_mpi.push_back(unhexlify(priv_p));
        //        //Q:
        //        std::string priv_q = "00000081008b4fa19051e3e5d3b95914a94c9faebe256ea8a97d18acef1b0ec13fef2bb58d9a20d788038fcc8d96e821ba6c1ff62ae4fcaa679bfc742aea0410f6bc15f6aa4fa838f5fc72370c36ca37918bdc8c693f51e6968d34ad04e48e8c52bac1b62dc2e2b226dff66453e887fc9ba89b47b781c7319debd57f289506ab3464722e57";
        //        rsa_priv_mpi.push_back(unhexlify(priv_q));
        //        //U:
        //        std::string priv_u = "00000080296ebe38400198771d0125a9c5768df98cab22743e57cfe0726c35cc2280f5598b2cbdeca3fa1100073710ba6f15e9d206174a59b19c631287c85b9b4bb88d806b88ed2e50ad3f885040fab3bb2adb952d135e629215ea17a68913575c4e88477b0babb8c5e7c0fcc2468f39e8f0152a380e0543c05884a545dcc079e1a911ef";
        //        rsa_priv_mpi.push_back(unhexlify(priv_u));
        //
        //
        //        //private key part
        //        //    ln = BN_bn2mpi(rsa_key->d, out);
        //        //    rsa_priv_mpi.push_back(std::string((char*)out, ln));
        //        //    ln = BN_bn2mpi(rsa_key->p, out);
        //        //    rsa_priv_mpi.push_back(std::string((char*)out, ln));
        //        //    ln = BN_bn2mpi(rsa_key->q, out);
        //        //    rsa_priv_mpi.push_back(std::string((char*)out, ln));
        //        //    ln = BN_bn2mpi(BN_mod_inverse(NULL, rsa_key->p, rsa_key->q, ctx), out);
        //        //    rsa_priv_mpi.push_back(std::string((char*)out, ln));
        //
        //
        //        //Key creation time
        //        time_t time = now();
        //        time = 1419998489;
        //
        //
        //
        //        // Secret Key Packet
        //        Tag5::Ptr sec = std::make_shared<Tag5>();
        //        sec -> set_version(RFC4880_V4);
        //        sec -> set_time(time);
        //        sec -> set_pka(RFC4880_PKA_RSA);//RSA
        //        sec -> set_mpi(rsa_pub_mpi);
        //        sec -> set_s2k_con(RFC4880_S2KU_ENCRYPTED_AND_HASHED);
        //        sec -> set_sym(RFC4880_SA_AES_256);// AES256
        //
        //
        //        // Secret Key Packet S2K
        //        S2K3::Ptr sec_s2k3 = std::make_shared<S2K3>();
        //        sec_s2k3 -> set_hash(RFC4880_HASH_SHA1);
        //        std::string salt_s = "vegAbuFronCachmAhavdadqUetetnoadcaryosaClmQYczXKRVyosaClmQYczXKR";
        //        sec_s2k3 -> set_salt(unhexlify(bintohex(salt_s)));
        //        sec_s2k3 -> set_count(96);
        //
        //        // calculate the key from the passphrase
        //        std::string key = sec_s2k3 -> run(passphrase, Symmetric_Algorithm_Key_Length.at(Symmetric_Algorithms.at(sec -> get_sym())) >> 3);
        //        // encrypt private key value
        //        sec -> set_s2k(sec_s2k3);
        //        // uint16_t p_bits = Symmetric_Algorithm_Block_Length.at(Symmetric_Algorithms.at(sec -> get_sym()));
        //        std::string IV_S = "vegAbuFronCachmAhavdadqUetetnovegAbuFronCachmAhavdadqUetetnoadcaryosaClmQYczXKRVyosaClmQYczXKRadcaryosaClmQYczXKRVyosaClmQYczXKR";
        //        sec -> set_IV(unhexlify(bintohex(IV_S)));
        //        std::string secret = write_MPI(rsa_priv_mpi[0]) + write_MPI(rsa_priv_mpi[1]) + write_MPI(rsa_priv_mpi[2]) + write_MPI(rsa_priv_mpi[3]);
        //        sec -> set_secret(use_normal_CFB_encrypt(9, secret + use_hash(2, secret), key, sec -> get_IV()));
        //
        //        std::string keyid = sec -> get_keyid();
        //
        //        if(get_is_debug())
        //            std::cout << "KeyID:" << hexlify(keyid) << std::endl;
        //
        //        Tag13::Ptr uid = std::make_shared<Tag13>();
        //        uid -> set_name(userid);
        //        uid -> set_comment("this is protonmail test");
        //        uid -> set_email("zhj4478@gmail.com");
        //
        //        Tag2::Ptr sig = std::make_shared<Tag2>();
        //        sig -> set_version(RFC4880_V4);
        //        sig -> set_type(RFC4880_CERT_GENERIC);
        //        sig -> set_pka(RFC4880_PKA_RSA);
        //        sig -> set_hash(RFC4880_HASH_SHA256);
        //
        //        //  Tag2Sub2:24
        //        //    Tag2Sub11-PSA: 0908070302
        //        //    Tag2Sub16-KeyID:7d2d53de4bcfb404
        //        //    Tag2Sub21-Pha: 08020a
        //        //    Tag2Sub22-Pca: 0201
        //        //    Tag2Sub27-Flags:03
        //        //    Tag2Sub30-Flags: 01
        //
        //        Tag2Sub2::Ptr tag2sub2 = std::make_shared<Tag2Sub2>();
        //        tag2sub2 -> set_time(1419998500);
        //
        //        Tag2Sub11::Ptr tag2sub11 = std::make_shared<Tag2Sub11>();
        //        tag2sub11 -> set_psa(unhexlify("0908070302"));
        //
        //        Tag2Sub16::Ptr tag2sub16 = std::make_shared<Tag2Sub16>();
        //        tag2sub16 -> set_keyid(keyid);
        //
        //        Tag2Sub21::Ptr tag2sub21 = std::make_shared<Tag2Sub21>();
        //        tag2sub21 -> set_pha(unhexlify("08020a"));
        //
        //        Tag2Sub22::Ptr tag2sub22 = std::make_shared<Tag2Sub22>();
        //        tag2sub22 -> set_pca(unhexlify("0201"));
        //
        //        Tag2Sub27::Ptr tag2sub27 = std::make_shared<Tag2Sub27>();
        //        tag2sub27->set_flags( 0x01 | 0x02);
        //
        //        Tag2Sub30::Ptr tag2sub30 = std::make_shared<Tag2Sub30>();
        //        tag2sub30 -> set_flags(0x01);
        //
        //        //    sub 2 time :1419998489
        //        //    sub 11 : 0908070302 size:5
        //        //    sub 16 : Tag2Sub16-KeyID:7d2d53de4bcfb404
        //        //    sub 21 : Tag2Sub21-Pha: 08020a
        //        //    sub 22 : Tag2Sub22-Pca: 0201 size: 3
        //        //    sub 27 : Tag2Sub27-Flags: 03  size: 1
        //        //    sub 30
        //        //sig -> set_unhashed_subpackets({tag2sub16});
        //        sig->set_hashed_subpackets({tag2sub2 , tag2sub11, tag2sub16, tag2sub21, tag2sub22, tag2sub27, tag2sub30});
        //
        //        std::string sig_hash = to_sign_10(sec, uid, sig);
        //        sig -> set_left16(sig_hash.substr(0, 2));
        //
        //        std::string str_sign = RSA_sign(sig_hash, rsa_priv_mpi, rsa_pub_mpi);
        //        std::cout << hexlify(str_sign) << std::endl;
        //        sig -> set_mpi({str_sign});
        //        
        //        if(get_is_debug())
        //            std::cout << "sig_hash:" << hexlify(sig_hash) << std::endl;
        //        
        //        
        //        
        //        // Secret Subkey Packet
        //        Tag7::Ptr ssb = std::make_shared<Tag7>();
        //        ssb -> set_version(RFC4880_V4);
        //        ssb -> set_time(time);
        //        ssb -> set_pka(RFC4880_PKA_RSA);
        //        ssb -> set_mpi(rsa_pub_mpi);
        //        ssb -> set_s2k_con(RFC4880_S2KU_ENCRYPTED_AND_HASHED);
        //        ssb -> set_sym(RFC4880_SA_AES_256);// AES256
        //        
        //        // Secret Subkey S2K
        //        S2K3::Ptr ssb_s2k3 = std::make_shared<S2K3>();
        //        ssb_s2k3 -> set_hash(RFC4880_HASH_SHA1);
        //        std::string salt_sub = "vegAbuFronCachmAhavdadqUetetnoadcaryosaClmQYczXKRVyosaClmQYczXKR";
        //        ssb_s2k3 -> set_salt(unhexlify(bintohex(salt_sub))); // new salt value
        //        ssb_s2k3 -> set_count(96);
        //        key = ssb_s2k3 -> run(passphrase, Symmetric_Algorithm_Key_Length.at(Symmetric_Algorithms.at(ssb -> get_sym())) >> 3);
        //        std::string IV_sub = "vegAbuFronCacvegAbuFronCachmAhavdadqUetetnoadcaryosaClmQYczXKRVyosaClmQYczXKRhmAhavdadqUetetnoadcaryosaClmQYczXKRVyosaClmQYczXKR";
        //        ssb -> set_s2k(ssb_s2k3);
        //        ssb -> set_IV(unhexlify(bintohex(IV_sub)));
        //        secret = write_MPI(rsa_priv_mpi[0]) + write_MPI(rsa_priv_mpi[1]) + write_MPI(rsa_priv_mpi[2]) + write_MPI(rsa_priv_mpi[3]);
        //        ssb -> set_secret(use_normal_CFB_encrypt(9, secret + use_hash(2, secret), key, ssb -> get_IV()));
        //        
        //        // Subkey Binding Signature
        //        Tag2::Ptr subsig = std::make_shared<Tag2>();
        //        subsig -> set_version(RFC4880_V4);
        //        subsig -> set_type(RFC4880_SIG_SUBKEY);
        //        subsig -> set_pka(RFC4880_PKA_RSA);
        //        subsig -> set_hash(RFC4880_HASH_SHA256);
        //        subsig -> set_hashed_subpackets({tag2sub2});
        //        subsig -> set_unhashed_subpackets({tag2sub16});
        //        sig_hash = to_sign_18(sec, ssb, subsig);
        //        subsig -> set_left16(sig_hash.substr(0, 2));
        //        subsig -> set_mpi(RSA_sign(sig_hash, dsa_pri, dsa_pub));
        //        
        //        PGPSecretKey private_key;
        //        private_key.set_ASCII_Armor(2);
        //        
        //        private_key.set_Armor_Header(std::vector <std::pair <std::string, std::string> > ({
        //            std::pair <std::string, std::string> ("Version", "ProtonMail v0.1.0"),
        //            std::pair <std::string, std::string> ("Comment", "https://protonmail.com")
        //        }));
        //        private_key.set_packets({sec, uid, sig, ssb, subsig});
        //        
        //        std::string private_key_s = private_key.write(2, 2);
        //        PGPPublicKey public_key = PGPPublicKey(private_key);
        //        
        //        
        //        std::cout<< private_key_s << std::endl;
        //        std::cout<< public_key.write() << std::endl;
        //        
        //        sec.reset();
        //        sec_s2k3.reset();
        //        uid.reset();
        //        sig.reset();
        //        tag2sub2.reset();
        //        tag2sub16.reset();
        //        ssb.reset();
        //        ssb_s2k3.reset();
        //        subsig.reset();
        //        
        //    }
        
        
        
    }}
