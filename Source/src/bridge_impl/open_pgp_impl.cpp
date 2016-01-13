#include "bridge/open_pgp_key.hpp"
#include "bridge_impl/open_pgp_impl.hpp"
#include "bridge/encrypt_package.hpp"

namespace ProtonMail {
    std::shared_ptr <ProtonMail::OpenPgp> OpenPgp::create_instance() {
        return std::make_shared<OpenPgpImpl>();
    }

    std::shared_ptr <ProtonMail::OpenPgp> OpenPgp::create_instance_with_keys(
            const std::vector <OpenPgpKey> &keys) {
        return std::make_shared<OpenPgpImpl>();
    }

    OpenPgpImpl::OpenPgpImpl() {

    }


    OpenPgpKey OpenPgpImpl::generate_key() {
        return OpenPgpKey("hello private key", "hello public key");
    }


/**check is primary key passphrase ok */
    bool OpenPgpImpl::check_passphrase(const std::string &private_key,
                                       const std::string &passphrase) {
        return true;
    }

/**encrypt message */
    std::string OpenPgpImpl::encrypt_message(const std::string &address_id,
                                             const std::string &plan_text) {
        return "hello encrypt message";
    }

    std::string OpenPgpImpl::decrypt_message(const std::string &encrypt_text,
                                             const std::string &passphras) {
        return "hello decrypt message";
    }

    EncryptPackage OpenPgpImpl::encrypt_attachment(const std::string & address_id, const std::vector<uint8_t> & unencrypt_data, const std::string & file_name) {
        std::string out_string = "hello encrypt_attachment";
        std::vector<uint8_t> myVector(out_string.begin(), out_string.end());
        return EncryptPackage(myVector, myVector);
    }

    std::vector<uint8_t> OpenPgpImpl::decrypt_attachment(const std::vector<uint8_t> & key, const std::vector<uint8_t> & data, const std::string & passphras) {
        std::string out_string = "hello decrypt_attachment";
        std::vector<uint8_t> myVector(out_string.begin(), out_string.end());
        return myVector;
    }

    /**TODO : not done and not inuse */
    std::vector<uint8_t> OpenPgpImpl::decrypt_attachment_with_password(const std::vector<uint8_t> & key, const std::vector<uint8_t> & data, const std::string & password){
        std::string out_string = "hello decrypt_attachment";
        std::vector<uint8_t> myVector(out_string.begin(), out_string.end());
        return myVector;
    }

    std::vector<uint8_t> OpenPgpImpl::get_public_key_session_key(const std::vector<uint8_t> & keyPackage, const std::string & privateKey, const std::string & passphrase)
    {
        std::string out_string = "hello get_public_key_session_key";
        std::vector<uint8_t> myVector(out_string.begin(), out_string.end());
        return myVector;
    }

    std::vector<uint8_t> OpenPgpImpl::get_symmetric_session_key(const std::vector<uint8_t> & keyPackage, const std::string & password){
        std::string out_string = "hello get_symmetric_session_key";
        std::vector<uint8_t> myVector(out_string.begin(), out_string.end());
        return myVector;
    }

    std::vector<uint8_t> OpenPgpImpl::get_new_public_key_package(const std::vector<uint8_t> & session, const std::string & publicKey) {
        std::string out_string = "hello get_new_public_key_package";
        std::vector<uint8_t> myVector(out_string.begin(), out_string.end());
        return myVector;
    }

    std::vector<uint8_t> OpenPgpImpl::get_new_symmetric_key_package(const std::vector<uint8_t> & session, const std::string & password) {
        std::string out_string = "hello get_new_symmetric_key_package";
        std::vector<uint8_t> myVector(out_string.begin(), out_string.end());
        return myVector;
    }

    std::string OpenPgpImpl::encrypt_message_aes(const std::string & plain_text, const std::string & password) {
        return "hello encrypt_message_aes";
    }

    std::string OpenPgpImpl::decrypt_message_aes(const std::string & encrypted_message, const std::string & password) {
        return "hello decrypt_message_aes";
    }

    std::string OpenPgpImpl::encryptMailboxPWD(const std::string & unencrypted_pwd, const std::string & salt) {
        return "hello encryptMailboxPWD";
    }

    std::string OpenPgpImpl::decryptMailboxPWD(const std::string & encrypted_pwd, const std::string & salt) {
        return "hello decryptMailboxPWD";
    }


}