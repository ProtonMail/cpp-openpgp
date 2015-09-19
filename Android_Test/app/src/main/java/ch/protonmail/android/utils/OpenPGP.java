package ch.protonmail.android.utils;

/**
 * Created by Yanfeng on 4/8/15.
 */
public class OpenPGP {

    public static final int KEYS_RESULT_OK = 1;

    /**
     * generate a new open pgp key
     * @param user_name user name user pick
     * @param passphrase password to encrypt the private key
     * @return new public key and private key
     */
    public static native OpenPGPKey GenerateKey(String user_name, String passphrase);

    /**
     * check is passphrase correct for the private key
     * @param private_key   user private key
     * @param passphrase    use passphrase
     * @return 1 is ok 0 is incorrect
     */
    public static native int CheckPassphrase(String private_key, String passphrase);

    /**
     *  update user's private key passphrase
     * @param private_key user's private key
     * @param old_passphrase old passphrase
     * @param new_passphrase new passphrase
     * @return new private key, is empty means old passphrase incorrect
     */
    public static native String UpdateKeyPassphrase(String private_key, String old_passphrase, String new_passphrase);

    /**
     * for check is private public key with passphrase correct
     * @param priv_key user's private key
     * @param pub_key user's public key
     * @param passphrase private key passphrase
     * @return if pass correct will return 1 otherwise 0
     */
    public static native int SetupKeys(String priv_key, String pub_key, String passphrase);


    //encrypt decrypt message

    /**
     * this is for encrypt message use public key
     * @param unencrypted_message plain text value
     * @param pub_key user's public key
     * @return encrypted message
     */
    private static native String EncryptMessage(byte[] unencrypted_message, String pub_key);

    /**
     * decrypt encrypt message use private key and passphrase
     * @param encrypted_message encrypted message
     * @param priv_key  user's private key
     * @param passphrase    user's private key passphrase
     * @return decrypted plaint text
     */
    private static native byte[] DecryptMessage(byte[] encrypted_message, String priv_key, String passphrase);

    public static String DecryptMessage(String encrypted_message, String privateKey, String passPhrase) {
        byte[] out = DecryptMessage(encrypted_message.getBytes(), privateKey, passPhrase);
        if (out != null && out.length > 0) {

            return new String(out);
        }
        return "";
    }

    public static String EncryptMessage(String unencrypted_message, String pub_key) {
        return EncryptMessage(unencrypted_message.getBytes(), pub_key);
    }

    /**
     * aes encrypt message use password this is for encrypt outside emails
     * @param unencrypted_message plain text message
     * @param password encrypt password
     * @return encrypted message
     */
    public static native String EncryptMessageAES(String unencrypted_message, String password);

    /**
     * aes decrypt message use for decrypt a outside email, not use on mollie, because we are not opening the outside email yet
     * @param encrypted_message encrypted message
     * @param password aes encrypt password
     * @return decrypted plain text
     */
    public static native String DecryptMessageAES(String encrypted_message, String password);


    //for local pwd encryption

    /**
     * encrypt password use for local cache
     * @param unencrypted_pwd mailbox password
     * @param salt slat value for encrypt pwd
     * @return encrypt pwd
     */
    public static native String EncryptMailboxPWD(String unencrypted_pwd, String salt);
    public static native String DecryptMailboxPWD(String encrypted_pwd, String salt);


    //encrypt decrypt attachments

    /**
     * encrypt attachment
     * @param data attachment bytes
     * @param pub_key user's public key
     * @return package include key&data package binary data
     */
    public static native EncryptPackage EncryptAttachment(byte[] data,  String pub_key, String file_name);

    /**
     * decrypt attachment
     * @param key  key package
     * @param data data package
     * @param priv_key user's private key
     * @param passphrase user's private key passphrase
     * @return decrypted attachment
     */
    public static native DecryptPackage DecryptAttachment(byte[] key, byte[] data,  String priv_key, String passphrase);
    public static native byte[] DecryptAttachmentWithPassword(byte[] key, byte[] data, String password); //TODO : not done and not inuse

    /**
     * get the session key from a public key package
     * @param keyPackage key package
     * @param privateKey user private key
     * @param passphrase private key passphrase
     * @return session key
     */
    public static native byte[] GetPublicKeySessionKey(byte[] keyPackage, String privateKey, String passphrase);

    /**
     * get the session key from a sym key package (not inuse )
     * @param keyPackage
     * @param password
     * @return
     */
    public static native byte[] GetSymmetricSessionKey(byte[] keyPackage, String password);


    /**
     * get a new public key package use session
     * @param session session
     * @param publicKey user public key
     * @return new public key package
     */
    public static native byte[] GetNewPublicKeyPackage(byte[] session, String publicKey);

    /**
     * get new symmetric key package
     * @param session session
     * @param password password
     * @return new symmetric key package
     */
    public static native byte[] GetNewSymmetricKeyPackage(byte[] session, String password);


    /**
     * test functions not in use
     */

    public static native int test1(int x, int y);
    public static native String test2(int x);

}
