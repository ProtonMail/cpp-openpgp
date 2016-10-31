//
//  sha_tests.cpp
//  OpenPGP
//
//  Created by Yanfeng Zhang on 10/28/16.
//  Copyright © 2016 Yanfeng Zhang. All rights reserved.
//

#import "utils_test.h"
#include <hash/Hashes.h>

namespace tests {
    namespace hash_tests {
        SUITE(sha)
        {
            //SHA* with test vectors from NIST FIPS 180-2
            TEST(SHA_1) {
                {
                    auto hash = SHA1("abc");
                    auto hash_out = hash.hexdigest();
                    VERIFY_ARE_EQUAL((hash_out), "a9993e364706816aba3e25717850c26c9cd0d89d");
                }
                {
                    auto hash = SHA1("abcdbcdecdefdefgefghfghighijhijkijkljklmklmnlmnomnopnopq");
                    auto hash_out = hash.hexdigest();
                    VERIFY_ARE_EQUAL((hash_out), "84983e441c3bd26ebaae4aa1f95129e5e54670f1");
                }

                // Test vectors from <http://csrc.nist.gov/groups/STM/cavp/documents/shs/shabytetestvectors.zip>
                const std::vector<std::string> SHA1_SHORT_MSG = {
                    "",
                    "36",
                    "195a",
                    "df4bd2",
                    "549e959e",
                    "f7fb1be205",
                    "c0e5abeaea63",
                    "63bfc1ed7f78ab",
                    "7e3d7b3eada98866",
                    "9e61e55d9ed37b1c20",
                    "9777cf90dd7c7e863506",
                    "4eb08c9e683c94bea00dfa",
                    "0938f2e2ebb64f8af8bbfc91",
                    "74c9996d14e87d3e6cbea7029d",
                    "51dca5c0f8e5d49596f32d3eb874",
                    "3a36ea49684820a2adc7fc4175ba78",
                    "3552694cdf663fd94b224747ac406aaf",
                    "f216a1cbde2446b1edf41e93481d33e2ed",
                    "a3cf714bf112647e727e8cfd46499acd35a6",
                    "148de640f3c11591a6f8c5c48632c5fb79d3b7",
                    "63a3cc83fd1ec1b6680e9974a0514e1a9ecebb6a",
                    "875a90909a8afc92fb7070047e9d081ec92f3d08b8",
                    "444b25f9c9259dc217772cc4478c44b6feff62353673",
                    "487351c8a5f440e4d03386483d5fe7bb669d41adcbfdb7",
                    "46b061ef132b87f6d3b0ee2462f67d910977da20aed13705",
                    "3842b6137bb9d27f3ca5bafe5bbb62858344fe4ba5c41589a5",
                    "44d91d3d465a4111462ba0c7ec223da6735f4f5200453cf132c3",
                    "cce73f2eabcb52f785d5a6df63c0a105f34a91ca237fe534ee399d",
                    "664e6e7946839203037a65a12174b244de8cbc6ec3f578967a84f9ce",
                    "9597f714b2e45e3399a7f02aec44921bd78be0fefee0c5e9b499488f6e",
                    "75c5ad1f3cbd22e8a95fc3b089526788fb4ebceed3e7d4443da6e081a35e",
                    "dd245bffe6a638806667768360a95d0574e1a0bd0d18329fdb915ca484ac0d",
                    "0321794b739418c24e7c2e565274791c4be749752ad234ed56cb0a6347430c6b",
                    "4c3dcf95c2f0b5258c651fcd1d51bd10425d6203067d0748d37d1340d9ddda7db3",
                    "b8d12582d25b45290a6e1bb95da429befcfdbf5b4dd41cdf3311d6988fa17cec0723",
                    "6fda97527a662552be15efaeba32a3aea4ed449abb5c1ed8d9bfff544708a425d69b72",
                    "09fa2792acbb2417e8ed269041cc03c77006466e6e7ae002cf3f1af551e8ce0bb506d705",
                    "5efa2987da0baf0a54d8d728792bcfa707a15798dc66743754406914d1cfe3709b1374eaeb",
                    "2836de99c0f641cd55e89f5af76638947b8227377ef88bfba662e5682babc1ec96c6992bc9a0",
                    "42143a2b9e1d0b354df3264d08f7b602f54aad922a3d63006d097f683dc11b90178423bff2f7fe",
                    "eb60c28ad8aeda807d69ebc87552024ad8aca68204f1bcd29dc5a81dd228b591e2efb7c4df75ef03",
                    "7de4ba85ec54747cdc42b1f23546b7e490e31280f066e52fac117fd3b0792e4de62d5843ee98c72015",
                    "e70653637bc5e388ccd8dc44e5eace36f7398f2bac993042b9bc2f4fb3b0ee7e23a96439dc01134b8c7d",
                    "dd37bc9f0b3a4788f9b54966f252174c8ce487cbe59c53c22b81bf77621a7ce7616dcb5b1e2ee63c2c309b",
                    "5f485c637ae30b1e30497f0fb7ec364e13c906e2813daa34161b7ac4a4fd7a1bddd79601bbd22cef1f57cbc7",
                    "f6c237fb3cfe95ec8414cc16d203b4874e644cc9a543465cad2dc563488a659e8a2e7c981e2a9f22e5e868ffe1",
                    "da7ab3291553c659873c95913768953c6e526d3a26590898c0ade89ff56fbd110f1436af590b17fed49f8c4b2b1e",
                    "8cfa5fd56ee239ca47737591cba103e41a18acf8e8d257b0dbe8851134a81ff6b2e97104b39b76e19da256a17ce52d",
                    "57e89659d878f360af6de45a9a5e372ef40c384988e82640a3d5e4b76d2ef181780b9a099ac06ef0f8a7f3f764209720",
                    "b91e64235dbd234eea2ae14a92a173ebe835347239cff8b02074416f55c6b60dc6ced06ae9f8d705505f0d617e4b29aef9",
                    "e42a67362a581e8cf3d847502215755d7ad425ca030c4360b0f7ef513e6980265f61c9fa18dd9ce668f38dbc2a1ef8f83cd6",
                    "634db92c22010e1cbf1e1623923180406c515272209a8acc42de05cc2e96a1e94c1f9f6b93234b7f4c55de8b1961a3bf352259",
                    "cc6ca3a8cb391cd8a5aff1faa7b3ffbdd21a5a3ce66cfaddbfe8b179e4c860be5ec66bd2c6de6a39a25622f9f2fcb3fc05af12b5",
                    "7c0e6a0d35f8ac854c7245ebc73693731bbbc3e6fab644466de27bb522fcb99307126ae718fe8f00742e6e5cb7a687c88447cbc961",
                    "c5581d40b331e24003901bd6bf244aca9e9601b9d81252bb38048642731f1146b8a4c69f88e148b2c8f8c14f15e1d6da57b2daa9991e",
                    "ec6b4a88713df27c0f2d02e738b69db43abda3921317259c864c1c386e9a5a3f533dc05f3beeb2bec2aac8e06db4c6cb3cddcf697e03d5",
                    "0321736beba578e90abc1a90aa56157d871618f6de0d764cc8c91e06c68ecd3b9de3824064503384db67beb7fe012232dacaef93a000fba7",
                    "d0a249a97b5f1486721a50d4c4ab3f5d674a0e29925d5bf2678ef6d8d521e456bd84aa755328c83fc890837726a8e7877b570dba39579aabdd",
                    "c32138531118f08c7dcc292428ad20b45ab27d9517a18445f38b8f0c2795bcdfe3ffe384e65ecbf74d2c9d0da88398575326074904c1709ba072",
                    "b0f4cfb939ea785eabb7e7ca7c476cdd9b227f015d905368ba00ae96b9aaf720297491b3921267576b72c8f58d577617e844f9f0759b399c6b064c",
                    "bd02e51b0cf2c2b8d204a026b41a66fbfc2ac37ee9411fc449c8d1194a0792a28ee731407dfc89b6dfc2b10faa27723a184afef8fd83def858a32d3f",
                    "e33146b83e4bb671392218da9a77f8d9f5974147182fb95ba662cb66011989c16d9af104735d6f79841aa4d1df276615b50108df8a29dbc9de31f4260d",
                    "411c13c75073c1e2d4b1ecf13139ba9656cd35c14201f1c7c6f0eeb58d2dbfe35bfdeccc92c3961cfabb590bc1eb77eac15732fb0275798680e0c7292e50",
                    "f2c76ef617fa2bfc8a4d6bcbb15fe88436fdc2165d3074629579079d4d5b86f5081ab177b4c3f530376c9c924cbd421a8daf8830d0940c4fb7589865830699",
                    "45927e32ddf801caf35e18e7b5078b7f5435278212ec6bb99df884f49b327c6486feae46ba187dc1cc9145121e1492e6b06e9007394dc33b7748f86ac3207cfe",
                };
                
                static const std::vector<std::string> SHA1_SHORT_MSG_HEXDIGEST = {
                    "da39a3ee5e6b4b0d3255bfef95601890afd80709",
                    "c1dfd96eea8cc2b62785275bca38ac261256e278",
                    "0a1c2d555bbe431ad6288af5a54f93e0449c9232",
                    "bf36ed5d74727dfd5d7854ec6b1d49468d8ee8aa",
                    "b78bae6d14338ffccfd5d5b5674a275f6ef9c717",
                    "60b7d5bb560a1acf6fa45721bd0abb419a841a89",
                    "a6d338459780c08363090fd8fc7d28dc80e8e01f",
                    "860328d80509500c1783169ebf0ba0c4b94da5e5",
                    "24a2c34b976305277ce58c2f42d5092031572520",
                    "411ccee1f6e3677df12698411eb09d3ff580af97",
                    "05c915b5ed4e4c4afffc202961f3174371e90b5c",
                    "af320b42d7785ca6c8dd220463be23a2d2cb5afc",
                    "9f4e66b6ceea40dcf4b9166c28f1c88474141da9",
                    "e6c4363c0852951991057f40de27ec0890466f01",
                    "046a7b396c01379a684a894558779b07d8c7da20",
                    "d58a262ee7b6577c07228e71ae9b3e04c8abcda9",
                    "a150de927454202d94e656de4c7c0ca691de955d",
                    "35a4b39fef560e7ea61246676e1b7e13d587be30",
                    "7ce69b1acdce52ea7dbd382531fa1a83df13cae7",
                    "b47be2c64124fa9a124a887af9551a74354ca411",
                    "8bb8c0d815a9c68a1d2910f39d942603d807fbcc",
                    "b486f87fb833ebf0328393128646a6f6e660fcb1",
                    "76159368f99dece30aadcfb9b7b41dab33688858",
                    "dbc1cb575ce6aeb9dc4ebf0f843ba8aeb1451e89",
                    "d7a98289679005eb930ab75efd8f650f991ee952",
                    "fda26fa9b4874ab701ed0bb64d134f89b9c4cc50",
                    "c2ff7ccde143c8f0601f6974b1903eb8d5741b6e",
                    "643c9dc20a929608f6caa9709d843ca6fa7a76f4",
                    "509ef787343d5b5a269229b961b96241864a3d74",
                    "b61ce538f1a1e6c90432b233d7af5b6524ebfbe3",
                    "5b7b94076b2fc20d6adb82479e6b28d07c902b75",
                    "6066db99fc358952cf7fb0ec4d89cb0158ed91d7",
                    "b89962c94d60f6a332fd60f6f07d4f032a586b76",
                    "17bda899c13d35413d2546212bcd8a93ceb0657b",
                    "badcdd53fdc144b8bf2cc1e64d10f676eebe66ed",
                    "01b4646180f1f6d2e06bbe22c20e50030322673a",
                    "10016dc3a2719f9034ffcc689426d28292c42fc9",
                    "9f42fa2bce6ef021d93c6b2d902273797e426535",
                    "cdf48bacbff6f6152515323f9b43a286e0cb8113",
                    "b88fb75274b9b0fd57c0045988cfcef6c3ce6554",
                    "c06d3a6a12d9e8db62e8cff40ca23820d61d8aa7",
                    "6e40f9e83a4be93874bc97cdebb8da6889ae2c7a",
                    "3efc940c312ef0dfd4e1143812248db89542f6a5",
                    "a0cf03f7badd0c3c3c4ea3717f5a4fb7e67b2e56",
                    "a544e06f1a07ceb175a51d6d9c0111b3e15e9859",
                    "199d986ed991b99a071f450c6b1121a727e8c735",
                    "33bac6104b0ad6128d091b5d5e2999099c9f05de",
                    "76d7db6e18c1f4ae225ce8ccc93c8f9a0dfeb969",
                    "f652f3b1549f16710c7402895911e2b86a9b2aee",
                    "63faebb807f32be708cf00fc35519991dc4e7f68",
                    "0e6730bc4a0e9322ea205f4edfff1fffda26af0a",
                    "b61a3a6f42e8e6604b93196c43c9e84d5359e6fe",
                    "32d979ca1b3ed0ed8c890d99ec6dd85e6c16abf4",
                    "6f18190bd2d02fc93bce64756575cea36d08b1c3",
                    "68f525feea1d8dbe0117e417ca46708d18d7629a",
                    "a7272e2308622ff7a339460adc61efd0ea8dabdc",
                    "aef843b86916c16f66c84d83a6005d23fd005c9e",
                    "be2cd6f380969be59cde2dff5e848a44e7880bd6",
                    "e5eb4543deee8f6a5287845af8b593a95a9749a1",
                    "534c850448dd486787b62bdec2d4a0b140a1b170",
                    "6fbfa6e4edce4cc85a845bf0d228dc39acefc2fa",
                    "018872691d9b04e8220e09187df5bc5fa6257cd9",
                    "d98d512a35572f8bd20de62e9510cc21145c5bf4",
                    "9f3ea255f6af95c5454e55d7354cabb45352ea0b",
                    "a70cfbfe7563dd0e665c7c6715a96a8d756950c0",
                };
                
                {
                    VERIFY_ARE_EQUAL(SHA1_SHORT_MSG.size(), SHA1_SHORT_MSG_HEXDIGEST.size());
                    for ( unsigned int i = 0; i < SHA1_SHORT_MSG.size(); ++i ) {
                        auto sha1 = SHA1(unhexlify(SHA1_SHORT_MSG[i]));
                        VERIFY_ARE_EQUAL(sha1.hexdigest(), SHA1_SHORT_MSG_HEXDIGEST[i]);
                    }
                }
            }
            
            TEST(SHA_224) {
                {
                    auto hash = SHA224("abc");
                    auto hash_out = hash.hexdigest();
                    VERIFY_ARE_EQUAL((hash_out), "23097d223405d8228642a477bda255b32aadbce4bda0b3f7e36c9da7");
                }
                
                {
                    auto hash = SHA224("abcdbcdecdefdefgefghfghighijhijkijkljklmklmnlmnomnopnopq");
                    auto hash_out = hash.hexdigest();
                    VERIFY_ARE_EQUAL((hash_out), "75388b16512776cc5dba5da1fd890150b0c6455cb4f58b1952522525");
                }
            }
            
            TEST(SHA_256) {
                {
                    auto hash = SHA256("abc");
                    auto hash_out = hash.hexdigest();
                    VERIFY_ARE_EQUAL((hash_out), "ba7816bf8f01cfea414140de5dae2223b00361a396177a9cb410ff61f20015ad");
                }
                
                {
                    auto hash = SHA256("abcdbcdecdefdefgefghfghighijhijkijkljklmklmnlmnomnopnopq");
                    auto hash_out = hash.hexdigest();
                    VERIFY_ARE_EQUAL((hash_out), "248d6a61d20638b8e5c026930c3e6039a33ce45964ff2167f6ecedd419db06c1");
                }
            }
            
            TEST(SHA_384) {
                {
                    auto hash = SHA384("abc");
                    auto hash_out = hash.hexdigest();
                    VERIFY_ARE_EQUAL((hash_out), "cb00753f45a35e8bb5a03d699ac65007272c32ab0eded1631a8b605a43ff5bed8086072ba1e7cc2358baeca134c825a7");
                }
                
                {
                    auto hash = SHA384("abcdbcdecdefdefgefghfghighijhijkijkljklmklmnlmnomnopnopq");
                    auto hash_out = hash.hexdigest();
                    VERIFY_ARE_EQUAL((hash_out), "3391fdddfc8dc7393707a65b1b4709397cf8b1d162af05abfe8f450de5f36bc6b0455a8520bc4e6f5fe95b1fe3c8452b");
                }
            }
            
            TEST(SHA_512) {
                {
                    auto hash = SHA512("abc");
                    auto hash_out = hash.hexdigest();
                    VERIFY_ARE_EQUAL((hash_out), "ddaf35a193617abacc417349ae20413112e6fa4e89a97ea20a9eeee64b55d39a2192992a274fc1a836ba3c23a3feebbd454d4423643ce80e2a9ac94fa54ca49f");
                }
                
                {
                    auto hash = SHA512("abcdbcdecdefdefgefghfghighijhijkijkljklmklmnlmnomnopnopq");
                    auto hash_out = hash.hexdigest();
                    VERIFY_ARE_EQUAL((hash_out), "204a8fc6dda82f0a0ced7beb8e08a41657c16ef468b228a8279be331a703c33596fd15c13b1b07f9aa1d3bea57789ca031ad85c7a71dd70354ec631238ca3445");
                }
            }
        }
    }
}


