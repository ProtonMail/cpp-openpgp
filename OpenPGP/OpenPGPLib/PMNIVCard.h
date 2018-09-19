// AUTOGENERATED FILE - DO NOT MODIFY!
// This file generated by Djinni from open_pgp.djinni

#import <Foundation/Foundation.h>
@class PMNIAddress;
@class PMNIBirthday;
@class PMNICategories;
@class PMNIEmail;
@class PMNIFormattedName;
@class PMNIGender;
@class PMNIKey;
@class PMNINickname;
@class PMNINote;
@class PMNIOrganization;
@class PMNIPMCustom;
@class PMNIPMEncrypt;
@class PMNIPMMimeType;
@class PMNIPMScheme;
@class PMNIPMSign;
@class PMNIStructuredName;
@class PMNITelephone;
@class PMNITitle;
@class PMNIUid;
@class PMNIUrl;
@class PMNIVCard;
@class PMNIVCardVersion;


@interface PMNIVCard : NSObject

- (nonnull NSArray<NSString *> *)getPropertyTypes;

- (nullable PMNIVCardVersion *)getVersion;

- (void)setVersion:(nullable PMNIVCardVersion *)version;

- (nullable PMNIFormattedName *)getFormattedName;

- (void)setFormattedName:(nullable PMNIFormattedName *)formattedName;

- (void)clearFormattedName;

- (nonnull NSArray<PMNITelephone *> *)getTelephoneNumbers;

- (void)addTelephone:(nullable PMNITelephone *)cell;

- (void)setTelephones:(nonnull NSArray<PMNITelephone *> *)cells;

- (void)clearTelephones;

- (nonnull NSArray<PMNIEmail *> *)getEmails;

- (void)addEmail:(nullable PMNIEmail *)email;

/**set will replace all exsiting */
- (void)setEmails:(nonnull NSArray<PMNIEmail *> *)emails;

- (void)clearEmails;

- (nullable PMNIUid *)getUid;

- (void)setUid:(nullable PMNIUid *)uuid;

- (nonnull NSArray<PMNIAddress *> *)getAddresses;

- (void)addAddress:(nullable PMNIAddress *)addr;

- (void)setAddresses:(nonnull NSArray<PMNIAddress *> *)addrs;

- (void)clearAddresses;

- (nullable PMNIOrganization *)getOrganization;

- (void)addOrganization:(nullable PMNIOrganization *)org;

- (void)setOrganizations:(nonnull NSArray<PMNIOrganization *> *)orgs;

- (void)clearOrganizations;

- (nullable PMNINote *)getNote;

- (void)setNote:(nullable PMNINote *)note;

- (void)clearNote;

- (nullable PMNINickname *)getNickname;

- (void)setNickname:(nullable PMNINickname *)nickname;

- (void)clearNickname;

- (nullable PMNITitle *)getTitle;

- (void)setTitle:(nullable PMNITitle *)title;

- (void)clearTitle;

- (nonnull NSArray<PMNIBirthday *> *)getBirthdays;

- (void)addBirthday:(nullable PMNIBirthday *)birthday;

- (void)setBirthdays:(nonnull NSArray<PMNIBirthday *> *)birthdays;

- (void)clearBirthdays;

- (nonnull NSArray<PMNIPMCustom *> *)getCustoms;

- (void)addCustom:(nullable PMNIPMCustom *)custom;

- (void)setCustoms:(nonnull NSArray<PMNIPMCustom *> *)customs;

- (void)clearCustoms;

- (nullable PMNIPMSign *)getPMSign:(nonnull NSString *)group;

- (void)addPMSign:(nullable PMNIPMSign *)sign;

- (void)setPMSign:(nullable PMNIPMSign *)sign;

- (void)clearPMSign;

- (nullable PMNIPMEncrypt *)getPMEncrypt:(nonnull NSString *)group;

- (void)addPMEncrypt:(nullable PMNIPMEncrypt *)encrypt;

- (void)setPMEncrypt:(nullable PMNIPMEncrypt *)encrypt;

- (void)clearPMEncrypt;

- (nullable PMNIPMScheme *)getPMScheme:(nonnull NSString *)group;

- (void)addPMScheme:(nullable PMNIPMScheme *)scheme;

- (void)setPMScheme:(nullable PMNIPMScheme *)scheme;

- (void)clearPMScheme;

- (nullable PMNIPMMimeType *)getPMMimeType:(nonnull NSString *)group;

- (void)addPMMimeType:(nullable PMNIPMMimeType *)mimetype;

- (void)setPMMimeType:(nullable PMNIPMMimeType *)mimetype;

- (void)clearPMMimeType;

- (nonnull NSArray<PMNIKey *> *)getKeys:(nonnull NSString *)group;

- (void)addKey:(nullable PMNIKey *)key;

/**set will replace all exsiting */
- (void)setKeys:(nonnull NSArray<PMNIKey *> *)keys;

- (void)clearKeys;

- (nullable PMNICategories *)getCategories:(nonnull NSString *)group;

- (void)addCategories:(nullable PMNICategories *)c;

- (void)setCategories:(nullable PMNICategories *)c;

- (void)clearCategories;

- (nonnull NSArray<PMNIUrl *> *)getUrls;

- (void)addUrl:(nullable PMNIUrl *)url;

- (void)setUrls:(nonnull NSArray<PMNIUrl *> *)urls;

- (void)clearUrls;

- (nullable PMNIGender *)getGender;

- (void)setGender:(nullable PMNIGender *)gender;

- (void)clearGender;

- (nullable PMNIStructuredName *)getStructuredName;

- (void)setStructuredName:(nullable PMNIStructuredName *)name;

- (void)clearStructuredName;

+ (nullable PMNIVCard *)createInstance;

@end
