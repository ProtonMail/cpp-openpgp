#include "mpi.h"

#include "BBS.h"
#include "includes.h"
#include "config.h"
#ifdef HAVE_OPENSSL_RSA_H
#include <openssl/rsa.h>
#endif


#include <sstream>
#include <string>

std::string hextompi(const std::string & hex){

    BIGNUM* e = BN_new();
    int iRet, ln;
    
    iRet= BN_hex2bn(&e, hex.c_str());
    ln = BN_bn2mpi(e, NULL);
    char bn[ln];
    iRet = BN_bn2mpi(e, (unsigned char*)bn);
    
    BN_free(e);
    
    return std::string(bn, ln);
}

//PGPMPI dectompi(const std::string & dec){
//    return PGPMPI(dec, 10);
//}
//
//std::string bintompi(const std::string & bin){
//    return "";//PGPMPI(bin, 2);
////BN_bn2bin(, )
//}
//
std::string rawtompi(const std::string & raw){
    return hextompi(hexlify(raw));
}
//
std::string mpitohex(const std::string & a){
    
    BIGNUM* e = BN_new();
    int ln = (int)a.size();
    
    BN_mpi2bn((unsigned char *)a.c_str(), ln, e);
    
    std::string hex = BN_bn2hex(e);
  //  std::cout << hex << std::endl;
    BN_free(e);
    
    return hex;
}


//std::string mpitodec(const PGPMPI & a){
//    return a.get_str(10);
//}
//
//std::string mpitobin(const std::string & a){
//    return a.get_str(2);
//}
//
std::string mpitoraw(const std::string & a){
    return unhexlify(mpitohex(a));
}
//
//unsigned long mpitoulong(const PGPMPI & a){
//    return a.get_ui();
//}
//
unsigned int bitsize(const std::string &a){
    BIGNUM* e = BN_new();
    int ln = (int)a.size();
    BN_mpi2bn((unsigned char *)a.c_str(), ln, e);
    int n = BN_num_bits(e);
    BN_free(e);
    return  n;
}

//
//bool knuth_prime_test(const PGPMPI & a, int test){
//    return mpz_probab_prime_p(a.get_mpz_t(), test);
//}
//
//PGPMPI mpigcd(const PGPMPI &a, const PGPMPI &b){
//    PGPMPI ret;
//    mpz_gcd(ret.get_mpz_t(), a.get_mpz_t(), b.get_mpz_t());
//    return ret;
//}
//PGPMPI nextprime(const PGPMPI &a){
//    PGPMPI ret;
//    mpz_nextprime(ret.get_mpz_t(), a.get_mpz_t());
//    return ret;
//}
//PGPMPI powm(const PGPMPI &base, const PGPMPI &exp, const PGPMPI &mod){
//    PGPMPI ret;
//    mpz_powm_sec(ret.get_mpz_t(), base.get_mpz_t(), exp.get_mpz_t(), mod.get_mpz_t());
//    return ret;
//}
//PGPMPI invert(const PGPMPI &a, const PGPMPI &b){
//    PGPMPI ret;
//    mpz_invert(ret.get_mpz_t(), a.get_mpz_t(), b.get_mpz_t());
//    return ret;
//}
//
//PGPMPI random(unsigned int bits){
//    try{
//        return bintompi(BBS().rand(bits));
//    } catch (...) {
//        BBS(static_cast <PGPMPI> (static_cast <unsigned int> (now()))); // seed just in case not seeded
//        return bintompi(BBS().rand(bits));
//    }
//}
//
//// given some value, return the formatted mpi
std::string write_MPI(const std::string & data){
    std::cout << hexlify(data) << std::endl;
    std::string out = mpitoraw(data);
    
    std::cout << hexlify(out) << std::endl;
    //int i = out.size();
   // std::string t = makehex(bitsize(data), 4);
//    std::cout << t << std::endl;
   // std::string p  = unhexlify(t);
 //   std::cout << p << std::endl;
    return unhexlify(makehex(bitsize(data), 4)) + out;
}

//// remove mpi from data, returning mpi value. the rest of the data will be returned through pass-by-reference
std::string read_MPI(std::string & data){
    uint16_t size = (static_cast <uint8_t> (data[0]) << 8) + static_cast <uint8_t> (data[1]); // get bits
    while (size & 7){
        size++;                                                                     // pad to nearest octet
    }
    size >>= 3;                                                                     // get number of octets
    std::string out = rawtompi(data.substr(2, size));                                    // turn to mpz_class
    std::cout << hexlify(out) << std::endl;
    data = data.substr(2 + size, data.size() - 2 - size);                           // remove mpi from data
    return out;
}
