// AUTOGENERATED FILE - DO NOT MODIFY!
// This file generated by Djinni from open_pgp.djinni

package ch.protonmail.android.utils.nativelib;

import java.util.ArrayList;
import java.util.concurrent.atomic.AtomicBoolean;
import javax.annotation.CheckForNull;
import javax.annotation.Nonnull;

public abstract class IVCard {
    @Nonnull
    public abstract ArrayList<String> getPropertyTypes();

    @CheckForNull
    public abstract IVCardVersion getVersion();

    public abstract void setVersion(@CheckForNull IVCardVersion version);

    @CheckForNull
    public abstract IFormattedName getFormattedName();

    public abstract void setFormattedName(@CheckForNull IFormattedName formattedName);

    public abstract void clearFormattedName();

    @Nonnull
    public abstract ArrayList<ITelephone> getTelephoneNumbers();

    public abstract void addTelephone(@CheckForNull ITelephone cell);

    public abstract void setTelephones(@Nonnull ArrayList<ITelephone> cells);

    public abstract void clearTelephones();

    @Nonnull
    public abstract ArrayList<IEmail> getEmails();

    public abstract void addEmail(@CheckForNull IEmail email);

    /**set will replace all exsiting */
    public abstract void setEmails(@Nonnull ArrayList<IEmail> emails);

    public abstract void clearEmails();

    @Nonnull
    public abstract ArrayList<IKey> getKeys();

    public abstract void addKey(@CheckForNull IKey key);

    /**set will replace all exsiting */
    public abstract void setKeys(@Nonnull ArrayList<IKey> keys);

    public abstract void clearKeys();

    @CheckForNull
    public abstract IUid getUid();

    public abstract void setUid(@CheckForNull IUid uuid);

    @Nonnull
    public abstract ArrayList<IAddress> getAddresses();

    public abstract void addAddress(@CheckForNull IAddress addr);

    public abstract void setAddresses(@Nonnull ArrayList<IAddress> addrs);

    public abstract void clearAddresses();

    @CheckForNull
    public abstract IOrganization getOrganization();

    public abstract void addOrganization(@CheckForNull IOrganization org);

    public abstract void setOrganizations(@Nonnull ArrayList<IOrganization> orgs);

    public abstract void clearOrganizations();

    @CheckForNull
    public abstract INote getNote();

    public abstract void setNote(@CheckForNull INote note);

    public abstract void clearNote();

    @CheckForNull
    public abstract INickname getNickname();

    public abstract void setNickname(@CheckForNull INickname nickname);

    public abstract void clearNickname();

    @CheckForNull
    public abstract ITitle getTitle();

    public abstract void setTitle(@CheckForNull ITitle title);

    public abstract void clearTitle();

    @Nonnull
    public abstract ArrayList<IBirthday> getBirthdays();

    public abstract void addBirthday(@CheckForNull IBirthday birthday);

    public abstract void setBirthdays(@Nonnull ArrayList<IBirthday> birthdays);

    public abstract void clearBirthdays();

    @Nonnull
    public abstract ArrayList<IPMCustom> getCustoms();

    public abstract void addCustom(@CheckForNull IPMCustom custom);

    public abstract void setCustoms(@Nonnull ArrayList<IPMCustom> customs);

    public abstract void clearCustoms();

    @CheckForNull
    public abstract IPMSign getPMSign();

    public abstract void addPMSign(@CheckForNull IPMSign sign);

    public abstract void setPMSign(@CheckForNull IPMSign sign);

    public abstract void clearPMSign();

    @CheckForNull
    public abstract IPMEncrypt getPMEncrypt();

    public abstract void addPMEncrypt(@CheckForNull IPMEncrypt encrypt);

    public abstract void setPMEncrypt(@CheckForNull IPMEncrypt encrypt);

    public abstract void clearPMEncrypt();

    @CheckForNull
    public abstract IPMScheme getPMScheme();

    public abstract void addPMScheme(@CheckForNull IPMScheme scheme);

    public abstract void setPMScheme(@CheckForNull IPMScheme scheme);

    public abstract void clearPMScheme();

    @Nonnull
    public abstract ArrayList<IUrl> getUrls();

    public abstract void addUrl(@CheckForNull IUrl url);

    public abstract void setUrls(@Nonnull ArrayList<IUrl> urls);

    public abstract void clearUrls();

    @CheckForNull
    public abstract IGender getGender();

    public abstract void setGender(@CheckForNull IGender gender);

    public abstract void clearGender();

    @CheckForNull
    public abstract IStructuredName getStructuredName();

    public abstract void setStructuredName(@CheckForNull IStructuredName name);

    public abstract void clearStructuredName();

    @CheckForNull
    public static native IVCard createInstance();

    private static final class CppProxy extends IVCard
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
        public ArrayList<String> getPropertyTypes()
        {
            assert !this.destroyed.get() : "trying to use a destroyed object";
            return native_getPropertyTypes(this.nativeRef);
        }
        private native ArrayList<String> native_getPropertyTypes(long _nativeRef);

        @Override
        public IVCardVersion getVersion()
        {
            assert !this.destroyed.get() : "trying to use a destroyed object";
            return native_getVersion(this.nativeRef);
        }
        private native IVCardVersion native_getVersion(long _nativeRef);

        @Override
        public void setVersion(IVCardVersion version)
        {
            assert !this.destroyed.get() : "trying to use a destroyed object";
            native_setVersion(this.nativeRef, version);
        }
        private native void native_setVersion(long _nativeRef, IVCardVersion version);

        @Override
        public IFormattedName getFormattedName()
        {
            assert !this.destroyed.get() : "trying to use a destroyed object";
            return native_getFormattedName(this.nativeRef);
        }
        private native IFormattedName native_getFormattedName(long _nativeRef);

        @Override
        public void setFormattedName(IFormattedName formattedName)
        {
            assert !this.destroyed.get() : "trying to use a destroyed object";
            native_setFormattedName(this.nativeRef, formattedName);
        }
        private native void native_setFormattedName(long _nativeRef, IFormattedName formattedName);

        @Override
        public void clearFormattedName()
        {
            assert !this.destroyed.get() : "trying to use a destroyed object";
            native_clearFormattedName(this.nativeRef);
        }
        private native void native_clearFormattedName(long _nativeRef);

        @Override
        public ArrayList<ITelephone> getTelephoneNumbers()
        {
            assert !this.destroyed.get() : "trying to use a destroyed object";
            return native_getTelephoneNumbers(this.nativeRef);
        }
        private native ArrayList<ITelephone> native_getTelephoneNumbers(long _nativeRef);

        @Override
        public void addTelephone(ITelephone cell)
        {
            assert !this.destroyed.get() : "trying to use a destroyed object";
            native_addTelephone(this.nativeRef, cell);
        }
        private native void native_addTelephone(long _nativeRef, ITelephone cell);

        @Override
        public void setTelephones(ArrayList<ITelephone> cells)
        {
            assert !this.destroyed.get() : "trying to use a destroyed object";
            native_setTelephones(this.nativeRef, cells);
        }
        private native void native_setTelephones(long _nativeRef, ArrayList<ITelephone> cells);

        @Override
        public void clearTelephones()
        {
            assert !this.destroyed.get() : "trying to use a destroyed object";
            native_clearTelephones(this.nativeRef);
        }
        private native void native_clearTelephones(long _nativeRef);

        @Override
        public ArrayList<IEmail> getEmails()
        {
            assert !this.destroyed.get() : "trying to use a destroyed object";
            return native_getEmails(this.nativeRef);
        }
        private native ArrayList<IEmail> native_getEmails(long _nativeRef);

        @Override
        public void addEmail(IEmail email)
        {
            assert !this.destroyed.get() : "trying to use a destroyed object";
            native_addEmail(this.nativeRef, email);
        }
        private native void native_addEmail(long _nativeRef, IEmail email);

        @Override
        public void setEmails(ArrayList<IEmail> emails)
        {
            assert !this.destroyed.get() : "trying to use a destroyed object";
            native_setEmails(this.nativeRef, emails);
        }
        private native void native_setEmails(long _nativeRef, ArrayList<IEmail> emails);

        @Override
        public void clearEmails()
        {
            assert !this.destroyed.get() : "trying to use a destroyed object";
            native_clearEmails(this.nativeRef);
        }
        private native void native_clearEmails(long _nativeRef);

        @Override
        public ArrayList<IKey> getKeys()
        {
            assert !this.destroyed.get() : "trying to use a destroyed object";
            return native_getKeys(this.nativeRef);
        }
        private native ArrayList<IKey> native_getKeys(long _nativeRef);

        @Override
        public void addKey(IKey key)
        {
            assert !this.destroyed.get() : "trying to use a destroyed object";
            native_addKey(this.nativeRef, key);
        }
        private native void native_addKey(long _nativeRef, IKey key);

        @Override
        public void setKeys(ArrayList<IKey> keys)
        {
            assert !this.destroyed.get() : "trying to use a destroyed object";
            native_setKeys(this.nativeRef, keys);
        }
        private native void native_setKeys(long _nativeRef, ArrayList<IKey> keys);

        @Override
        public void clearKeys()
        {
            assert !this.destroyed.get() : "trying to use a destroyed object";
            native_clearKeys(this.nativeRef);
        }
        private native void native_clearKeys(long _nativeRef);

        @Override
        public IUid getUid()
        {
            assert !this.destroyed.get() : "trying to use a destroyed object";
            return native_getUid(this.nativeRef);
        }
        private native IUid native_getUid(long _nativeRef);

        @Override
        public void setUid(IUid uuid)
        {
            assert !this.destroyed.get() : "trying to use a destroyed object";
            native_setUid(this.nativeRef, uuid);
        }
        private native void native_setUid(long _nativeRef, IUid uuid);

        @Override
        public ArrayList<IAddress> getAddresses()
        {
            assert !this.destroyed.get() : "trying to use a destroyed object";
            return native_getAddresses(this.nativeRef);
        }
        private native ArrayList<IAddress> native_getAddresses(long _nativeRef);

        @Override
        public void addAddress(IAddress addr)
        {
            assert !this.destroyed.get() : "trying to use a destroyed object";
            native_addAddress(this.nativeRef, addr);
        }
        private native void native_addAddress(long _nativeRef, IAddress addr);

        @Override
        public void setAddresses(ArrayList<IAddress> addrs)
        {
            assert !this.destroyed.get() : "trying to use a destroyed object";
            native_setAddresses(this.nativeRef, addrs);
        }
        private native void native_setAddresses(long _nativeRef, ArrayList<IAddress> addrs);

        @Override
        public void clearAddresses()
        {
            assert !this.destroyed.get() : "trying to use a destroyed object";
            native_clearAddresses(this.nativeRef);
        }
        private native void native_clearAddresses(long _nativeRef);

        @Override
        public IOrganization getOrganization()
        {
            assert !this.destroyed.get() : "trying to use a destroyed object";
            return native_getOrganization(this.nativeRef);
        }
        private native IOrganization native_getOrganization(long _nativeRef);

        @Override
        public void addOrganization(IOrganization org)
        {
            assert !this.destroyed.get() : "trying to use a destroyed object";
            native_addOrganization(this.nativeRef, org);
        }
        private native void native_addOrganization(long _nativeRef, IOrganization org);

        @Override
        public void setOrganizations(ArrayList<IOrganization> orgs)
        {
            assert !this.destroyed.get() : "trying to use a destroyed object";
            native_setOrganizations(this.nativeRef, orgs);
        }
        private native void native_setOrganizations(long _nativeRef, ArrayList<IOrganization> orgs);

        @Override
        public void clearOrganizations()
        {
            assert !this.destroyed.get() : "trying to use a destroyed object";
            native_clearOrganizations(this.nativeRef);
        }
        private native void native_clearOrganizations(long _nativeRef);

        @Override
        public INote getNote()
        {
            assert !this.destroyed.get() : "trying to use a destroyed object";
            return native_getNote(this.nativeRef);
        }
        private native INote native_getNote(long _nativeRef);

        @Override
        public void setNote(INote note)
        {
            assert !this.destroyed.get() : "trying to use a destroyed object";
            native_setNote(this.nativeRef, note);
        }
        private native void native_setNote(long _nativeRef, INote note);

        @Override
        public void clearNote()
        {
            assert !this.destroyed.get() : "trying to use a destroyed object";
            native_clearNote(this.nativeRef);
        }
        private native void native_clearNote(long _nativeRef);

        @Override
        public INickname getNickname()
        {
            assert !this.destroyed.get() : "trying to use a destroyed object";
            return native_getNickname(this.nativeRef);
        }
        private native INickname native_getNickname(long _nativeRef);

        @Override
        public void setNickname(INickname nickname)
        {
            assert !this.destroyed.get() : "trying to use a destroyed object";
            native_setNickname(this.nativeRef, nickname);
        }
        private native void native_setNickname(long _nativeRef, INickname nickname);

        @Override
        public void clearNickname()
        {
            assert !this.destroyed.get() : "trying to use a destroyed object";
            native_clearNickname(this.nativeRef);
        }
        private native void native_clearNickname(long _nativeRef);

        @Override
        public ITitle getTitle()
        {
            assert !this.destroyed.get() : "trying to use a destroyed object";
            return native_getTitle(this.nativeRef);
        }
        private native ITitle native_getTitle(long _nativeRef);

        @Override
        public void setTitle(ITitle title)
        {
            assert !this.destroyed.get() : "trying to use a destroyed object";
            native_setTitle(this.nativeRef, title);
        }
        private native void native_setTitle(long _nativeRef, ITitle title);

        @Override
        public void clearTitle()
        {
            assert !this.destroyed.get() : "trying to use a destroyed object";
            native_clearTitle(this.nativeRef);
        }
        private native void native_clearTitle(long _nativeRef);

        @Override
        public ArrayList<IBirthday> getBirthdays()
        {
            assert !this.destroyed.get() : "trying to use a destroyed object";
            return native_getBirthdays(this.nativeRef);
        }
        private native ArrayList<IBirthday> native_getBirthdays(long _nativeRef);

        @Override
        public void addBirthday(IBirthday birthday)
        {
            assert !this.destroyed.get() : "trying to use a destroyed object";
            native_addBirthday(this.nativeRef, birthday);
        }
        private native void native_addBirthday(long _nativeRef, IBirthday birthday);

        @Override
        public void setBirthdays(ArrayList<IBirthday> birthdays)
        {
            assert !this.destroyed.get() : "trying to use a destroyed object";
            native_setBirthdays(this.nativeRef, birthdays);
        }
        private native void native_setBirthdays(long _nativeRef, ArrayList<IBirthday> birthdays);

        @Override
        public void clearBirthdays()
        {
            assert !this.destroyed.get() : "trying to use a destroyed object";
            native_clearBirthdays(this.nativeRef);
        }
        private native void native_clearBirthdays(long _nativeRef);

        @Override
        public ArrayList<IPMCustom> getCustoms()
        {
            assert !this.destroyed.get() : "trying to use a destroyed object";
            return native_getCustoms(this.nativeRef);
        }
        private native ArrayList<IPMCustom> native_getCustoms(long _nativeRef);

        @Override
        public void addCustom(IPMCustom custom)
        {
            assert !this.destroyed.get() : "trying to use a destroyed object";
            native_addCustom(this.nativeRef, custom);
        }
        private native void native_addCustom(long _nativeRef, IPMCustom custom);

        @Override
        public void setCustoms(ArrayList<IPMCustom> customs)
        {
            assert !this.destroyed.get() : "trying to use a destroyed object";
            native_setCustoms(this.nativeRef, customs);
        }
        private native void native_setCustoms(long _nativeRef, ArrayList<IPMCustom> customs);

        @Override
        public void clearCustoms()
        {
            assert !this.destroyed.get() : "trying to use a destroyed object";
            native_clearCustoms(this.nativeRef);
        }
        private native void native_clearCustoms(long _nativeRef);

        @Override
        public IPMSign getPMSign()
        {
            assert !this.destroyed.get() : "trying to use a destroyed object";
            return native_getPMSign(this.nativeRef);
        }
        private native IPMSign native_getPMSign(long _nativeRef);

        @Override
        public void addPMSign(IPMSign sign)
        {
            assert !this.destroyed.get() : "trying to use a destroyed object";
            native_addPMSign(this.nativeRef, sign);
        }
        private native void native_addPMSign(long _nativeRef, IPMSign sign);

        @Override
        public void setPMSign(IPMSign sign)
        {
            assert !this.destroyed.get() : "trying to use a destroyed object";
            native_setPMSign(this.nativeRef, sign);
        }
        private native void native_setPMSign(long _nativeRef, IPMSign sign);

        @Override
        public void clearPMSign()
        {
            assert !this.destroyed.get() : "trying to use a destroyed object";
            native_clearPMSign(this.nativeRef);
        }
        private native void native_clearPMSign(long _nativeRef);

        @Override
        public IPMEncrypt getPMEncrypt()
        {
            assert !this.destroyed.get() : "trying to use a destroyed object";
            return native_getPMEncrypt(this.nativeRef);
        }
        private native IPMEncrypt native_getPMEncrypt(long _nativeRef);

        @Override
        public void addPMEncrypt(IPMEncrypt encrypt)
        {
            assert !this.destroyed.get() : "trying to use a destroyed object";
            native_addPMEncrypt(this.nativeRef, encrypt);
        }
        private native void native_addPMEncrypt(long _nativeRef, IPMEncrypt encrypt);

        @Override
        public void setPMEncrypt(IPMEncrypt encrypt)
        {
            assert !this.destroyed.get() : "trying to use a destroyed object";
            native_setPMEncrypt(this.nativeRef, encrypt);
        }
        private native void native_setPMEncrypt(long _nativeRef, IPMEncrypt encrypt);

        @Override
        public void clearPMEncrypt()
        {
            assert !this.destroyed.get() : "trying to use a destroyed object";
            native_clearPMEncrypt(this.nativeRef);
        }
        private native void native_clearPMEncrypt(long _nativeRef);

        @Override
        public IPMScheme getPMScheme()
        {
            assert !this.destroyed.get() : "trying to use a destroyed object";
            return native_getPMScheme(this.nativeRef);
        }
        private native IPMScheme native_getPMScheme(long _nativeRef);

        @Override
        public void addPMScheme(IPMScheme scheme)
        {
            assert !this.destroyed.get() : "trying to use a destroyed object";
            native_addPMScheme(this.nativeRef, scheme);
        }
        private native void native_addPMScheme(long _nativeRef, IPMScheme scheme);

        @Override
        public void setPMScheme(IPMScheme scheme)
        {
            assert !this.destroyed.get() : "trying to use a destroyed object";
            native_setPMScheme(this.nativeRef, scheme);
        }
        private native void native_setPMScheme(long _nativeRef, IPMScheme scheme);

        @Override
        public void clearPMScheme()
        {
            assert !this.destroyed.get() : "trying to use a destroyed object";
            native_clearPMScheme(this.nativeRef);
        }
        private native void native_clearPMScheme(long _nativeRef);

        @Override
        public ArrayList<IUrl> getUrls()
        {
            assert !this.destroyed.get() : "trying to use a destroyed object";
            return native_getUrls(this.nativeRef);
        }
        private native ArrayList<IUrl> native_getUrls(long _nativeRef);

        @Override
        public void addUrl(IUrl url)
        {
            assert !this.destroyed.get() : "trying to use a destroyed object";
            native_addUrl(this.nativeRef, url);
        }
        private native void native_addUrl(long _nativeRef, IUrl url);

        @Override
        public void setUrls(ArrayList<IUrl> urls)
        {
            assert !this.destroyed.get() : "trying to use a destroyed object";
            native_setUrls(this.nativeRef, urls);
        }
        private native void native_setUrls(long _nativeRef, ArrayList<IUrl> urls);

        @Override
        public void clearUrls()
        {
            assert !this.destroyed.get() : "trying to use a destroyed object";
            native_clearUrls(this.nativeRef);
        }
        private native void native_clearUrls(long _nativeRef);

        @Override
        public IGender getGender()
        {
            assert !this.destroyed.get() : "trying to use a destroyed object";
            return native_getGender(this.nativeRef);
        }
        private native IGender native_getGender(long _nativeRef);

        @Override
        public void setGender(IGender gender)
        {
            assert !this.destroyed.get() : "trying to use a destroyed object";
            native_setGender(this.nativeRef, gender);
        }
        private native void native_setGender(long _nativeRef, IGender gender);

        @Override
        public void clearGender()
        {
            assert !this.destroyed.get() : "trying to use a destroyed object";
            native_clearGender(this.nativeRef);
        }
        private native void native_clearGender(long _nativeRef);

        @Override
        public IStructuredName getStructuredName()
        {
            assert !this.destroyed.get() : "trying to use a destroyed object";
            return native_getStructuredName(this.nativeRef);
        }
        private native IStructuredName native_getStructuredName(long _nativeRef);

        @Override
        public void setStructuredName(IStructuredName name)
        {
            assert !this.destroyed.get() : "trying to use a destroyed object";
            native_setStructuredName(this.nativeRef, name);
        }
        private native void native_setStructuredName(long _nativeRef, IStructuredName name);

        @Override
        public void clearStructuredName()
        {
            assert !this.destroyed.get() : "trying to use a destroyed object";
            native_clearStructuredName(this.nativeRef);
        }
        private native void native_clearStructuredName(long _nativeRef);
    }
}
