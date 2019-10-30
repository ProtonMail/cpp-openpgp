//
//  openpgp_pka_encrypt_test.cpp
//  OpenPGP
//
//  Created by Yanfeng Zhang on 11/1/16.
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


#include "utils_test.h"

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
        
        SUITE(gpg_pka_encrypt)
        {
            const std::string GPG_PKA_ENCRYPT_ALICE_TO_BOB =
            "-----BEGIN PGP MESSAGE-----" "\n"
            "Version: GnuPG v1" "\n"
            "" "\n"
            "hQEMA9QjCqNoYcNdAQgApgs5sD8I8rCDyf/m135MqNTtybb/dU9+PjaMe8BnQnY8" "\n"
            "UwXj/CedfWZ+GukGcTDmHiQLa+bkdP6A5iXYbVNoQfbRFhoZR6VvRtHWIvnxR/V6" "\n"
            "UR5iFpmL6aSWa5Lg91H2kTjxtMKTYIrWe0ttFuXO7XnL3AliLiv9Ko3hnUeolGQ3" "\n"
            "yXyluV9twaalzobgQdZ4WWLWTY2W+DCVC/ESUJoUbb2TIvVDQ6L/ulQ4WdgZSIkL" "\n"
            "4gnm4SQMvgK55Z0wbhaXoyhC+eNgWW49hm9iGbATGqR1d89iJ3jmrk3noNt69RHi" "\n"
            "IPY/esD4Aw5eQ1g8Ni67qWRtUFox0CAYZAtF51yP19LA3wH/sUrMEeudL5H8FTjk" "\n"
            "acaKfhhHQ0VveKz21aVz4pGRCujcPxzhslhD6LnZuxFEugaqVfPpjHiqvBCkMkIm" "\n"
            "85xea+0g0IZJlcoh4aVBUqRyagKlsy434fqMfGjOM70D3LNheZGLEBhfgdPaHbYN" "\n"
            "VCQljZDTyMq0i0VYmzSKMVDA07FnLZOJg/REx3+2n9OysYS3BZukIfZigH6Flx2a" "\n"
            "fedrAN4hRgploOh3MDdNgFmVv2CilgaeZkrXPN7EecahKI7EYyBKjcLzDkTKu7Pw" "\n"
            "0k1Id4C6NZSt0wyz4L4hiQ8WtYSaGmRXLLBA+GCIASre4E2f+qSNeEB6xQOdHuZ+" "\n"
            "84EFxyuCupuSRj1/6rluUe7K8NXvzoq6lrnuYLHSLI/xk08mRNMGdZG1AiVWFjvA" "\n"
            "lvMo+TUp8vBJrE86NgLdvpyip5JQ9LjjaHcwFjFEbAzGztswfLs6j/Q10e6MQNXs" "\n"
            "Dlyl7J8y+pvmmBsPuAZvQRZVVzoNbRMDfaBgUx7lm2LP4vuCrwfitnfExcJA3eYb" "\n"
            "BFWyJke4a5Nluw/gLhyi1+8=" "\n"
            "=/hTO" "\n"
            "-----END PGP MESSAGE-----"
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
            
            TEST(encrypt) {
                std::string in = GPG_PKA_ENCRYPT_ALICE_TO_BOB;
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
                VERIFY_ARE_EQUAL(tag18->get_size(), 415);
                
                // tag1
                {
                    VERIFY_ARE_EQUAL(tag1->get_keyid(), "\xd4\x23\x0a\xa3\x68\x61\xc3\x5d");
                    VERIFY_ARE_EQUAL(tag1->get_pka(), 1); // RSA
                    auto mpi = tag1->get_mpi();
                    VERIFY_ARE_EQUAL(mpi.size(), 1);
                    
                    auto key = mpi[0];
                    VERIFY_ARE_EQUAL(bitsize(key), 2048);
                    auto strHex_key = mpitohex(key);
                    std::transform(strHex_key.begin(), strHex_key.end(), strHex_key.begin(), ::tolower);
                    VERIFY_ARE_EQUAL(strHex_key, "a60b39b03f08f2b083c9ffe6d77e4ca8d4edc9b6ff754f7e3e368c7bc06742763c5305e3fc279d7d667e1ae9067130e61e240b6be6e474fe80e625d86d536841f6d1161a1947a56f46d1d622f9f147f57a511e6216998be9a4966b92e0f751f69138f1b4c293608ad67b4b6d16e5ceed79cbdc09622e2bfd2a8de19d47a8946437c97ca5b95f6dc1a6a5ce86e041d6785962d64d8d96f830950bf112509a146dbd9322f54343a2ffba543859d81948890be209e6e1240cbe02b9e59d306e1697a32842f9e360596e3d866f6219b0131aa47577cf622778e6ae4de7a0db7af511e220f63f7ac0f8030e5e43583c362ebba9646d505a31d02018640b45e75c8fd7");
                }
                // tag18
                {
                    std::string in_pri = GPG_PRIKEY_BOB;
                    PGPSecretKey pgp_pri(in_pri);
                    bool verify = false;
                    std::string message = decrypt_pka(pgp_pri, pgp, PASSPHRASE, verify, false);
                    VERIFY_ARE_EQUAL(message, "The magic words are squeamish ossifrage\n");
                }
            }

        }
    }
}
