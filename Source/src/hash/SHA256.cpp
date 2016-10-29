#include <hash/SHA256.h>
#include <openssl/sha.h>

uint32_t SHA256::S0(const uint32_t & value) const{
    return ROR(value, 2, 32) ^ ROR(value, 13, 32) ^ ROR(value, 22, 32);
}

uint32_t SHA256::S1(const uint32_t & value) const{
    return ROR(value, 6, 32) ^ ROR(value, 11, 32) ^ ROR(value, 25, 32);
}

uint32_t SHA256::s0(const uint32_t & value) const{
    return ROR(value, 7, 32) ^ ROR(value, 18, 32) ^ (value >> 3);
}

uint32_t SHA256::s1(const uint32_t & value) const{
    return ROR(value, 17, 32) ^ ROR(value, 19, 32) ^ (value >> 10);
}

void SHA256::original_h(){
    ctx.h0 = 0x6a09e667;
    ctx.h1 = 0xbb67ae85;
    ctx.h2 = 0x3c6ef372;
    ctx.h3 = 0xa54ff53a;
    ctx.h4 = 0x510e527f;
    ctx.h5 = 0x9b05688c;
    ctx.h6 = 0x1f83d9ab;
    ctx.h7 = 0x5be0cd19;
}

void SHA256::calc(const std::string &data, context &state) const{
    for(unsigned int n = 0; n < (data.size() >> 6); n++){
        std::string temp = data.substr(n << 6, 64);
        uint32_t skey[64];
        for(uint8_t x = 0; x < 16; x++){
            skey[x] = (uint32_t)toint(temp.substr(x << 2, 4), 256);
        }
        for(uint8_t x = 16; x < 64; x++){
            skey[x] = s1(skey[x - 2]) + skey[x - 7] + s0(skey[x - 15]) + skey[x - 16];
        }
        uint32_t a = state.h0, b = state.h1, c = state.h2, d = state.h3, e = state.h4, f = state.h5, g = state.h6, h = state.h7;
        for(uint8_t x = 0; x < 64; x++){
            uint32_t t1 = h + S1(e) + (uint32_t)Ch(e, f, g) + SHA256_K[x] + skey[x];
            uint32_t t2 = S0(a) + (uint32_t)Maj(a, b, c);
            h = g;
            g = f;
            f = e;
            e = d + t1;
            d = c;
            c = b;
            b = a;
            a = t1 + t2;
        }
        state.h0 += a; state.h1 += b; state.h2 += c; state.h3 += d; state.h4 += e; state.h5 += f; state.h6 += g; state.h7 += h;
    }
}

SHA256::SHA256() :
    Hash(),
    ctx()
{
    original_h();
}

SHA256::SHA256(const std::string & str) :
    SHA256()
{
    update(str);
}

void SHA256::update(const std::string &str){

    stack = str;
}

std::string SHA256::hexdigest(){
    char outputBuffer[65];
    unsigned char hash[SHA256_DIGEST_LENGTH];
    SHA256_CTX sha256;
    SHA256_Init(&sha256);
    SHA256_Update(&sha256, stack.c_str(), stack.length());
    SHA256_Final(hash, &sha256);
    int i = 0;
    for(i = 0; i < SHA256_DIGEST_LENGTH; i++)
    {
        sprintf(outputBuffer + (i * 2), "%02x", hash[i]);
    }
    outputBuffer[64] = 0;
    std::string d = std::string(outputBuffer, 64);
    return d;
}

unsigned int SHA256::blocksize() const{
    return 512;
}

unsigned int SHA256::digestsize() const{
    return 256;
}
