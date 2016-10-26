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
        BIGNUM* toBI(const std::string &input) {
            std::vector<uint8_t> revered(input.rbegin(), input.rend());
            
            BIGNUM* modulus = BN_bin2bn((unsigned char*)revered.data(), static_cast<int>(revered.size()), NULL);
            return modulus;
        }
        
        std::string fromBI(int bit_length, BIGNUM* input) {
            
            size_t length = 8192;
            uint8_t tmp_out[length];
            int i = BN_bn2bin(input, tmp_out);
            
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
        
        // the input can't be null -- will add the null check later
        // the return need to free
        // return = a ^ e % m
        BIGNUM* nnmod_exp(BIGNUM* a, BIGNUM* e, BIGNUM* m) {
            BN_CTX *ctx = BN_CTX_new();
            
            BIGNUM* cal_exp_before_mod = BN_new();
            BN_mod_exp(cal_exp_before_mod, a, e, m, ctx);
            
            BN_CTX_free(ctx);
            
            if ( compareToZero(cal_exp_before_mod) < 0 ) {
                BIGNUM * tmp = add(cal_exp_before_mod, m);
                BN_free(cal_exp_before_mod);
                cal_exp_before_mod = tmp;
            }
            
            return cal_exp_before_mod;
        }
        
        BIGNUM* subtract(BIGNUM* a, BIGNUM* b) {
            BIGNUM* cal_sub = BN_new(); //need free the out_bn
            BN_sub(cal_sub, a, b);
            return cal_sub;
        }
        
        BIGNUM* multiply(BIGNUM* a, BIGNUM* b) {
            BN_CTX *ctx = BN_CTX_new();
            BIGNUM* cal_mul = BN_new(); //need free the out_bn
            BN_mul(cal_mul, a, b, ctx);
            
            BN_CTX_free(ctx);
            return cal_mul;
        }
        
        // return = a % b positive number
        BIGNUM* nnmod(BIGNUM* a, BIGNUM* b) {
            BN_CTX *ctx = BN_CTX_new();
            BIGNUM* cal_mod = BN_new(); //need free the out_bn
            BN_nnmod(cal_mod, a, b, ctx);
            BN_CTX_free(ctx);
            return cal_mod;
        }
        
        BIGNUM* add(BIGNUM* a, BIGNUM* b) {
            BIGNUM* cal_add = BN_new(); //need free the out_bn
            BN_add(cal_add, a, b);
            return cal_add;
        }
        
        int compareToZero(BIGNUM* a) {
            BIGNUM* zero = BN_new();
            BN_zero(zero);
            int ret = BN_cmp(a, zero);
            BN_free(zero);
            return ret;
        }
        
        // return = ( a * b + c ) % d
        BIGNUM* mul_add_nnmod(BIGNUM* a, BIGNUM* b, BIGNUM* c, BIGNUM* d) {
            BIGNUM* cal_mul = multiply(a, b);
            BIGNUM* cal_add = add(cal_mul, c);
            BN_free(cal_mul);
            BIGNUM* cal_mod = nnmod(cal_add, d);
            BN_free(cal_add);
            return cal_mod;
        }
        
        // need release bignum
        BIGNUM* valueOf(int value) {
            std::ostringstream os ;
            os << value ;
            std::string str_value =  os.str();
            
            BIGNUM * str_bn = BN_new();
            BN_dec2bn(&str_bn, (char *)str_value.c_str());
            return str_bn;
        }
    }
}
