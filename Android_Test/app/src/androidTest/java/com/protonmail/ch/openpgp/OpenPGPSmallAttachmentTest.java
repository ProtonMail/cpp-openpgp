package com.protonmail.ch.openpgp;

import android.test.AndroidTestCase;
import android.util.Log;

import java.util.ArrayList;

import ch.protonmail.android.utils.Address;
import ch.protonmail.android.utils.AppUtil;
import ch.protonmail.android.utils.EncryptPackage;
import ch.protonmail.android.utils.OpenPgp;
import ch.protonmail.android.utils.OpenPgpKey;

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



    public void test_badCase() {
        String test_string = "this is a test attachment1111111";
        String keyString = "c1c04c038eac9f302e252bc3010800bba534aedfeb1f72ab4930e2f1f508c96a0cc44ce8fc975f4f185f38d3b712dd7a0f124e6447d7d300752b11db8717385d560867e5bf6b68592d7b4cacca1f633083928dbf7d93ea7eebb993949ddefe737e5c365cd539afece7a5a27af182b229ca18e522c1d8d16d241d91bb38c847250c134d6bddd28b8c8db971015fc11c18f46e74c0e7bed6ac5ace05e445eea3660518b9c781fb24c312d3eac7c96761b4579de0d8da8a6363f1a53716a6aaeeca535026c1552362d90d80c977414a257a0d4b8172194557018b1bdd5b20ae715497487689e53761366d92607343b379246487759357b9b4792fd85fc2ce18477de75a3e4837f78cda1c0cf4b8299f92";
        byte[] key = AppUtil.hexStringToByteArray(keyString);

        String dataString = "d259018f44a04a1b5bee3d567b197278ce4d94d5b3c958e422150f7edb481bd648ee1b08d7718283866eeb1dc7028c1cd1b315adf5354b5e98be7ba8a9e5acd454f004462ed543136a8506e0a9382ff9652bfc7c186288cce0b420";
        byte[] data = AppUtil.hexStringToByteArray(dataString);

        OpenPgp openPgp = OpenPgp.createInstance();

        ArrayList<OpenPgpKey> keys = new ArrayList<>();
        keys.add(new OpenPgpKey(publicKey, privateKey));
        openPgp.addAddress(new Address("1", "feng@protonmail.ch", keys));

        byte[] new_out_data = openPgp.decryptAttachment(key, data, privatePassphrase);

        assertNotNull("DecryptAttachment out data", new_out_data);
        assertTrue(new_out_data.length > 0);
        String test_out_msg = new String(new_out_data);
        assertTrue("test_out_msg should be same as test_string", test_out_msg.equalsIgnoreCase(test_string));

    }

    public void test_encryptSmallAttachment() {

        String test_string = "this is a test attachment1111111";
        byte[] data_in = test_string.getBytes();

        OpenPgp openPgp = OpenPgp.createInstance();

        ArrayList<OpenPgpKey> keys = new ArrayList<>();
        keys.add(new OpenPgpKey(publicKey, privateKey));
        openPgp.addAddress(new Address("1", "feng@protonmail.ch", keys));

        for( int i = 0; i< 200; i++) {

            EncryptPackage encryptPackage = openPgp.encryptAttachment("1", data_in, "test.txt");
            assertNotNull(encryptPackage);
            assertNotNull(encryptPackage.getKeyPackage());
            assertNotNull(encryptPackage.getDataPackage());

            Log.d("Start 1", "Count: " + i);
            Log.d("BadPackage", "BadKey1: " + AppUtil.byteArrayToHexString(encryptPackage.getKeyPackage()));
            Log.d("BadPackage", "BadData1: " + AppUtil.byteArrayToHexString(encryptPackage.getDataPackage()));
            byte[] new_out_data = openPgp.decryptAttachment(encryptPackage.getKeyPackage(), encryptPackage.getDataPackage(), privatePassphrase);

            assertNotNull("DecryptAttachment 1 Count" + i, new_out_data);
            assertTrue(new_out_data.length > 0);
            String test_out_msg = new String(new_out_data);
            assertTrue("test_out_msg should be same as test_string", test_out_msg.equalsIgnoreCase(test_string));

            byte[] sessionBytes = openPgp.getPublicKeySessionKey(encryptPackage.getKeyPackage(), privateKey, privatePassphrase);
            assertNotNull(sessionBytes);
            assertTrue(sessionBytes.length > 0);

            byte[] newKeyPackage = openPgp.getNewPublicKeyPackage(sessionBytes, publicKey);
            assertNotNull(newKeyPackage);
            assertTrue(newKeyPackage.length > 0);

            Log.d("Start 2", "Count: " + i);
            Log.d("BadPackage", "BadKey2: " + AppUtil.byteArrayToHexString(newKeyPackage));
            byte[] out = openPgp.decryptAttachment(newKeyPackage, encryptPackage.getDataPackage(),privatePassphrase);

            assertNotNull("DecryptAttachment 2 Count" + i, out);
            assertTrue(out.length > 0);
            String test_out_msg1 = new String(out);
            assertTrue("test_out_msg1 should be same as test_string", test_out_msg1.equalsIgnoreCase(test_string));

            byte[] newSymKeyPackage = openPgp.getNewSymmetricKeyPackage(sessionBytes, privatePassphrase);
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
