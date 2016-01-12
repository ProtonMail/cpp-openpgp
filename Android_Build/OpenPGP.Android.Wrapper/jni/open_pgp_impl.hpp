#pragma once

#include "bridge/open_pgp.hpp"

namespace ProtonMail {

    class OpenPgpImpl : public ProtonMail::OpenPgp {

    public:
        OpenPgpImpl();

        /**generat new key pair */
        OpenPgpKey generate_key();

        /**check is primary key passphrase ok */
        bool check_passphrase(const std::string &private_key, const std::string &passphrase);

        /**encrypt message */
        std::string encrypt_message(const std::string &address_id, const std::string &plan_text);

        std::string decrypt_message(const std::string &encrypt_text, const std::string &passphras);

        //
        EncryptPackage encrypt_attachment(const std::string & address_id, const std::vector<uint8_t> & unencrypt_data, const std::string & file_name);

        std::vector<uint8_t> decrypt_attachment(const std::vector<uint8_t> & key, const std::vector<uint8_t> & data, const std::string & passphras);

        /**TODO : not done and not inuse */
        std::vector<uint8_t> decrypt_attachment_with_password(const std::vector<uint8_t> & key, const std::vector<uint8_t> & data, const std::string & password);

        std::vector<uint8_t> get_public_key_session_key(const std::vector<uint8_t> & keyPackage, const std::string & privateKey, const std::string & passphrase);

        std::vector<uint8_t> get_symmetric_session_key(const std::vector<uint8_t> & keyPackage, const std::string & password);

        std::vector<uint8_t> get_new_public_key_package(const std::vector<uint8_t> & session, const std::string & publicKey);

        std::vector<uint8_t> get_new_symmetric_key_package(const std::vector<uint8_t> & session, const std::string & password);

        std::string encrypt_message_aes(const std::string & plain_text, const std::string & password);

        std::string decrypt_message_aes(const std::string & encrypted_message, const std::string & password);

        std::string encryptMailboxPWD(const std::string & unencrypted_pwd, const std::string & salt);

        std::string decryptMailboxPWD(const std::string & encrypted_pwd, const std::string & salt);

    };

}
