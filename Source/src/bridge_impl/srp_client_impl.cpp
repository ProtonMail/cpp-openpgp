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


namespace ProtonMail {
    
    
    BIGNUM* SrpClientImpl::toBI(const std::string &input) {
        std::vector<uint8_t> revered(input.rbegin(), input.rend());
        BIGNUM* modulus = BN_bin2bn((unsigned char*)revered.data(), revered.size(), NULL);
        return modulus;
    }
    
    std::string SrpClientImpl::fromBI(int bit_length, BIGNUM* input) {
        
        size_t length = 8192;
        uint8_t tmp_out[length];
        int i = BN_bn2bin(input, tmp_out);
        
        std::vector<uint8_t> buffer(tmp_out, tmp_out + i);
        std::reverse(buffer.begin(), buffer.end());
        
        int buf_size = buffer.size();
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
    BIGNUM* SrpClientImpl::nnmod_exp(BIGNUM* a, BIGNUM* e, BIGNUM* m) {
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
//        BIGNUM* cal_exp_before_mod = BN_new();
//        int i = BN_exp(cal_exp_before_mod, a, e, ctx);
//        
//        BIGNUM* cal_mod = BN_new(); //need free the out_bn
//        BN_nnmod(cal_mod, cal_exp_before_mod, m, ctx);
//        
//        BN_free(cal_exp_before_mod);
//        BN_CTX_free(ctx);
//        
//        return cal_mod;
    }
    
    BIGNUM* SrpClientImpl::subtract(BIGNUM* a, BIGNUM* b) {
        BIGNUM* cal_sub = BN_new(); //need free the out_bn
        BN_sub(cal_sub, a, b);
        return cal_sub;
    }
    
    BIGNUM* SrpClientImpl::multiply(BIGNUM* a, BIGNUM* b) {
        BN_CTX *ctx = BN_CTX_new();
        BIGNUM* cal_mul = BN_new(); //need free the out_bn
        BN_mul(cal_mul, a, b, ctx);
        
        BN_CTX_free(ctx);
        return cal_mul;
    }
    
    // return = a % b positive number
    BIGNUM* SrpClientImpl::nnmod(BIGNUM* a, BIGNUM* b) {
        BN_CTX *ctx = BN_CTX_new();
        BIGNUM* cal_mod = BN_new(); //need free the out_bn
        BN_nnmod(cal_mod, a, b, ctx);
        BN_CTX_free(ctx);
        return cal_mod;
    }
    
    BIGNUM* SrpClientImpl::add(BIGNUM* a, BIGNUM* b) {
        BIGNUM* cal_add = BN_new(); //need free the out_bn
        BN_add(cal_add, a, b);
        return cal_add;
    }
    
    int SrpClientImpl::compareToZero(BIGNUM* a) {
        BIGNUM* zero = BN_new();
        BN_zero(zero);
        if (BN_is_zero(zero)) {
            std::cout << "zero" << std::endl;
        }
        int ret = BN_cmp(a, zero);
        BN_free(zero);
        return ret;
    }
    
    // return = ( a * b + c ) % d
    BIGNUM* SrpClientImpl::mul_add_nnmod(BIGNUM* a, BIGNUM* b, BIGNUM* c, BIGNUM* d) {
        BIGNUM* cal_mul = multiply(a, b);
        BIGNUM* cal_add = add(cal_mul, c);
        BN_free(cal_mul);
        BIGNUM* cal_mod = nnmod(cal_add, d);
        BN_free(cal_add);
        return cal_mod;
    }
    
    // need release bignum
    BIGNUM* SrpClientImpl::valueOf(int value) {
        std::string str_value = std::to_string(value);
        BIGNUM * str_bn = BN_new();
        BN_dec2bn(&str_bn, (char *)str_value.c_str());
        return str_bn;
    }
    
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
    
    SrpProofs SrpClient::generate_proofs(int32_t bit_length, const std::vector<uint8_t> & modulus_repr, const std::vector<uint8_t> & server_ephemeral_repr, const std::vector<uint8_t> & hashed_password_repr){
        
        std::string tmp_modulus = "4bf8418265571e5a735318333a5b78bde137bf7067a5a5724455140cc99181c176c99539ad07106070c11ab9d002519d72c1a66557190b9d49809b4407abf96c1a719e7b2383c5e26d99b41985ce0e19bbaa48b9c0ce4010aa1329b64a68ab910f6f7ba4f4ec55da9475714d7640f19374379efdcde9910971c092d4869b96537efda7554e351f08c03da7225abce3a3f747e17024369e9227b317a0be51af444af5269a1b76bb5b5c03b32c7fbd10bc695bdd591566cdd071da13cf8957c4ec667858f96d29a8bfb1d7c8950703822a3aa2355957b09b1de0f5747f25f715bfee4539d4b8461effdf31a3eaaa1bf0ab8485bb4208aec1e98437b3dd1c70119d";
        std::string tmp_ephemeral = "e8712193bf16bdeaa6a700250f81c71b4fa4edf3b5a8fed96c052927db1df9e5ee895318c23158bb89f494b545583ce4f170693680c9626f39f7710915c09581ea7af9da9b53e46d1ef6055c9527df6cea8352330d6a509c0ef457bdea8102296f1381cf3aab799645a0c1377a33d63e4937af09edc7973be2810506fef85a4397661820788be0cfd0208c6114cae5002652b03e1a1aff3af1f6d8ba77ba9cd1bd5ff630c662c1ee9cb8b03fb74774183bf97107fc0474935e488c707cd44297a0744168509707cd83d1d4c3bd289ef8121275a743a12b67872e8c1646720085c6389c95575eb08f8499283d79b6ce403ef656b58ef760e6c102beed298d773d";
        std::string tmp_hashedpwd = "bc173fac3bcda272e2de5a0b9f4c2cc091158c57494868fe8e68be2d3ec3aca4e1c7808d7cd2a44f9708428151bcdb6aeadf69189cf90d39fca76a780549c53fc1bed6fabb63c80eaaadf5fabac5b301e6d7648d7cfc2aa9c707865f2654bdb352ae922e0b9d98ff671b82124c079a4f4555c94d58c8c040241deeb78c615337aefb9ffaa0cc4ace1df84d012196fee71f666b05998edc63b03c2cbfe0d170dc493e6169bc3d9876d87ddd392d9ac0994fa5090e141dd1451511592b4846094963dcddf68a4bca38d6998677e8310334ea11651b2393262d4b81837da86b4f329a3576d09e8868d29ce735793285219817ef4aa7373c9f862c51fee76054e0a6";
        
        std::string plain_modulus = unhexlify(tmp_modulus);
        std::string plain_ephemeral = unhexlify(tmp_ephemeral);
        std::string plain_hashedpwd = unhexlify(tmp_hashedpwd);
        
        if (modulus_repr.size() * 8 != bit_length) {
            // throw std::runtime_error("Error: modulus size is invalid");
        }
        if (server_ephemeral_repr.size() * 8 != bit_length) {
            // throw std::runtime_error("Error: server ephemeral size is invalid");
        }
        if (hashed_password_repr.size() * 8 != bit_length) {
            // throw std::runtime_error("Error: hased passowrd size is invalid");
        }
        
        BIGNUM* modulus = SrpClientImpl::toBI(plain_modulus);
        BIGNUM* serverEphemeral =  SrpClientImpl::toBI(plain_ephemeral);
        BIGNUM* hashedPassword = SrpClientImpl::toBI(plain_hashedpwd);
        
        int modulus_bites = BN_num_bits(modulus);
        if (modulus_bites != bit_length) {
            throw std::runtime_error("Error: modulus size is invalid");
        }
        
        BIGNUM* generator = SrpClientImpl::valueOf(2);
        
        
        std::cout << hexlify(SrpClientImpl::fromBI(bit_length, generator)) << std::endl;
        
        std::stringstream tmp_s;
        std::string generateor_bytes = SrpClientImpl::fromBI(bit_length, generator);
        tmp_s << generateor_bytes;
        tmp_s << plain_modulus;
        std::string stream_string = tmp_s.str();
        std::string hashed_generator_modulusRepr = SrpClientImpl::expand_hash(stream_string);
        std::cout << hexlify(hashed_generator_modulusRepr) << std::endl;
        
        BIGNUM* multiplier_before_mod = SrpClientImpl::toBI(hashed_generator_modulusRepr);
        
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
        
        //shift check
        
        BIGNUM * bn_bitLength = SrpClientImpl::valueOf(bit_length * 2);
        std::cout << hexlify(SrpClientImpl::fromBI(bit_length, bn_bitLength)) << std::endl;
        
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
            
            std::string test_clientSecret ="66b9c41c94fa15c4cc5ded54e9b07282dca916ff56b4af13c0d467b35b5ff82833a65ebf5833f0cd14fea0d791a6f101d0a5c2a0edc4381f10cd94f097c176996c8e03d6a7babe43f80f7c2a153a183e8b2551328bc073db15151729975f4497a346385d793e4fb50522fb3aeebebca9b1cf21ce2eaae63c8054a0961cde6cfb3f977cb04fc1f6d709d99e4f84227a0fabb507a29bb68e9b6f85a29c7cea3705dcfe891831ff14d8ec01be3674baab1eebaf9de9d8e0b2990c8f32cf7b4675f851e974bacec937a5ebef9ab0c8cdbad2ca4fd3b9fa721cdb444a480c6ca55b25ddf95ec2d9ed90fe6a01462cd21a4879ea1c9181456f8baf27df5460f0fe503e";
            clientSecret = SrpClientImpl::toBI(unhexlify(test_clientSecret));
            
            clientEphemeral = SrpClientImpl::nnmod_exp(generator, clientSecret, modulus);
            
            std::cout << hexlify(SrpClientImpl::fromBI(bit_length, clientEphemeral)) << std::endl;
            
            std::stringstream scrambling_param_stream;
            scrambling_param_stream << SrpClientImpl::fromBI(bit_length, clientEphemeral);
            scrambling_param_stream << plain_ephemeral;
            std::string scramblingParam_bytes = scrambling_param_stream.str();
            
            scramblingParam = SrpClientImpl::toBI(SrpClientImpl::expand_hash(scramblingParam_bytes));
            
            
            std::cout << hexlify(SrpClientImpl::fromBI(bit_length, scramblingParam)) << std::endl;
            
        } while (SrpClientImpl::compareToZero(clientSecret) == 0);
        
        //all return values need free
        BIGNUM * cal_nnmod_exp = SrpClientImpl::nnmod_exp(generator, hashedPassword, modulus);
        BIGNUM * cal_mul = SrpClientImpl::multiply(cal_nnmod_exp, multiplier);
        BIGNUM * cal_mod = SrpClientImpl::nnmod(cal_mul, modulus);
        
        BIGNUM * subtracted = SrpClientImpl::subtract(serverEphemeral, cal_mod);
        if (SrpClientImpl::compareToZero(subtracted) < 0) {
            BIGNUM * tmp = SrpClientImpl::add(subtracted, modulus);
            BN_free(subtracted);
            subtracted = tmp;
        }
        
        BIGNUM* exponent = SrpClientImpl::mul_add_nnmod(scramblingParam, hashedPassword, clientSecret, modulusMinusOne);
        BIGNUM* sharedSession = SrpClientImpl::nnmod_exp(subtracted, exponent, modulus);
        
        std::string clientEphemeralRepr = SrpClientImpl::fromBI(bit_length, clientEphemeral);
        
        
        std::cout << hexlify(clientEphemeralRepr) << std::endl;
        
        
        std::stringstream client_proof_stream;
        client_proof_stream << clientEphemeralRepr;
        client_proof_stream << plain_ephemeral;
        client_proof_stream << SrpClientImpl::fromBI(bit_length, sharedSession);
        
        std::string clientProof = SrpClientImpl::expand_hash(client_proof_stream.str());
        
        std::cout << hexlify(clientProof) << std::endl;
        
        std::stringstream server_proof_stream;
        server_proof_stream << clientEphemeralRepr;
        server_proof_stream << clientProof;
        server_proof_stream << SrpClientImpl::fromBI(bit_length, sharedSession);
        
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
        BIGNUM* modulus = SrpClientImpl::toBI(modulusRepr);
        BIGNUM* generator = SrpClientImpl::valueOf(2);
        std::string hashedPasswordRepr = std::string(hashed_password_repr.begin(), hashed_password_repr.end());
        BIGNUM* hashedPassword  = SrpClientImpl::toBI(hashedPasswordRepr);
        BIGNUM* cal_mod_pow = SrpClientImpl::nnmod_exp(generator, hashedPassword, modulus);
        
        std::string str_out = SrpClientImpl::fromBI(bit_length, cal_mod_pow);
        
        BN_free(modulus);
        BN_free(generator);
        BN_free(hashedPassword);
        BN_free(cal_mod_pow);
        
        return std::vector<uint8_t>(str_out.begin(), str_out.end());
    }
    
}
