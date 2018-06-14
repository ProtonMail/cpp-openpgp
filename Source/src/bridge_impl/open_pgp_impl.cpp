#include <openpgp/PGPKey.h>
#include <openpgp/openpgp.h>
#include <openpgp/PGPCleartextSignature.h>
#include <openpgp/PGPMessage.h>
#include <openpgp/encrypt.h>
#include <openpgp/decrypt.h>
#include <openpgp/sign.h>
#include <bridge/address.hpp>


#include "bridge/open_pgp_key.hpp"
#include "bridge_impl/open_pgp_impl.hpp"
#include "bridge/encrypt_package.hpp"
#include "bridge/encrypt_sign_package.hpp"
#include "bridge/decrypt_sign_verify.hpp"

#include <exception/pgp_exception_define.h>
#include <exception/pgp_exception.h>

#include <utilities/utilities.h>
#include <utilities/BBS.h>

#include <openpgp/private_key.h>

#include <openpgp/FindKey.h>
#include <regex>



namespace ProtonMail {
    // static functions
    
    std::shared_ptr <ProtonMail::OpenPgp> OpenPgp::create_instance() {
        return std::make_shared<OpenPgpImpl>();
    }
    
    std::shared_ptr <ProtonMail::OpenPgp> OpenPgp::create_instance_with_address(const Address & address) {
        std::shared_ptr <ProtonMail::OpenPgp> pOpenPGP = std::make_shared<OpenPgpImpl>();
        pOpenPGP->add_address(address);
        return pOpenPGP;
    }
    
    std::shared_ptr <ProtonMail::OpenPgp> OpenPgp::create_instance_with_addresses(const std::vector<Address> & address) {
        std::shared_ptr <ProtonMail::OpenPgp> pOpenPGP = std::make_shared<OpenPgpImpl>();
        for (auto add : address) // access by reference to avoid copying
        {
            pOpenPGP->add_address(add);
        }
        return pOpenPGP;
    }
    
    void OpenPgp::enable_debug(bool isDebug) {
        //OpenPgpImpl::m_is_debug_mode = isDebug;
    }
    
    
    std::vector<uint8_t> OpenPgp::random_bits(int32_t bits) {
        auto random_out = BBS().rand_byts(bits);
        return std::vector<uint8_t>(random_out.begin(), random_out.end());
    }
    
//    OpenPgpKey OpenPgp::generate_new_key(const std::string & user_id,
//                                         const std::string & email,
//                                         const std::string & passphrase,
//                                         int32_t bits) {
//        ProtonMail::pgp::openpgp p;
//        if (user_id.empty()) {
//            throw std::runtime_error("Invalid user name format");
//        }
//        if (email.empty()) {
//            throw std::runtime_error("Invalid email format");
//        }
//        if (passphrase.empty()) {
//            throw std::runtime_error("Invalid passphrase format");
//        }
//        std::string comments = "create by ios";
//        std::string priv_key = "";
//        std::string pub_key = "";
//        p.generate_new_key(bits, passphrase, user_id, email, comments, pub_key, priv_key);
//        
//        return OpenPgpKey("", pub_key, priv_key, "", false);
//    }
    
    std::string OpenPgp::update_single_passphrase(const std::string & private_key,
                                                  const std::string & old_passphrase,
                                                  const std::string & new_passphrase) {
        std::string str_private_key = private_key;
        PGPSecretKey secret_key;
        secret_key.set_is_debug(false);
        secret_key.read(str_private_key);
        
        bool isOk = check_private_passphrase(secret_key, old_passphrase);
        if (!isOk) {
            return "";
        }
        std::string new_key = ProtonMail::pgp::update_passphrase(secret_key, old_passphrase, new_passphrase);
        return new_key;
    }
    
    
    /**check is primary key passphrase ok */
    bool OpenPgp::check_passphrase(const std::string &private_key,
                                   const std::string &passphrase) {
        try
        {
            std::string str_private_key = private_key;
            PGPSecretKey privateKey(str_private_key);
            return check_private_passphrase(privateKey, passphrase);
        }
        catch (const ProtonMail::pgp_exception & pgp_ex)
        {
            
        }
        catch (const std::runtime_error& error)
        {
            
        }
        catch (const std::exception& e)
        {
            
        }
        catch (...)
        {
            
        }
        return false;
    }
    
    std::vector<OpenPgpKey> OpenPgp::update_keys_passphrase(const std::vector<OpenPgpKey> & private_keys,
                                                            const std::string & old_passphrase,
                                                            const std::string & new_passphrase) {
        //any kind of exceptions will stop this update
        auto updated_keys = std::vector<OpenPgpKey>();
        for (auto key : private_keys) {
            std::string str_private_key = key.private_key;
            PGPSecretKey secret_key;
            secret_key.set_is_debug(false);
            secret_key.read(str_private_key);
            
            try {
                std::string new_key = ProtonMail::pgp::update_passphrase(secret_key, old_passphrase, new_passphrase);
                updated_keys.push_back(OpenPgpKey(key.key_id, key.public_key, new_key, key.finger_print, true));
            }
            catch (...)
            {
                updated_keys.push_back(OpenPgpKey(key.key_id, key.public_key, key.private_key, key.finger_print, false));
            }
        }
        return updated_keys;
    }
    
    //
    //
    OpenPgpImpl::OpenPgpImpl() {
        m_private_key = std::make_shared<PGPSecretKey>();
    }
    
    OpenPgpImpl::~OpenPgpImpl() {
        m_private_key.reset();
    }
    
//    OpenPgpKey OpenPgp::generate_key_with_email(const std::string & email,
//                                                    const std::string & passphrase,
//                                                    int32_t bits) {
//        ProtonMail::pgp::openpgp p;
//        if (email.empty()) {
//            throw std::runtime_error("Invalid email address");
//        }
//        //std::string email = user_name + "@" + domain;
//        std::string comments = ""; //"create by ios"; //remove the comments because the frentend is not friendly with it.
//        std::string priv_key = "";
//        std::string pub_key = "";
//        p.generate_new_key(bits, passphrase, email/*user_name*/, email, comments, pub_key, priv_key);
//        
//        return OpenPgpKey("", pub_key, priv_key, "", false);
//    }
    
    OpenPgpKey OpenPgpImpl::generate_key(const std::string & user_name,
                                         const std::string & domain,
                                         const std::string & passphrase,
                                         int32_t bits,
                                         int32_t time) {
        ProtonMail::pgp::openpgp p;
        if (user_name.empty()) {
            throw std::runtime_error("Invalid user name format");
        }
        std::string email = user_name + "@" + domain;
        std::string comments = ""; //"create by ios"; //remove the comments because the frentend is not friendly with it.
        
        std::string priv_key = "";
        std::string pub_key = "";
        p.generate_new_key(bits, passphrase, email/*user_name*/, email, comments, pub_key, priv_key, time);
        
        return OpenPgpKey("", pub_key, priv_key, "", false);
    }
    
    bool OpenPgpImpl::add_address(const Address & address) {
        m_addresses.insert (std::pair<std::string, Address>(address.address_id, address));
        for (const auto &key : address.keys) {
            std::string private_key = key.private_key;
            m_private_key->read(private_key);
        }
        return true;
    }
    
    bool OpenPgpImpl::remove_address(const std::string & address_id) {
        return false;
    }
    
    bool OpenPgpImpl::clean_addresses() {
        m_addresses.clear();
        m_private_key = std::make_shared<PGPSecretKey>();
        return true;
    }
    
    /**update the information carried in the packet. //TODO need add more parameters */
    void OpenPgpImpl::update_private_info(const std::string & private_key) {
        
    }
    
    
    /**decrypt message use the address key ring with password */
    std::string OpenPgp::decrypt_message_with_address(const Address & address, const std::string & encrypt_text, const std::string & passphras) {
        std::string encrypt_msg = encrypt_text;
        PGPSecretKey secret_key;
        for (const auto &key : address.keys) {
            std::string private_key = key.private_key;
            secret_key.read(private_key);
        }
        ProtonMail::PMPGPMessage pm_pgp_msg(encrypt_msg, false);
        bool verify = false; //ignore
        std::string plain_text = decrypt_pka(secret_key, pm_pgp_msg, passphras, verify, false);
        return plain_text;
    }
    
    /**decrypt attachment use the address key ring with password */
    std::vector<uint8_t> OpenPgp::decrypt_attachment_with_address(const Address & address, const std::vector<uint8_t> & key, const std::vector<uint8_t> & data, const std::string & passphras) {
        
        PGPSecretKey secret_key;
        for (const auto &key : address.keys) {
            std::string private_key = key.private_key;
            secret_key.read(private_key);
        }

        std::string str_key_package(key.begin(), key.end());
        std::string str_data_package (data.begin(), data.end());
        
        ProtonMail::PMPGPMessage pm_pgp_msg(str_key_package, true);
        pm_pgp_msg.append(str_data_package, true);
        
        bool verify = false;
        std::string test_plain_txt = decrypt_pka(secret_key, pm_pgp_msg, passphras, verify, false);
        
        std::vector<uint8_t> out_vector(test_plain_txt.begin(), test_plain_txt.end());
        return out_vector;
    }
    
    /**encrypt message */
    std::string OpenPgpImpl::encrypt_message(const std::string &address_id,
                                             const std::string &plan_text,
                                             const std::string &passphras,
                                             bool trim) {
        
        std::unordered_map<std::string, Address>::const_iterator got = m_addresses.find (address_id);
        
        std::string user_pub_key = got->second.keys[0].public_key;
        std::string user_priv_key = got->second.keys[0].private_key;
        PGPPublicKey pub(user_pub_key);
        
        std::regex re("([ \t]+)(?=(\\r\\n|\\n)|$)");
        std::string unencrypt_msg = trim ? std::regex_replace(plan_text, re, "") : plan_text;
        
        PGPSecretKey::Ptr privKey = nullptr;
        
        if (!user_priv_key.empty() && !passphras.empty()) {
            privKey = std::make_shared<PGPSecretKey>(user_priv_key);
        }
        
        PGPMessage encrypted_pgp = encrypt_pka(pub, unencrypt_msg, "", 9, 2, true, privKey, passphras, 0x01);
        std::string encrypt_message = encrypted_pgp.write();
        return encrypt_message;
    }
    
    std::string OpenPgpImpl::encrypt_message_single_key(const std::string & public_key,
                                                        const std::string & plain_text,
                                                        const std::string & private_key,
                                                        const std::string & passphras,
                                                        bool trim) {
        
        std::string str_user_public_key = public_key;
        PGPPublicKey pub(str_user_public_key);
        
        std::regex re("([ \t]+)(?=(\\r\\n|\\n)|$)");
        std::string unencrypt_msg = trim ? std::regex_replace(plain_text, re, "") : plain_text;
        
        std::string user_priv_key = private_key;
        
        PGPSecretKey::Ptr privKey = nullptr;
        if (!private_key.empty() && !passphras.empty()) {
            privKey = std::make_shared<PGPSecretKey>(user_priv_key);
        }
        
        PGPMessage encrypted_pgp = encrypt_pka(pub, unencrypt_msg, "", 9, 2, true, privKey, passphras, 0x01);
        std::string encrypt_message = encrypted_pgp.write();
        
        return encrypt_message;
    }
    
    std::string OpenPgpImpl::encrypt_message_single_binary_pub_key(const std::vector<uint8_t> & public_key, const std::string & plain_text, const std::string & private_key, const std::string & passphras, bool trim) {
        std::string str_user_public_key(public_key.begin(), public_key.end());
        PGPPublicKey pub(str_user_public_key);
        
        std::regex re("([ \t]+)(?=(\\r\\n|\\n)|$)");
        std::string unencrypt_msg = trim ? std::regex_replace(plain_text, re, "") : plain_text;
        
        std::string user_priv_key = private_key;
        
        PGPSecretKey::Ptr privKey = nullptr;
        if (!private_key.empty() && !passphras.empty()) {
            privKey = std::make_shared<PGPSecretKey>(user_priv_key);
        }
        
        PGPMessage encrypted_pgp = encrypt_pka(pub, unencrypt_msg, "", 9, 2, true, privKey, passphras, 0x01);
        std::string encrypt_message = encrypted_pgp.write();
        
        return encrypt_message;
    }
    
    
    std::string OpenPgpImpl::decrypt_message(const std::string &encrypt_text,
                                             const std::string &passphras) {
        
        std::string encrypt_msg = encrypt_text;
        ProtonMail::PMPGPMessage pm_pgp_msg(encrypt_msg, false);
        
        bool verify = false;
        std::string plain_text = decrypt_pka(*m_private_key, pm_pgp_msg, passphras, verify, false);
        
        return plain_text;
    }
    
    std::string OpenPgpImpl::decrypt_message_single_key(const std::string & encrypt_text,
                                                        const std::string & private_key,
                                                        const std::string & passphras) {
        std::string str_private_key = private_key;
        
        PGPSecretKey pgp_private_key(str_private_key);
        
        std::string encrypt_msg = encrypt_text;
        ProtonMail::PMPGPMessage pm_pgp_msg(encrypt_msg, false);
        
        bool verify = false;
        std::string plain_text = decrypt_pka(pgp_private_key, pm_pgp_msg, passphras, verify, false);
        
        return plain_text;
    }
    
    EncryptPackage OpenPgpImpl::encrypt_attachment(const std::string & address_id,
                                                   const std::vector<uint8_t> & unencrypt_data,
                                                   const std::string & file_name, const std::string & passphras) {
        
        //NSData to string need error handling here
        std::string unencrypt_msg(unencrypt_data.begin(), unencrypt_data.end());
        
        // here need add more check
        std::unordered_map<std::string, Address>::const_iterator got = m_addresses.find (address_id);
        
        std::string user_pub_key = got->second.keys[0].public_key;
        std::string user_priv_key = got->second.keys[0].private_key;
        
        PGPPublicKey pub(user_pub_key);
        
        PGPSecretKey::Ptr privKey = nullptr;
        
        if (!user_priv_key.empty() && !passphras.empty()) {
            privKey = std::make_shared<PGPSecretKey>(user_priv_key);
        }
        
        PGPMessage encrypted_pgp = encrypt_pka(pub, unencrypt_msg, file_name, 9, 2, true, privKey, passphras, 0x00);
        
        std::string keyPackage = encrypted_pgp.write(1, 0, 1);
        std::string dataPackage = encrypted_pgp.write(1, 0, 18);
        
        return EncryptPackage(std::vector<uint8_t>(keyPackage.begin(), keyPackage.end()), std::vector<uint8_t>(dataPackage.begin(), dataPackage.end()));
    }
    
    EncryptPackage OpenPgpImpl::encrypt_attachment_single_key(const std::string & public_key,
                                                              const std::vector<uint8_t> & unencrypt_data,
                                                              const std::string & file_name, const std::string & private_key, const std::string & passphras) {
        
        std::string str_public_key = public_key;
        std::string unencrypt_msg(unencrypt_data.begin(), unencrypt_data.end());
        
        PGPPublicKey pub(str_public_key);
        
        
        std::string user_priv_key = private_key;
        PGPSecretKey::Ptr privKey = nullptr;
        if (!private_key.empty() && !passphras.empty()) {
            privKey = std::make_shared<PGPSecretKey>(user_priv_key);
        }
        PGPMessage encrypted_pgp = encrypt_pka(pub, unencrypt_msg, file_name, 9, 2, true, privKey, passphras, 0x00);
        
        std::string keyPackage = encrypted_pgp.write(1, 0, 1);
        std::string dataPackage = encrypted_pgp.write(1, 0, 18);
        
        return EncryptPackage(std::vector<uint8_t>(keyPackage.begin(), keyPackage.end()), std::vector<uint8_t>(dataPackage.begin(), dataPackage.end()));
    }
    
    EncryptPackage OpenPgpImpl::encrypt_attachment_single_binary_key(const std::vector<uint8_t> & public_key, const std::vector<uint8_t> & unencrypt_data, const std::string & file_name, const std::string & private_key, const std::string & passphras) {
        
        
        std::string str_public_key(public_key.begin(), public_key.end());
        std::string unencrypt_msg(unencrypt_data.begin(), unencrypt_data.end());
        
        PGPPublicKey pub(str_public_key);
        
        
        std::string user_priv_key = private_key;
        PGPSecretKey::Ptr privKey = nullptr;
        if (!private_key.empty() && !passphras.empty()) {
            privKey = std::make_shared<PGPSecretKey>(user_priv_key);
        }
        PGPMessage encrypted_pgp = encrypt_pka(pub, unencrypt_msg, file_name, 9, 2, true, privKey, passphras, 0x00);
        
        std::string keyPackage = encrypted_pgp.write(1, 0, 1);
        std::string dataPackage = encrypted_pgp.write(1, 0, 18);
        
        return EncryptPackage(std::vector<uint8_t>(keyPackage.begin(), keyPackage.end()), std::vector<uint8_t>(dataPackage.begin(), dataPackage.end()));
        
    }
    
    std::vector<uint8_t> OpenPgpImpl::decrypt_attachment(const std::vector<uint8_t> & key,
                                                         const std::vector<uint8_t> & data,
                                                         const std::string & passphras) {
        
        std::string str_key_package(key.begin(), key.end());
        std::string str_data_package (data.begin(), data.end());
        
        ProtonMail::PMPGPMessage pm_pgp_msg(str_key_package, true);
        pm_pgp_msg.append(str_data_package, true);
        
        bool verify = false;
        std::string test_plain_txt = decrypt_pka(*m_private_key, pm_pgp_msg, passphras, verify, false);
        
        std::vector<uint8_t> out_vector(test_plain_txt.begin(), test_plain_txt.end());
        return out_vector;
    }
    
    
    std::vector<uint8_t> OpenPgpImpl::decrypt_attachment_single_key(const std::vector<uint8_t> & key,
                                                                    const std::vector<uint8_t> & data,
                                                                    const std::string & private_key,
                                                                    const std::string & passphras) {
        
        std::string str_key_package(key.begin(), key.end());
        std::string str_data_package (data.begin(), data.end());
        std::string str_private_key = private_key;
        
        PGPSecretKey pgp_private_key(str_private_key);
        
        ProtonMail::PMPGPMessage pm_pgp_msg(str_key_package, true);
        pm_pgp_msg.append(str_data_package, true);
        
        bool verify = false;
        std::string test_plain_txt = decrypt_pka(pgp_private_key, pm_pgp_msg, passphras, verify, false);
        
        std::vector<uint8_t> out_vector(test_plain_txt.begin(), test_plain_txt.end());
        return out_vector;
    }
    
    
    
    EncryptPackage OpenPgp::split_message(const std::string & encrypted) {
        std::string encrypted_message = encrypted;
        
        ProtonMail::PMPGPMessage pm_pgp_msg(encrypted_message, false);
        
        std::string keyPackage = pm_pgp_msg.write(1, 0, 1);
        std::string dataPackage = pm_pgp_msg.write(1, 0, 18);
        
        return EncryptPackage(std::vector<uint8_t>(keyPackage.begin(), keyPackage.end()), std::vector<uint8_t>(dataPackage.begin(), dataPackage.end()));
    }
    
    std::string  OpenPgp::combine_packages(const std::vector<uint8_t> & key, const std::vector<uint8_t> & data) {
        std::string str_key_package(key.begin(), key.end());
        std::string str_data_package (data.begin(), data.end());
        
        ProtonMail::PMPGPMessage pm_pgp_msg(str_key_package, true);
        pm_pgp_msg.append(str_data_package, true);
        
        return pm_pgp_msg.write();
    }

    
    
    /**TODO : not done and not inuse */
    std::vector<uint8_t> OpenPgpImpl::decrypt_attachment_with_password(const std::vector<uint8_t> & key,
                                                                       const std::vector<uint8_t> & data,
                                                                       const std::string & password) {
        std::string str_key_package(key.begin(), key.end());
        std::string str_data_package(data.begin(), data.end());
        
        ProtonMail::PMPGPMessage pm_pgp_msg(str_key_package, true);
        pm_pgp_msg.append(str_data_package, true);
        
        std::string test_plain_txt = decrypt_sym(pm_pgp_msg, password);
        
        std::vector<uint8_t> out_vector(test_plain_txt.begin(), test_plain_txt.end());
        return out_vector;
    }
    
    std::vector<uint8_t> OpenPgpImpl::get_public_key_session_key(const std::vector<uint8_t> & keyPackage,
                                                                 const std::string & passphrase) {
        
        std::string str_key_package(keyPackage.begin(), keyPackage.end());
        ProtonMail::PMPGPMessage pm_pgp_msg(str_key_package, true);
        
        std::string sessionKey = decrypt_pka_only_session(*m_private_key, pm_pgp_msg, passphrase);
        
        std::vector<uint8_t> out_vector(sessionKey.begin(), sessionKey.end());
        return out_vector;
    }
    
    std::vector<uint8_t> OpenPgpImpl::get_public_key_session_key_single_key(const std::vector<uint8_t> & keyPackage,
                                                                            const std::string & privateKey,
                                                                            const std::string & passphrase) {
        
        std::string str_private_key = privateKey;
        
        PGPSecretKey pgp_private_key(str_private_key);
        
        std::string str_key_package(keyPackage.begin(), keyPackage.end());
        ProtonMail::PMPGPMessage pm_pgp_msg(str_key_package, true);
        
        std::string sessionKey = decrypt_pka_only_session(pgp_private_key, pm_pgp_msg, passphrase);
        
        std::vector<uint8_t> out_vector(sessionKey.begin(), sessionKey.end());
        return out_vector;
    }
    
    std::vector<uint8_t> OpenPgpImpl::get_symmetric_session_key(const std::vector<uint8_t> & keyPackage,
                                                                const std::string & password){
        
        std::string str_key_package(keyPackage.begin(), keyPackage.end());
        ProtonMail::PMPGPMessage pm_pgp_msg(str_key_package, true);
        std::string sessionkey = decrypt_pka_only_sym_session(pm_pgp_msg, password);
        
        std::vector<uint8_t> out_vector(sessionkey.begin(), sessionkey.end());
        
        return out_vector;
    }
    
    std::vector<uint8_t> OpenPgpImpl::get_new_public_key_package(const std::vector<uint8_t> & session,
                                                                 const std::string & publicKey) {
        
        std::string str_sessionKey (session.begin(), session.end());
        
        std::string user_pub_key = publicKey;
        
        PGPPublicKey pub(user_pub_key);
        
        PGPMessage out_msg = encrypt_pka_only_session(pub, str_sessionKey);
        
        std::string encrypted_data = out_msg.write(1);
        
        std::vector<uint8_t> out_vector(encrypted_data.begin(), encrypted_data.end());
        
        return out_vector;
    }
    
    std::vector<uint8_t> OpenPgpImpl::get_new_symmetric_key_package(const std::vector<uint8_t> & session,
                                                                    const std::string & password) {
        
        std::string str_key_package(session.begin(), session.end());
        
        PGPMessage out_msg = encrypt_pka_only_sym_session(password, str_key_package);
        
        std::string encrypted_data = out_msg.write(1);
        std::vector<uint8_t> out_vector(encrypted_data.begin(), encrypted_data.end());
        
        return out_vector;
    }
    
    std::string OpenPgpImpl::encrypt_message_aes(const std::string & plain_text,
                                                 const std::string & password) {
        
        PGPMessage encrypted_sym = encrypt_sym(password, plain_text, "", 9, 0, true, nullptr, "");
        std::string encrypt_message = encrypted_sym.write();
        return encrypt_message;
    }
    
    std::string OpenPgpImpl::decrypt_message_aes(const std::string & encrypted_message,
                                                 const std::string & password) {
        
        std::string encrypt_msg = encrypted_message;
        ProtonMail::PMPGPMessage pm_pgp_msg(encrypt_msg, false);
        std::string out_unencrypt_msg = decrypt_sym(pm_pgp_msg, password);
        
        return out_unencrypt_msg;
    }
    std::string OpenPgpImpl::encrypt_mailbox_pwd(const std::string & unencrypted_pwd,
                                                 const std::string & salt) {
        
        PGPMessage encrypted_sym = encrypt_sym(salt, unencrypted_pwd, "", 9, 0, true, nullptr, "");
        std::string encrypt_message = hexlify(encrypted_sym.write(1));
        return encrypt_message;
    }
    
    std::string OpenPgpImpl::decrypt_mailbox_pwd(const std::string & encrypted_pwd,
                                                 const std::string & salt) {
        
        std::string str_encrypted_message = unhexlify(encrypted_pwd);
        ProtonMail::PMPGPMessage pm_pgp_msg(str_encrypted_message, false);
        std::string out_unencrypt_msg = decrypt_sym(pm_pgp_msg, salt);
        return out_unencrypt_msg;
    }
    
    std::string OpenPgpImpl::read_clearsigned_message(const std::string & signed_message) {
        std::string signed_copy = signed_message;
        PGPCleartextSignature signature;
        signature.read(signed_copy);
        return signature.get_message();
    }
    
    int32_t OpenPgpImpl::throw_an_exception() {
        throw ExampleException();
    }
    
    std::string OpenPgpImpl::encrypt_hash_cbc(const std::string & plain_text,
                                              const std::string & password) {
        return "";
    }
    
    std::string OpenPgpImpl::decrypt_hash_cbc(const std::string & encrypted_text,
                                              const std::string & password) {
        return "";
    }
    
    //    public static function encrypt_id( $MessageID, $isRandom = false ) {
    //        if ( !ENCRYPT_IDS ) {
    //            return strval($MessageID);
    //        }
    //        if ( !$isRandom && isset( self::$id_to_enc_[$MessageID] ) ) {
    //            return strval(self::$id_to_enc_[$MessageID]);
    //        }
    //        $key1 = pack( "H*", "5f8b0f69c2e711c19f43633f77f70a59a1198fd73b5ce2d53e1ec43b43b37e66" ); // need keep it forever
    //        $key2 = pack( "H*", "4b6b0acf4524565b756530b0383de0b8a801b79bf242ccfeab1906e8520a63fd" ); // need keep it forever
    //        $key3 = pack( "H*", "001190d069249177ce51ee891b9c4cea52d0323ca5f90ec18d23273f22205a83" );
    //        $text = $MessageID;
    //        $block_size = mcrypt_get_block_size( MCRYPT_RIJNDAEL_128, MCRYPT_MODE_CBC );
    //        $pad = $block_size - ( strlen( $MessageID ) % $block_size );
    //        $text .= str_repeat( chr( $pad ), $pad );
    //        $iv_size = mcrypt_get_iv_size( MCRYPT_RIJNDAEL_128, MCRYPT_MODE_CBC );
    //        if ( $isRandom ) {
    //            $iv = mcrypt_create_iv( $iv_size, MCRYPT_DEV_URANDOM );
    //        }
    //        else {
    //            $new_iv = hash_hmac( "sha256", $MessageID , $key3, true );
    //            $iv = substr( $new_iv, 0 , $iv_size );
    //        }
    //        $crypt = mcrypt_encrypt( MCRYPT_RIJNDAEL_128, $key1, $text, MCRYPT_MODE_CBC, $iv );
    //        $h_mac = hash_hmac( "sha256", $iv.$crypt, $key2, true );
    //        $output = base64_encode( $iv . $crypt . $h_mac );
    //        $output = str_replace( array( '/', '+' ), array( '_', '-' ), $output );
    //        //echo bin2hex($iv . $crypt . $h_mac) . "\r\n";
    //        if ( !$isRandom ) {
    //            self::$id_to_enc_[$MessageID] = $output;
    //        }
    //        return strval($output);
    //    }
    //    public static function decrypt_id( $EncMessageID ) {
    //        if ( !ENCRYPT_IDS ) {
    //            return intval($EncMessageID);
    //        }
    //        // Sanitization
    //        if ( strlen( $EncMessageID ) > 200 ) {
    //            return 0;
    //        }
    //        if ( isset( self::$enc_to_id_[$EncMessageID] ) ) {
    //            return intval(self::$enc_to_id_[$EncMessageID]);
    //        }
    //        $key1 = pack( "H*", "5f8b0f69c2e711c19f43633f77f70a59a1198fd73b5ce2d53e1ec43b43b37e66" );
    //        $key2 = pack( "H*", "4b6b0acf4524565b756530b0383de0b8a801b79bf242ccfeab1906e8520a63fd" );
    //        $EncMessageID = str_replace( array( '_', '-' ), array( '/', '+' ), $EncMessageID );
    //        $message = base64_decode( $EncMessageID );
    //        //echo bin2hex($message) . "\r\n";
    //        $iv_size = mcrypt_get_iv_size( MCRYPT_RIJNDAEL_128, MCRYPT_MODE_CBC );
    //        $iv = substr( $message, 0, $iv_size );
    //        $h_mac_size = strlen( hash_hmac( "sha256", "", "", true ) );
    //        $h_mac = substr( $message, - $h_mac_size );
    //        $crypt = substr( $message, $iv_size, -$h_mac_size );
    //        $crypt_h_mac = hash_hmac( "sha256", $iv. $crypt, $key2, true );
    //        if ( !Util::hash_equals( $h_mac, $crypt_h_mac ) )
    //            return 0;
    //        $text = mcrypt_decrypt( MCRYPT_RIJNDAEL_128, $key1, $crypt, MCRYPT_MODE_CBC, $iv );
    //        $pad = ord( $text[strlen( $text )-1] );
    //        $text = substr( $text, 0, -1*$pad );
    //        self::$enc_to_id_[$EncMessageID] = $text;
    //        if ( self::is_int( $text ) ) {
    //            return intval($text);
    //        }
    //        return $text;
    //    }
    
    
    
    /**for signature */
    EncryptSignPackage OpenPgpImpl::encrypt_message_sign_external(const std::string & public_key, const std::string & private_key, const std::string & plain_text, const std::string & passphras) {
        
        
        std::string str_user_public_key = public_key;
        PGPPublicKey pub(str_user_public_key);
        
        std::string unencrypt_msg = plain_text;
        
        std::string str_user_private_key = private_key;
        auto pgp_private_key = std::make_shared<PGPSecretKey>(str_user_private_key);
    
        
        auto c = encrypt(pub,
                         unencrypt_msg,
                         "",
                         9,
                         2,
                         true,
                         pgp_private_key, true, passphras);
        
        
        
//        PGPMessage encrypted_pgp = encrypt_pka(pub, unencrypt_msg);
//        std::string encrypt_message = encrypted_pgp.write();

        return EncryptSignPackage("", "");
    }
    
    DecryptSignVerify OpenPgpImpl::decrypt_message_verify_single_key(const std::string & private_key, const std::string & passphras, const std::string & encrypted, const std::string & signature) {
        std::string str_private_key = private_key;
        PGPSecretKey pgp_private_key(str_private_key);
        std::string encrypt_msg = encrypted;
        ProtonMail::PMPGPMessage pm_pgp_msg(encrypt_msg, false);
        
        auto verifier = pgp_private_key.pubkey();
        bool verify = false;
        std::string plain_text = decrypt_pka(pgp_private_key, pm_pgp_msg, passphras, verify, false, verifier);
        
        return DecryptSignVerify(plain_text, verify);
    }
    
    DecryptSignVerify OpenPgpImpl::decrypt_message_verify(const std::string & passphras, const std::string & encrypted, const std::string & signature) {
        std::string encrypt_msg = encrypted;
        ProtonMail::PMPGPMessage pm_pgp_msg(encrypt_msg, false);

        auto verifier = Secret2PublicKey(m_private_key);
        bool verify = false;
        std::string plain_text = decrypt_pka(*m_private_key, pm_pgp_msg, passphras, verify, false, verifier);
        return DecryptSignVerify(plain_text, verify);
    }
    
    
    std::string OpenPgpImpl::sign_detached(const std::string & private_key, const std::string & plain_text, const std::string & passphras) {
        auto privKeyIn = private_key;
        PGPSecretKey privKey(privKeyIn);

        auto signed_detached = sign_detach(privKey, passphras, plain_text, 2); //sha 1
        
        std::string pgpMsg = signed_detached.write();
        
        return pgpMsg;
    }
    
    bool OpenPgpImpl::sign_detached_verify(const std::string & signature, const std::string & plain_text) {
        std::string detached_sign = signature;
        PGPDetachedSignature sig(detached_sign);
        auto verifier = m_private_key->pub();
        auto check = verify_detachedsig(verifier, plain_text, sig);
        return check;
    }

    bool OpenPgpImpl::sign_detached_verify_single_pub_key(const std::string & public_key, const std::string & signature, const std::string & plain_text) {
        std::string detached_sign = signature;
        PGPDetachedSignature sig(detached_sign);
        
        std::string str_user_public_key = public_key;
        PGPPublicKey pubKey(str_user_public_key);
        
        auto check = verify_detachedsig(pubKey, plain_text, sig);
        return check;
    }
    
    bool OpenPgpImpl::sign_detached_verify_single_binary_pub_key(const std::vector<uint8_t> & public_key, const std::string & signature, const std::string & plain_text) {
        std::string detached_sign = signature;
        PGPDetachedSignature sig(detached_sign);
        
        std::string str_user_public_key(public_key.begin(), public_key.end());
        PGPPublicKey pubKey(str_user_public_key);
        
        auto check = verify_detachedsig(pubKey, plain_text, sig);
        return check;
    }
    
    bool OpenPgpImpl::sign_detached_verify_single_private_key(const std::string & private_key, const std::string & signature, const std::string & plain_text) {
        std::string detached_sign = signature;
        PGPDetachedSignature sig(detached_sign);
        
        std::string str_user_private_key = private_key;
        PGPSecretKey privKey(str_user_private_key);
        
        auto verifier = privKey.pub();
        
        auto check = verify_detachedsig(verifier, plain_text, sig);
        
        return check;
    }
    
    
}
