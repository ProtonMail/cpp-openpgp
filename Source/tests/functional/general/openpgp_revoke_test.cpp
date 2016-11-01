//
//  openpgp_revoke_test.cpp
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
        
        SUITE(pgp_revoke)
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

            const std::string GPG_REVOKE3_ALICE =
            "-----BEGIN PGP PUBLIC KEY BLOCK-----" "\n"
            "Version: GnuPG v1" "\n"
            "Comment: A revocation certificate should follow" "\n"
            "" "\n"
            "iQEfBCABAgAJBQJTptQ1Ah0DAAoJENXX2nHDVJYOz7kH/RM+2sD6mxh+BfjOja3o" "\n"
            "LzHTomYZD5Ebea7Ql0lSYBs+/+7YoaHcqfdCKSowi+jKxD/yyAHvkBwGxsalIHNt" "\n"
            "/EsCyPkq96maA/idPWLfmETLYnHkCSAKf7bS4p/j5yvlMFAEo5dlv38Cvm3N5H5E" "\n"
            "Ex5VKdOXWSQyp03sxtts1ieEjxU1phZhA+ahf5klb+rWaP3rN6csPwvAxHldsyTa" "\n"
            "E404w3AR1bBx7M53+4TaRk6qanWy4atv+mZTsFORSeX5LPsDidhD8myrzEHw1iOW" "\n"
            "ZzSyp/oRBDCynxp4VK5a/7+eIou7RAFSJCVCWFx6OLlaVBqNmvzP/WwiewoRvNYL" "\n"
            "K8c=" "\n"
            "=d89H" "\n"
            "-----END PGP PUBLIC KEY BLOCK-----"
            ;
            
            TEST(revoke) {
                
                std::string in = GPG_REVOKE3_ALICE;
                PGPPublicKey pgp(in);
                
                auto packets = pgp.get_packets();
                VERIFY_ARE_EQUAL(packets.size(), 1);
                
                Packet::Ptr p0 = packets[0];
                
                VERIFY_ARE_EQUAL(p0->get_tag(), 2);
                Tag2::Ptr revsig = std::dynamic_pointer_cast<Tag2>(p0);
                
                VERIFY_ARE_EQUAL(revsig->get_version(), 4);
                VERIFY_ARE_EQUAL(revsig->get_size(), 287);
                
                VERIFY_ARE_EQUAL(revsig->get_type(), 0x20);  // Key revocation signature
                VERIFY_ARE_EQUAL(revsig->get_pka(), 1);      // RSA
                VERIFY_ARE_EQUAL(revsig->get_hash(), 2);     // SHA1
                VERIFY_ARE_EQUAL(revsig->get_left16(), "\xcf\xb9");
                
                auto mpi = revsig->get_mpi();
                VERIFY_ARE_EQUAL(mpi.size(), 1);
                
                auto sign = mpi[0];
                VERIFY_ARE_EQUAL(bitsize(sign), 2045);
                VERIFY_ARE_EQUAL(mpitohex(sign), "133edac0fa9b187e05f8ce8dade82f31d3a266190f911b79aed0974952601b3effeed8a1a1dca9f742292a308be8cac43ff2c801ef901c06c6c6a520736dfc4b02c8f92af7a99a03f89d3d62df9844cb6271e409200a7fb6d2e29fe3e72be5305004a39765bf7f02be6dcde47e44131e5529d397592432a74decc6db6cd627848f1535a6166103e6a17f99256fead668fdeb37a72c3f0bc0c4795db324da138d38c37011d5b071ecce77fb84da464eaa6a75b2e1ab6ffa6653b0539149e5f92cfb0389d843f26cabcc41f0d623966734b2a7fa110430b29f1a7854ae5affbf9e228bbb440152242542585c7a38b95a541a8d9afccffd6c227b0a11bcd60b2bc7");
                
                // hashed
                {
                    auto hashed = revsig->get_hashed_subpackets();
                    VERIFY_ARE_EQUAL(hashed.size(), 2);
                    
                    Subpacket::Ptr
                    s0 = hashed[0],
                    s1 = hashed[1];
                    
                    VERIFY_ARE_EQUAL(s0->get_type(), 2);
                    VERIFY_ARE_EQUAL(s1->get_type(), 29);
                    
                    Tag2Sub2::Ptr sub2   = std::dynamic_pointer_cast<Tag2Sub2>(s0);
                    Tag2Sub29::Ptr sub29 = std::dynamic_pointer_cast<Tag2Sub29>(s1);
                    
                    // sub2
                    {
                        VERIFY_ARE_EQUAL(sub2->get_time(), get_utc(2014, 6, 22, 13, 03, 49));
                    }
                    // sub29
                    {
                        VERIFY_ARE_EQUAL(sub29->get_code(), 03);  // Key is no longer used
                        VERIFY_ARE_EQUAL(sub29->get_reason(), ""); // (empty string)
                    }
                }
                // unhashed
                {
                    auto unhashed = revsig->get_unhashed_subpackets();
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
