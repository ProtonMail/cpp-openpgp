#include <openpgp/PGPKey.h>
#include <openpgp/openpgp.h>
#include <openpgp/PGPCleartextSignature.h>
#include <openpgp/PGPMessage.h>
#include <openpgp/encrypt.h>
#include <openpgp/decrypt.h>
#include <bridge/address.hpp>

#include "bridge/open_pgp_key.hpp"
#include "bridge_impl/open_pgp_impl.hpp"
#include "bridge/encrypt_package.hpp"

#include <exception/pgp_exception_define.h>
#include <exception/pgp_exception.h>

#include <utilities/utilities.h>

#include <openpgp/private_key.h>



namespace ProtonMail {
    std::shared_ptr <ProtonMail::OpenPgp> OpenPgp::create_instance() {
        return std::make_shared<OpenPgpImpl>();
    }

    std::shared_ptr <ProtonMail::OpenPgp> OpenPgp::create_instance_with_keys(const Address & address) {
        std::shared_ptr <ProtonMail::OpenPgp> pOpenPGP = std::make_shared<OpenPgpImpl>();
        pOpenPGP->add_address(address);
        return pOpenPGP;
    }

    OpenPgpImpl::OpenPgpImpl() {
        m_private_key = std::make_shared<PGPSecretKey>();
    }
    
    OpenPgpImpl::~OpenPgpImpl() {
        m_private_key.reset();
    }
    
    OpenPgpKey OpenPgpImpl::generate_key(const std::string & user_name, const std::string & domain, const std::string & passphrase) {
        
        pm::pgp::openpgp p;
        
        std::string email = user_name + "@" + domain;
        std::string comments = "create by ios";
        
        std::string priv_key = "";
        std::string pub_key = "";
        p.generate_new_key(2048, passphrase, user_name, email, comments, pub_key, priv_key);
        
        return OpenPgpKey(pub_key, priv_key);
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
    
    void OpenPgpImpl::enable_debug(bool isDebug) {
        
    }
    
    /**check is primary key passphrase ok */
    bool OpenPgpImpl::check_passphrase(const std::string &private_key,
                                       const std::string &passphrase) {
    
        try
        {
            std::string str_private_key = private_key;
            if(m_is_debug_mode)
                std::cout << private_key;
            
            PGPSecretKey privateKey(str_private_key);
            
            return check_private_passphrase(privateKey, passphrase);
        }
        catch (const pm::pgp_exception & pgp_ex)
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
    
    std::string OpenPgpImpl::update_single_passphrase(const std::string & private_key, const std::string & old_passphrase, const std::string & new_passphrase) {
        try
        {
            std::string str_private_key = private_key;
            PGPSecretKey secret_key;
            secret_key.set_is_debug(false);
            secret_key.read(str_private_key);
            
            bool isOk = check_private_passphrase(secret_key, old_passphrase);
            if (!isOk) {
                return "";
            }
            std::string new_key = pm::pgp::update_passphrase(secret_key, old_passphrase, new_passphrase);
            
            return new_key;
        }
        catch (const pm::pgp_exception & pgp_ex)
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
        return "";
    }
    
    /**update the information carried in the packet. //TODO need add more parameters */
    void OpenPgpImpl::update_private_info(const std::string & private_key) {
        
    }

    /**encrypt message */
    std::string OpenPgpImpl::encrypt_message(const std::string &address_id,
                                             const std::string &plan_text) {
        
        std::unordered_map<std::string, Address>::const_iterator got = m_addresses.find (address_id);

        std::string user_pub_key = got->second.keys[0].public_key;
        PGPPublicKey pub(user_pub_key);
        
        std::string unencrypt_msg = plan_text;
        
        PGPMessage encrypted_pgp = encrypt_pka(pub, unencrypt_msg);
        std::string encrypt_message = encrypted_pgp.write();
        
        return encrypt_message;
    }
    
    std::string OpenPgpImpl::encrypt_message_single_key(const std::string & public_key, const std::string & plain_text) {
        std::string str_user_public_key = public_key;
        PGPPublicKey pub(str_user_public_key);
        
        std::string unencrypt_msg = plain_text;
        
        PGPMessage encrypted_pgp = encrypt_pka(pub, unencrypt_msg);
        std::string encrypt_message = encrypted_pgp.write();
        
        return encrypt_message;
    }
    
    
    std::string OpenPgpImpl::decrypt_message(const std::string &encrypt_text,
                                             const std::string &passphras) {
        std::string encrypt_msg = encrypt_text;
        pm::PMPGPMessage pm_pgp_msg(encrypt_msg, false);
        
        std::string plain_text = decrypt_pka(*m_private_key, pm_pgp_msg, passphras, false);
    
        return plain_text;
    }
    
    std::string OpenPgpImpl::decrypt_message_single_key(const std::string & encrypt_text, const std::string & private_key, const std::string & passphras) {
        std::string str_private_key = private_key;
        
        PGPSecretKey pgp_private_key(str_private_key);
        
        std::string encrypt_msg = encrypt_text;
        pm::PMPGPMessage pm_pgp_msg(encrypt_msg, false);
        
        std::string plain_text = decrypt_pka(pgp_private_key, pm_pgp_msg, passphras, false);
        
        return plain_text;
    }

    EncryptPackage OpenPgpImpl::encrypt_attachment(const std::string & address_id, const std::vector<uint8_t> & unencrypt_data, const std::string & file_name) {
        
        //NSData to string  need error handling here
        std::string unencrypt_msg(unencrypt_data.begin(), unencrypt_data.end());
        
        // here need add more check
        std::unordered_map<std::string, Address>::const_iterator got = m_addresses.find (address_id);
        
        std::string user_pub_key = got->second.keys[0].public_key;
        
        PGPPublicKey pub(user_pub_key);
        
        PGPMessage encrypted_pgp = encrypt_pka(pub, unencrypt_msg, file_name);
        
        std::string keyPackage = encrypted_pgp.write(1, 0, 1);
        std::string dataPackage = encrypted_pgp.write(1, 0, 18);

        return EncryptPackage(std::vector<uint8_t>(keyPackage.begin(), keyPackage.end()), std::vector<uint8_t>(dataPackage.begin(), dataPackage.end()));
    }
    
    EncryptPackage OpenPgpImpl::encrypt_attachment_single_key(const std::string & public_key, const std::vector<uint8_t> & unencrypt_data, const std::string & file_name) {
        std::string str_public_key = public_key;
        std::string unencrypt_msg(unencrypt_data.begin(), unencrypt_data.end());
        
        PGPPublicKey pub(str_public_key);
        
        PGPMessage encrypted_pgp = encrypt_pka(pub, unencrypt_msg, file_name);
        
        std::string keyPackage = encrypted_pgp.write(1, 0, 1);
        std::string dataPackage = encrypted_pgp.write(1, 0, 18);
        
        return EncryptPackage(std::vector<uint8_t>(keyPackage.begin(), keyPackage.end()), std::vector<uint8_t>(dataPackage.begin(), dataPackage.end()));
    }

    std::vector<uint8_t> OpenPgpImpl::decrypt_attachment(const std::vector<uint8_t> & key, const std::vector<uint8_t> & data, const std::string & passphras) {
        
        std::string str_key_package(key.begin(), key.end());
        std::string str_data_package (data.begin(), data.end());
        
        pm::PMPGPMessage pm_pgp_msg(str_key_package, true);
        pm_pgp_msg.append(str_data_package, true);
        
        std::string test_plain_txt = decrypt_pka(*m_private_key, pm_pgp_msg, passphras, false);
        
        std::vector<uint8_t> out_vector(test_plain_txt.begin(), test_plain_txt.end());
        return out_vector;
    }
    
    
    std::vector<uint8_t> OpenPgpImpl::decrypt_attachment_single_key(const std::vector<uint8_t> & key, const std::vector<uint8_t> & data, const std::string & private_key, const std::string & passphras) {
        
        std::string str_key_package(key.begin(), key.end());
        std::string str_data_package (data.begin(), data.end());
        std::string str_private_key = private_key;
        
        PGPSecretKey pgp_private_key(str_private_key);
        
        pm::PMPGPMessage pm_pgp_msg(str_key_package, true);
        pm_pgp_msg.append(str_data_package, true);
        
        std::string test_plain_txt = decrypt_pka(pgp_private_key, pm_pgp_msg, passphras, false);
        
        std::vector<uint8_t> out_vector(test_plain_txt.begin(), test_plain_txt.end());
        return out_vector;
    }

    /**TODO : not done and not inuse */
    std::vector<uint8_t> OpenPgpImpl::decrypt_attachment_with_password(const std::vector<uint8_t> & key, const std::vector<uint8_t> & data, const std::string & password){
        std::string str_key_package(key.begin(), key.end());
        std::string str_data_package(data.begin(), data.end());
        
        pm::PMPGPMessage pm_pgp_msg(str_key_package, true);
        pm_pgp_msg.append(str_data_package, true);
        
        std::string test_plain_txt = decrypt_sym(pm_pgp_msg, password);
        
        std::vector<uint8_t> out_vector(test_plain_txt.begin(), test_plain_txt.end());
        return out_vector;
    }

    std::vector<uint8_t> OpenPgpImpl::get_public_key_session_key(const std::vector<uint8_t> & keyPackage, const std::string & passphrase)
    {
        std::string str_key_package(keyPackage.begin(), keyPackage.end());
        pm::PMPGPMessage pm_pgp_msg(str_key_package, true);
        
        std::string sessionKey = decrypt_pka_only_session(*m_private_key, pm_pgp_msg, passphrase);
        
        std::vector<uint8_t> out_vector(sessionKey.begin(), sessionKey.end());
        return out_vector;
    }
    
    std::vector<uint8_t> OpenPgpImpl::get_public_key_session_key_single_key(const std::vector<uint8_t> & keyPackage, const std::string & privateKey, const std::string & passphrase) {
        std::string str_private_key = privateKey;
        
        PGPSecretKey pgp_private_key(str_private_key);
        
        std::string str_key_package(keyPackage.begin(), keyPackage.end());
        pm::PMPGPMessage pm_pgp_msg(str_key_package, true);
        
        std::string sessionKey = decrypt_pka_only_session(pgp_private_key, pm_pgp_msg, passphrase);
        
        std::vector<uint8_t> out_vector(sessionKey.begin(), sessionKey.end());
        return out_vector;
    }

    std::vector<uint8_t> OpenPgpImpl::get_symmetric_session_key(const std::vector<uint8_t> & keyPackage, const std::string & password){
        
        std::string str_key_package(keyPackage.begin(), keyPackage.end());
        pm::PMPGPMessage pm_pgp_msg(str_key_package, true);
        std::string sessionkey = decrypt_pka_only_sym_session(pm_pgp_msg, password);

        std::vector<uint8_t> out_vector(sessionkey.begin(), sessionkey.end());
        
        return out_vector;
    }

    std::vector<uint8_t> OpenPgpImpl::get_new_public_key_package(const std::vector<uint8_t> & session, const std::string & publicKey) {
        std::string str_sessionKey (session.begin(), session.end());
        
        std::string user_pub_key = publicKey;
        
        PGPPublicKey pub(user_pub_key);
        
        PGPMessage out_msg = encrypt_pka_only_session(pub, str_sessionKey);
        
        std::string encrypted_data = out_msg.write(1);
        
        std::vector<uint8_t> out_vector(encrypted_data.begin(), encrypted_data.end());
        
        return out_vector;
    }

    std::vector<uint8_t> OpenPgpImpl::get_new_symmetric_key_package(const std::vector<uint8_t> & session, const std::string & password) {
        std::string str_key_package(session.begin(), session.end());
        
        PGPMessage out_msg = encrypt_pka_only_sym_session(password, str_key_package);
        
        std::string encrypted_data = out_msg.write(1);
        std::vector<uint8_t> out_vector(encrypted_data.begin(), encrypted_data.end());
        
        return out_vector;
    }
    
    std::string OpenPgpImpl::encrypt_message_aes(const std::string & plain_text, const std::string & password) {
        PGPMessage encrypted_sym = encrypt_sym(password, plain_text, "", 9, 0, true, nullptr, "");
        std::string encrypt_message = encrypted_sym.write();
        return encrypt_message;
    }

    std::string OpenPgpImpl::decrypt_message_aes(const std::string & encrypted_message, const std::string & password) {
        std::string encrypt_msg = encrypted_message;
        pm::PMPGPMessage pm_pgp_msg(encrypt_msg, false);
        std::string out_unencrypt_msg = decrypt_sym(pm_pgp_msg, password);
        
        return out_unencrypt_msg;
    }
    std::string OpenPgpImpl::encrypt_mailbox_pwd(const std::string & unencrypted_pwd, const std::string & salt) {
        PGPMessage encrypted_sym = encrypt_sym(salt, unencrypted_pwd, "", 9, 0, true, nullptr, "");
        std::string encrypt_message = hexlify(encrypted_sym.write(1));
        return encrypt_message;
    }
    
    std::string OpenPgpImpl::decrypt_mailbox_pwd(const std::string & encrypted_pwd, const std::string & salt) {
        std::string str_encrypted_message = unhexlify(encrypted_pwd);
        pm::PMPGPMessage pm_pgp_msg(str_encrypted_message, false);
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
    
}
