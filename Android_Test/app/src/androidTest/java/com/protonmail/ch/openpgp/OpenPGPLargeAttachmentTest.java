package com.protonmail.ch.openpgp;

import android.test.AndroidTestCase;
import android.util.Log;

import ch.protonmail.android.utils.AppUtil;
import ch.protonmail.android.utils.DecryptPackage;
import ch.protonmail.android.utils.EncryptPackage;


/**
 * Created by Yanfeng on 9/16/15.
 */
public class OpenPGPLargeAttachmentTest extends AndroidTestCase {

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

//    public void test_encryptLargeAttachment() {
//        byte[] data_in = AppUtil.readBytes(getContext(), R.raw.large);
//
//        for( int i = 0; i< 1; i++) {
//
//            EncryptPackage encryptPackage = OpenPGP.EncryptAttachment(data_in, publicKey, "large.txt");
//            assertNotNull(encryptPackage);
//            assertNotNull(encryptPackage.KeyPackage);
//            assertNotNull(encryptPackage.DataPackage);
//
//            DecryptPackage new_out_data = OpenPGP.DecryptAttachment(encryptPackage.KeyPackage, encryptPackage.DataPackage, privateKey, privatePassphrase);
//            assertNotNull("Count" + i, new_out_data);
//            assertNotNull("Count" + i, new_out_data.DecryptData);
//            assertTrue("Count" + i, new_out_data.DecryptData.length > 0);
//
//            byte[] sessionBytes = OpenPGP.GetPublicKeySessionKey(encryptPackage.KeyPackage, privateKey, privatePassphrase);
//            assertNotNull("Count" + i, sessionBytes);
//            assertTrue(sessionBytes.length > 0);
//
//            byte[] newKeyPackage = OpenPGP.GetNewPublicKeyPackage(sessionBytes, publicKey);
//            assertNotNull("Count" + i, newKeyPackage);
//            assertTrue(newKeyPackage.length > 0);
//
//            DecryptPackage out = OpenPGP.DecryptAttachment(newKeyPackage, encryptPackage.DataPackage, privateKey, privatePassphrase);
//            assertNotNull("Count" + i, out);
//            assertNotNull("Count" + i, out.DecryptData);
//            assertTrue("Count" + i, out.DecryptData.length > 0);
//
//            byte[] newSymKeyPackage = OpenPGP.GetNewSymmetricKeyPackage(sessionBytes, privatePassphrase);
//            assertNotNull("Count" + i, new_out_data);
//            assertTrue(newSymKeyPackage.length > 0);
//
////            byte[] out1 = OpenPGP.DecryptAttachmentWithPassword(newSymKeyPackage, encryptPackage.DataPackage, privatePassphrase);
////            assertNotNull(out1);
////            assertTrue(out1.length > 0);
//
//            Log.d("UnitTest", "Count: " + i);
//        }
//    }

}
