//
//  opengpg_symmetric_encrypt_test.cpp
//  OpenPGP
//
//  Created by Yanfeng Zhang on 11/1/16.
//  Copyright © 2016 Yanfeng Zhang. All rights reserved.
//

#import "utils_test.h"

#include <openpgp/PGPKey.h>
#include <openpgp/encrypt.h>
#include <openpgp/decrypt.h>

#include <openpgp/private_key.h>
#include <openpgp/pgptime.h>
#include <algorithm>
#include <string>

using namespace ProtonMail::pgp;

namespace tests {
    namespace open_pgp_tests {
        
        SUITE(gpg_symmetric_encrypt)
        {
            const std::string GPG_PRIKEY_ALICE =
            "-----BEGIN PGP PRIVATE KEY BLOCK-----" "\n"
            "Version: GnuPG v1" "\n"
            "" "\n"
            "lQO+BFOm0SgBCAC8BH6U1HHzzL1SXWpvjhf3sfAFJ8ciw5E854f70AkOOvi+fllB" "\n"
            "D2OzmDqVB7dhBFwRUQ5i9ajPvNwYCXakwiVze44G2FMfOMbqqZaVTVUhpnYyMfB8" "\n"
            "K0NgXQUqvfOdbGaKyUvIn1QwUtBQUwxwxIpJqXCGfAAXj5B23Q4VHSVGMnZ7KSbp" "\n"
            "uqIsbQwhPx9F3nSZE5bX6NEFCM9nkTlBCrMRsSed08DTf6zKVNUjzRSj30iOuPWS" "\n"
            "xaGbz+3mfIFwgVxYit850YgZfaQEkqrFsYPDA/bvI7C15I/3Oy2AavsPtPFroydp" "\n"
            "JJ06fKDvC5s9V4Utyal5ttVvPcFw4o3LLlNtABEBAAH+AwMCWDAp11UNSahgR9sK" "\n"
            "NxF2s11cwBsyMu0saVLcwD1Fu5kobQPYkEIkhotkDjt/wS6aXTf4sDr0yZK7HH4z" "\n"
            "BmXBH7CT6EPT6RVd8BZOd4Clul6wv9WDC7M4fjWnVwrbT90Wb/ID6LP7RW+foaHq" "\n"
            "WYZkfA1173/40W3DOuD63p7nImw8acDF03r85ta5tY1DkQ+WJH1Kp6HeiVEMP6QB" "\n"
            "PJYS46ptYL4bk1jpj5PJySRJkdMxy5AobWw1SkXXVz+D4k9+pHX5XJeGBpStGVnA" "\n"
            "Q2lZH8CLdhoF9ILZ/dDi9YcfpwFJAxchPpMWCA6sU/UgwgpIF1WAjTWWuEkvwLq5" "\n"
            "uo+zfQxM2jR0t3bF4e7SU2Jw8trggaVKpDabTldQXVywizuMz1BuNwGZaGYECN7G" "\n"
            "+v+jeM+c0MHFzR2U+KLnGxRM0kccMBxtDKK/KiTGiJzcn/jZ57EO/cAhIjivYvUX" "\n"
            "KWGZ6IhbMrGiOKOwJiq9Yp9nq/WtYwzkFkquW6V+cfp533QjfqZ1beIsEtss+9Ap" "\n"
            "kZuLcKFkNhPsAAhTazlIK/Nqdy6bQLUHaPmEMVtj3N4Pjaz6XvVXSSzFX8OvM6AZ" "\n"
            "/A2MLibbM4d52ZUjQZE8tdrmzl8fgHiHGPyUcxFg6Cd/2lCz1xia15e8OBmgcWRb" "\n"
            "3QbugyedaJ+0qTaykg5sGh4Txa8idD40Ij+VG9RwpC088a/zDb7R6GnVTih7+adE" "\n"
            "TDxfITWs/p0yx1Ak77bJPsdEQK/r5YyQqEFOp5WJb5VLyN4BEw5xi8eQ/Ysrqc9h" "\n"
            "tUz8jvYT+dQs0J3Eu+JzVXipJR3n7kMCzeC1sXcNClKsZI0OkfhuVSpQttOq2mzy" "\n"
            "vQzISGKD+65kvQc+z9v11BcAu3wctyCMotF9M0K4emuo1rIvtyOpnSTzwgfkVGYn" "\n"
            "QbQkYWxpY2UgKHRlc3Qga2V5KSA8YWxpY2VAZXhhbXBsZS5jb20+iQE4BBMBAgAi" "\n"
            "BQJTptEoAhsDBgsJCAcDAgYVCAIJCgsEFgIDAQIeAQIXgAAKCRDV19pxw1SWDgRe" "\n"
            "B/9oihiiWPhmz1DxyTjcFbESmNoL+9aAJB9SVFr1AjcihYzftXnaIuZtrjbf+agX" "\n"
            "95cZLpW3B0urSTgay4N/EhbU6OPC3i+1VHpRW1I2gjvLSzvKGmhFX6mExNwhsaWv" "\n"
            "IwiupYDAriyj9ds0O+qlWVJHAtCeQNGSMxTvDxVkas7JG5xtnLqdm4f6eGJqUirh" "\n"
            "Ug8K7TYd8A+BkanssfsScy6fbl4cS+zjl+Tc+6zUGRiILC36dbmLVFh/DNYRlb3O" "\n"
            "QbaQMpp0bG43t+LvmwYga/KA/5PsC4kZKXkEkqmXGsqp5+FBWFykGADdRitvgjXA" "\n"
            "8eC2kaUFTaj5ApX1lJ4i+15cnQO+BFOm0SgBCADZiqxOP0meImSuvXHqDn2KjUaQ" "\n"
            "/3PQkSXNGXiS8btZSSuFI9xeSgueBwK6v2WnERPZanui7jfNwq6LCwPGexbBK9Z+" "\n"
            "aDXk3gHNhLq6U/s9IilCUtuyuoVNH+JfRztqyBQTkml7xgSdOGXZoA+QmXHjsZA3" "\n"
            "WOEbE6RmHPeQgL6sbZ3bkRPfp4jS/Digc7jScX0OKHIfN9wPe265o4n4BQ+sOHuj" "\n"
            "3trzIhCZVTTfUYiYLUMdD22T2qSLEK56M3Vx+LvOpZyWd3ie7cL88lcvPSrOmuEr" "\n"
            "SBeqCNlUGkI9DmD9ZX8zLD/kfu8kLlZxXSVCKXG2OBoealK7rldNoAd/g6U1ABEB" "\n"
            "AAH+AwMCWDAp11UNSahgIgHkKsaBTTV8y1UYQNlT6BELtZZXShxeeaFRBM9PFy0f" "\n"
            "bMx953y3UYBl+Wr1/BZQG3dWYv8+7F4kSI63UsvScOIkdoePbAaR7eDNxrHAq1TP" "\n"
            "bEGY7uETAGiAh7B441JCNOgMiKjgEivt8fZ693hGyn6Hhfm6wwRMjAXehfR19DN7" "\n"
            "XcuSCXKXg97v8PQOzcBdS2JmAme1dzblnAZu85eUeVgr9rBXh6vFEQGngaTXqCI4" "\n"
            "zaQz/RjxVnPP5elpquG7y1z3B5YTYFsyOOyYCT09xsCTC7Gmk7nwW+ptl4tbnxvt" "\n"
            "uVkMVJyZTp/O0K07bN4+p8YRRc45XlMVFtyCCqKlqdMn4PYcvEWm2WqjKCOnRwQs" "\n"
            "bUTdz0KwvC7jWtikSz1+oWCFIFejybOusd1f9F4NqkfzkH0zaVb/96R3iqX2Epdq" "\n"
            "3ReRscaYgQ2Fd4mJqY/7iGP5u1eoyo9t28zUx9ClDXd3k0mWkijHc5LEYIuOveHu" "\n"
            "KYfMoirBt18Lx8saJ23B3Rt9nMAVfyoy2h0PSdYqvfGVz3GCWVxmisdH6zg91SQp" "\n"
            "WEQFpzmYR+FmXk0m+JN2EJTFBNRLxy9DlAEqSYhlLtPqNuVfdRvOlxOGh9x48w0P" "\n"
            "fzGfMV1bxn6GVHd10lrDk1/iZTw3tcBpMddIV57eyRNUbsw3VYY2wdDHbQSvD2x4" "\n"
            "I/Y2MSLPF+FteP9GRZBaXG/+acloOSmwKYoaEZbGKSdeSZttsQqfb44VyZvMi/3w" "\n"
            "hOsFvhzygCTFwfFrrPceCGH+VgiajK7kYoDDTr3L0b9v/SPgd0RLt/rNhCyFFxgt" "\n"
            "qX90SOsMxBGaLcigydk4j6caGTSkZyA5d/yy5W5hsbFprj2W4YG4pBi7r8xowqt9" "\n"
            "M1Cubf5H2jYxY2npvo2osFXXTYkBHwQYAQIACQUCU6bRKAIbDAAKCRDV19pxw1SW" "\n"
            "DprrB/9FQ6Qet+d0bGcwo/nqFfZqXsPID6O43cDBhVVt6+2X8AghPvYTKkAD1OHs" "\n"
            "E7acvUq88p2QhtNr8nGgYSycHD9XSrb2ntcvAfM4e86PRXi01HsB7shUacjOf349" "\n"
            "Q6LvPQDrw0WoiT2jt0UDpoxhvfg+YQ0tNwhwVzoPz9IGL5XNZsmTX0bVOfnszBFg" "\n"
            "Praso8o491up8qG7aVbcIKQP6HeO/1HHRqkpM5Jq/s6qh2pjzIEmmoXL6j8NlRbe" "\n"
            "H4tNEoTfRILsIldryXrOlbw6tahOQKf81gZ/we8SHO9Iw4R7aAdv9oDP25T5+RD6" "\n"
            "yIbeiofZ4wRWFZPjq1fejaSZdPJT" "\n"
            "=SrxY" "\n"
            "-----END PGP PRIVATE KEY BLOCK-----"
            ;
            
            const std::string GPG_SYMMETRIC_ENCRYPT_TO_ALICE =
            "-----BEGIN PGP MESSAGE-----" "\n"
            "Version: GnuPG v1" "\n"
            "" "\n"
            "hQEMA58P9A/ScGHhAQf+KJgvZ0a4rLKIW063wHpcLf6ukOnEdlUNkBB3GZFTQPkG" "\n"
            "yjAW+81uCFRkjmEuWgTIDVLoGE9viQkgdpsHQgXFs6goaJimOfdKck5OUpcJgS/r" "\n"
            "Jcd9nzRJU6QnYM2/SK3LuBydgp6xAQosj2vCM0oS03A9uaKui70rOy7tqAWIPBER" "\n"
            "SJ0jq8LHrFnVU1xjOhFeqq/DQzyuejYWe04kfwcvyWhVVGJKOED1KoEY88DYs0EG" "\n"
            "Oqi+TvF/i1CR5gNEhrT8uzTyqGWIRgC3hhRo6PmZJAyIgYxGqDo/dT3OWTCiBy4x" "\n"
            "AZpPEZMUlOn2vtrLvWXUNqzzFPNqMJLK5bZ7M+NqN4wuBAMDAl8EHF1mNsiVYGq+" "\n"
            "lTvld4dwexLgr3oIAPM4nLt/3QWDegipHxPXZUpcWtJtAZBe42dZp2ykgM6otpvd" "\n"
            "Xs+p+n4WWlo7GgEmD0uDmZovp1JnKqxv7K7xNlQq2l/989eDlUWJBGxDhF4uPFZ+" "\n"
            "gBY8dv7mNIrYKbJ9BC7xEpGkAgABTESjTtT/JFFUg/EiAw5BY6au6K+VWf9hzA==" "\n"
            "=Ve5X" "\n"
            "-----END PGP MESSAGE-----"
            ;
            
            const std::string PASSPHRASE = "test";
            
            TEST(symmetric) {
                std::string in = GPG_SYMMETRIC_ENCRYPT_TO_ALICE;
                PGPMessage pgp(in);
                
                auto packets = pgp.get_packets();
                VERIFY_ARE_EQUAL(packets.size(), 3);
                
                Packet::Ptr
                p0 = packets[0],
                p1 = packets[1],
                p2 = packets[2];
                VERIFY_ARE_EQUAL(p0->get_tag(), 1);
                VERIFY_ARE_EQUAL(p1->get_tag(), 3);
                VERIFY_ARE_EQUAL(p2->get_tag(), 18);
                
                Tag1::Ptr tag1 = std::dynamic_pointer_cast<Tag1>(p0);
                Tag3::Ptr tag3 = std::dynamic_pointer_cast<Tag3>(p1);
                Tag18::Ptr tag18 = std::dynamic_pointer_cast<Tag18>(p2);
                
                VERIFY_ARE_EQUAL(tag1->get_version(), 3);
                VERIFY_ARE_EQUAL(tag3->get_version(), 4);
                VERIFY_ARE_EQUAL(tag18->get_version(), 1);
                
                VERIFY_ARE_EQUAL(tag1->get_size(), 268);
                VERIFY_ARE_EQUAL(tag3->get_size(), 46);
                VERIFY_ARE_EQUAL(tag18->get_size(), 109);
                
                // tag1
                {
                    VERIFY_ARE_EQUAL(tag1->get_keyid(), "\x9f\x0f\xf4\x0f\xd2\x70\x61\xe1");
                    VERIFY_ARE_EQUAL(tag1->get_pka(), 1); // RSA
                    auto mpi = tag1->get_mpi();
                    VERIFY_ARE_EQUAL(mpi.size(), 1);
                    
                    auto key = mpi[0];
                    VERIFY_ARE_EQUAL(bitsize(key), 2046);
                    auto strHex_key = mpitohex(key);
                    std::transform(strHex_key.begin(), strHex_key.end(), strHex_key.begin(), ::tolower);
                    VERIFY_ARE_EQUAL(strHex_key, "28982f6746b8acb2885b4eb7c07a5c2dfeae90e9c476550d90107719915340f906ca3016fbcd6e0854648e612e5a04c80d52e8184f6f890920769b074205c5b3a8286898a639f74a724e4e529709812feb25c77d9f344953a42760cdbf48adcbb81c9d829eb1010a2c8f6bc2334a12d3703db9a2ae8bbd2b3b2eeda805883c1111489d23abc2c7ac59d5535c633a115eaaafc3433cae7a36167b4e247f072fc9685554624a3840f52a8118f3c0d8b341063aa8be4ef17f8b5091e6034486b4fcbb34f2a865884600b7861468e8f999240c88818c46a83a3f753dce5930a2072e31019a4f11931494e9f6bedacbbd65d436acf314f36a3092cae5b67b33e36a37");
                }
                // tag3
                {
                    VERIFY_ARE_EQUAL(tag3->get_sym(), 3);  // CAST5
                    auto s2k = tag3->get_s2k();
                    VERIFY_ARE_EQUAL(s2k->get_type(), 3);
                    auto s2k3 = std::dynamic_pointer_cast<S2K3>(s2k);
                    VERIFY_ARE_EQUAL(s2k3->get_hash(), 2);  // SHA1
                    VERIFY_ARE_EQUAL(s2k3->get_salt(), "\x5f\x04\x1c\x5d\x66\x36\xc8\x95");
                    VERIFY_ARE_EQUAL(s2k3->get_count(), 96);
                    // TODO
                    auto esk = tag3->get_esk();
                }
                // tag18
                {
                    std::string in_pri = GPG_PRIKEY_ALICE;
                    PGPSecretKey pgp_pri(in_pri);
                    std::string message = decrypt_pka(pgp_pri, pgp, PASSPHRASE, false);
                    VERIFY_ARE_EQUAL(message, "The magic words are squeamish ossifrage\n");
                }
            }


        }
    }
}
