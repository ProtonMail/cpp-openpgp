//
//  utility.cpp
//  OpenPGP
//
//  Created by Yanfeng Zhang on 1/31/15.
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



#include <utilities/utility.h>
#include <hash/MD5.h>
#include <utilities/utilities.h>
#include <utilities/base64.h>
#include <openpgp/cfb.h>

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


#include <iostream>
#include <string>
#include <sstream>
#include <algorithm>
#include <iterator>

#include <bitset>         // std::bitset

namespace ProtonMail {

    
    std::vector<std::string> str_split(const std::string &str, const std::string &delim) {
        std::vector<std::string> tokens;
        // Skip delimiters at beginning.
        std::string::size_type lastPos = str.find_first_not_of(delim, 0);
        // Find first "non-delimiter".
        std::string::size_type pos     = str.find_first_of(delim, lastPos);
        
        while (std::string::npos != pos || std::string::npos != lastPos)
        {
            // Found a token, add it to the vector.
            tokens.push_back(str.substr(lastPos, pos - lastPos));
            // Skip delimiters.  Note the "not_of"
            lastPos = str.find_first_not_of(delim, pos);
            // Find next "non-delimiter"
            pos = str.find_first_of(delim, lastPos);
        }
        return tokens;
    }
    
    // trim from start
    std::string &ltrim(std::string &s) {
        s.erase(s.begin(), std::find_if(s.begin(), s.end(),
                                        std::not1(std::ptr_fun<int, int>(std::isspace))));
        return s;
    }
    
    // trim from end
    std::string &rtrim(std::string &s) {
        s.erase(std::find_if(s.rbegin(), s.rend(),
                             std::not1(std::ptr_fun<int, int>(std::isspace))).base(), s.end());
        return s;
    }
    
    // trim from both ends
    std::string &str_trim(std::string &s) {
        return ltrim(rtrim(s));
    }
    
    void optimized_trim(std::string& s)
    {
        std::string::size_type pos = s.find_last_not_of(' ');
        if(pos != std::string::npos)
        {
            if (s.length()!=pos+1)//if there are trailing whitespaces erase them
                s.erase(pos+1);
            pos = s.find_first_not_of(' ');
            if(pos!=0) //if there are leading whitespaces erase them
                s.erase(0, pos);
        }
        else s="";
    }
    
    std::string decrypt_message_id(std::string& enc_msg)
    {
       // aes_cfb_256_encrypt();
        std::string test_msg = "x_-YHVQVFZT-L35gCPBeMMnyXZe8vkcOGM_zZM3a5Uyw1giMFvg5jg==";
        enc_msg = test_msg;
        std::string IVSource = MD5("wqPBNpeCf").hexdigest();
        std::string KeySource = "zeULFiE7Axedotu9QSoPIxNh8oCz3QcFoPvYPLka";
        std::string SaltSource = "DstYFJQHMsKwqPBNpeCfatXsfpnMRcRtTJVwUTXu";
        auto BlockSize = 16;
        auto IV =  IVSource.substr(0, 16);//.substringToIndex(advance(IVSource.startIndex,BlockSize))
        auto EncKey = KeySource.substr(0, BlockSize);
        
    
        std::replace(enc_msg.begin(), enc_msg.end(), '_', '/');
        std::replace(enc_msg.begin(), enc_msg.end(), '-', '+');
        auto EncMessageID = base64_decode(enc_msg);
        
        
        auto t = use_OpenPGP_CFB_decrypt(9,  0, EncMessageID, EncKey);
        
        std::string data = use_normal_CFB_decrypt(9, EncMessageID, EncKey, IV);
        //std::cout << hexlify(data) << std::endl;
        
        //std::cout << data << std::endl;
//        let decodedData = NSData(base64EncodedString: EncMessageID, options: NSDataBase64DecodingOptions.init(0))
//        let decodedString = NSString(data: decodedData!, encoding: NSUTF8StringEncoding)
//        println(decodedString) // foo
//        
//        
//        let cryptData    = NSMutableData(length: Int(decodedData!.length) + kCCBlockSizeAES128)
//        var cryptPointer = UnsafeMutablePointer<UInt8>(cryptData!.mutableBytes)
//        let cryptLength  = size_t(cryptData!.length)
//        
//        var numBytesEncrypted :UInt = 0
//        var cryptStatus = CCCrypt(
//                                  UInt32(kCCDecrypt),
//                                  UInt32(kCCAlgorithmAES128),
//                                  UInt32(kCCOptionPKCS7Padding),
//                                  EncKey.dataUsingEncoding(NSUTF8StringEncoding),
//                                  EncKey.dataUsingEncoding(NSUTF8StringEncoding)?.length,
//                                  IV.dataUsingEncoding(NSUTF8StringEncoding),                                // will be NULL if ivData is nil
//                                  decodedData,
//                                  decodedData?.length,
//                                  cryptPointer,
//                                  cryptLength,

        return "";
    }
    
    
    std::string aes_cfb_256_encrypt()
    {
//        std::string messageID = "11147588";
//        std::string IVSource = MD5("wqPBNpeCf").hexdigest();
//        std::string KeySource = "zeULFiE7Axedotu9QSoPIxNh8oCz3QcFoPvYPLka";
//        std::string SaltSource = "DstYFJQHMsKwqPBNpeCfatXsfpnMRcRtTJVwUTXu";
//        
//        
//        messageID = messageID + SaltSource.substr(0, 40 - messageID.size());
//        
//        
//        EVP_CIPHER_CTX ctx;
//        const EVP_CIPHER * cipher;
//        EVP_CIPHER_CTX_init(&ctx);
//        cipher = EVP_aes_128_ctr();
//        
//        auto BlockSize = 16;
//        auto IV =  IVSource.substr(0, BlockSize);//.substringToIndex(advance(IVSource.startIndex,BlockSize))
//        auto EncKey = KeySource.substr(0, BlockSize);
//        
//        EVP_EncryptInit(&ctx, cipher, (unsigned char*)EncKey.c_str(), (unsigned char*)IV.c_str());
//        
//        std::string in_str = messageID;
//        unsigned char outbuf[40];
//        int outlen, inlen = 0;
//        
//        if(!EVP_EncryptUpdate(&ctx, outbuf, &outlen, (unsigned char*)in_str.c_str(), in_str.size()))
//            return "";
//        
//        std::string out_str((char*)&outbuf);
//        
//        std::cout << out_str << std::endl;
//        
//        std::cout << hexlify(out_str) << std::endl;
//        
//        std::cout << base64_encode(out_str) << std::endl;
//        
//        
//        std::cout << base64_encode(unhexlify("08c9170b55958c653bb8ae3b133e6f3c4ed759c8e5c813929261cb8d303715cf03807d6695409396")) << std::endl;
//        
//        if(!EVP_EncryptFinal(&ctx, outbuf, &outlen))
//            return "";
//        
//        
//        EVP_CIPHER_CTX_cleanup(&ctx);
        
        return "";
    }
    void aes_cfb_256_decrypt()
    {
        
        
//        unsigned char key[32];
//        strcpy(key, "10000000000000000000000000000002");
//        unsigned char iv[8];
//        unsigned char inbuf[BUFSIZE], outbuf[BUFSIZE];
//        EVP_CIPHER_CTX ctx;
//        
//        EVP_CIPHER_CTX_init(&ctx);
//        EVP_DecryptInit(&ctx, EVP_aes_256_cfb(), key, 0);
//        
//        while(1) {
//            inlen = fread(inbuf, 1, BUFSIZE, in);
//            if(inlen <= 0) break;
//            if(!EVP_DecryptUpdate(&ctx, outbuf, &outlen, inbuf, inlen)) return 0;
//            fwrite(outbuf, 1, outlen, out);
//        }
//        
//        if(!EVP_DecryptFinal(&ctx, outbuf, &outlen)) return 0;
//        fwrite(outbuf, 1, outlen, out);  
//        EVP_CIPHER_CTX_cleanup(&ctx);  
//        return 1;  
//    
                   /* Allow enough space in output buffer for additional block */
//            unsigned char inbuf[1024], outbuf[1024 + EVP_MAX_BLOCK_LENGTH];
//            int inlen, outlen;
//            EVP_CIPHER_CTX ctx;
//            /* Bogus key and IV: we'd normally set these from
//             * another source.
//             */
//            unsigned char key[] = "0123456789abcdeF";
//            unsigned char iv[] = "1234567887654321";
//            /* Don't set key or IV right away; we want to check lengths */
//            EVP_CIPHER_CTX_init(&ctx);
//            EVP_CipherInit_ex(&ctx, EVP_aes_128_cbc(), NULL, NULL, NULL,
//                              do_encrypt);
//            OPENSSL_assert(EVP_CIPHER_CTX_key_length(&ctx) == 16);
//            OPENSSL_assert(EVP_CIPHER_CTX_iv_length(&ctx) == 16);
//            /* Now we can set key and IV */
//            EVP_CipherInit_ex(&ctx, NULL, NULL, key, iv, do_encrypt);
//            for(;;)
//            {
//                inlen = fread(inbuf, 1, 1024, in);
//                if(inlen <= 0) break;
//                if(!EVP_CipherUpdate(&ctx, outbuf, &outlen, inbuf, inlen))
//                {
//                    /* Error */
//                    EVP_CIPHER_CTX_cleanup(&ctx);
//                    return 0;
//                }
//                fwrite(outbuf, 1, outlen, out);
//            }
//            if(!EVP_CipherFinal_ex(&ctx, outbuf, &outlen))
//            {
//                /* Error */
//                EVP_CIPHER_CTX_cleanup(&ctx);
//                return 0;
//            }
//            fwrite(outbuf, 1, outlen, out);
//            EVP_CIPHER_CTX_cleanup(&ctx);
//            return 1;
        
    }
    
    std::string quote_printable_decode(const std::string &input) {
        const int hexVal[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 0, 0, 0, 0, 0, 0, 0, 10, 11, 12, 13, 14, 15};
        
        /**
         * BitSet of printable characters as defined in RFC 1521.
         */
        std::bitset<256> PRINTABLE_CHARS;
        std::bitset<256> CRLF_CHARS;
        std::bitset<256> HEX_CHARS;
        
        const char ESCAPE_CHAR = '=';
        const char TAB = 9;
        const char SPACE = 32;
        const char CR = '\r';
        const char LF = '\n';

        for (int i = 33; i <= 60; i++) {
            PRINTABLE_CHARS.set(i);
        }
        for (int i = 62; i <= 126; i++) {
            PRINTABLE_CHARS.set(i);
        }
        PRINTABLE_CHARS.set(TAB);
        PRINTABLE_CHARS.set(SPACE);
        
        CRLF_CHARS.set(CR);
        CRLF_CHARS.set(LF);
        
        // normalized hex is numeric & upper alpha
        for (int i = 48; i <= 57; i++) {
            HEX_CHARS.set(i);
        }
        for (int i = 65; i <= 70; i++) {
            HEX_CHARS.set(i);
        }
        //// Static initializer for printable chars collection
        
        std::vector<int> output;
        auto size = input.size();
        for (int i = 0; i < size; ++i)
        {
            auto b = input[i];
            if (PRINTABLE_CHARS.test(b) || CRLF_CHARS.test(b)) {
                output.push_back(b);
            } else {
                if (b == ESCAPE_CHAR) {
                    if ((++i) < size) {
                        auto b1 = input[i];
                        if (HEX_CHARS.test(b1)) {
                            if ((++i) < size) {
                                auto b2 = input[i];
                                if (HEX_CHARS.test(b2)) {
                                    auto m = (hexVal[b1 - '0'] << 4) + hexVal[b2 - '0'];
                                    output.push_back(m);
                                } else {
                                    throw std::runtime_error("Error: MALFORMED_INPUT.");
                                }
                            } else {
                                throw std::runtime_error("Error: MALFORMED_INPUT.");
                            }
                        } else {
                            // remove mta extra whitespace
                            while (b1 != CR) {
                                if (b1 != SPACE && b1 != TAB) {
                                    throw std::runtime_error("Error: MALFORMED_INPUT.");
                                }
                                b1 = input[++i]; // eats the CR and WS
                            }
                            b1 = input[++i]; // eats the LF
                        }
                    } else {
                        throw std::runtime_error("Error: MALFORMED_INPUT.");
                    }
                } else {
                    throw std::runtime_error("Error: MALFORMED_INPUT.");
                }
            }
        }


        return std::string(output.begin(), output.end());


//        std::vector<int> output;
//        auto size = input.size();
//        for (int i = 0; i < size; ++i)
//        {
//            if (input[i] == '=')
//            {
//                output.push_back((hexVal[input[++i] - '0'] << 4) + hexVal[input[++i] - '0']);
//            }
//            else
//            {
//                output.push_back(input[i]);
//            }
//        }
//
//        return std::string(output.begin(), output.end());
    }

    std::string quote_printable_encode(const std::string &s) {
//        QString *output = new QString();
//
//        char byte;
//        const char hex[] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F'};
//
//        for (int i = 0; i < input.length() ; ++i)
//        {
//            byte = input[i];
//            
//            if ((byte == 0x20) || (byte >= 33) && (byte <= 126) && (byte != 61))
//            {
//                output->append(byte);
//            }
//            else
//            {
//                output->append('=');
//                output->append(hex[((byte >> 4) & 0x0F)]);
//                output->append(hex[(byte & 0x0F)]);
//            }
//        }
//        
//        return *output;
        return "";
    }
    
    std::string replaceAll(std::string& str_in, const std::string& from, const std::string& to) {
        std::string str = str_in;
        if(from.empty())
            return str_in;
        size_t start_pos = 0;
        while((start_pos = str.find(from, start_pos)) != std::string::npos) {
            str.replace(start_pos, from.length(), to);
            start_pos += to.length(); // In case 'to' contains 'from', like replacing 'x' with 'yx'
        }
        return str;
    }
}

