//
//  openpgp_privatekey_test.cpp
//  OpenPGP
//
//  Created by Yanfeng Zhang on 10/31/16.
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
        
        SUITE(pgp_private_key)
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
            
            const std::string GPG_PRIKEY_BOB =
            "-----BEGIN PGP PRIVATE KEY BLOCK-----" "\n"
            "Version: GnuPG v1" "\n"
            "" "\n"
            "lQO+BFOm0k8BCAC1r3JzpCyUjSIMyDm35lOJItSe5hLK7aIHxscs5oxmQiLpR80d" "\n"
            "6pisPWiwA9gMDs700LpE+m/QtR4y17MlNU2S1i1RLlt118SEnwD+g/fTBZrCOmuy" "\n"
            "FWLizoRhtlLcu3ir4j47APfu1I3De5x3t1TeBuSY41rSkxXlZ8G9hlu2xAO6MmCE" "\n"
            "fJpNc/tHt9cTXTMGKapVJK/F9dQZ+T2NgPf0nyr5EIfpx+GckZlx3qFT+SleN/UY" "\n"
            "ETk2LL6ElpwARVmcyDv3J9BuLekA0aQSR9GqmDpQmMFBoXds69pBhWtXu228puop" "\n"
            "8LSwO7ZF6c/flTp8xniRlpIEejk4WchhSYdlABEBAAH+AwMCvNC2kifbXMNgvLwI" "\n"
            "pj6Uzyh4ZY+in+ymNP28auJzvct9J+FHyS9uZPg07fhtjNI3CaTUJptNkI8arVOX" "\n"
            "e348g2CrkLnycin9RlA+JMj7o8hRlo1AdYG9EUK2XyqGZxcg9fwSrs6xNPe2s5YA" "\n"
            "NYX4k5JL0tRh/ob1W8lLrduDPO5t0EZ77S2Y9wiPakBP2Loc3lb3qpKAtZqy45Ui" "\n"
            "IBlBhfSBtH27uv9E5SjrAvsxB0u+nFt64UAQLR77OfSkqQL8vNjGB+LmwBRJUC1T" "\n"
            "MP73SLyUzUUg2FZkChZg63SN4YPh8B3y79iasIO00bZ5OXKcWza7AsN7MqFPKzwr" "\n"
            "Ud0o4t07q3vR2yhI+S/OdYVqNUMswnGwj3TgVNOJ1NvTeOF8Dx9GVueyyVAas96m" "\n"
            "uxvtIDq3lGD8HuNiqzKF+m+I0D0WAQNYlMhuSmvRjaMNFxULs8MED5+EfP3m4nXl" "\n"
            "41ei4WcwQVKjvbl2jXUxoFv8lxm6idPp5XmdrYKP0svsZPBgqOdf9idmptwv+Qsl" "\n"
            "GRqcOgYPo5ROj6Jy4S3xAI7VigpfDjWkbzMNWyDQFX4+mv2JIZGnPEuUHHqxkrLb" "\n"
            "ElIezIg9p3ubvyzSdwqQSouFMZz7E4o09J5ySPdnwnt7vGm+itkuy2FpiAQ7avuh" "\n"
            "4No9Ip9Z1Njd5WKFylagPHWPe2jxeUd7FleL9luesYRGijSrMNCjSR4snBxmis/r" "\n"
            "YhUNcoc099N631RbaqgEQOktCy9g1HF9rCpsSUAKDN7Qt7FFAwhgY4RUpMwDKnhN" "\n"
            "WK9WjC/RdlJRjY1xQYJmX41Xhkk6d5sCLEHAnAvXQ/Yp+9V6UNz2AnTlXEFx3W0R" "\n"
            "DRFR6MT6ONfw+fZ62SCCV7DROVOziHC51JPDOcHo9RD6zY14ql6NXmnF4o4A5xju" "\n"
            "ybQgYm9iICh0ZXN0IGtleSkgPGJvYkBleGFtcGxlLmNvbT6JATgEEwECACIFAlOm" "\n"
            "0k8CGwMGCwkIBwMCBhUIAgkKCwQWAgMBAh4BAheAAAoJEDyPdgfKWA+eXnAIAK9b" "\n"
            "mKFpr06+aHyGekHM50P0DRWRN1fAdTQTYbg7T6MvGduk/yz1qnDxpi45LsiU0EDS" "\n"
            "qhoINBRTVcSz9PJkk3BVnDAWrAFKICXE9HRkEBUsaa5E8L+kDUuAUoR/3kDdUqWp" "\n"
            "w64WYGcD6jgWpRMdD6GxcOyJw1+W59ZT+nSQCE/7yACSth07ZFNio736pEVQtv9T" "\n"
            "n81faIgij7Du/yTd1XMMoPpJAnwiSwUnuIlv3TM+7XjGVY4dhmX1I+8P+Ez5fBF0" "\n"
            "NHCcXZbU7VBPT5FmVuFl0HnqinNXKidpXBJnpfjC0jL2eEFWMe/3FpAqHttgK2T1" "\n"
            "EBq4NnXRHvYoA116hpCdA74EU6bSTwEIALTFMEWhDjrtDTJ7a01DWtQnvGfqxDTe" "\n"
            "SJNSvtT40u8nMoXYHqh0Y0Bj7AEUC+RgNn4CDOF/JaizfH5W5i6Vy09dHwoxR1sT" "\n"
            "h66g/7C7+OZevk+hybE1CCD3aIdDmHPElecGgM8AxJiXcK7HX37+MahzjguAk/1e" "\n"
            "buAHCjuR6rT42EaVsKAYoqUPEGv8mpvzulr1j5YFc3UsvWHywtpsA3qQQzHUaICr" "\n"
            "cbwv0cQQCc6ReCfi+dCn7uwqtKrEoRurDby8H0WM9wLchLMzlH98ZvWFqcP9gADl" "\n"
            "URtmuJQv06cs3YDE3N9ZA8jUbcrUtwMZysGj0UbwbSmW6Wb3d2iu++UAEQEAAf4D" "\n"
            "AwK80LaSJ9tcw2CdOJWnRUlrzRAh4ZGRTahvTi8zid3V5sCBVWKmCafQLtPufjgl" "\n"
            "fsMWamAiELp82M/m8sbn65jz2bAzDlUFStrQdgxPID+QySxKUw8WjYpUgYG0WE5L" "\n"
            "jdv36CRkUFNbWpMcSAo2elL/ywK8EIsldGfMnq9oj/hnTpm8NzQxYv5AewNlr8Mo" "\n"
            "cf0fO49xG9ua4vxftKGV20EQzQq5ap/xPdvPygX80+uGtJ6wBOZPX2AKtbPPjaeB" "\n"
            "vX3uSeLnyCh3uPbO6nmGpMBSoilWmlMHtn8VdPgM63RRdyNdy7n5I0zAVAeKYTtt" "\n"
            "LmJrZWV5CKp3ztTKgYsdboUHBVlBWYXRroVJpPSCZjQIQgDLLoKjyk/QkR7X7UZl" "\n"
            "42iTiFcwu+hHfA9T8wyDNKeXH0YyPQMw350XQOqolvHTorwAgw2/dXOHlXtu96fT" "\n"
            "H38OT83CEgNdVxMGdockqqTRrXMYcvspf7jSwJ7Td61+Q92NVF2ysgI0eP/UluL0" "\n"
            "uqijlXq1lHMBbXGc5n1nG0BiwoPUcPbojx7LeDUpEDnklue3fc06+8V1uk/YnGDf" "\n"
            "hq+Mh4GdowMNs3j8LRwtHNP4eCfBnuakIj/fpfHp+Q1nscVPRMYyofRfaG1g1Obl" "\n"
            "lqpmlDOS5UYzuTCwBBcbc/y5iXvmSrF9XTkahc7wuEVWkG3rYc4vVYqsbGkdV1wR" "\n"
            "P6EQiw08fA/FGr8amCxSoi/F0QTe+v0nKrTMm65FT0ltkowbrrXgEXKhI3mqg/ti" "\n"
            "xOlWg8fN3cmoTOeqAj3hIKGb/LnDrJkvehZdD7O4f684r6AQs3ZBM3ySCHlR4L+a" "\n"
            "6IqHY6lvOby5g7R2Zvq5lJAmRe7C4uli/g6m2v9VtQ1HgHcjrzuzWkZqqu4t1yrn" "\n"
            "hzUH8ZCknlSymo9qWLmZiQEfBBgBAgAJBQJTptJPAhsMAAoJEDyPdgfKWA+eqGAH" "\n"
            "/jzr4JcJJ2uN/epqiAIYau56M0mxdun1/H096+69h4HvpjoCWYyy1UylbblMdW29" "\n"
            "Uj2inXfk1uQPMTNTZ44NcQelj2mt11ypJHfE8uJL61KlJMnr15dEf3AbHJztOFnl" "\n"
            "InORKx1GgKPTWR9rJj2jnMFu87yImJvEeqK2/83lyapbZ9rFR7hTWI4HAvDsXK3k" "\n"
            "uUkLv5epH8m0QipnQu1Gj3zTW3rB/iLk8Li7+a0IdduZdjKYGtTR0Ru732qg0qeN" "\n"
            "Zjnpf2NTGxYHBXLN0Nu+Dpa/YcR3jCCQGKMPkQDoYGF40BnspBxxn3LWzwMBP9Ov" "\n"
            "rLKWGpju144Zj3G3V3fn1/c=" "\n"
            "=s9c+" "\n"
            "-----END PGP PRIVATE KEY BLOCK-----"
            ;
            
            const std::string PASSPHRASE = "test";
            
            TEST(private_key) {
                
                std::string in = GPG_PRIKEY_ALICE;
                PGPSecretKey pgp(in);
                
                auto packets = pgp.get_packets();
                VERIFY_ARE_EQUAL(packets.size(), 5);
                
                Packet::Ptr
                p0 = packets[0],
                p1 = packets[1],
                p2 = packets[2],
                p3 = packets[3],
                p4 = packets[4];
                
                VERIFY_ARE_EQUAL(p0->get_tag(), 5);
                VERIFY_ARE_EQUAL(p1->get_tag(), 13);
                VERIFY_ARE_EQUAL(p2->get_tag(), 2);
                VERIFY_ARE_EQUAL(p3->get_tag(), 7);
                VERIFY_ARE_EQUAL(p4->get_tag(), 2);
                Tag5::Ptr  seckey = std::dynamic_pointer_cast<Tag5>(p0);
                Tag13::Ptr userid = std::dynamic_pointer_cast<Tag13>(p1);
                Tag7::Ptr  subkey = std::dynamic_pointer_cast<Tag7>(p3);
                Tag2::Ptr  pubsig = std::dynamic_pointer_cast<Tag2>(p2),
                subsig = std::dynamic_pointer_cast<Tag2>(p4);
                
                VERIFY_ARE_EQUAL(seckey->get_version(), 4);
                VERIFY_ARE_EQUAL(subkey->get_version(), 4);
                VERIFY_ARE_EQUAL(pubsig->get_version(), 4);
                VERIFY_ARE_EQUAL(subsig->get_version(), 4);
                VERIFY_ARE_EQUAL(userid->get_version(), 0);  // undefined
                
                VERIFY_ARE_EQUAL(seckey->get_size(), 958);
                VERIFY_ARE_EQUAL(userid->get_size(), 36);
                VERIFY_ARE_EQUAL(pubsig->get_size(), 312);
                VERIFY_ARE_EQUAL(subkey->get_size(), 958);
                VERIFY_ARE_EQUAL(subsig->get_size(), 287);
                
                time_t gen_time = get_utc(2014, 6, 22, 12, 50, 48);
                
                // seckey
                {
                    VERIFY_ARE_EQUAL(seckey->get_time(), gen_time); // 2014-06-22T12:50:48 UTC
                    VERIFY_ARE_EQUAL(seckey->get_pka(), 1); // RSA
                    auto mpi = seckey->get_mpi();
                    auto n = mpi[0], e = mpi[1];
                    VERIFY_ARE_EQUAL(bitsize(n), 2048);  // 2048-bit
                    
                    auto strHex_n = mpitohex(n);
                    std::transform(strHex_n.begin(), strHex_n.end(), strHex_n.begin(), ::tolower);
                    VERIFY_ARE_EQUAL(strHex_n, "bc047e94d471f3ccbd525d6a6f8e17f7b1f00527c722c3913ce787fbd0090e3af8be7e59410f63b3983a9507b761045c11510e62f5a8cfbcdc180976a4c225737b8e06d8531f38c6eaa996954d5521a6763231f07c2b43605d052abdf39d6c668ac94bc89f543052d050530c70c48a49a970867c00178f9076dd0e151d254632767b2926e9baa22c6d0c213f1f45de74991396d7e8d10508cf679139410ab311b1279dd3c0d37facca54d523cd14a3df488eb8f592c5a19bcfede67c8170815c588adf39d188197da40492aac5b183c303f6ef23b0b5e48ff73b2d806afb0fb4f16ba32769249d3a7ca0ef0b9b3d57852dc9a979b6d56f3dc170e28dcb2e536d");
                    VERIFY_ARE_EQUAL(bitsize(e), 17);    // 17-bit
                    VERIFY_ARE_EQUAL(mpitohex(e), "010001");
                    VERIFY_ARE_EQUAL(seckey->get_sym(), 3); // CAST5
                    VERIFY_ARE_EQUAL(seckey->get_IV(), "\x47\xdb\x0a\x37\x11\x76\xb3\x5d");
                    auto secs2k = seckey->get_s2k();
                    VERIFY_ARE_EQUAL(secs2k->get_type(), 3);  // Salted-S2K
                    VERIFY_ARE_EQUAL(secs2k->get_hash(), 2);  // SHA1
                    S2K3::Ptr secs2k3 = std::dynamic_pointer_cast<S2K3>(secs2k);
                    VERIFY_ARE_EQUAL(secs2k3->get_count(), 96);
                    auto secmpi = decrypt_secret_key(seckey, PASSPHRASE);
                    VERIFY_ARE_EQUAL(secmpi.size(), 4);
                    
                    auto strHex_secmip_0 = mpitohex(secmpi[0]);
                    std::transform(strHex_secmip_0.begin(), strHex_secmip_0.end(), strHex_secmip_0.begin(), ::tolower);
                    VERIFY_ARE_EQUAL(strHex_secmip_0, "03949bbb19be693235e62b7ef33fcd6f5813afb7d8db542c99a3921eed10a3153050c993e30dbe6c454939836d27bb5f2c137323899bccd48fd909efe5b93b60a645daaf6aa3d1b8ee08fed72d56158bd13cb62c73e34ba0ed82f6ba76390eff43ea71f110ae7e814ad3fa5e8007dd5750acc92873aaff320ea56cf0ade4dc7994ac78d9dfc567ead2589f514ac4a95d2a28685d1f593129f7f82fdaca2e4e87b4b223ca3d6c742370bfba2a4954b1c7bcf4290addad26c2a52ea4a5d664a8c32cf729bb1c783fa817ef50c5432a3c1c73ef9d1e08ecf9780d5f3c8667ade01f397270b2919d632cba1ccd4c0861cb8420f4eabe8606115342657a281f1051d1");
                    
                    auto strHex_secmip_1 = mpitohex(secmpi[1]);
                    std::transform(strHex_secmip_1.begin(), strHex_secmip_1.end(), strHex_secmip_1.begin(), ::tolower);
                    VERIFY_ARE_EQUAL(strHex_secmip_1, "d03b3727809678a98fb4f94f9fde836efeaacafefd721ebb83c90dfebcc169a88944859afb2c4154c20d45a155d85bf692be56c1778b0bd94b77fd878d81bbe5584fbb28e716785821b1f4e0a3bffb7bc812c51394dc803d53afa261745092ed3169fcc7e2d125f2595a1555efc5f350be6654b050057839be3fc3ac1719453d");
                    auto strHex_secmip_2 = mpitohex(secmpi[2]);
                    std::transform(strHex_secmip_2.begin(), strHex_secmip_2.end(), strHex_secmip_2.begin(), ::tolower);
                    VERIFY_ARE_EQUAL(strHex_secmip_2, "e7262ff9b96de7b93a9977edebd1b424217c8e1edce2e1ac9e38493ef5e727b4fbbc64312e0a48823fa5e71292d939e724f2c5d32eed544be5e7bc3421b4b6031cd65b1d8531d24e1d44bd282edddb20f58abdd78722a18e4f62fde869381f5e6040e1163e399f7b7b614f17bb51038c23c57b1d87241d97dbc7e4b85e1909f1");
                    auto strHex_secmip_3 = mpitohex(secmpi[3]);
                    std::transform(strHex_secmip_3.begin(), strHex_secmip_3.end(), strHex_secmip_3.begin(), ::tolower);
                    VERIFY_ARE_EQUAL(strHex_secmip_3, "a5b011afc09d933d7f75b58e750bee1f05bf95d7bc354d3989eaa58cbdf85c367536b11dd29e016fe90f419288765e50af6e00a96660169716313f8d4080ce407cbad43a912e23170552d97a0465ab90a0a6b879a85bef0c2bbae100cbfc2927a01a0842fe8c2c6234149b35c05075438f7f4e2a3d5f19f427f423b868c0dad1");
                }
                
                // userid
                {
                    VERIFY_ARE_EQUAL(userid->raw(), "alice (test key) <alice@example.com>");
                }
                
                // pubsig (same as test_gpg_public_key)
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
                    VERIFY_ARE_EQUAL(subkey->get_pka(), 1); // RSA
                    auto mpi = subkey->get_mpi();
                    auto n = mpi[0], e = mpi[1];
                    VERIFY_ARE_EQUAL(bitsize(n), 2048);  // 2048-bit
                    auto strHex_n = mpitohex(n);
                    std::transform(strHex_n.begin(), strHex_n.end(), strHex_n.begin(), ::tolower);
                    VERIFY_ARE_EQUAL(strHex_n, "d98aac4e3f499e2264aebd71ea0e7d8a8d4690ff73d09125cd197892f1bb59492b8523dc5e4a0b9e0702babf65a71113d96a7ba2ee37cdc2ae8b0b03c67b16c12bd67e6835e4de01cd84baba53fb3d22294252dbb2ba854d1fe25f473b6ac8141392697bc6049d3865d9a00f909971e3b1903758e11b13a4661cf79080beac6d9ddb9113dfa788d2fc38a073b8d2717d0e28721f37dc0f7b6eb9a389f8050fac387ba3dedaf32210995534df5188982d431d0f6d93daa48b10ae7a337571f8bbcea59c9677789eedc2fcf2572f3d2ace9ae12b4817aa08d9541a423d0e60fd657f332c3fe47eef242e56715d25422971b6381a1e6a52bbae574da0077f83a535");
                    VERIFY_ARE_EQUAL(bitsize(e), 17);    // 17-bit
                    VERIFY_ARE_EQUAL(mpitohex(e), "010001");
                    VERIFY_ARE_EQUAL(subkey->get_sym(), 3); // CAST5
                    VERIFY_ARE_EQUAL(subkey->get_IV(), "\x22\x01\xe4\x2a\xc6\x81\x4d\x35");
                    auto subs2k = subkey->get_s2k();
                    VERIFY_ARE_EQUAL(subs2k->get_type(), 3);  // Salted-S2K
                    VERIFY_ARE_EQUAL(subs2k->get_hash(), 2);  // SHA1
                    S2K3::Ptr subs2k3 = std::dynamic_pointer_cast<S2K3>(subs2k);
                    VERIFY_ARE_EQUAL(subs2k3->get_count(), 96);
                    auto secmpi = decrypt_secret_key(subkey, PASSPHRASE);
                    VERIFY_ARE_EQUAL(secmpi.size(), 4);
                    auto strHex_secmip_0 = mpitohex(secmpi[0]);
                    std::transform(strHex_secmip_0.begin(), strHex_secmip_0.end(), strHex_secmip_0.begin(), ::tolower);
                    VERIFY_ARE_EQUAL(strHex_secmip_0, "6275226e19b3ba880b7490d6855e0090dc47136a22a343864dd118e2bcd893dd0b7eeb4f9a373e11cc4f7e7110d36fe5c171b1ba78c1b5f5466534db851201a6f52dd3b15baf1591d05021e92208644f594824d33d8db0b64ad77c52f37fed4534e47fac5edf88bed54e0d64ee079ce5b66034c49bc152ff059e57a7c5b546b9526a98fa7d2371d8843887c7708a5a5db82f3520cb7d784602b145e4c3de287fc2dd50a9b9c99d34176852e1024cf1eac2d9039b5a690991ee2f1b178c308587f62801955d3254530203b039823aec6d50bd40d791711fff815c76cd99164725cd43f4c2134c1053f63281d4a6d210809f6b686a3db45d66ebd85ac16883e413");
                    auto strHex_secmip_1 = mpitohex(secmpi[1]);
                    std::transform(strHex_secmip_1.begin(), strHex_secmip_1.end(), strHex_secmip_1.begin(), ::tolower);
                    VERIFY_ARE_EQUAL(strHex_secmip_1, "ebc63b9c2c5002d77f3f3261ce3ebdd4710827b180f0a2b5b847c2e5e6365903fc8ae73078666737850c0575d1ef558b0d77e3039f1e4cef6a97e90ccc70bec4459f4140725d98f2d275f81da1326b34cf1e0b0b69466e878e2c98823732ea5baa0cff7d687bf44590a0bab69f6d7182dcfb8ec20197fe9533730ce0549f991b");
                    auto strHex_secmip_2 = mpitohex(secmpi[2]);
                    std::transform(strHex_secmip_2.begin(), strHex_secmip_2.end(), strHex_secmip_2.begin(), ::tolower);
                    VERIFY_ARE_EQUAL(strHex_secmip_2, "ec3409ddb6f104384a7f4788ba73164d8420bdbc240d815c6e615603955ca128a388c21c0c19fe42be806922c2708d37efefd57a52f1fb777cfad002f2ba4f6c4c7119734340f13639b02a5c66d9b98048388ab3e97fca8f47fb07d360ed629762c045929f4f60c37c34a52ae75a12be68cb9644d7867de03029c3dccc736fef");
                    auto strHex_secmip_3 = mpitohex(secmpi[3]);
                    std::transform(strHex_secmip_3.begin(), strHex_secmip_3.end(), strHex_secmip_3.begin(), ::tolower);
                    VERIFY_ARE_EQUAL(strHex_secmip_3, "0547d7351f3047b5d4728cfed246eef218e4d0840d5f5edb9faf723da93bbb914e806a8ea569889eada1a37a6dd69da1c7f6f2e21d8fc6622dc759adb97a3e4003fcd7a499bcecebf9b7f4be958c3486501810ce321b2c343d1d19aae7f6b6454b5a7a5c551986f49e904b63a6f7cc32ccafa78bb7a7696d627ba67489cdcc89");
                }
                
                // subsig (same as test_gpg_public_key)
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
