// AUTOGENERATED FILE - DO NOT MODIFY!
// This file generated by Djinni from open_pgp.djinni

package ch.protonmail.android.utils;

public final class OpenPgpKey {


    /*package*/ final String publicKey;

    /*package*/ final String privateKey;

    public OpenPgpKey(
            String publicKey,
            String privateKey) {
        this.publicKey = publicKey;
        this.privateKey = privateKey;
    }

    public String getPublicKey() {
        return publicKey;
    }

    public String getPrivateKey() {
        return privateKey;
    }

    @Override
    public String toString() {
        return "OpenPgpKey{" +
                "publicKey=" + publicKey +
                "," + "privateKey=" + privateKey +
        "}";
    }

}
