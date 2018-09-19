//
//  vcard.hpp
//  OpenPGP
//
//  Created by Yanfeng Zhang on 12/2/16.
//  Copyright © 2016 Yanfeng Zhang. All rights reserved.
//

#ifndef vcard_hpp
#define vcard_hpp

#include <string>
#include <map>
#include <vector>

#include <bridge/i_v_card.hpp>
#include "vcard_version.hpp"
#include <ezvcard/property/vcard_property.hpp>
#include "raw_property.hpp"
#include "formatted_name.hpp"
#include "email.hpp"
#include "mailer.hpp"
#include "photo.hpp"
#include "structured_name.hpp"
#include "organization.hpp"
#include "address_property.hpp"
#include "telephone.hpp"
#include "url.hpp"
#include "uid.hpp"
#include "title.hpp"
#include "key.hpp"
#include "note.hpp"
#include "nick_name.hpp"
#include "birthday.hpp"
#include "pm_encrypt_property.hpp"
#include "pm_sign_property.hpp"
#include "pm_custom_property.hpp"
#include "pm_scheme_property.hpp"
#include "pm_mimetype_property.hpp"
#include "gender.hpp"
#include "categories.hpp"


namespace ezvcard {
    
    class VCard : public ProtonMail::IVCard {
        
    private:
        VCardVersion::Ptr _version;
        ListMultimap<std::string, VCardProperty::Ptr> _properties = ListMultimap<std::string, VCardProperty::Ptr>();
        
    public:
        typedef std::shared_ptr<VCard> Ptr;
        
        VCard();
        VCard(VCardVersion::Ptr version);
        //VCard(const VCard::Ptr& original);
        
        void setVersion(const VCardVersion::Ptr& version);
        std::vector<VCardProperty::Ptr> getProperties();
        void addProperty(const VCardProperty::Ptr& property);
        std::vector<VCardProperty::Ptr> setProperty(const VCardProperty::Ptr& property);
        std::vector<VCardProperty::Ptr> setProperty(const std::string& className, const VCardProperty::Ptr& property);
        std::vector<VCardProperty::Ptr> setProperty(const std::string& className, const std::vector<VCardProperty::Ptr>& properties);
        void clearProperties(const std::string& className);
        //    void clearProperty(const std::string& className)
        
        //    public String write() ;
        //    public void write(File file) throws IOException {
        //    public void write(OutputStream out) throws IOException {
        //    public void write(Writer writer) throws IOException {
        //    public String writeXml() {
        //    public void writeXml(File file) throws IOException, TransformerException {
        //    public void writeXml(OutputStream out) throws TransformerException {
        //    public void writeXml(Writer writer) throws TransformerException {
        //    public String writeHtml() {
        //    public void writeHtml(File file) throws IOException {
        //    public void writeHtml(OutputStream out) throws IOException {
        //    public void writeHtml(Writer writer) throws IOException {
        //    public String writeJson() {
        //    public void writeJson(File file) throws IOException {
        //    public void writeJson(OutputStream out) throws IOException {
        //    public void writeJson(Writer writer) throws IOException {
        
        
        //    public Kind getKind() {
        //    public void setKind(Kind kind) {
        //    public List<Member> getMembers() {
        //    public void addMember(Member member) {
        //    public void addMemberAlt(Member... altRepresentations) {
        //    public Profile getProfile() {
        //    public void setProfile(Profile profile) {
        //    public Classification getClassification() {
        //    public void setClassification(Classification classification) {
        //    public Classification setClassification(String classification) {
        //    public List<Source> getSources() {
        //    public void addSource(Source source) {
        //    public Source addSource(String source) {
        //    public void addSourceAlt(Source... altRepresentations) {
        //    public SourceDisplayText getSourceDisplayText() {
        //    public void setSourceDisplayText(SourceDisplayText sourceDisplayText) {
        //    public SourceDisplayText setSourceDisplayText(String sourceDisplayText) {
        //    public List<FormattedName> getFormattedNames() {
        
        RawProperty::Ptr getExtendedProperty();
        void setFormattedName(FormattedName::Ptr formattedName);
        
        //    public List<Organization> getOrganizations() {
        
        //    public void addAddress(Address address) {
        //    public void addAddressAlt(Address... altRepresentations) {
        
        //    public void setFormattedNameAlt(FormattedName... altRepresentations) {
        //    public void addFormattedNameAlt(FormattedName... altRepresentations) {
        //    public void addFormattedName(FormattedName formattedName) {
        //    public FormattedName setFormattedName(String formattedName) {
        //    public List<StructuredName> getStructuredNames() {
        
        //    public void setStructuredNameAlt(StructuredName... altRepresentations) {
        //    public void setStructuredName(StructuredName structuredName) {
        
        
        //    public void setNicknameAlt(Nickname... altRepresentations) {
        //    public void addNicknameAlt(Nickname... altRepresentations) {
        //    public void setNickname(Nickname nickname) {
        //    public void addNickname(Nickname nickname) {
        //    public Nickname setNickname(String... nicknames) {
        //    public SortString getSortString();
        
        Mailer::Ptr getMailer();
        void setMailer(Mailer::Ptr mailer);
        Mailer::Ptr setMailer(const std::string& mailer);
        
        //    public void setSortString(SortString sortString) {
        //    public SortString setSortString(String sortString) {
        
        std::vector<Title::Ptr> getTitles();
        std::shared_ptr<ITitle> getTitle();
        void addTitle(const Title::Ptr& title);
        void setTitle(const std::shared_ptr<ITitle> & title) final;
        void clearTitle() final;
//        Title::Ptr addTitle(const std::string& title);
        //    public void addTitleAlt(Title... altRepresentations) {
        
        //    public List<Role> getRoles() {
        //    public void addRole(Role role) {
        //    public Role addRole(String role) {
        //    public void addRoleAlt(Role... altRepresentations) {
        
        //    public List<Photo> getPhotos() {
        void addPhoto(Photo::Ptr photo);
        //    public void addPhotoAlt(Photo... altRepresentations) {
        
        //    public List<Logo> getLogos() {
        //    public void addLogo(Logo logo) {
        //    public void addLogoAlt(Logo... altRepresentations) {
        
        //    public List<Sound> getSounds() {
        //    public void addSound(Sound sound) {
        //    public void addSoundAlt(Sound... altRepresentations) {
        
        //    public List<Birthplace> getBirthplaces() {
        //    public Birthplace getBirthplace() {
        //    public void setBirthplaceAlt(Birthplace... altRepresentations) {
        //    public void setBirthplace(Birthplace birthplace) {
        
        //    public List<Deathplace> getDeathplaces() {
        //    public Deathplace getDeathplace() {
        //    public void setDeathplaceAlt(Deathplace... altRepresentations) {
        //    public void setDeathplace(Deathplace deathplace) {
        
        //    public List<Deathdate> getDeathdates() {
        //    public Deathdate getDeathdate() {
        //    public void setDeathdateAlt(Deathdate... altRepresentations) {
        //    public void setDeathdate(Deathdate deathdate) {

        //    public void setBirthdayAlt(Birthday... altRepresentations) {
        //    public void setBirthday(Birthday birthday) {
        
        //    public List<Anniversary> getAnniversaries() {
        //    public Anniversary getAnniversary() {
        //    public void setAnniversaryAlt(Anniversary... altRepresentations) {
        //    public void setAnniversary(Anniversary anniversary) {
        
        //    public Revision getRevision() {
        //    public void setRevision(Revision revision) {
        //    public Revision setRevision(Date rev) {
        
        //    public ProductId getProductId() {
        //    public void setProductId(ProductId productId) {
        //    public ProductId setProductId(String productId) {
        
        //    public List<Label> getOrphanedLabels() {
        //    public void addOrphanedLabel(Label label) {
        
        //    public List<Email> getEmails() {
        //    public void addEmail(Email email) {
        //    public Email addEmail(String email, EmailType... types) {
        //    public void addEmailAlt(Email... altRepresentations) {
        
        //    void addTelephoneNumber(Telephone telephoneNumber) {
        //    public Telephone addTelephoneNumber(String telephoneNumber, TelephoneType... types) {
        //    public void addTelephoneNumberAlt(Telephone... altRepresentations) {
        
        //    public void addUrl(Url url) {
        //    public Url addUrl(String url) {
        //    public void addUrlAlt(Url... altRepresentations) {
        
        //    Uid::Ptr getUid();

        //    public List<Timezone> getTimezones() {
        //    public Timezone getTimezone() {
        //    public void setTimezoneAlt(Timezone... altRepresentations) {
        //    public void addTimezoneAlt(Timezone... altRepresentations) {
        //    public void setTimezone(Timezone timezone) {
        //    public void addTimezone(Timezone timezone) {
        
        //    public List<Geo> getGeos() {
        //    public Geo getGeo() {
        //    public void setGeoAlt(Geo... altRepresentations) {
        //    public void addGeoAlt(Geo... altRepresentations) {
        //    public void setGeo(Geo geo) {
        //    public void addGeo(Geo geo) {
        //    public Geo setGeo(double latitude, double longitude) {
        
        //    public void setOrganizationAlt(Organization... altRepresentations) {
        //    public void addOrganizationAlt(Organization... altRepresentations) {
        //    public void setOrganization(Organization organization) {
        //    public void addOrganization(Organization organization) {
        //    public Organization setOrganization(String... departments) {
        //    public List<Categories> getCategoriesList() {
        //    public Categories getCategories() {
        //    public void setCategoriesAlt(Categories... altRepresentations) {
        //    public void addCategoriesAlt(Categories... altRepresentations) {
        //    public void setCategories(Categories categories) {
        //    public void addCategories(Categories categories) {
        //    public Categories setCategories(String... categories) {
        
        //    public Agent getAgent() {
        //    public void setAgent(Agent agent) {
        std::vector<Note::Ptr> getNotes();
        void addNote(const Note::Ptr& note);
//        Note::Ptr addNote(const std::string& note);
        //    public void addNoteAlt(Note... altRepresentations) {
        
        //    public List<Key> getKeys() {
        //    public void addKey(Key key) {
        //    public void addKeyAlt(Key... altRepresentations) {
        
        //    public List<Impp> getImpps() {
        //    public void addImpp(Impp impp) {
        //    public void addImppAlt(Impp... altRepresentations) {
        
        //    public List<Related> getRelations() {
        //    public void addRelated(Related related) {
        //    public void addRelatedAlt(Related... altRepresentations) {
        
        //    public List<Language> getLanguages() {
        //    public void addLanguage(Language language) {
        //    public Language addLanguage(String language) {
        //    public void addLanguageAlt(Language... altRepresentations) {
        
        //    public List<CalendarRequestUri> getCalendarRequestUris() {
        //    public void addCalendarRequestUri(CalendarRequestUri calendarRequestUri) {
        //    public void addCalendarRequestUriAlt(CalendarRequestUri... altRepresentations) {
        //    public List<CalendarUri> getCalendarUris() {
        //    public void addCalendarUri(CalendarUri calendarUri) {
        //    public void addCalendarUriAlt(CalendarUri... altRepresentations) {
        
        //    public List<FreeBusyUrl> getFbUrls() {
        //    public void addFbUrl(FreeBusyUrl fbUrl) {
        //    public void addFbUrlAlt(FreeBusyUrl... altRepresentations) {
        
        //    public List<ClientPidMap> getClientPidMaps() {
        //    public void addClientPidMap(ClientPidMap clientPidMap) {
        
        //    public List<Xml> getXmls() {
        //    public void addXml(Xml xml) {
        //    public void addXmlAlt(Xml... altRepresentations) {
        
        //    public List<Expertise> getExpertise() {
        //    public void addExpertise(Expertise expertise) {
        //    public Expertise addExpertise(String expertise) {
        //    public void addExpertiseAlt(Expertise... altRepresentations) {
        
        //    public List<Hobby> getHobbies() {
        //    public void addHobby(Hobby hobby) {
        //    public Hobby addHobby(String hobby) {
        //    public void addHobbyAlt(Hobby... altRepresentations) {
        
        //    public List<Interest> getInterests() {
        //    public void addInterest(Interest interest) {
        //    public Interest addInterest(String interest) {
        //    public void addInterestAlt(Interest... altRepresentations) {
        
        //    public List<OrgDirectory> getOrgDirectories() {
        //    public void addOrgDirectory(OrgDirectory orgDirectory) {
        //    public OrgDirectory addOrgDirectory(String orgDirectory) {
        //    public void addOrgDirectoryAlt(OrgDirectory... altRepresentations) {
        
        //    public <T extends VCardProperty & HasAltId> List<List<T>> getPropertiesAlt(Class<T> clazz) {
        
        //    public boolean removeProperty(VCardProperty property) {
        //    public <T extends VCardProperty> List<T> removeProperties(Class<T> clazz) {
        
        //    public List<RawProperty> getExtendedProperties(String name) {
        //    public List<RawProperty> getExtendedProperties() {
        //    public RawProperty addExtendedProperty(String name, String value) {
        //    public RawProperty addExtendedProperty(String name, String value, VCardDataType dataType) {
        //    public RawProperty setExtendedProperty(String name, String value) {
        //    public RawProperty setExtendedProperty(String name, String value, VCardDataType dataType) {
        
        //    public List<RawProperty> removeExtendedProperty(String name) {
        
        //    public <T extends VCardProperty & HasAltId> void addPropertyAlt(Class<T> propertyClass, T... altRepresentations) {
        //    public <T extends VCardProperty & HasAltId> void addPropertyAlt(Class<T> propertyClass, Collection<T> altRepresentations) {
        //    public <T extends VCardProperty & HasAltId> List<T> setPropertyAlt(Class<T> propertyClass, T... altRepresentations) {
        //    public <T extends VCardProperty & HasAltId> List<T> setPropertyAlt(Class<T> propertyClass, Collection<T> altRepresentations) {
        
        //    private static <T> List<T> castList(List<?> list, Class<T> castTo) {
        //    public ValidationWarnings validate(VCardVersion version) {
        //    public String toString() {
        //    public int hashCode() {
        //    public boolean equals(Object obj) {
        //    static <T extends HasAltId> String generateAltId(Collection<T> properties) {
        
    private:
        template<class FROM, class TO>
        std::vector<std::shared_ptr<TO>> getProperties() {
            auto className = FROM::CLASSNAME;
            return _properties.get<TO>(className);
        }
        
        //get vcardproperty based object
        template<class T>
        std::vector<std::shared_ptr<T>> getProperties() {
            static_assert(std::is_base_of<VCardProperty, T>::value, "getProperties<T>(): T must be extent of VCardProperty type :-(");
            auto className = T::CLASSNAME;
            return _properties.get<T>(className);
        }
        template<class T>
        std::shared_ptr<T> getProperty() {
            static_assert(std::is_base_of<VCardProperty, T>::value, "getProperty<T>(): T must be extent of VCardProperty type :-(");
            auto className = T::CLASSNAME;
            return std::dynamic_pointer_cast<T>(_properties.first(className));
        }
  
        //this for add function for bridge interface
        template<class B, class T>
        void addProperty(const std::shared_ptr<B>& property) {
            if (auto convertedObj = std::dynamic_pointer_cast<T>(property)) {
                addProperty(convertedObj);
            } else {
                //TODO::handle error later
            }
        }
        //this for add function for bridge interface
        template<class B, class T>
        void setProperty(const std::shared_ptr<B>& property) {
            if (auto convertedObj = std::dynamic_pointer_cast<T>(property)) {
                setProperty(convertedObj->className(), convertedObj);
            } else {
                //TODO::handle error later
            }
        }
        
        //this set function replace all exsiting with new list for bridge interface
        template<class B, class T>
        void setProperty(const std::vector<std::shared_ptr<B>> & properties) {
            static_assert(std::is_base_of<VCardProperty, T>::value, "getProperty<T>(): T must be extent of VCardProperty type :-(");
            auto className = T::CLASSNAME;
            std::vector<VCardProperty::Ptr> out;
            for (auto b : properties) {
                if (auto o = std::dynamic_pointer_cast<VCardProperty>(b)) {
                    out.push_back(o);
                }
            }
            if (out.size() > 0) {
                setProperty(className, out);
            }
            
        }
        
    public: //vcard bridge interface impl
        std::shared_ptr<IVCardVersion> getVersion() final;
        void setVersion(const std::shared_ptr<IVCardVersion> & version) final;
        
        std::vector<std::string> getPropertyTypes() final;
        
        std::shared_ptr<IFormattedName> getFormattedName() final;
        void setFormattedName(const std::shared_ptr<IFormattedName> & formattedName) final;
        void clearFormattedName() final;
        
        std::vector<std::shared_ptr<ITelephone>> getTelephoneNumbers() final;
        void addTelephone(const std::shared_ptr<ITelephone>& telephoneNumber) final;
        void setTelephones(const std::vector<std::shared_ptr<ITelephone>> & cells) final;
        void clearTelephones() final;
        
        std::vector<std::shared_ptr<IUrl>> getUrls() final;
        void addUrl(const std::shared_ptr<IUrl> & url) final;
        void setUrls(const std::vector<std::shared_ptr<IUrl>> & urls) final;
        void clearUrls() final;
        
        std::shared_ptr<IStructuredName> getStructuredName() final;
        void setStructuredName(const std::shared_ptr<IStructuredName> & name) final;
        void clearStructuredName() final;

        std::shared_ptr<IOrganization> getOrganization() final;
        void addOrganization(const std::shared_ptr<IOrganization>& organization) final;
        void setOrganizations(const std::vector<std::shared_ptr<IOrganization>> & orgs) final;
        void clearOrganizations() final;

        std::vector<std::shared_ptr<IAddress>> getAddresses() final;
        void addAddress(const std::shared_ptr<IAddress>& addr) final;
        void setAddresses(const std::vector<std::shared_ptr<IAddress>> & addrs) final;
        void clearAddresses() final;
        
        std::vector<std::shared_ptr<IEmail>> getEmails() final;
        void addEmail(const std::shared_ptr<IEmail> & email) final;
        void setEmails(const std::vector<std::shared_ptr<IEmail>> & emails) final;
        void clearEmails() final;

        std::vector<std::shared_ptr<IBirthday>> getBirthdays() final;
        Birthday::Ptr getBirthday();
        void addBirthday(const std::shared_ptr<IBirthday> & birthday) final;
        void setBirthdays(const std::vector<std::shared_ptr<IBirthday>> & birthdays) final;
        void clearBirthdays() final;
        
        //std::vector<std::shared_ptr<INickname>> getNicknames() final;
        //void setFormattedName(FormattedName::Ptr formattedName);
        //void setMailer(Mailer::Ptr mailer);
        std::shared_ptr<INickname> getNickname();
        void setNickname(const std::shared_ptr<INickname> & nickname) final;
        void clearNickname() final;
        
        std::shared_ptr<INote> getNote() final;
        void setNote(const std::shared_ptr<INote> & note) final;
        void clearNote() final;
        
        std::shared_ptr<IUid> getUid() final;
        void setUid(const Uid::Ptr & uid);
        void setUid(const std::shared_ptr<IUid> & uid) final;
        
        PMCustom::Ptr getPMCustom();
        std::vector<PMCustom::Ptr> getPMCustoms();
        std::vector<std::shared_ptr<IPMCustom>> getCustoms() final;
        void addCustom(const std::shared_ptr<IPMCustom> & custom) final;
        void setCustoms(const std::vector<std::shared_ptr<IPMCustom>> & customs) final;
        void clearCustoms() final;
        
        std::shared_ptr<IGender> getGender() final;
        void setGender(const std::shared_ptr<IGender>& gender) final;
        void clearGender() final;
        
        std::vector<std::shared_ptr<IKey>> getKeys(const std::string & group) final;
        void addKey(const std::shared_ptr<IKey> & key) final;
        void setKeys(const std::vector<std::shared_ptr<IKey>> & keys) final;
        void clearKeys() final;
        
        std::shared_ptr<IPMSign> getPMSign(const std::string & group) final;
        void addPMSign(const std::shared_ptr<IPMSign> & sign) final;
        void setPMSign(const std::shared_ptr<IPMSign> & sign) final;
        void clearPMSign();
        
        std::shared_ptr<IPMEncrypt> getPMEncrypt(const std::string & group) final;
        void addPMEncrypt(const std::shared_ptr<IPMEncrypt> & encrypt) final;
        void setPMEncrypt(const std::shared_ptr<IPMEncrypt> & encrypt) final;
        void clearPMEncrypt() final;
        
        std::shared_ptr<IPMScheme> getPMScheme(const std::string & group) final;
        void addPMScheme(const std::shared_ptr<IPMScheme> & scheme) final;
        void setPMScheme(const std::shared_ptr<IPMScheme> & scheme) final;
        void clearPMScheme() final;
        
        std::shared_ptr<IPMMimeType> getPMMimeType(const std::string & group) final;
        void addPMMimeType(const std::shared_ptr<IPMMimeType> & mimetype) final;
        void setPMMimeType(const std::shared_ptr<IPMMimeType> & mimetype) final;
        void clearPMMimeType() final;
        
        std::shared_ptr<ICategories> getCategories(const std::string & group) final;
        void addCategories(const std::shared_ptr<ICategories> & c) final;
        void setCategories(const std::shared_ptr<ICategories> & c) final;
        void clearCategories() final;

    };
    
}

#endif /* vcard_hpp */
