//
//  base64.cpp
//  OpenPGP
//
//  Created by Yanfeng Zhang on 1/31/15.
//  Copyright (c) 2015 Yanfeng Zhang. All rights reserved.
//

#include <iostream>
#include <algorithm>
#include <stdexcept>

#include <utilities/base64.h>
#include <utilities/utility.h>
#include <utilities/UTF8.h> 
#include <utilities/includes.h>



static const std::string base64_chars =
"ABCDEFGHIJKLMNOPQRSTUVWXYZ"
"abcdefghijklmnopqrstuvwxyz"
"0123456789+/";


static inline bool is_base64(unsigned char c) {
    return (isalnum(c) || (c == '+') || (c == '/'));
}


std::string base64_encode(const std::string &s)
{
    static const std::string base64_chars = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
    size_t i=0,ix=0,leng = s.length();
    std::string r; r.reserve( (1 + ((leng - 1) / 3))*4 );
    
    for(i=0,ix=leng - leng%3; i<ix; i+=3)
    {
        r+= base64_chars[ (s[i] & 0xfc) >> 2 ];
        r+= base64_chars[ ((s[i] & 0x03) << 4) + ((s[i+1] & 0xf0) >> 4)  ];
        r+= base64_chars[ ((s[i+1] & 0x0f) << 2) + ((s[i+2] & 0xc0) >> 6)  ];
        r+= base64_chars[ s[i+2] & 0x3f ];
    }
    if (ix<leng)
    {
        r+= base64_chars[ (s[ix] & 0xfc) >> 2 ];
        r+= base64_chars[ ((s[ix] & 0x03) << 4) + (ix+1<leng ? (s[ix+1] & 0xf0) >> 4 : 0)];
        r+= ix+1<leng ? base64_chars[ ((s[ix+1] & 0x0f) << 2) ] : '=';
        r+= "=";
    }
    return r;
}

std::string base64_encode(unsigned char const* bytes_to_encode, unsigned int in_len) {
    std::string ret;
    int i = 0;
    int j = 0;
    unsigned char char_array_3[3];
    unsigned char char_array_4[4];
    
    while (in_len--) {
        char_array_3[i++] = *(bytes_to_encode++);
        if (i == 3) {
            char_array_4[0] = (char_array_3[0] & 0xfc) >> 2;
            char_array_4[1] = ((char_array_3[0] & 0x03) << 4) + ((char_array_3[1] & 0xf0) >> 4);
            char_array_4[2] = ((char_array_3[1] & 0x0f) << 2) + ((char_array_3[2] & 0xc0) >> 6);
            char_array_4[3] = char_array_3[2] & 0x3f;
            
            for(i = 0; (i <4) ; i++)
                ret += base64_chars[char_array_4[i]];
            i = 0;
        }
    }
    
    if (i)
    {
        for(j = i; j < 3; j++)
            char_array_3[j] = '\0';
        
        char_array_4[0] = (char_array_3[0] & 0xfc) >> 2;
        char_array_4[1] = ((char_array_3[0] & 0x03) << 4) + ((char_array_3[1] & 0xf0) >> 4);
        char_array_4[2] = ((char_array_3[1] & 0x0f) << 2) + ((char_array_3[2] & 0xc0) >> 6);
        char_array_4[3] = char_array_3[2] & 0x3f;
        
        for (j = 0; (j < i + 1); j++)
            ret += base64_chars[char_array_4[j]];
        
        while((i++ < 3))
            ret += '=';
        
    }
    
    return ret;
    
}

std::string base64_decode(std::string const& encoded_string) {
    size_t in_len = encoded_string.size();
    size_t i = 0;
    size_t j = 0;
    int in_ = 0;
    unsigned char char_array_4[4], char_array_3[3];
    std::string ret;
    
    while (in_len-- && ( encoded_string[in_] != '=') && is_base64(encoded_string[in_])) {
        char_array_4[i++] = encoded_string[in_]; in_++;
        if (i ==4) {
            for (i = 0; i <4; i++)
                char_array_4[i] = static_cast<unsigned char>(base64_chars.find(char_array_4[i]));
            
            char_array_3[0] = (char_array_4[0] << 2) + ((char_array_4[1] & 0x30) >> 4);
            char_array_3[1] = ((char_array_4[1] & 0xf) << 4) + ((char_array_4[2] & 0x3c) >> 2);
            char_array_3[2] = ((char_array_4[2] & 0x3) << 6) + char_array_4[3];
            
            for (i = 0; (i < 3); i++)
                ret += char_array_3[i];
            i = 0;
        }
    }
    
    if (i) {
        for (j = i; j <4; j++)
            char_array_4[j] = 0;
        
        for (j = 0; j <4; j++)
            char_array_4[j] = static_cast<unsigned char>(base64_chars.find(char_array_4[j]));
        
        char_array_3[0] = (char_array_4[0] << 2) + ((char_array_4[1] & 0x30) >> 4);
        char_array_3[1] = ((char_array_4[1] & 0xf) << 4) + ((char_array_4[2] & 0x3c) >> 2);
        char_array_3[2] = ((char_array_4[2] & 0x3) << 6) + char_array_4[3];
        
        for (j = 0; (j < i - 1); j++) ret += char_array_3[j];
    }
    
    return ret;
}


//std::string encode_utf8_base64(std::string & in)
//{
//    //std::cout << in.length() << std::endl;
//   // std::cout << in<<std::endl;
//    std::string aaa =  js_encodeURIComponent(in);
//   // std::cout << aaa<<std::endl;
//    //
//    std::string base_decoded = js_unescape(aaa);
//   // std::cout << base_decoded<<std::endl;
//    
//    std::string decoded = base64_encode((unsigned char*)base_decoded.c_str(), (int)base_decoded.size());
//    
//  //  std::cout << decoded<<std::endl;
//    pm::optimized_trim(decoded);
//    
//    return decoded;
//}
//
//std::string encode_utf8_base64_msg(std::string & in)
//{
//  //  std::cout << in.length() << std::endl;
//   // std::cout << in<<std::endl;
//    std::string aaa =  encodeURIComponent(in);
//   // std::cout << aaa<<std::endl;
//    
//    std::string base_decoded = js_unescape(aaa);
//   // std::cout << base_decoded<<std::endl;
//    
//    std::string decoded = base64_encode((unsigned char*)base_decoded.c_str(), (int)base_decoded.size());
//    
//  //  std::cout << decoded<<std::endl;
//    pm::optimized_trim(decoded);
//    
//    return decoded;
//
//}

std::string decode_utf8_base64(std::string & in)
{
    pm::optimized_trim(in);
    //std::cout << in<<std::endl;
    std::string aaa = base64_decode(in); //atob(in); //decode
    //std::cout << hexlify( aaa) <<std::endl;
    //std::cout <<  aaa <<std::endl;
    
    //return aaa;
    std::string base_decoded = encodeURIComponent(aaa);//js_escape(aaa);
   // std::cout << base_decoded<<std::endl;
    
    std::string decoded = js_decodeURIComponent(base_decoded);
    
   // std::cout << decoded<<std::endl;
  //  std::cout << hexlify( decoded) <<std::endl;
    return decoded;
}


std::string decode_utf8_base64_msg(std::string & in)
{
    pm::optimized_trim(in);
    //std::cout << in<<std::endl;
    std::string aaa = base64_decode(in); //atob(in); //decode
    //std::cout << hexlify( aaa) <<std::endl;
    //std::cout <<  aaa <<std::endl;
    
    //return aaa;
    std::string base_decoded = encodeURIComponent(aaa);//js_escape(aaa);
   // std::cout << base_decoded<<std::endl;
    
    std::string decoded = decodeURIComponent(base_decoded);
    
  //  std::cout << decoded<<std::endl;
  //  std::cout << hexlify( decoded) <<std::endl;
    return decoded;
}




std::string string_to_hex(const std::string& input)
{
    static const char* const lut = "0123456789ABCDEF";
    size_t len = input.length();
    
    std::string output;
    output.reserve(2 * len);
    for (size_t i = 0; i < len; ++i)
    {
        const unsigned char c = input[i];
        output.push_back(lut[c >> 4]);
        output.push_back(lut[c & 15]);
    }
    return output;
}

std::string hex_to_string(const std::string& input)
{
    static const char* const lut = "0123456789abcdef";
    size_t len = input.length();
    if (len & 1) throw std::invalid_argument("odd length");
    
    std::string output;
    output.reserve(len / 2);
    for (size_t i = 0; i < len; i += 2)
    {
        char a = input[i];
        const char* p = std::lower_bound(lut, lut + 16, a);
        if (*p != a)
            throw std::invalid_argument("not a hex digit");
        
        char b = input[i + 1];
        const char* q = std::lower_bound(lut, lut + 16, b);
        if (*q != b)
            throw std::invalid_argument("not a hex digit");
        
        output.push_back(((p - lut) << 4) | (q - lut));
    }
    return output;
}





