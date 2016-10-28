//
//  UTF8.cpp
//  OpenPGP
//
//  Created by Yanfeng Zhang on 1/31/15.
//  Copyright (c) 2015 Yanfeng Zhang. All rights reserved.
//

#include <utilities/UTF8.h>
#include <string>
#include <sstream>
#include <iostream>
#include <locale>
#include <utilities/includes.h>
//#include <codecvt>
#include <iomanip>
#include <iostream>
#include <fstream>
#include <cmath>

#include <regex>
#include <string>

std::string to_hex( unsigned int c )
{
    std::ostringstream stm ;
    stm << '%' << std::hex << std::uppercase << c ;
    return stm.str() ;
}

unsigned int to_string(char a, char b )
{
    int cint = 0;
    
    cint = (cint << 4) | e_val[a];
    cint = (cint << 4) | e_val[b];
    
    return cint;
}

std::string encode(std::string str)
{
    static std::string unreserved = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz-_.~";
    std::string r;
    
    for (int i = 0; i < str.length(); i++ )
    {
        char c = str.at(i);
        if (unreserved.find(c) != -1)
            r+=c;
        else
            r+=to_hex(c);
    }
    
    return r;
}


typedef unsigned char BYTE;

inline BYTE toHex(const BYTE &x)
{
    return x > 9 ? x -10 + 'A': x + '0';
}

inline BYTE fromHex(const BYTE &x)
{
    return isdigit(x) ? x-'0' : x-'A'+10;
}

std::string URLEncode(const std::string &sIn)
{
    std::string sOut;
    for( size_t ix = 0; ix < sIn.size(); ix++ )
    {
        BYTE buf[4];
        memset( buf, 0, 4 );
        if( isalnum( (BYTE)sIn[ix] ) )
        {
            buf[0] = sIn[ix];
        }
        //else if ( isspace( (BYTE)sIn[ix] ) ) //貌似把空格编码成%20或者+都可以
        //{
        //    buf[0] = '+';
        //}
        else
        {
            buf[0] = '%';
            buf[1] = toHex( (BYTE)sIn[ix] >> 4 );
            buf[2] = toHex( (BYTE)sIn[ix] % 16);
        }
        sOut += (char *)buf;
    }
    return sOut;
};

std::string URLDecode(const std::string &sIn)
{
    std::string sOut;
    for( size_t ix = 0; ix < sIn.size(); ix++ )
    {
        BYTE ch = 0;
        if(sIn[ix]=='%')
        {
            ch = (fromHex(sIn[ix+1])<<4);
            ch |= fromHex(sIn[ix+2]);
            ix += 2;
        }
        else if(sIn[ix] == '+')
        {
            ch = ' ';
        }
        else
        {
            ch = sIn[ix];
        }
        sOut += (char)ch;
    }
    return sOut;
}




const char HEX2DEC[256] =
{
    /*       0  1  2  3   4  5  6  7   8  9  A  B   C  D  E  F */
    /* 0 */ -1,-1,-1,-1, -1,-1,-1,-1, -1,-1,-1,-1, -1,-1,-1,-1,
    /* 1 */ -1,-1,-1,-1, -1,-1,-1,-1, -1,-1,-1,-1, -1,-1,-1,-1,
    /* 2 */ -1,-1,-1,-1, -1,-1,-1,-1, -1,-1,-1,-1, -1,-1,-1,-1,
    /* 3 */  0, 1, 2, 3,  4, 5, 6, 7,  8, 9,-1,-1, -1,-1,-1,-1,
    
    /* 4 */ -1,10,11,12, 13,14,15,-1, -1,-1,-1,-1, -1,-1,-1,-1,
    /* 5 */ -1,-1,-1,-1, -1,-1,-1,-1, -1,-1,-1,-1, -1,-1,-1,-1,
    /* 6 */ -1,10,11,12, 13,14,15,-1, -1,-1,-1,-1, -1,-1,-1,-1,
    /* 7 */ -1,-1,-1,-1, -1,-1,-1,-1, -1,-1,-1,-1, -1,-1,-1,-1,
    
    /* 8 */ -1,-1,-1,-1, -1,-1,-1,-1, -1,-1,-1,-1, -1,-1,-1,-1,
    /* 9 */ -1,-1,-1,-1, -1,-1,-1,-1, -1,-1,-1,-1, -1,-1,-1,-1,
    /* A */ -1,-1,-1,-1, -1,-1,-1,-1, -1,-1,-1,-1, -1,-1,-1,-1,
    /* B */ -1,-1,-1,-1, -1,-1,-1,-1, -1,-1,-1,-1, -1,-1,-1,-1,
    
    /* C */ -1,-1,-1,-1, -1,-1,-1,-1, -1,-1,-1,-1, -1,-1,-1,-1,
    /* D */ -1,-1,-1,-1, -1,-1,-1,-1, -1,-1,-1,-1, -1,-1,-1,-1,
    /* E */ -1,-1,-1,-1, -1,-1,-1,-1, -1,-1,-1,-1, -1,-1,-1,-1,
    /* F */ -1,-1,-1,-1, -1,-1,-1,-1, -1,-1,-1,-1, -1,-1,-1,-1
};

std::string ecape(std::string & sin)
{
    std::string aa = sin;
    //wchar_t *aa = L"冯a继b业";
    std::string ss = "";
    size_t size = aa.size();
    for(int i=0;i<size;i++)
    {
        if(aa[i] > (char)0xff) //翻译不翻译的关键
        {
            char tmp[5];
            sprintf(tmp,"%x",aa[i]);
            ss += "%u";
            ss += tmp;
        }
        else
        {
            char tmp[5];
            sprintf(tmp,"%c",aa[i]);
            ss += tmp;
        }
    }
  //  std::cout << ss << std::endl;
    return 0;
}



std::string urlencode_new(const std::string &s)
{
    //RFC 3986 section 2.3 Unreserved Characters (January 2005)
    const std::string unreserved = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789-_.~";
    
    std::string escaped="";
    for(size_t i=0; i<s.length(); i++)
    {
        if (unreserved.find_first_of(s[i]) != std::string::npos)
        {
            escaped.push_back(s[i]);
        }
        else
        {
            escaped.append("%");
            char buf[3];
            sprintf(buf, "%.2X", s[i]);
            escaped.append(buf);
        }
    }
    return escaped;
}






////good part => save as js


std::string decodeURIComponent(const std::string & sSrc)
{
    // Note from RFC1630:  "Sequences which start with a percent sign
    // but are not followed by two hexadecimal characters (0-9, A-F) are reserved
    // for future extension"
    
    const unsigned char * pSrc = (const unsigned char *)sSrc.c_str();
    const size_t SRC_LEN = sSrc.length();
    const unsigned char * const SRC_END = pSrc + SRC_LEN;
    const unsigned char * const SRC_LAST_DEC = SRC_END - 2;   // last decodable '%'
    
    char * const pStart = new char[SRC_LEN];
    char * pEnd = pStart;
    
    while (pSrc < SRC_LAST_DEC)
    {
        if (*pSrc == '%')
        {
            char dec1, dec2;
            if (-1 != (dec1 = HEX2DEC[*(pSrc + 1)])
                && -1 != (dec2 = HEX2DEC[*(pSrc + 2)]))
            {
                *pEnd++ = (dec1 << 4) + dec2;
                pSrc += 3;
                continue;
            }
        }
        
        *pEnd++ = *pSrc++;
    }
    
    // the last 2- chars
    while (pSrc < SRC_END)
        *pEnd++ = *pSrc++;
    
    std::string sResult(pStart, pEnd);
    delete [] pStart;
    return sResult;
}

// Only alphanum is safe.
const char SAFE[256] =
{
    /*      0 1 2 3  4 5 6 7  8 9 A B  C D E F */
    /* 0 */ 0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0,
    /* 1 */ 0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0,
    /* 2 */ 0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,1,0,
    /* 3 */ 1,1,1,1, 1,1,1,1, 1,1,0,0, 0,0,0,0,
    
    /* 4 */ 0,1,1,1, 1,1,1,1, 1,1,1,1, 1,1,1,1,
    /* 5 */ 1,1,1,1, 1,1,1,1, 1,1,1,0, 0,0,0,0,
    /* 6 */ 0,1,1,1, 1,1,1,1, 1,1,1,1, 1,1,1,1,
    /* 7 */ 1,1,1,1, 1,1,1,1, 1,1,1,0, 0,0,0,0,
    
    /* 8 */ 0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0,
    /* 9 */ 0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0,
    /* A */ 0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0,
    /* B */ 0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0,
    
    /* C */ 0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0,
    /* D */ 0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0,
    /* E */ 0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0,
    /* F */ 0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0
};


std::string js_encodeURIComponent(const std::string & sSrc)
{
    size_t size = sSrc.length();
    std::string out_str;
    
    for (int i=0; i<size; i++) {
        unsigned char code = sSrc[i];
        //std::cout << code << std::endl;
        if(code > 0x7f)
        {
            int charcode = code;
            int first_bits = 6;
            const int other_bits = 6;
            int first_val = 0xC0;
            int t = 0;
            
            std::string low;
            while (charcode >= (1 << first_bits))
            {
                {
                    t = 128 | (charcode & ((1 << other_bits)-1));
                    charcode >>= other_bits;
                    first_val |= 1 << (first_bits);
                    first_bits--;
                }
                low += to_hex(t);
            }
            t = first_val | charcode;
            out_str += to_hex(t);
            out_str += low;
        }
        else
        {
            if( (sSrc[i]>='a' && sSrc[i]<='z') || (sSrc[i]>='A' && sSrc[i]<='Z') || ( sSrc[i]>='0' && sSrc[i]<='9' ))
            {
                out_str += sSrc[i];
            }
            else
            {
                char tmp[3];
                sprintf(tmp,"%02x", sSrc[i]);
                out_str += "%";
                out_str += tmp;
            }
        }
        
    }
    
    return out_str;
}

std::string js_decodeURIComponent(const std::string &input)
{
    size_t size = input.length();
    std::string out_s;
    for (int i = 0 ; i<size; i++) {
        unsigned char code = input[i];
        if(code == '%')
        {
            unsigned int high = to_string(input[i+1], input[i+2]);
            
            int first_val = 0xC0;
            
            if(high > first_val)
            {
                unsigned int low = to_string(input[i+4], input[i+5]);
                
                int charcode = 0;
                int high_bit_mask = (1 << 6) -1;
                int high_bit_shift = 0;
                int total_bits = 0;
                const int other_bits = 6;
                
                int t = high;
                while((t & 0xC0) == 0xC0)
                {
                    t <<= 1;
                    t &= 0xff;
                    total_bits += 6;
                    high_bit_mask >>= 1;
                    high_bit_shift++;
                    charcode <<= other_bits;
                    charcode |= low & ((1 << other_bits)-1);
                }
                charcode |= ((t >> high_bit_shift) & high_bit_mask) << total_bits;
                out_s += charcode;
                i += 5;
            }
            else
            {
                unsigned int de_hex = to_string(input[i+1], input[i+2]);
                out_s += de_hex;
                i += 2;
            }
        }
        else
        {
            out_s += code;
        }
        
        //
        //        if (code < 128)
        //        {
        //            if(code == '%')
        //            {
        //                int cint;
        //                cint = (cint << 4) | e_val[input[i+1]];
        //                cint = (cint << 4) | e_val[input[i+2]];
        //                i+=2;
        //                out_s += (char)cint;
        //            }
        //            else
        //            {
        //                out_s += code;
        //            }
        //        }
        //        else
        //        {
        //                    }
    }
    //        else if (ch == '%') {
    //            int cint = 0;
    //            std::wstring ci;
    //            if ('u' != str[i+1]) {         // %XX : map to ascii(XX)
    //                cint = (cint << 4) | e_val[str[i+1]];
    //                cint = (cint << 4) | e_val[str[i+2]];
    //                i+=2;
    //                sbuf += (char)cint;
    //            } else {                            // %uXXXX : map to unicode(XXXX)
    //                cint = (cint << 4) | e_val[str[i+2]];
    //                cint = (cint << 4) | e_val[str[i+3]];
    //                cint = (cint << 4) | e_val[str[i+4]];
    //                cint = (cint << 4) | e_val[str[i+5]];
    //                i+=5;
    //
    //                ci = (wchar_t)cint;
    //                sbuf += converter.to_bytes(ci);
    //            }
    //
    //    }
    return out_s;
}


std::string encodeURIComponent(const std::string & sSrc)
{
    const char DEC2HEX[16 + 1] = "0123456789ABCDEF";
    const unsigned char * pSrc = (const unsigned char *)sSrc.c_str();
    const size_t SRC_LEN = sSrc.length();
    unsigned char * const pStart = new unsigned char[SRC_LEN * 3];
    unsigned char * pEnd = pStart;
    const unsigned char * const SRC_END = pSrc + SRC_LEN;
    
    for (; pSrc < SRC_END; ++pSrc)
    {
        if (SAFE[*pSrc])
            *pEnd++ = *pSrc;
        else
        {
            // escape this char
            *pEnd++ = '%';
            //char a = DEC2HEX[*pSrc >> 4];
            //char b = DEC2HEX[*pSrc & 0x0F];
            
           // std::cout << a << std::endl;
            //*pEnd++
            *pEnd++ = DEC2HEX[*pSrc >> 4];
           // std::cout << b << std::endl;
            
            *pEnd++ = DEC2HEX[*pSrc & 0x0F];
        }
    }
    
    std::string sResult((char *)pStart, (char *)pEnd);
    delete [] pStart;
    return sResult;
}




////

//std::string js_escape(std::string &str)
//{
//    std::wstring wcs;
//    
//    typedef std::codecvt_utf8_utf16<wchar_t> convert_type;
//    std::wstring_convert<convert_type, wchar_t> converter;
//    wcs = converter.from_bytes(str);
//    
//   // std::cout << wcs.length() << std::endl;
//    str = "";
//    for(int i=0;i<wcs.size();i++)
//    {
//        if(wcs[i]>0xff)
//        {
//            char tmp[5];
//            sprintf(tmp,"%04X",wcs[i]);
//            str += "%u";
//            str += tmp;
//        }
//        else
//        {
//            
//            if( (wcs[i]>='a' && wcs[i]<='z') || (wcs[i]>='A' && wcs[i]<='Z') || ( wcs[i]>='0' && wcs[i]<='9' ) || wcs[i] == '-' || wcs[i] == '_' || wcs[i] == '.')
//            {
//                str += converter.to_bytes(wcs[i]);
//            }
//            else
//            {
//                char tmp[3];
//                sprintf(tmp,"%04x",wcs[i]);
//                str += "%";
//                str += tmp;
//            }
//        }
//    }
//    return str;
//}
//
//
//std::string js_unescape(std::string &str)
//{
//    std::string sbuf;
//    
//    typedef std::codecvt_utf8<wchar_t> convert_type;
//    std::wstring_convert<convert_type, wchar_t> converter;
//    
//    
//    int i = 0;
//    int len = static_cast<int>(str.length());
//    while (i < len) {
//        int ch = str[i];
//        if ('A' <= ch && ch <= 'Z') {    // 'A'..'Z' : as it was
//            sbuf += ch;
//        } else if ('a' <= ch && ch <= 'z') {    // 'a'..'z' : as it was
//            sbuf += ch;
//        } else if ('0' <= ch && ch <= '9') {    // '0'..'9' : as it was
//            sbuf += ch;
//        } else if (ch == '-' || ch == '_'       // unreserved : as it was
//                   || ch == '.' || ch == '!'
//                   || ch == '~' || ch == '*'
//                   || ch == '\'' || ch == '('
//                   || ch == ')' || ch == '+') {
//            sbuf += ch;
//        } else if (ch == '%') {
//            int cint = 0;
//            std::wstring ci;
//            if ('u' != str[i+1]) {         // %XX : map to ascii(XX)
//                cint = (cint << 4) | e_val[str[i+1]];
//                cint = (cint << 4) | e_val[str[i+2]];
//                i+=2;
//                sbuf += (char)cint;
//            } else {                            // %uXXXX : map to unicode(XXXX)
//                cint = (cint << 4) | e_val[str[i+2]];
//                cint = (cint << 4) | e_val[str[i+3]];
//                cint = (cint << 4) | e_val[str[i+4]];
//                cint = (cint << 4) | e_val[str[i+5]];
//                i+=5;
//                
//                ci = (wchar_t)cint;
//                sbuf += converter.to_bytes(ci);
//            }
//        }
//        i++;
//    }
//    
//    return sbuf;
//}

std::string escape(std::string& s) {
    const int SRC_LEN = static_cast<int>(s.length());
    std::string out;
    for (int i = 0; i < SRC_LEN; i++) {
        char ch = s.at(i);
        if (ch == ' ') {                        // space : map to '+'
            out += to_hex(ch);
        } else if ('A' <= ch && ch <= 'Z') {    // 'A'..'Z' : as it was
            out += ch;
        } else if ('a' <= ch && ch <= 'z') {    // 'a'..'z' : as it was
            out += ch;
        } else if ('0' <= ch && ch <= '9') {    // '0'..'9' : as it was
            out += ch;
        } else if (ch == '-' || ch == '_'       // unreserved : as it was
                   || ch == '.' || ch == '!'
                   || ch == '~' || ch == '*'
                   || ch == '\'' || ch == '('
                   || ch == ')') {
            out += ch;
        } else if (ch <= 0x007F) {              // other ASCII : map to %XX
            //            out += to_hex(ch);
            //        } else {                                // unicode : map to %uXXXX
            out += '%';
            out += 'u';
            
            std::ostringstream stm ;
            stm << 'u';// << std::hex << std::uppercase << c ;
            
            
            for(int i = 0; i < 8; i++)
            {
                stm << std::hex << std::uppercase << ((ch >> i) & 1) ;
                // std::cout << ((ch >> i) & 1) << std::endl;
                
            }
            
          //  std::cout << hexlify(ch) << std::endl;
            
            std::string h = e_hex[(ch >> 8)];
          //  std::cout << h << std::endl;
            out += h ;
            h =  e_hex[(0x00FF & ch)];
           // std::cout << h << std::endl;
            out += h;
        }
    }
    return out;
}

//
//
/////
//
//std::string unescape(std::string s) {
//    StringBuffer sbuf = new StringBuffer();
//    int i = 0;
//    int len = s.length();
//    while (i < len) {
//        int ch = s.charAt(i);
//        if (ch == '+') {                        // + : map to ' '
//            sbuf.append(' ');
//        } else if ('A' <= ch && ch <= 'Z') {    // 'A'..'Z' : as it was
//            sbuf.append((char)ch);
//        } else if ('a' <= ch && ch <= 'z') {    // 'a'..'z' : as it was
//            sbuf.append((char)ch);
//        } else if ('0' <= ch && ch <= '9') {    // '0'..'9' : as it was
//            sbuf.append((char)ch);
//        } else if (ch == '-' || ch == '_'       // unreserved : as it was
//                   || ch == '.' || ch == '!'
//                   || ch == '~' || ch == '*'
//                   || ch == '\'' || ch == '('
//                   || ch == ')') {
//            sbuf.append((char)ch);
//        } else if (ch == '%') {
//            int cint = 0;
//            if ('u' != s.charAt(i+1)) {         // %XX : map to ascii(XX)
//                cint = (cint << 4) | val[s.charAt(i+1)];
//                cint = (cint << 4) | val[s.charAt(i+2)];
//                i+=2;
//            } else {                            // %uXXXX : map to unicode(XXXX)
//                cint = (cint << 4) | val[s.charAt(i+2)];
//                cint = (cint << 4) | val[s.charAt(i+3)];
//                cint = (cint << 4) | val[s.charAt(i+4)];
//                cint = (cint << 4) | val[s.charAt(i+5)];
//                i+=5;
//            }
//            sbuf.append((char)cint);
//        }
//        i++;
//    }
//    return sbuf.toString();
//}


std::string url_encode(const std::string &value) {
    std::ostringstream escaped;
    escaped.fill('0');
    escaped << std::hex;
    
    for (std::string::const_iterator i = value.begin(), n = value.end(); i != n; ++i) {
        std::string::value_type c = (*i);
        
        // Keep alphanumeric and other accepted characters intact
        if (isalnum(c) || c == '-' || c == '_' || c == '.' || c == '~') {
            escaped << c;
            continue;
        }
        
        // Any other characters are percent-encoded
        escaped << '%' << std::setw(2) << int((unsigned char) c);
    }
    
    return escaped.str();
}


std::string getHex(std::string buf) {
    std::string o;
    for (int i = 0; i < buf.length(); i++) {
        int n = static_cast<int>( buf[i] & 0xff );
        
        char tmp[3];
        sprintf(tmp,"%02x",n);
        o += "%";
        o += tmp;
    }
    return o;
}

//std::string js_encodeURIComponent(const std::string &input) {
//    if ("" == input) {
//        return input;
//    }
//
//    static std::string ALLOWED_CHARS = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789-_.!~*'()";
//
//    size_t l = input.length();
//    std::string o_out;
//    //  try {
//    for (int i = 0; i < l; i++) {
//        std::string e = input.substr(i, i + 1);
//
//        std::size_t found = ALLOWED_CHARS.find(e);
//        if (found==std::string::npos)
//        {
//            o_out += getHex(e);
//            continue;
//        }
//        o_out += e;
//    }
//    return o_out;
//    //    } catch (UnsupportedEncodingException e) {
//    //        e.printStackTrace();
//    //    }
//    // return input;
//}

int bin_value(char ch)
{
    if('0'<=ch && ch<='9')
    {
        return ch - '0';
    }
    else if('a'<=ch && ch<='z')
    {
        return ch - 'a' + 0x0A;
    }
    else if('A'<=ch && ch<='Z')
    {
        return ch - 'A' + 0x0A;
    }
    else
    {
        return -1;
    }
}

//not tested
std::string hex2bin(std::string& s_in)
{
    std::string out;
    
    for (int i = 0; i < s_in.size();) {
        //int a = (bin_value(s_in[0])<<4) & 0xF0;
        //int b = (bin_value(s_in[1])   ) & 0x0F;
        
        //        char out_a;
        //        sprintf(out, "%d", (a | b));
        // out += std::string(static_cast<int>(a | b));
        
        i+=2;
    }
    return out;
}



void A_to_B(const char* input)
{
    int ascii;           // used to store the ASCII number of a character
    size_t length = strlen(input);        //find the length of the user's input
    
   // std::cout << " ";
    
    for(int x = 0; x < length; x++)          //repeat until user's input have all been read
        // x < length because the last character is "\0"
    {
        ascii = input[x];        //store a character in its ASCII number
        
        /* Refer to http://www.wikihow.com/Convert-from-Decimal-to-Binary for conversion method used
         * in this program*/
        
        char* binary_reverse = new char [9];       //dynamic memory allocation
        char* binary = new char [9];
        
        int y = 0;    //counter used for arrays
        
        while(ascii != 1)    //continue until ascii == 1
        {
            if(ascii % 2 == 0)    //if ascii is divisible by 2
            {
                binary_reverse[y] = '0';   //then put a zero
            }
            else if(ascii % 2 == 1)    //if it isnt divisible by 2
            {
                binary_reverse[y] = '1';   //then put a 1
            }
            ascii /= 2;    //find the quotient of ascii / 2
            y++;    //add 1 to y for next loop
        }
        
        if(ascii == 1)    //when ascii is 1, we have to add 1 to the beginning
        {
            binary_reverse[y] = '1';
            y++;
        }
        
        if(y < 8)  //add zeros to the end of string if not 8 characters (1 byte)
        {
            for(; y < 8; y++)  //add until binary_reverse[7] (8th element)
            {
                binary_reverse[y] = '0';
            }
        }
        
        for(int z = 0; z < 8; z++)  //our array is reversed. put the numbers in the rigth order (last comes first)
        {
            binary[z] = binary_reverse[7 - z];
        }
        
       // std::cout << binary;   //display the 8 digit binary number
        
        delete [] binary_reverse;     //free the memory created by dynamic mem. allocation
        delete [] binary;
    }
    
   // std::cout << std::endl;
}

void B_to_A(const char* input)
{
    size_t length = strlen(input);     //get length of string
    
    int binary[8];    //array used to store 1 byte of binary number (1 character)
    int asciiNum = 0;      //the ascii number after conversion from binary
    char ascii;      //the ascii character itself
    
   // std::cout << " ";
    
    int z = 0;   //counter used
    
    for(int x = 0; x < length / 8; x++)     //reading in bytes. total characters = length / 8
    {
        for(int a = 0; a < 8; a++)      //store info into binary[0] through binary[7]
        {
            binary[a] = static_cast<int>( input[z] - 48 );      //z never resets
            z++;
        }
        
        int power[8];    //will set powers of 2 in an array
        int counter = 7;        //power starts at 2^0, ends at 2^7
        for(int x = 0; x < 8; x++)
        {
            power[x] = counter;      //power[] = {7, 6, 5, ..... 1, 0}
            counter--;    //decrement counter each time
        }
        
        for(int y = 0; y < 8; y++)    //will compute asciiNum
        {
            double a = binary[y];    //store the element from binary[] as "a"
            double b = power[y];    //store the lement from power[] as "b"
            
            asciiNum += a* std::pow(2, b);   //asciiNum = sum of a * 2^power where 0 <= power <= 7, power is int
        }
        
        ascii = asciiNum;   //assign the asciiNum value to ascii, to change it into an actual character
        asciiNum = 0;    //reset asciiNum for next loop
        
      //  std::cout << ascii;	//display the ascii character
    }
}


//encodeing
std::string btoa (std::string& s_in) {
    //    /var base64 = {};
    std::string PADCHAR = "=";
    std::string ALPHA = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
    
    //    base64.encode = function(s) {
    //        if (arguments.length !== 1) {
    //            throw new SyntaxError("Not enough arguments");
    //        }
//    auto padchar = PADCHAR;
//    auto alpha   = ALPHA;
//    var getbyte = base64.getbyte;
//    
//    var i, b10;
//    var x = [];
//    
//    // convert to string
//    s = '' + s;
//    
//    var imax = s.length - s.length % 3;
//    
//    if (s.length === 0) {
//        return s;
//    }
//    for (i = 0; i < imax; i += 3) {
//        b10 = (getbyte(s,i) << 16) | (getbyte(s,i+1) << 8) | getbyte(s,i+2);
//        x.push(alpha.charAt(b10 >> 18));
//        x.push(alpha.charAt((b10 >> 12) & 0x3F));
//        x.push(alpha.charAt((b10 >> 6) & 0x3f));
//        x.push(alpha.charAt(b10 & 0x3f));
//    }
//    switch (s.length - imax) {
//        case 1:
//            b10 = getbyte(s,i) << 16;
//            x.push(alpha.charAt(b10 >> 18) + alpha.charAt((b10 >> 12) & 0x3F) +
//                   padchar + padchar);
//            break;
//        case 2:
//            b10 = (getbyte(s,i) << 16) | (getbyte(s,i+1) << 8);
//            x.push(alpha.charAt(b10 >> 18) + alpha.charAt((b10 >> 12) & 0x3F) +
//                   alpha.charAt((b10 >> 6) & 0x3f) + padchar);
//            break;
//    }
//    return x.join('');
return "";
}


//base64.getbyte64 = function(s,i) {
//    // This is oddly fast, except on Chrome/V8.
//    //  Minimal or no improvement in performance by using a
//    //   object with properties mapping chars to value (eg. 'A': 0)
//    var idx = base64.ALPHA.indexOf(s.charAt(i));
//    if (idx === -1) {
//        throw base64.makeDOMException();
//    }
//    return idx;
//}


std::string atob (std::string& s_in) {

    char PADCHAR = '=';
    std::string ALPHA = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

        // convert to string
    //s_in = '' + s_in;
    // var getbyte64 = base64.getbyte64;
    int pads, i;//, b10;
    auto imax = s_in.length();
    if (imax == 0) {
        return s_in;
    }
    
    if (imax % 4 != 0) {
        // need throw exception throw base64.makeDOMException();
    }
    
    pads = 0;
    if (s_in[imax - 1] == PADCHAR) {
        pads = 1;
        if (s_in[imax - 2] == PADCHAR) {
            pads = 2;
        }
        // either way, we want to ignore this last block
        imax -= 4;
    }
    
    std::string s_out;
    for (i = 0; i < imax; i += 4) {
        auto b10 = (ALPHA[s_in[i]]<< 18) | (ALPHA[s_in[i+1]] << 12) | (ALPHA[s_in[i+2]] << 6) | ALPHA[s_in[i+3]];
        s_out += (uint8_t)(b10 >> 16);
        s_out += (uint8_t)((b10 >> 8) & 0xff);
        s_out += (uint8_t)(b10 & 0xff);
    }
    
    switch (pads) {
        case 1:
        {
            auto b10 = (ALPHA[s_in[i]] << 18) | (ALPHA[s_in[i+1]] << 12) | (ALPHA[s_in[i+2]] << 6);
            s_out += (uint8_t)(b10 >> 16);
            s_out += (uint8_t)((b10 >> 8) & 0xff);
            break;
        }
        case 2:
        {
            auto b11 = (ALPHA[s_in[i]] << 18) | (ALPHA[s_in[i+1]] << 12);
            s_out += (uint8_t)(b11 >> 16);
            break;
        }
    }
    return s_out;
}
