#include "RSA.h"
#include "config.h"
#include "RSA.h"

#ifdef HAVE_OPENSSL_RSA_H
#include <openssl/rsa.h>
#endif


#ifdef HAVE_OPENSSL_ERR_H
#include <openssl/err.h>
#endif

//std::vector <PGPMPI> RSA_keygen(const unsigned int & bits){
//    BBS(static_cast <PGPMPI> (static_cast <unsigned int> (now()))); // seed just in case not seeded
//
//    PGPMPI p = 3, q = 3;
//    while (p == q){
//        p = bintompi(BBS().rand(bits));
//        q = bintompi(BBS().rand(bits));
//        p = nextprime(p);
//        q = nextprime(q);
//    }
//
//    PGPMPI n = p * q;
//    PGPMPI tot = (p - 1) * (q - 1);
//    PGPMPI e = bintompi(BBS().rand(bits));
//    e += ((e & 1) == 0);
//    PGPMPI gcd = 0;
//    while (gcd != 1){
//        e += 2;
//        gcd = mpigcd(tot, e);
//    }
//    PGPMPI d;
//    d = invert(e, tot);
//    return {n, e, d}; // split this into {n, e} and {d}
//}
//
std::string RSA_encrypt(const std::string & data, const std::vector <std::string> & pub){
    
    //size_t msg_size = data.size();//Notes: Convert
    
    BIGNUM* b_e = BN_mpi2bn((unsigned char * )data.c_str(), (int)data.size(), NULL);
    uint8_t cleartext[8192];
    int lin = BN_bn2bin(b_e, cleartext);
    
    std::string t = std::string((char*)cleartext , lin);
    
    t = zero + t;
    
    size_t length = 8192;
    uint8_t out[length];
    
    lin = (int)t.size();
    
    
    RSA* orsa = RSA_new();
    
    orsa->n = BN_mpi2bn((unsigned char *)pub[0].c_str(), (int)pub[0].size(), NULL);
    orsa->e = BN_mpi2bn((unsigned char *)pub[1].c_str(), (int)pub[1].size(), NULL);
    

    int n = RSA_public_encrypt(lin, (unsigned char*)t.c_str(), out, orsa, RSA_NO_PADDING);
    
    if (n == -1) {
        BIO            *fd_out;
        
        fd_out = BIO_new_fd(fileno(stderr), BIO_NOCLOSE);
        ERR_print_errors(fd_out);
        std::cout << fd_out << std::endl;
    }
    orsa->n = orsa->e = NULL;
    RSA_free(orsa);
    
   // std::cout << out << std::endl;
    
    BIGNUM* e = BN_bin2bn(out, n, NULL);
    
    int i = BN_bn2mpi(e, out);
    
    std::string mpi_out = std::string((char*)out, i);
    //std::cout << hexlify(mpi_out) << std::endl;
    return mpi_out;
}

std::string RSA_decrypt(const std::string & data, const std::vector <std::string> & pri, const std::vector <std::string> & pub)
{
    BIGNUM * e = BN_mpi2bn((unsigned char*)data.c_str(), (int)data.size(), NULL);
    uint8_t cleartext[8192];
    BN_bn2bin(e, cleartext);
    int size =  (unsigned)(BN_num_bits(e) + 7) / 8;
   
    //std::cout << data << std::endl;
   // std::cout << pri.size() << std::endl;
    RSA * rsa = RSA_new();
    
    size_t length = 8192;
    uint8_t out[length];

    int resultDecrypt = 0;
    
    rsa->n = BN_mpi2bn((unsigned char *)pub[0].c_str(), (int)pub[0].size(), NULL);
   // rsa->e = BN_mpi2bn((unsigned char *)pub[1].c_str(), (int)pub[1].size(), NULL);
    rsa->d = BN_mpi2bn((unsigned char *)pri[0].c_str(), (int)pri[0].size(), NULL);
    rsa->p = BN_mpi2bn((unsigned char *)pri[1].c_str(), (int)pri[1].size(), NULL);
    rsa->q = BN_mpi2bn((unsigned char *)pri[2].c_str(), (int)pri[2].size(), NULL);
   
    resultDecrypt = RSA_private_decrypt(size , cleartext, out, rsa, RSA_NO_PADDING);
    if(resultDecrypt == -1)
    {
        
    }
    RSA_free ( rsa );
    
    std::string mpi_out = rawtompi(std::string((char*)out, resultDecrypt));
   
    //std::cout << mpitohex(mpi_out) << std::endl;
    
    return mpi_out;
}

std::string RSA_sign(const std::string & data, const std::vector <std::string> & pri, const std::vector <std::string> & pub)
{
    return "";
}

//PGPMPI RSA_sign(const PGPMPI & data, const std::vector <PGPMPI> & pri, const std::vector <PGPMPI> & pub){
//    return RSA_decrypt(data, pri, pub);
//}
//
//PGPMPI RSA_sign(const std::string & data, const std::vector <PGPMPI> & pri, const std::vector <PGPMPI> & pub){
//    return RSA_decrypt(rawtompi(data), pri, pub);
//}
//
//bool RSA_verify(const PGPMPI & data, const std::vector <PGPMPI> & signature, const std::vector <PGPMPI> & pub){
//    return (RSA_encrypt(signature[0], pub) == data);
//}
//
//bool RSA_verify(const std::string & data, const std::vector <PGPMPI> & signature, const std::vector <PGPMPI> & pub){
//    return RSA_verify(rawtompi(data), signature, pub);
//}
