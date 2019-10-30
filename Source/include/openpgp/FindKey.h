//
//  FindKey.h
//  OpenPGP_OSX_Lib
//
//  Created by Yanfeng Zhang on 4/7/15.
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



#ifndef __OpenPGP_OSX_Lib__FindKey__
#define __OpenPGP_OSX_Lib__FindKey__

#include <openpgp/pgp.h>
#include <package/Tag5.h>
#include <package/Tag6.h>


std::ostream & operator <<(std::ostream & stream, const PGPPublicKey & pgp);

// Extract Public Key data from a Secret Key
PGPPublicKey Secret2PublicKey(const PGPSecretKey & pri);
PGPPublicKey::Ptr Secret2PublicKeyPtr(const PGPSecretKey & pri);
PGPPublicKey::Ptr Secret2PublicKey(const PGPSecretKey::Ptr &pri);

// Search PGP keys for signing keys
// leave keyid empty to find the signing key without matching the key id
Key::Ptr find_signing_key(const PGPKey::Ptr & key, const uint8_t tag, const std::string & keyid = "");
Tag6::Ptr find_signing_key(const PGPPublicKey & key, const uint8_t tag, const std::string & keyid = "");
Tag5::Ptr find_signing_key(const PGPSecretKey & key, const uint8_t tag, const std::string & keyid = "");

#endif /* defined(__OpenPGP_OSX_Lib__FindKey__) */
