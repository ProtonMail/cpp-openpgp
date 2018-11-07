// AUTOGENERATED FILE - DO NOT MODIFY!
// This file generated by Djinni from open_pgp.djinni

package ch.protonmail.android.utils.nativelib;

import java.util.concurrent.atomic.AtomicBoolean;
import javax.annotation.CheckForNull;
import javax.annotation.Nonnull;

public abstract class ITitle {
    @Nonnull
    public abstract String getTitle();

    @Nonnull
    public abstract String getType();

    @CheckForNull
    public static ITitle createInstance(@Nonnull String type, @Nonnull String value)
    {
        return CppProxy.createInstance(type,
                                       value);
    }

    private static final class CppProxy extends ITitle
    {
        private final long nativeRef;
        private final AtomicBoolean destroyed = new AtomicBoolean(false);

        private CppProxy(long nativeRef)
        {
            if (nativeRef == 0) throw new RuntimeException("nativeRef is zero");
            this.nativeRef = nativeRef;
        }

        private native void nativeDestroy(long nativeRef);
        public void _djinni_private_destroy()
        {
            boolean destroyed = this.destroyed.getAndSet(true);
            if (!destroyed) nativeDestroy(this.nativeRef);
        }
        protected void finalize() throws java.lang.Throwable
        {
            _djinni_private_destroy();
            super.finalize();
        }

        @Override
        public String getTitle()
        {
            assert !this.destroyed.get() : "trying to use a destroyed object";
            return native_getTitle(this.nativeRef);
        }
        private native String native_getTitle(long _nativeRef);

        @Override
        public String getType()
        {
            assert !this.destroyed.get() : "trying to use a destroyed object";
            return native_getType(this.nativeRef);
        }
        private native String native_getType(long _nativeRef);

        @CheckForNull
        public static native ITitle createInstance(@Nonnull String type, @Nonnull String value);
    }
}
