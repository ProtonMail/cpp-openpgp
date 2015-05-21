package ch.protonmail.android.utils;

/**
 * Created by Yanfeng on 4/8/15.
 */
public class OpenPGP {

    public native int SetupKeys(String priv_key, String pub_key, String passphrase);

    public native int test1(int x, int y);
    public native String test2(int x);

    public native String EncryptMessage(String unencrypted_message, String pub_key);
    public native String DecryptMessage(String encrypted_message, String priv_key, String passphrase);

    public native String EncryptMessageAES(String unencrypted_message, String password);
    public native String DecryptMessageAES(String encrypted_message, String password);


    public native String EncryptMailboxPWD(String unencrypted_pwd, String salt);
    public native String DecryptMailboxPWD(String encrypted_pwd, String salt);

}

