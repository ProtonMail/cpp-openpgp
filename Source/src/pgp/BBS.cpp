#include "BBS.h"
#include "config.h"
#ifdef HAVE_OPENSSL_RSA_H
#include <openssl/rand.h>
#endif
#include <ctime>

bool BBS::seeded = false;

//PGPMPI BBS::state = 0;
//
//PGPMPI BBS::m = 0;
//
//const PGPMPI BBS::two = 2;

//void BBS::init(const std::string & seed, const unsigned int & bits, std::string p, std::string q){
//    if (!seeded){
//        char rand_buff[16];
//        RAND_seed(rand_buff, 16);
//        
//        gmp_randclass rng(gmp_randinit_default);                 // set up rng for initializing BBS
//        rng.seed(rng.get_z_bits(bits));                          // seed itself with random garbage
//        if (p == 0){
//            p = rng.get_z_bits(bits);
//            p = nextprime(p);                                    // find closest prime
//            while ((p & 3) != 3){                                // search for primes that are 3 = p mod 4
//                p += 1;
//                p = nextprime(p);                                // find next prime
//            }
//        }
//        if (q == 0){
//            q = rng.get_z_bits(bits);
//            q = nextprime(q);                                    // find closest prime
//            PGPMPI pq_gcd = 1025;
//            while (((q & 3) != 3) && (pq_gcd < 1024)){           // search for primes that are 3 = q mod 4 and gcd(p - 1, q - 1) is small
//                q += 1;
//                q = nextprime(q);                                // find next prime
//                pq_gcd = mpigcd(p-1, q-1);
//            }
//        }
//        m = p * q;
//        state = seed;
//        seeded = true;
//    }
//}

//void BBS::r_number(){
//    state = powm(state, two, m);
//}
//
//bool BBS::parity(const std::string & par) const{
//    PGPMPI value = state;
//    if (par == "least"){
//        return ((state & 1) == 1);
//    }
//    else{
//        bool t = 0;
//        while (value != 0){
//            t ^= ((value & 1) == 1);
//            value >>= 1;
//        }
//        t ^= (par == "odd");
//        return t;
//    }
//}

BBS::BBS(...):
    par()
{
//    if (!seeded){
//        throw std::runtime_error("Error: BBS must be seeded first.");
//    }
}

BBS::BBS(const std::string & SEED, const unsigned int & bits, std::string p, std::string q):
    par()
{
    srand((unsigned int)time(NULL)); //Note: Convert
  //  init(SEED, bits, p, q);

}

std::string BBS::randbit(){

    int i = rand() % 2;
    return (i == 1) ? "1" : "0";
}

void BBS::c_rand(unsigned char *dest, size_t length)
{
    RAND_bytes(dest, (int)length);
}


std::string BBS::rand_byts(const unsigned int & bits, const std::string & par){
    // returns string because SIZE might be larger than 64 bits
    
    int size = bits/8;
    unsigned char key[size];
    RAND_bytes(key, size);
//    std::string b;
    
//    for (unsigned char& k : key)
//    {
//        b += std::string(1, (char)k);
//        //std::cout << k << std::endl;
//        printf("%c",k);
//        printf("\n");
//        //printf("%o", k);
//    }
//    

    std::string my_std_string(reinterpret_cast<const char *>(key), 32);
    
  //  std::cout << my_std_string << std::endl;
    return my_std_string;
}


std::string BBS::rand_b(const unsigned int & bits){
    unsigned char key[bits];
    RAND_bytes(key, bits);
    std::string my_std_string(reinterpret_cast<const char *>(key), bits);
    return my_std_string;
}



std::string BBS::gen_random_key(const int len) {
    
    static const char alphanum[] =
    "0123456789"
    "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
    "abcdefghijklmnopqrstuvwxyz()*.!-=_";
    
    std::string out_c;
    size_t count = sizeof(alphanum);
    
    for (int i = 0; i < len; ++i) {
        out_c += alphanum[rand() % (count - 1)];
    }
    
    return out_c;
}
