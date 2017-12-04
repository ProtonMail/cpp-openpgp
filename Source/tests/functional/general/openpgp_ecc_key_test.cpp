//
//  openpgp_ecc_key_test.cpp
//  crypto_test
//
//  Created by Yanfeng Zhang on 12/4/17.
//  Copyright © 2017 Yanfeng Zhang. All rights reserved.
//

#include "utils_test.h"

#include <openpgp/PGPKey.h>
#include <openpgp/encrypt.h>
#include <openpgp/decrypt.h>

#include <openpgp/private_key.h>
#include <openpgp/pgptime.h>
#include <algorithm>
#include <iostream>
#include <string>

using namespace ProtonMail::pgp;

namespace tests {
    namespace open_pgp_tests {
        
        SUITE(openpgp_ecc_key_test)
        {
            std::string pub_key_armor =
            "-----BEGIN PGP PUBLIC KEY BLOCK-----" "\n"
            "" "\n"
            "mQENBFOGnaMBB/98ZH1zXdaT9K72UCxTOod8gcljsHZiS/cfFSLsZXoVV0CQ63P7" "\n"
            "S5wc5PI95uUI8L1xFd4bb0mFq2xjj3kHIU25PALskwMD7F4lvsJa9hBstHrqbSTl" "\n"
            "rxa6bks8SYMqXMY4lV3pmM93whsS3chVeZV9u75X4eV1PFR2Fai7v+OVOVC18G4E" "\n"
            "Q38eprk0q5HGITYlfK9AFNiICZYtJCwa8JngBsiu2bpOFUy7h/lta1kP6jGyeBPk" "\n"
            "kNvlfoI8tN1/9qHaJWXOLQHChzKcZWQ1JeV0MoU6ahKLVk9WbqmTfnYSCbdNocSj" "\n"
            "rA0F+UJaE2HzpGeopULzErMFJp+bhGh5RDbtABEBAAG0BlVzZXJJRIkBMgQQAQgA" "\n"
            "JgUCU4adpgYLCQgHAwIJEI0MCLgORQt8BBUIAgoDFgIBAhsDAh4BAADHmgf9HUWB" "\n"
            "8NeKf7qH0b9EmL27S9QizP3TCiHJh+rm4FqXCeCKH/q88gBmLwFnuHjkVtCoXV0T" "\n"
            "1mZdXGPf88oM7u/S9J8gigiIcAzZeHTWWpMe3xYNiDOwcLPP77p5ribQHIcDCdUP" "\n"
            "OMObIG1hllGvy8iCDEDz0KGGEEyE2WLDp80wBCxJrfAKULQsGcLy2GGaBpIkmdPJ" "\n"
            "KLDkrcoUZ1AAvaYaqQvdDHkd3TLpp2uRw0D6X61ohua4KEFxgTEs2wLvLMF6f383" "\n"
            "YTvISqTllrl5BckyAlw8enWDnwadMxYF5x19zLZVO2bNG3vE6DyxlG/hEavhO/8J" "\n"
            "9yRoFhiSoOf6+KG+L7kBDQRThp2mAQgAniLmZ9MA1F43MI42euYI5DiE/EGvjisv" "\n"
            "EuucwtcBRw4OOiWhkJFwMB7B0IzezvJYvxUVziDVqtt/eL1uoG8rwEOKoAlhywuQ" "\n"
            "r+DZYlU7PNgW/h8ijbr/xO0FG0XKaPmffhUOANEiPeCcUPD8n2HHYbJpDEPOO2/9" "\n"
            "CcEw3mDVka1j8/JtB3hdV5lZdl8KJn1Xtut+Djo7keb/9pL5PqMiS7j1G4R7MLxd" "\n"
            "fYvfxcGWwS0JtM8CISKzwbIa3LlyKw3wkHJGtn5zP/U/YmX6MEpDokiTg06PCyKu" "\n"
            "nhRSduUbdv1Pxna9X2n76TgdseDojYz/q94X9lmHT/bIqq3qxB+pQQARAQABiQEf" "\n"
            "BBgBCAATBQJThp2sCRCNDAi4DkULfAIbDAAAosAH/RETXAq3N+zrkxLiAIowYuRo" "\n"
            "XmXC7s7nIsIMEUXA6oDXBjcO2ytO4rdy9poqnBRRuW+/lt3uWa2JjQH2SQyaroSd" "\n"
            "KEsJ/x5EaW8yuP0BQosyxFpcmhTyIJOjpve6SdGe780hvPw6l/nIfMapDGDumVf5" "\n"
            "aj//ekiiMX42hI9zdX8TTJo+Y3+bJiMVTQS3PYzt1G9kzxCuzYl5Q+ep89/ex+TZ" "\n"
            "L6Iv+dFo9roXKetZ3Ii/7gJ1zi/GancVCyT/5QBQP2qTE9jQU9muwnoCTfokX+bA" "\n"
            "p77RUJRKzdf/5OV7iKWtAJQbBBUfj6Ce294WkxW16btjWHkvCdtMiWwdcTKJisw=" "\n"
            "=nJEC" "\n"
            "-----END PGP PUBLIC KEY BLOCK-----";
            std::string priv_key_armor =
            "-----BEGIN PGP PRIVATE KEY BLOCK-----" "\n"
            "" "\n"
            "lQPGBFOGnaMBB/98ZH1zXdaT9K72UCxTOod8gcljsHZiS/cfFSLsZXoVV0CQ63P7" "\n"
            "S5wc5PI95uUI8L1xFd4bb0mFq2xjj3kHIU25PALskwMD7F4lvsJa9hBstHrqbSTl" "\n"
            "rxa6bks8SYMqXMY4lV3pmM93whsS3chVeZV9u75X4eV1PFR2Fai7v+OVOVC18G4E" "\n"
            "Q38eprk0q5HGITYlfK9AFNiICZYtJCwa8JngBsiu2bpOFUy7h/lta1kP6jGyeBPk" "\n"
            "kNvlfoI8tN1/9qHaJWXOLQHChzKcZWQ1JeV0MoU6ahKLVk9WbqmTfnYSCbdNocSj" "\n"
            "rA0F+UJaE2HzpGeopULzErMFJp+bhGh5RDbtABEBAAH+BwMCczvUnswKb6TjnIGF" "\n"
            "P9Ult8EK3LZt+fqL8/aFW3rNMwslvjjKmqAj4PqZmGDt0YZSHPTg3mYJGYJ6EN8T" "\n"
            "2LxpCRIJ+Vb3qOB0hMyoOnbjTOyCWBpWYhpFuuQrmuxcWJKwmtDv7nDvhKebsj3e" "\n"
            "LsvugVQJ6UzBtyqEGhNlIsiRZ7nmxMaLGut+FTofeVtOpYxyETOqVS+Gl8dJfLKt" "\n"
            "cNZcLgtMJc2QO4uXwUw1L5qOP5vgo2vUOxhridoXITYsD0ohdoMyLYMkFkLYy9IO" "\n"
            "m5cocwkS1JsRVCc7WNB+l4olLBmCFhQkd6oUZvWqgUX3wj16oGYWE51NWVX6HJt3" "\n"
            "rRL5FXMumrJHedh+blr0CXlUOnkLftl6j5EflWrJ/cc5qIVRYIrDtQ5Y2mB1BaFl" "\n"
            "CDNol9gMBe+nIjvfzSNQiFqS7I1CDKWCVVYQi9xEE9pRnzySq8U45SYlugUjJMCO" "\n"
            "kRWOM57+/L7XMAP1D+K06WbV/VaNr30xshtgUMJ4/Ip/WyaXHBtAswfQKjiyUDeT" "\n"
            "0J4SPoGBfFfIz4WWmug6Z8LupGk8ygrXkP5He4KySzwuunQv31n0MofVeQZfnX01" "\n"
            "mJ5Triip+yBuV+i0ympJEK3FET7z3rFyQ5LGZkJi+/UhKHuIg3T8h083gnU6Zvro" "\n"
            "9nmt1VNOUo+waa5BV1HGso/nMGfDoA7qFtfWizw3wLF5gMO97Co9Z7SBdfAcXLld" "\n"
            "rbeRZaDY+KFb7zOxK8T9+FBftf1lHL2464dqidlmnhr41DisDsoBK3eHjNSfPmkp" "\n"
            "+N8NkvnUTtg6KyzEzBhB5WEJd3kyfO9QoSrLQI8uO8BnV/9Go+h7BaBXnCbnjYDT" "\n"
            "A5qsCIOY9UAlk8EZOg5LizMukp8SLeYV1m20c9l3VA1nKjtuU4oICFdZ5dz++/Wk" "\n"
            "qd+L+dxKbNgDtAZVc2VySUSJATIEEAEIACYFAlOGnaYGCwkIBwMCCRCNDAi4DkUL" "\n"
            "fAQVCAIKAxYCAQIbAwIeAQAAx5oH/R1FgfDXin+6h9G/RJi9u0vUIsz90wohyYfq" "\n"
            "5uBalwngih/6vPIAZi8BZ7h45FbQqF1dE9ZmXVxj3/PKDO7v0vSfIIoIiHAM2Xh0" "\n"
            "1lqTHt8WDYgzsHCzz++6ea4m0ByHAwnVDzjDmyBtYZZRr8vIggxA89ChhhBMhNli" "\n"
            "w6fNMAQsSa3wClC0LBnC8thhmgaSJJnTySiw5K3KFGdQAL2mGqkL3Qx5Hd0y6adr" "\n"
            "kcNA+l+taIbmuChBcYExLNsC7yzBen9/N2E7yEqk5Za5eQXJMgJcPHp1g58GnTMW" "\n"
            "Becdfcy2VTtmzRt7xOg8sZRv4RGr4Tv/CfckaBYYkqDn+vihvi+dA8YEU4adpgEI" "\n"
            "AJ4i5mfTANReNzCONnrmCOQ4hPxBr44rLxLrnMLXAUcODjoloZCRcDAewdCM3s7y" "\n"
            "WL8VFc4g1arbf3i9bqBvK8BDiqAJYcsLkK/g2WJVOzzYFv4fIo26/8TtBRtFymj5" "\n"
            "n34VDgDRIj3gnFDw/J9hx2GyaQxDzjtv/QnBMN5g1ZGtY/PybQd4XVeZWXZfCiZ9" "\n"
            "V7brfg46O5Hm//aS+T6jIku49RuEezC8XX2L38XBlsEtCbTPAiEis8GyGty5cisN" "\n"
            "8JByRrZ+cz/1P2Jl+jBKQ6JIk4NOjwsirp4UUnblG3b9T8Z2vV9p++k4HbHg6I2M" "\n"
            "/6veF/ZZh0/2yKqt6sQfqUEAEQEAAf4HAwKLciKB2ePTMuPbVsisVAg+Vno+dJCu" "\n"
            "7TQh/mCfygQcdV7v65hke2LdOw+clwSWZ0D2YvgYkAfdWM5PBSXIynHO+4i4LGdt" "\n"
            "hWYIB6rNvnON44bdpBXtfEw1c+a9pChXFplcKqobvrLt3lJkiXpALTco76Z0otpL" "\n"
            "uU54eFG20lKFzv5/xllUjW0rq7zqQMKgqRjLnNAjhjBeDAO5bGoqYQgYgd27wAHA" "\n"
            "ZI4LSpJWJC4SzWjUJvmXYdC61DpRpwI98xR9OfN1iYtRNEC6wsVB6TchXOZ9ajRR" "\n"
            "KJ51+MDP4DD50Zq635UyqZz4iJM0laGH/l0SyT68R5gSlJA1Xd9BcXlZDHyom9+U" "\n"
            "bnZWkQelGlM49uBXkRSmRelcQv0qVgswL7GfBqzDMN4f6wWavJCFblt+gisWR+IT" "\n"
            "w038hHAB014lW5Wn1+FNi0tabpOzYydK4OP+Apu6K+gcj1KsR26VT1+aMXMeRrrU" "\n"
            "VL3wBTibuJQ+1FXJGZwgtCZKdA7PMwjqEoL/QnmtwsOBTF0smdraiVksvpyvL8sy" "\n"
            "SZXG+wY0dFKPsUHiGPmnqB4m2gxo6euY4MbQGtQgHmnlytXB1qUkxIt9/7TDg7Lf" "\n"
            "wifGzPxbgAbu7fwo7qFcGMi8p9pHtV2hZjCDAjDV7E0i97pmglzksTNGjXce2gbA" "\n"
            "tsuCXjbbBeXKc2FJZSECOj42yAlYIiPD9lngQGr3Ub/Mq97sSsEr/m/TxHtRSezr" "\n"
            "kFcoq2MM/qv7/oKlY9R/QNtup7fIfRLnlGK0mryLWSdSpvAX4AAS3d5uVepeK+7M" "\n"
            "9dOeeTVqlcXK+xSL18g2pE2ddln8WRxtxY4CrR97nYLksa+Tn0HWs2cictGri+N2" "\n"
            "sB6e7Go8FkuQpQrE6dnnwi3Rg9UF4hwXn29Mv8rk9wOHCcAnn03eMHM8oeuurk6J" "\n"
            "AR8EGAEIABMFAlOGnawJEI0MCLgORQt8AhsMAACiwAf9ERNcCrc37OuTEuIAijBi" "\n"
            "5GheZcLuzuciwgwRRcDqgNcGNw7bK07it3L2miqcFFG5b7+W3e5ZrYmNAfZJDJqu" "\n"
            "hJ0oSwn/HkRpbzK4/QFCizLEWlyaFPIgk6Om97pJ0Z7vzSG8/DqX+ch8xqkMYO6Z" "\n"
            "V/lqP/96SKIxfjaEj3N1fxNMmj5jf5smIxVNBLc9jO3Ub2TPEK7NiXlD56nz397H" "\n"
            "5Nkvoi/50Wj2uhcp61nciL/uAnXOL8ZqdxULJP/lAFA/apMT2NBT2a7CegJN+iRf" "\n"
            "5sCnvtFQlErN1//k5XuIpa0AlBsEFR+PoJ7b3haTFbXpu2NYeS8J20yJbB1xMomK" "\n"
            "zA==" "\n"
            "=S0dp" "\n"
            "-----END PGP PRIVATE KEY BLOCK-----";

            
            
            
            std::string private_key_arm =
            "-----BEGIN PGP PRIVATE KEY BLOCK-----" "\n"
            "Version: GnuPG v1.4.11 (GNU/Linux)" "\n"
            "" "\n"
            "lIYEWiWkHRYJKwYBBAHaRw8BAQdAgdPJ/4hrTXoKWEieZOS847vE5I1x4Bdw5Aip" "\n"
            "WPXVsqf+BwMC1sJUj23/AorjdlM5tauKSgB62Dy3y5RIlhNQ3Pge4DRO2yrnp3YN" "\n"
            "M1r/IaSMFg92MjKY3dyQoJOMVKidpDWQQmmIuX7ay8Tn5WHM6HHrY7Q1ZmVuZ0Bw" "\n"
            "cm90b25tYWlsLmNvbSAodGVzdCBmZW5nKSA8ZmVuZ0Bwcm90b25tYWlsLmNvbT6I" "\n"
            "kAQTFgoAOBYhBNkyyxHaenqw2l9m2IVNHDKVqHb9BQJaJaQdAhsDBQsJCAcDBRUK" "\n"
            "CQgLBRYCAwEAAh4BAheAAAoJEIVNHDKVqHb9MekBAL/KmbfU9s8gcBBLXJJ4hF0q" "\n"
            "d5QHYn2pZa8U/XBvhp8CAP0U9Xb5wgi070kEv6npSH7gP1XQyrSQBrNd2Qg7zYHg" "\n"
            "DpyLBFolpB0SCisGAQQBl1UBBQEBB0BcHZ45vrW5SLeagrhp4x/wBZI/G9O/7bR4" "\n"
            "876hd8ZucwMBCAf+BwMCVeGWUHR83xHjOIY1Re57etncgSQZXPz4JsNK2fdo4ljt" "\n"
            "3YslxUrnu9KU/s2esnl9aTvnzmCWDqFbFc8SXr9T3UP3/uJKGCrTL/X99ZdmGoh4" "\n"
            "BBgWCgAgFiEE2TLLEdp6erDaX2bYhU0cMpWodv0FAlolpB0CGwwACgkQhU0cMpWo" "\n"
            "dv3jowEA7hYCbQ/ddVpue+wk7SDAPEX8foKstYFyeT6/PouBgJQA/2KfIzQcn1jF" "\n"
            "GouZvTVI/4QrM7ibsv3SOusapg1oXSAI" "\n"
            "=GE4U" "\n"
            "-----END PGP PRIVATE KEY BLOCK-----";
            
            std::string public_key_arm =
            "-----BEGIN PGP PUBLIC KEY BLOCK-----" "\n"
            "Version: GnuPG v1.4.11 (GNU/Linux)" "\n"
            "" "\n"
            "mDMEWiWkHRYJKwYBBAHaRw8BAQdAgdPJ/4hrTXoKWEieZOS847vE5I1x4Bdw5Aip" "\n"
            "WPXVsqe0NWZlbmdAcHJvdG9ubWFpbC5jb20gKHRlc3QgZmVuZykgPGZlbmdAcHJv" "\n"
            "dG9ubWFpbC5jb20+iJAEExYKADgWIQTZMssR2np6sNpfZtiFTRwylah2/QUCWiWk" "\n"
            "HQIbAwULCQgHAwUVCgkICwUWAgMBAAIeAQIXgAAKCRCFTRwylah2/THpAQC/ypm3" "\n"
            "1PbPIHAQS1ySeIRdKneUB2J9qWWvFP1wb4afAgD9FPV2+cIItO9JBL+p6Uh+4D9V" "\n"
            "0Mq0kAazXdkIO82B4A64OARaJaQdEgorBgEEAZdVAQUBAQdAXB2eOb61uUi3moK4" "\n"
            "aeMf8AWSPxvTv+20ePO+oXfGbnMDAQgHiHgEGBYKACAWIQTZMssR2np6sNpfZtiF" "\n"
            "TRwylah2/QUCWiWkHQIbDAAKCRCFTRwylah2/eOjAQDuFgJtD911Wm577CTtIMA8" "\n"
            "Rfx+gqy1gXJ5Pr8+i4GAlAD/Yp8jNByfWMUai5m9NUj/hCszuJuy/dI66xqmDWhd" "\n"
            "IAg=" "\n"
            "=jCWa" "\n"
            "-----END PGP PUBLIC KEY BLOCK-----";
            
            //PGPPublicKey pub_key(pub_key_armor);
            //PGPSecretKey priv_key(priv_key_armor);
//            
//            PGPPublicKey public_key(public_key_arm);
//            PGPSecretKey private_key(private_key_arm);
            
            
            //VERIFY_IS_TRUE(private_key.)
//            std::cout << "" << std::endl;
            
        }
    }
}


