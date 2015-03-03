/*
decrypt.h
Functions for decrypting PGP encrypted data

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

#ifndef __DECRYPT__
#define __DECRYPT__

#include <iostream>
#include <sstream>
#include <stdexcept>
#include <vector>

#include "Compress.h"
#include "Hashes.h"
#include "packets.h"
#include "PKA/PKA.h"
#include "cfb.h"
#include "consts.h"
#include "mpi.h"
#include "PGPKey.h"
#include "PGPMessage.h"
#include "PMPGPMessage.h"



std::string pka_decrypt(const uint8_t pka, std::vector <std::string> & data, const std::vector <std::string> & pri, const std::vector <std::string> & pub = {});

// decrypt data once session key is known
PGPMessage decrypt_data(const uint8_t sym, const PGPMessage & m, const std::string & session_key, const bool writefile = true, const PGPPublicKey::Ptr & verify = nullptr);

std::string decrypt_pm_pka(const PGPSecretKey & pri, const std::string & passphrase, const std::string & msg);

// called from outside
// session key encrypted with public key algorithm; will call decrypt_sym if tag3 is found
std::string decrypt_pka(const PGPSecretKey & pri, const PGPMessage & m, const std::string & passphrase, const bool writefile = true, const PGPPublicKey::Ptr & verify = nullptr);
std::string decrypt_pka(const PGPSecretKey & pri, const pm::PMPGPMessage & m, const std::string & passphrase, const bool writefile = true, const PGPPublicKey::Ptr & verify = nullptr);
// session key encrypted with symmetric algorithm
std::string decrypt_sym(const PGPMessage & m, const std::string & passphrase, const bool writefile = true, const PGPPublicKey::Ptr & verify = nullptr);



#endif
