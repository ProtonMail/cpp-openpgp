package com.protonmail.ch.openpgp;

import android.test.AndroidTestCase;
import android.util.Log;

import org.json.JSONArray;
import org.json.JSONException;
import org.json.JSONObject;

import java.util.ArrayList;

import ch.protonmail.android.utils.AppUtil;


/**
 * Created by Yanfeng on 9/16/15.
 */
public class OpenPGPMultipleKeyTest extends AndroidTestCase {

    static {
        try {
            System.loadLibrary("gnustl_shared");
            System.loadLibrary("openpgp");
            System.loadLibrary("openpgp_android");
        } catch (Exception ex) {
            ex.printStackTrace();
        }
    }

    private String jsonString = "";
    private String testMessage = "";

    private static final String privatePassphrase = "123";

    @Override
    protected void setUp() throws Exception {
        super.setUp();
        jsonString = AppUtil.readTxt(getContext(), R.raw.feng_mulitiple_keys);
        testMessage = AppUtil.readTxt(getContext(), R.raw.feng_mulitiple_test_message);
        assertTrue("jsonString is empty", !jsonString.isEmpty());
        assertTrue("testMessage is empty", !testMessage.isEmpty());
    }

//    public void test_encryptMessage() throws JSONException {
//       // OpenPGPKeys
//        OpenPGP pgp = new OpenPGP();
//        String jsonString = AppUtil.readTxt(getContext(), R.raw.feng_mulitiple_keys);
//        try {
//            JSONObject pages = new JSONObject(jsonString);
//            JSONObject user = pages.getJSONObject("User");
//            JSONArray addresses = user.getJSONArray("Addresses");
//            for (int i = 0; i < addresses.length(); ++i) {
//                JSONObject address = addresses.getJSONObject(i);
//                String addressID = address.getString("ID");
//                ArrayList<OpenPGPKey> address_keys = new ArrayList<OpenPGPKey>();
//                JSONArray keys = address.getJSONArray("Keys");
//                for (int j = 0; j < keys.length(); ++j) {
//                    JSONObject key = keys.getJSONObject(j);
//                    OpenPGPKey keyo = new OpenPGPKey();
//                    keyo.PublicKey = key.getString("PublicKey");
//                    keyo.PrivateKey = key.getString("PrivateKey");
//                    address_keys.add(keyo);
//                }
//                pgp.AddKeys(addressID, address_keys);
//            }
//
//            Log.d("", "");
//
//        } catch (JSONException e) {
//            e.printStackTrace();
//        }
//
//        for( int i = 0; i< 200; i++) {
//            String tmp_out = pgp.DecryptMessage(testMessage, "123");
//            assertNotNull("decryptedText can't null", tmp_out);
//            assertTrue("decryptedText can't empty", !tmp_out.isEmpty());
//        }
//    }
}
