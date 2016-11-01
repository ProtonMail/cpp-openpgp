//
//  openpgp_pka_encrypt_anonymous_test.cpp
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

using namespace pm::pgp;

namespace tests {
    namespace open_pgp_tests {
        
        SUITE(pgp_pka_encrypt_anonymous)
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

            const std::string GPG_PKA_ENCRYPT_TO_ALICE =
            "-----BEGIN PGP MESSAGE-----" "\n"
            "Version: GnuPG v1" "\n"
            "" "\n"
            "hQEMA58P9A/ScGHhAQf/UwMe4vS+PqKAjU/HJY91plKvIzrVvgzZEOYV7SZmkeis" "\n"
            "WEs5YLCcbF1lyMaNTKpGxf4XLLpwQqryPaGn98phqtKAFfiJNezZH4UB8/n4UwKl" "\n"
            "B8hiqtLZt+2XW9VwSq61eg7rwsOTMV2+biew4/M0fMxnfxlS36mtK7xpgDhrkIZy" "\n"
            "locRPKyYQva/gCrrN2kydwhE+Olr6mg74UVX9XumtzXx+cXy5aVqy/gQ96rMnZZX" "\n"
            "vmWfcHrsappqo2Fqay4QqNyUzMvKOc+A4dwyBYA6Dr5mFIcb5KUhF7CjmwvGeRnD" "\n"
            "otvPu2ygsh85zY9TdPOt8q3Jf3aX9mP/qYXEfn3hb9JtAQdDbYqyUNHoEWUarEMi" "\n"
            "3Ea9nK0QblfG2Oz7RwWdBzDpGgZMfUI4E9N+JgewnhfhhS38lsDXSQvKukCSsm6Y" "\n"
            "lBLM0RAwqxG+JGB2CkbXDeInqAelHZuSa8ZVO9jrjGjyB3fvMvZxLKsxPiBRVg==" "\n"
            "=mCKG" "\n"
            "-----END PGP MESSAGE-----"
            ;
            
            const std::string PASSPHRASE = "test";
            
            TEST(anonymous) {
                
                std::string in = GPG_PKA_ENCRYPT_TO_ALICE;
                PGPMessage pgp(in);
                
                auto packets = pgp.get_packets();
                VERIFY_ARE_EQUAL(packets.size(), 2);
                
                Packet::Ptr
                p0 = packets[0],
                p1 = packets[1];
                VERIFY_ARE_EQUAL(p0->get_tag(), 1);
                VERIFY_ARE_EQUAL(p1->get_tag(), 18);
                
                Tag1::Ptr  tag1  = std::dynamic_pointer_cast<Tag1>(p0);
                Tag18::Ptr tag18 = std::dynamic_pointer_cast<Tag18>(p1);
                
                VERIFY_ARE_EQUAL(tag1->get_version(), 3);
                VERIFY_ARE_EQUAL(tag18->get_version(), 1);
                
                VERIFY_ARE_EQUAL(tag1->get_size(), 268);
                VERIFY_ARE_EQUAL(tag18->get_size(), 109);
                
                // tag1
                {
                    VERIFY_ARE_EQUAL(tag1->get_keyid(), "\x9f\x0f\xf4\x0f\xd2\x70\x61\xe1");
                    VERIFY_ARE_EQUAL(tag1->get_pka(), 1); // RSA
                    auto mpi = tag1->get_mpi();
                    VERIFY_ARE_EQUAL(mpi.size(), 1);
                    
                    auto key = mpi[0];
                    VERIFY_ARE_EQUAL(bitsize(key), 2047);
                    auto strHex_key = mpitohex(key);
                    std::transform(strHex_key.begin(), strHex_key.end(), strHex_key.begin(), ::tolower);
                    VERIFY_ARE_EQUAL(strHex_key, "53031ee2f4be3ea2808d4fc7258f75a652af233ad5be0cd910e615ed266691e8ac584b3960b09c6c5d65c8c68d4caa46c5fe172cba7042aaf23da1a7f7ca61aad28015f88935ecd91f8501f3f9f85302a507c862aad2d9b7ed975bd5704aaeb57a0eebc2c393315dbe6e27b0e3f3347ccc677f1952dfa9ad2bbc6980386b9086729687113cac9842f6bf802aeb376932770844f8e96bea683be14557f57ba6b735f1f9c5f2e5a56acbf810f7aacc9d9657be659f707aec6a9a6aa3616a6b2e10a8dc94cccbca39cf80e1dc3205803a0ebe6614871be4a52117b0a39b0bc67919c3a2dbcfbb6ca0b21f39cd8f5374f3adf2adc97f7697f663ffa985c47e7de16f");
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
