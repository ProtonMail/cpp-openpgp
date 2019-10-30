//
//  openpgpjs_testcases.cpp
//  OpenPGP
//
//  Created by Yanfeng Zhang on 11/1/16.
//  Copyright © 2016 Yanfeng Zhang. All rights reserved.
//

#include "utils_test.h"

#include <openpgp/PGPKey.h>
#include <openpgp/encrypt.h>
#include <openpgp/decrypt.h>
#include <algorithm>
#include <string>
#include <openpgp/pgptime.h>


#include "bridge/encrypt_package.hpp"
#include "bridge_impl/open_pgp_impl.hpp"
#include "bridge/open_pgp_key.hpp"


namespace tests {
    namespace open_pgp_tests {
        SUITE(openpgo_testcases)
        {
            auto pub_key =
            "-----BEGIN PGP PUBLIC KEY BLOCK-----" "\n"
            "Version: GnuPG v2.0.19 (GNU/Linux)" "\n"
            "" "\n"
            "mI0EUmEvTgEEANyWtQQMOybQ9JltDqmaX0WnNPJeLILIM36sw6zL0nfTQ5zXSS3+" "\n"
            "fIF6P29lJFxpblWk02PSID5zX/DYU9/zjM2xPO8Oa4xo0cVTOTLj++Ri5mtr//f5" "\n"
            "GLsIXxFrBJhD/ghFsL3Op0GXOeLJ9A5bsOn8th7x6JucNKuaRB6bQbSPABEBAAG0" "\n"
            "JFRlc3QgTWNUZXN0aW5ndG9uIDx0ZXN0QGV4YW1wbGUuY29tPoi5BBMBAgAjBQJS" "\n"
            "YS9OAhsvBwsJCAcDAgEGFQgCCQoLBBYCAwECHgECF4AACgkQSmNhOk1uQJQwDAP6" "\n"
            "AgrTyqkRlJVqz2pb46TfbDM2TDF7o9CBnBzIGoxBhlRwpqALz7z2kxBDmwpQa+ki" "\n"
            "Bq3jZN/UosY9y8bhwMAlnrDY9jP1gdCo+H0sD48CdXybblNwaYpwqC8VSpDdTndf" "\n"
            "9j2wE/weihGp/DAdy/2kyBCaiOY1sjhUfJ1GogF49rC4jQRSYS9OAQQA6R/PtBFa" "\n"
            "JaT4jq10yqASk4sqwVMsc6HcifM5lSdxzExFP74naUMMyEsKHP53QxTF0Grqusag" "\n"
            "Qg/ZtgT0CN1HUM152y7ACOdp1giKjpMzOTQClqCoclyvWOFB+L/SwGEIJf7LSCEr" "\n"
            "woBuJifJc8xAVr0XX0JthoW+uP91eTQ3XpsAEQEAAYkBPQQYAQIACQUCUmEvTgIb" "\n"
            "LgCoCRBKY2E6TW5AlJ0gBBkBAgAGBQJSYS9OAAoJEOCE90RsICyXuqIEANmmiRCA" "\n"
            "SF7YK7PvFkieJNwzeK0V3F2lGX+uu6Y3Q/Zxdtwc4xR+me/CSBmsURyXTO29OWhP" "\n"
            "GLszPH9zSJU9BdDi6v0yNprmFPX/1Ng0Abn/sCkwetvjxC1YIvTLFwtUL/7v6NS2" "\n"
            "bZpsUxRTg9+cSrMWWSNjiY9qUKajm1tuzPDZXAUEAMNmAN3xXN/Kjyvj2OK2ck0X" "\n"
            "W748sl/tc3qiKPMJ+0AkMF7Pjhmh9nxqE9+QCEl7qinFqqBLjuzgUhBU4QlwX1GD" "\n"
            "AtNTq6ihLMD5v1d82ZC7tNatdlDMGWnIdvEMCv2GZcuIqDQ9rXWs49e7tq1NncLY" "\n"
            "hz3tYjKhoFTKEIq3y3Pp" "\n"
            "=h/aX" "\n"
            "-----END PGP PUBLIC KEY BLOCK-----" "\n";
            
            auto priv_key =
            "-----BEGIN PGP PRIVATE KEY BLOCK-----" "\n"
            "Version: GnuPG v2.0.19 (GNU/Linux)" "\n"
            "" "\n"
            "lQH+BFJhL04BBADclrUEDDsm0PSZbQ6pml9FpzTyXiyCyDN+rMOsy9J300Oc10kt" "\n"
            "/nyBej9vZSRcaW5VpNNj0iA+c1/w2FPf84zNsTzvDmuMaNHFUzky4/vkYuZra//3" "\n"
            "+Ri7CF8RawSYQ/4IRbC9zqdBlzniyfQOW7Dp/LYe8eibnDSrmkQem0G0jwARAQAB" "\n"
            "/gMDAu7L//czBpE40p1ZqO8K3k7UejemjsQqc7kOqnlDYd1Z6/3NEA/UM30Siipr" "\n"
            "KjdIFY5+hp0hcs6EiiNq0PDfm/W2j+7HfrZ5kpeQVxDek4irezYZrl7JS2xezaLv" "\n"
            "k0Fv/6fxasnFtjOM6Qbstu67s5Gpl9y06ZxbP3VpT62+Xeibn/swWrfiJjuGEEhM" "\n"
            "bgnsMpHtzAz/L8y6KSzViG/05hBaqrvk3/GeEA6nE+o0+0a6r0LYLTemmq6FbaA1" "\n"
            "PHo+x7k7oFcBFUUeSzgx78GckuPwqr2mNfeF+IuSRnrlpZl3kcbHASPAOfEkyMXS" "\n"
            "sWGE7grCAjbyQyM3OEXTSyqnehvGS/1RdB6kDDxGwgE/QFbwNyEh6K4eaaAThW2j" "\n"
            "IEEI0WEnRkPi9fXyxhFsCLSI1XhqTaq7iDNqJTxE+AX2b9ZuZXAxI3Tc/7++vEyL" "\n"
            "3p18N/MB2kt1Wb1azmXWL2EKlT1BZ5yDaJuBQ8BhphM3tCRUZXN0IE1jVGVzdGlu" "\n"
            "Z3RvbiA8dGVzdEBleGFtcGxlLmNvbT6IuQQTAQIAIwUCUmEvTgIbLwcLCQgHAwIB" "\n"
            "BhUIAgkKCwQWAgMBAh4BAheAAAoJEEpjYTpNbkCUMAwD+gIK08qpEZSVas9qW+Ok" "\n"
            "32wzNkwxe6PQgZwcyBqMQYZUcKagC8+89pMQQ5sKUGvpIgat42Tf1KLGPcvG4cDA" "\n"
            "JZ6w2PYz9YHQqPh9LA+PAnV8m25TcGmKcKgvFUqQ3U53X/Y9sBP8HooRqfwwHcv9" "\n"
            "pMgQmojmNbI4VHydRqIBePawnQH+BFJhL04BBADpH8+0EVolpPiOrXTKoBKTiyrB" "\n"
            "UyxzodyJ8zmVJ3HMTEU/vidpQwzISwoc/ndDFMXQauq6xqBCD9m2BPQI3UdQzXnb" "\n"
            "LsAI52nWCIqOkzM5NAKWoKhyXK9Y4UH4v9LAYQgl/stIISvCgG4mJ8lzzEBWvRdf" "\n"
            "Qm2Ghb64/3V5NDdemwARAQAB/gMDAu7L//czBpE40iPcpLzL7GwBbWFhSWgSLy53" "\n"
            "Md99Kxw3cApWCok2E8R9/4VS0490xKZIa5y2I/K8thVhqk96Z8Kbt7MRMC1WLHgC" "\n"
            "qJvkeQCI6PrFM0PUIPLHAQtDJYKtaLXxYuexcAdKzZj3FHdtLNWCooK6n3vJlL1c" "\n"
            "WjZcHJ1PH7USlj1jup4XfxsbziuysRUSyXkjn92GZLm+64vCIiwhqAYoizF2NHHG" "\n"
            "hRTN4gQzxrxgkeVchl+ag7DkQUDANIIVI+A63JeLJgWJiH1fbYlwESByHW+zBFNt" "\n"
            "qStjfIOhjrfNIc3RvsggbDdWQLcbxmLZj4sB0ydPSgRKoaUdRHJY0S4vp9ouKOtl" "\n"
            "2au/P1BP3bhD0fDXl91oeheYth+MSmsJFDg/vZJzCJhFaQ9dp+2EnjN5auNCNbaI" "\n"
            "beFJRHFf9cha8p3hh+AK54NRCT++B2MXYf+TPwqX88jYMBv8kk8vYUgo8128r1zQ" "\n"
            "EzjviQE9BBgBAgAJBQJSYS9OAhsuAKgJEEpjYTpNbkCUnSAEGQECAAYFAlJhL04A" "\n"
            "CgkQ4IT3RGwgLJe6ogQA2aaJEIBIXtgrs+8WSJ4k3DN4rRXcXaUZf667pjdD9nF2" "\n"
            "3BzjFH6Z78JIGaxRHJdM7b05aE8YuzM8f3NIlT0F0OLq/TI2muYU9f/U2DQBuf+w" "\n"
            "KTB62+PELVgi9MsXC1Qv/u/o1LZtmmxTFFOD35xKsxZZI2OJj2pQpqObW27M8Nlc" "\n"
            "BQQAw2YA3fFc38qPK+PY4rZyTRdbvjyyX+1zeqIo8wn7QCQwXs+OGaH2fGoT35AI" "\n"
            "SXuqKcWqoEuO7OBSEFThCXBfUYMC01OrqKEswPm/V3zZkLu01q12UMwZach28QwK" "\n"
            "/YZly4ioND2tdazj17u2rU2dwtiHPe1iMqGgVMoQirfLc+k=" "\n"
            "=lw5e" "\n"
            "-----END PGP PRIVATE KEY BLOCK-----" "\n";
            
            auto pub_key_de =
            "-----BEGIN PGP PUBLIC KEY BLOCK-----" "\n"
            "Version: GnuPG v2.0.22 (GNU/Linux)" "\n"
            "" "\n"
            "mQMuBFLVgdQRCACOlpq0cd1IazNjOEpWPZvx/O3JMbdDs3B3iCG0Mo5OUZ8lpKU5" "\n"
            "EslVgTd8IcUU14ZMOO7y91dw0KP4q61b4OIy7oVxzfFfKCC1s0Dc7GTay+qo5afJ" "\n"
            "wbWcgTyCIahTRmi5UepU7xdRHRMlqAclOwY2no8fw0JRQfFwRFCjbMdmvzC/k+Wo" "\n"
            "A42nn8YaSAG2v7OqF3rkYjkv/7iak48PO/l0Q13USAJLIWdHvRTir78mQUsEY0qR" "\n"
            "VoNqz5sMqakzhTvTav07EVy/1xC6GKoWXA9sdB/4r7+blVuu9M4yD40GkE69oAXO" "\n"
            "mz6tG3lRq41S0OSzNyDWtUQgMVF6wYqVxUGrAQDJM5A1rF1RKzFiHdkyy57E8LC1" "\n"
            "SIJyIXWJ0c5b8/olWQf9G5a17fMjkRTC3FO+ZHwFE1jIM6znYOF2GltDToLuJPq9" "\n"
            "lWrI7zVP9AJPwrUt7FK2MBNAvd1jKyIhdU98PBQ2pr+jmyqIycl9iDGXLDO7D7E/" "\n"
            "TBnxwQzoL/5b7UnPImuXOwv5JhVmyV2t003xjzb1EGggOnpKugUtVLps8JiLl9n+" "\n"
            "Nkj5wpU7NXbuHj2XGkkGmKkCIz4l0dJQR9V6svJV9By0RPgfGPXlN1VR6f2ounNy" "\n"
            "6REnDCQP9S3Li5eNcxlSGDIxIZL22j63sU/68GVlzqhVdGXxofv5jGtajiNSpPot" "\n"
            "ElZU0dusna4PzYmiBCsyN8jENWSzHLJ37N4ScN4b/gf6Axf9FU0PjzPBN1o9W6zj" "\n"
            "kpfhlSWDjE3BK8jJ7KvzecM2QE/iJsbuyKEsklw1v0MsRDsox5QlQJcKOoUHC+OT" "\n"
            "iKm8cnPckLQNPOw/kb+5Auz7TXBQ63dogDuqO8QGGOpjh8SIYbblYQI5ueo1Tix3" "\n"
            "PlSU36SzOQfxSOCeIomEmaFQcU57O1CLsRl//+5lezMFDovJyQHQZfiTxSGfPHij" "\n"
            "oQzEUyEWYHKQhIRV6s5VGvF3hN0t8fo0o57bzhV6E7IaSz2Cnm0O0S2PZt8DBN9l" "\n"
            "LYNw3cFgzMb/qdFJGR0JXz+moyAYh/fYMiryb6d8ghhvrRy0CrRlC3U5K6qiYfKu" "\n"
            "lLQURFNBL0VMRyA8ZHNhQGVsZy5qcz6IewQTEQgAIwUCUtWB1AIbAwcLCQgHAwIB" "\n"
            "BhUIAgkKCwQWAgMBAh4BAheAAAoJELqZP8Ku4Yo6Aa0A/1Kz5S8d9czLiDbrhSa/" "\n"
            "C1rQ5qiWpFq9UNTFg2P/gASvAP92TzUMLK2my8ew1xXShtrfXked5fkSuFrPlZBs" "\n"
            "b4Ta67kCDQRS1YHUEAgAxOKx4y5QD78uPLlgNBHXrcncUNBIt4IXBGjQTxpFcn5j" "\n"
            "rSuj+ztvXJQ8wCkx+TTb2yuL5M+nXd7sx4s+M4KZ/MZfI6ZX4lhcoUdAbB9FWiV7" "\n"
            "uNntyeFo8qgGM5at/Q0EsyzMSqbeBxk4bpd5MfYGThn0Ae2xaw3X94KaZ3LjtHo2" "\n"
            "V27FD+jvmmoAj9b1+zcO/pJ8SuojQmcnS4VDVV+Ba5WPTav0LzDdQXyGMZI9PDxC" "\n"
            "jAI2f1HjTuxIt8X8rAQSQdoMIcQRYEjolsXS6iob1eVigyL86hLJjI3VPn6kBCv3" "\n"
            "Tb+WXX+9LgSAt9yvv4HMwBLK33k6IH7M72SqQulZywADBQgAt2xVTMjdVyMniMLj" "\n"
            "Ed4HbUgwyCPkVkcA4zTXqfKu+dAe4dK5tre0clkXZVtR1V8RDAD0zaVyM030e2zb" "\n"
            "zn4cGKDL2dmwk2ZBeXWZDgGKoKvGKYf8PRpTAYweFzol3OUdfXH5SngOylCD4OCL" "\n"
            "s4RSVkSsllIWqLpnS5IJFgt6PDVcQgGXo2ZhVYkoLNhWTIEBuJWIyc4Vj20YpTms" "\n"
            "lgHnjeq5rP6781MwAJQnViyJ2SziGK4/+3CoDiQLO1zId42otXBvsbUuLSL5peX4" "\n"
            "v2XNVMLJMY5iSfzbBWczecyapiQ3fbVtWgucgrqlrqM3546v+GdATBhGOu8ppf5j" "\n"
            "7d1A7ohhBBgRCAAJBQJS1YHUAhsMAAoJELqZP8Ku4Yo6SgoBAIVcZstwz4lyA2et" "\n"
            "y61IhKbJCOlQxyem+kepjNapkhKDAQDIDL38bZWU4Rm0nq82Xb4yaI0BCWDcFkHV" "\n"
            "og2umGfGng==" "\n"
            "=v3+L" "\n"
            "-----END PGP PUBLIC KEY BLOCK-----" "\n";
            
            auto priv_key_de =
            "-----BEGIN PGP PRIVATE KEY BLOCK-----" "\n"
            "Version: GnuPG v2.0.22 (GNU/Linux)" "\n"
            "" "\n"
            "lQN5BFLVgdQRCACOlpq0cd1IazNjOEpWPZvx/O3JMbdDs3B3iCG0Mo5OUZ8lpKU5" "\n"
            "EslVgTd8IcUU14ZMOO7y91dw0KP4q61b4OIy7oVxzfFfKCC1s0Dc7GTay+qo5afJ" "\n"
            "wbWcgTyCIahTRmi5UepU7xdRHRMlqAclOwY2no8fw0JRQfFwRFCjbMdmvzC/k+Wo" "\n"
            "A42nn8YaSAG2v7OqF3rkYjkv/7iak48PO/l0Q13USAJLIWdHvRTir78mQUsEY0qR" "\n"
            "VoNqz5sMqakzhTvTav07EVy/1xC6GKoWXA9sdB/4r7+blVuu9M4yD40GkE69oAXO" "\n"
            "mz6tG3lRq41S0OSzNyDWtUQgMVF6wYqVxUGrAQDJM5A1rF1RKzFiHdkyy57E8LC1" "\n"
            "SIJyIXWJ0c5b8/olWQf9G5a17fMjkRTC3FO+ZHwFE1jIM6znYOF2GltDToLuJPq9" "\n"
            "lWrI7zVP9AJPwrUt7FK2MBNAvd1jKyIhdU98PBQ2pr+jmyqIycl9iDGXLDO7D7E/" "\n"
            "TBnxwQzoL/5b7UnPImuXOwv5JhVmyV2t003xjzb1EGggOnpKugUtVLps8JiLl9n+" "\n"
            "Nkj5wpU7NXbuHj2XGkkGmKkCIz4l0dJQR9V6svJV9By0RPgfGPXlN1VR6f2ounNy" "\n"
            "6REnDCQP9S3Li5eNcxlSGDIxIZL22j63sU/68GVlzqhVdGXxofv5jGtajiNSpPot" "\n"
            "ElZU0dusna4PzYmiBCsyN8jENWSzHLJ37N4ScN4b/gf6Axf9FU0PjzPBN1o9W6zj" "\n"
            "kpfhlSWDjE3BK8jJ7KvzecM2QE/iJsbuyKEsklw1v0MsRDsox5QlQJcKOoUHC+OT" "\n"
            "iKm8cnPckLQNPOw/kb+5Auz7TXBQ63dogDuqO8QGGOpjh8SIYbblYQI5ueo1Tix3" "\n"
            "PlSU36SzOQfxSOCeIomEmaFQcU57O1CLsRl//+5lezMFDovJyQHQZfiTxSGfPHij" "\n"
            "oQzEUyEWYHKQhIRV6s5VGvF3hN0t8fo0o57bzhV6E7IaSz2Cnm0O0S2PZt8DBN9l" "\n"
            "LYNw3cFgzMb/qdFJGR0JXz+moyAYh/fYMiryb6d8ghhvrRy0CrRlC3U5K6qiYfKu" "\n"
            "lP4DAwJta87fJ43wickVqBNBfgrPyVInvHC/MjSTKzD/9fFin7zYPUofXjj/EZMN" "\n"
            "4IqNqDd1aI5vo67jF0nGvpcgU5qabYWDgq2wKrQURFNBL0VMRyA8ZHNhQGVsZy5q" "\n"
            "cz6IewQTEQgAIwUCUtWB1AIbAwcLCQgHAwIBBhUIAgkKCwQWAgMBAh4BAheAAAoJ" "\n"
            "ELqZP8Ku4Yo6Aa0A/1Kz5S8d9czLiDbrhSa/C1rQ5qiWpFq9UNTFg2P/gASvAP92" "\n"
            "TzUMLK2my8ew1xXShtrfXked5fkSuFrPlZBsb4Ta650CYwRS1YHUEAgAxOKx4y5Q" "\n"
            "D78uPLlgNBHXrcncUNBIt4IXBGjQTxpFcn5jrSuj+ztvXJQ8wCkx+TTb2yuL5M+n" "\n"
            "Xd7sx4s+M4KZ/MZfI6ZX4lhcoUdAbB9FWiV7uNntyeFo8qgGM5at/Q0EsyzMSqbe" "\n"
            "Bxk4bpd5MfYGThn0Ae2xaw3X94KaZ3LjtHo2V27FD+jvmmoAj9b1+zcO/pJ8Suoj" "\n"
            "QmcnS4VDVV+Ba5WPTav0LzDdQXyGMZI9PDxCjAI2f1HjTuxIt8X8rAQSQdoMIcQR" "\n"
            "YEjolsXS6iob1eVigyL86hLJjI3VPn6kBCv3Tb+WXX+9LgSAt9yvv4HMwBLK33k6" "\n"
            "IH7M72SqQulZywADBQgAt2xVTMjdVyMniMLjEd4HbUgwyCPkVkcA4zTXqfKu+dAe" "\n"
            "4dK5tre0clkXZVtR1V8RDAD0zaVyM030e2zbzn4cGKDL2dmwk2ZBeXWZDgGKoKvG" "\n"
            "KYf8PRpTAYweFzol3OUdfXH5SngOylCD4OCLs4RSVkSsllIWqLpnS5IJFgt6PDVc" "\n"
            "QgGXo2ZhVYkoLNhWTIEBuJWIyc4Vj20YpTmslgHnjeq5rP6781MwAJQnViyJ2Szi" "\n"
            "GK4/+3CoDiQLO1zId42otXBvsbUuLSL5peX4v2XNVMLJMY5iSfzbBWczecyapiQ3" "\n"
            "fbVtWgucgrqlrqM3546v+GdATBhGOu8ppf5j7d1A7v4DAwJta87fJ43wicncdV+Y" "\n"
            "7ess/j8Rx6/4Jt7ptmRjJNRNbB0ORLZ5BA9544qzAWNtfPOs2PUEDT1L+ChXfD4w" "\n"
            "ZG3Yk5hE+PsgbSbGQ5iTSTg9XJYqiGEEGBEIAAkFAlLVgdQCGwwACgkQupk/wq7h" "\n"
            "ijpKCgD9HC+RyNOutHhPFbgSvyH3cY6Rbnh1MFAUH3SG4gmiE8kA/A679f/+Izs1" "\n"
            "DHTORVqAOdoOcu5Qh7AQg1GdSmfFAsx2" "\n"
            "=kyeP" "\n"
            "-----END PGP PRIVATE KEY BLOCK-----" "\n";
            
            auto passphrase = "hello world";
            auto plaintext = "short message\nnext line\n한국어/조선말";
            auto password1 = "I am a password";
            auto password2 = "I am another password";
            
            
            TEST(private_key_2_public_key_test) {
                std::string key = priv_key_de;
                PGPSecretKey priv(key);
                auto pubkey = priv.pub();
            }
            
            TEST(mdc_test) {
                
                {
                    std::string mdc_messae = "-----BEGIN PGP MESSAGE-----\r\n"
                    "Version: OpenPGP.js v3.0.9\r\n"
                    "Comment: https://openpgpjs.org\r\n"
                    "\r\n"
                    "wYwD4IT3RGwgLJcBA/99QQ/P/MP3Ne0ZJxHfkDHHv8OO44tAKgprKIpCpj2l\r\n"
                    "MuMa4D3LfTuDNjt5STCfQ9R2DNWIVxmKKFA/Gv8GiFY39S0slpLrkvB65bPs\r\n"
                    "PeO253PgJxTvzqA5NzC566fxbSYF0iVejpEf85ZMT0DTklDiVFXFMFHHIN6+\r\n"
                    "BCOTc6IpSsnAG5V4w3Mh/3lTQWjdU468wnKHOvKGjHae3KZ2Qg3tqPCOHD0N\r\n"
                    "ltJPjs2pQ7mrhWzpG7/GyBcau2F59xsD4AmE/Z/HFD6rZrUjaMk7nRwjtl2s\r\n"
                    "KxrgXau38kJcrldt1mtO55PwgQArtCb8TsW7bbHGu5OlXFrHtK154wsHDlkX\r\n"
                    "rjX2LtmZnnerWbSRu4tpAi9ot5kejFXWsUm5E9exAdjcg5fnFq2dpZ/Oc57B\r\n"
                    "gqUn5Zn7to2kVsOEv1emmS0YoKaRiwozXuwUPcD2pwF85EBpPMCut4/mRFex\r\n"
                    "3BHJyA==\r\n"
                    "=kV/J\r\n"
                    "-----END PGP MESSAGE-----";
                    
                    std::string privKey = priv_key;
                    PGPSecretKey pk (privKey);
                    PGPMessage msg(mdc_messae);
//                    auto out = decrypt_pka(pk, msg, passphrase, retVerify);
//                    VERIFY_ARE_EQUAL(out, "");
                    
                }
                
                {
                    std::string mdc_messae = "-----BEGIN PGP MESSAGE-----\r\n"
                    "Version: OpenPGP.js VERSION\r\n"
                    "Comment: https://openpgpjs.org\r\n"
                    "\r\n"
                    "wYwD4IT3RGwgLJcBBADRn2rWzydBXbQUMFruybN9afSa0QA1UZAjsja0hHgF\r\n"
                    "xHlkagsp4WLadOd2DzByv5szcNly2ywZrRjfyFkFVCuexYwmzCUEou4FfxRh\r\n"
                    "X2zHTc+56JhLBPedH6q2iVW2OOC9EisLWD9lnofsvgaCwagXxdFCqj3XCSk1\r\n"
                    "i8Wcln3PZcnAGxzZfGCEzZg+K1JolYX+dQZ4g424XJL4nI5ozUm5ZcQEq0An\r\n"
                    "9jwgUEFz3HK2ccEHOHXfs7c0w7Xopy/rseGgAbFsVDTbgqYcNPRJt1ii5tTF\r\n"
                    "ezLuEPyM7cokjREWnCY9jUIx2U2DSaym/bfnHtrb8j2Vd0MG8bQbPLJP2gCD\r\n"
                    "w0a3vmb2Mxp1PIDmH42sVsy5obbObvIkwPJjI5zQTv0EANGoHPp4uWTcnNK9\r\n"
                    "lgaWly1BWEv2+XZicAzrgxVlY/Z19gVXv36PVCF3yrnp6mxGhk0F41WD5yJB\r\n"
                    "CIyfPw==\r\n"
                    "=uHa0\r\n"
                    "-----END PGP MESSAGE-----";
                    
                    std::string privKey = priv_key;
                    bool retVerify = false;
                    PGPSecretKey pk (privKey);
                    PGPMessage msg(mdc_messae);
                    auto out = decrypt_pka(pk, msg, passphrase, retVerify);
                    VERIFY_IS_TRUE(out != "");
                }
                
            }
            
            TEST(generate_key_test) {
                //TODO::fix the new interface
                { // invalid user name input
                    //auto user_id = "";
                    //auto email = "test@example.com";
                    //auto passphrase = "";
                    //VERIFY_THROWS_EQUAL(ProtonMail::OpenPgp::generate_new_key(user_id, email, passphrase, 2048), std::runtime_error, "Invalid user name format");
                }
                //TODO:: add email user id validation
//                { //should fail for invalid user email address
//                    auto user_id = "Test User";
//                    auto email = "textexample.com";
//                    auto passphrase = "";
//                    VERIFY_THROWS_EQUAL(ProtonMail::OpenPgp::generate_new_key(user_id, email, passphrase, 2048), std::runtime_error, "Invalid user name format");
//                }
//                
//                { //should fail for invalid user email address
//                    auto user_id = "Test User";
//                    auto email = "text@examplecom";
//                    auto passphrase = "";
//                    VERIFY_THROWS_EQUAL(ProtonMail::OpenPgp::generate_new_key(user_id, email, passphrase, 2048), std::runtime_error, "Invalid email format");
//                }
//                
//                { //should fail for invalid string user id
//                    auto user_id = "Test User text@example.com>";
//                    auto email = "test@example.com";
//                    auto passphrase = "";
//                    VERIFY_THROWS_EQUAL(ProtonMail::OpenPgp::generate_new_key(user_id, email, passphrase, 2048), std::runtime_error, "Invalid passphrase format");
//                }
                
                { //should work for valid single user id & email
                    auto user_id = "test"; // username
                    auto email = "example.com"; //domain
                    auto passphrase = "123"; //pwd
                    auto pgp = ProtonMail::OpenPgpImpl::create_instance();
                    auto new_key = pgp->generate_key(user_id, email, passphrase, 2048, 0);
                    
                    VERIFY_IS_FALSE( new_key.private_key.empty());
                    VERIFY_IS_FALSE( new_key.public_key.empty());
                }


//                it('should work for valid single string user id', function(done) {
//                    var opt = {
//                    userIds: 'Test User <text@example.com>'
//                    };
//                    openpgp.generateKey(opt).then(function() { done(); });
//                });

//                it('should work for valid string user id', function(done) {
//                    var opt = {
//                    userIds: ['Test User <text@example.com>']
//                    };
//                    openpgp.generateKey(opt).then(function() { done(); });
//                });

//                it('should work for valid single user id hash', function(done) {
//                    var opt = {
//                    userIds: [{ name: 'Test User', email: 'text@example.com' }]
//                    };
//                    openpgp.generateKey(opt).then(function() { done(); });
//                });

//                it('should work for an empty name', function(done) {
//                    var opt = {
//                    userIds: { email: 'text@example.com' }
//                    };
//                    openpgp.generateKey(opt).then(function() { done(); });
//                });

//                it('should work for an empty email address', function(done) {
//                    var opt = {
//                    userIds: { name: 'Test User' }
//                    };
//                    openpgp.generateKey(opt).then(function() { done(); });
//                });
                
//                it('should have default params set', function(done) {
//                    var opt = {
//                    userIds: { name: 'Test User', email: 'text@example.com' },
//                    passphrase: 'secret',
//                    unlocked: true
//                    };
//                    openpgp.generateKey(opt).then(function(newKey) {
//                        expect(keyGenStub.withArgs({
//                        userIds: ['Test User <text@example.com>'],
//                        passphrase: 'secret',
//                        numBits: 2048,
//                        unlocked: true
//                        }).calledOnce).to.be.true;
//                        expect(newKey.key).to.exist;
//                        expect(newKey.privateKeyArmored).to.exist;
//                        expect(newKey.publicKeyArmored).to.exist;
//                        done();
//                    });
//                });

//                it('should work for no params', function(done) {
//                    openpgp.generateKey().then(function(newKey) {
//                        expect(keyGenStub.withArgs({
//                        userIds: [],
//                        passphrase: undefined,
//                        numBits: 2048,
//                        unlocked: false
//                        }).calledOnce).to.be.true;
//                        expect(newKey.key).to.exist;
//                        done();
//                    });
//                });

            
            }
            
            
            TEST(aes_encrypt_test) {
                {
                    auto openpgp = ProtonMail::OpenPgpImpl::create_instance();
                    auto encrypted = openpgp->encrypt_message_single_key(pub_key, plaintext, "", "", false);
                    auto spited = openpgp->split_message(encrypted);
                    
                    auto out = openpgp->decrypt_attachment_single_key(spited.key_package, spited.data_package, priv_key, passphrase);
                    std::string output(out.begin(), out.end());
                    VERIFY_ARE_EQUAL(output, plaintext);
                    auto combined = openpgp->combine_packages(spited.key_package, spited.data_package);
                    auto out1 = openpgp->decrypt_message_single_key(combined, priv_key, passphrase);
                    VERIFY_ARE_EQUAL(out1, plaintext);
                    
                }
                
                
                
                //                it('should encrypt and decrypt with one password', function(done) {
                //                    var encOpt = {
                //                    data: plaintext,
                //                    passwords: password1
                //                    };
                //                    var decOpt = {
                //                    password: password1
                //                    };
                //                    openpgp.encrypt(encOpt).then(function(encrypted) {
                //                        decOpt.message = openpgp.message.readArmored(encrypted.data);
                //                        return openpgp.decrypt(decOpt);
                //                    }).then(function(decrypted) {
                //                        expect(decrypted.data).to.equal(plaintext);
                //                        done();
                //                    });
                //                });
                
            }
            
            
            TEST(encrypt_decrypt_test) {
                
                //'should encrypt and decrypt with one password'
                auto openpgp = ProtonMail::OpenPgpImpl::create_instance();
                auto encrypted= openpgp->encrypt_message_aes(plaintext, password1);
                VERIFY_ARE_NOT_EQUAL(encrypted, "");
                auto decrypted = openpgp->decrypt_message_aes(encrypted, password1);
                VERIFY_ARE_NOT_EQUAL(decrypted, "");
                VERIFY_ARE_EQUAL(decrypted, plaintext);
            }
            
            //            describe('AES encrypt, decrypt', function() {
            //
            //
            //                it('should encrypt and decrypt with two passwords', function(done) {
            //                    var encOpt = {
            //                    data: plaintext,
            //                    passwords: [password1, password2]
            //                    };
            //                    var decOpt = {
            //                    password: password2
            //                    };
            //                    openpgp.encrypt(encOpt).then(function(encrypted) {
            //                        decOpt.message = openpgp.message.readArmored(encrypted.data);
            //                        return openpgp.decrypt(decOpt);
            //                    }).then(function(decrypted) {
            //                        expect(decrypted.data).to.equal(plaintext);
            //                        done();
            //                    });
            //                });
            //
            //                it('should encrypt and decrypt with password and not ascii armor', function(done) {
            //                    var encOpt = {
            //                    data: plaintext,
            //                    passwords: password1,
            //                    armor: false
            //                    };
            //                    var decOpt = {
            //                    password: password1
            //                    };
            //                    openpgp.encrypt(encOpt).then(function(encrypted) {
            //                        decOpt.message = encrypted.message;
            //                        return openpgp.decrypt(decOpt);
            //                    }).then(function(decrypted) {
            //                        expect(decrypted.data).to.equal(plaintext);
            //                        done();
            //                    });
            //                });
            //
            //                it('should encrypt and decrypt with binary data and transferable objects', function(done) {
            //                    openpgp.config.zero_copy = true; // activate transferable objects
            //                    var encOpt = {
            //                    data: new Uint8Array([0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01]),
            //                    passwords: password1,
            //                    armor: false
            //                    };
            //                    var decOpt = {
            //                    password: password1,
            //                    format: 'binary'
            //                    };
            //                    openpgp.encrypt(encOpt).then(function(encrypted) {
            //                        decOpt.message = encrypted.message;
            //                        return openpgp.decrypt(decOpt);
            //                    }).then(function(decrypted) {
            //                        if (openpgp.getWorker()) {
            //                            expect(encOpt.data.byteLength).to.equal(0); // transfered buffer should be empty
            //                        }
            //                        expect(decrypted.data).to.deep.equal(new Uint8Array([0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01]));
            //                        done();
            //                    });
            //                });
            //            });
            //        }
            
            
            
            
        }
    }
}
