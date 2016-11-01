//
//  opengpg_clearsign_test.cpp
//  OpenPGP
//
//  Created by Yanfeng Zhang on 11/1/16.
//  Copyright © 2016 Yanfeng Zhang. All rights reserved.
//

#import "utils_test.h"

#include <openpgp/PGPKey.h>
#include <openpgp/encrypt.h>
#include <openpgp/decrypt.h>

#include <openpgp/PGPCleartextSignature.h>
#include <openpgp/private_key.h>
#include <openpgp/pgptime.h>
#include <algorithm>
#include <string>

using namespace pm::pgp;

namespace tests {
    namespace open_pgp_tests {
        
        SUITE(gpg_clearsign)
        {
            const std::string GPG_CLEARSIGN_ALICE =
            "-----BEGIN PGP SIGNED MESSAGE-----" "\n"
            "Hash: SHA1" "\n"
            "" "\n"
            "The magic words are squeamish ossifrage" "\n"
            "-----BEGIN PGP SIGNATURE-----" "\n"
            "Version: GnuPG v1" "\n"
            "" "\n"
            "iQEcBAEBAgAGBQJTptSlAAoJENXX2nHDVJYOd44H/00d+QOSWbQngtMMkeKa6fes" "\n"
            "IOYj6Gwl4GnKRBr8ShzsMMlIbBoXeZ6LHTncuCQLdCadCDrWLwkjIZX++Eq8qIbE" "\n"
            "X1JjvqoC3eSwo+pP9lnTvKq1UJqdJl5jJtVg+NBmLsBzR/vzYOJCH4UfEtkjzqyE" "\n"
            "E5JFdH7zGAuDbrR4VCjJ6m/lhC5W1rp1grJ4tcporWvLemMFaPgAUXJk3c5pDJar" "\n"
            "WSVgO+g7VSB99FSDyc9X+IVW5agGkQ+yE+XLPuArxF5OSolOuuxpZ1Vc+udhVlei" "\n"
            "OaRSP1bQ45nM01EY0rTayiGAsP4k2NJYxZ+CA9y4V5+JgIAjIasnSZK88j2dAJU=" "\n"
            "=dvc9" "\n"
            "-----END PGP SIGNATURE-----"
            ;
            
            TEST(clearsign) {
                
                std::string in = GPG_CLEARSIGN_ALICE;
                PGPCleartextSignature pgp(in);
                
                VERIFY_ARE_EQUAL(pgp.get_message(), "The magic words are squeamish ossifrage");
                
                auto key = pgp.get_sig();
                auto packets = key.get_packets();
                
                VERIFY_ARE_EQUAL(packets.size(), 1);
                
                Packet::Ptr p0 = packets[0];
                VERIFY_ARE_EQUAL(p0->get_tag(), 2);
                
                Tag2::Ptr tag2 = std::dynamic_pointer_cast<Tag2>(p0);
                
                VERIFY_ARE_EQUAL(tag2->get_version(), 4);
                
                VERIFY_ARE_EQUAL(tag2->get_size(), 284);
                
                VERIFY_ARE_EQUAL(tag2->get_pka(), 1);  // RSA
                VERIFY_ARE_EQUAL(tag2->get_hash(), 2); // SHA1
                VERIFY_ARE_EQUAL(tag2->get_left16(), "\x77\x8e");
                
                auto mpi = tag2->get_mpi();
                VERIFY_ARE_EQUAL(mpi.size(), 1);
                auto sign = mpi[0];
                VERIFY_ARE_EQUAL(bitsize(sign), 2047);
                auto strHex_sign = mpitohex(sign);
                std::transform(strHex_sign.begin(), strHex_sign.end(), strHex_sign.begin(), ::tolower);
                VERIFY_ARE_EQUAL(strHex_sign, "4d1df9039259b42782d30c91e29ae9f7ac20e623e86c25e069ca441afc4a1cec30c9486c1a17799e8b1d39dcb8240b74269d083ad62f09232195fef84abca886c45f5263beaa02dde4b0a3ea4ff659d3bcaab5509a9d265e6326d560f8d0662ec07347fbf360e2421f851f12d923ceac84139245747ef3180b836eb4785428c9ea6fe5842e56d6ba7582b278b5ca68ad6bcb7a630568f800517264ddce690c96ab5925603be83b55207df45483c9cf57f88556e5a806910fb213e5cb3ee02bc45e4e4a894ebaec6967555cfae7615657a239a4523f56d0e399ccd35118d2b4daca2180b0fe24d8d258c59f8203dcb8579f8980802321ab274992bcf23d9d0095");
                
                // hashed
                {
                    auto hashed = tag2->get_hashed_subpackets();
                    VERIFY_ARE_EQUAL(hashed.size(), 1);
                    
                    Subpacket::Ptr s0 = hashed[0];
                    VERIFY_ARE_EQUAL(s0->get_type(), 2);
                    
                    Tag2Sub2::Ptr sub2 = std::dynamic_pointer_cast<Tag2Sub2>(s0);
                    VERIFY_ARE_EQUAL(sub2->get_time(), get_utc(2014, 06, 22, 13, 05, 41));
                }
                // unhashed
                {
                    auto unhashed = tag2->get_unhashed_subpackets();
                    VERIFY_ARE_EQUAL(unhashed.size(), 1);
                    
                    Subpacket::Ptr s0 = unhashed[0];
                    VERIFY_ARE_EQUAL(s0->get_type(), 16);
                    
                    Tag2Sub16::Ptr sub16 = std::dynamic_pointer_cast<Tag2Sub16>(s0);
                    VERIFY_ARE_EQUAL(sub16->get_keyid(), "\xd5\xd7\xda\x71\xc3\x54\x96\x0e");
                }
                
            }
        }
    }
}
