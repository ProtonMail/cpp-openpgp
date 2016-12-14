package com.protonmail.ch.openpgp;

import android.test.AndroidTestCase;
import android.util.Log;

import java.util.ArrayList;

import ch.protonmail.android.utils.AppUtil;
import ch.protonmail.android.utils.nativelib.*;


/**
 * Created by Yanfeng on 9/16/15.
 */
public class OpenPGPMediumAttachmentTest extends AndroidTestCase {

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

    public void test_encryptMediumAttachment() {
        byte[] data_in = AppUtil.readBytes(getContext(), R.raw.testpdf);

        OpenPgp openPgp = OpenPgp.createInstance();

        ArrayList<OpenPgpKey> keys = new ArrayList<>();
        keys.add(new OpenPgpKey(publicKey, privateKey));
        openPgp.addAddress(new Address("1", "feng@protonmail.ch", keys));

        for( int i = 0; i< 30; i++) {

            EncryptPackage encryptPackage = openPgp.encryptAttachment("1", data_in, "testpdf.txt");
            assertNotNull(encryptPackage);
            assertNotNull(encryptPackage.getKeyPackage());
            assertNotNull(encryptPackage.getDataPackage());

            byte[] new_out_data = openPgp.decryptAttachment(encryptPackage.getKeyPackage(), encryptPackage.getDataPackage(), privatePassphrase);
            assertNotNull("Count" + i, new_out_data);
            assertTrue("Count" + i, new_out_data.length > 0);

            byte[] sessionBytes = openPgp.getPublicKeySessionKey(encryptPackage.getKeyPackage(), privatePassphrase);
            assertNotNull("Count" + i, sessionBytes);
            assertTrue(sessionBytes.length > 0);

            byte[] newKeyPackage = openPgp.getNewPublicKeyPackage(sessionBytes, publicKey);
            assertNotNull("Count" + i, newKeyPackage);
            assertTrue(newKeyPackage.length > 0);

            byte[] out = openPgp.decryptAttachment(newKeyPackage, encryptPackage.getDataPackage(), privatePassphrase);
            assertNotNull("Count" + i, out);
            assertTrue(out.length > 0);

            byte[] newSymKeyPackage = openPgp.getNewSymmetricKeyPackage(sessionBytes, privatePassphrase);
            assertNotNull("Count" + i, newSymKeyPackage);
            assertTrue(newSymKeyPackage.length > 0);

            byte[] out1 = openPgp.decryptAttachmentWithPassword(newSymKeyPackage,encryptPackage.getDataPackage(),privatePassphrase);
            assertNotNull(out1);
            assertTrue(out1.length > 0);

            Log.d("UnitTest", "Count: " + i);
        }
    }

}
