package com.protonmail.ch.openpgp;

import android.test.AndroidTestCase;
import android.util.Log;

import java.nio.ByteBuffer;

import ch.protonmail.android.utils.AppUtil;
import ch.protonmail.android.utils.DecryptPackage;
import ch.protonmail.android.utils.EncryptPackage;
import ch.protonmail.android.utils.OpenPGP;
import ch.protonmail.android.utils.OpenPGPKey;


/**
 * Created by Yanfeng on 9/16/15.
 */
public class OpenPGPSmallAttachmentTest extends AndroidTestCase {

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




//    public void test_encryptMediumAttachment() {
//        byte[] data_in = AppUtil.readBytes(getContext(), R.raw.testpdf);
//
//        for( int i = 0; i< 10; i++) {
//
//            EncryptPackage encryptPackage = OpenPGP.EncryptAttachment(data_in, publicKey, "testpdf.txt");
//            assertNotNull(encryptPackage);
//            assertNotNull(encryptPackage.KeyPackage);
//            assertNotNull(encryptPackage.DataPackage);
//
//            byte[] new_out_data = OpenPGP.DecryptAttachment(encryptPackage.KeyPackage, encryptPackage.DataPackage, privateKey, privatePassphrase);
//            assertNotNull(new_out_data);
//            assertTrue(new_out_data.length > 0);
//
//            byte[] sessionBytes = OpenPGP.GetPublicKeySessionKey(encryptPackage.KeyPackage, privateKey, privatePassphrase);
//            assertNotNull(sessionBytes);
//            assertTrue(sessionBytes.length > 0);
//
//            byte[] newKeyPackage = OpenPGP.GetNewPublicKeyPackage(sessionBytes, publicKey);
//            assertNotNull(newKeyPackage);
//            assertTrue(newKeyPackage.length > 0);
//
//            byte[] out = OpenPGP.DecryptAttachment(newKeyPackage, encryptPackage.DataPackage, privateKey, privatePassphrase);
//            assertNotNull(out);
//            assertTrue(out.length > 0);
//
//            byte[] newSymKeyPackage = OpenPGP.GetNewSymmetricKeyPackage(sessionBytes, privatePassphrase);
//            assertNotNull(new_out_data);
//            assertTrue(new_out_data.length > 0);
//
////            byte[] out1 = OpenPGP.DecryptAttachmentWithPassword(newSymKeyPackage, encryptPackage.DataPackage, privatePassphrase);
////            assertNotNull(out1);
////            assertTrue(out1.length > 0);
//
//            Log.d("UnitTest", "Count: " + i);
//        }
//    }

    public void test_encryptSmallAttachment() {

        String test_string = "this is a test attachment1111111";
        byte[] data_in = test_string.getBytes();
        for( int i = 0; i< 50; i++) {

            EncryptPackage encryptPackage = OpenPGP.EncryptAttachment(data_in, publicKey, "test.txt");
            assertNotNull(encryptPackage);
            assertNotNull(encryptPackage.KeyPackage);
            assertNotNull(encryptPackage.DataPackage);

            Log.d("Start 1", "Count: " + i);
            DecryptPackage new_out_data = OpenPGP.DecryptAttachment(encryptPackage.KeyPackage, encryptPackage.DataPackage, privateKey, privatePassphrase);
            assertNotNull("DecryptAttachment 1 Count" + i, new_out_data);
            assertTrue(new_out_data.DecryptData.length > 0);
            String test_out_msg = new String(new_out_data.DecryptData);
            assertTrue("test_out_msg should be same as test_string", test_out_msg.equalsIgnoreCase(test_string));

            byte[] sessionBytes = OpenPGP.GetPublicKeySessionKey(encryptPackage.KeyPackage, privateKey, privatePassphrase);
            assertNotNull(sessionBytes);
            assertTrue(sessionBytes.length > 0);

            byte[] newKeyPackage = OpenPGP.GetNewPublicKeyPackage(sessionBytes, publicKey);
            assertNotNull(newKeyPackage);
            assertTrue(newKeyPackage.length > 0);

            Log.d("Start 2", "Count: " + i);
            DecryptPackage out = OpenPGP.DecryptAttachment(newKeyPackage, encryptPackage.DataPackage, privateKey, privatePassphrase);
            assertNotNull("DecryptAttachment 2 Count" + i, out);
            assertTrue(out.DecryptData.length > 0);
            String test_out_msg1 = new String(out.DecryptData);
            assertTrue("test_out_msg1 should be same as test_string", test_out_msg1.equalsIgnoreCase(test_string));

            byte[] newSymKeyPackage = OpenPGP.GetNewSymmetricKeyPackage(sessionBytes, privatePassphrase);
            assertNotNull("Count" + i, newSymKeyPackage);
            assertTrue(newSymKeyPackage.length > 0);

//            byte[] out1 = OpenPGP.DecryptAttachmentWithPassword(newSymKeyPackage, encryptPackage.DataPackage, privatePassphrase);
//            assertNotNull(out1);
//            assertTrue(out1.length > 0);

//            String test_out_msg2 = new String(out1);
//            assertTrue("test_out_msg2 should be same as test_string", test_out_msg2.equalsIgnoreCase(test_string));

            Log.d("SmallAttachment", "Count: " + i);
        }
    }

}
