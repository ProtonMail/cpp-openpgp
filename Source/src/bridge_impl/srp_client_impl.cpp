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
        std::string tmp_ephemeral = "404b33bc47271a1ace0ffe93a94824e5fd6a754f01f1e111459042bd9b94fac994bec6c5eddabdb79bf58717dcc4c381754ac64f63df78348edcb154bde6eacb12859d375610fbf7ce3316b61ff07e6c8edfa281633b5698dd25a621401a4d9c1704eb8e6235d7baa735884e753941b6eeef0e1666aaf0a590d3668dd3b172db63bb540a3190fb665ab1b4f77ce0dc0d09ce131a7ebf8a81736c2d97e046c0b299e95da3c5321602c7f86cde1bd0a217e00f2dc883c6d6041c8975d702a0724947fc7b75b54ddbb3520c1565c4af9d18b850f5c348884dfda4f82afbda5cd98a2dac350aca63875e37e38307aeae2bd8513393b46a46481e84cac2ca5930ec35";
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
        
        unsigned char g = 2;
        BIGNUM* generator = BN_bin2bn(&g, 1, NULL);
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
        
        
        BIGNUM * clientSecret = BN_new();


        BN_rand(clientSecret,bit_length,0,0);
        int length = BN_num_bits(clientSecret);
        char *show = BN_bn2dec(clientSecret);
        printf("length:%d,rnd:%s\n",length,show);
        
//        if (!modulus.isProbablePrime(10) || !modulus.shiftRight(1).isProbablePrime(10)) {
//            throw std::runtime_error("multiplier compare value invalid");
//        }
        
//        std::string test = SrpClientImpl::fromBI(bit_length, modulus);
//        std::cout << hexlify(test) << std::endl;
//        
//        std::string test1 = SrpClientImpl::fromBI(bit_length, modulusMinusOne);
//        std::cout << hexlify(test1) << std::endl;
//        

        //BN_cmp(<#const BIGNUM *a#>, <#const BIGNUM *b#>)
   
        //        if (multiplier.compareTo(BigInteger.ONE) <= 0 || multiplier.compareTo(modulusMinusOne) >= 0) {
        //            return null;
        //        }
        //
        //        if (serverEphemeral.compareTo(BigInteger.ONE) <= 0 || serverEphemeral.compareTo(modulusMinusOne) >= 0) {
        //            return null;
        //        }
        //
        //        if (!modulus.isProbablePrime(10) || !modulus.shiftRight(1).isProbablePrime(10)) {
        //            return null;
        //        }
        //
        //        final SecureRandom random = new SecureRandom();
        //        BigInteger clientSecret;
        //        BigInteger clientEphemeral;
        //        BigInteger scramblingParam;
        //        do {
        //            do {
        //                clientSecret = new BigInteger(bitLength, random);
        //            }
        //            while (clientSecret.compareTo(modulusMinusOne) >= 0 || clientSecret.compareTo(BigInteger.valueOf(bitLength * 2)) <= 0);
        //            clientEphemeral = generator.modPow(clientSecret, modulus);
        //            scramblingParam = toBI(PasswordUtils.expandHash(ArrayUtils.addAll(fromBI(bitLength, clientEphemeral), serverEphemeralRepr)));
        //        } while (scramblingParam.equals(BigInteger.ZERO)); // Very unlikely
        //
        //        BigInteger subtracted = serverEphemeral.subtract(generator.modPow(hashedPassword, modulus).multiply(multiplier).mod(modulus));
        //        if (subtracted.compareTo(BigInteger.ZERO) < 0) {
        //            subtracted = subtracted.add(modulus);
        //        }
        //        final BigInteger exponent = scramblingParam.multiply(hashedPassword).add(clientSecret).mod(modulusMinusOne);
        //        final BigInteger sharedSession = subtracted.modPow(exponent, modulus);
        //
        //        final byte[] clientEphemeralRepr = fromBI(bitLength, clientEphemeral);
        //        final byte[] clientProof = PasswordUtils.expandHash(ArrayUtils.addAll(ArrayUtils.addAll(clientEphemeralRepr, serverEphemeralRepr), fromBI(bitLength, sharedSession)));
        //        final byte[] serverProof = PasswordUtils.expandHash(ArrayUtils.addAll(ArrayUtils.addAll(clientEphemeralRepr, clientProof), fromBI(bitLength, sharedSession)));
        //
        //        return new Proofs(clientEphemeralRepr, clientProof, serverProof);
        
        std::vector<uint8_t> a;
        ProtonMail::SrpProofs s(a,a,a);
        return s;
    }
    
    std::vector<uint8_t> SrpClient::generate_Verifier(int32_t bit_length, const std::vector<uint8_t> & modulus_repr, const std::vector<uint8_t> & hashed_password_repr)
    {
        return std::vector<uint8_t>();
    }
    
    

}

//public class SRPClient {
//    private static BigInteger toBI(final byte[] repr) {
//        final byte[] reversed = Arrays.copyOf(repr, repr.length);
//        ArrayUtils.reverse(reversed);
//        return new BigInteger(1, reversed);
//    }
//
//    private static byte[] fromBI(final int bitLength, final BigInteger bi) {
//        final byte[] twosComp = bi.toByteArray();
//        ArrayUtils.reverse(twosComp);
//        final byte[] output = new byte[bitLength / 8];
//        System.arraycopy(twosComp, 0, output, 0, Math.min(twosComp.length, output.length));
//        return output;
//    }
//
//    public static Proofs generateProofs(final int bitLength, final byte[] modulusRepr, final byte[] serverEphemeralRepr, final byte[] hashedPasswordRepr) throws NoSuchAlgorithmException {
//        if (modulusRepr.length * 8 != bitLength || serverEphemeralRepr.length * 8 != bitLength || hashedPasswordRepr.length * 8 != bitLength) {
//            // FIXME: better error message?
//            return null;
//        }
//
//        final BigInteger modulus = toBI(modulusRepr);
//        final BigInteger serverEphemeral = toBI(serverEphemeralRepr);
//        final BigInteger hashedPassword = toBI(hashedPasswordRepr);
//
//        if (modulus.bitLength() != bitLength) {
//            return null;
//        }
//
//        final BigInteger generator = BigInteger.valueOf(2);
//
//        final BigInteger multiplier = toBI(PasswordUtils.expandHash(ArrayUtils.addAll(fromBI(bitLength, generator), modulusRepr))).mod(modulus);
//        final BigInteger modulusMinusOne = modulus.clearBit(0);
//
//        if (multiplier.compareTo(BigInteger.ONE) <= 0 || multiplier.compareTo(modulusMinusOne) >= 0) {
//            return null;
//        }
//
//        if (serverEphemeral.compareTo(BigInteger.ONE) <= 0 || serverEphemeral.compareTo(modulusMinusOne) >= 0) {
//            return null;
//        }
//
//        if (!modulus.isProbablePrime(10) || !modulus.shiftRight(1).isProbablePrime(10)) {
//            return null;
//        }
//
//        final SecureRandom random = new SecureRandom();
//        BigInteger clientSecret;
//        BigInteger clientEphemeral;
//        BigInteger scramblingParam;
//        do {
//            do {
//                clientSecret = new BigInteger(bitLength, random);
//            }
//            while (clientSecret.compareTo(modulusMinusOne) >= 0 || clientSecret.compareTo(BigInteger.valueOf(bitLength * 2)) <= 0);
//            clientEphemeral = generator.modPow(clientSecret, modulus);
//            scramblingParam = toBI(PasswordUtils.expandHash(ArrayUtils.addAll(fromBI(bitLength, clientEphemeral), serverEphemeralRepr)));
//        } while (scramblingParam.equals(BigInteger.ZERO)); // Very unlikely
//
//        BigInteger subtracted = serverEphemeral.subtract(generator.modPow(hashedPassword, modulus).multiply(multiplier).mod(modulus));
//        if (subtracted.compareTo(BigInteger.ZERO) < 0) {
//            subtracted = subtracted.add(modulus);
//        }
//        final BigInteger exponent = scramblingParam.multiply(hashedPassword).add(clientSecret).mod(modulusMinusOne);
//        final BigInteger sharedSession = subtracted.modPow(exponent, modulus);
//
//        final byte[] clientEphemeralRepr = fromBI(bitLength, clientEphemeral);
//        final byte[] clientProof = PasswordUtils.expandHash(ArrayUtils.addAll(ArrayUtils.addAll(clientEphemeralRepr, serverEphemeralRepr), fromBI(bitLength, sharedSession)));
//        final byte[] serverProof = PasswordUtils.expandHash(ArrayUtils.addAll(ArrayUtils.addAll(clientEphemeralRepr, clientProof), fromBI(bitLength, sharedSession)));
//
//        return new Proofs(clientEphemeralRepr, clientProof, serverProof);
//    }
//
//    public static byte[] generateVerifier(final int bitLength, final byte[] modulusRepr, final byte[] hashedPasswordRepr) {
//        final BigInteger modulus = toBI(modulusRepr);
//        final BigInteger generator = BigInteger.valueOf(2);
//        final BigInteger hashedPassword = toBI(hashedPasswordRepr);
//
//        return fromBI(bitLength, generator.modPow(hashedPassword, modulus));
//    }
//
//    public static class Proofs {
//        public final byte[] clientEphemeral;
//        public final byte[] clientProof;
//        public final byte[] expectedServerProof;
//
//        public Proofs(final byte[] clientEphemeral, final byte[] clientProof, final byte[] expectedServerProof) {
//            this.clientEphemeral = clientEphemeral;
//            this.clientProof = clientProof;
//            this.expectedServerProof = expectedServerProof;
//        }
//    }
//}
