/*
RSA.h
RSA algorithm

Copyright (c) 2013, 2014 Jason Lee

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
*/

#ifndef __RSA__
#define __RSA__

#include <algorithm>
#include <vector>
#include <iostream>

#include <utilities/consts.h>
#include <utilities/bignumber.h>
#include <utilities/includes.h>
#include <utilities/mpi.h>
#include <utilities/PKCS1.h>


//move to cpp later
#ifdef HAVE_SYS_CDEFS_H
#include <sys/cdefs.h>
#endif

#if defined(__NetBSD__)
__COPYRIGHT("@(#) Copyright (c) 2009 The NetBSD Foundation, Inc. All rights reserved.");
__RCSID("$NetBSD: openssl_crypto.c,v 1.32 2010/11/07 06:56:52 agc Exp $");
#endif

#ifdef HAVE_OPENSSL_DSA_H
#include <openssl/dsa.h>
#endif

#ifdef HAVE_OPENSSL_RSA_H
#include <openssl/rsa.h>
#endif

#ifdef HAVE_OPENSSL_ERR_H
#include <openssl/err.h>
#endif

#include <openssl/pem.h>
#include <openssl/evp.h>
#include <openssl/err.h>

#include <stdlib.h>
#include <string.h>

#ifdef HAVE_UNISTD_H
#include <unistd.h>
#endif

namespace ProtonMail {
    namespace crypto {
        class PKA_RSA {
        private:
            bool inited = false;
            
            //mpidata : mpi data with customized padding
            std::string encrypt(const std::string& mpidata, const std::vector <std::string>& pub_mpi, int padding = RSA_NO_PADDING) {
                
                BIGNUM* b_e = BN_mpi2bn((unsigned char * )mpidata.c_str(), static_cast<int>(mpidata.size()), NULL);
                uint8_t cleartext[8192];
                int lin = BN_bn2bin(b_e, cleartext);
                
                //release
                BN_free(b_e);
                
                std::string t = std::string((char*)cleartext , lin);
                t = zero + t;
                size_t length = 8192;
                uint8_t out[length];
                
                lin = static_cast<int>(t.size());
                
                RSA* orsa = RSA_new();
                orsa->n = BN_mpi2bn((unsigned char *)pub_mpi[0].c_str(), static_cast<int>(pub_mpi[0].size()), NULL);
                orsa->e = BN_mpi2bn((unsigned char *)pub_mpi[1].c_str(), static_cast<int>(pub_mpi[1].size()), NULL);
                int n = RSA_public_encrypt(lin, (unsigned char*)t.c_str(), out, orsa, padding);
                if (n == -1) {
                    BIO            *fd_out;
                    fd_out = BIO_new_fd(fileno(stderr), BIO_NOCLOSE);
                    ERR_print_errors(fd_out);
                    std::cout << fd_out << std::endl;
                }
                
                RSA_free(orsa);
                
                BIGNUM* e = BN_bin2bn(out, n, NULL);
                int i = BN_bn2mpi(e, out);
                BN_free(e);
                
                std::string mpi_out = std::string((char*)out, i);
                //std::cout << hexlify(mpi_out) << std::endl;
                return mpi_out;
                
            }
            
            
        public:
            
            
            std::vector <std::string> rsa_pub_mpi;  //n e
            std::vector <std::string> rsa_priv_mpi;  //d p q
            
            
            PKA_RSA() {
            }
            
            //mpidata : mpi data with customized padding
            std::string encrypt(const std::string& mpidata, int padding = RSA_NO_PADDING) {
                return encrypt(mpidata, rsa_pub_mpi, padding);
            }
            
            //out : mpi data with customized padding
            std::string decrypt(const std::string& encrypted, int padding = RSA_NO_PADDING) {
                BIGNUM * e = BN_mpi2bn((unsigned char*)encrypted.c_str(), static_cast<int>(encrypted.size()), NULL);
                uint8_t cleartext[8192];
                BN_bn2bin(e, cleartext);
                int size =  (unsigned)(BN_num_bits(e) + 7) / 8;
                BN_free(e);
                
                RSA * rsa = RSA_new();
                size_t length = 8192;
                uint8_t out[length];
                int resultDecrypt = 0;
                rsa->n = BN_mpi2bn((unsigned char *)rsa_pub_mpi[0].c_str(), static_cast<int>(rsa_pub_mpi[0].size()), NULL);
                //rsa->e = BN_mpi2bn((unsigned char *)pub[1].c_str(), static_cast<int>(pub[1].size()), NULL);
                rsa->d = BN_mpi2bn((unsigned char *)rsa_priv_mpi[0].c_str(), static_cast<int>(rsa_priv_mpi[0].size()), NULL);
                rsa->p = BN_mpi2bn((unsigned char *)rsa_priv_mpi[1].c_str(), static_cast<int>(rsa_priv_mpi[1].size()), NULL);
                rsa->q = BN_mpi2bn((unsigned char *)rsa_priv_mpi[2].c_str(), static_cast<int>(rsa_priv_mpi[2].size()), NULL);
                
                resultDecrypt = RSA_private_decrypt(size , cleartext, out, rsa, padding);
                if(resultDecrypt == -1)
                {
                    
                }
                RSA_free ( rsa );
                //std::cout << hexlify(std::string(std::string((char*)out, resultDecrypt))) << std::endl;
                std::string mpi_out = rawtompi(std::string((char*)out, resultDecrypt));
                return mpi_out;
            }
            
            std::string sign(const std::string& mpidata, int padding = RSA_NO_PADDING) {
                
                BIGNUM* b_e = BN_mpi2bn((unsigned char * )mpidata.c_str(), static_cast<int>(mpidata.size()), NULL);
                uint8_t cleartext[8192];
                int lin = BN_bn2bin(b_e, cleartext);
                
                //release
                BN_free(b_e);
                
                std::string t = std::string((char*)cleartext , lin);
                t = zero + t;
                size_t length = 8192;
                uint8_t out[length];
                
                lin = static_cast<int>(t.size());

                RSA            *orsa;
                int             n;
                
                orsa = RSA_new();
                orsa->n = BN_mpi2bn((unsigned char *)rsa_pub_mpi[0].c_str(), static_cast<int>(rsa_pub_mpi[0].size()), NULL);
                /* debug */
                /* If this isn't set, it's very likely that the programmer hasn't */
                /* decrypted the secret key. RSA_check_key segfaults in that case. */
                /* Use __ops_decrypt_seckey() to do that. */
                orsa->e = BN_mpi2bn((unsigned char *)rsa_pub_mpi[1].c_str(), static_cast<int>(rsa_pub_mpi[1].size()), NULL);
                
                orsa->d = BN_mpi2bn((unsigned char *)rsa_priv_mpi[0].c_str(), static_cast<int>(rsa_priv_mpi[0].size()), NULL);
                orsa->p = BN_mpi2bn((unsigned char *)rsa_priv_mpi[1].c_str(), static_cast<int>(rsa_priv_mpi[1].size()), NULL);
                orsa->q = BN_mpi2bn((unsigned char *)rsa_priv_mpi[2].c_str(), static_cast<int>(rsa_priv_mpi[2].size()), NULL);
                
                if (orsa->d == NULL) {
                    (void) fprintf(stderr, "orsa is not set\n");
                    return 0;
                }
                if (RSA_check_key(orsa) != 1) {
                    (void) fprintf(stderr, "RSA_check_key is not set\n");
                    return 0;
                }
//                /* end debug */
//                int keysize = (BN_num_bits(orsa->n) + 7) / 8;
////                //SHA256(data, dataLen, hash);
////                std::string encoded = EMSA_PKCS1_v1_5(8, mpidata, keysize);
////                encoded = zero + encoded;

                n = RSA_private_encrypt(lin, (unsigned char*)t.c_str(), out, orsa, padding);
                
                std::string mpi_out = rawtompi(std::string((char*)out, n));
                
                RSA_free(orsa);
                
                return mpi_out;
            }
            
            bool verify(std::string mpidata, std::string signature, int padding = RSA_NO_PADDING) {
                
                
                BIGNUM* b_e = BN_mpi2bn((unsigned char * )signature.c_str(), static_cast<int>(signature.size()), NULL);
                uint8_t cleartext[8192];
                int lin = BN_bn2bin(b_e, cleartext);
                
                //release
                BN_free(b_e);
                
                std::string t = std::string((char*)cleartext , lin);
                size_t length = 8192;
                uint8_t out[length];
                
                lin = static_cast<int>(t.size());
                
                RSA* orsa = RSA_new();
                orsa->n = BN_mpi2bn((unsigned char *)rsa_pub_mpi[0].c_str(), static_cast<int>(rsa_pub_mpi[0].size()), NULL);
                orsa->e = BN_mpi2bn((unsigned char *)rsa_pub_mpi[1].c_str(), static_cast<int>(rsa_pub_mpi[1].size()), NULL);
                int n = RSA_public_decrypt(lin, (unsigned char*)t.c_str(), out, orsa, padding);
                if (n == -1) {
                    BIO            *fd_out;
                    fd_out = BIO_new_fd(fileno(stderr), BIO_NOCLOSE);
                    ERR_print_errors(fd_out);
                    std::cout << fd_out << std::endl;
                }
                
                RSA_free(orsa);
                
                BIGNUM* e = BN_bin2bn(out, n, NULL);
                int i = BN_bn2mpi(e, out);
                BN_free(e);
                
                std::string mpi_out = std::string((char*)out, i);
                //std::cout << hexlify(mpi_out) << std::endl;
                return mpi_out == mpidata;

                
                
               // return (encrypt(signature, rsa_pub_mpi, RSA_PKCS1_PADDING) == mpidata);
            }
            
            void generate(int bits) {
                if (inited) return ;
                BN_CTX *ctx= BN_CTX_new();
                BIGNUM* e = BN_new();
                
                RSA *rsa_key = RSA_new();
                
                int iRet = BN_set_word(e, 65537);
                if(!iRet)
                {
                    std::cout<<"BN_set_word error "<< std::endl;
                }
                
                iRet = RSA_generate_key_ex(rsa_key, bits, e, NULL);
                if(!iRet)
                {
                    std::cout<<"RSA_generate_key_ex key error "<< std::endl;
                }
                
                size_t length = 8192;
                uint8_t out[length];
                
                int ln = 0;
                
                //private key part
                ln = BN_bn2mpi(rsa_key->d, out);
                rsa_priv_mpi.push_back(std::string((char*)out, ln));
                ln = BN_bn2mpi(rsa_key->p, out);
                rsa_priv_mpi.push_back(std::string((char*)out, ln));
                ln = BN_bn2mpi(rsa_key->q, out);
                rsa_priv_mpi.push_back(std::string((char*)out, ln));
                
                BIGNUM * rsa_inverse = BN_mod_inverse(NULL, rsa_key->p, rsa_key->q, ctx);
                ln = BN_bn2mpi(rsa_inverse, out);
                BN_free(rsa_inverse);
                
                rsa_priv_mpi.push_back(std::string((char*)out, ln));
                //pub key part
                ln = BN_bn2mpi(rsa_key->n, out);
                rsa_pub_mpi.push_back(std::string((char*)out, ln));
                ln = BN_bn2mpi(rsa_key->e, out);
                rsa_pub_mpi.push_back(std::string((char*)out, ln));
                
                BN_CTX_free(ctx);
                BN_free(e);
                //rsa_key->n = rsa_key->e = rsa_key->d = rsa_key->p = rsa_key->q = NULL;
                RSA_free(rsa_key);
                
                inited = true;
            }
        };
    }
}




//// Generate RSA key values
//std::vector <PGPMPI> RSA_keygen(const uint32_t & bits = 2048);
//
//// Encrypt some data
std::string RSA_encrypt(const std::string & data, const std::vector <std::string> & pub);
//
// Decrypt some data
std::string RSA_decrypt(const std::string & data, const std::vector <std::string> & pri, const std::vector <std::string> & pub);
//
//// Sign some data
//PGPMPI RSA_sign(const PGPMPI & data, const std::vector <PGPMPI> & pri, const std::vector <PGPMPI> & pub);
std::string RSA_sign(const std::string & data, const std::vector <std::string> & pri, const std::vector <std::string> & pub);


//// Verify signature
//bool RSA_verify(const PGPMPI & data, const std::vector <PGPMPI> & signature, const std::vector <PGPMPI> & pub);
bool RSA_verify(const std::string & data, const std::vector <std::string> & signature, const std::vector <std::string> & pub);
#endif
