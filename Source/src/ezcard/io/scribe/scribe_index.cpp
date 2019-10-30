//
//  scribe_index.cpp
//  OpenPGP
//
//  Created by Yanfeng Zhang on 12/2/16.
//  Copyright © 2016 Yanfeng Zhang. All rights reserved.
//

#include "scribe_index.hpp"
#include <iostream>
#include <string>
#include <unordered_map>

#include "string_util.hpp"

#include "raw_property.hpp"

#include "formatted_name_scribe.hpp"
#include "email_scribe.hpp"
#include "product_id_scribe.hpp"
#include "raw_property_scribe.hpp"
#include "mailer_scribe.hpp"
#include "photo_scribe.hpp"
#include "structured_name_scribe.hpp"
#include "organization_scribe.hpp"
#include "address_scribe.hpp"
#include "telephone_scribe.hpp"
#include "uri_property_scribe.hpp"
#include "url_scribe.hpp"
#include "uid_scribe.hpp"
#include "title_scribe.hpp"
#include "note_scribe.hpp"
#include "nickname_scribe.hpp"
#include "birthday_scribe.hpp"
#include "pm_custom_scribe.hpp"
#include "gender_scribe.hpp"
#include "key_scribe.hpp"
#include "pm_encrypt_scribe.hpp"
#include "pm_sign_scribe.hpp"
#include "pm_scheme_scribe.hpp"
#include "pm_mime_type_scribe.hpp"
#include "categories_scribe.hpp"
////2.1, RFC 2426, RFC 6350
//!!!ScribeIndex::registerStandard(new AddressScribe());
//ScribeIndex::registerStandard(new AgentScribe());
//ScribeIndex::registerStandard(new AnniversaryScribe());
//!!!ScribeIndex::registerStandard(new BirthdayScribe());
//ScribeIndex::registerStandard(new CalendarRequestUriScribe());
//ScribeIndex::registerStandard(new CalendarUriScribe());
//ScribeIndex::registerStandard(new ClassificationScribe());
//ScribeIndex::registerStandard(new ClientPidMapScribe());
//!!!ScribeIndex::registerStandard(new EmailScribe());
//ScribeIndex::registerStandard(new FreeBusyUrlScribe());
//!!!ScribeIndex::registerStandard(std::make_shared<FormattedNameScribe>());
//ScribeIndex::registerStandard(new GenderScribe());
//ScribeIndex::registerStandard(new GeoScribe());
//ScribeIndex::registerStandard(new ImppScribe());
//ScribeIndex::registerStandard(new KindScribe());
//ScribeIndex::registerStandard(new LabelScribe());
//ScribeIndex::registerStandard(new LanguageScribe());
//ScribeIndex::registerStandard(new LogoScribe());
//!!!ScribeIndex::registerStandard(new MailerScribe());
//ScribeIndex::registerStandard(new MemberScribe());
//!!!ScribeIndex::registerStandard(new NicknameScribe());
//!!!ScribeIndex::registerStandard(new NoteScribe());
//!!!ScribeIndex::registerStandard(new OrganizationScribe());
//!!!ScribeIndex::registerStandard(new PhotoScribe());
//!!!ScribeIndex::registerStandard(new ProductIdScribe());
//ScribeIndex::registerStandard(new ProfileScribe());
//ScribeIndex::registerStandard(new RelatedScribe());
//ScribeIndex::registerStandard(new RevisionScribe());
//ScribeIndex::registerStandard(new RoleScribe());
//ScribeIndex::registerStandard(new SortStringScribe());
//ScribeIndex::registerStandard(new SoundScribe());
//ScribeIndex::registerStandard(new SourceDisplayTextScribe());
//ScribeIndex::registerStandard(new SourceScribe());
//!!!ScribeIndex::registerStandard(new StructuredNameScribe());
//!!!ScribeIndex::registerStandard(new TelephoneScribe());
//ScribeIndex::registerStandard(new TimezoneScribe());
//!!!ScribeIndex::registerStandard(new TitleScribe());
//ScribeIndex::registerStandard(new UidScribe());
//!!!ScribeIndex::registerStandard(new UrlScribe());
//
////RFC 6351
//ScribeIndex::registerStandard(new XmlScribe());
//
////RFC 6474
//ScribeIndex::registerStandard(new BirthplaceScribe());
//ScribeIndex::registerStandard(new DeathdateScribe());
//ScribeIndex::registerStandard(new DeathplaceScribe());
//
////RFC 6715
//ScribeIndex::registerStandard(new ExpertiseScribe());
//ScribeIndex::registerStandard(new OrgDirectoryScribe());
//ScribeIndex::registerStandard(new InterestScribe());
//ScribeIndex::registerStandard(new HobbyScribe());

namespace ezvcard {
    
    ScribeIndex::ScribeIndex() {
        registerStandard(std::make_shared<AddressScribe>());
        registerStandard(std::make_shared<BirthdayScribe>());
        registerStandard(std::make_shared<EmailScribe>());
        registerStandard(std::make_shared<FormattedNameScribe>());
        registerStandard(std::make_shared<GenderScribe>());
        registerStandard(std::make_shared<KeyScribe>());
        registerStandard(std::make_shared<MailerScribe>());
        registerStandard(std::make_shared<NicknameScribe>());
        registerStandard(std::make_shared<NoteScribe>());
        registerStandard(std::make_shared<OrganizationScribe>());
        registerStandard(std::make_shared<PhotoScribe>());
        registerStandard(std::make_shared<ProductIdScribe>());
        registerStandard(std::make_shared<StructuredNameScribe>());
        registerStandard(std::make_shared<TelephoneScribe>());
        registerStandard(std::make_shared<TitleScribe>());
        registerStandard(std::make_shared<UrlScribe>());
        registerStandard(std::make_shared<UidScribe>());
        registerStandard(std::make_shared<CategoriesScribe>());
        //
        registerExtended(std::make_shared<PMCustomScribe>());
        registerExtended(std::make_shared<PMEncryptScribe>());
        registerExtended(std::make_shared<PMSignScribe>());
        registerExtended(std::make_shared<PMSchemeScribe>());
        registerExtended(std::make_shared<PMMimeTypeScribe>());
        
        
    }
    
    ScribeIndex::~ScribeIndex() {
        
    }
    
    
    void ScribeIndex::registerStandard(const VCardPropertyScribe::Ptr& scribe) {
        auto upper_name = str_to_upper(scribe->getPropertyName());
        standardByName[upper_name] = scribe;
        
        auto class_name = scribe->className();
        standardByClass[class_name] = scribe;
        
        //standardByQName.put(scribe.getQName(), scribe);
    }
    
    void ScribeIndex::registerExtended(const VCardPropertyScribe::Ptr& scribe) {
        auto upper_name = str_to_upper(scribe->getPropertyName());
        extendedByName[upper_name] = scribe;
        
        auto class_name = scribe->className();
        extendedByClass[class_name] = scribe;
        
        //extendedByQName.put(scribe.getQName(), scribe);
    }
    
    /**
     * Gets a property scribe by name.
     * @param propertyName the property name (case-insensitive, e.g. "FN")
     * @return the property scribe or null if not found
     */
    VCardPropertyScribe::Ptr ScribeIndex::getPropertyScribe(const std::string& propertyName) {
        auto upper_propertyName = str_to_upper(propertyName);
        auto it = extendedByName.find(upper_propertyName);
        if (it != extendedByName.end()) {
            return it->second;
        }
        
        auto standard_it = standardByName.find(upper_propertyName);
        if (standard_it != standardByName.end()) {
            return standard_it->second;
        }
        
        return nullptr;
    }
    
    /**
     * Gets a property scribe by class.
     * @param clazz the property class
     * @return the property scribe or null if not found
     */
    
    VCardPropertyScribe::Ptr ScribeIndex::getPropertyScribe(const VCardProperty::Ptr& property) {
        if (RawProperty::Ptr raw = std::dynamic_pointer_cast<RawProperty>(property)) {
            return std::make_shared<RawPropertyScribe>(raw->getPropertyName());
        }
        return getPropertyScribe(property->getPropertyName());
    }
    
    
    //public VCardPropertyScribe<? extends VCardProperty> getPropertyScribe(Class<? extends VCardProperty> clazz) {
    //    VCardPropertyScribe<? extends VCardProperty> scribe = extendedByClass.get(clazz);
    //    if (scribe != null) {
    //        return scribe;
    //    }
    //
    //    return standardByClass.get(clazz);
    //}
    
    
    /**
     * Determines if a scribe exists for a given property instance.
     * @param property the property
     * @return true if a scribe exists, false if not
     */
    bool ScribeIndex::hasPropertyScribe(const VCardProperty::Ptr& property) {
        if (RawProperty::Ptr raw = std::dynamic_pointer_cast<RawProperty>(property)) {
            return true;
        }
        return getPropertyScribe(property->getPropertyName()) != nullptr;
    }
    
    
    //    /**
    //     * Gets the appropriate property scribe for a given property instance.
    //     * @param property the property instance
    //     * @return the property scribe or null if not found
    //     */
    //    public VCardPropertyScribe<? extends VCardProperty> getPropertyScribe(VCardProperty property) {
    //        if (property instanceof RawProperty) {
    //            RawProperty raw = (RawProperty) property;
    //            return new RawPropertyScribe(raw.getPropertyName());
    //        }
    //
    //        return getPropertyScribe(property.getClass());
    //    }
    //
    //    /**
    //     * Gets a property scribe by XML local name and namespace.
    //     * @param qname the XML local name and namespace
    //     * @return the property scribe or a {@link XmlScribe} if not found
    //     */
    //    public VCardPropertyScribe<? extends VCardProperty> getPropertyScribe(QName qname) {
    //        VCardPropertyScribe<? extends VCardProperty> scribe = extendedByQName.get(qname);
    //        if (scribe != null) {
    //            return scribe;
    //        }
    //
    //        scribe = standardByQName.get(qname);
    //        if (scribe != null) {
    //            return scribe;
    //        }
    //
    //        if (VCardVersion.V4_0.getXmlNamespace().equals(qname.getNamespaceURI())) {
    //            return new RawPropertyScribe(qname.getLocalPart().toUpperCase());
    //        }
    //
    //        return getPropertyScribe(Xml.class);
    //    }
    //
    //    /**
    //     * Registers a property scribe.
    //     * @param scribe the scribe to register
    //     */
    //    public void register(VCardPropertyScribe<? extends VCardProperty> scribe) {
    //        extendedByName.put(scribe.getPropertyName().toUpperCase(), scribe);
    //        extendedByClass.put(scribe.getPropertyClass(), scribe);
    //        extendedByQName.put(scribe.getQName(), scribe);
    //    }
    //
    //    /**
    //     * Unregisters a property scribe.
    //     * @param scribe the scribe to unregister
    //     */
    //    public void unregister(VCardPropertyScribe<? extends VCardProperty> scribe) {
    //        extendedByName.remove(scribe.getPropertyName().toUpperCase());
    //        extendedByClass.remove(scribe.getPropertyClass());
    //        extendedByQName.remove(scribe.getQName());
    //    }
    //
    
}
