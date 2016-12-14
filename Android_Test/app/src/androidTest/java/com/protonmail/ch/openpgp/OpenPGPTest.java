package com.protonmail.ch.openpgp;

import android.test.AndroidTestCase;
import android.util.Log;

import java.util.ArrayList;

import ch.protonmail.android.utils.AppUtil;
import ch.protonmail.android.utils.nativelib.*;


/**
 * Created by Yanfeng on 9/16/15.
 */
public class OpenPGPTest extends AndroidTestCase {

    static {
        try {
            System.loadLibrary("gnustl_shared");
            System.loadLibrary("openpgp");
            System.loadLibrary("openpgp_android");
        } catch (Exception ex) {
            ex.printStackTrace();
        }
    }

    private String privateKey = "";
    private String publicKey = "";

    private static final String privatePassphrase = "123";

    @Override
    protected void setUp() throws Exception {
        super.setUp();
        privateKey = AppUtil.readTxt(getContext(), R.raw.privatekey);
        publicKey = AppUtil.readTxt(getContext(), R.raw.publickey);
        assertTrue("private is empty", !privateKey.isEmpty());
        assertTrue("public is empty", !publicKey.isEmpty());
    }

    public void test_generateNewKey() {
        OpenPgp openPgp = OpenPgp.createInstance();

        OpenPgpKey newKey = openPgp.generateKey("feng", "protonmail.com", "123123", 4096);
        assertNotNull(newKey);
        assertNotNull(newKey.getPrivateKey());
        assertNotNull(newKey.getPublicKey());

        boolean check1 = openPgp.checkPassphrase(newKey.getPrivateKey(), "");
        assertTrue("here should be a wrong pwd", check1 == false);
        boolean check2 = openPgp.checkPassphrase(newKey.getPrivateKey(), "123");
        assertTrue("here should be a wrong pwd", check2 == false);
        boolean check3 = openPgp.checkPassphrase(newKey.getPrivateKey(), "123123"); //ok
        assertTrue("here should be a right pwd", check3 == true);

        String newKey1 = openPgp.updateSinglePassphrase(newKey.getPrivateKey(), "", "123");
        assertTrue("here should be a wrong pwd and return a null new key", (newKey1 == null || newKey1.isEmpty()));
        String newKey2 = openPgp.updateSinglePassphrase(newKey.getPrivateKey(), "123", "123");
        assertTrue("here should be a wrong pwd and return a null new key", (newKey2 == null || newKey2.isEmpty()));
        String updatedPrivateKey = openPgp.updateSinglePassphrase(newKey.getPrivateKey(), "123123", "123"); //ok
        assertTrue("here should be a right pwd and return not null value", updatedPrivateKey != null);
        assertTrue("here should be a right pwd and return not empty value", !updatedPrivateKey.isEmpty());

        boolean check4 = openPgp.checkPassphrase(updatedPrivateKey, "");
        assertTrue("here should be a wrong pwd", check4 == false);
        boolean check5 = openPgp.checkPassphrase(updatedPrivateKey, "123"); //ok
        assertTrue("here should be a right pwd", check5 == true);
        boolean check6 = openPgp.checkPassphrase(updatedPrivateKey, "123123");
        assertTrue("here should be a wrong pwd", check6 == false);
    }

    public void test_checkPassword() {
        OpenPgp openPgp = OpenPgp.createInstance();

        boolean isOk = openPgp.checkPassphrase(privateKey, privatePassphrase);
        assertTrue("The password not match", isOk == true);
        boolean check4 = openPgp.checkPassphrase(privateKey, "");
        assertTrue("The password not match", check4 == false);
        boolean check5 = openPgp.checkPassphrase(privateKey, privatePassphrase);
        assertTrue("The password not match", check5 == true);
        boolean check6 = openPgp.checkPassphrase(privateKey, "123123");
        assertTrue("The password not match", check6 == false);
    }

    public void test_encryptMessage() {
        String cleartext = AppUtil.readTxt(getContext(), R.raw.test_plain_message);
        assertNotNull("cleartext can't null", cleartext);
        assertTrue("cleartext can't empty", !cleartext.isEmpty());

        OpenPgp openPgp = OpenPgp.createInstance();
        ArrayList<OpenPgpKey> keys = new ArrayList<>();
        keys.add(new OpenPgpKey("", publicKey, privateKey, "",false));
        openPgp.addAddress(new Address("1", "feng@protonmail.ch", keys));

        for( int i = 0; i< 200; i++) {
            String encryptedText = openPgp.encryptMessage("1", cleartext);
            assertNotNull("encryptedText can't null", encryptedText);
            assertTrue("cleartext can't empty", !encryptedText.isEmpty());

            String decryptedText = openPgp.decryptMessage(encryptedText, privatePassphrase);
            assertNotNull("decryptedText can't null", encryptedText);
            assertTrue("decryptedText can't empty", !encryptedText.isEmpty());

            assertTrue("decryptedText should be same as cleartext", decryptedText.equalsIgnoreCase(cleartext));
        }
    }

    public void test_encryptMessageAES() {
        String original_text = "<div>lajflkjasklfjlksdfkl</div><div><br></div><div>Sent from iPhone <a href=\"https://protonmail.ch\">ProtonMail</a>, encrypted email based in Switzerland.<br></div>";
        String test_aes_str = "-----BEGIN PGP MESSAGE-----\nVersion: OpenPGP.js v0.10.1-IE\nComment: http://openpgpjs.org\n\nww0ECQMIina34sp8Nlpg0sAbAc/x6pR8h57OJv9pklLuEc/aH5lFT9OpWS+N\n7oPaJCGK1f3aQV7g5V5INlUvwICeDiSkDMo+hHGtFgDFEwgNiMDc7wAtod1U\nZ5PTHegr8KWWmBiDIYuPVFJH8mALVcQen9MI1xFSYO8RvSxM/P6dJPzrVZQK\noIRW98dxMjJqMWW9HgqWCej6TRDua65r/X7Ucco9tWpwzmQCnvJLqpcYYrEk\ngcGyXsp3RvISG6pWh8ZFemeO6yoqnphYmcAa/i4h4CiMqKDDJuOg4UdpW46U\nGoNSV+C4hz5ymRDj\n=hUe3\n-----END PGP MESSAGE-----";

        OpenPgp openPgp = OpenPgp.createInstance();

        for( int i = 0; i< 200; i++) {

            String plain_text = openPgp.decryptMessageAes(test_aes_str, privatePassphrase);
            assertTrue("plain_text should be same as original_text", plain_text.equalsIgnoreCase(original_text));

            String new_enc_msg = openPgp.encryptMessageAes(original_text, privatePassphrase);
            assertTrue("decryptedText should be same as cleartext", new_enc_msg != null);

            String new_dec_msg = openPgp.decryptMessageAes(new_enc_msg, privatePassphrase);
            assertTrue("new_dec_msg should not be null", new_dec_msg != null);
            assertTrue("new_dec_msg should be same as new_dec_msg", new_dec_msg.equalsIgnoreCase(original_text));
        }
    }

    public void test_badMsg_emojiOne() {
        String badEncryptedMsg = AppUtil.readTxt(getContext(), R.raw.feng_bad_msg_emoji_1);

        OpenPgp openPgp = OpenPgp.createInstance();
        ArrayList<OpenPgpKey> keys = new ArrayList<>();
        keys.add(new OpenPgpKey("", publicKey, privateKey, "",false));
        openPgp.addAddress(new Address("1", "feng@protonmail.ch", keys));

        for (int i = 0; i < 200; i++) {
            String out = openPgp.decryptMessage(badEncryptedMsg, privatePassphrase);
            assertNotNull(out);
            Log.d("Unit Testing", "count:" + i + " - " + out);
        }
    }
}
