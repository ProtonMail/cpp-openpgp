//
//  openpgp_keyrings_test.cpp
//  OpenPGP
//
//  Created by Yanfeng Zhang on 11/10/16.
//  Copyright © 2016 Yanfeng Zhang. All rights reserved.
//


#include "utils_test.h"

#include <openpgp/PGPKey.h>
#include <openpgp/encrypt.h>
#include <openpgp/decrypt.h>
#include <algorithm>
#include <string>
#include <openpgp/pgptime.h>

#include "bridge_impl/open_pgp_impl.hpp"
#include "bridge/open_pgp_key.hpp"


namespace tests {
    namespace open_pgp_tests {
        SUITE(openpgp_keyrings_test)
        {
            auto keySize = 512;
            auto user = "whiteout.test@t-online.de",
            passphrase = "asdf",
            keyId = "f6f60e9b42cdff4c",
            keyFingerP = "5856cef789c3a307e8a1b976f6f60e9b42cdff4c",
            pubkey = "-----BEGIN PGP PUBLIC KEY BLOCK-----" "\n"
            "Version: OpenPGP.js v.1.20131011" "\n"
            "Comment: http://openpgpjs.org" "" "\n"
            "" "\n"
            "xk0EUlhMvAEB/2MZtCUOAYvyLFjDp3OBMGn3Ev8FwjzyPbIF0JUw+L7y2XR5" "\n"
            "RVGvbK88unV3cU/1tOYdNsXI6pSp/Ztjyv7vbBUAEQEAAc0pV2hpdGVvdXQg" "\n"
            "VXNlciA8d2hpdGVvdXQudGVzdEB0LW9ubGluZS5kZT7CXAQQAQgAEAUCUlhM" "\n"
            "vQkQ9vYOm0LN/0wAAAW4Af9C+kYW1AvNWmivdtr0M0iYCUjM9DNOQH1fcvXq" "\n"
            "IiN602mWrkd8jcEzLsW5IUNzVPLhrFIuKyBDTpLnC07Loce1" "\n"
            "=6XMW" "\n"
            "-----END PGP PUBLIC KEY BLOCK-----\n",
            
            privkey = "-----BEGIN PGP PRIVATE KEY BLOCK-----" "\n"
            "Version: OpenPGP.js v.1.20131011" "\n"
            "Comment: http://openpgpjs.org" "\n"
            "" "\n"
            "xcBeBFJYTLwBAf9jGbQlDgGL8ixYw6dzgTBp9xL/BcI88j2yBdCVMPi+8tl0" "\n"
            "eUVRr2yvPLp1d3FP9bTmHTbFyOqUqf2bY8r+72wVABEBAAH+AwMIhNB4ivtv" "\n"
            "Y2xg6VeMcjjHxZayESHACV+nQx5Tx6ev6xzIF1Qh72fNPDppLhFSFOuTTMsU" "\n"
            "kTN4c+BVYt29spH+cA1jcDAxQ2ULrNAXo+hheOqhpedTs8aCbcLFkJAS16hk" "\n"
            "YSk4OnJgp/z24rVju1SHRSFbgundPzmNgXeX9e8IkviGhhQ11Wc5YwVkx03t" "\n"
            "Z3MdDMF0jyhopbPIoBdyJB0dhvBh98w3JmwpYh9wjUA9MBHD1tvHpRmSZ3BM" "\n"
            "UCmATn2ZLWBRWiYqFbgDnL1GM80pV2hpdGVvdXQgVXNlciA8d2hpdGVvdXQu" "\n"
            "dGVzdEB0LW9ubGluZS5kZT7CXAQQAQgAEAUCUlhMvQkQ9vYOm0LN/0wAAAW4" "\n"
            "Af9C+kYW1AvNWmivdtr0M0iYCUjM9DNOQH1fcvXqIiN602mWrkd8jcEzLsW5" "\n"
            "IUNzVPLhrFIuKyBDTpLnC07Loce1" "\n"
            "=ULta" "\n"
            "-----END PGP PRIVATE KEY BLOCK-----\n",
            keyId2 = "ba993fc2aee18a3a",
            keyFingerP2 = "560b7a7f3f9ab516b233b299ba993fc2aee18a3a",
            subkeyId2 = "f47c5210a8cc2740",
            subkeyFingerP2 = "2a20c371141e000833848d85f47c5210a8cc2740",
            pubkey2 = "-----BEGIN PGP PUBLIC KEY BLOCK-----" "\n"
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
            "-----END PGP PUBLIC KEY BLOCK-----" "\n",
            user3 = "plain@email.org",
            keyFingerP3 = "f9972bf320a86a93c6614711ed241e1de755d53c",
            pubkey3 = "-----BEGIN PGP PUBLIC KEY BLOCK-----" "\n"
            "" "\n"
            "xo0EVe6wawEEAKG4LDE9946jdvvbfVTF9qWtOyxHYjb40z7hgcZsPEGd6QfN" "\n"
            "XbfNJBeQ5S9j/2jRu8NwBgdXIpMp4QwB2Q/cEp1rbw5kUVuRbhfsb2BzuiBr" "\n"
            "Q5jHa5oZSGbbLWRoOXTvJH8VE2gbKSj/km1VaXzq2Qmv+YIHxav1it7vNmg5" "\n"
            "E2kBABEBAAHND3BsYWluQGVtYWlsLm9yZ8K1BBABCAApBQJV7rBrBgsJCAcD" "\n"
            "AgkQ7SQeHedV1TwEFQgCCgMWAgECGQECGwMCHgEAAGJmBACVJPoFtW96UkIW" "\n"
            "GX1bgW99c4K87Me+5ZCHqPOdXFpRinAPBdJT9vkBWLb/aOQQCDWJvdVXKFLD" "\n"
            "FCbSBjcohR71n6145F5im8b0XzXnKh+MRRv/0UHiHGtB/Pkg38jbLeXbVfCM" "\n"
            "9JJm+s+PFef+8wN84sEtD/MX2cj61teuPf2VEs6NBFXusGsBBACoJW/0y5Ea" "\n"
            "FH0nJOuoenrEBZkFtGbdwo8A4ufCCrm9ppFHVVnw4uTPH9dOjw8IAnNy7wA8" "\n"
            "8yZCkreQ491em09knR7k2YdJccWwW8mGRILHQDDEPetZO1dSVW+MA9X7Pcle" "\n"
            "wbFEHCIkWEgymn3zenie1LXIljPzizHje5vWBrSlFwARAQABwp8EGAEIABMF" "\n"
            "AlXusGsJEO0kHh3nVdU8AhsMAACB2AP/eRJFAVTyiP5MnMjsSBuNMNBp1X0Y" "\n"
            "+RrWDpO9H929+fm9oFTedohf/Ja5w9hsRk2VzjLOXe/uHdrcgaBmAdFunbvv" "\n"
            "IWneczohBvLOarevZj1J+H3Ej/DVF2W7kJZLpvPfh7eo0biClS/GQUVw1rlE" "\n"
            "ph10hhUaSJ326LsFJccT3jk=" "\n"
            "=4jat" "\n"
            "-----END PGP PUBLIC KEY BLOCK-----" "\n";
            
            
            
            
            TEST(generate_key_test) {
                auto pgp = OpenPgpImpl();
                pgp.gen
                
            }
            
        }
        
        
    }
}
