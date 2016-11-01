//
//  openpgp_publickey_test.cpp
//  OpenPGP
//
//  Created by Yanfeng Zhang on 10/31/16.
//  Copyright © 2016 Yanfeng Zhang. All rights reserved.
//

#import "utils_test.h"

#include <openpgp/PGPKey.h>
#include <openpgp/encrypt.h>
#include <openpgp/decrypt.h>
#include <algorithm>
#include <string>

namespace tests {
    namespace open_pgp_tests {
        time_t get_utc(int year, int month, int day, int hour, int minute, int second) {
            tm in;
            in.tm_year = year - 1900;
            in.tm_mon  = month - 1;
            in.tm_mday = day;
            in.tm_hour = hour;
            in.tm_min  = minute;
            in.tm_sec  = second;
            time_t result = mktime(&in); // generate by local timezone
            
            // detect timezone
            int utc = 0, local = 0;
            tm *tmp;
            tmp = gmtime(&result);
            utc = tmp->tm_hour;
            tmp = localtime(&result);
            local = tmp->tm_hour;
            if ( utc != local ) {
                int diff = local - utc;
                if ( diff < 0 && diff < -12 ) {
                    diff += 24;
                } else if (diff > 0 && diff > 12) {
                    diff -= 24;
                }
                result += diff*60*60;
            }
            return result;
        }

        SUITE(pgp_public_key)
        {
            
            const std::string GPG_PUBKEY_ALICE =
            "-----BEGIN PGP PUBLIC KEY BLOCK-----" "\n"
            "Version: GnuPG v1" "\n"
            "" "\n"
            "mQENBFOm0SgBCAC8BH6U1HHzzL1SXWpvjhf3sfAFJ8ciw5E854f70AkOOvi+fllB" "\n"
            "D2OzmDqVB7dhBFwRUQ5i9ajPvNwYCXakwiVze44G2FMfOMbqqZaVTVUhpnYyMfB8" "\n"
            "K0NgXQUqvfOdbGaKyUvIn1QwUtBQUwxwxIpJqXCGfAAXj5B23Q4VHSVGMnZ7KSbp" "\n"
            "uqIsbQwhPx9F3nSZE5bX6NEFCM9nkTlBCrMRsSed08DTf6zKVNUjzRSj30iOuPWS" "\n"
            "xaGbz+3mfIFwgVxYit850YgZfaQEkqrFsYPDA/bvI7C15I/3Oy2AavsPtPFroydp" "\n"
            "JJ06fKDvC5s9V4Utyal5ttVvPcFw4o3LLlNtABEBAAG0JGFsaWNlICh0ZXN0IGtl" "\n"
            "eSkgPGFsaWNlQGV4YW1wbGUuY29tPokBOAQTAQIAIgUCU6bRKAIbAwYLCQgHAwIG" "\n"
            "FQgCCQoLBBYCAwECHgECF4AACgkQ1dfaccNUlg4EXgf/aIoYolj4Zs9Q8ck43BWx" "\n"
            "EpjaC/vWgCQfUlRa9QI3IoWM37V52iLmba423/moF/eXGS6VtwdLq0k4GsuDfxIW" "\n"
            "1Ojjwt4vtVR6UVtSNoI7y0s7yhpoRV+phMTcIbGlryMIrqWAwK4so/XbNDvqpVlS" "\n"
            "RwLQnkDRkjMU7w8VZGrOyRucbZy6nZuH+nhialIq4VIPCu02HfAPgZGp7LH7EnMu" "\n"
            "n25eHEvs45fk3Pus1BkYiCwt+nW5i1RYfwzWEZW9zkG2kDKadGxuN7fi75sGIGvy" "\n"
            "gP+T7AuJGSl5BJKplxrKqefhQVhcpBgA3UYrb4I1wPHgtpGlBU2o+QKV9ZSeIvte" "\n"
            "XLkBDQRTptEoAQgA2YqsTj9JniJkrr1x6g59io1GkP9z0JElzRl4kvG7WUkrhSPc" "\n"
            "XkoLngcCur9lpxET2Wp7ou43zcKuiwsDxnsWwSvWfmg15N4BzYS6ulP7PSIpQlLb" "\n"
            "srqFTR/iX0c7asgUE5Jpe8YEnThl2aAPkJlx47GQN1jhGxOkZhz3kIC+rG2d25ET" "\n"
            "36eI0vw4oHO40nF9DihyHzfcD3tuuaOJ+AUPrDh7o97a8yIQmVU031GImC1DHQ9t" "\n"
            "k9qkixCuejN1cfi7zqWclnd4nu3C/PJXLz0qzprhK0gXqgjZVBpCPQ5g/WV/Myw/" "\n"
            "5H7vJC5WcV0lQilxtjgaHmpSu65XTaAHf4OlNQARAQABiQEfBBgBAgAJBQJTptEo" "\n"
            "AhsMAAoJENXX2nHDVJYOmusH/0VDpB6353RsZzCj+eoV9mpew8gPo7jdwMGFVW3r" "\n"
            "7ZfwCCE+9hMqQAPU4ewTtpy9SrzynZCG02vycaBhLJwcP1dKtvae1y8B8zh7zo9F" "\n"
            "eLTUewHuyFRpyM5/fj1Dou89AOvDRaiJPaO3RQOmjGG9+D5hDS03CHBXOg/P0gYv" "\n"
            "lc1myZNfRtU5+ezMEWA+tqyjyjj3W6nyobtpVtwgpA/od47/UcdGqSkzkmr+zqqH" "\n"
            "amPMgSaahcvqPw2VFt4fi00ShN9EguwiV2vJes6VvDq1qE5Ap/zWBn/B7xIc70jD" "\n"
            "hHtoB2/2gM/blPn5EPrIht6Kh9njBFYVk+OrV96NpJl08lM=" "\n"
            "=xJuO" "\n"
            "-----END PGP PUBLIC KEY BLOCK-----"
            ;
            
            TEST(public_key) {
                
                std::string in = GPG_PUBKEY_ALICE;
                PGPPublicKey pgp(in);
                
                auto packets = pgp.get_packets();
                VERIFY_ARE_EQUAL(packets.size(), 5);
                
                Packet::Ptr
                p0 = packets[0],
                p1 = packets[1],
                p2 = packets[2],
                p3 = packets[3],
                p4 = packets[4];
                
                VERIFY_ARE_EQUAL(p0->get_tag(), 6);
                VERIFY_ARE_EQUAL(p1->get_tag(), 13);
                VERIFY_ARE_EQUAL(p2->get_tag(), 2);
                VERIFY_ARE_EQUAL(p3->get_tag(), 14);
                VERIFY_ARE_EQUAL(p4->get_tag(), 2);
                
                Tag6::Ptr  pubkey = std::dynamic_pointer_cast<Tag6>(p0);
                Tag13::Ptr userid = std::dynamic_pointer_cast<Tag13>(p1);
                Tag14::Ptr subkey = std::dynamic_pointer_cast<Tag14>(p3);
                Tag2::Ptr  pubsig = std::dynamic_pointer_cast<Tag2>(p2),
                subsig = std::dynamic_pointer_cast<Tag2>(p4);
                
                VERIFY_ARE_EQUAL(pubkey->get_version(), 4);
                VERIFY_ARE_EQUAL(subkey->get_version(), 4);
                VERIFY_ARE_EQUAL(pubsig->get_version(), 4);
                VERIFY_ARE_EQUAL(subsig->get_version(), 4);
                VERIFY_ARE_EQUAL(userid->get_version(), 0);  // undefined
                
                VERIFY_ARE_EQUAL(pubkey->get_size(), 269);
                VERIFY_ARE_EQUAL(userid->get_size(), 36);
                VERIFY_ARE_EQUAL(pubsig->get_size(), 312);
                VERIFY_ARE_EQUAL(subkey->get_size(), 269);
                VERIFY_ARE_EQUAL(subsig->get_size(), 287);
                
                time_t gen_time = get_utc(2014, 6, 22, 12, 50, 48);
                
                // pubkey
                {
                    VERIFY_ARE_EQUAL(pubkey->get_time(), gen_time); // 2014-06-22T12:50:48 UTC
                    VERIFY_ARE_EQUAL(pubkey->get_pka(), 1);             // RSA
                    auto mpi = pubkey->get_mpi();
                    auto n = mpi[0], e = mpi[1];
                    VERIFY_ARE_EQUAL(bitsize(n), 2048);  // 2048-bit
                    auto strHex_n = mpitohex(n);
                    std::transform(strHex_n.begin(), strHex_n.end(), strHex_n.begin(), ::tolower);
                    VERIFY_ARE_EQUAL(strHex_n, "bc047e94d471f3ccbd525d6a6f8e17f7b1f00527c722c3913ce787fbd0090e3af8be7e59410f63b3983a9507b761045c11510e62f5a8cfbcdc180976a4c225737b8e06d8531f38c6eaa996954d5521a6763231f07c2b43605d052abdf39d6c668ac94bc89f543052d050530c70c48a49a970867c00178f9076dd0e151d254632767b2926e9baa22c6d0c213f1f45de74991396d7e8d10508cf679139410ab311b1279dd3c0d37facca54d523cd14a3df488eb8f592c5a19bcfede67c8170815c588adf39d188197da40492aac5b183c303f6ef23b0b5e48ff73b2d806afb0fb4f16ba32769249d3a7ca0ef0b9b3d57852dc9a979b6d56f3dc170e28dcb2e536d");
                    VERIFY_ARE_EQUAL(bitsize(e), 17);    // 17-bit
                    VERIFY_ARE_EQUAL(mpitohex(e),"010001");
                }

                // userid
                {
                    VERIFY_ARE_EQUAL(userid->raw(), "alice (test key) <alice@example.com>");
                }

                // pubsig
                {
                    VERIFY_ARE_EQUAL(pubsig->get_type(), 0x13); // Positive certification of a User ID and Public-Key packet
                    VERIFY_ARE_EQUAL(pubsig->get_pka(), 1);     // RSA
                    VERIFY_ARE_EQUAL(pubsig->get_hash(), 2);    // SHA1
                    VERIFY_ARE_EQUAL(pubsig->get_left16(), "\x04\x5e");
                    auto mpi = pubsig->get_mpi();
                    VERIFY_ARE_EQUAL(mpi.size(), 1);
                    VERIFY_ARE_EQUAL(bitsize(mpi[0]), 2047); // 2047-bit
                    
                    auto strHex_mpi_0 = mpitohex(mpi[0]);
                    std::transform(strHex_mpi_0.begin(), strHex_mpi_0.end(), strHex_mpi_0.begin(), ::tolower);
                    VERIFY_ARE_EQUAL(strHex_mpi_0, "688a18a258f866cf50f1c938dc15b11298da0bfbd680241f52545af5023722858cdfb579da22e66dae36dff9a817f797192e95b7074bab49381acb837f1216d4e8e3c2de2fb5547a515b5236823bcb4b3bca1a68455fa984c4dc21b1a5af2308aea580c0ae2ca3f5db343beaa559524702d09e40d1923314ef0f15646acec91b9c6d9cba9d9b87fa78626a522ae1520f0aed361df00f8191a9ecb1fb12732e9f6e5e1c4bece397e4dcfbacd41918882c2dfa75b98b54587f0cd61195bdce41b690329a746c6e37b7e2ef9b06206bf280ff93ec0b891929790492a9971acaa9e7e141585ca41800dd462b6f8235c0f1e0b691a5054da8f90295f5949e22fb5e5c");
                    // pubsig/hashed
                    auto pubsub = pubsig->get_hashed_subpackets();
                    VERIFY_ARE_EQUAL(pubsub.size(), 7);
                    Subpacket::Ptr
                    ps0 = pubsub[0],
                    ps1 = pubsub[1],
                    ps2 = pubsub[2],
                    ps3 = pubsub[3],
                    ps4 = pubsub[4],
                    ps5 = pubsub[5],
                    ps6 = pubsub[6];
                    
                    VERIFY_ARE_EQUAL(ps0->get_type(), 2);
                    VERIFY_ARE_EQUAL(ps1->get_type(), 27);
                    VERIFY_ARE_EQUAL(ps2->get_type(), 11);
                    VERIFY_ARE_EQUAL(ps3->get_type(), 21);
                    VERIFY_ARE_EQUAL(ps4->get_type(), 22);
                    VERIFY_ARE_EQUAL(ps5->get_type(), 30);
                    VERIFY_ARE_EQUAL(ps6->get_type(), 23);
                    Tag2Sub2::Ptr  pubsub2  = std::dynamic_pointer_cast<Tag2Sub2>(ps0);
                    Tag2Sub27::Ptr pubsub27 = std::dynamic_pointer_cast<Tag2Sub27>(ps1);
                    Tag2Sub11::Ptr pubsub11 = std::dynamic_pointer_cast<Tag2Sub11>(ps2);
                    Tag2Sub21::Ptr pubsub21 = std::dynamic_pointer_cast<Tag2Sub21>(ps3);
                    Tag2Sub22::Ptr pubsub22 = std::dynamic_pointer_cast<Tag2Sub22>(ps4);
                    Tag2Sub30::Ptr pubsub30 = std::dynamic_pointer_cast<Tag2Sub30>(ps5);
                    Tag2Sub23::Ptr pubsub23 = std::dynamic_pointer_cast<Tag2Sub23>(ps6);
                    
                    // pubsig/sub2
                    {
                        VERIFY_ARE_EQUAL(pubsub2->get_time(), gen_time); // 2014-06-22T12:50:48 UTC
                    }
                    // pubsig/sub27
                    {
                        VERIFY_ARE_EQUAL(pubsub27->get_flags(), (1 | 2));
                    }
                    // pubsig/sub11
                    {
                        std::string psa = pubsub11->get_psa();
                        VERIFY_ARE_EQUAL(psa.size(), 5);
                        VERIFY_ARE_NOT_EQUAL(psa.find(9), std::string::npos); // AES 256-bit
                        VERIFY_ARE_NOT_EQUAL(psa.find(8), std::string::npos); // AES 192-bit
                        VERIFY_ARE_NOT_EQUAL(psa.find(7), std::string::npos); // AES 128-bit
                        VERIFY_ARE_NOT_EQUAL(psa.find(3), std::string::npos); // CAST5
                        VERIFY_ARE_NOT_EQUAL(psa.find(2), std::string::npos); // TDES
                    }
                    // pubsig/sub21
                    {
                        std::string pha = pubsub21->get_pha();
                        VERIFY_ARE_EQUAL(pha.size(), 5);
                        VERIFY_ARE_NOT_EQUAL(pha.find(8), std::string::npos);  // SHA256
                        VERIFY_ARE_NOT_EQUAL(pha.find(2), std::string::npos);  // SHA1
                        VERIFY_ARE_NOT_EQUAL(pha.find(9), std::string::npos);  // SHA384
                        VERIFY_ARE_NOT_EQUAL(pha.find(10), std::string::npos); // SHA512
                        VERIFY_ARE_NOT_EQUAL(pha.find(11), std::string::npos); // SHA224
                    }
                    // pubsig/sub22
                    {
                        std::string pca = pubsub22->get_pca();
                        VERIFY_ARE_EQUAL(pca.size(), 3);
                        VERIFY_ARE_NOT_EQUAL(pca.find(2), std::string::npos); // ZLIB
                        VERIFY_ARE_NOT_EQUAL(pca.find(3), std::string::npos); // BZip2
                        VERIFY_ARE_NOT_EQUAL(pca.find(1), std::string::npos); // ZIP
                    }
                    // pubsig/sub30
                    {
                        VERIFY_ARE_EQUAL(pubsub30->get_flags(), 1); // Modification Detection
                    }
                    // pubsig/sub23
                    {
                        VERIFY_ARE_EQUAL(pubsub23->get_flags(), static_cast<char>(0x80)); // No-modify
                    }
                    
                    // pubsig/unhashed
                    auto uh_pubsub = pubsig->get_unhashed_subpackets();
                    VERIFY_ARE_EQUAL(uh_pubsub.size(), 1);
                    Subpacket::Ptr uhps0 = uh_pubsub[0];
                    VERIFY_ARE_EQUAL(uhps0->get_type(), 16);
                    Tag2Sub16::Ptr pubsub16 = std::dynamic_pointer_cast<Tag2Sub16>(uhps0);
                    // pubsig/sub16
                    {
                        VERIFY_ARE_EQUAL(pubsub16->get_keyid(), "\xd5\xd7\xda\x71\xc3\x54\x96\x0e");
                    }
                }

                // subkey
                {
                    VERIFY_ARE_EQUAL(subkey->get_time(), gen_time); // 2014-06-22T12:50:48 UTC
                    VERIFY_ARE_EQUAL(subkey->get_pka(), 1);             // RSA
                    auto mpi = subkey->get_mpi();
                    auto n = mpi[0], e = mpi[1];
                    VERIFY_ARE_EQUAL(bitsize(n), 2048);  // 2048-bit
                    auto strHex_n = mpitohex(n);
                    std::transform(strHex_n.begin(), strHex_n.end(), strHex_n.begin(), ::tolower);
                    VERIFY_ARE_EQUAL(strHex_n, "d98aac4e3f499e2264aebd71ea0e7d8a8d4690ff73d09125cd197892f1bb59492b8523dc5e4a0b9e0702babf65a71113d96a7ba2ee37cdc2ae8b0b03c67b16c12bd67e6835e4de01cd84baba53fb3d22294252dbb2ba854d1fe25f473b6ac8141392697bc6049d3865d9a00f909971e3b1903758e11b13a4661cf79080beac6d9ddb9113dfa788d2fc38a073b8d2717d0e28721f37dc0f7b6eb9a389f8050fac387ba3dedaf32210995534df5188982d431d0f6d93daa48b10ae7a337571f8bbcea59c9677789eedc2fcf2572f3d2ace9ae12b4817aa08d9541a423d0e60fd657f332c3fe47eef242e56715d25422971b6381a1e6a52bbae574da0077f83a535");
                    VERIFY_ARE_EQUAL(bitsize(e), 17);    // 17-bit
                    VERIFY_ARE_EQUAL(mpitohex(e), "010001");
                }
                
                // subsig
                {
                    VERIFY_ARE_EQUAL(subsig->get_type(), 0x18); // Subkey Binding Signature
                    VERIFY_ARE_EQUAL(subsig->get_pka(), 1);     // RSA
                    VERIFY_ARE_EQUAL(subsig->get_hash(), 2);    // SHA1
                    VERIFY_ARE_EQUAL(subsig->get_left16(), "\x9a\xeb");
                    VERIFY_ARE_EQUAL(bitsize(subsig->get_mpi()[0]), 2047); // 2047-bit
                    
                    // subsig/hashed
                    auto subsub = subsig->get_hashed_subpackets();
                    VERIFY_ARE_EQUAL(subsub.size(), 2);
                    Subpacket::Ptr
                    ss0 = subsub[0],
                    ss1 = subsub[1];
                    
                    VERIFY_ARE_EQUAL(ss0->get_type(), 2);
                    VERIFY_ARE_EQUAL(ss1->get_type(), 27);
                    
                    Tag2Sub2::Ptr  subsub2  = std::dynamic_pointer_cast<Tag2Sub2>(ss0);
                    Tag2Sub27::Ptr subsub27 = std::dynamic_pointer_cast<Tag2Sub27>(ss1);
                    // subsig/sub2
                    {
                        VERIFY_ARE_EQUAL(subsub2->get_time(), gen_time); // 2014-06-22T12:50:48 UTC
                    }
                    // subsig/sub27
                    {
                        VERIFY_ARE_EQUAL(subsub27->get_flags(), (4 | 8));
                    }
                    
                    // subsig/unhashed
                    auto uh_subsub = subsig->get_unhashed_subpackets();
                    VERIFY_ARE_EQUAL(uh_subsub.size(), 1);
                    Subpacket::Ptr uhss0 = uh_subsub[0];
                    VERIFY_ARE_EQUAL(uhss0->get_type(), 16);
                    Tag2Sub16::Ptr subsub16 = std::dynamic_pointer_cast<Tag2Sub16>(uhss0);
                    // subsig/sub16
                    {
                        VERIFY_ARE_EQUAL(subsub16->get_keyid(), "\xd5\xd7\xda\x71\xc3\x54\x96\x0e");
                    }
                }
            }
        }
    }
}
