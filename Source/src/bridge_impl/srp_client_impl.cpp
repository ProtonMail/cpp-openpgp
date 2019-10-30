//
//  srp_client_impl.cpp
//  OpenPGP_OSX_Lib
//
//  Created by Yanfeng Zhang on 10/6/16.
//
//  The MIT License
// 
//  Copyright (c) 2019 Proton Technologies AG
// 
//  Permission is hereby granted, free of charge, to any person obtaining a copy
//  of this software and associated documentation files (the "Software"), to deal
//  in the Software without restriction, including without limitation the rights
//  to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
//  copies of the Software, and to permit persons to whom the Software is
//  furnished to do so, subject to the following conditions:
// 
//  The above copyright notice and this permission notice shall be included in
//  all copies or substantial portions of the Software.
// 
//  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
//  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
//  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
//  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
//  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
//  OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
//  THE SOFTWARE.


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
        }//
        if (hashed_password_repr_bytes.size() * 8 != bit_length) {
            throw std::runtime_error("Error: hased passowrd size is invalid");
        }
        
        //                std::string tmp_modulus = "4bf8418265571e5a735318333a5b78bde137bf7067a5a5724455140cc99181c176c99539ad07106070c11ab9d002519d72c1a66557190b9d49809b4407abf96c1a719e7b2383c5e26d99b41985ce0e19bbaa48b9c0ce4010aa1329b64a68ab910f6f7ba4f4ec55da9475714d7640f19374379efdcde9910971c092d4869b96537efda7554e351f08c03da7225abce3a3f747e17024369e9227b317a0be51af444af5269a1b76bb5b5c03b32c7fbd10bc695bdd591566cdd071da13cf8957c4ec667858f96d29a8bfb1d7c8950703822a3aa2355957b09b1de0f5747f25f715bfee4539d4b8461effdf31a3eaaa1bf0ab8485bb4208aec1e98437b3dd1c70119d";
        //                std::string tmp_ephemeral = "e8712193bf16bdeaa6a700250f81c71b4fa4edf3b5a8fed96c052927db1df9e5ee895318c23158bb89f494b545583ce4f170693680c9626f39f7710915c09581ea7af9da9b53e46d1ef6055c9527df6cea8352330d6a509c0ef457bdea8102296f1381cf3aab799645a0c1377a33d63e4937af09edc7973be2810506fef85a4397661820788be0cfd0208c6114cae5002652b03e1a1aff3af1f6d8ba77ba9cd1bd5ff630c662c1ee9cb8b03fb74774183bf97107fc0474935e488c707cd44297a0744168509707cd83d1d4c3bd289ef8121275a743a12b67872e8c1646720085c6389c95575eb08f8499283d79b6ce403ef656b58ef760e6c102beed298d773d";
        //                std::string tmp_hashedpwd = "bc173fac3bcda272e2de5a0b9f4c2cc091158c57494868fe8e68be2d3ec3aca4e1c7808d7cd2a44f9708428151bcdb6aeadf69189cf90d39fca76a780549c53fc1bed6fabb63c80eaaadf5fabac5b301e6d7648d7cfc2aa9c707865f2654bdb352ae922e0b9d98ff671b82124c079a4f4555c94d58c8c040241deeb78c615337aefb9ffaa0cc4ace1df84d012196fee71f666b05998edc63b03c2cbfe0d170dc493e6169bc3d9876d87ddd392d9ac0994fa5090e141dd1451511592b4846094963dcddf68a4bca38d6998677e8310334ea11651b2393262d4b81837da86b4f329a3576d09e8868d29ce735793285219817ef4aa7373c9f862c51fee76054e0a6";
        
        
        auto modulus_repr = std::string(modulus_repr_bytes.begin(), modulus_repr_bytes.end());
        auto server_ephemeral_repr = std::string(server_ephemeral_repr_bytes.begin(), server_ephemeral_repr_bytes.end());
        auto hashed_password_repr = std::string(hashed_password_repr_bytes.begin(), hashed_password_repr_bytes.end());
        
        Biginteger modulus = BN::toBI(modulus_repr);
        Biginteger serverEphemeral = BN::toBI(server_ephemeral_repr);
        Biginteger hashedPassword = BN::toBI(hashed_password_repr);
        
        int modulus_bites = BN::num_bits(modulus);
        if (modulus_bites != bit_length) {
            throw std::runtime_error("Error: modulus size is invalid");
        }
        
        Biginteger generator = BN::valueOf(2);
        
        std::stringstream ss_modulus_repr;
        std::string generateor_bytes = BN::fromBI(bit_length, generator);
        ss_modulus_repr << generateor_bytes;
        ss_modulus_repr << modulus_repr;
        std::string hashed_generator_modulusRepr = SrpClientImpl::expand_hash(ss_modulus_repr.str());
        
        Biginteger multiplier_before_mod = BN::toBI(hashed_generator_modulusRepr);
        Biginteger multiplier = BN::nnmod(multiplier_before_mod, modulus);
        Biginteger modulusMinusOne = BN::dup(modulus);
        BN_clear_bit(modulusMinusOne.get(), 0);
        
        const Biginteger bn_one = BN::one();
        if (BN_cmp(multiplier.get(), bn_one.get()) <= 0 || BN_cmp(multiplier.get(), modulusMinusOne.get()) >= 0) {
            throw std::runtime_error("multiplier compare value invalid");
        }
        
        if (BN_cmp(serverEphemeral.get(), bn_one.get()) <= 0 || BN_cmp(serverEphemeral.get(), modulusMinusOne.get()) >= 0) {
            throw std::runtime_error("serverEphemeral compare value invalid");
        }
        
        Biginteger bn_shifted = BN::rshift(modulus, 1);
        if (!BN_is_prime(modulus.get(), 10, NULL, NULL, NULL) || !BN_is_prime(bn_shifted.get(), 10, NULL, NULL, NULL)) {
            throw std::runtime_error("BN_is_prime check failed");
        }
        
        Biginteger bn_bitLength = BN::valueOf(bit_length * 2);
        Biginteger clientSecret;
        Biginteger clientEphemeral;
        Biginteger scramblingParam;
        
        do {
            clientSecret = BN::rand_and_comp(bit_length, modulusMinusOne, bn_bitLength);
            clientEphemeral = BN::nnmod_exp(generator, clientSecret, modulus);
            std::stringstream ss_scrambling_param_stream;
            ss_scrambling_param_stream << BN::fromBI(bit_length, clientEphemeral);
            ss_scrambling_param_stream << server_ephemeral_repr;
            std::string scramblingParam_bytes = ss_scrambling_param_stream.str();
            scramblingParam = BN::toBI(SrpClientImpl::expand_hash(scramblingParam_bytes));
        } while (BN::compareToZero(clientSecret) == 0);
        
        //all return values need free
        Biginteger cal_nnmod_exp = BN::nnmod_exp(generator, hashedPassword, modulus);
        Biginteger cal_mul = BN::multiply(cal_nnmod_exp, multiplier);
        Biginteger cal_mod = BN::nnmod(cal_mul, modulus);
        
        Biginteger subtracted = BN::subtract(serverEphemeral, cal_mod);
        if (BN::compareToZero(subtracted) < 0) {
            subtracted = BN::add(subtracted, modulus);
        }
        
        Biginteger exponent = BN::mul_add_nnmod(scramblingParam, hashedPassword, clientSecret, modulusMinusOne);
        Biginteger sharedSession = BN::nnmod_exp(subtracted, exponent, modulus);
        
        std::string clientEphemeralRepr = BN::fromBI(bit_length, clientEphemeral);
        
        std::stringstream client_proof_stream;
        client_proof_stream << clientEphemeralRepr;
        client_proof_stream << server_ephemeral_repr;
        client_proof_stream << BN::fromBI(bit_length, sharedSession);
        std::string clientProof = SrpClientImpl::expand_hash(client_proof_stream.str());
        
        std::stringstream server_proof_stream;
        server_proof_stream << clientEphemeralRepr;
        server_proof_stream << clientProof;
        server_proof_stream << BN::fromBI(bit_length, sharedSession);
        
        std::string serverProof = SrpClientImpl::expand_hash(server_proof_stream.str());
        
        ProtonMail::SrpProofs s(std::vector<uint8_t>(clientEphemeralRepr.begin(), clientEphemeralRepr.end()),
                                std::vector<uint8_t>(clientProof.begin(), clientProof.end()),
                                std::vector<uint8_t>(serverProof.begin(), serverProof.end()));
        return s;
    }
    
    std::vector<uint8_t> SrpClient::generate_Verifier(int32_t bit_length, const std::vector<uint8_t> & modulus_repr, const std::vector<uint8_t> & hashed_password_repr)
    {
        std::string modulusRepr = std::string(modulus_repr.begin(), modulus_repr.end());
        auto modulus = BN::toBI(modulusRepr);
        auto generator = BN::valueOf(2);
        std::string hashedPasswordRepr = std::string(hashed_password_repr.begin(), hashed_password_repr.end());
        auto hashedPassword  = BN::toBI(hashedPasswordRepr);
        auto cal_mod_pow = BN::nnmod_exp(generator, hashedPassword, modulus);
        
        std::string str_out = BN::fromBI(bit_length, cal_mod_pow);
        
        return std::vector<uint8_t>(str_out.begin(), str_out.end());
    }
    
}
