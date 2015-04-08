#include "StdAfx.h"
#include "openpgp_wrapper.h"
#include <stdio.h>
#include <stdlib.h>


#include <openpgp/openpgp.h>
#include <openpgp/PMPGPMessage.h>
#include <utilities/utility.h>
#include <openpgp/private_key.h>
#include <openpgp/encrypt.h>
#include <openpgp/decrypt.h>

extern "C" {

JNIEXPORT jint JNICALL
Java_ch_protonmail_android_utils_OpenPGP_test1(JNIEnv* env, jobject o, jint x, jint y)
{
	return 100000;
}
//

JNIEXPORT jstring JNICALL
Java_ch_protonmail_android_utils_OpenPGP_test2(JNIEnv* env, jobject o, jint x)
{
	const std::string str_test = "This is a hello word from native through jni";
	jstring jsRet = 0;


	if (!str_test.empty())
	{
		jsRet = (env)->NewStringUTF((const char*) str_test.c_str());
	}
	return jsRet;
}


// openpgp functions

JNIEXPORT jint JNICALL
Java_ch_protonmail_android_utils_OpenPGP_SetupKeys(JNIEnv* env, jobject o, jstring priv_key, jstring pub_key, jstring passphrase)
{
    try
    {
		std::string str_priv_key = (*env).GetStringUTFChars(priv_key, 0);
		std::string str_pub_key = (*env).GetStringUTFChars(pub_key, 0);
		std::string str_passphrase = (*env).GetStringUTFChars(passphrase, 0);

		PGPSecretKey secret_key;
	    secret_key.set_is_debug(false);
		secret_key.read(str_priv_key);

		PGPPublicKey public_key;
	    public_key.set_is_debug(false);
	   	public_key.read(str_pub_key);

	    std::string verifyString = "this is a protonmail encryption test string";
	    LOG_E("Start encrypt check");
	    PGPMessage encrypted = encrypt_pka(public_key, verifyString);
		LOG_E("Start decroypt check");
	    std::string clain_txt = decrypt_pka(secret_key, encrypted, str_passphrase, false);
	    LOG_E("Check pwd");
	    if(verifyString == clain_txt)
	    {
	    	LOG_E("return ok");
	        return 1;
	    }
    }
    catch (const std::runtime_error& error)
    {
    	LOG_E("runtime_error");
    }
    catch (const std::exception& e)
    {
    	LOG_E("exception");
    }
    catch (...)
    {
    	LOG_E("Other exception");
    }

    LOG_E("not ok");
	return 0;
}

JNIEXPORT jstring JNICALL
Java_ch_protonmail_android_utils_OpenPGP_EncryptMessage(JNIEnv* env, jobject o, jstring unencrypt_message, jstring pub_key)
{
	try
    {
    	std::string str_unencrypt_msg = (*env).GetStringUTFChars(unencrypt_message, 0);
		std::string str_pub_key = (*env).GetStringUTFChars(pub_key, 0);

        PGPPublicKey pub(str_pub_key);
        PGPMessage encrypted_pgp = encrypt_pka(pub, str_unencrypt_msg);
        std::string encrypt_message = encrypted_pgp.write();

        jstring jsRet = 0;
		if (!encrypt_message.empty())
		{
			jsRet = (env)->NewStringUTF((const char*) encrypt_message.c_str());
		}
		return jsRet;
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
	return 0;
}

JNIEXPORT jstring JNICALL
Java_ch_protonmail_android_utils_OpenPGP_DecryptMessage(JNIEnv* env, jobject o, jstring encrypted_message, jstring priv_key, jstring passphrase)
{
	try
    {
    	std::string str_encrypted_msg = (*env).GetStringUTFChars(encrypted_message, 0);
		std::string str_priv_key = (*env).GetStringUTFChars(priv_key, 0);
		std::string str_passphrase = (*env).GetStringUTFChars(passphrase, 0);

        pm::PMPGPMessage pm_pgp_msg(str_encrypted_msg);

        PGPSecretKey secret_key;
	    secret_key.set_is_debug(false);
		secret_key.read(str_priv_key);

        std::string test_plain_txt = decrypt_pka(secret_key, pm_pgp_msg, str_passphrase, false);

        jstring jsRet = 0;
		if (!test_plain_txt.empty())
		{
			jsRet = (env)->NewStringUTF((const char*) test_plain_txt.c_str());
		}
		return jsRet;
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
    return 0;
}

JNIEXPORT jstring JNICALL
Java_ch_protonmail_android_utils_OpenPGP_EncryptMessageAES(JNIEnv* env, jobject o, jstring unencrypt_message, jstring password)
{
	try
    {
        std::string str_unencrypt_message = (*env).GetStringUTFChars(unencrypt_message, 0);
		std::string str_password = (*env).GetStringUTFChars(password, 0);

        PGPMessage encrypted_sym = encrypt_sym(str_password, str_unencrypt_message, "", 9, 0, true, nullptr, "");
        std::string encrypt_message = encrypted_sym.write();

        jstring jsRet = 0;
		if (!encrypt_message.empty())
		{
			jsRet = (env)->NewStringUTF((const char*) encrypt_message.c_str());
		}
		return jsRet;
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
	return 0;
}
JNIEXPORT jstring JNICALL
Java_ch_protonmail_android_utils_OpenPGP_DecryptMessageAES(JNIEnv* env, jobject o, jstring encrypted_message, jstring password)
{
	try
    {
        std::string str_encrypted_message = (*env).GetStringUTFChars(encrypted_message, 0);
		std::string str_password = (*env).GetStringUTFChars(password, 0);

        pm::PMPGPMessage pm_pgp_msg(str_encrypted_message);
        std::string out_unencrypt_msg = decrypt_sym(pm_pgp_msg, str_password);

        jstring jsRet = 0;
		if (!out_unencrypt_msg.empty())
		{
			jsRet = (env)->NewStringUTF((const char*) out_unencrypt_msg.c_str());
		}
		return jsRet;
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
    return 0;
}

}