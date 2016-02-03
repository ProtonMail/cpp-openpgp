package com.protonmail.ch.openpgp;

import android.content.Context;
import android.net.Uri;
import android.support.annotation.NonNull;
import android.support.v7.app.ActionBarActivity;
import android.support.v4.app.Fragment;
import android.os.Bundle;
import android.util.Base64;
import android.util.Log;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.Button;
import android.widget.TextView;

import java.io.ByteArrayOutputStream;
import java.io.File;
import java.io.FileInputStream;
import java.io.IOException;
import java.io.InputStream;

import ch.protonmail.android.utils.EncryptPackage;
import ch.protonmail.android.utils.OpenPgp;
import ch.protonmail.android.utils.OpenPgpKey;

public class MainActivity extends ActionBarActivity {

    private Context mContext;
    String publicKey = "-----BEGIN PGP PUBLIC KEY BLOCK-----\nVersion: OpenPGP.js v0.7.1\nComment: http://openpgpjs.org\n\nxsBNBFSjdRkBB/9slBPGNrHAMbYT71AnxF4a0W/fcrzCP27yd1nte+iUKGyh\nyux3xGQRIHrwB9zyYBPFORXXwaQIA3YDH73YnE0FPfjh+fBWENWXKBkOVx1R\nefPTytGIyATFtLvmN1D65WkvnIfBdcOc7FWj6N4w5yOajpL3u/46Pe73ypic\nhe10XuwO4198q/8YamGpTFgQVj4H7QbtuIxoV+umIAf96p9PCMAxipF+piao\nD8LYWDUCK/wr1tSXIkNKL+ZCyuCYyIAnOli7xgIlKNCWvC8csuJEYcZlmf42\n/iHyrWeusyumLeBPhRABikE2ePSo+XI7LznD/CIrLhEk6RJT31+JR0NlABEB\nAAHNBlVzZXJJRMLAcgQQAQgAJgUCVKN1JAYLCQgHAwIJEH0tU95Lz7QEBBUI\nAgoDFgIBAhsDAh4BAAAXCgf8CsNCB0tKdLrwGe+dDLTGGdgyYr33Jz6GVta6\nJMl4rccf5T8QiRPkOIWITITpi5maxrn1w7yOUI3xkqCLCEO9vqLhIRr1/aBq\nvVUI+0L7goJoVrx6ynSR1KNNHM/hkttA+t1t894qgug6hooUfxtFWU8KesKK\ngdMFOxst3ODTeZxzO6xmiaf9Mof/y1M5y1fsKuUH57AJRzkJYviZmpEWMAxI\nmmiCPv/iMRUeR7hX9+spG2O9A0Ny46g89T59Wkerggu6/ulgX0O6MAhsuBY3\n+10TgajGyub5oJTLKVDY/nlVvmaEA+4IthepIQs+L3380oQz3GEtr/UfB1PB\nD/VfTM7ATQRUo3UkAQf/dcKxn9bt+fDMxuQT6sxSWjX4ptf6W0QbucDA/5Dw\n2vCFvCGakDdsczduFJ23QI7iZHHig5Fyp5M2MV+1DM/EJs9OZxMK6k0I4M4r\niucSf2L2XPv8m2Q5/nn7+gdvH6mO8POsDu766A0fMNhN36eHa5730dahJlIR\nYP+wOunUkQ3wzTPE4MZh878eCvkaeelMTMPNnQu9ONgxVyaO8GG09M0uJCxV\nqQ6PXBMtYSBydrYUscAeHQrreyfECNPobWgXRafTwftk/n9aGIzLViv4zo36\nGwuk7JzC3AF2PANxYus6EACPckwsjpbMVLpIpSvjDGdlYg9BPtNk0Fd4qZt2\nzwARAQABwsBfBBgBCAATBQJUo3UmCRB9LVPeS8+0BAIbDAAAgzcH/1kyh+20\ntcUGMRrT3akfhVv3o4d9C4j0Ja7PQMKwZNiSdFSbQ8ZE9xbR5cKB/Z33emMw\n+54CeJsanj7lOeefRqoHUynpirANguPLmp8SW4Dor4rwSOs4gfO1ttzw7+8M\nIeFG8p8OQ5B+J3+KCUdiuB+6zdxGW3rIfA9OAPYAObQUJ7quS/lmoNrOzKVm\nJWa7x4f9cS2Wls/vt/jeEn2j0x/GqN0KI8P2PjixiBY5Ogf6FRHvWWUD4SYx\n8YHf6rvFXGHW3tdMRRb24miP0UuhbOyUUiQm1xNIe2fJ+IUCD9cumgWbGXof\nGjz3pBuLbZus9/waqlaZWpyEUl5bKsqeifA=\n=LhM4\n-----END PGP PUBLIC KEY BLOCK-----";
    String privateKey = "-----BEGIN PGP PRIVATE KEY BLOCK-----\r\nVersion: OpenPGP.js v0.9.0\r\nComment: http://openpgpjs.org\r\n\r\n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\nPPekG4ttm6z3/BqqVplanIRSXlsqyp6J8A==\r\n=Pyb1\r\n-----END PGP PRIVATE KEY BLOCK-----\r\n";
    static public Uri uriSavedImage;
    static {
        try {
            System.loadLibrary("gnustl_shared");
            System.loadLibrary("openpgp");
            System.loadLibrary("openpgp_android");
        } catch (Exception ex) {
            ex.printStackTrace();
        }
    }

    private static final int BUFFER_SIZE = 4096;
    public static String getBase64String(@NonNull File file) throws IOException {
        InputStream in = null;
        final byte[] buffer = new byte[BUFFER_SIZE];
        ByteArrayOutputStream out = new ByteArrayOutputStream();

        try {
            in = new FileInputStream(file);
            int read;

            while ((read = in.read(buffer)) != -1) {
                out.write(buffer, 0, read);
            }
        } finally {
            if (in != null) {
                in.close();
            }
        }

        return Base64.encodeToString(out.toByteArray(), Base64.DEFAULT);
    }

    private static final int CAPTURE_IMAGE_ACTIVITY_REQUEST_CODE = 100;
    private static final int CAPTURE_VIDEO_ACTIVITY_REQUEST_CODE = 200;

//    private void Encrypt_Message(){
//        final OpenPGP openPGP = new OpenPGP();
//
//        final File file = new File(MainActivity.uriSavedImage.getPath());
//        if (!file.exists()) {
//        } else {
//            try {
//                long size = file.getTotalSpace();
//                final String base64Content = getBase64String(file);
//
//                byte[] content = Base64.decode(base64Content, Base64.DEFAULT);
//                EncryptPackage EncryptPackage = openPGP.EncryptAttachment(content, publicKey, "temp.jp");
//
//                //TypedByteArray KeyPackage = new TypedByteArray(attachment.getMimeType(), EncryptPackage.KeyPackage);
//                //TypedByteArray DataPackage = new TypedByteArray(attachment.getMimeType(), EncryptPackage.DataPackage);
//                //AttachmentUploadResponse response = mApi.uploadAttachment(attachment, mMessage.getMessageId(), KeyPackage, DataPackage);
//
//                DecryptPackage image = openPGP.DecryptAttachment(EncryptPackage.KeyPackage, EncryptPackage.DataPackage, privateKey, "123");
//
//                File path = Environment.getExternalStoragePublicDirectory(Environment.DIRECTORY_DOWNLOADS);
//                File d_file = new File(path, "temp.jpg");
//                try {
//                    FileOutputStream stream = new FileOutputStream(d_file, true);
//                    stream.write(image.DecryptData);
//                    stream.close();
//                    Log.i("saveData", "Data Saved");
//                } catch (IOException e) {
//                    Log.e("SAVE DATA", "Could not write file " + e.getMessage());
//                }
//
//                Log.e("test", "error while attaching file: ");
//            } catch (Exception e) {
//                Log.e("test", "error while attaching file: " + MainActivity.uriSavedImage.getPath(), e);
//            }
//
//            Log.e("OpenPGP", "OpenFile Done");
//        }
//    }
//
//    @Override
//    protected void onActivityResult(int requestCode, int resultCode, Intent data) {
//        this.Encrypt_Message();
//        if (requestCode == CAPTURE_IMAGE_ACTIVITY_REQUEST_CODE) {
//            if (resultCode == RESULT_OK) {
//                // Image captured and saved to fileUri specified in the Intent
//                Toast.makeText(this, "Image saved to:\n" +
//                        data.getData(), Toast.LENGTH_LONG).show();
//            } else if (resultCode == RESULT_CANCELED) {
//                // User cancelled the image capture
//            } else {
//                // Image capture failed, advise user
//            }
//        }
//
//        if (requestCode == CAPTURE_VIDEO_ACTIVITY_REQUEST_CODE) {
//            if (resultCode == RESULT_OK) {
//                // Video captured and saved to fileUri specified in the Intent
//                Toast.makeText(this, "Video saved to:\n" +
//                        data.getData(), Toast.LENGTH_LONG).show();
//            } else if (resultCode == RESULT_CANCELED) {
//                // User cancelled the video capture
//            } else {
//                // Video capture failed, advise user
//            }
//        }
//    }

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        if (savedInstanceState == null) {
            getSupportFragmentManager().beginTransaction()
                    .add(R.id.container, new PlaceholderFragment())
                    .commit();
        }


    }


//    @Override
//    public boolean onCreateOptionsMenu(Menu menu) {
//        // Inflate the menu; this adds items to the action bar if it is present.
//        getMenuInflater().inflate(R.menu.menu_main, menu);
//        return true;
//    }
//
//    @Override
//    public boolean onOptionsItemSelected(MenuItem item) {
//        // Handle action bar item clicks here. The action bar will
//        // automatically handle clicks on the Home/Up button, so long
//        // as you specify a parent activity in AndroidManifest.xml.
//        int id = item.getItemId();
//
//        //noinspection SimplifiableIfStatement
//        if (id == R.id.action_settings) {
//            return true;
//        }
//
//        return super.onOptionsItemSelected(item);
//    }

    /**
     * A placeholder fragment containing a simple view.
     */
    public static class PlaceholderFragment extends Fragment {

        String privateKey = "-----BEGIN PGP PRIVATE KEY BLOCK-----\r\nVersion: OpenPGP.js v0.9.0\r\nComment: http://openpgpjs.org\r\n\r\n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\nPPekG4ttm6z3/BqqVplanIRSXlsqyp6J8A==\r\n=Pyb1\r\n-----END PGP PRIVATE KEY BLOCK-----\r\n";
        String passphrase = "123";
        String publicKey = "-----BEGIN PGP PUBLIC KEY BLOCK-----\nVersion: OpenPGP.js v0.7.1\nComment: http://openpgpjs.org\n\nxsBNBFSjdRkBB/9slBPGNrHAMbYT71AnxF4a0W/fcrzCP27yd1nte+iUKGyh\nyux3xGQRIHrwB9zyYBPFORXXwaQIA3YDH73YnE0FPfjh+fBWENWXKBkOVx1R\nefPTytGIyATFtLvmN1D65WkvnIfBdcOc7FWj6N4w5yOajpL3u/46Pe73ypic\nhe10XuwO4198q/8YamGpTFgQVj4H7QbtuIxoV+umIAf96p9PCMAxipF+piao\nD8LYWDUCK/wr1tSXIkNKL+ZCyuCYyIAnOli7xgIlKNCWvC8csuJEYcZlmf42\n/iHyrWeusyumLeBPhRABikE2ePSo+XI7LznD/CIrLhEk6RJT31+JR0NlABEB\nAAHNBlVzZXJJRMLAcgQQAQgAJgUCVKN1JAYLCQgHAwIJEH0tU95Lz7QEBBUI\nAgoDFgIBAhsDAh4BAAAXCgf8CsNCB0tKdLrwGe+dDLTGGdgyYr33Jz6GVta6\nJMl4rccf5T8QiRPkOIWITITpi5maxrn1w7yOUI3xkqCLCEO9vqLhIRr1/aBq\nvVUI+0L7goJoVrx6ynSR1KNNHM/hkttA+t1t894qgug6hooUfxtFWU8KesKK\ngdMFOxst3ODTeZxzO6xmiaf9Mof/y1M5y1fsKuUH57AJRzkJYviZmpEWMAxI\nmmiCPv/iMRUeR7hX9+spG2O9A0Ny46g89T59Wkerggu6/ulgX0O6MAhsuBY3\n+10TgajGyub5oJTLKVDY/nlVvmaEA+4IthepIQs+L3380oQz3GEtr/UfB1PB\nD/VfTM7ATQRUo3UkAQf/dcKxn9bt+fDMxuQT6sxSWjX4ptf6W0QbucDA/5Dw\n2vCFvCGakDdsczduFJ23QI7iZHHig5Fyp5M2MV+1DM/EJs9OZxMK6k0I4M4r\niucSf2L2XPv8m2Q5/nn7+gdvH6mO8POsDu766A0fMNhN36eHa5730dahJlIR\nYP+wOunUkQ3wzTPE4MZh878eCvkaeelMTMPNnQu9ONgxVyaO8GG09M0uJCxV\nqQ6PXBMtYSBydrYUscAeHQrreyfECNPobWgXRafTwftk/n9aGIzLViv4zo36\nGwuk7JzC3AF2PANxYus6EACPckwsjpbMVLpIpSvjDGdlYg9BPtNk0Fd4qZt2\nzwARAQABwsBfBBgBCAATBQJUo3UmCRB9LVPeS8+0BAIbDAAAgzcH/1kyh+20\ntcUGMRrT3akfhVv3o4d9C4j0Ja7PQMKwZNiSdFSbQ8ZE9xbR5cKB/Z33emMw\n+54CeJsanj7lOeefRqoHUynpirANguPLmp8SW4Dor4rwSOs4gfO1ttzw7+8M\nIeFG8p8OQ5B+J3+KCUdiuB+6zdxGW3rIfA9OAPYAObQUJ7quS/lmoNrOzKVm\nJWa7x4f9cS2Wls/vt/jeEn2j0x/GqN0KI8P2PjixiBY5Ogf6FRHvWWUD4SYx\n8YHf6rvFXGHW3tdMRRb24miP0UuhbOyUUiQm1xNIe2fJ+IUCD9cumgWbGXof\nGjz3pBuLbZus9/waqlaZWpyEUl5bKsqeifA=\n=LhM4\n-----END PGP PUBLIC KEY BLOCK-----";

        //.net private key
        String private_key_net = "-----BEGIN PGP PRIVATE KEY BLOCK-----\n" +
                "Version:    OpenPGP.js v0.7.1\n" +
                "Comment:    http://openpgpjs.org\n" +
                "\n" +
                "xcMGBFRAGVYBCAC873RDV1sSYgUg/xFxoRGWeJpUKtI6e/1W+h+3IxHftQAtQYBN\n" +
                "L3XtigghJTjMjKoeCW4Q6qILXk2O3P8JKxewmMe8lPMK9WRE42kEpZl31pJ4YaDN\n" +
                "NFSBuF/uHsNnXgM3INEmRri3ewIlEcptnmOnqIXbsEpPlUo5LpaIXyHmdVqRo5fi\n" +
                "JykZWY2OIqV0QRw0hSkz4Lcl0ZONDfd5O4bvfYwq0CzxuuCz7YFl73vIC+gwcEH8\n" +
                "6msBOeWR2JN3E4O8NqrUwyQSaHqQmXENkXISo6KpNlLPkaN5CGppDMXYpClDIc82\n" +
                "4V/JmGuXHmDyEmecyWw2djsqxirjlnkDQV4JABEBAAH+CQMIzFi3glrFyiFgsxzZ\n" +
                "kO4NBtPh5Sy+auolrMVb/ijp/MX80GAnV6/pL7xsVCFAdg9PZqreot+iVTK2gAK7\n" +
                "ih9OUZ3CZ2CsCXKtPD5Bv9fxUWlKeB8yTcyP/ivnqTc/AXu6S7/YQNqyY8dgSTnG\n" +
                "Q4ZTbI7UYclr6MnEeoAWzDFDtAGmmRc2W/aIUn+lHyMiB9tM/geEmeZPipCKR4Iz\n" +
                "9HKcOXYFIsz7jC0uBVbYowe974WfYDNjMKDCaBV7o6Bd3Gw9BS/VpN9+dnLdQvu3\n" +
                "YvnxEzCrBKcnJ3J4DwsYHm0fwLwMce293K3Y7jWEOlbZYiu6HzwDoFu2CGMjYVOF\n" +
                "P8OecTYwOgxLwHpAsw1EXFHOC4Z4W1L44xtB3qesk9kwueh8ON0yxOtsLtIpNcb7\n" +
                "MGH+7OwAhSIVpjFwsGrTHxelKgPgeSgroPJqIs4Rdz84AGFvkNW32EW3qxUsmGmJ\n" +
                "+XP+tzXoyWang2wjmeOF1n+Y0Xdp4wVkIWsZqfkzSfIEh2xoFKziWKEASPf7u0i3\n" +
                "eyu7A0Es+7dhds3BDkw4O9Dt5elQyKygclaDB3ny79VRRZCBfuCAVfAyO/DpizvF\n" +
                "ltJSwQZ2j3pdDOnfYhRtzk5C03OyDJDpVXtGxRY5JpMFnjOsLO9yFQF9apsOOjfV\n" +
                "Ou6YwaaJ0brCBevFfTfneXhk/oXxrR7twRNAY5bdKmGVS2C3pOemR+o1lKWY6Az3\n" +
                "WGKnaf+KX2/23mMh2Dl7bqwqHrWvJTWwOi2lW28TkVrxAqLidnJmWfGRYS6L83NV\n" +
                "icHcAycmB8hjCngRkzw3ZTzzkaHdKeEvHdU/fJLxuLHYCLc9MYCs/NEcMqw+H+pX\n" +
                "M8r0gU4nD0jpSiJbfT9Tk+mLSXkHp9aDbDzD0Zywa6Oqwq1a3XHr/jMXRgAEHSpz\n" +
                "Tn/+hL5MFNLczQDCwHIEEAEIACYFAlRAGVgGCwkIBwMCCRDJ6DjbEVuFVgQVCAIK\n" +
                "AxYCAQIbAwIeAQAAweEIAIiV9RcpkS/D2jEG51JBbnV0X3e3xWLYn9sqKBUUcCgf\n" +
                "OtWuCqSisTsEGjtENkSEUVym1d0CJDZYdg/hgTGMhZr7L8PFNSY215TgZcXjyWvL\n" +
                "9NgrMJinDa+epUs5rOW0OA08JmadL07wzleMFWjLBVLLnLL2uq9/R/Rndpf/7g1R\n" +
                "gC2CYoza37aFbI33OOe1VfrpjUJ074bffSrmzvYHdkB/dNlJhvRftxHLtzkzlLhI\n" +
                "eKr3jhx0MTFzNhX9VtXNbx8HqRbJWKRgtoBxUvm54f7WNV3gZUckjWJDz7+TAACb\n" +
                "xEJxqaaCPlnmb3RFRd8dQCu67TP+0hsM2q7PtgcnRAfHwwYEVEAZWAEIANUYBlFP\n" +
                "MvdZvr10DxX4+OJYAiT/4BSAEawkMLThyNYycnEIM3Epv2lZbJyzFU8RUxifhHAY\n" +
                "i8+sYWA/czncabzWS7i0Hmes7FAz6nLAPf/jiIx5A8F35mhdGuvmN11OaXJbRT5J\n" +
                "e5Xot0UmnZ8NSglOK8F0R0V2+uQ5Nb8lF7XlGeRDBaE8eW4aMQydyIrF5W5cUIfI\n" +
                "FUYJnvURTpHY2nPR8N8XfMBEK/b9bXSO8KyvxsUghhOO/UrhpeUVHukcCrvtsZuE\n" +
                "VqB+WkFYhxr9Se+YHc23BWMsNNBLL6deVQzPGwePiYnUYtwzOdh1TXeaBy1YuBJU\n" +
                "VmszvThb3n9cgecAEQEAAf4JAwgz6ysmk5if3mAE3Qcb5jY5h9h5kiK6LmKpNb2L\n" +
                "Wx5ZdBOYR3KRIZDpnOh1X4Fn0fGKcrS0vadviI9ni+Dj66S8CEWEL9a7QF6o07K1\n" +
                "pERKvDgAT/taLqJpWmMQSnWJKslqbgxAsA4NVxuz2sQ0Wh7KOTCK/QVMUCIl/jTw\n" +
                "A7xkhoAvQElZKzOSXTSSe99uLGguHYx2jm4GrUjpR3NhbeYgb/COF0yYF0tC0zvL\n" +
                "xz/iC7bNSRk347EAjtI504yUuqYx44EVeiEP1xhsZR43w82qXfeyP7Djac1yFgYu\n" +
                "LRdYWB35HvjHdIilQckKiyBkLhyG1x2gPo2D0Rc1YwitZ2OLL/OdjZFFtUWsab+R\n" +
                "UpJc/NPrYntyejyevQEdIeqOKwjlWnzEBX1DPlLlXO+r1BNZKrjgackrG/FWD1Fo\n" +
                "xE8uM/GmM1Hm+OY7feJUNa5/L63X5cS+gcNzeAwGeMcKI2RgaDM6nEeJ/xKJA6wx\n" +
                "iO8h8TaAtEoxvYOXJIxlKUR/BDn8SqAG0ChyatFdXlVjV+p3YbKvULayBRD7Qnxm\n" +
                "I+PzXR0I5jDXku4G5Tjypa8tDAFqipwMl/tIXu8icbTp5R4Eque6KkYWLqckAzHE\n" +
                "yjnO+9ZzYaysOcDiP3JJ12rwYWedInH6G5Ujdsgeo9e9H2ythgwVE/RzkB5recau\n" +
                "OtEA1+0NpJu7M8wDcHI1aaq7dBXtvP124JxOmEY4ClrKR4TPiuJ7wVVD+VEWlxca\n" +
                "Xa3CjpUUgL81+q9yfB9aTtSCYTMzVKQ33l7JPWZmR1sUV5lSOyXXmTIdbm32YOfX\n" +
                "dQtN1qOtWuady2CMEw2AnsOBitQqxRWzP869VhOebgJ0A8CVUZLe0eDyQNWPe8Qy\n" +
                "KmrRxwzn+JgTTPv6MsctLmODXUsoKf7utkDbk9v1qlV/Kuk9F2IgEbjCwF8EGAEI\n" +
                "ABMFAlRAGVoJEMnoONsRW4VWAhsMAACEaQgAiZwPofEwkH1IPs3HZDF9JMFUuxr+\n" +
                "hizcGBKmdDFXidm+cn27ywsUFwL/I5MO01GypumZr5VfWOuwG7NH7S0QBV4Y43DO\n" +
                "8nabT4j/FYqqXfxHUk//S3nNMCQ0CtZv+blZdA1JqOjzQZjjcxDFMGTDi4u22PBt\n" +
                "2hAi5kxKtogLlN8G/hrM5tWjsEvAClf5jjT0bpV0Cb6aVoZ4t7MlmWViUx7mEZ+Y\n" +
                "WslT2ufu/4Kh1Jhb1wOK+qhhFOnN5OqD5NesX57xxeM5rPvesXR2dqJAq5nIE4bh\n" +
                "u/44gJtO9lySgIMXx6S6ZtB5P0rn0HhNRRWRmPN81dXnrq3pBQ8O6CC9Gw==\n" +
                "=EIgA\n" +
                "-----END PGP PRIVATE KEY BLOCK-----";


        String public_key_net = "-----BEGIN PGP PUBLIC KEY BLOCK-----\n" +
                "Version: OpenPGP.js v0.7.1\n" +
                "Comment: http://openpgpjs.org\n" +
                "\n" +
                "xsBNBFRAGVYBCAC873RDV1sSYgUg/xFxoRGWeJpUKtI6e/1W+h+3IxHftQAt\n" +
                "QYBNL3XtigghJTjMjKoeCW4Q6qILXk2O3P8JKxewmMe8lPMK9WRE42kEpZl3\n" +
                "1pJ4YaDNNFSBuF/uHsNnXgM3INEmRri3ewIlEcptnmOnqIXbsEpPlUo5LpaI\n" +
                "XyHmdVqRo5fiJykZWY2OIqV0QRw0hSkz4Lcl0ZONDfd5O4bvfYwq0CzxuuCz\n" +
                "7YFl73vIC+gwcEH86msBOeWR2JN3E4O8NqrUwyQSaHqQmXENkXISo6KpNlLP\n" +
                "kaN5CGppDMXYpClDIc824V/JmGuXHmDyEmecyWw2djsqxirjlnkDQV4JABEB\n" +
                "AAHNBlVzZXJJRMLAcgQQAQgAJgUCVEAZWAYLCQgHAwIJEMnoONsRW4VWBBUI\n" +
                "AgoDFgIBAhsDAh4BAADB4QgAiJX1FymRL8PaMQbnUkFudXRfd7fFYtif2yoo\n" +
                "FRRwKB861a4KpKKxOwQaO0Q2RIRRXKbV3QIkNlh2D+GBMYyFmvsvw8U1JjbX\n" +
                "lOBlxePJa8v02CswmKcNr56lSzms5bQ4DTwmZp0vTvDOV4wVaMsFUsucsva6\n" +
                "r39H9Gd2l//uDVGALYJijNrftoVsjfc457VV+umNQnTvht99KubO9gd2QH90\n" +
                "2UmG9F+3Ecu3OTOUuEh4qveOHHQxMXM2Ff1W1c1vHwepFslYpGC2gHFS+bnh\n" +
                "/tY1XeBlRySNYkPPv5MAAJvEQnGppoI+WeZvdEVF3x1AK7rtM/7SGwzars+2\n" +
                "BydEB87ATQRUQBlYAQgA1RgGUU8y91m+vXQPFfj44lgCJP/gFIARrCQwtOHI\n" +
                "1jJycQgzcSm/aVlsnLMVTxFTGJ+EcBiLz6xhYD9zOdxpvNZLuLQeZ6zsUDPq\n" +
                "csA9/+OIjHkDwXfmaF0a6+Y3XU5pcltFPkl7lei3RSadnw1KCU4rwXRHRXb6\n" +
                "5Dk1vyUXteUZ5EMFoTx5bhoxDJ3IisXlblxQh8gVRgme9RFOkdjac9Hw3xd8\n" +
                "wEQr9v1tdI7wrK/GxSCGE479SuGl5RUe6RwKu+2xm4RWoH5aQViHGv1J75gd\n" +
                "zbcFYyw00Esvp15VDM8bB4+JidRi3DM52HVNd5oHLVi4ElRWazO9OFvef1yB\n" +
                "5wARAQABwsBfBBgBCAATBQJUQBlaCRDJ6DjbEVuFVgIbDAAAhGkIAImcD6Hx\n" +
                "MJB9SD7Nx2QxfSTBVLsa/oYs3BgSpnQxV4nZvnJ9u8sLFBcC/yOTDtNRsqbp\n" +
                "ma+VX1jrsBuzR+0tEAVeGONwzvJ2m0+I/xWKql38R1JP/0t5zTAkNArWb/m5\n" +
                "WXQNSajo80GY43MQxTBkw4uLttjwbdoQIuZMSraIC5TfBv4azObVo7BLwApX\n" +
                "+Y409G6VdAm+mlaGeLezJZllYlMe5hGfmFrJU9rn7v+CodSYW9cDivqoYRTp\n" +
                "zeTqg+TXrF+e8cXjOaz73rF0dnaiQKuZyBOG4bv+OICbTvZckoCDF8ekumbQ\n" +
                "eT9K59B4TUUVkZjzfNXV566t6QUPDuggvRs=\n" +
                "=9/hF\n" +
                "-----END PGP PUBLIC KEY BLOCK-----";



        String string_armed_key ="-----BEGIN PGP MESSAGE-----\n" +
                "Version: ProtonMail v0.1.0\n" +
                "Comment: https://protonmail.com\n" +
                "\n"+
                "wcBMA8noONsRW4VWAQf/a3RUJaR4nsnmBE+tbBymAx3rCZvG2xbHdUIJpxd/0V7r\n"+
                "Wb4ScHpPLSWEzSI9fWGZJCfRVQ6BwVub7myANjgl2qX6fenAuAxC4qU16P4QvZYS\n"+
                "TkE9XwS1X7YL4SatsMnUtQYgb0SMFXSjA0/19UyukXAmwx8LJsoFRir8AlAfdyYg\n"+
                "Fg02foN2ZKbHc/aLBtjEUYTps2BW3xw3Z/H6NXSr524/jbRGbHkqy3zul4b1q6eZ\n"+
                "LxtA5r3XYE6njC6lfyy5x+OnoJF0QagwcA5Rsul2bl+KAbI6nLMdelKePn1bQYBZ\n"+
                "WUvm9JeyiguDuX1LrtHefh1CR9Po2g7Rc7Cv9fTNLQ==\n" +
                "=3zGb\n" +
                "-----END PGP MESSAGE-----";

        String string_armed_data = "-----BEGIN PGP MESSAGE-----\n"+
                "Version: ProtonMail v0.1.0\n"+
                "Comment: https://protonmail.com\n"+
                "\n"+
                "0nIBn2Lq4RT8AotgzNwSWBtz8F8y1kU67t8Pa7GOGrtZxl4YhKl1YNcn8T6F1yfB\n"+
                "I3u5URSjY4OS6Y3BqJC3xMjr5hoMBmwy2rTEsheKK3NJ/TWJvLDXPsTQi3PO75Ae\n"+
                "P0VubLe5TAMFwKg2VjnyYogU1Ts=\n"+
                "=OUZw\n"+
                "-----END PGP MESSAGE-----";


        public PlaceholderFragment() {
        }


        private static final int BUFFER_SIZE = 4096;
        public static String getBase64String(@NonNull File file) throws IOException {
            InputStream in = null;
            final byte[] buffer = new byte[BUFFER_SIZE];
            ByteArrayOutputStream out = new ByteArrayOutputStream();

            try {
                in = new FileInputStream(file);
                int read;

                while ((read = in.read(buffer)) != -1) {
                    out.write(buffer, 0, read);
                }
            } finally {
                if (in != null) {
                    in.close();
                }
            }

            return Base64.encodeToString(out.toByteArray(), Base64.DEFAULT);
        }

        TextView helloworld;
        private static final int CAPTURE_IMAGE_ACTIVITY_REQUEST_CODE = 100;
        private Uri fileUri;
        @Override
        public View onCreateView(LayoutInflater inflater, ViewGroup container, Bundle savedInstanceState) {
            View rootView = inflater.inflate(R.layout.fragment_main, container, false);
            this.helloworld = (TextView) rootView.findViewById(R.id.hello_world);
            //String test = OpenPGP.test2(100);
           // this.helloworld.setText(test);


            Button test_button = (Button) rootView.findViewById(R.id.pgp_test);
            test_button.setOnClickListener(new View.OnClickListener() {
                @Override
                public void onClick(View view) {

                    OpenPgp test = OpenPgp.createInstance();
                    test.generateKey("feng", "protonmail.com", "123", 2048);
//                    OpenPgpKey test1 = test.generateKey("feng", "protonmail.ch", "123");
//                    boolean test2 = test.checkPassphrase("", "");
//                    String test3 = test.encryptMessage("", "");
//                    String test4 = test.decryptMessage("", "");
//                    EncryptPackage test5 = test.encryptAttachment("", "".getBytes(), "");
//                    byte[] test6 = test.decryptAttachment("".getBytes(), "".getBytes(), "");
//

//                    try {
//                        test.throwAnException();
//                    } catch (RuntimeException e) {
//                        String error = e.getMessage();
//                        Log.d("", error);
//                    }

                    /**TODO : not done and not inuse */
//                    byte[] test7 = test.decryptAttachmentWithPassword("".getBytes(), "".getBytes(), "");
//
//                    byte[] test8 = test.getPublicKeySessionKey("".getBytes(), "", "");
//
//                    byte[] test9 = test.getSymmetricSessionKey("".getBytes(), "");
//
//                    byte[] test10 = test.getNewPublicKeyPackage("".getBytes(), "");
//
//                    byte[] test11 = test.getNewSymmetricKeyPackage("".getBytes(), "");
//
//                    String test12 = test.encryptMessageAes("", "");
//
//                    String test13 = test.decryptMessageAes("", "");
//
//                    String test14 = test.encryptMailboxPwd("test pwd", "4428c82a118a2dc76f53dab507d3b1d69850ebb9");
//
//                    String test15 = test.decryptMailboxPwd(test14, "4428c82a118a2dc76f53dab507d3b1d69850ebb9");
//
//                    Log.d("", "");

//                    File path = Environment.getExternalStoragePublicDirectory(Environment.DIRECTORY_DOWNLOADS);
//                    String d = "adsfasdfasdfasfasdfasdfasdf";
//                    File file = new File(path, "_Ascent_Test.txt");
//                    try {
//                        FileOutputStream stream = new FileOutputStream(file, true);
//                        stream.write(d.getBytes());
//                        stream.close();
//                        Log.i("saveData", "Data Saved");
//                    } catch (IOException e) {
//                        Log.e("SAVE DATA", "Could not write file " + e.getMessage());
//                    }
//
//                    Intent intent = new Intent(MediaStore.ACTION_IMAGE_CAPTURE);
//                    File imagesFolder = new File(Environment.getExternalStorageDirectory(), "MyImages");
//                    imagesFolder.mkdirs(); // <----
//                    File image = new File(imagesFolder, "image_001.jpg");
//                    MainActivity.uriSavedImage = Uri.fromFile(image);
//                    intent.putExtra(MediaStore.EXTRA_OUTPUT, MainActivity.uriSavedImage); // set the image file name
//                    // start the image capture Intent
//                    startActivityForResult(intent, CAPTURE_IMAGE_ACTIVITY_REQUEST_CODE);


//                    OpenPGP pgp = new OpenPGP();
//
//                    String jsonString = AppUtil.readTxt(getActivity(), R.raw.feng_mulitiple_keys);
//                    try {
//                        JSONObject pages = new JSONObject(jsonString);
//                        JSONObject user = pages.getJSONObject("User");
//                        JSONArray addresses = user.getJSONArray("Addresses");
//                        for (int i = 0; i < addresses.length(); ++i) {
//                            JSONObject address = addresses.getJSONObject(i);
//                            String addressID = address.getString("ID");
//                            ArrayList<OpenPGPKey> address_keys = new ArrayList<OpenPGPKey>();
//                            JSONArray keys = address.getJSONArray("Keys");
//                            for (int j = 0; j < keys.length(); ++j) {
//                                JSONObject key = keys.getJSONObject(j);
//                                OpenPGPKey keyo = new OpenPGPKey();
//                                keyo.PublicKey = key.getString("PublicKey");
//                                keyo.PrivateKey = key.getString("PrivateKey");
//                                address_keys.add(keyo);
//                            }
//                            pgp.AddKeys(addressID, address_keys);
//                        }
//
//                        Log.d("", "");
//
//                    } catch (JSONException e) {
//                        e.printStackTrace();
//                    }
//
//
//                    String encrypted_test_data = AppUtil.readTxt(getActivity(), R.raw.feng_mulitiple_test_message);
//
//                    String tmp_out = pgp.DecryptMessage(encrypted_test_data, "123");
//
//
//                    String cleartext = AppUtil.readTxt(getActivity(), R.raw.test_plain_message);
//


//                    long time= System.currentTimeMillis();
//
//                    //test generate a new key
//                    OpenPGPKey newKey = OpenPGP.GenerateKey("feng", "123123");
//
//                    int check1 = OpenPGP.CheckPassphrase(newKey.PrivateKey, "");
//                    int check2 = OpenPGP.CheckPassphrase(newKey.PrivateKey, "123");
//                    int check3 = OpenPGP.CheckPassphrase(newKey.PrivateKey, "123123");
//
//
//                    String scheck1 = OpenPGP.UpdateKeyPassphrase(newKey.PrivateKey, "", "123");
//                    String scheck2 = OpenPGP.UpdateKeyPassphrase(newKey.PrivateKey, "123", "123");
//                    String scheck3 = OpenPGP.UpdateKeyPassphrase(newKey.PrivateKey, "123123", "123");
//
//
//                    long end = System.currentTimeMillis();
//
//                    int check4 = OpenPGP.CheckPassphrase(scheck3, "");
//                    int check5 = OpenPGP.CheckPassphrase(scheck3, "123");
//                    int check6 = OpenPGP.CheckPassphrase(scheck3, "123123");
//
//                    helloworld.setText("Time:" + String.valueOf(end - time));
//                    int isPwdOK = OpenPGP.SetupKeys(privateKey,publicKey,passphrase);
//                    int isPwdOK1 = OpenPGP.SetupKeys(privateKey, publicKey, "123123");
//
//                    Log.e("test", String.format("%d",isPwdOK));
//                    String test_encrypt = OpenPGP.EncryptMailboxPWD("thisisatestmailbox", "4428c82a118a2dc76f53dab507d3b1d69850ebb9");
//                    String test_plain_text = OpenPGP.DecryptMailboxPWD(test_encrypt, "4428c82a118a2dc76f53dab507d3b1d69850ebb9");
//
//                    Log.e("DecryptMailboxPWD", test_plain_text);
//
//                    String encryptedText = OpenPGP.EncryptMessageWithKey(cleartext, publicKey);
//                    String decryptedText = OpenPGP.DecryptMessage(encryptedText, privateKey, passphrase);
//                    if (decryptedText.equalsIgnoreCase(cleartext)) {
//                        Log.e("Test", "OK");
//                    }
//
//                    String test_password = "123";
//                    String original_text = "<div>lajflkjasklfjlksdfkl</div><div><br></div><div>Sent from iPhone <a href=\"https://protonmail.ch\">ProtonMail</a>, encrypted email based in Switzerland.<br></div>";
//                    String test_aes_str = "-----BEGIN PGP MESSAGE-----\nVersion: OpenPGP.js v0.10.1-IE\nComment: http://openpgpjs.org\n\nww0ECQMIina34sp8Nlpg0sAbAc/x6pR8h57OJv9pklLuEc/aH5lFT9OpWS+N\n7oPaJCGK1f3aQV7g5V5INlUvwICeDiSkDMo+hHGtFgDFEwgNiMDc7wAtod1U\nZ5PTHegr8KWWmBiDIYuPVFJH8mALVcQen9MI1xFSYO8RvSxM/P6dJPzrVZQK\noIRW98dxMjJqMWW9HgqWCej6TRDua65r/X7Ucco9tWpwzmQCnvJLqpcYYrEk\ngcGyXsp3RvISG6pWh8ZFemeO6yoqnphYmcAa/i4h4CiMqKDDJuOg4UdpW46U\nGoNSV+C4hz5ymRDj\n=hUe3\n-----END PGP MESSAGE-----";
//                    String plain_text = OpenPGP.DecryptMessageAES(test_aes_str, test_password);
//
//                    if (plain_text.equalsIgnoreCase(original_text)) {
//                        Log.e("Test", "OK");
//                    }
//
//
//                    String new_enc_msg = OpenPGP.EncryptMessageAES(original_text, test_password);
//                    if(new_enc_msg != null)
//                    {
//                        Log.e("Test", "OK");
//                    }
//
//                    String new_dec_msg = OpenPGP.DecryptMessageAES(new_enc_msg, test_password);
//                    if(new_enc_msg != null && new_dec_msg.equalsIgnoreCase(original_text))
//                    {
//                        Log.e("Test", "OK");
//                    }
//
//                    // byte[] data_out = open_test.DecryptAttachment(string_armed_key.getBytes(), string_armed_data.getBytes(), private_key_net, "123");
//                    // String str_out_data = new String(data_out);
//                   //for (int i = 0; i< 100 ; i ++ ) {
//
//                        String testString = "this is a test attachment1111111";
//                        byte[] data_in = testString.getBytes();
//
//                        EncryptPackage encryptPackage = OpenPGP.EncryptAttachment(data_in, public_key_net, "test.txt");
//                        DecryptPackage new_out_data = OpenPGP.DecryptAttachment(encryptPackage.KeyPackage, encryptPackage.DataPackage, private_key_net, "123");
//                        String test_out_msg = new String(new_out_data.DecryptData);
//
//
//                    byte[] sessionBytes = OpenPGP.GetPublicKeySessionKey(encryptPackage.KeyPackage, private_key_net, "123");
//
//                    byte[] newKeyPackage = OpenPGP.GetNewPublicKeyPackage(sessionBytes, public_key_net);
//
//                    DecryptPackage out = OpenPGP.DecryptAttachment(newKeyPackage, encryptPackage.DataPackage, private_key_net, "123");
//                    String pak = new String(out.DecryptData);
//
//                    byte[] newSymKeyPackage = OpenPGP.GetNewSymmetricKeyPackage(data_in, "123");
//
//
//                    byte[] out1 = OpenPGP.DecryptAttachmentWithPassword(newSymKeyPackage, encryptPackage.DataPackage, "123");
//                    //String pak1 = new String(out1);


 //                   String testEmpty = "";
//                    String testEmptyencryptedText = OpenPGP.EncryptMessage(testEmpty, publicKey);
//                    String testEmptydecryptedText = OpenPGP.DecryptMessage(testEmptyencryptedText, privateKey, passphrase);
//                    if (testEmpty.equalsIgnoreCase(testEmptydecryptedText)) {
//                        Log.e("Test", "OK");
//                    }
                }
            });



            return rootView;
        }



    }
}
