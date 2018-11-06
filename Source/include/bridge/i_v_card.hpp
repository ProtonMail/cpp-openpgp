// AUTOGENERATED FILE - DO NOT MODIFY!
// This file generated by Djinni from open_pgp.djinni

#pragma once

#include <memory>
#include <string>
#include <vector>

namespace ProtonMail {

class IAddress;
class IBirthday;
class ICategories;
class IEmail;
class IFormattedName;
class IGender;
class IKey;
class INickname;
class INote;
class IOrganization;
class IPMCustom;
class IPMEncrypt;
class IPMMimeType;
class IPMScheme;
class IPMSign;
class IPhoto;
class IStructuredName;
class ITelephone;
class ITitle;
class IUid;
class IUrl;
class IVCardVersion;

class IVCard {
public:
    virtual ~IVCard() {}

    virtual std::vector<std::string> getPropertyTypes() = 0;

    virtual std::shared_ptr<IVCardVersion> getVersion() = 0;

    virtual void setVersion(const std::shared_ptr<IVCardVersion> & version) = 0;

    virtual std::shared_ptr<IFormattedName> getFormattedName() = 0;

    virtual void setFormattedName(const std::shared_ptr<IFormattedName> & formattedName) = 0;

    virtual void clearFormattedName() = 0;

    virtual std::vector<std::shared_ptr<ITelephone>> getTelephoneNumbers() = 0;

    virtual void addTelephone(const std::shared_ptr<ITelephone> & cell) = 0;

    virtual void setTelephones(const std::vector<std::shared_ptr<ITelephone>> & cells) = 0;

    virtual void clearTelephones() = 0;

    virtual std::vector<std::shared_ptr<IEmail>> getEmails() = 0;

    virtual void addEmail(const std::shared_ptr<IEmail> & email) = 0;

    /**set will replace all exsiting */
    virtual void setEmails(const std::vector<std::shared_ptr<IEmail>> & emails) = 0;

    virtual void clearEmails() = 0;

    virtual std::shared_ptr<IUid> getUid() = 0;

    virtual void setUid(const std::shared_ptr<IUid> & uuid) = 0;

    virtual std::vector<std::shared_ptr<IAddress>> getAddresses() = 0;

    virtual void addAddress(const std::shared_ptr<IAddress> & addr) = 0;

    virtual void setAddresses(const std::vector<std::shared_ptr<IAddress>> & addrs) = 0;

    virtual void clearAddresses() = 0;

    virtual std::shared_ptr<IOrganization> getOrganization() = 0;

    virtual void addOrganization(const std::shared_ptr<IOrganization> & org) = 0;

    virtual void setOrganizations(const std::vector<std::shared_ptr<IOrganization>> & orgs) = 0;

    virtual void clearOrganizations() = 0;

    virtual std::shared_ptr<INote> getNote() = 0;

    virtual void setNote(const std::shared_ptr<INote> & note) = 0;

    virtual void clearNote() = 0;

    virtual std::shared_ptr<INickname> getNickname() = 0;

    virtual void setNickname(const std::shared_ptr<INickname> & nickname) = 0;

    virtual void clearNickname() = 0;

    virtual std::shared_ptr<ITitle> getTitle() = 0;

    virtual void setTitle(const std::shared_ptr<ITitle> & title) = 0;

    virtual void clearTitle() = 0;

    virtual std::vector<std::shared_ptr<IBirthday>> getBirthdays() = 0;

    virtual void addBirthday(const std::shared_ptr<IBirthday> & birthday) = 0;

    virtual void setBirthdays(const std::vector<std::shared_ptr<IBirthday>> & birthdays) = 0;

    virtual void clearBirthdays() = 0;

    virtual std::vector<std::shared_ptr<IPMCustom>> getCustoms() = 0;

    virtual void addCustom(const std::shared_ptr<IPMCustom> & custom) = 0;

    virtual void setCustoms(const std::vector<std::shared_ptr<IPMCustom>> & customs) = 0;

    virtual void clearCustoms() = 0;

    virtual std::shared_ptr<IPMSign> getPMSign(const std::string & group) = 0;

    virtual void addPMSign(const std::shared_ptr<IPMSign> & sign) = 0;

    virtual void setPMSign(const std::shared_ptr<IPMSign> & sign) = 0;

    virtual void clearPMSign() = 0;

    virtual std::shared_ptr<IPMEncrypt> getPMEncrypt(const std::string & group) = 0;

    virtual void addPMEncrypt(const std::shared_ptr<IPMEncrypt> & encrypt) = 0;

    virtual void setPMEncrypt(const std::shared_ptr<IPMEncrypt> & encrypt) = 0;

    virtual void clearPMEncrypt() = 0;

    virtual std::shared_ptr<IPMScheme> getPMScheme(const std::string & group) = 0;

    virtual void addPMScheme(const std::shared_ptr<IPMScheme> & scheme) = 0;

    virtual void setPMScheme(const std::shared_ptr<IPMScheme> & scheme) = 0;

    virtual void clearPMScheme() = 0;

    virtual std::shared_ptr<IPMMimeType> getPMMimeType(const std::string & group) = 0;

    virtual void addPMMimeType(const std::shared_ptr<IPMMimeType> & mimetype) = 0;

    virtual void setPMMimeType(const std::shared_ptr<IPMMimeType> & mimetype) = 0;

    virtual void clearPMMimeType() = 0;

    virtual std::vector<std::shared_ptr<IKey>> getKeys(const std::string & group) = 0;

    virtual void addKey(const std::shared_ptr<IKey> & key) = 0;

    /**set will replace all exsiting */
    virtual void setKeys(const std::vector<std::shared_ptr<IKey>> & keys) = 0;

    virtual void clearKeys() = 0;

    virtual std::shared_ptr<ICategories> getCategories(const std::string & group) = 0;

    virtual void addCategories(const std::shared_ptr<ICategories> & c) = 0;

    virtual void setCategories(const std::shared_ptr<ICategories> & c) = 0;

    virtual void clearCategories() = 0;

    virtual std::shared_ptr<IPhoto> getPhoto() = 0;

    virtual void setPhoto(const std::shared_ptr<IPhoto> & photo) = 0;

    virtual void clearPhotos() = 0;

    virtual std::vector<std::shared_ptr<IUrl>> getUrls() = 0;

    virtual void addUrl(const std::shared_ptr<IUrl> & url) = 0;

    virtual void setUrls(const std::vector<std::shared_ptr<IUrl>> & urls) = 0;

    virtual void clearUrls() = 0;

    virtual std::shared_ptr<IGender> getGender() = 0;

    virtual void setGender(const std::shared_ptr<IGender> & gender) = 0;

    virtual void clearGender() = 0;

    virtual std::shared_ptr<IStructuredName> getStructuredName() = 0;

    virtual void setStructuredName(const std::shared_ptr<IStructuredName> & name) = 0;

    virtual void clearStructuredName() = 0;

    static std::shared_ptr<IVCard> create_instance();
};

}  // namespace ProtonMail
