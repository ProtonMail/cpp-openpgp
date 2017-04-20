//
//  bcrypt_tests.cpp
//  OpenPGP
//
//  Created by Yanfeng Zhang on 3/28/17.
//  Copyright © 2017 Yanfeng Zhang. All rights reserved.
//

#include "utils_test.h"

#include <string>
#include <vector>
#include <hash/Hashes.h>
#include <hash/bcrypt.hpp>
#include <codecvt>

using namespace ProtonMail;

namespace tests {
    namespace hash_tests {
        SUITE(bcrypt)
        {
            std::vector<std::vector<std::string>> test_vectors = {
                { "", "$2a$06$DCq7YPn5Rq63x1Lad4cll.", "$2a$06$DCq7YPn5Rq63x1Lad4cll.TV4S6ytwfsfvkgY8jIucDrjc8deX1s."},
                { "", "$2a$08$HqWuK6/Ng6sg9gQzbLrgb.", "$2a$08$HqWuK6/Ng6sg9gQzbLrgb.Tl.ZHfXLhvt/SgVyWhQqgqcZ7ZuUtye" },
                { "", "$2a$10$k1wbIrmNyFAPwPVPSVa/ze", "$2a$10$k1wbIrmNyFAPwPVPSVa/zecw2BCEnBwVS2GbrmgzxFUOqW9dk4TCW" },
                { "", "$2a$12$k42ZFHFWqBp3vWli.nIn8u", "$2a$12$k42ZFHFWqBp3vWli.nIn8uYyIkbvYRvodzbfbK18SSsY.CsIQPlxO" },
                { "a", "$2a$06$m0CrhHm10qJ3lXRY.5zDGO", "$2a$06$m0CrhHm10qJ3lXRY.5zDGO3rS2KdeeWLuGmsfGlMfOxih58VYVfxe" },
                { "a", "$2a$08$cfcvVd2aQ8CMvoMpP2EBfe", "$2a$08$cfcvVd2aQ8CMvoMpP2EBfeodLEkkFJ9umNEfPD18.hUF62qqlC/V." },
                { "a", "$2a$10$k87L/MF28Q673VKh8/cPi.", "$2a$10$k87L/MF28Q673VKh8/cPi.SUl7MU/rWuSiIDDFayrKk/1tBsSQu4u" },
                { "a", "$2a$12$8NJH3LsPrANStV6XtBakCe", "$2a$12$8NJH3LsPrANStV6XtBakCez0cKHXVxmvxIlcz785vxAIZrihHZpeS" },
                { "abc", "$2a$06$If6bvum7DFjUnE9p2uDeDu", "$2a$06$If6bvum7DFjUnE9p2uDeDu0YHzrHM6tf.iqN8.yx.jNN1ILEf7h0i" },
                { "abc", "$2a$08$Ro0CUfOqk6cXEKf3dyaM7O", "$2a$08$Ro0CUfOqk6cXEKf3dyaM7OhSCvnwM9s4wIX9JeLapehKK5YdLxKcm" },
                { "abc", "$2a$10$WvvTPHKwdBJ3uk0Z37EMR.", "$2a$10$WvvTPHKwdBJ3uk0Z37EMR.hLA2W6N9AEBhEgrAOljy2Ae5MtaSIUi" },
                { "abc", "$2a$12$EXRkfkdmXn2gzds2SSitu.", "$2a$12$EXRkfkdmXn2gzds2SSitu.MW9.gAVqa9eLS1//RYtYCmB1eLHg.9q" },
                { "abcdefghijklmnopqrstuvwxyz", "$2a$06$.rCVZVOThsIa97pEDOxvGu", "$2a$06$.rCVZVOThsIa97pEDOxvGuRRgzG64bvtJ0938xuqzv18d3ZpQhstC" },
                { "abcdefghijklmnopqrstuvwxyz", "$2a$08$aTsUwsyowQuzRrDqFflhge", "$2a$08$aTsUwsyowQuzRrDqFflhgekJ8d9/7Z3GV3UcgvzQW3J5zMyrTvlz." },
                { "abcdefghijklmnopqrstuvwxyz", "$2a$10$fVH8e28OQRj9tqiDXs1e1u", "$2a$10$fVH8e28OQRj9tqiDXs1e1uxpsjN0c7II7YPKXua2NAKYvM6iQk7dq" },
                { "abcdefghijklmnopqrstuvwxyz", "$2a$12$D4G5f18o7aMMfwasBL7Gpu", "$2a$12$D4G5f18o7aMMfwasBL7GpuQWuP3pkrZrOAnqP.bmezbMng.QwJ/pG" },
                { "~!@#$%^&*()      ~!@#$%^&*()PNBFRD", "$2a$06$fPIsBO8qRqkjj273rfaOI.", "$2a$06$fPIsBO8qRqkjj273rfaOI.HtSV9jLDpTbZn782DC6/t7qT67P6FfO" },
                { "~!@#$%^&*()      ~!@#$%^&*()PNBFRD", "$2a$08$Eq2r4G/76Wv39MzSX262hu", "$2a$08$Eq2r4G/76Wv39MzSX262huzPz612MZiYHVUJe/OcOql2jo4.9UxTW" },
                { "~!@#$%^&*()      ~!@#$%^&*()PNBFRD", "$2a$10$LgfYWkbzEvQ4JakH7rOvHe", "$2a$10$LgfYWkbzEvQ4JakH7rOvHe0y8pHKF9OaFgwUZ2q7W2FFZmZzJYlfS" },
                { "~!@#$%^&*()      ~!@#$%^&*()PNBFRD", "$2a$12$WApznUOJfkEGSmYRfnkrPO", "$2a$12$WApznUOJfkEGSmYRfnkrPOr466oFDCaj4b6HY3EXGvfxm43seyhgC" },
            };

            TEST(testHashpw) {
                {
                    std::cout << "BCrypt::hashpw(): ";
                    for (int i = 0; i < test_vectors.size(); i++) {
                        ProtonMail::BCrypt bcrypt;
                        std::string plain = test_vectors[i][0];
                        std::string salt = test_vectors[i][1];
                        std::string expected = test_vectors[i][2];
                        std::string hashed = bcrypt.hashpw(plain, salt);
                        VERIFY_ARE_EQUAL(hashed, expected);
                        std::cout << ".";
                    }
                    std::cout << std::endl;
                }
            }
            
            /**
             * Test method for 'BCrypt.gensalt(int)'
             */
            TEST(testGensaltInt) {
                {
                    std::cout << "BCrypt.gensalt(log_rounds): ";
                    for (int i = 4; i <= 12; i++) {
                        std::cout << " " << std::to_string(i) << ":";
                        for (int j = 0; j < test_vectors.size(); j += 4) {
                            ProtonMail::BCrypt bcrypt;
                            std::string plain = test_vectors[j][0];
                            std::string salt = bcrypt.gensalt(i);
                            std::string hashed1 = bcrypt.hashpw(plain, salt);
                            std::string hashed2 = bcrypt.hashpw(plain, hashed1);
                            VERIFY_ARE_EQUAL(hashed1, hashed2);
                            std::cout << ".";
                        }
                    }
                    std::cout << std::endl;
                }
            }
            
            /**
             * Test method for 'BCrypt.gensalt()'
             */
            TEST(testGensalt) {
                {
                    std::cout << "BCrypt::gensalt(): ";
                    for (int i = 0; i < test_vectors.size(); i += 4) {
                        ProtonMail::BCrypt bcrypt;
                        std::string plain = test_vectors[i][0];
                        std::string salt = bcrypt.gensalt();
                        std::string hashed1 = bcrypt.hashpw(plain, salt);
                        std::string hashed2 = bcrypt.hashpw(plain, hashed1);
                        VERIFY_ARE_EQUAL(hashed1, hashed2);
                        std::cout << ".";
                    }
                    std::cout << std::endl;
                }
            }
            
            /**
             * Test method for 'BCrypt.checkpw(String, String)'
             * expecting success
             */
            TEST(testCheckpw_success) {
                {
                    std::cout << "BCrypt.checkpw w/ good passwords: ";
                    for (int i = 0; i < test_vectors.size(); i++) {
                        ProtonMail::BCrypt bcrypt;
                        std::string plain = test_vectors[i][0];
                        std::string expected = test_vectors[i][2];
                        VERIFY_IS_TRUE(bcrypt.checkpw(plain, expected));
                        std::cout << ".";
                    }
                    std::cout << std::endl;
                }
            }
            
            /**
             * Test method for 'BCrypt.checkpw(String, String)'
             * expecting failure
             */
            TEST(testCheckpw_failure) {
                {
                    std::cout << "BCrypt.checkpw w/ bad passwords: ";
                    for (int i = 0; i < test_vectors.size(); i++) {
                        int broken_index = (i + 4) % test_vectors.size();
                        ProtonMail::BCrypt bcrypt;
                        std::string plain = test_vectors[i][0];
                        std::string expected = test_vectors[broken_index][2];
                        VERIFY_IS_FALSE(bcrypt.checkpw(plain, expected));
                        std::cout << ".";
                    }
                    std::cout << std::endl;
                }
            }
            /**
             * Test for correct hashing of non-US-ASCII passwords
             */
            TEST(testInternationalChars) {
                {
                    std::cout << "BCrypt.hashpw w/ international chars: ";
                    std::wstring wpw1 = L"\u2605\u2605\u2605\u2605\u2605\u2605\u2605\u2605";
                    std::string pw2 = "????????";
                    
                    using convert_typeX = std::codecvt_utf8<wchar_t>;
                    std::wstring_convert<convert_typeX, wchar_t> converterX;
                    std::string pw1 = converterX.to_bytes(wpw1);
                    
                    ProtonMail::BCrypt bcrypt;
                    std::string h1 = bcrypt.hashpw(pw1, bcrypt.gensalt());
                    VERIFY_IS_FALSE(bcrypt.checkpw(pw2, h1));
                    
                    std::cout << ".";
                    
                    std::string h2 = bcrypt.hashpw(pw2, bcrypt.gensalt());
                    VERIFY_IS_FALSE(bcrypt.checkpw(pw1, h2));
                    
                    std::cout << ".";
                    std::cout << std::endl;
                }
            }
        }
    }
}
