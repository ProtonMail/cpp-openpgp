//
//  bignumber.cpp
//  OpenPGP_OSX_Lib
//
//  Created by Yanfeng Zhang on 10/13/16.
//  Copyright © 2016 Yanfeng Zhang. All rights reserved.
//

#include "utilities/bignumber.h"

#include <vector>
#include <string>
#include <sstream>
#include <algorithm>

namespace ProtonMail {
    namespace BN {
        Biginteger toBI(const std::string &input) {
            std::vector<uint8_t> revered(input.rbegin(), input.rend());
            BIGNUM* bn = BN_bin2bn((unsigned char*)revered.data(), static_cast<int>(revered.size()), NULL);
            return Biginteger(bn, [](BIGNUM* ptr) {
                BN_free(ptr);
            });
        }
        
        int num_bits(const Biginteger &input) {
            if (input == nullptr) {
                throw std::runtime_error("Error: num_bits input can't be null");
            }
            return BN_num_bits(input.get());
        }
        
        Biginteger dup(const Biginteger &a) {
            if (a == nullptr) {
                throw std::runtime_error("Error: dup input can't be null");
            }
            BIGNUM* dup = BN_dup(a.get());
            return Biginteger(dup, [](BIGNUM* ptr) {
                BN_free(ptr);
            });
        }
        
        const Biginteger one() {
            BIGNUM* one = BN_new();
            BN_one(one);
            return Biginteger(one, [](BIGNUM* ptr) {
                BN_free(ptr);
            });
        }
        
        std::string fromBI(int bit_length, const Biginteger &input) {
            if (input == nullptr) {
                throw std::runtime_error("Error: fromBI input can't be null");
            }
            size_t length = 8192;
            uint8_t tmp_out[length];
            int i = BN_bn2bin(input.get(), tmp_out);
            
            std::vector<uint8_t> buffer(tmp_out, tmp_out + i);
            std::reverse(buffer.begin(), buffer.end());
            
            size_t buf_size = buffer.size();
            int out_size = bit_length / 8;
            
            std::vector<uint8_t> out;
            out.reserve(out_size);
            for(int k = 0 ; k < out_size ; k++ )
                out[k] = 0 ;
            
            for (int i = 0 ; i < out_size; i++) {
                if ( i< buf_size) {
                    out.push_back(buffer[i]);
                } else {
                    out.push_back(0);
                }
            }
            return std::string(out.begin(), out.end());
        }
        
        // generate a rand bn and compare with a & b
        Biginteger rand_and_comp(int bit_length, const Biginteger &compA /*modulusMinusOne*/, const Biginteger &compB /*bn_bitLength*/) {
            BIGNUM * rand = BN_new();
            do {
                BN_rand(rand, bit_length, 0, 0);
            } while (BN_cmp(rand, compA.get()) >= 0 || BN_cmp(rand, compB.get()) <= 0);
            return Biginteger(rand, [](BIGNUM* ptr) {
                BN_free(ptr);
            });
        }
        
        // the input can't be null -- will add the null check later
        // the return need to free
        // return = a ^ e % m
        Biginteger nnmod_exp(const Biginteger &a, const Biginteger &e, const Biginteger &m) {
            BN_CTX *ctx = BN_CTX_new();
            BIGNUM* cal_exp_before_mod = BN_new();
            BN_mod_exp(cal_exp_before_mod, a.get(), e.get(), m.get(), ctx);
            BN_CTX_free(ctx);
            
            Biginteger cal_out = Biginteger(cal_exp_before_mod, [](BIGNUM* ptr) {
                BN_free(ptr);
            });
            
            if (compareToZero(cal_out) < 0 ) {
                cal_out = add(cal_out, m);
            }
            return cal_out;
        }
        
        Biginteger subtract(const Biginteger &a, const Biginteger &b) {
            BIGNUM* cal_sub = BN_new(); //need free the out_bn
            BN_sub(cal_sub, a.get(), b.get());
            return Biginteger(cal_sub, [](BIGNUM* ptr) {
                BN_free(ptr);
            });
        }
        
        Biginteger rshift(const Biginteger &a, int n) {
            BIGNUM* bn_shifted = BN_new();
            BN_rshift(bn_shifted, a.get(), n);
            return Biginteger(bn_shifted, [](BIGNUM* ptr) {
                BN_free(ptr);
            });
        }
        
        Biginteger multiply(const Biginteger &a, const Biginteger &b) {
            BN_CTX *ctx = BN_CTX_new();
            BIGNUM* cal_mul = BN_new(); //need free the out_bn
            BN_mul(cal_mul, a.get(), b.get(), ctx);
            BN_CTX_free(ctx);
            
            return Biginteger(cal_mul, [](BIGNUM* ptr) {
                BN_free(ptr);
            });
        }
        
        // return = a % b positive number
        Biginteger nnmod(const Biginteger &a,  const Biginteger &b) {
            if (a == nullptr) {
                throw std::runtime_error("Error: nnmod input a can't be null");
            }
            if (b == nullptr) {
                throw std::runtime_error("Error: nnmod input b can't be null");
            }

            BN_CTX *ctx = BN_CTX_new();
            BIGNUM* cal_mod = BN_new(); //need free the out_bn
            BN_nnmod(cal_mod, a.get(), b.get(), ctx);
            BN_CTX_free(ctx);
            
            return Biginteger(cal_mod, [](BIGNUM* ptr) {
                BN_free(ptr);
            });
        }
        
        Biginteger add(const Biginteger &a, const Biginteger &b) {
            BIGNUM* cal_add = BN_new(); //need free the out_bn
            BN_add(cal_add, a.get(), b.get());
            return Biginteger(cal_add, [](BIGNUM* ptr) {
                BN_free(ptr);
            });
        }
        
        int compareToZero(const Biginteger &a) {
            //TODO add a check
            BIGNUM* zero = BN_new();
            BN_zero(zero);
            int ret = BN_cmp(a.get(), zero);
            BN_free(zero);
            return ret;
        }
        
        // return = ( a * b + c ) % d
        Biginteger mul_add_nnmod(const Biginteger &a, const Biginteger &b, const Biginteger &c, const Biginteger &d) {
            Biginteger cal_mul = multiply(a, b);
            Biginteger cal_add = add(cal_mul, c);
            Biginteger cal_mod = nnmod(cal_add, d);
            return cal_mod;
        }
        
        // need release bignum
        Biginteger valueOf(int value) {
            std::ostringstream os ;
            os << value ;
            std::string str_value =  os.str();
            
            BIGNUM * str_bn = BN_new();
            BN_dec2bn(&str_bn, (char *)str_value.c_str());
            
            return Biginteger(str_bn, [](BIGNUM* ptr) {
                BN_free(ptr);
            });
        }
    }
}
