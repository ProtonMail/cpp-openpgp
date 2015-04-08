//
//  FindKey.h
//  OpenPGP_OSX_Lib
//
//  Created by Yanfeng Zhang on 4/7/15.
//  Copyright (c) 2015 Yanfeng Zhang. All rights reserved.
//

#ifndef __OpenPGP_OSX_Lib__FindKey__
#define __OpenPGP_OSX_Lib__FindKey__

#include <openpgp/pgp.h>
#include <package/Tag5.h>
#include <package/Tag6.h>


std::ostream & operator <<(std::ostream & stream, const PGPPublicKey & pgp);

// Extract Public Key data from a Secret Key
PGPPublicKey Secret2PublicKey(const PGPSecretKey & pri);

// Search PGP keys for signing keys
// leave keyid empty to find the signing key without matching the key id
Key::Ptr find_signing_key(const PGPKey::Ptr & key, const uint8_t tag, const std::string & keyid = "");
Tag6::Ptr find_signing_key(const PGPPublicKey & key, const uint8_t tag, const std::string & keyid = "");
Tag5::Ptr find_signing_key(const PGPSecretKey & key, const uint8_t tag, const std::string & keyid = "");

#endif /* defined(__OpenPGP_OSX_Lib__FindKey__) */
