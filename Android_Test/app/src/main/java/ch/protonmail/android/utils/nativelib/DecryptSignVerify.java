// AUTOGENERATED FILE - DO NOT MODIFY!
// This file generated by Djinni from open_pgp.djinni

package ch.protonmail.android.utils.nativelib;

import javax.annotation.CheckForNull;
import javax.annotation.Nonnull;

public final class DecryptSignVerify {


    /*package*/ final String mPlainText;

    /*package*/ final boolean mVerify;

    public DecryptSignVerify(
            @Nonnull String plainText,
            boolean verify) {
        this.mPlainText = plainText;
        this.mVerify = verify;
    }

    @Nonnull
    public String getPlainText() {
        return mPlainText;
    }

    public boolean getVerify() {
        return mVerify;
    }

    @Override
    public String toString() {
        return "DecryptSignVerify{" +
                "mPlainText=" + mPlainText +
                "," + "mVerify=" + mVerify +
        "}";
    }

}
