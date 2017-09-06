/*
encrypt.h
Function to encrypt data with a PGP public key

Copyright (c) 2013, 2014 Jason Lee

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
*/

#ifndef __PGPENCRYPT__
#define __PGPENCRYPT__

#include <iostream>
#include <sstream>
#include <stdexcept>
#include <vector>

#include <compress/compress.h>
#include <hash/Hashes.h>
#include <encryption/PKA.h>
#include <openpgp/cfb.h>
#include <utilities/mpi.h>
#include <openpgp/PGPKey.h>
#include <openpgp/PGPMessage.h>
//#include "PKCS1.h"
//#include "revoke.h"
#include <package/Tag6.h>
#include <openpgp/PMPGPMessage.h>

Tag6::Ptr find_encrypting_key(const PGP & k);
//std::vector <std::string> pka_encrypt(const uint8_t pka, std::string data, const std::vector <std::string> & pub);
std::vector <std::string> pka_encrypt(const uint8_t pka, const std::string & data, const std::vector <std::string> & pub);

Packet::Ptr encrypt_data(const std::string & session_key, const std::string & data, const std::string & filename = "", const uint8_t sym_alg = 9, const uint8_t comp = 1, const bool mdc = true, const PGPSecretKey::Ptr & signer = nullptr, const std::string & sig_passphrase = "");

std::vector<Packet::Ptr> encrypt(const std::string & session_key, const std::string & data, const std::string & filename = "", const uint8_t sym_alg = 9, const uint8_t comp = 1, const bool mdc = true, const PGPSecretKey::Ptr & signer = nullptr, bool signerExternal = true, const std::string & sig_passphrase = "");

// Encrypt data
// Default:
//      Symmetric Key Algorithm: AES256
//      Compression Algorithm: ZLIB
//      Use Modification Detection Packet: true
//
std::string encrypt_pm_pka(const PGPPublicKey & pub, const std::string & data);

//pm::PMPGPMessage encrypt_pka(const PGPPublicKey & pub, const std::string & data, const std::string & filename = "", const uint8_t sym_alg = 9, const uint8_t comp = 2, const bool mdc = true, const PGPSecretKey::Ptr & signer = nullptr, const std::string & sig_passphrase = "", bool is_pm_pka = true);
PGPMessage encrypt_pka(const PGPPublicKey & pub, const std::string & data, const std::string & filename = "", const uint8_t sym_alg = 9, const uint8_t comp = 2, const bool mdc = true, const PGPSecretKey::Ptr & signer = nullptr, const std::string & sig_passphrase = "");

PGPMessage encrypt_pka_only_data(const std::string & sessionkey, const std::string & data, const std::string & filename = "", const uint8_t sym_alg = 9, const uint8_t comp = 2, const bool mdc = true, const PGPSecretKey::Ptr & signer = nullptr, const std::string & sig_passphrase = "");
PGPMessage encrypt_pka_only_session(const PGPPublicKey & pub, std::string & session_key, const uint8_t sym_alg=9);
PGPMessage encrypt_pka_only_sym_session(const std::string & passphrase, std::string & session_key, const uint8_t sym_alg=9);


//this is new and will need refactor for this file
std::vector<PGPMessage::Ptr> encrypt(const PGPPublicKey & pub, const std::string & data, const std::string & filename = "", const uint8_t sym_alg = 9, const uint8_t comp = 2, const bool mdc = true, const PGPSecretKey::Ptr & signer = nullptr, bool signerExternal = true, const std::string & sig_passphrase = "");


PGPMessage encrypt_sym(const std::string & passphrase, const std::string & data, const std::string & filename = "", const uint8_t sym_alg = 9, const uint8_t comp = 2, const bool mdc = true, const PGPSecretKey::Ptr & signer = nullptr, const std::string & sig_passphrase = "");


std::string generat_session_key (const uint8_t sym_alg = 9);


#endif
