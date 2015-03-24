//
//  utility.cpp
//  OpenPGP
//
//  Created by Yanfeng Zhang on 1/31/15.
//  Copyright (c) 2015 Yanfeng Zhang. All rights reserved.
//

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

#include <string.h>

namespace pm {
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
        aes_cfb_256_encrypt();
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
        std::cout << hexlify(data) << std::endl;
        
        std::cout << data << std::endl;
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
        std::string messageID = "11147588";
        std::string IVSource = MD5("wqPBNpeCf").hexdigest();
        std::string KeySource = "zeULFiE7Axedotu9QSoPIxNh8oCz3QcFoPvYPLka";
        std::string SaltSource = "DstYFJQHMsKwqPBNpeCfatXsfpnMRcRtTJVwUTXu";
        
        
        messageID = messageID + SaltSource.substr(0, 40 - messageID.size());
        
        
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
}

