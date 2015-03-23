//
//  private_key.cpp
//  UNNetPGP
//
//  Created by Yanfeng Zhang on 1/21/15.
//  Copyright (c) 2015 UP-NEXT. All rights reserved.
//

#include "private_key.h"

#include "config.h"
#include "RFC4880.h"

#include "Tag5.h"
#include <base/rsa_key.h>
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
#include <pgp/PGPKey.h>
#include "cfb.h"
#include "sigcalc.h"
#include <encryption/RSA.h>
#include "sign.h"

namespace pm {
    namespace pgp
    {
        std::string update_passphrase(PGPSecretKey & pri, const std::string & old_pwd, const std::string & new_pwd)
        {
            if (pri.get_ASCII_Armor() != 2){
                throw std::runtime_error("Error: No Private Key found.");
            }
            
            //find default private key;
            Tag5::Ptr sec = find_decrypting_key(pri, "", true);
            if (!sec){
                throw std::runtime_error("Error: Correct Private Key not found.");
            }
            std::vector <std::string> pub_mpi = sec -> get_mpi();
            std::vector <std::string> pri_mpi = decrypt_secret_key(sec, old_pwd);
            
            // Secret Key Packet S2K
            S2K3::Ptr sec_s2k3 = std::make_shared<S2K3>();
            sec_s2k3 -> set_hash(RFC4880_HASH_SHA256);
            sec_s2k3 -> set_salt(unhexlify(bintohex(BBS().rand_b(64))));
            sec_s2k3 -> set_count(96);
            // calculate the key from the passphrase
            std::string key = sec_s2k3 -> run(new_pwd, Symmetric_Algorithm_Key_Length.at(Symmetric_Algorithms.at(sec -> get_sym())) >> 3);
            // encrypt private key value
            sec -> set_s2k(sec_s2k3);
            sec -> set_IV(unhexlify(bintohex(BBS().rand_b(Symmetric_Algorithm_Block_Length.at(Symmetric_Algorithms.at(sec -> get_sym()))))));
            std::string secret = write_MPI(pri_mpi[0]) + write_MPI(pri_mpi[1]) + write_MPI(pri_mpi[2]) + write_MPI(pri_mpi[3]);
            sec -> set_secret(use_normal_CFB_encrypt(9, secret + use_hash(2, secret), key, sec -> get_IV()));

            
            //find default private key;
            Tag7::Ptr ssb = find_decrypting_sub_key(pri, "", true);
            if (!sec){
                throw std::runtime_error("Error: Correct Private Key not found.");
            }
            //std::vector <std::string> pub_sub_mpi = ssb -> get_mpi();
            std::vector <std::string> pri_sub_mpi = decrypt_secret_key(ssb, old_pwd);
            // Secret Subkey S2K
            S2K3::Ptr ssb_s2k3 = std::make_shared<S2K3>();
            ssb_s2k3 -> set_hash(RFC4880_HASH_SHA256);
            ssb_s2k3 -> set_salt(unhexlify(bintohex(BBS().rand_b(64)))); // new salt value
            ssb_s2k3 -> set_count(96);
            std::string subkey = ssb_s2k3 -> run(new_pwd, Symmetric_Algorithm_Key_Length.at(Symmetric_Algorithms.at(ssb -> get_sym())) >> 3);
            ssb -> set_s2k(ssb_s2k3);
            ssb -> set_IV(unhexlify(bintohex(BBS().rand_b(Symmetric_Algorithm_Block_Length.at(Symmetric_Algorithms.at(ssb -> get_sym()))))));
            std::string sub_secret = write_MPI(pri_sub_mpi[0]) + write_MPI(pri_sub_mpi[1]) + write_MPI(pri_sub_mpi[2]) + write_MPI(pri_sub_mpi[3]);
            ssb -> set_secret(use_normal_CFB_encrypt(9, sub_secret + use_hash(2, sub_secret), subkey, ssb -> get_IV()));
            
            // Subkey Binding Signature
//            Tag2::Ptr subsig = std::make_shared<Tag2>();
//            subsig -> set_version(RFC4880_V4);
//            subsig -> set_type(RFC4880_SIG_SUBKEY);
//            subsig -> set_pka(RFC4880_PKA_RSA);
//            subsig -> set_hash(RFC4880_HASH_SHA256);
//            
//            Tag2Sub27::Ptr sb_tag2sub27 = std::make_shared<Tag2Sub27>();
//            sb_tag2sub27->set_flags(12);
//            Tag2Sub16::Ptr tag2sub16 = std::make_shared<Tag2Sub16>();
//            tag2sub16 -> set_keyid(sec->get_keyid());
//            Tag2Sub2::Ptr tag2sub2 = std::make_shared<Tag2Sub2>();
//            tag2sub2 -> set_time(sec->get_time());
//            subsig -> set_hashed_subpackets({tag2sub2, sb_tag2sub27});
//            subsig -> set_unhashed_subpackets({tag2sub16});
//            std::string sig_hash = to_sign_18(sec, ssb, subsig);
//            subsig -> set_left16(sig_hash.substr(0, 2));
//            subsig -> set_mpi({RSA_sign(sig_hash, pri_mpi, pub_mpi)});

        
            pri.update_packet(0, sec);
            pri.update_packet(3, ssb);
            //pri.update_packet(4, subsig);
            
            std::string priv = pri.write(2, 2);
            
            
            //std::cout << priv << std::endl;
            
            return priv;
//            //
//            //    std::cout<< "D: " << hexlify( pri_mpi[0]) << std::endl;
//            //    std::cout<< "P: " << hexlify(pri_mpi[1]) << std::endl;
//            //    std::cout<< "Q: " << hexlify(pri_mpi[2]) << std::endl;
//            //    std::cout<< "U: " << hexlify(pri_mpi[3]) << std::endl;
//            //
//            // get session key
//            session_key = zero + pka_decrypt(pka, session_key_mpi, pri_mpi, pub_mpi);     // symmetric algorithm, session key, 2 octet checksum wrapped in EME_PKCS1_ENCODE
//            session_key = EME_PKCS1v1_5_DECODE(session_key);                              // remove EME_PKCS1 encoding
//            sym = session_key[0];                                                         // get symmetric algorithm
//            std::string checksum = session_key.substr(session_key.size() - 2, 2);         // get 2 octet checksum
//            session_key = session_key.substr(1, session_key.size() - 3);                  // remove both from session key
//            uint16_t sum = 0;
//            for(char & c : session_key){                                                  // calculate session key checksum
//                sum += static_cast <uint8_t> (c);
//            }
//            if (unhexlify(makehex(sum, 4)) != checksum){                                  // check session key checksums
//                throw std::runtime_error("Error: Calculated session key checksum does not match given checksum.");
//            }
//            
//            sec.reset();
//            
//            // std::cout << hexlify(session_key) << std::endl;
//            
//            // decrypt the data with the extracted key
//            PGPMessage decrypted = decrypt_data(sym, m, session_key, writefile, verify);
//            
//            std::string out = "";
//            // if signing key provided, check the signature
//            if (verify){
//                // out = "Message was" + std::string(verify_message(*verify, decrypted)?"":" not") + " signed by key " + hexlify(verify -> keyid()) + ".\n";
//            }
//            
//            // extract data
//            for(Packet::Ptr const & p : decrypted.get_packets()){
//                if (p -> get_tag() == 11){
//                    std::string raw = p -> raw();
//                    Tag11 tag11(raw);
//                    out += tag11.out(writefile);
//                }
//            }
            
            
//            // Secret Key Packet
//            Tag5::Ptr sec = std::make_shared<Tag5>();
//            sec -> set_version(RFC4880_V4);
//            sec -> set_time(time);
//            sec -> set_pka(RFC4880_PKA_RSA);//RSA
//            sec -> set_mpi(rsa_pub_mpi);
//            sec -> set_s2k_con(RFC4880_S2KU_ENCRYPTED_AND_HASHED);
//            sec -> set_sym(RFC4880_SA_AES_256);// AES256
//            
//            
//            // Secret Key Packet S2K
//            S2K3::Ptr sec_s2k3 = std::make_shared<S2K3>();
//            sec_s2k3 -> set_hash(RFC4880_HASH_SHA1);
//            std::string salt_s = "vegAbuFronCachmAhavdadqUetetnoadcaryosaClmQYczXKRVyosaClmQYczXKR";
//            sec_s2k3 -> set_salt(unhexlify(bintohex(salt_s)));
//            sec_s2k3 -> set_count(96);
//            
//            // calculate the key from the passphrase
//            std::string key = sec_s2k3 -> run(passphrase, Symmetric_Algorithm_Key_Length.at(Symmetric_Algorithms.at(sec -> get_sym())) >> 3);
//            // encrypt private key value
//            sec -> set_s2k(sec_s2k3);
//            // uint16_t p_bits = Symmetric_Algorithm_Block_Length.at(Symmetric_Algorithms.at(sec -> get_sym()));
//            std::string IV_S = "vegAbuFronCachmAhavdadqUetetnovegAbuFronCachmAhavdadqUetetnoadcaryosaClmQYczXKRVyosaClmQYczXKRadcaryosaClmQYczXKRVyosaClmQYczXKR";
//            sec -> set_IV(unhexlify(bintohex(IV_S)));
//            std::string secret = write_MPI(rsa_priv_mpi[0]) + write_MPI(rsa_priv_mpi[1]) + write_MPI(rsa_priv_mpi[2]) + write_MPI(rsa_priv_mpi[3]);
//            sec -> set_secret(use_normal_CFB_encrypt(9, secret + use_hash(2, secret), key, sec -> get_IV()));
//            
//            std::string keyid = sec -> get_keyid();
//            
//            if(get_is_debug())
//                std::cout << "KeyID:" << hexlify(keyid) << std::endl;
//            
//            Tag13::Ptr uid = std::make_shared<Tag13>();
//            uid -> set_name(userid);
//            uid -> set_comment("this is protonmail test");
//            uid -> set_email("zhj4478@gmail.com");
//            
//            Tag2::Ptr sig = std::make_shared<Tag2>();
//            sig -> set_version(RFC4880_V4);
//            sig -> set_type(RFC4880_CERT_GENERIC);
//            sig -> set_pka(RFC4880_PKA_RSA);
//            sig -> set_hash(RFC4880_HASH_SHA256);
//            
//            Tag2Sub2::Ptr tag2sub2 = std::make_shared<Tag2Sub2>();
//            tag2sub2 -> set_time(time);
//            
//            Tag2Sub11::Ptr tag2sub11 = std::make_shared<Tag2Sub11>();
//            tag2sub11 -> set_psa(unhexlify("0908070302"));
//            
//            Tag2Sub16::Ptr tag2sub16 = std::make_shared<Tag2Sub16>();
//            tag2sub16 -> set_keyid(keyid);
//            
//            Tag2Sub21::Ptr tag2sub21 = std::make_shared<Tag2Sub21>();
//            tag2sub21 -> set_pha(unhexlify("08020a"));
//            
//            Tag2Sub22::Ptr tag2sub22 = std::make_shared<Tag2Sub22>();
//            tag2sub22 -> set_pca(unhexlify("0201"));
//            
//            Tag2Sub27::Ptr tag2sub27 = std::make_shared<Tag2Sub27>();
//            tag2sub27->set_flags( 0x01 | 0x02);
//            
//            Tag2Sub30::Ptr tag2sub30 = std::make_shared<Tag2Sub30>();
//            tag2sub30 -> set_flags(0x01);
//            
//            //    sub 2 time :1419998489
//            //    sub 11 : 0908070302 size:5
//            //    sub 16 : Tag2Sub16-KeyID:7d2d53de4bcfb404
//            //    sub 21 : Tag2Sub21-Pha: 08020a
//            //    sub 22 : Tag2Sub22-Pca: 0201 size: 3
//            //    sub 27 : Tag2Sub27-Flags: 03  size: 1
//            //    sub 30
//            //sig -> set_unhashed_subpackets({tag2sub16});
//            sig->set_hashed_subpackets({tag2sub2 , tag2sub11, tag2sub16, tag2sub21, tag2sub22, tag2sub27, tag2sub30});
//            
//            std::string sig_hash = to_sign_13(sec, uid, sig);
//            sig -> set_left16(sig_hash.substr(0, 2));
//            //sig -> set_mpi(DSA_sign(sig_hash, dsa_pri, dsa_pub));
//            
//            
//            
//            if(get_is_debug())
//                std::cout << "sig_hash:" << hexlify(sig_hash) << std::endl;
//            
//            // Secret Subkey Packet
//            Tag7::Ptr ssb = std::make_shared<Tag7>();
//            ssb -> set_version(RFC4880_V4);
//            ssb -> set_time(time);
//            ssb -> set_pka(RFC4880_PKA_RSA);// ElGamal
//            ssb -> set_mpi(rsa_pub_mpi);
//            ssb -> set_s2k_con(RFC4880_S2KU_ENCRYPTED_AND_HASHED);
//            ssb -> set_sym(RFC4880_SA_AES_256);// AES256
//            
//            // Secret Subkey S2K
//            S2K3::Ptr ssb_s2k3 = std::make_shared<S2K3>();
//            ssb_s2k3 -> set_hash(RFC4880_HASH_SHA1);
//            std::string salt_sub = "vegAbuFronCachmAhavdadqUetetnoadcaryosaClmQYczXKRVyosaClmQYczXKR";
//            ssb_s2k3 -> set_salt(unhexlify(bintohex(salt_sub))); // new salt value
//            ssb_s2k3 -> set_count(96);
//            key = ssb_s2k3 -> run(passphrase, Symmetric_Algorithm_Key_Length.at(Symmetric_Algorithms.at(ssb -> get_sym())) >> 3);
//            std::string IV_sub = "vegAbuFronCacvegAbuFronCachmAhavdadqUetetnoadcaryosaClmQYczXKRVyosaClmQYczXKRhmAhavdadqUetetnoadcaryosaClmQYczXKRVyosaClmQYczXKR";
//            ssb -> set_s2k(ssb_s2k3);
//            ssb -> set_IV(unhexlify(bintohex(IV_sub)));
//            secret = write_MPI(rsa_priv_mpi[0]) + write_MPI(rsa_priv_mpi[1]) + write_MPI(rsa_priv_mpi[2]) + write_MPI(rsa_priv_mpi[3]);
//            ssb -> set_secret(use_normal_CFB_encrypt(9, secret + use_hash(2, secret), key, ssb -> get_IV()));
//            
//            // Subkey Binding Signature
//            Tag2::Ptr subsig = std::make_shared<Tag2>();
//            subsig -> set_version(RFC4880_V4);
//            subsig -> set_type(RFC4880_SIG_SUBKEY);
//            subsig -> set_pka(RFC4880_PKA_RSA);
//            subsig -> set_hash(RFC4880_HASH_SHA256);
//            subsig -> set_hashed_subpackets({tag2sub2});
//            subsig -> set_unhashed_subpackets({tag2sub16});
//            sig_hash = to_sign_18(sec, ssb, subsig);
//            subsig -> set_left16(sig_hash.substr(0, 2));
//            //subsig -> set_mpi(DSA_sign(sig_hash, dsa_pri, dsa_pub));
//            //RSA_sign(int type, const unsigned char *m, unsigned int m_length, unsigned char *sigret, unsigned int *siglen, RSA *rsa)
//            
//            PGPSecretKey private_key;
//            private_key.set_ASCII_Armor(2);
//            
//            private_key.set_Armor_Header(std::vector <std::pair <std::string, std::string> > ({
//                std::pair <std::string, std::string> ("Version", "ProtonMail v0.1.0"),
//                std::pair <std::string, std::string> ("Comment", "https://protonmail.com")
//            }));
//            private_key.set_packets({sec, uid, sig, ssb, subsig});
//            
//            std::string private_key_s = private_key.write(2, 2);
//            
//            PGPPublicKey public_key = PGPPublicKey(private_key);
//            
//            std::cout<< private_key_s << std::endl;
//            std::cout<< public_key.write() << std::endl;
        }
        
        
        
        Tag5::Ptr find_decrypting_key(const PGPSecretKey & k, const std::string & keyid, const bool& find_default){
            for(Packet::Ptr const & p : k.get_packets()){
                if ((p -> get_tag() == 5) || (p -> get_tag() == 7)){
                    std::string raw = p -> raw();
                    Tag5::Ptr key = std::make_shared<Tag5>(raw);
                    if (key -> get_public_ptr() -> get_keyid() != keyid && find_default == false){
                        key.reset();
                        continue;
                    }
                    // make sure key has encrypting keys
                    if ((key -> get_pka() == 1) || // RSA
                        (key -> get_pka() == 2) || // RSA
                        (key -> get_pka() == 16)){ // ElGamal
                        return key;
                    }
                    key.reset();
                }
            }
            return nullptr;
        }

        Tag7::Ptr find_decrypting_sub_key(const PGPSecretKey & k, const std::string & keyid, const bool& find_default){
            for(Packet::Ptr const & p : k.get_packets()){
                if ((p -> get_tag() == 7)){
                    std::string raw = p -> raw();
                    Tag7::Ptr key = std::make_shared<Tag7>(raw);
                    if (key -> get_public_ptr() -> get_keyid() != keyid  && find_default == false){
                        key.reset();
                        continue;
                    }
                    // make sure key has encrypting keys
                    if ((key -> get_pka() == 1) || // RSA
                        (key -> get_pka() == 2) || // RSA
                        (key -> get_pka() == 16)){ // ElGamal
                        return key;
                    }
                    key.reset();
                }
            }
            return nullptr;
        }

//        Tag2::Ptr find_sign(const PGPSecretKey & k, const std::string & keyid, const bool& find_default)
//        {
//            for(Packet::Ptr const & p : k.get_packets()){
//                if ((p -> get_tag() == 2)){
//                    std::string raw = p -> raw();
//                    Tag2::Ptr key = std::make_shared<Tag2>(raw);
//                    if (key -> get_public_ptr() -> get_keyid() != keyid  && find_default == false){
//                        key.reset();
//                        continue;
//                    }
//                    // make sure key has encrypting keys
//                    if ((key -> get_pka() == 1) || // RSA
//                        (key -> get_pka() == 2) || // RSA
//                        (key -> get_pka() == 16)){ // ElGamal
//                        return key;
//                    }
//                    key.reset();
//                }
//            }
//            return nullptr;
//
//        }
//        Tag2::Ptr find_sub_sign(const PGPSecretKey & k, const std::string & keyid, const bool& find_default = false)
//        {
//            for(Packet::Ptr const & p : k.get_packets()){
//                if ((p -> get_tag() == 2)){
//                    std::string raw = p -> raw();
//                    Tag5::Ptr key = std::make_shared<Tag5>(raw);
//                    if (key -> get_public_ptr() -> get_keyid() != keyid  && find_default == false){
//                        key.reset();
//                        continue;
//                    }
//                    // make sure key has encrypting keys
//                    if ((key -> get_pka() == 1) || // RSA
//                        (key -> get_pka() == 2) || // RSA
//                        (key -> get_pka() == 16)){ // ElGamal
//                        return key;
//                    }
//                    key.reset();
//                }
//            }
//            return nullptr;
//            
//        }
//        Tag13::Ptr find_id(const PGPSecretKey & k, const std::string & keyid, const bool& find_default = false)
//        {
//            for(Packet::Ptr const & p : k.get_packets()){
//                if ((p -> get_tag() == 2)){
//                    std::string raw = p -> raw();
//                    Tag5::Ptr key = std::make_shared<Tag5>(raw);
//                    if (key -> get_public_ptr() -> get_keyid() != keyid  && find_default == false){
//                        key.reset();
//                        continue;
//                    }
//                    // make sure key has encrypting keys
//                    if ((key -> get_pka() == 1) || // RSA
//                        (key -> get_pka() == 2) || // RSA
//                        (key -> get_pka() == 16)){ // ElGamal
//                        return key;
//                    }
//                    key.reset();
//                }
//            }
//            return nullptr;
//            
//        }
        
        
        std::vector <std::string> decrypt_secret_key(const Tag5::Ptr & pri, const std::string & passphrase){
            std::vector <std::string> out;
            S2K::Ptr s2k = pri -> get_s2k();
            
            // calculate key used in encryption algorithm
            std::string key = s2k -> run(passphrase, Symmetric_Algorithm_Key_Length.at(Symmetric_Algorithms.at(pri -> get_sym())) >> 3);
            //std::cout << hexlify(key) << std::endl;
            
            // decrypt secret key
            std::string secret_key = use_normal_CFB_decrypt(pri -> get_sym(), pri -> get_secret(), key, pri -> get_IV());
            
            // std::cout << hexlify(secret_key) << std::endl;
            
            // get checksum and remove it from the string
            const unsigned int hash_size = (pri -> get_s2k_con() == 254)?20:2;
            std::string checksum = secret_key.substr(secret_key.size() - hash_size, hash_size);
            secret_key = secret_key.substr(0, secret_key.size() - hash_size);
            //std::cout << hexlify(secret_key) << std::endl;
            
            // calculate and check checksum
            if(pri -> get_s2k_con() == 254){
                //  std::cout << hexlify(checksum) << std::endl;
                
                
                std::string hash_check = use_hash(2, secret_key); //use_hash(s2k -> get_hash(), secret_key);
                //  std::cout << hexlify(hash_check) << std::endl;
                
                if (hash_check != checksum){
                    throw std::runtime_error("Error: Secret key checksum and calculated checksum do not match.");
                }
            }
            else{ // all other values; **UNTESTED**
                uint16_t sum = 0;
                for(char & c : secret_key){
                    sum += static_cast <unsigned char> (c);
                }
                if (unhexlify(makehex(sum, 4)) != checksum){
                    if (use_hash(s2k -> get_hash(), secret_key) != checksum){
                        throw std::runtime_error("Error: Secret key checksum and calculated checksum do not match.");
                    }
                }
            }
            
            // extract MPI values
            while (secret_key.size()){
                out.push_back(read_MPI(secret_key));
            }
            
            s2k.reset();
            
            return out;
        }

        
//        Tag5::Ptr encrypt_secret_key()
//        {
//        }
        
    }
}