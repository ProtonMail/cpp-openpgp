// AUTOGENERATED FILE - DO NOT MODIFY!
// This file generated by Djinni from open_pgp.djinni

package ch.protonmail.android.utils;

import java.util.concurrent.atomic.AtomicBoolean;
import javax.annotation.CheckForNull;
import javax.annotation.Nonnull;

public abstract class OpenPgp {
    public abstract boolean addAddress(@Nonnull Address address);

    public abstract boolean removeAddress(@Nonnull String addressId);

    public abstract boolean cleanAddresses();

    /**disable/enable debug model */
    public abstract void enableDebug(boolean isDebug);

    /**generat new key pair */
    @Nonnull
    public abstract OpenPgpKey generateKey(@Nonnull String userName, @Nonnull String domain, @Nonnull String passphrase);

    /**check is primary key passphrase ok */
    public abstract boolean checkPassphrase(@Nonnull String privateKey, @Nonnull String passphrase);

    /**update single private key password */
    @Nonnull
    public abstract String updateSinglePassphrase(@Nonnull String privateKey, @Nonnull String oldPassphrase, @Nonnull String newPassphrase);

    /**update the information carried in the packet. //TODO need add more parameters */
    public abstract void updatePrivateInfo(@Nonnull String privateKey);

    /**encrypt message */
    @Nonnull
    public abstract String encryptMessage(@Nonnull String addressId, @Nonnull String plainText);

    @Nonnull
    public abstract String encryptMessageSingleKey(@Nonnull String publicKey, @Nonnull String plainText);

    @Nonnull
    public abstract String decryptMessage(@Nonnull String encryptText, @Nonnull String passphras);

    @Nonnull
    public abstract String decryptMessageSingleKey(@Nonnull String encryptText, @Nonnull String privateKey, @Nonnull String passphras);

    @Nonnull
    public abstract EncryptPackage encryptAttachment(@Nonnull String addressId, @Nonnull byte[] unencryptData, @Nonnull String fileName);

    @Nonnull
    public abstract EncryptPackage encryptAttachmentSingleKey(@Nonnull String publicKey, @Nonnull byte[] unencryptData, @Nonnull String fileName);

    @Nonnull
    public abstract byte[] decryptAttachment(@Nonnull byte[] key, @Nonnull byte[] data, @Nonnull String passphras);

    @Nonnull
    public abstract byte[] decryptAttachmentSingleKey(@Nonnull byte[] key, @Nonnull byte[] data, @Nonnull String privateKey, @Nonnull String passphras);

    @Nonnull
    public abstract byte[] decryptAttachmentWithPassword(@Nonnull byte[] key, @Nonnull byte[] data, @Nonnull String password);

    @Nonnull
    public abstract byte[] getPublicKeySessionKey(@Nonnull byte[] keyPackage, @Nonnull String privateKey, @Nonnull String passphrase);

    @Nonnull
    public abstract byte[] getSymmetricSessionKey(@Nonnull byte[] keyPackage, @Nonnull String password);

    @Nonnull
    public abstract byte[] getNewPublicKeyPackage(@Nonnull byte[] session, @Nonnull String publicKey);

    @Nonnull
    public abstract byte[] getNewSymmetricKeyPackage(@Nonnull byte[] session, @Nonnull String password);

    @Nonnull
    public abstract String encryptMessageAes(@Nonnull String plainText, @Nonnull String password);

    @Nonnull
    public abstract String decryptMessageAes(@Nonnull String encryptedMessage, @Nonnull String password);

    @Nonnull
    public abstract String encryptMailboxPwd(@Nonnull String unencryptedPwd, @Nonnull String salt);

    @Nonnull
    public abstract String decryptMailboxPwd(@Nonnull String encryptedPwd, @Nonnull String salt);

    @CheckForNull
    public static native OpenPgp createInstance();

    @CheckForNull
    public static native OpenPgp createInstanceWithKeys(@Nonnull Address address);

    private static final class CppProxy extends OpenPgp
    {
        private final long nativeRef;
        private final AtomicBoolean destroyed = new AtomicBoolean(false);

        private CppProxy(long nativeRef)
        {
            if (nativeRef == 0) throw new RuntimeException("nativeRef is zero");
            this.nativeRef = nativeRef;
        }

        private native void nativeDestroy(long nativeRef);
        public void destroy()
        {
            boolean destroyed = this.destroyed.getAndSet(true);
            if (!destroyed) nativeDestroy(this.nativeRef);
        }
        protected void finalize() throws java.lang.Throwable
        {
            destroy();
            super.finalize();
        }

        @Override
        public boolean addAddress(Address address)
        {
            assert !this.destroyed.get() : "trying to use a destroyed object";
            return native_addAddress(this.nativeRef, address);
        }
        private native boolean native_addAddress(long _nativeRef, Address address);

        @Override
        public boolean removeAddress(String addressId)
        {
            assert !this.destroyed.get() : "trying to use a destroyed object";
            return native_removeAddress(this.nativeRef, addressId);
        }
        private native boolean native_removeAddress(long _nativeRef, String addressId);

        @Override
        public boolean cleanAddresses()
        {
            assert !this.destroyed.get() : "trying to use a destroyed object";
            return native_cleanAddresses(this.nativeRef);
        }
        private native boolean native_cleanAddresses(long _nativeRef);

        @Override
        public void enableDebug(boolean isDebug)
        {
            assert !this.destroyed.get() : "trying to use a destroyed object";
            native_enableDebug(this.nativeRef, isDebug);
        }
        private native void native_enableDebug(long _nativeRef, boolean isDebug);

        @Override
        public OpenPgpKey generateKey(String userName, String domain, String passphrase)
        {
            assert !this.destroyed.get() : "trying to use a destroyed object";
            return native_generateKey(this.nativeRef, userName, domain, passphrase);
        }
        private native OpenPgpKey native_generateKey(long _nativeRef, String userName, String domain, String passphrase);

        @Override
        public boolean checkPassphrase(String privateKey, String passphrase)
        {
            assert !this.destroyed.get() : "trying to use a destroyed object";
            return native_checkPassphrase(this.nativeRef, privateKey, passphrase);
        }
        private native boolean native_checkPassphrase(long _nativeRef, String privateKey, String passphrase);

        @Override
        public String updateSinglePassphrase(String privateKey, String oldPassphrase, String newPassphrase)
        {
            assert !this.destroyed.get() : "trying to use a destroyed object";
            return native_updateSinglePassphrase(this.nativeRef, privateKey, oldPassphrase, newPassphrase);
        }
        private native String native_updateSinglePassphrase(long _nativeRef, String privateKey, String oldPassphrase, String newPassphrase);

        @Override
        public void updatePrivateInfo(String privateKey)
        {
            assert !this.destroyed.get() : "trying to use a destroyed object";
            native_updatePrivateInfo(this.nativeRef, privateKey);
        }
        private native void native_updatePrivateInfo(long _nativeRef, String privateKey);

        @Override
        public String encryptMessage(String addressId, String plainText)
        {
            assert !this.destroyed.get() : "trying to use a destroyed object";
            return native_encryptMessage(this.nativeRef, addressId, plainText);
        }
        private native String native_encryptMessage(long _nativeRef, String addressId, String plainText);

        @Override
        public String encryptMessageSingleKey(String publicKey, String plainText)
        {
            assert !this.destroyed.get() : "trying to use a destroyed object";
            return native_encryptMessageSingleKey(this.nativeRef, publicKey, plainText);
        }
        private native String native_encryptMessageSingleKey(long _nativeRef, String publicKey, String plainText);

        @Override
        public String decryptMessage(String encryptText, String passphras)
        {
            assert !this.destroyed.get() : "trying to use a destroyed object";
            return native_decryptMessage(this.nativeRef, encryptText, passphras);
        }
        private native String native_decryptMessage(long _nativeRef, String encryptText, String passphras);

        @Override
        public String decryptMessageSingleKey(String encryptText, String privateKey, String passphras)
        {
            assert !this.destroyed.get() : "trying to use a destroyed object";
            return native_decryptMessageSingleKey(this.nativeRef, encryptText, privateKey, passphras);
        }
        private native String native_decryptMessageSingleKey(long _nativeRef, String encryptText, String privateKey, String passphras);

        @Override
        public EncryptPackage encryptAttachment(String addressId, byte[] unencryptData, String fileName)
        {
            assert !this.destroyed.get() : "trying to use a destroyed object";
            return native_encryptAttachment(this.nativeRef, addressId, unencryptData, fileName);
        }
        private native EncryptPackage native_encryptAttachment(long _nativeRef, String addressId, byte[] unencryptData, String fileName);

        @Override
        public EncryptPackage encryptAttachmentSingleKey(String publicKey, byte[] unencryptData, String fileName)
        {
            assert !this.destroyed.get() : "trying to use a destroyed object";
            return native_encryptAttachmentSingleKey(this.nativeRef, publicKey, unencryptData, fileName);
        }
        private native EncryptPackage native_encryptAttachmentSingleKey(long _nativeRef, String publicKey, byte[] unencryptData, String fileName);

        @Override
        public byte[] decryptAttachment(byte[] key, byte[] data, String passphras)
        {
            assert !this.destroyed.get() : "trying to use a destroyed object";
            return native_decryptAttachment(this.nativeRef, key, data, passphras);
        }
        private native byte[] native_decryptAttachment(long _nativeRef, byte[] key, byte[] data, String passphras);

        @Override
        public byte[] decryptAttachmentSingleKey(byte[] key, byte[] data, String privateKey, String passphras)
        {
            assert !this.destroyed.get() : "trying to use a destroyed object";
            return native_decryptAttachmentSingleKey(this.nativeRef, key, data, privateKey, passphras);
        }
        private native byte[] native_decryptAttachmentSingleKey(long _nativeRef, byte[] key, byte[] data, String privateKey, String passphras);

        @Override
        public byte[] decryptAttachmentWithPassword(byte[] key, byte[] data, String password)
        {
            assert !this.destroyed.get() : "trying to use a destroyed object";
            return native_decryptAttachmentWithPassword(this.nativeRef, key, data, password);
        }
        private native byte[] native_decryptAttachmentWithPassword(long _nativeRef, byte[] key, byte[] data, String password);

        @Override
        public byte[] getPublicKeySessionKey(byte[] keyPackage, String privateKey, String passphrase)
        {
            assert !this.destroyed.get() : "trying to use a destroyed object";
            return native_getPublicKeySessionKey(this.nativeRef, keyPackage, privateKey, passphrase);
        }
        private native byte[] native_getPublicKeySessionKey(long _nativeRef, byte[] keyPackage, String privateKey, String passphrase);

        @Override
        public byte[] getSymmetricSessionKey(byte[] keyPackage, String password)
        {
            assert !this.destroyed.get() : "trying to use a destroyed object";
            return native_getSymmetricSessionKey(this.nativeRef, keyPackage, password);
        }
        private native byte[] native_getSymmetricSessionKey(long _nativeRef, byte[] keyPackage, String password);

        @Override
        public byte[] getNewPublicKeyPackage(byte[] session, String publicKey)
        {
            assert !this.destroyed.get() : "trying to use a destroyed object";
            return native_getNewPublicKeyPackage(this.nativeRef, session, publicKey);
        }
        private native byte[] native_getNewPublicKeyPackage(long _nativeRef, byte[] session, String publicKey);

        @Override
        public byte[] getNewSymmetricKeyPackage(byte[] session, String password)
        {
            assert !this.destroyed.get() : "trying to use a destroyed object";
            return native_getNewSymmetricKeyPackage(this.nativeRef, session, password);
        }
        private native byte[] native_getNewSymmetricKeyPackage(long _nativeRef, byte[] session, String password);

        @Override
        public String encryptMessageAes(String plainText, String password)
        {
            assert !this.destroyed.get() : "trying to use a destroyed object";
            return native_encryptMessageAes(this.nativeRef, plainText, password);
        }
        private native String native_encryptMessageAes(long _nativeRef, String plainText, String password);

        @Override
        public String decryptMessageAes(String encryptedMessage, String password)
        {
            assert !this.destroyed.get() : "trying to use a destroyed object";
            return native_decryptMessageAes(this.nativeRef, encryptedMessage, password);
        }
        private native String native_decryptMessageAes(long _nativeRef, String encryptedMessage, String password);

        @Override
        public String encryptMailboxPwd(String unencryptedPwd, String salt)
        {
            assert !this.destroyed.get() : "trying to use a destroyed object";
            return native_encryptMailboxPwd(this.nativeRef, unencryptedPwd, salt);
        }
        private native String native_encryptMailboxPwd(long _nativeRef, String unencryptedPwd, String salt);

        @Override
        public String decryptMailboxPwd(String encryptedPwd, String salt)
        {
            assert !this.destroyed.get() : "trying to use a destroyed object";
            return native_decryptMailboxPwd(this.nativeRef, encryptedPwd, salt);
        }
        private native String native_decryptMailboxPwd(long _nativeRef, String encryptedPwd, String salt);
    }
}
