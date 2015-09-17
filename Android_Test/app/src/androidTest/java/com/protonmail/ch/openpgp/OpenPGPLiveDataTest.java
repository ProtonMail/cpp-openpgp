package com.protonmail.ch.openpgp;

import android.test.AndroidTestCase;
import android.util.Log;


import ch.protonmail.android.utils.AppUtil;
import ch.protonmail.android.utils.OpenPGP;
import ch.protonmail.android.utils.OpenPGPKey;



/**
 * Created by Yanfeng on 9/16/15.
 */
public class OpenPGPLiveDataTest extends AndroidTestCase {

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
        OpenPGPKey newKey = OpenPGP.GenerateKey("feng", "123123");
        assertNotNull(newKey);
        assertNotNull(newKey.PrivateKey);
        assertNotNull(newKey.PublicKey);
    }

    public void test_checkPassword() {
        int isOk = OpenPGP.CheckPassphrase(privateKey, privatePassphrase);

        assertTrue("The password not match", isOk == 1);
    }

    public void test_badMsg_emojiOne() {
        String badEncryptedMsg = AppUtil.readTxt(getContext(), R.raw.feng_bad_msg_emoji_1);
        for (int i = 0; i < 100; i++) {
            String out = OpenPGP.DecryptMessage(badEncryptedMsg, privateKey, privatePassphrase);
            assertNotNull(out);
            Log.d("Unit Testing", "count:" + i + " - " + out);
        }
    }
}
