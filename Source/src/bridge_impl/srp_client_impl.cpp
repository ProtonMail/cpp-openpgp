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
           // throw std::runtime_error("Error: modulus size is invalid");
        }
        if (server_ephemeral_repr_bytes.size() * 8 != bit_length) {
           // throw std::runtime_error("Error: server ephemeral size is invalid");
        }
        if (hashed_password_repr_bytes.size() * 8 != bit_length) {
            //throw std::runtime_error("Error: hased passowrd size is invalid");
        }
        
        auto modulus_repr = std::string(modulus_repr_bytes.begin(), modulus_repr_bytes.end());
        auto server_ephemeral_repr = std::string(server_ephemeral_repr_bytes.begin(), server_ephemeral_repr_bytes.end());
        auto hashed_password_repr = std::string(hashed_password_repr_bytes.begin(), hashed_password_repr_bytes.end());
        
        
//        std::string modulus_repr ="4bf8418265571e5a735318333a5b78bde137bf7067a5a5724455140cc99181c176c99539ad07106070c11ab9d002519d72c1a66557190b9d49809b4407abf96c1a719e7b2383c5e26d99b41985ce0e19bbaa48b9c0ce4010aa1329b64a68ab910f6f7ba4f4ec55da9475714d7640f19374379efdcde9910971c092d4869b96537efda7554e351f08c03da7225abce3a3f747e17024369e9227b317a0be51af444af5269a1b76bb5b5c03b32c7fbd10bc695bdd591566cdd071da13cf8957c4ec667858f96d29a8bfb1d7c8950703822a3aa2355957b09b1de0f5747f25f715bfee4539d4b8461effdf31a3eaaa1bf0ab8485bb4208aec1e98437b3dd1c70119d";
//        modulus_repr = unhexlify(modulus_repr);
//        
//        std::string server_ephemeral_repr ="5a025a1e8814b994c26b8bcf90b3156f1e8f5e690597e63667d60b58169000e5cfc43ce56a331ba944f46105909ba54192e6cc059fc3747ed8428277b2bec01564484f401d677aac92a3807f742baf16b84e9dc76769f6cb62461b6835b2d851d8ffbf4dd2ac96484f44839181614d0b921683c6c335d20abf45493bd17b071db381148cb4cf333c8425063630660b988eecf8c754e4ba2670500918ba339d27d624ba8de06f2923d16cb7deffdc32ba5d655dd4509afc0f8477463c7e418303f096dd2bde52634f39d2ed801b10954746849e3f5b900832a47b930bd342f1d1e0bb9e03e8ed4feba6fb527e7abd910ef4fd47695b7457d9be52cd137afb7d23";
//        server_ephemeral_repr = unhexlify(server_ephemeral_repr);
//        
//        std::string hashed_password_repr ="bc173fac3bcda272e2de5a0b9f4c2cc091158c57494868fe8e68be2d3ec3aca4e1c7808d7cd2a44f9708428151bcdb6aeadf69189cf90d39fca76a780549c53fc1bed6fabb63c80eaaadf5fabac5b301e6d7648d7cfc2aa9c707865f2654bdb352ae922e0b9d98ff671b82124c079a4f4555c94d58c8c040241deeb78c615337aefb9ffaa0cc4ace1df84d012196fee71f666b05998edc63b03c2cbfe0d170dc493e6169bc3d9876d87ddd392d9ac0994fa5090e141dd1451511592b4846094963dcddf68a4bca38d6998677e8310334ea11651b2393262d4b81837da86b4f329a3576d09e8868d29ce735793285219817ef4aa7373c9f862c51fee76054e0a6";
//        hashed_password_repr = unhexlify(hashed_password_repr);
        
        
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

            } while (BN_cmp(clientSecret, modulusMinusOne) >= 0 || BN_cmp(clientSecret, bn_bitLength) <= 0);
            std::cout << hexlify(BN::fromBI(bit_length, clientSecret)) << std::endl;
            
//            std::string test_clientSecret ="d6bb266755fac6867a2acd866b67d64b1e266f4d72ea6610e41141ed23812a788d295af27f2876451817819d7e84194b5df9ebe762960f418af43b7fb3c091c9edb416a92e4c20b01bf92152ada901187a05533f71cd1bbc680f529e303c8ac2a2848aa02407636f2254a7cb97b9a73915368e5281a1753ccadd8a0adbc14b30d1cffa51c580103249fe4cf5a2ee1c827f83e402bcbd4bacaca92a23e1b099859f0c9e8f38bacf41bfc38d01c06ceccfd11e9b9d9bb48c5c18c157ddff591069232bf47b7b9d8e515e2ce3a49015c803b7e119fd9b80734ff56a4039706545af7204032302c789d17fbb4ef9a87ddae2badd3a2e7bfcdd8197d71c28878db31a";
//            clientSecret = BN::toBI(unhexlify(test_clientSecret));
            clientEphemeral = BN::nnmod_exp(generator, clientSecret, modulus);

            std::cout << hexlify(BN::fromBI(bit_length, clientEphemeral)) << std::endl;
            
            std::stringstream scrambling_param_stream;
            scrambling_param_stream << BN::fromBI(bit_length, clientEphemeral);
            scrambling_param_stream << server_ephemeral_repr;
            std::string scramblingParam_bytes = scrambling_param_stream.str();
            
            scramblingParam = BN::toBI(SrpClientImpl::expand_hash(scramblingParam_bytes));
            std::cout << hexlify(BN::fromBI(bit_length, scramblingParam)) << std::endl;
            
    
//            scramblingParam = toBI(PasswordUtils.expandHash(ArrayUtils.addAll(fromBI(bitLength, clientEphemeral), serverEphemeralRepr)));
//            
//            final byte[] scramblingParam_bytes = fromBI(bitLength, scramblingParam);
//            Log.e("generateProofs", "scramblingParam_bytes: " + byteArrayToHex( scramblingParam_bytes ) );
            
            
            
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
        client_proof_stream << server_ephemeral_repr;
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
