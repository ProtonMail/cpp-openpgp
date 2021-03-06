#pragma once

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

#include "bridge/open_pgp.hpp"
#include <unordered_map>

namespace ProtonMail {

    class ExampleException: public std::exception {
        virtual const char* what() const throw() {
            return "Exception Thrown";
        }
    };

    extern ExampleException EXAMPLE_EXCEPTION;

    struct Address;
    class OpenPgpImpl : public ProtonMail::OpenPgp {

    private:
        std::shared_ptr<PGPSecretKey> m_private_key;
        std::shared_ptr<PGPPublicKey> m_public_key;

        bool m_is_private_key_loaded;
        bool m_is_public_key_loaded;

        bool m_is_passpharse_right;
        std::string m_str_passpharse;
        
        std::unordered_map<std::string, ProtonMail::Address> m_addresses;

    public:
        OpenPgpImpl();
        ~OpenPgpImpl();
        
        static bool m_is_debug_mode;
        
        /**generat new key pair */
        OpenPgpKey generate_key(const std::string & user_name, const std::string & domain, const std::string & passphrase, int32_t bits, int32_t time);
        
        bool add_address(const Address & address) ;

        bool remove_address(const std::string & address_id);

        bool clean_addresses();

        void enable_debug(bool isDebug);

        /**check is primary key passphrase ok */
        bool check_passphrase(const std::string &private_key, const std::string &passphrase);

        /**update single private key password */
        std::string update_single_passphrase(const std::string & private_key, const std::string & old_passphrase, const std::string & new_passphrase);

        /**update the information carried in the packet. //TODO need add more parameters */
        void update_private_info(const std::string & private_key);

        /**encrypt message */
        std::string encrypt_message(const std::string &address_id, const std::string &plan_text, const std::string & passphras, bool trim);

        std::string encrypt_message_single_key(const std::string & public_key, const std::string & plain_text, const std::string & private_key, const std::string & passphras, bool trim);
        
        std::string encrypt_message_single_binary_pub_key(const std::vector<uint8_t> & public_key, const std::string & plain_text, const std::string & private_key, const std::string & passphras, bool trim);

        std::string decrypt_message(const std::string &encrypt_text, const std::string &passphras);

        std::string decrypt_message_single_key(const std::string & encrypt_text, const std::string & private_key, const std::string & passphras);

        
        /**for signature */
        EncryptSignPackage encrypt_message_sign_external(const std::string & public_key, const std::string & private_key, const std::string & plain_text, const std::string & passphras);
        DecryptSignVerify decrypt_message_verify_single_key(const std::string & private_key, const std::string & passphras, const std::string & encrypted, const std::string & signature);
        DecryptSignVerify decrypt_message_verify(const std::string & passphras, const std::string & encrypted, const std::string & signature);

        
        std::string sign_detached(const std::string & private_key, const std::string & plain_text, const std::string & passphras);
        
        bool sign_detached_verify_single_pub_key(const std::string & public_key, const std::string & signature, const std::string & plain_text) ;
        bool sign_detached_verify_single_binary_pub_key(const std::vector<uint8_t> & public_key, const std::string & signature, const std::string & plain_text);
        bool sign_detached_verify_single_private_key(const std::string & private_key, const std::string & signature, const std::string & plain_text) ;
        bool sign_detached_verify(const std::string & signature, const std::string & plain_text) ;
        

        



        //
        EncryptPackage encrypt_attachment(const std::string & address_id, const std::vector<uint8_t> & unencrypt_data, const std::string & file_name, const std::string & passphras);

        EncryptPackage encrypt_attachment_single_key(const std::string & public_key, const std::vector<uint8_t> & unencrypt_data, const std::string & file_name, const std::string & private_key, const std::string & passphras);

        EncryptPackage encrypt_attachment_single_binary_key(const std::vector<uint8_t> & public_key, const std::vector<uint8_t> & unencrypt_data, const std::string & file_name, const std::string & private_key, const std::string & passphras);
        
        std::vector<uint8_t> decrypt_attachment(const std::vector<uint8_t> & key, const std::vector<uint8_t> & data, const std::string & passphras);

        std::vector<uint8_t> decrypt_attachment_single_key(const std::vector<uint8_t> & key, const std::vector<uint8_t> & data, const std::string & private_key, const std::string & passphras);

        /**TODO : not done and not inuse */
        std::vector<uint8_t> decrypt_attachment_with_password(const std::vector<uint8_t> & key, const std::vector<uint8_t> & data, const std::string & password);

        std::vector<uint8_t> get_public_key_session_key(const std::vector<uint8_t> & keyPackage, const std::string & passphrase);

        std::vector<uint8_t> get_public_key_session_key_single_key(const std::vector<uint8_t> & keyPackage, const std::string & privateKey, const std::string & passphrase);

        std::vector<uint8_t> get_symmetric_session_key(const std::vector<uint8_t> & keyPackage, const std::string & password);

        std::vector<uint8_t> get_new_public_key_package(const std::vector<uint8_t> & session, const std::string & publicKey);
        std::vector<uint8_t> get_new_public_key_package_binary(const std::vector<uint8_t> & session, const std::vector<uint8_t> & publicKey);

        std::vector<uint8_t> get_new_symmetric_key_package(const std::vector<uint8_t> & session, const std::string & password);

        std::string encrypt_message_aes(const std::string & plain_text, const std::string & password);

        std::string decrypt_message_aes(const std::string & encrypted_message, const std::string & password);

        std::string encrypt_mailbox_pwd(const std::string & unencrypted_pwd, const std::string & salt);

        std::string decrypt_mailbox_pwd(const std::string & encrypted_pwd, const std::string & salt);

        std::string read_clearsigned_message(const std::string & signed_message);

        int32_t throw_an_exception();
        
        std::string encrypt_hash_cbc(const std::string & plain_text, const std::string & password);
        
        std::string decrypt_hash_cbc(const std::string & encrypted_text, const std::string & password);
    };

}
