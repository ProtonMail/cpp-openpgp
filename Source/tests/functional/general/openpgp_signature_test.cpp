//
//  openpgp_signature_test.cpp
//  OpenPGP
//
//  Created by Yanfeng Zhang on 8/28/17.
//  Copyright © 2017 Yanfeng Zhang. All rights reserved.
//

#include "utils_test.h"

#include <algorithm>
#include <string>

#include <openpgp/PGPKey.h>
#include <openpgp/openpgp.h>
#include <openpgp/PGPCleartextSignature.h>
#include <openpgp/PGPMessage.h>
#include <openpgp/encrypt.h>
#include <openpgp/decrypt.h>
#include <openpgp/verify.h>
#include <openpgp/sign.h>
#include <openpgp/pgptime.h>
#include <openpgp/private_key.h>
#include <openpgp/pgptime.h>

#include "bridge_impl/open_pgp_impl.hpp"
#include "bridge/open_pgp_key.hpp"

#include "bridge/open_pgp.hpp"

using namespace ProtonMail::pgp;

namespace tests {
    namespace open_pgp_tests {
        const std::string priv_key_arm1 =
        "-----BEGIN PGP PRIVATE KEY BLOCK-----" "\n"
        "Version: GnuPG v1.4.11 (GNU/Linux)" "\n"
        "" "\n"
        "lQHhBFERnrMRBADmM0hIfkI3yosjgbWo9v0Lnr3CCE+8KsMszgVS+hBu0XfGraKm" "\n"
        "ivcA2aaJimHqVYOP7gEnwFAxHBBpeTJcu5wzCFyJwEYqVeS3nnaIhBPplSF14Duf" "\n"
        "i6bB9RV7KxVAg6aunmM2tAutqC+a0y2rDaf7jkJoZ9gWJe2zI+vraD6fiwCgxvHo" "\n"
        "3IgULB9RqIqpLoMgXfcjC+cD/1jeJlKRm+n71ryYwT/ECKsspFz7S36z6q3XyS8Q" "\n"
        "QfrsUz2p1fbFicvJwIOJ8B20J/N2/nit4P0gBUTUxv3QEa7XCM/56/xrGkyBzscW" "\n"
        "AzBoy/AK9K7GN6z13RozuAS60F1xO7MQc6Yi2VU3eASDQEKiyL/Ubf/s/rkZ+sGj" "\n"
        "yJizBACtwCbQzA+z9XBZNUat5NPgcZz5Qeh1nwF9Nxnr6pyBv7tkrLh/3gxRGHqG" "\n"
        "063dMbUk8pmUcJzBUyRsNiIPDoEUsLjY5zmZZmp/waAhpREsnK29WLCbqLdpUors" "\n"
        "c1JJBsObkA1IM8TZY8YUmvsMEvBLCCanuKpclZZXqeRAeOHJ0v4DAwK8WfuTe5B+" "\n"
        "M2BOOeZbN8BpfiA1l//fMMHLRS3UvbLBv4P1+4SyvhyYTR7M76Q0xPc03MFOWHL+" "\n"
        "S9VumbQWVGVzdDIgPHRlc3QyQHRlc3QuY29tPohiBBMRAgAiBQJREZ6zAhsDBgsJ" "\n"
        "CAcDAgYVCAIJCgsEFgIDAQIeAQIXgAAKCRARJ5QDyxae+MXNAKCzWSDR3tMrTrDb" "\n"
        "TAri73N1Xb3j1ACfSl9y+SAah2q7GvmiR1+6+/ekqJGdAVgEURGesxAEANlpMZjW" "\n"
        "33jMxlKHDdyRFXtKOq8RreXhq00plorHbgz9zFEWm4VF53+E/KGnmHGyY5Cy8TKy" "\n"
        "ZjaueZZ9XuG0huZg5If68irFfNZtxdA26jv8//PdZ0Uj+X6J3RVa2peMLDDswTYL" "\n"
        "OL1ZO1fxdtDD40fdAiIZ1QyjwEG0APtz41EfAAMFBAC5/dtgBBPtHe8UjDBaUe4n" "\n"
        "NzHuUBBp6XE+H7eqHNFCuZAJ7yqJLGVHNIaQR419cNy08/OO/+YUQ7rg78LxjFiv" "\n"
        "CH7IzhfU+6yvELSbgRMicY6EnAP2GT+b1+MtFNa3lBGtBHcJla52c2rTAHthYZWk" "\n"
        "fT5R5DnJuQ2cJHBMS9HWyP4DAwK8WfuTe5B+M2C7a/YJSUv6SexdGCaiaTcAm6g/" "\n"
        "PvA6hw/FLzIEP67QcQSSTmhftQIwnddt4S4MyJJH3U4fJaFfYQ1zCniYJohJBBgR" "\n"
        "AgAJBQJREZ6zAhsMAAoJEBEnlAPLFp74QbMAn3V4857xwnO9/+vzIVnL93W3k0/8" "\n"
        "AKC8omYPPomN1E/UJFfXdLDIMi5LoA==" "\n"
        "=LSrW" "\n"
        "-----END PGP PRIVATE KEY BLOCK-----";
        
        const std::string pub_key_arm1 =
        "-----BEGIN PGP PUBLIC KEY BLOCK-----" "\n"
        "Version: GnuPG v1.4.11 (GNU/Linux)" "\n"
        "" "\n"
        "mQGiBFERlw4RBAD6Bmcf2w1dtUmtCLkdxeqZLArk3vYoQAjdibxA3gXVyur7fsWb" "\n"
        "ro0jVbBHqOCtC6jDxE2l52NP9+tTlWeVMaqqNvUE47LSaPq2DGI8Wx1Rj6bF3mTs" "\n"
        "obYEwhGbGh/MhJnME9AHODarvk8AZbzo0+k1EwrBWF6dTUBPfqO7rGU2ewCg80WV" "\n"
        "x5pt3evj8rRK3jQ8SMKTNRsD/1PhTdxdZTdXARAFzcW1VaaruWW0Rr1+XHKKwDCz" "\n"
        "i7HE76SO9qjnQfZCZG75CdQxI0h8GFeN3zsDqmhob2iSz2aJ1krtjM+iZ1FBFd57" "\n"
        "OqCV6wmk5IT0RBN12ZzMS19YvzN/ONXHrmTZlKExd9Mh9RKLeVNw+bf6JsKQEzcY" "\n"
        "JzFkBACX9X+hDYchO/2hiTwx4iOO9Fhsuh7eIWumB3gt+aUpm1jrSbas/QLTymmk" "\n"
        "uZuQVXI4NtnlvzlNgWv4L5s5RU5WqNGG7WSaKNdcrvJZRC2dgbUJt04J5CKrWp6R" "\n"
        "aIYal/81Ut1778lU01PEt563TcQnUBlnjU5OR25KhfSeN5CZY7QUVGVzdCA8dGVz" "\n"
        "dEB0ZXN0LmNvbT6IYgQTEQIAIgUCURGXDgIbAwYLCQgHAwIGFQgCCQoLBBYCAwEC" "\n"
        "HgECF4AACgkQikDlZK/UvLSspgCfcNaOpTg1W2ucR1JwBbBGvaERfuMAnRgt3/rs" "\n"
        "EplqEakMckCtikEnpxYe" "\n"
        "=b2Ln" "\n"
        "-----END PGP PUBLIC KEY BLOCK-----" "\n";
        
        const std::string msg_arm1 =
        "-----BEGIN PGP MESSAGE-----" "\n"
        "Version: GnuPG v1.4.11 (GNU/Linux)" "\n"
        "" "\n"
        "hQEOA1N4OCSSjECBEAP/diDJCQn4e88193PgqhbfAkohk9RQ0v0MPnXpJbCRTHKO" "\n"
        "8r9nxiAr/TQv4ZOingXdAp2JZEoE9pXxZ3r1UWew04czxmgJ8FP1ztZYWVFAWFVi" "\n"
        "Tj930TBD7L1fY/MD4fK6xjEG7z5GT8k4tn4mLm/PpWMbarIglfMopTy1M/py2cID" "\n"
        "/2Sj7Ikh3UFiG+zm4sViYc5roNbMy8ixeoKixxi99Mx8INa2cxNfqbabjblFyc0Z" "\n"
        "BwmbIc+ZiY2meRNI5y/tk0gRD7hT84IXGGl6/mH00bsX/kkWdKGeTvz8s5G8RDHa" "\n"
        "Za4HgLbXItkX/QarvRS9kvkD01ujHfj+1ZvgmOBttNfP0p8BQLIICqvg1eYD9aPB" "\n"
        "+GtOZ2F3+k5VyBL5yIn/s65SBjNO8Fqs3aL0x+p7s1cfUzx8J8a8nWpqq/qIQIqg" "\n"
        "ZJH6MZRKuQwscwH6NWgsSVwcnVCAXnYOpbHxFQ+j7RbF/+uiuqU+DFH/Rd5pik8b" "\n"
        "0Dqnp0yfefrkjQ0nuvubgB6Rv89mHpnvuJfFJRInpg4lrHwLvRwdpN2HDozFHcKK" "\n"
        "aOU=" "\n"
        "=4iGt" "\n"
        "-----END PGP MESSAGE-----" "\n";
        
        const std::string priv_key_arm2 =
        "-----BEGIN PGP PRIVATE KEY BLOCK-----" "\n"
        "Version: GnuPG v2.0.19 (GNU/Linux)" "\n"
        "" "\n"
        "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" "\n"
        "=lw5e" "\n"
        "-----END PGP PRIVATE KEY BLOCK-----" "\n";
        
        const std::string pub_key_arm2 =
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
        
        const std::string pub_key_arm3 =
        "-----BEGIN PGP PUBLIC KEY BLOCK-----" "\n"
        "Version: GnuPG v2.0.19 (GNU/Linux)" "\n"
        "" "\n"
        "mQENBFKV0FUBCACtZliApy01KBGbGNB36YGH4lpr+5KoqF1I8A5IT0YeNjyGisOk" "\n"
        "WsDsUzOqaNvgzQ82I3MY/jQV5rLBhH/6LiRmCA16WkKcqBrHfNGIxJ+Q+ofVBHUb" "\n"
        "aS9ClXYI88j747QgWzirnLuEA0GfilRZcewII1pDA/G7+m1HwV4qHsPataYLeboq" "\n"
        "hPA3h1EVVQFMAcwlqjOuS8+weHQRfNVRGQdRMm6H7166PseDVRUHdkJpVaKFhptg" "\n"
        "rDoNI0lO+UujdqeF1o5tVZ0j/s7RbyBvdLTXNuBbcpq93ceSWuJPZmi1XztQXKYe" "\n"
        "y0f+ltgVtZDEc7TGV5WDX9erRECCcA3+s7J3ABEBAAG0G0pTIENyeXB0byA8ZGlm" "\n"
        "ZmllQGhvbWUub3JnPokBPwQTAQIAKQUCUpXQVQIbAwUJCWYBgAcLCQgHAwIBBhUI" "\n"
        "AgkKCwQWAgMBAh4BAheAAAoJENvyI+hwU030yRAIAKX/mGEgi/miqasbbQoyK/CS" "\n"
        "a7sRxgZwOWQLdi2xxpE5V4W4HJIDNLJs5vGpRN4mmcNK2fmJAh74w0PskmVgJEhP" "\n"
        "dFJ14UC3fFPq5nbqkBl7hU0tDP5jZxo9ruQZfDOWpHKxOCz5guYJ0CW97bz4fChZ" "\n"
        "NFDyfU7VsJQwRIoViVcMCipP0fVZQkIhhwpzQpmVmN8E0a6jWezTZv1YpMdlzbEf" "\n"
        "H79l3StaOh9/Un9CkIyqEWdYiKvIYms9nENyehN7r/OKYN3SW+qlt5GaL+ws+N1w" "\n"
        "6kEZjPFwnsr+Y4A3oHcAwXq7nfOz71USojSmmo8pgdN8je16CP98vw3/k6TncLS5" "\n"
        "AQ0EUpXQVQEIAMEjHMeqg7B04FliUFWr/8C6sJDb492MlGAWgghIbnuJfXAnUGdN" "\n"
        "oAzn0S+n93Y/qHbW6YcjHD4/G+kK3MuxthAFqcVjdHZQXK0rkhXO/u1co7v1cdtk" "\n"
        "OTEcyOpyLXolM/1S2UYImhrml7YulTHMnWVja7xu6QIRso+7HBFT/u9D47L/xXrX" "\n"
        "MzXFVZfBtVY+yoeTrOY3OX9cBMOAu0kuN9eT18Yv2yi6XMzP3iONVHtl6HfFrAA7" "\n"
        "kAtx4ne0jgAPWZ+a8hMy59on2ZFs/AvSpJtSc1kw/vMTWkyVP1Ky20vAPHQ6Ej5q" "\n"
        "1NGJ/JbcFgolvEeI/3uDueLjj4SdSIbLOXMAEQEAAYkBJQQYAQIADwUCUpXQVQIb" "\n"
        "DAUJCWYBgAAKCRDb8iPocFNN9NLkB/wO4iRxia0zf4Kw2RLVZG8qcuo3Bw9UTXYY" "\n"
        "lI0AutoLNnSURMLLCq6rcJ0BCXGj/2iZ0NBxZq3t5vbRh6uUv+hpiSxK1nF7AheN" "\n"
        "4aAAzhbWx0UDTF04ebG/neE4uDklRIJLhif6+Bwu+EUeTlGbDj7fqGSsNe8g92w7" "\n"
        "1e41rF/9CMoOswrKgIjXAou3aexogWcHvKY2D+1q9exORe1rIa1+sUGl5PG2wsEs" "\n"
        "znN6qtN5gMlGY1ofWDY+I02gO4qzaZ/FxRZfittCw7v5dmQYKot9qRi2Kx3Fvw+h" "\n"
        "ivFBpC4TWgppFBnJJnAsFXZJQcejMW4nEmOViRQXY8N8PepQmgsu" "\n"
        "=ummy" "\n"
        "-----END PGP PUBLIC KEY BLOCK-----" "\n";
        
        
        const std::string pub_revoked =
        "-----BEGIN PGP PUBLIC KEY BLOCK-----" "\n"
        "Version: GnuPG v2.0.19 (GNU/Linux)" "\n"
        "" "\n"
        "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" "\n"
        "pMiJM+NJAQ==" "\n"
        "=ok+o" "\n"
        "-----END PGP PUBLIC KEY BLOCK-----" "\n";
        
        
        const std::string pub_v3 =
        "-----BEGIN PGP PUBLIC KEY BLOCK-----" "\n"
        "Version: SKS 1.1.3" "\n"
        "" "\n"
        "mQENAy9J/w4AAAEIALBDDD4vWqG/Jg59ghhMYAa+E7ECCTv2At8hxsM5cMP8P9sMLjs+GMfD" "\n"
        "IdQSOqlQXbunYADvM1l/h2fOuUMoYFIIGaUsO5Daxvd9uWceM4DVzhXMeJZb9wc5jEJEF21+" "\n"
        "qidKj5OGsMyTrg++mn4Gh/aFXvvy3N3KWaQpPfNi3NRZUpNLz0IlfbXVBQGD6reLoxPptJun" "\n"
        "NqpClyRiesgq8HCscmB2oQo+b9KzSSgzU9qQJA4SljMYVmJ2sDE/sjREI8iKL8lIgUMhJG9q" "\n"
        "NggWjuxFTpVcGKkuQFJIvdL+UhTVvEBuqw6n4cmFAzfZ/AInJM032qLtsaIf5begFKI3up0A" "\n"
        "BRGJARUDBSAxm7HC5begFKI3up0BAbdDB/0TOcI0ec+OPxC5RTZAltgIgyUc0yOjHoTD/yBh" "\n"
        "WjZdQ9YVrLGMWTW4fjhm4rFnppVZKS/N71bwI76SnN9zO4pPfx86aQPR7StmSLJxB+cfh2GL" "\n"
        "gudJoG9ifhJWdNYMUD/yhA0TpJkdHMD5yTDE5Ce/PqKLviiX9C5MPW0AT1MDvafQlzeUXfb5" "\n"
        "1a71vQNPw7W1NBAVZRwztm7TNUaxWMFuOmUtOJpq4F/qDQTIHW2zGPJvl47rpf6JSiyIyU70" "\n"
        "l0deiQcZOXPC80tgInhNoBrz3zbEXhXRJo1fHkr2YSLclpJaoUOHsPxoyrNB28ASL5ZknPwI" "\n"
        "Zx3+cFxaGpRprfSdtCFKb2huIEEuIFBlcnJ5IDxwZXJyeUBwaG9lbml4Lm5ldD6JARUDBRAv" "\n"
        "Sf8k5begFKI3up0BAcbGB/0eLod2qrQxoE2/RUWQtqklOPUj/p/ZTmvZm8BgsdIflb0AMeey" "\n"
        "9o8AbxyAgA3pcrcCjcye79M1Ma2trEvRksvs8hViuq3BXXjDbjPZi3wTtKSvbAC022OV52Sb" "\n"
        "8/sgiTGp7xC8QMqS8w4ZeKoxJGh1TVMYrevUA8a2Rr5aDqrR3EA4rifSHwkVjJWOPF69xiKt" "\n"
        "IVA0LcYJvGsPOQCf2ag+nOcnDrF4dvcmg6XZ/RyLepve+1qkhXsA/oq+yHoaqWfe+bwgssk/" "\n"
        "qw1aEUk7Di8x7vY+cfjvWaazcYGw8kkIwSSqqIq0pkKFz2xDDfSaDJl6OW/2GUK0wDpJmYZo" "\n"
        "PN40iJUDBRAvSgDsU5OkROGu2G8BAeUqBACbC45t4+wYxWCxxp81pkFRb8RWBvEvbXI+Spwd" "\n"
        "4NcKs8jc5OVC8V02yiq4KbKFDRxdw2OWpUCSRAJe1gjsfFrZ+2RivpKk06kbAYthES03MjXg" "\n"
        "cfcV3z2d7IWanJzdcOlzsHzPe1+RoUAaqBjvcqPRCGRlk0ogkYHyWYxElc6574iVAwUQL9iL" "\n"
        "CXr7ES8bepftAQGPywP/d9GSpEmS7LLIqazl4rgN1nkXN5KqduiH8Whu3xcBrdOAn7IYnGTp" "\n"
        "O+Ag4qwKKH+y/ke9CeZL6AnrU9c0pux150dHsDeHtpTPyInkjgKI7BofprydvpiFNd0nlAi4" "\n"
        "J4SAEYr3q92Qn/IiKpnLgo6Ls/GFb7q6y1O/2LL8PC2zrYU=" "\n"
        "=eoGb" "\n"
        "-----END PGP PUBLIC KEY BLOCK-----" "\n";
        
        
        SUITE(openpgo_signature_test)
        {//Testing signature checking on CAST5-enciphered message
            
            TEST(checkint_cast5_enciphered_message) {  //doesnt support yet
                auto pgp = ProtonMail::OpenPgpImpl::create_instance();
                //decrypt message
                //                auto decrypted = pgp->decrypt_message_single_key(msg_arm1,
                //                                                                 priv_key_arm1,
                //                                                                 "abcd");
                //                //verify signature
                //
                //                std::cout << decrypted << std::endl;
                
                
                //auto priv_key = openpgp.key.readArmored(priv_key_arm1).keys[0];
                //var pub_key = openpgp.key.readArmored(pub_key_arm1).keys[0];
                //            var msg = openpgp.message.readArmored(msg_arm1);
                //            priv_key.decrypt("abcd");
                //
                //            openpgp.decrypt({ privateKey: priv_key, publicKeys:[pub_key], message:msg }).then(function(decrypted) {
                //                expect(decrypted.data).to.exist;
                //                expect(decrypted.signatures[0].valid).to.be.true;
                //                expect(decrypted.signatures[0].signature.packets.length).to.equal(1);
                //                done();
                //            });
            }
            
            
            TEST(testing_GnuPG_stripped_key_extensions) {
                // exercises the GnuPG s2k type 1001 extension:
                // the secrets on the primary key have been stripped.
                std::string priv_key_gnupg_armored =
                "-----BEGIN PGP PRIVATE KEY BLOCK-----" "\n"
                "Version: GnuPG v1.4.11 (GNU/Linux)" "\n"
                "" "\n"
                "lQGqBFERnrMRBADmM0hIfkI3yosjgbWo9v0Lnr3CCE+8KsMszgVS+hBu0XfGraKm" "\n"
                "ivcA2aaJimHqVYOP7gEnwFAxHBBpeTJcu5wzCFyJwEYqVeS3nnaIhBPplSF14Duf" "\n"
                "i6bB9RV7KxVAg6aunmM2tAutqC+a0y2rDaf7jkJoZ9gWJe2zI+vraD6fiwCgxvHo" "\n"
                "3IgULB9RqIqpLoMgXfcjC+cD/1jeJlKRm+n71ryYwT/ECKsspFz7S36z6q3XyS8Q" "\n"
                "QfrsUz2p1fbFicvJwIOJ8B20J/N2/nit4P0gBUTUxv3QEa7XCM/56/xrGkyBzscW" "\n"
                "AzBoy/AK9K7GN6z13RozuAS60F1xO7MQc6Yi2VU3eASDQEKiyL/Ubf/s/rkZ+sGj" "\n"
                "yJizBACtwCbQzA+z9XBZNUat5NPgcZz5Qeh1nwF9Nxnr6pyBv7tkrLh/3gxRGHqG" "\n"
                "063dMbUk8pmUcJzBUyRsNiIPDoEUsLjY5zmZZmp/waAhpREsnK29WLCbqLdpUors" "\n"
                "c1JJBsObkA1IM8TZY8YUmvsMEvBLCCanuKpclZZXqeRAeOHJ0v4DZQJHTlUBtBZU" "\n"
                "ZXN0MiA8dGVzdDJAdGVzdC5jb20+iGIEExECACIFAlERnrMCGwMGCwkIBwMCBhUI" "\n"
                "AgkKCwQWAgMBAh4BAheAAAoJEBEnlAPLFp74xc0AoLNZINHe0ytOsNtMCuLvc3Vd" "\n"
                "vePUAJ9KX3L5IBqHarsa+aJHX7r796SokZ0BWARREZ6zEAQA2WkxmNbfeMzGUocN" "\n"
                "3JEVe0o6rxGt5eGrTSmWisduDP3MURabhUXnf4T8oaeYcbJjkLLxMrJmNq55ln1e" "\n"
                "4bSG5mDkh/ryKsV81m3F0DbqO/z/891nRSP5fondFVral4wsMOzBNgs4vVk7V/F2" "\n"
                "0MPjR90CIhnVDKPAQbQA+3PjUR8AAwUEALn922AEE+0d7xSMMFpR7ic3Me5QEGnp" "\n"
                "cT4ft6oc0UK5kAnvKoksZUc0hpBHjX1w3LTz847/5hRDuuDvwvGMWK8IfsjOF9T7" "\n"
                "rK8QtJuBEyJxjoScA/YZP5vX4y0U1reUEa0EdwmVrnZzatMAe2FhlaR9PlHkOcm5" "\n"
                "DZwkcExL0dbI/gMDArxZ+5N7kH4zYLtr9glJS/pJ7F0YJqJpNwCbqD8+8DqHD8Uv" "\n"
                "MgQ/rtBxBJJOaF+1AjCd123hLgzIkkfdTh8loV9hDXMKeJgmiEkEGBECAAkFAlER" "\n"
                "nrMCGwwACgkQESeUA8sWnvhBswCfdXjznvHCc73/6/MhWcv3dbeTT/wAoLyiZg8+" "\n"
                "iY3UT9QkV9d0sMgyLkug" "\n"
                "=GQsY" "\n"
                "-----END PGP PRIVATE KEY BLOCK-----" "\n";
                
                
                PGPSecretKey private_key(priv_key_gnupg_armored);
                auto pubkey = pub_key_arm1;
                PGPPublicKey pub_key(pubkey); //get pub key need to add function
                auto msgArm1 = msg_arm1;
                PGPMessage msg(msgArm1);
                
                //                auto tag7 = private_key.tag7(0);
                //                uint8_t packet = 0;
                //                std::vector <std::string> session_key_mpi;
                //                for(Packet::Ptr const & p : msg.get_packets()){
                //                    packet = p->get_tag();
                //                    std::cout << packet << std::endl;
                //
                ////                    if ((p -> get_tag() == 1) || (p -> get_tag() == 3)){
                ////                        data = p -> raw();
                ////                        packet = p -> get_tag();
                ////                        if (packet == 1)
                ////                        {
                ////                            if (p -> get_tag() == 1) {
                ////                                Tag1 tag1(data);
                ////                                sec = find_decrypting_key(pri, tag1.get_keyid(), true);
                ////                                if (!sec){
                ////                                    continue;
                ////                                }
                ////                                pka = tag1.get_pka();
                ////                                session_key_mpi = tag1.get_mpi();
                ////                                break;
                ////                            }
                ////                        }
                ////                    }
                //                }
                
                // get session key
                //                session_key = zero + pka_decrypt(pka, session_key_mpi, pri_mpi, pub_mpi);     // symmetric algorithm, session key, 2 octet checksum wrapped in EME_PKCS1_ENCODE
                //                session_key = EME_PKCS1v1_5_DECODE(session_key);                              // remove EME_PKCS1 encoding
                //                sym = session_key[0];                                                         // get symmetric algorithm
                //                std::string checksum = session_key.substr(session_key.size() - 2, 2);         // get 2 octet checksum
                //                session_key = session_key.substr(1, session_key.size() - 3);                  // remove both from session key
                //                uint16_t sum = 0;
                //                for(char & c : session_key){                                                  // calculate session key checksum
                //                    sum += static_cast <uint8_t> (c);
                //                }
                //                if (unhexlify(makehex(sum, 4)) != checksum){                                  // check session key checksums
                //                    throw ProtonMail::pgp_exception(ProtonMail::PM_DECRYPT_SESSION_SUMCHECK_NOT_MATCH, "Error: Calculated session key checksum does not match given checksum.");
                //                }
                
                //                sec.reset();
                //
                //                return session_key;
                
                
                //                var pub_key = openpgp.key.readArmored(pub_key_arm1).keys[0];
                //                var msg = openpgp.message.readArmored(msg_arm1);
                //
                //                priv_key_gnupg_ext.subKeys[0].subKey.decrypt("abcd");
                //                msg.decrypt(priv_key_gnupg_ext).then(function(msg) {
                //                    var verified = msg.verify([pub_key]);
                //                    expect(verified).to.exist;
                //                    expect(verified).to.have.length(1);
                //                    expect(verified[0].valid).to.be.true;
                //                    expect(verified[0].signature.packets.length).to.equal(1);
                //                    done();
                //                });
            };
            
            TEST(Verify_V4_signature_Hash)
            { //: SHA1. PK: RSA. Signature Type: 0x00 (binary document)
                std::string signedArmor =
                "-----BEGIN PGP MESSAGE-----" "\n"
                "Version: GnuPG v2.0.19 (GNU/Linux)" "\n"
                "" "\n"
                "owGbwMvMwMT4oOW7S46CznTGNeZJLCWpFSVBU3ZGF2fkF5Uo5KYWFyemp3LlAUUV" "\n"
                "cjLzUrneTp3zauvaN9O26L9ZuOFNy4LXyydwcXXMYWFgZGJgY2UCaWXg4hSAmblK" "\n"
                "nPmfsXYxd58Ka9eVrEnSpzilr520fXBrJsf2P/oTqzTj3hzyLG0o3TTzxFfrtOXf" "\n"
                "cw6U57n3/Z4X0pEZ68C5/o/6NpPICD7fuEOz3936raZ6wXGzueY8pfPnVjY0ajAc" "\n"
                "PtJzvvqj+ubYaT1sK9wWhd9lL3/V+9Zuua9QjOWC22buchsCroh8fLoZAA==" "\n"
                "=VH8F" "\n"
                "-----END PGP MESSAGE-----" "\n";
                PGPMessage msg(signedArmor);
                auto pubkey = pub_key_arm2;
                auto pub_key = std::make_shared<PGPPublicKey>(pubkey);
                bool check = msg.verify(pub_key);
                VERIFY_IS_TRUE(check);
            }
            
            TEST(Verify_V3_signature)
            {//. Hash: MD5. PK: RSA. Signature Type: 0x01 (text document)" "\n"
                std::string signedArmor =
                "-----BEGIN PGP MESSAGE-----" "\n"
                "Version: GnuPG v2.0.19 (GNU/Linux)" "\n"
                "" "\n"
                "owGbwMvMyMj4oOW7S46CznTG09YlLCWpFSVBU47xFGfkF5Uo5KYWFyemp/Jy5QGF" "\n"
                "FXIy84DMt1PnvNq69s20LfpvFm5407Lg9fIJvFy8XJ0MU5lZGUFa4eYxxiQz/6+/" "\n"
                "aFt4/6+e76O6s1afLi65emmK9xsdh7Mr60UnT2UN0LwocWnT7t/nOMJubnypvzTu" "\n"
                "aPJyvm9TTpobW/O+P1n2THLS4UCvWt12Oa2lJ04GLwk/bDF1u+8ZpfPCpsxLVzcs" "\n"
                "ZGtbq/f23XxV/jkL47hr3s3Ic4yoZTW4oZO27GYf37TPp9L3VboCAA==" "\n"
                "=pa6B" "\n"
                "-----END PGP MESSAGE-----" "\n";
                
                PGPMessage msg(signedArmor);
                auto pubkey = pub_key_arm2;
                auto pub_key = std::make_shared<PGPPublicKey>(pubkey);
                bool check = msg.verify(pub_key);
                VERIFY_IS_TRUE(check);
            }
            
            TEST(Verify_signature_of_signed_and_encrypted_message_from_GPG2_with_openpgp_decrypt) {
                std::string msg_armor =
                "-----BEGIN PGP MESSAGE-----" "\n"
                "Version: GnuPG v2.0.19 (GNU/Linux)" "\n"
                "" "\n"
                "hIwD4IT3RGwgLJcBBADEBdm+GEW7IV1K/Bykg0nB0WYO08ai7/8/+Y/O9xu6RiU0" "\n"
                "q7/jWuKms7kSjw9gxMCjf2dGnAuT4Cg505Kj5WfeBuHh618ovO8qo4h0qHyp1/y3" "\n"
                "o1P0IXPAb+LGJOeO7DyM9Xp2AOBiIKOVWzFTg+MBZOc+XZEVx3FioHfm9SSDudLA" "\n"
                "WAEkDakCG6MRFj/7SmOiV8mQKH+YPMKT69eDZW7hjINabrpM2pdRU7c9lC7CMUBx" "\n"
                "Vj7wZsQBMASSC8f2rhpGA2iKvYMsmW3g9R1xkvj1MXWftSPUS4jeNTAgEwvvF6Af" "\n"
                "cP+OYSXKlTbwfEr73ES2O3/IFE9sHRjPqWaxWuv4DDQ5YfIxE54C1aE8Aq5/QaIH" "\n"
                "v38TUSia0yEMCc/tJd58DikkT07AF162tcx9Ro0ZjhudyuvUyXIfPfxA+XWR2pdz" "\n"
                "ifxyV4zia9RvaCUY8vXGM+gQJ3NNXx2LkZA3kWUEyxFVL1Vl/XUQY0M6U+uccSk4" "\n"
                "eMXm6eyEWDcj0lBRckqKoKo1w/uan11jPuHsnRz6jO9DsuKEz79UDgI=" "\n"
                "=cFi7" "\n"
                "-----END PGP MESSAGE-----" "\n";
                
                std::string plaintext = "short message\nnext line\n한국어/조선말";
                
                PGPMessage esMsg(msg_armor);
                auto pubKeyArm2 = pub_key_arm2;
                PGPPublicKey::Ptr pubKey = std::make_shared<PGPPublicKey>(pubKeyArm2);
                auto privKeyArm2 = priv_key_arm2;
                PGPSecretKey privKey(privKeyArm2);
                std::string plain_text = decrypt_pka(privKey, esMsg, "hello world", false, pubKey);
                VERIFY_ARE_EQUAL(plain_text, plaintext);
            }
            
            TEST(Encrypt_Sign_Verify_test_1) {
                std::string plaintext = "short message\nnext line\n한국어/조선말丰张feng";
                
                auto pubKeyArm2 = pub_key_arm2;
                PGPPublicKey::Ptr pubKey = std::make_shared<PGPPublicKey>(pubKeyArm2);
                auto privKeyArm2 = priv_key_arm2;
                PGPSecretKey::Ptr privKey = std::make_shared<PGPSecretKey>(privKeyArm2);
                
                auto encrypted_pgp = encrypt_pka(*pubKey, plaintext, "", 9, 2, true, privKey, "hello world");

                std::string encrypt_message = encrypted_pgp.write();
                std::cout << encrypt_message << std::endl;
                
                PGPMessage esMsg(encrypt_message);
                std::string plain_text = decrypt_pka(*privKey, esMsg, "hello world", false, pubKey);
                
                std::cout << plain_text << std::endl;
                
                
                std::cout << plaintext << std::endl;
                
                VERIFY_ARE_EQUAL(plain_text, plaintext);
            }
            
            TEST(Verify_signature_of_signed_and_encrypted_message) {
                //from PGP 10.3.0 with openpgp.decrypt
                std::string msg_armor =
                "-----BEGIN PGP MESSAGE-----" "\n"
                "Version: Encryption Desktop 10.3.0 (Build 9307)" "\n"
                "Charset: utf-8" "\n"
                "" "\n"
                "qANQR1DBjAPghPdEbCAslwED/2S4oNvCjO5TdLUMMUuVOQc8fi6c5XIBu7Y09fEX" "\n"
                "Jm/UrkDHVgmPojLGBDF0CYENNZOVrNfpahY7A3r4HPzGucBzCO1uxuUIKjhtNAAM" "\n"
                "mjD939ernjooOZrM6xDuRaX8adG0LSxpNaVJGxXd/EdlmKDJbYDI6aJ5INrUxzAR" "\n"
                "DAqw0sBSAXgRWgiH6IIiAo5y5WFEDEN9sGStaEQT2wd32kX73M4iZuMt/GM2agiB" "\n"
                "sWb7yLcNHiJ/3OnTfDg9+T543kFq9FlwFbwqygO/wm9e/kgMBq0ZsFOfV+GRtXep" "\n"
                "3qNbJsmzGvdqiUHb/+hkdE191jaSVcO/zaMW4N0Vc1IwIEhZ8I9+9bKwusdVhHT5" "\n"
                "MySnhIogv+0Ilag/aY+UiCt+Zcie69T7Eix48fC/VVW5w3INf1T2CMmDm5ZLZFRN" "\n"
                "oyqzb9Vsgu1gS7SCb6qTbnbV9PlSyU4wJB6siX8hz/U0urokT5se3uYRjiV0KbkA" "\n"
                "zl1/r/wCrmwX4Gl9VN9+33cQgYZAlJLsRw8N82GhbVweZS8qwv24GQ==" "\n"
                "=nx90" "\n"
                "-----END PGP MESSAGE-----" "\n";
                
                auto plaintext = "short message\nnext line\n한국어/조선말\n\n";
                
                PGPMessage esMsg(msg_armor);
                auto pubKeyArm2 = pub_key_arm2;
                PGPPublicKey::Ptr pubKey = std::make_shared<PGPPublicKey>(pubKeyArm2);
                auto privKeyArm2 = priv_key_arm2;
                PGPSecretKey privKey(privKeyArm2);
                
                std::string plain_text = decrypt_pka(privKey, esMsg, "hello world", false, pubKey);
                std::string find = "\r\n";
                auto size = find.size();
                for (std::size_t pos = plain_text.find(find); pos!= std::string::npos; pos = plain_text.find(find, pos + 1))
                    plain_text.replace(pos, size, "\n");
                
                VERIFY_ARE_EQUAL(plain_text, plaintext);
            }
            
            TEST(Verify_signed_message_with_two_one_pass_signatures) {
                std::string msg_armor =
                "-----BEGIN PGP MESSAGE-----" "\n"
                "Version: GnuPG v2.0.19 (GNU/Linux)" "\n"
                "" "\n"
                "owGbwMvMwMF4+5Pyi4Jg3y8ME8DcBy3fXXIUdKYzrjFNYilJrSgJmsXDXJyRX1Si" "\n"
                "kJtaXJyYnsqVBxRVyMnMS+V6O3XOq61r30zbov9m4YY3LQteL5/QMYeFgZGDgY2V" "\n"
                "CaSRgYtTAGZiYxYLwySbQk07ptZel6gmjrKyBWsyWdkOG3oscLBdIpXXfDdb6fNv" "\n"
                "8ULN5L1ed+xNo79P2dBotWud6vn7e9dtLJ7o12PunnvEz8gyyvP4/As/los0xsnZ" "\n"
                "H+8ublrhvGtLxJUZuUKZO6QdHq2Nepuw8OrfiMXPBDQXXpV2q11Ze+rD3lndgv/C" "\n"
                "bJQNOhll0J0H839jFvt/16m20h/ZmDoWqJywapnypjdIjcXr+7rJFess40yenV7Q" "\n"
                "2LSu/EX6Aq29x+dv+GPUMfuhTNE3viWWUR4PD6T7XfmdViUwmSf8fkRNUn/t3a2n" "\n"
                "cq46Xr36seCor/OLp0atSZwHrjx2SU5zPLheZn+zw/0d1/YZnD7AEeP9s/Cuycyv" "\n"
                "CZ5HZNKufvB8fsh+dfdSXW0GfqkPfxk36Vw8ufpjaoZDyt2nxxg/6D4KS3UvZzv3" "\n"
                "axdLZ9yd0OJNZv4P501If24W4vTGz6nI7Ser8Yd2PiOvE5MWMT0wLZQ+zPX1sv0/" "\n"
                "s8PvkyWmVM0O0fB/ZSHovHNNPffDg/rWhzOmXQ9/7vTn477F+aWm5sYzJ75/BQA=" "\n"
                "=+L0S" "\n"
                "-----END PGP MESSAGE-----" "\n";
                
                auto plaintext = "short message\nnext line\n한국어/조선말";
                
                PGPMessage sMsg(msg_armor);
                auto pubKeyArm2 = pub_key_arm2;
                PGPPublicKey::Ptr pubKey = std::make_shared<PGPPublicKey>(pubKeyArm2);
                auto pubKeyArm3 = pub_key_arm3;
                pubKey->read(pubKeyArm3);
                
                std::string out = "";
                for(Packet::Ptr const & p : sMsg.get_packets()){
                    if (p -> get_tag() == 11){
                        std::string raw = p -> raw();
                        Tag11 tag11(raw);
                        out += tag11.out(false);
                    }
                }
                VERIFY_ARE_EQUAL(out, plaintext);
                
                auto check = sMsg.verify(pubKey);
                VERIFY_IS_TRUE(check);
            }
            
            
            TEST(Verify_cleartext_signed_message_with_two_signatures) {
                std::string msg_armor =
                "-----BEGIN PGP SIGNED MESSAGE-----" "\n"
                "Hash: SHA256" "\n"
                "" "\n"
                "short message" "\n"
                "next line" "\n"
                "한국어/조선말" "\n"
                "-----BEGIN PGP SIGNATURE-----" "\n"
                "Version: GnuPG v2.0.19 (GNU/Linux)" "\n"
                "" "\n"
                "iJwEAQEIAAYFAlKcju8ACgkQ4IT3RGwgLJci6gP/dCmIraUa6AGpJxzGfK+jYpjl" "\n"
                "G0KunFyGmyPxeJVnPi2bBp3EPIbiayQ71CcDe9DKpF046tora07AA9eo+/YbvJ9P" "\n"
                "PWeScw3oj/ejsmKQoDBGzyDMFUphevnhgc5lENjovJqmiu6FKjNmADTxcZ/qFTOq" "\n"
                "44EWTgdW3IqXFkNpKjeJARwEAQEIAAYFAlKcju8ACgkQ2/Ij6HBTTfQi6gf9HxhE" "\n"
                "ycLDhQ8iyC090TaYwsDytScU2vOMiI5rJCy2tfDV0pfn+UekYGMnKxZTpwtmno1j" "\n"
                "mVOlieENszz5IcehS5TYwk4lmRFjoba+Z8qwPEYhYxP29GMbmRIsH811sQHFTigo" "\n"
                "LI2t4pSSSUpAiXd9y6KtvkWcGGn8IfkNHCEHPh1ov28QvH0+ByIiKYK5N6ZB8hEo" "\n"
                "0uMYhKQPVJdPCvMkAxQCRPw84EvmxuJ0HMCeSB9tHQXpz5un2m8D9yiGpBQPnqlW" "\n"
                "vCCq7fgaUz8ksxvQ9bSwv0iIIbbBdTP7Z8y2c1Oof6NDl7irH+QCeNT7IIGs8Smn" "\n"
                "BEzv/FqkQAhjy3Krxg==" "\n"
                "=3Pkl" "\n"
                "-----END PGP SIGNATURE-----" "\n";
                
                auto plaintext = "short message\nnext line\n한국어/조선말";
                
                PGPCleartextSignature sMsg(msg_armor);
                
                auto pubKeyArm2 = pub_key_arm2;
                PGPPublicKey::Ptr pubKey = std::make_shared<PGPPublicKey>(pubKeyArm2);
                auto pubKeyArm3 = pub_key_arm3;
                pubKey->read(pubKeyArm3);
                
                std::string out = sMsg.get_message();
                VERIFY_ARE_EQUAL(out, plaintext);
                
                auto check = sMsg.verify(pubKey);
                VERIFY_IS_TRUE(check);
            }
            
            TEST(Sign_text_with_and_verify) {
                //leads to same string cleartext and valid signatures
                std::string plaintext = "short message\nnext line\n한국어/조선말";
                
                auto pubKeyArm2 = pub_key_arm2;
                PGPPublicKey::Ptr pubKey = std::make_shared<PGPPublicKey>(pubKeyArm2);
                auto privKeyArm2 = priv_key_arm2;
                PGPSecretKey privKey(privKeyArm2);
                
                PGPCleartextSignature signedMsg = sign_cleartext(privKey, "hello world", plaintext, 2);
                std::string pgpMsg = signedMsg.write();
                
                PGPCleartextSignature csMsg(pgpMsg);
                
                std::string out = csMsg.get_message();
                VERIFY_ARE_EQUAL(out, plaintext);
                
                auto check = csMsg.verify(pubKey);
                VERIFY_IS_TRUE(check);
            }
            
            //            TEST(Sign_text_and_verify_leads_to_same_bytes_cdy("short message\nnext line\n한국어/조선말");
            //                var pubKey = openpgp.key.readArmored(pub_key_arm2).keys[0];
            //                var privKey = openpgp.key.readArmored(priv_key_arm2).keys[0];
            //                privKey.getSigningKeyPacket().decrypt("hello world");
            //
            //                openpgp.sign({ privateKeys:[privKey], data:plaintext }).then(function(signed) {
            //                    var csMsg = openpgp.message.readArmored(signed.data);
            //                    return openpgp.verify({ publicKeys:[pubKey], message:csMsg });
            //
            //                }).then(function(cleartextSig) {
            //                    expect(cleartextSig).to.exist;
            //                    expect(cleartextSig.data).to.deep.equal(plaintext);
            //                    expect(cleartextSig.signatures).to.have.length(1);
            //                    expect(cleartextSig.signatures[0].valid).to.be.true;
            //                    expect(cleartextSig.signatures[0].signature.packets.length).to.equal(1);
            //                    done();
            //                });
            //
            //            });
            //
            //    it("Sign text with openpgp.sign and verify with openpgp.verify leads to same bytes cleartext and valid signatures - not armored" "\n" function(done) {
            //        var plaintext = openpgp.util.str2Uint8Array("short message\nnext line\n한국어/조선말");
            //        var pubKey = openpgp.key.readArmored(pub_key_arm2).keys[0];
            //        var privKey = openpgp.key.readArmored(priv_key_arm2).keys[0];
            //        privKey.getSigningKeyPacket().decrypt("hello world");
            //
            //        openpgp.sign({ privateKeys:[privKey], data:plaintext, armor:false }).then(function(signed) {
            //            var csMsg = signed.message;
            //            return openpgp.verify({ publicKeys:[pubKey], message:csMsg });
            //
            //        }).then(function(cleartextSig) {
            //            expect(cleartextSig).to.exist;
            //            expect(cleartextSig.data).to.deep.equal(plaintext);
            //            expect(cleartextSig.signatures).to.have.length(1);
            //            expect(cleartextSig.signatures[0].valid).to.be.true;
            //            expect(cleartextSig.signatures[0].signature.packets.length).to.equal(1);
            //            done();
            //        });
            //
            //    });
            //
            //    it("Verify primary key revocation signature" "\n" function(done) {
            //        var pubKey = openpgp.key.readArmored(pub_revoked).keys[0];
            //
            //        var verified = pubKey.revocationSignature.verify(pubKey.primaryKey, {key: pubKey.primaryKey});
            //
            //        expect(verified).to.be.true;
            //        done();
            //    });
            //
            //    it("Verify subkey revocation signature" "\n" function(done) {
            //        var pubKey = openpgp.key.readArmored(pub_revoked).keys[0];
            //
            //        var verified = pubKey.subKeys[0].revocationSignature.verify(pubKey.primaryKey, {key: pubKey.primaryKey, bind: pubKey.subKeys[0].subKey});
            //
            //        expect(verified).to.be.true;
            //        done();
            //    });
            //
            //    it("Verify key expiration date" "\n" function(done) {
            //        var pubKey = openpgp.key.readArmored(pub_revoked).keys[0];
            //
            //        expect(pubKey).to.exist;
            //        expect(pubKey.users[0].selfCertifications[0].keyNeverExpires).to.be.false;
            //        expect(pubKey.users[0].selfCertifications[0].keyExpirationTime).to.equal(5*365*24*60*60);
            //        done();
            //    });
            //
            //    it("Verify V3 certification signature" "\n" function(done) {
            //        var pubKey = openpgp.key.readArmored(pub_v3).keys[0];
            //
            //        var verified = pubKey.users[0].selfCertifications[0].verify(pubKey.primaryKey, {key: pubKey.primaryKey, userid: pubKey.users[0].userId});
            //
            //        expect(verified).to.be.true;
            //        done();
            //    });
            //
            //    it("Write unhashed subpackets" "\n" function() {
            //        var pubKey = openpgp.key.readArmored(pub_key_arm2).keys[0];
            //        expect(pubKey.users[0].selfCertifications).to.exist;
            //        pubKey = openpgp.key.readArmored(pubKey.armor()).keys[0];
            //        expect(pubKey.users[0].selfCertifications).to.exist;
            //    });
            //
            //    it("Write V3 signatures" "\n" function() {
            //        var pubKey = openpgp.key.readArmored(pub_v3).keys[0];
            //        var pubKey2 = openpgp.key.readArmored(pubKey.armor()).keys[0];
            //        expect(pubKey2).to.exist;
            //        expect(pubKey.users[0].selfCertifications).to.eql(pubKey2.users[0].selfCertifications);
            //    });
            //
            //    it("Write V4 signatures" "\n" function() {
            //        var pubKey = openpgp.key.readArmored(pub_key_arm2).keys[0];
            //        var pubKey2 = openpgp.key.readArmored(pubKey.armor()).keys[0];
            //        expect(pubKey2).to.exist;
            //        expect(pubKey.users[0].selfCertifications).to.eql(pubKey2.users[0].selfCertifications);
            //    });
            //
            
            TEST(feng_1_test) {
                std::string data = "BEGIN:VCARD\nVERSION:4.0\nFN:feng1\nitem0.EMAIL;TYPE=Email;PREF=0:feng1.0@gmail.com\nitem1.EMAIL;TYPE=Email;PREF=1:feng1.1@gmail.com\nitem2.EMAIL;TYPE=Email;PREF=2:feng1.2@gmail.com\nUID:proton-web-16b8b261-d370-6963-e3b3-f1dfb40a06e0\nEND:VCARD";
                std::string signature = "-----BEGIN PGP SIGNATURE-----\nVersion: ProtonMail\nComment: https://protonmail.com\n\nwsBcBAEBCAAQBQJZusbZCRBtyZmxRiNPQAAAB5AH/0GPInPKbQF245ZO/ekk\nq9+ZJY5zRglfTBPt5RZvC0dWrXlFIIJ/h001k5hUlZH3OnsM8vQB3t4kQQqg\nQ04IH8M2AaO47vpKeQMWv2gr+0b5vpT++oR2/t9gT351iLC30LN8e4iCArJo\nZHXmymuGYHt+rAGM6Bg0g/PwSlnh57bQGCMciIxIizCWEAQvKrtp+BJnTViI\nYzojqNKTa9YT4riHwArt0zL3dNkKH6Wwdf0quWgp2u3T2SPZ6vvIopY89brd\nJnpj+YAvo9HelBdD5WgQEg5UaVjuTmZ8axLE4EVHnJN1onfi3Q3VOj8MM2Uz\nJ3hbi6awz4bhiiV34Jh4gx0=\n=bEYF\n-----END PGP SIGNATURE-----\n";
                std::string publickey = "-----BEGIN PGP PUBLIC KEY BLOCK-----\r\nVersion: OpenPGP.js v2.5.8\r\nComment: https://openpgpjs.org\r\n\r\nxsBNBFlewwUBCACX0HZ5EqxFh+4es4YSGZKbbxlFo+Jj/2BQxs7iH4VPzvDV\nxanVBD5D7NFywyQ8ud4X8eM81dhP9oGXs+BHNOJ9/Xf72V43lBzBSEOjnoY5\nVTBWTYE4IxkBDZWU4xoLch3DhTgWUHfKECdg/1VBpJzH9pkko0o2l8uLaz2q\n6HWFntipsxgwxc/Dr6r/HbkAFBh7+/Eow5PoDv5a//juWG+0rUu0PrYt1XuH\n9XBOiHgOmYxaoDhC4osXIFBGRqwVbtZa92yO2WQ7t4AznSPk4XSJO77DQUwl\nIhNodbMCLq94P6fhy0gTgrptZmaQ9nWno+mBxW0m3+xC9jAnJeuu7MMtABEB\nAAHNL2ZlbmcxMDBAcHJvdG9ubWFpbC5jb20gPGZlbmcxMDBAcHJvdG9ubWFp\nbC5jb20+wsB1BBABCAApBQJZXsMGBgsJBwgDAgkQbcmZsUYjT0AEFQgKAgMW\nAgECGQECGwMCHgEAAPisB/47Cv9DMuitxImo9iBKTG2Av7dpvj7s6AVNvQVj\nMW4Yo4FHu8UqF9h/MCdMLAwNelcoUCieuvemH5FICyDWtKory33eXnA+pI3b\nrdCfyoO58t4kiapfjQBdBaB+wjpnAIEQ6yfp9vSG/qM0PbwgAy+HJPkvjtZi\n1PJK4mv2fFjYozXB4yTVIV7i5Yl5PbWNzZEjpaeYZRhH+s9xZTHYSo/M8s9x\ndjTQ9/kdegqTlLRP8m+/iAheIxIrWJma/jjovN+2OCEj7nyBVV5a2yfBoCJ6\nOdZAeANJGQ7UNFsjjwCFoToY2uU3U40WFAcq4wTxXhp/UHmWu+BbozJj4+tW\nuef8zsBNBFlewwUBCADI/Byo35dRWbcOLBFZWh2xghd3FLHPsT/JaB8vr1Ac\nm8UqRV2yoperkzof+QdtFaMgh1u8Za6tdRl5lBsisx6Mcb3Bag6X/TO7sj7h\njeb9xR5s44DvXywZATqTsdrzC05K56Mk7mr+S11k/U+hcLeb9vt+juMorlHx\nSr+jYRdC8w3EcTIuhD3DszaqhSC2ioSd9sCfg5chY3i/UOy2sPistIWjWkF9\nKjERTWg7T7AQNGad6uWiRqrF6ClzTUkShfgFM0oA2gH5u279AIEfAiogol5I\nllTfTljnQr6kW91JDeMKQjZgBX9s0MAgLiiIzX1ipw8EU4EwqcszYMSte3kN\nABEBAAHCwF8EGAEIABMFAllewwYJEG3JmbFGI09AAhsMAAC9kwf/Rfh8mUvm\n8TlBl5DOQWLHfpQYP4Y4AI66zYCSLGh9W8K07DYODGdHD9Otxrb3IR6ItD3+\n3pA2LgiWq7AHCoqh8iei1q75+a11xzFI/RPct7coxPUPHSMf0nKZ+FtP/B4/\n06CCRAv9EMTB9UI7HCNaut0jLmT/qeQ0C8DjeHXrM055tvaRz72KXMs95bCn\nMVahehFRUoWugkSBwqnVeRIXjyPYQRmLCobzmtZFcoo59LK+pM5SNw43uPb6\nEYvFxEzts49UIchNOy2VDJyGuW5aC+ZPknpf3W+RnxgboqChY1RdksiECjJ+\n19ZrhcGdZW7Pr0TSvGhdqZbL3BmZoO+eXw==\r\n=PJ77\r\n-----END PGP PUBLIC KEY BLOCK-----\r\n\r\n";
                
                
                auto pgp = ProtonMail::OpenPgp::create_instance();
                auto check2 = pgp->sign_detached_verify(publickey, signature, data);
                VERIFY_IS_TRUE(check2);
            }
            
            TEST(detached_signature_pm_1) {
                //leads to same string cleartext and valid signatures
                std::string plaintext = "short message\nnext line\n한국어/조선말";
                auto pgp = ProtonMail::OpenPgp::create_instance();
                auto pgpMsg = pgp->sign_detached(priv_key_arm2, plaintext, "hello world");
                auto check1 = pgp->sign_detached_verify(pub_key_arm2, pgpMsg, plaintext);
                VERIFY_IS_TRUE(check1);
                auto check2 = pgp->sign_detached_verify(pub_key_arm3, pgpMsg, plaintext);
                VERIFY_IS_FALSE(check2);
            }
            
            //    it("Verify a detached signature using readSignedContent" "\n" function() {
            //        var detachedSig = ["-----BEGIN PGP SIGNATURE-----" "\n"
            //                           "Version: GnuPG v1.4.13 (Darwin)" "\n"
            //                           "Comment: GPGTools - https://gpgtools.org" "\n"
            //                           "Comment: Using GnuPG with Thunderbird - http://www.enigmail.net/" "\n"
            //                           "" "\n"
            //                           "iQEcBAEBCgAGBQJTqH5OAAoJENf7k/zfv8I8oFoH/R6EFTw2CYUQoOKSAQstWIHp" "\n"
            //                           "fVVseLOkFbByUV5eLuGVBNI3DM4GQ6C7dGntKAn34a1iTGcAIZH+fIhaZ2WtNdtA" "\n"
            //                           "R+Ijn8xDjbF/BWvcTBOaRvgw9b8viPxhkVYa3PioHYz6krt/LmFqFdp/phWZcqR4" "\n"
            //                           "jzWMX55h4FOw3YBNGiz2NuIg+iGrFRWPYgd8NVUmJKReZHs8C/6HGz7F4/A24k6Y" "\n"
            //                           "7xms9D6Er+MhspSl+1dlRdHjtXiRqC5Ld1hi2KBKc6YzgOLpVw5l9sffbnH+aRG4" "\n"
            //                           "dH+2J5U3elqBDK1i3GyG8ixLSB0FGW9+lhYNosZne2xy8SbQKdgsnTBnWSGevP0=" "\n"
            //                           "=xiih" "\n"
            //                           "-----END PGP SIGNATURE-----"
            //                           ].join("\r\n");
            //
            //        var content = ["Content-Type: multipart/mixed;" "\n"
            //                       " boundary="------------070307080002050009010403"" "\n"
            //                       "" "\n"
            //                       "This is a multi-part message in MIME format." "\n"
            //                       "--------------070307080002050009010403" "\n"
            //                       "Content-Type: text/plain; charset=ISO-8859-1" "\n"
            //                       "Content-Transfer-Encoding: quoted-printable" "\n"
            //                       "" "\n"
            //                       "test11" "\n"
            //                       "" "\n"
            //                       "--------------070307080002050009010403" "\n"
            //                       "Content-Type: application/macbinary;" "\n"
            //                       " name="test.bin"" "\n"
            //                       "Content-Transfer-Encoding: base64" "\n"
            //                       "Content-Disposition: attachment;" "\n"
            //                       " filename="test.bin"" "\n"
            //                       "" "\n"
            //                       "dGVzdGF0dGFjaG1lbnQ=" "\n"
            //                       "--------------070307080002050009010403--" "\n"
            //                       ""
            //                       ].join("\r\n");
            //
            //        var publicKeyArmored = "-----BEGIN PGP PUBLIC KEY BLOCK-----\r\nVersion: OpenPGP.js v.1.20131116\r\nComment: Whiteout Mail - http://whiteout.io\r\n\r\nxsBNBFKODs4BB/9iOF4THsjQMY+WEpT7ShgKxj4bHzRRaQkqczS4nZvP0U3g\r\nqeqCnbpagyeKXA+bhWFQW4GmXtgAoeD5PXs6AZYrw3tWNxLKu2Oe6Tp9K/XI\r\nxTMQ2wl4qZKDXHvuPsJ7cmgaWqpPyXtxA4zHHS3WrkI/6VzHAcI/y6x4szSB\r\nKgSuhI3hjh3s7TybUC1U6AfoQGx/S7e3WwlCOrK8GTClirN/2mCPRC5wuIft\r\nnkoMfA6jK8d2OPrJ63shy5cgwHOjQg/xuk46dNS7tkvGmbaa+X0PgqSKB+Hf\r\nYPPNS/ylg911DH9qa8BqYU2QpNh9jUKXSF+HbaOM+plWkCSAL7czV+R3ABEB\r\nAAHNLVdoaXRlb3V0IFVzZXIgPHNhZmV3aXRobWUudGVzdHVzZXJAZ21haWwu\r\nY29tPsLAXAQQAQgAEAUCUo4O2gkQ1/uT/N+/wjwAAN2cB/9gFRmAfvEQ2qz+\r\nWubmT2EsSSnjPMxzG4uyykFoa+TaZCWo2Xa2tQghmU103kEkQb1OEjRjpgwJ\r\nYX9Kghnl8DByM686L5AXnRyHP78qRJCLXSXl0AGicboUDp5sovaa4rswQceH\r\nvcdWgZ/mgHTRoiQeJddy9k+H6MPFiyFaVcFwegVsmpc+dCcC8yT+qh8ZIbyG\r\nRJU60PmKKN7LUusP+8DbSv39zCGJCBlVVKyA4MzdF5uM+sqTdXbKzOrT5DGd\r\nCZaox4s+w16Sq1rHzZKFWfQPfKLDB9pyA0ufCVRA3AF6BUi7G3ZqhZiHNhMP\r\nNvE45V/hS1PbZcfPVoUjE2qc1Ix1\r\n=7Wpe\r\n-----END PGP PUBLIC KEY BLOCK-----";
            //        var publicKeys = openpgp.key.readArmored(publicKeyArmored).keys;
            //
            //        var msg = openpgp.message.readSignedContent(content, detachedSig);
            //        var result = msg.verify(publicKeys);
            //        expect(result[0].valid).to.be.true;
            //    });
            //
            //    it("Detached signature signing and verification" "\n" function () {
            //        var msg = openpgp.message.fromText("hello");
            //        var pubKey2 = openpgp.key.readArmored(pub_key_arm2).keys[0];
            //        var privKey2 = openpgp.key.readArmored(priv_key_arm2).keys[0];
            //        privKey2.decrypt("hello world");
            //
            //        var opt = {numBits: 512, userIds: { name:"test" "\n" email:"a@b.com" }, passphrase: null};
            //        if (openpgp.util.getWebCryptoAll()) { opt.numBits = 2048; } // webkit webcrypto accepts minimum 2048 bit keys
            //        openpgp.generateKey(opt).then(function(gen) {
            //            var generatedKey = gen.key;
            //            var detachedSig = msg.signDetached([generatedKey, privKey2]);
            //            var result = msg.verifyDetached(detachedSig, [generatedKey.toPublic(), pubKey2]);
            //            expect(result[0].valid).to.be.true;
            //            expect(result[1].valid).to.be.true;
            //        });
            //    });
            //
            //    it("Sign message with key without password" "\n" function(done) {
            //        var opt = {numBits: 512, userIds: { name:"test" "\n" email:"a@b.com" }, passphrase: null};
            //        if (openpgp.util.getWebCryptoAll()) { opt.numBits = 2048; } // webkit webcrypto accepts minimum 2048 bit keys
            //        openpgp.generateKey(opt).then(function(gen) {
            //            var key = gen.key;
            //
            //            var message = openpgp.message.fromText("hello world");
            //            message = message.sign([key]);
            //
            //            expect(message).to.exist;
            //            done();
            //        });
            //    });
            
            TEST(Verify_signed_key) {
                std::string signedArmor =
                "-----BEGIN PGP PUBLIC KEY BLOCK-----" "\n"
                "Version: GnuPG v1" "\n"
                "" "\n"
                "mI0EUmEvTgEEANyWtQQMOybQ9JltDqmaX0WnNPJeLILIM36sw6zL0nfTQ5zXSS3+" "\n"
                "fIF6P29lJFxpblWk02PSID5zX/DYU9/zjM2xPO8Oa4xo0cVTOTLj++Ri5mtr//f5" "\n"
                "GLsIXxFrBJhD/ghFsL3Op0GXOeLJ9A5bsOn8th7x6JucNKuaRB6bQbSPABEBAAG0" "\n"
                "JFRlc3QgTWNUZXN0aW5ndG9uIDx0ZXN0QGV4YW1wbGUuY29tPoi5BBMBAgAjBQJS" "\n"
                "YS9OAhsvBwsJCAcDAgEGFQgCCQoLBBYCAwECHgECF4AACgkQSmNhOk1uQJQwDAP6" "\n"
                "AgrTyqkRlJVqz2pb46TfbDM2TDF7o9CBnBzIGoxBhlRwpqALz7z2kxBDmwpQa+ki" "\n"
                "Bq3jZN/UosY9y8bhwMAlnrDY9jP1gdCo+H0sD48CdXybblNwaYpwqC8VSpDdTndf" "\n"
                "9j2wE/weihGp/DAdy/2kyBCaiOY1sjhUfJ1GogF49rCIRgQQEQIABgUCVuXBfQAK" "\n"
                "CRARJ5QDyxae+O0fAJ9hUQPejXvZv6VW1Q3/Pm3+x2wfJACgwFg9NlrPPfejoC1w" "\n"
                "P+z+vE5NFA24jQRSYS9OAQQA6R/PtBFaJaT4jq10yqASk4sqwVMsc6HcifM5lSdx" "\n"
                "zExFP74naUMMyEsKHP53QxTF0GrqusagQg/ZtgT0CN1HUM152y7ACOdp1giKjpMz" "\n"
                "OTQClqCoclyvWOFB+L/SwGEIJf7LSCErwoBuJifJc8xAVr0XX0JthoW+uP91eTQ3" "\n"
                "XpsAEQEAAYkBPQQYAQIACQUCUmEvTgIbLgCoCRBKY2E6TW5AlJ0gBBkBAgAGBQJS" "\n"
                "YS9OAAoJEOCE90RsICyXuqIEANmmiRCASF7YK7PvFkieJNwzeK0V3F2lGX+uu6Y3" "\n"
                "Q/Zxdtwc4xR+me/CSBmsURyXTO29OWhPGLszPH9zSJU9BdDi6v0yNprmFPX/1Ng0" "\n"
                "Abn/sCkwetvjxC1YIvTLFwtUL/7v6NS2bZpsUxRTg9+cSrMWWSNjiY9qUKajm1tu" "\n"
                "zPDZXAUEAMNmAN3xXN/Kjyvj2OK2ck0XW748sl/tc3qiKPMJ+0AkMF7Pjhmh9nxq" "\n"
                "E9+QCEl7qinFqqBLjuzgUhBU4QlwX1GDAtNTq6ihLMD5v1d82ZC7tNatdlDMGWnI" "\n"
                "dvEMCv2GZcuIqDQ9rXWs49e7tq1NncLYhz3tYjKhoFTKEIq3y3Pp" "\n"
                "=fvK7" "\n"
                "-----END PGP PUBLIC KEY BLOCK-----" "\n";
                
                auto signedKeyArmor = signedArmor;
                PGPPublicKey signedKey(signedKeyArmor);
                auto privKeyArm2 = priv_key_arm1;
                PGPSecretKey signerKey(privKeyArm2);
                
                bool check = verify_key(signerKey, signedKey);
                VERIFY_IS_TRUE(check);
            }
            
            TEST(dino_sign_verify_test) {
//                auto signedArmor =
//                "-----BEGIN PGP SIGNATURE-----" "\n"
//                "Version: ProtonMail" "\n"
//                "Comment: https://protonmail.com" "\n"
//                "" "\n"
//                "wsBcBAEBCAAQBQJZ8TzGCRDDtWY4RN39IwAAQ1cH/ioG9ilzZ+N2qS7xBOYy" "\n"
//                "CBp14lWLIrOodbh9P00FteA7vmpZreFnWCi596wn+gjcNa2wYvrWQrF13LnW" "\n"
//                "4GkifcLxjl/OHqLImVVOOxEQpX6rvdz2CcwDvRlj/CWxd3PL2VRfEJcAW8Jg" "\n"
//                "IiIigmPVT7YW26jJ5nuVa77kYzmnBEGL5A+WiIoJddCNBwlxn/C7K9rkXw1B" "\n"
//                "0Bd6J/jSAvMC6S5ElrwpuXPFUTZzxNXDyV6+qblR9T511gpTOAamFtEwpt8i" "\n"
//                "k7VLXIckMOLKavbly84/WKyg1ViWoGmEGzfNJbHPrxMZ+CwhsEeJMiBANhPn" "\n"
//                "4jQ49RU279/oD7LD6FovPg0=" "\n"
//                "=/jLE" "\n"
//                "-----END PGP SIGNATURE-----" "\n";
//
//                auto pbkey =
//                "-----BEGIN PGP PUBLIC KEY BLOCK-----" "\n"
//                "Version: OpenPGP.js v2.5.8" "\n"
//                "Comment: https://openpgpjs.org" "\n"
//                "" "\n"
//                "xsBNBFjRE2EBCADGHT8HPRPWDlMdod/krvXKLjG1te+Jyf5BJY9ckpfmNu1X" "\n"
//                "uglKRUUkUdvuWwXDOVjMTLhQLXKWGueQmRm0rZj/z0Wze7CTDskvh81x/DlK" "\n"
//                "TU29Y+EjZ2ysEoIM1eaKv+/3sgn2dh7Ma6PHgAeb7wHOLY6+mmNQzuNrttHn" "\n"
//                "WZf/ISOVatgmxm4ds52yrG8wzoNUjwUwIpLutkgYs2+b91LR/P5z5ZXHydcE" "\n"
//                "3ZiMy6VYQ+wAzWwH9L+YwCuNi4kHXHzcX6J+szowHCkPDMJMejF1MwZ9WM+R" "\n"
//                "XugVAtiZ0fUPyTT/GVxsCaazGAiZIuseBkpGHB8nLyL9walIH/2kAU6NABEB" "\n"
//                "AAHNN2ouam92YW5vdnNraUBwcm90b25tYWlsLmNoIDxqLmpvdmFub3Zza2lA" "\n"
//                "cHJvdG9ubWFpbC5jaD7CwHUEEAEIACkFAljcRn0GCwkHCAMCCRDDtWY4RN39" "\n"
//                "IwQVCAoCAxYCAQIZAQIbAwIeAQAAYK0IAJPTVgUnNKpj4K9WbzcVOI68Bf8r" "\n"
//                "ap0Yku6KjgTTuVowUg4Bvn225a5FLN0jWJBtbexxG0KGn5uh1DfiIJRdLuzK" "\n"
//                "pCd4Jbntb1ay2i7CkD25kYXopGUUk8aE2QGS4sI8ThBzX8auG64/LWFMdoPO" "\n"
//                "oZDausgqSFUYzKLIwmuF1LLLIhvBjlaCjx2GnZwBvsgvipoD8CpRJxByk/qv" "\n"
//                "WYP6Mns3j180l+NixUHlpmGKR/lg0ppUpG8EoWalnoPXTBSdYnR90lywBRIe" "\n"
//                "FvGnAOsH5mAAttdc5j9gyMetzVCZ5btVDUVwuP4pf+O+CXYWjWwHSvR5+Gxc" "\n"
//                "Ra9oFugox34dkHPOwE0EWNETYQEIALvo2uYZ+TJ8ju86xqpxmkS1uYaezDVf" "\n"
//                "UWVcYFWTxOssTfsZVDVGbCVtV76pR95jwzxCfXVxq1WUBiv618UmZ0mpTFEr" "\n"
//                "agRaordfrj0NAu1KAIlj1VPjpFOjQUMejc0dhlhonKXSj34bHzaI+u/BdBOu" "\n"
//                "rWS1Atn/32J4oUf+HzpweuqgP37SWUH/ahAdbiqyg9hcZR+pm91yj2GLCgTn" "\n"
//                "8chUuDtY/CLtViX//6V1NpHauBvmB/B17smC0wb4VkCTAbV9VvvkgTkj1taA" "\n"
//                "dA2FN0Icg2fBUXUuv4HRE3I2Ck+0btSUY6gQDPG4PIQlN+kF/8tVryOa3QAq" "\n"
//                "ZZQqK0MJXLEAEQEAAcLAXwQYAQgAEwUCWNxGfQkQw7VmOETd/SMCGwwAAIfD" "\n"
//                "CAC6GK4bBYKj5jFHk8d5Bnk/H4B2puZzEPPSAoJts/WKgTmY6sMoY6MTUCCn" "\n"
//                "VOPIFOVCvU/SjRmDOk4ZDRr5IPRsBiY1ziFxsLOu4+/XI455quaHxhwQlTDM" "\n"
//                "ZJh9hEh6Dsv7AOtp4dqpHk0s5tmm1oZa5mAzdrPDZ+llmAxpscauc4WYBxIs" "\n"
//                "RuxqHKpd+QfwHDW0CPq0bMlwN3/q5/uLv9wfwrlYvaLmJO++qy0sLWNqzeWN" "\n"
//                "aVx5TNc9JD+G6k1rFKof561vvff5WGr/4Rfe8FiyD27MXz0Et/RcGZrr4IUE" "\n"
//                "ncPm/RJPHxIp6ZPNeC/vCSl6o7wi0pnCaH+Oo9WWXHYg" "\n"
//                "=S3I+" "\n"
//                "-----END PGP PUBLIC KEY BLOCK-----" "\n";
//
//                auto signedKeyArmor = signedArmor;
//                auto publicKey = pbkey;
                
//                auto pgp = ProtonMail::OpenPgp::create_instance();
//                auto check = pgp->sign_detached_verify(publicKey, signedKeyArmor, "");
//                VERIFY_IS_TRUE(check);
            }
            
            TEST(dino_sign_verify_test_2) {
//                auto signedArmor = "-----BEGIN PGP SIGNATURE-----\nVersion: ProtonMail\nComment: https://protonmail.com\n\nwsBcBAEBCAAQBQJZ8TzSCRDDtWY4RN39IwAAfN8IAIeWN8oQj4MCGEpgoE5W\nfZZ4zZG1aBp3TSEnsiYAPpP/uIkg5MNdfay/EGlgJXIjxFxdDvgX51b7GL93\nil/HZ91yL6HX8oNNnC/r28ksuRobTQ74btVc5Qi3Pk6gaoBLIvHPCJB2zK7d\nUF0njZ8dltJEiWI5rKUa4fCEABhSUaeUDCIqEj/7kaedqAdbjw2DcbqRacAb\nJW8nyk3zVrXtk+WMejcRqGNgOLIPINa43iet2Ta9mqS/3t1eRB/IQl/kUVMR\nrOp0faZmab7ZAN9HO1R7Z2cMS8rGzBbseZsUhmYozAwoU7KY47TdrENIE/cz\nIAsc5bpYjbbN7yooFejYISA=\n=fPZg\n-----END PGP SIGNATURE-----\n";
//                auto pbkey =
//                "-----BEGIN PGP PUBLIC KEY BLOCK-----" "\n"
//                "Version: OpenPGP.js v2.5.8" "\n"
//                "Comment: https://openpgpjs.org" "\n"
//                "" "\n"
//                "xsBNBFjRE2EBCADGHT8HPRPWDlMdod/krvXKLjG1te+Jyf5BJY9ckpfmNu1X" "\n"
//                "uglKRUUkUdvuWwXDOVjMTLhQLXKWGueQmRm0rZj/z0Wze7CTDskvh81x/DlK" "\n"
//                "TU29Y+EjZ2ysEoIM1eaKv+/3sgn2dh7Ma6PHgAeb7wHOLY6+mmNQzuNrttHn" "\n"
//                "WZf/ISOVatgmxm4ds52yrG8wzoNUjwUwIpLutkgYs2+b91LR/P5z5ZXHydcE" "\n"
//                "3ZiMy6VYQ+wAzWwH9L+YwCuNi4kHXHzcX6J+szowHCkPDMJMejF1MwZ9WM+R" "\n"
//                "XugVAtiZ0fUPyTT/GVxsCaazGAiZIuseBkpGHB8nLyL9walIH/2kAU6NABEB" "\n"
//                "AAHNN2ouam92YW5vdnNraUBwcm90b25tYWlsLmNoIDxqLmpvdmFub3Zza2lA" "\n"
//                "cHJvdG9ubWFpbC5jaD7CwHUEEAEIACkFAljcRn0GCwkHCAMCCRDDtWY4RN39" "\n"
//                "IwQVCAoCAxYCAQIZAQIbAwIeAQAAYK0IAJPTVgUnNKpj4K9WbzcVOI68Bf8r" "\n"
//                "ap0Yku6KjgTTuVowUg4Bvn225a5FLN0jWJBtbexxG0KGn5uh1DfiIJRdLuzK" "\n"
//                "pCd4Jbntb1ay2i7CkD25kYXopGUUk8aE2QGS4sI8ThBzX8auG64/LWFMdoPO" "\n"
//                "oZDausgqSFUYzKLIwmuF1LLLIhvBjlaCjx2GnZwBvsgvipoD8CpRJxByk/qv" "\n"
//                "WYP6Mns3j180l+NixUHlpmGKR/lg0ppUpG8EoWalnoPXTBSdYnR90lywBRIe" "\n"
//                "FvGnAOsH5mAAttdc5j9gyMetzVCZ5btVDUVwuP4pf+O+CXYWjWwHSvR5+Gxc" "\n"
//                "Ra9oFugox34dkHPOwE0EWNETYQEIALvo2uYZ+TJ8ju86xqpxmkS1uYaezDVf" "\n"
//                "UWVcYFWTxOssTfsZVDVGbCVtV76pR95jwzxCfXVxq1WUBiv618UmZ0mpTFEr" "\n"
//                "agRaordfrj0NAu1KAIlj1VPjpFOjQUMejc0dhlhonKXSj34bHzaI+u/BdBOu" "\n"
//                "rWS1Atn/32J4oUf+HzpweuqgP37SWUH/ahAdbiqyg9hcZR+pm91yj2GLCgTn" "\n"
//                "8chUuDtY/CLtViX//6V1NpHauBvmB/B17smC0wb4VkCTAbV9VvvkgTkj1taA" "\n"
//                "dA2FN0Icg2fBUXUuv4HRE3I2Ck+0btSUY6gQDPG4PIQlN+kF/8tVryOa3QAq" "\n"
//                "ZZQqK0MJXLEAEQEAAcLAXwQYAQgAEwUCWNxGfQkQw7VmOETd/SMCGwwAAIfD" "\n"
//                "CAC6GK4bBYKj5jFHk8d5Bnk/H4B2puZzEPPSAoJts/WKgTmY6sMoY6MTUCCn" "\n"
//                "VOPIFOVCvU/SjRmDOk4ZDRr5IPRsBiY1ziFxsLOu4+/XI455quaHxhwQlTDM" "\n"
//                "ZJh9hEh6Dsv7AOtp4dqpHk0s5tmm1oZa5mAzdrPDZ+llmAxpscauc4WYBxIs" "\n"
//                "RuxqHKpd+QfwHDW0CPq0bMlwN3/q5/uLv9wfwrlYvaLmJO++qy0sLWNqzeWN" "\n"
//                "aVx5TNc9JD+G6k1rFKof561vvff5WGr/4Rfe8FiyD27MXz0Et/RcGZrr4IUE" "\n"
//                "ncPm/RJPHxIp6ZPNeC/vCSl6o7wi0pnCaH+Oo9WWXHYg" "\n"
//                "=S3I+" "\n"
//                "-----END PGP PUBLIC KEY BLOCK-----" "\n";
//
//                auto signedKeyArmor = signedArmor;
//                auto publicKey = pbkey;
//                auto str_check = "BEGIN:VCARD\nVERSION:4.0\nitem1.EMAIL;TYPE=xINTERNET:aaronlura@yahoo.com\nUID:proton-web-2d8ced50-cee1-a3a6-cb24-18b06d6eb4d3\nFN:    \nEND:VCARD";
//
//                auto pgp = ProtonMail::OpenPgp::create_instance();
//                auto check = pgp->sign_detached_verify(publicKey, signedKeyArmor, str_check);
//                VERIFY_IS_TRUE(check);
                
            }
        }
    }
}
