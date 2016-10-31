
#include <utilities/utilities.h>
#include <utilities/includes.h>
#include <utilities/BBS.h>
#include <utilities/base64.h>
#include <hash/Hash.h>
#include <hash/HMAC.h>
#include <encryption/AES.h>

namespace pm {

    
    
//    
//    static function encrypt_message_id($MessageID, $isRandom = true) {
//        
//        std::string key_one = 
//        $key1 = pack("H*","5f8b0f69c2e711c19f43
//                             633f77f70a59a1198fd7
//                             3b5ce2d53e1ec43b43b37e66"); // need keep it forever
//    
    
    
    //        $key2 = pack("H*","4b6b0acf4524565b756530b0383de0b8a801b79bf242ccfeab1906e8520a63fd"); // need keep it forever
//        $key3 = pack("H*","001190d069249177ce51ee891b9c4cea52d0323ca5f90ec18d23273f22205a83");
//        $text = $MessageID;
//        $block_size = mcrypt_get_block_size(MCRYPT_RIJNDAEL_128,MCRYPT_MODE_CBC);
//        $pad = $block_size - (strlen($MessageID) % $block_size);
//        $text .= str_repeat(chr($pad),$pad);
//        
//        $iv_size = mcrypt_get_iv_size(MCRYPT_RIJNDAEL_128,MCRYPT_MODE_CBC);
//        if($isRandom)
//        {
//            $iv = mcrypt_create_iv($iv_size,MCRYPT_DEV_URANDOM);
//        }
//        else
//        {
//            $new_iv = hash_hmac("sha256", $MessageID ,$key3,true);
//            $iv = substr($new_iv, 0 , $iv_size);
//        }
//        $crypt = mcrypt_encrypt(MCRYPT_RIJNDAEL_128, $key1, $text,MCRYPT_MODE_CBC,$iv);
//        $h_mac = hash_hmac("sha256",$iv.$crypt,$key2,true);
//        $output = base64_encode($iv . $crypt . $h_mac);
//        $output = str_replace(array('/','+'), array('_','-'), $output);
//        //echo bin2hex($iv . $crypt . $h_mac) . "\r\n";
//        return $output;
//    }
    
    const std::string key_factory = "3b98f67c7fcec923b56a8e74bffffc00358ac382840d7bf131071ff6353562f85051397ab6f39f832d9dcc49724dce94eb65ff282f83266b57e8a9306adb04149d6f14998cfdcd5a526e0c81a5d1696e39ddc86c3c3bd5e672f70356b87198589eab94a0943a94960241a9587d7bf05c139f391daeda316290008a85616ed1fb7fa9ed060b931823f8e59c7457c2e9f7a2b4c6ee87404243254c970b926e7f5c4dd8f4194366a4d8e3da95c2ccc55b06bbf436f81c759b4fc1342bd27f1d356235f7a3c56ed216f90e45efedd3229a92d63ef1e825c1e4e243520fa3663ce89de6e5279e68e890e0d6b5653d405412719b45adeef94a8f95d29b6fb70c6c6f53b1687687829ed36ca3bc3db989c38f07536868ca45f2cd02e2ba5fe413e61b346d7c6003b3d9b54c1b93abe4cfcef6f2fd84faa0b11dc94f2a076268b761c7b2be5116da3a1a31e872a1437a81a7648f3b060313969e066246193baf9299f49851f4c0df3c84acf799c46d50c6666782744c99b18dec752d26815addc0598aa1";
    //const int factory_size = 768;
    
    const int iKeySize = 64; //(32 * 2)
    const int iIVSize = 16; //(32 * 2)
    const int hmacSize = 32;
   
    const int iKeyOne = 20;  //first key position
    const int iKeyTwo = 100;
    const int iKeyThree = 180;
    std::string encrypt_mailbox_password(std::string plaintext, std::string salt_value)
    {
        std::string key_one = unhexlify(key_factory.substr(iKeyOne, iKeySize));   //for salt hash
        std::cout << "key_one:" << hexlify(key_one) << std::endl;
        std::string key_two = unhexlify(key_factory.substr(iKeyTwo, iKeySize));    //for aes cbc 256
        std::cout << "key_two:" << hexlify(key_two) << std::endl;
        std::string key_three = unhexlify(key_factory.substr(iKeyThree, iKeySize));  //for enc data hash
        std::cout << "key_three:" << hexlify(key_three) << std::endl;
        
        std::cout << hexlify(BBS().rand_b(iIVSize)) << std::endl;
        std::string random_iv = unhexlify(salt_value) +BBS().rand_b(iIVSize);
        random_iv = random_iv.substr(0, iIVSize);
        std::cout << "random:" << hexlify(random_iv) << std::endl;
        
        //std::string hash_salt = hash_hmac("sha256", salt_value, key_one, true);
        
//        std::cout << "hash_salt:" << hexlify(hash_salt) << std::endl;
//        std::cout << "hash+plain" << hexlify(hash_salt + plaintext) << std::endl;
        
        std::string enc_data = aes_cbc_256_encrypt(key_two, random_iv, plaintext);
        std::cout << "enc_data:" << hexlify(enc_data) << std::endl;
        
        std::string hash_enc_data = hash_hmac("sha256", random_iv + enc_data, key_three, true);
        std::cout << "hash_enc_data:" << hexlify(hash_enc_data) << std::endl;
        return hexlify(hash_enc_data + random_iv + enc_data);
    }
    
    std::string decrypt_mailbox_password(std::string enc_value, std::string salt_value)
    {
        std::string key_one = unhexlify(key_factory.substr(iKeyOne, iKeySize));   //for salt hash
        std::cout << "key_one:" << hexlify(key_one) << std::endl;
        std::string key_two = unhexlify(key_factory.substr(iKeyTwo, iKeySize));    //for aes cbc 256
        std::cout << "key_two:" << hexlify(key_two) << std::endl;
        std::string key_three = unhexlify(key_factory.substr(iKeyThree, iKeySize));  //for enc data hash
        std::cout << "key_three:" << hexlify(key_three) << std::endl;
        
        std::string unhexlify_enc_value = unhexlify(enc_value);
        std::cout << "input:" << enc_value << std::endl;
        
        std::string hash_enc_data = unhexlify_enc_value.substr(0, hmacSize);
        std::cout << "hash_enc_data:" << hexlify(hash_enc_data) << std::endl;
        std::string random_iv = unhexlify_enc_value.substr(hmacSize, iIVSize);
        std::cout << "random:" << hexlify(random_iv) << std::endl;
        
        int enc_data_start = hmacSize + iIVSize;
        std::string enc_data = unhexlify_enc_value.substr(enc_data_start);
        std::cout << "enc_data:" << hexlify(enc_data) << std::endl;
        
        std::string match_hash_enc_data = hash_hmac("sha256", random_iv + enc_data, key_three, true);
        std::cout << "match_hash_enc_data:" << hexlify(match_hash_enc_data) << std::endl;
        
        std::cout << hexlify(match_hash_enc_data) << std::endl;
        std::cout << hexlify(hash_enc_data) << std::endl;
        
        int compare = match_hash_enc_data.compare(hash_enc_data );
        if( compare != 0)
        {
            std::cout << "hash_enc_data not match" << std::endl;
            return "hash_enc_data not match";
        }
        
        std::string decrypt_data = aes_cbc_256_decrypt(key_two, random_iv, enc_data);
        std::cout << decrypt_data << std::endl;
        if(hexlify(random_iv).find(salt_value) != 0 && salt_value.find(hexlify(random_iv)) != 0)
        {
            std::cout << "random:" << hexlify(random_iv) << std::endl;
            std::cout << "salt_value:" << hexlify(salt_value) << std::endl;
            std::cout << "salt not match" << std::endl;
            return random_iv; //bad here
        }
        
        return decrypt_data; //base64_encode(decrypt_data);
//        std::cout << hexlify(decrypt_data) << std::endl;
//        //decrypt_data = unhexlify(decrypt_data);
//
//        std::string match_hash_salt = unhexlify(decrypt_data.substr(0, hmacSize * 2));
//        std::cout << hexlify(match_hash_salt) << std::endl;
//        std::string hash_salt = hash_hmac("sha256", salt_value, key_one, true);
//        std::cout << hexlify(hash_salt) << std::endl;
//        if( match_hash_salt.compare(hash_salt) != 0)
//        {
//            std::cout << "hash_salt not match" << std::endl;
//            return "";
//        }
//        std::string plain_text = decrypt_data.substr(hmacSize*2);
//        return plain_text;
    }
}
