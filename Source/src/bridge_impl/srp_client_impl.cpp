//
//  srp_client_impl.cpp
//  OpenPGP_OSX_Lib
//
//  Created by Yanfeng Zhang on 10/6/16.
//  Copyright © 2016 Yanfeng Zhang. All rights reserved.
//

#include <string>
#include <sstream>
#include <vector>
#include <iostream>
#include <algorithm>    // std::reverse
#include <hash/SHA512.h>

#include "bridge_impl/srp_client_impl.hpp"
#include "bridge/srp_proofs.hpp"
#include "utilities/bignumber.h"

namespace ProtonMail {
    
    SrpClientImpl::SrpClientImpl() {
        
    }
    
    SrpClientImpl::~SrpClientImpl() {
        
    }
    
    std::string SrpClientImpl::expand_hash(const std::string & input) {
        std::string str_input(input.begin(), input.end());
        unsigned char i = 0;
        std::stringstream s;
        
        str_input.insert(str_input.end(), i++);
        std::string sha_one = SHA512(str_input).digest();
        s << SHA512(str_input).digest();
        
        str_input.pop_back();
        str_input.insert(str_input.end(), i++);
        s << SHA512(str_input).digest();
        
        str_input.pop_back();
        str_input.insert(str_input.end(), i++);
        s << SHA512(str_input).digest();
        
        str_input.pop_back();
        str_input.insert(str_input.end(), i);
        s << SHA512(str_input).digest();
        
        std::string stream_string = s.str();
        return stream_string;
    }
    
    
    std::vector<uint8_t> SrpClient::expand_hash(const std::vector<uint8_t> & input) {
        std::string str_input(input.begin(), input.end());
        std::string out = SrpClientImpl::expand_hash(str_input);
        std::vector<uint8_t> buffer(out.begin(), out.end());
        return buffer;
    }
    
    SrpProofs SrpClient::generate_proofs(int32_t bit_length, const std::vector<uint8_t> & modulus_repr_bytes, const std::vector<uint8_t> & server_ephemeral_repr_bytes, const std::vector<uint8_t> & hashed_password_repr_bytes){
        
        if (modulus_repr_bytes.size() * 8 != bit_length) {
            throw std::runtime_error("Error: modulus size is invalid");
        }
        if (server_ephemeral_repr_bytes.size() * 8 != bit_length) {
            throw std::runtime_error("Error: server ephemeral size is invalid");
        }
        if (hashed_password_repr_bytes.size() * 8 != bit_length) {
            throw std::runtime_error("Error: hased passowrd size is invalid");
        }
        
        auto modulus_repr = std::string(modulus_repr_bytes.begin(), modulus_repr_bytes.end());
        auto server_ephemeral_repr = std::string(server_ephemeral_repr_bytes.begin(), server_ephemeral_repr_bytes.end());
        auto hashed_password_repr = std::string(hashed_password_repr_bytes.begin(), hashed_password_repr_bytes.end());
        
        BIGNUM* modulus = BN::toBI(modulus_repr);
        BIGNUM* serverEphemeral =  BN::toBI(server_ephemeral_repr);
        BIGNUM* hashedPassword = BN::toBI(hashed_password_repr);
        
        int modulus_bites = BN_num_bits(modulus);
        if (modulus_bites != bit_length) {
            throw std::runtime_error("Error: modulus size is invalid");
        }
        
        BIGNUM* generator = BN::valueOf(2);
        
        std::cout << hexlify(BN::fromBI(bit_length, generator)) << std::endl;
        
        std::stringstream tmp_s;
        std::string generateor_bytes = BN::fromBI(bit_length, generator);
        tmp_s << generateor_bytes;
        tmp_s << modulus_repr;
        std::string stream_string = tmp_s.str();
        std::string hashed_generator_modulusRepr = SrpClientImpl::expand_hash(stream_string);
        std::cout << hexlify(hashed_generator_modulusRepr) << std::endl;
        
        BIGNUM* multiplier_before_mod = BN::toBI(hashed_generator_modulusRepr);
        
        BIGNUM * multiplier = BN_new();
        BN_CTX *ctx = BN_CTX_new();
        
        BN_nnmod(multiplier, multiplier_before_mod, modulus, ctx);
        
        BIGNUM* modulusMinusOne = BN_dup(modulus);
        BN_clear_bit(modulusMinusOne, 0);
        
        const BIGNUM* bn_one = BN_value_one();
        if (BN_cmp(multiplier, bn_one) <= 0 || BN_cmp(multiplier, modulusMinusOne) >= 0) {
            throw std::runtime_error("multiplier compare value invalid");
        }
        
        if (BN_cmp(serverEphemeral, bn_one) <= 0 || BN_cmp(serverEphemeral, modulusMinusOne) >= 0) {
            throw std::runtime_error("serverEphemeral compare value invalid");
        }
        
        BIGNUM* bn_shifted = BN_new();
        BN_rshift(bn_shifted, modulus, 1);
        if (!BN_is_prime(modulus, 10, NULL, NULL, NULL) || !BN_is_prime(bn_shifted, 10, NULL, NULL, NULL)) {
            throw std::runtime_error("BN_is_prime check failed");
        }
        
        BIGNUM * bn_bitLength = BN::valueOf(bit_length * 2);
        std::cout << hexlify(BN::fromBI(bit_length, bn_bitLength)) << std::endl;
        
        BIGNUM * clientSecret = BN_new();
        BIGNUM * clientEphemeral;
        BIGNUM * scramblingParam = BN_new();
        
        do {
            
            do {
                
                BN_rand(clientSecret,bit_length,0,0);
                int length = BN_num_bits(clientSecret);
                char *show = BN_bn2dec(clientSecret);
                
                printf("length:%d,rnd:%s\n",length,show);

            } while (BN_cmp(clientSecret, modulusMinusOne) >= 0 || BN_cmp(clientSecret, bn_bitLength) <= 0);
            
            clientEphemeral = BN::nnmod_exp(generator, clientSecret, modulus);
            
            std::cout << hexlify(BN::fromBI(bit_length, clientEphemeral)) << std::endl;
            
            std::stringstream scrambling_param_stream;
            scrambling_param_stream << BN::fromBI(bit_length, clientEphemeral);
            scrambling_param_stream << serverEphemeral;
            std::string scramblingParam_bytes = scrambling_param_stream.str();
            
            scramblingParam = BN::toBI(SrpClientImpl::expand_hash(scramblingParam_bytes));
            std::cout << hexlify(BN::fromBI(bit_length, scramblingParam)) << std::endl;
            
        } while (BN::compareToZero(clientSecret) == 0);
        
        //all return values need free
        BIGNUM * cal_nnmod_exp = BN::nnmod_exp(generator, hashedPassword, modulus);
        BIGNUM * cal_mul = BN::multiply(cal_nnmod_exp, multiplier);
        BIGNUM * cal_mod = BN::nnmod(cal_mul, modulus);
        
        BIGNUM * subtracted = BN::subtract(serverEphemeral, cal_mod);
        if (BN::compareToZero(subtracted) < 0) {
            BIGNUM * tmp = BN::add(subtracted, modulus);
            BN_free(subtracted);
            subtracted = tmp;
        }
        
        BIGNUM* exponent = BN::mul_add_nnmod(scramblingParam, hashedPassword, clientSecret, modulusMinusOne);
        BIGNUM* sharedSession = BN::nnmod_exp(subtracted, exponent, modulus);
        
        std::string clientEphemeralRepr = BN::fromBI(bit_length, clientEphemeral);
        
        
        std::cout << hexlify(clientEphemeralRepr) << std::endl;
        
        
        std::stringstream client_proof_stream;
        client_proof_stream << clientEphemeralRepr;
        client_proof_stream << serverEphemeral;
        client_proof_stream << BN::fromBI(bit_length, sharedSession);
        
        std::string clientProof = SrpClientImpl::expand_hash(client_proof_stream.str());
        
        std::cout << hexlify(clientProof) << std::endl;
        
        std::stringstream server_proof_stream;
        server_proof_stream << clientEphemeralRepr;
        server_proof_stream << clientProof;
        server_proof_stream << BN::fromBI(bit_length, sharedSession);
        
        std::string serverProof = SrpClientImpl::expand_hash(server_proof_stream.str());
        
        std::cout << hexlify(serverProof) << std::endl;
        
        ProtonMail::SrpProofs s(std::vector<uint8_t>(clientEphemeralRepr.begin(), clientEphemeralRepr.end()),
                                std::vector<uint8_t>(clientProof.begin(), clientProof.end()),
                                std::vector<uint8_t>(serverProof.begin(), serverProof.end()));
        return s;
    }
    
    std::vector<uint8_t> SrpClient::generate_Verifier(int32_t bit_length, const std::vector<uint8_t> & modulus_repr, const std::vector<uint8_t> & hashed_password_repr)
    {
        std::string modulusRepr = std::string(modulus_repr.begin(), modulus_repr.end());
        BIGNUM* modulus = BN::toBI(modulusRepr);
        BIGNUM* generator = BN::valueOf(2);
        std::string hashedPasswordRepr = std::string(hashed_password_repr.begin(), hashed_password_repr.end());
        BIGNUM* hashedPassword  = BN::toBI(hashedPasswordRepr);
        BIGNUM* cal_mod_pow = BN::nnmod_exp(generator, hashedPassword, modulus);
        
        std::string str_out = BN::fromBI(bit_length, cal_mod_pow);
        
        BN_free(modulus);
        BN_free(generator);
        BN_free(hashedPassword);
        BN_free(cal_mod_pow);
        
        return std::vector<uint8_t>(str_out.begin(), str_out.end());
    }
    
}
