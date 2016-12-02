//
//  ez_vcard_simple_vcards_test.cpp
//  OpenPGP
//
//  Created by Yanfeng Zhang on 6/2/17.
//  Copyright © 2017 Yanfeng Zhang. All rights reserved.
//

#include "utils_test.h"

#include <ezvcard/ezvcard.hpp>
#include <ezvcard/vcard.hpp>
#include <ezvcard/io/chain/chaining_text_string_parser.hpp>

using namespace ezvcard;
namespace tests {
    namespace ez_vcard_tests {
        SUITE(ez_vcard_email_test)
        {
            //            TEST(validate) {
            //                auto vcard = Ezvcard::parse(str).first();
            //                VERIFY_IS_TRUE(VCardVersion::V3_0->equals(vcard->getVersion()));
            //                auto fn = vcard->getFormattedName();
            //                VERIFY_IS_NOT_NULL(fn);
            //                VERIFY_ARE_EQUAL("1 & 1", fn->get_value());
            //            }
            
            TEST(test_protonmail_web) {
                std::string str_protonmail_web =
                "BEGIN:VCARD\r\n"
                "VERSION:3.0\r\n"
                "N:1\\;&\\;1\r\n"  //
                "FN:1 & 1\r\n"      //
                "EMAIL;TYPE=Email:test@example.com\r\n"  //
                "EMAIL;TYPE=Home:test1@example.com\r\n"    //
                "EMAIL;TYPE=Work:test3@example.com\r\n"   //
                "TEL;TYPE=Cell:6176767087\r\n"          //
                "TEL;TYPE=Fax:6414551782\r\n"           //
                "ADR;TYPE=Home:500 King Dr Daly City CA\\, 94080\r\n"//
                "ORG;TYPE=Org:TestOrg\r\n"//=
                "TITLE;TYPE=Title:TestTitle\r\n"
                "NICKNAME:TestNickName\r\n"
                "BDAY;TYPE=Bday:19841007\r\n"
                "ITEM1.CUSTOM:TestCustomField1\r\n"
                "ITEM1.X-ABLABEL:Custom\r\n"
                "ITEM2.CUSTOM:TestCustomField2\r\n"
                "ITEM2.X-ABLABEL:Custom\r\n"
                "ITEM3.CUSTOM:333333\r\n"
                "ITEM3.X-ABLABEL:Custom\r\n"
                "NOTE;TYPE=Note:test notes 11\r\n"
                "END:VCARD\r\n";
                
                auto vcard = Ezvcard::parse(str_protonmail_web).first();
                VERIFY_IS_NOT_NULL(vcard);
                VERIFY_IS_TRUE(vcard->getVersion() == VCardVersion::V3_0());
                
                auto addresses = vcard->getAddresses();
                VERIFY_IS_TRUE(addresses.size() == 1);
                {
                    auto addr = addresses[0];
                    Address::Ptr a = std::dynamic_pointer_cast<Address>(addr);
                    auto street = a->getStreetAddress();
                    auto poBox = a->getPoBox();
                    VERIFY_IS_TRUE(poBox == "500 King Dr Daly City CA, 94080");
                }
                
                auto telephones = vcard->getTelephoneNumbers();
                VERIFY_IS_TRUE(telephones.size() == 2);
                {
                    auto tel1 = telephones[0];
                    VERIFY_IS_NOT_NULL(tel1);
                    std::vector<std::string> types{"Cell"};
                    auto ts = tel1->getTypes();
                    VERIFY_IS_TRUE(ts == types);
                    VERIFY_IS_TRUE(tel1->getText() == "6176767087");
                }
                {
                    auto tel2 = telephones[1];
                    VERIFY_IS_NOT_NULL(tel2);
                    std::vector<std::string> types{"Fax"};
                    auto ts = tel2->getTypes();
                    VERIFY_IS_TRUE(ts == types);
                    VERIFY_IS_TRUE(tel2->getText() == "6414551782");
                }
                
                auto emails = vcard->getEmails();
                VERIFY_IS_TRUE(emails.size() == 3);
                {
                    auto email = emails[0];
                    VERIFY_IS_NOT_NULL(email);
                    std::vector<std::string> types{"Email"};
                    auto ts = email->getTypes();
                    VERIFY_IS_TRUE(ts == types);
                    VERIFY_IS_TRUE(email->getValue() == "test@example.com");
                }
                {
                    auto email = emails[1];
                    VERIFY_IS_NOT_NULL(email);
                    std::vector<std::string> types{"Home"};
                    auto ts = email->getTypes();
                    VERIFY_IS_TRUE(ts == types);
                    VERIFY_IS_TRUE(email->getValue() == "test1@example.com");
                }
                {
                    auto email = emails[2];
                    VERIFY_IS_NOT_NULL(email);
                    std::vector<std::string> types{"Work"};
                    auto ts = email->getTypes();
                    VERIFY_IS_TRUE(ts == types);
                    VERIFY_IS_TRUE(email->getValue() == "test3@example.com");
                }
                
                Organization::Ptr org = std::dynamic_pointer_cast<Organization>(vcard->getOrganization());
                {
                    VERIFY_IS_TRUE(org->getType() == "Org");
                    std::vector<std::string> check { "TestOrg" };
                    VERIFY_IS_TRUE(org->getValues() == check);
                }
                
                auto title = vcard->getTitle();
                {
                    VERIFY_IS_TRUE(title->getType() == "Title");
                    VERIFY_IS_TRUE(title->getTitle() == "TestTitle");
                }
                
                auto nickName = vcard->getNickname();
                {
                    VERIFY_IS_TRUE(nickName->getType() == "");
                    std::vector<std::string> cNicknames { "TestNickName" };
                    VERIFY_IS_TRUE(nickName->getValues() == cNicknames);
                }
                
                auto birthday = vcard->getBirthday();
                {
                    VERIFY_IS_TRUE(birthday->getType() == "Bday");
                    VERIFY_IS_TRUE(birthday->getDate() == "19841007");
                }
                
                auto note = vcard->getNote();
                {
                    VERIFY_IS_TRUE(note->getType() == "Note");
                    VERIFY_IS_TRUE(note->getNote() == "test notes 11");
                }
                
                auto customs = vcard->getPMCustoms();
                VERIFY_IS_TRUE(emails.size() == 3);
                {
                    auto custom = customs[0];
                    VERIFY_IS_TRUE(custom->getType() == "");
                    VERIFY_IS_TRUE(custom->getValue() == "TestCustomField1");
                    VERIFY_IS_TRUE(custom->getGroup() == "ITEM1");
                }
                {
                    auto custom = customs[1];
                    VERIFY_IS_TRUE(custom->getType() == "");
                    VERIFY_IS_TRUE(custom->getValue() == "TestCustomField2");
                    VERIFY_IS_TRUE(custom->getGroup() == "ITEM2");
                }
                {
                    auto custom = customs[2];
                    VERIFY_IS_TRUE(custom->getType() == "");
                    VERIFY_IS_TRUE(custom->getValue() == "333333");
                    VERIFY_IS_TRUE(custom->getGroup() == "ITEM3");
                }
                
                //"ITEM1.CUSTOM:TestCustomField1\r\n"
                //"ITEM1.X-ABLABEL:Custom\r\n"
                //"ITEM2.CUSTOM:TestCustomField2\r\n"
                //"ITEM2.X-ABLABEL:Custom\r\n"
                //"ITEM3.CUSTOM:333333\r\n"
                //"ITEM3.X-ABLABEL:Custom\r\n"
            }
            
            TEST(rfc2426_example) {
                
                std::string str =
                "BEGIN:vCard\r\n"
                "VERSION:3.0\r\n"
                "FN:Frank Dawson\r\n"
                "ORG:Lotus Development Corporation\r\n"
                "ADR;TYPE=Work,POSTAL,PARCEL:;;6544 Battleford Drive\r\n"
                " ;Raleigh;NC;27613-3502;U.S.A.\r\n"
                "TEL;TYPE=VOICE,MSG,WORK:+1-919-676-9515\r\n"
                "TEL;TYPE=FAX,WORK:+1-919-676-9564\r\n"
                "EMAIL;TYPE=INTERNET,PREF:Frank_Dawson@Lotus.com\r\n"
                "EMAIL;TYPE=INTERNET:fdawson@earthlink.net\r\n"
                "URL:http://home.earthlink.net/~fdawson\r\n"
                "END:vCard\r\n"
                "BEGIN:vCard\r\n"
                "VERSION:3.0\r\n"
                "FN:Tim Howes\r\n"
                "ORG:Netscape Communications Corp.\r\n"
                "ADR;TYPE=WORK:;;501 E. Middlefield Rd.;Mountain View;\r\n"
                " CA; 94043;U.S.A.\r\n"
                "TEL;TYPE=VOICE,MSG,WORK:+1-415-937-3419\r\n"
                "TEL;TYPE=FAX,WORK:+1-415-528-4164\r\n"
                "EMAIL;TYPE=INTERNET:howes@netscape.com\r\n"
                "END:vCard\r\n";
                
                auto vcards = Ezvcard::parse(str).all();
                VERIFY_IS_TRUE(vcards.size() == 2);
                {
                    auto vcard = vcards[0];
                    VERIFY_IS_NOT_NULL(vcard);
                    auto vcardversion = std::dynamic_pointer_cast<VCardVersion>(vcard->getVersion());
                    VERIFY_IS_TRUE(VCardVersion::V3_0()->equals(vcardversion));
                    auto fn = vcard->getFormattedName();
                    VERIFY_ARE_EQUAL(fn->getValue(), "Frank Dawson");
                    auto org = vcard->getOrganization();
                    VERIFY_IS_TRUE(org->getValues() == std::vector<std::string> {"Lotus Development Corporation"});
                    
                    auto addresses = vcard->getAddresses();
                    VERIFY_IS_TRUE(addresses.size() == 1);
                    {
                        auto address = addresses[0];
                        VERIFY_IS_NOT_NULL(address);
                        VERIFY_IS_TRUE(address->getStreetAddress() =="6544 Battleford Drive");
                        VERIFY_IS_TRUE(address->getLocality() == "Raleigh");
                        VERIFY_IS_TRUE(address->getRegion() == "NC");
                        VERIFY_IS_TRUE(address->getPostalCode() == "27613-3502");
                        VERIFY_IS_TRUE(address->getCountry() == "U.S.A.");
                        std::vector<std::string> types{"Work","POSTAL","PARCEL"};
                        auto ts = address->getTypes();
                        VERIFY_IS_TRUE(ts == types);
                    }
                    
                    auto telephones = vcard->getTelephoneNumbers();
                    VERIFY_IS_TRUE(telephones.size() == 2);
                    {
                        
                        auto tel1 = telephones[0];
                        VERIFY_IS_NOT_NULL(tel1);
                        std::vector<std::string> types{"VOICE","MSG","WORK"};
                        auto ts = tel1->getTypes();
                        VERIFY_IS_TRUE(ts == types);
                        VERIFY_IS_TRUE(tel1->getText() == "+1-919-676-9515");
                    }
                    {
                        auto tel2 = telephones[1];
                        VERIFY_IS_NOT_NULL(tel2);
                        std::vector<std::string> types{"FAX","WORK"};
                        auto ts = tel2->getTypes();
                        VERIFY_IS_TRUE(ts == types);
                        VERIFY_IS_TRUE(tel2->getText() == "+1-919-676-9564");
                    }
                    
                    auto emails = vcard->getEmails();
                    VERIFY_IS_TRUE(emails.size() == 2);
                    {
                        auto email = emails[0];
                        VERIFY_IS_NOT_NULL(email);
                        std::vector<std::string> types{"INTERNET","PREF"};
                        auto ts = email->getTypes();
                        VERIFY_IS_TRUE(ts == types);
                        VERIFY_IS_TRUE(email->getValue() == "Frank_Dawson@Lotus.com");
                    }
                    
                    {
                        auto email = emails[1];
                        VERIFY_IS_NOT_NULL(email);
                        std::vector<std::string> types{"INTERNET"};
                        auto ts = email->getTypes();
                        VERIFY_IS_TRUE(ts == types);
                        VERIFY_IS_TRUE(email->getValue() == "fdawson@earthlink.net");
                    }
                    
                    auto urls = vcard->getUrls();
                    VERIFY_IS_TRUE(urls.size() == 1);
                    auto url = urls[0];
                    VERIFY_IS_NOT_NULL(url);
                    VERIFY_IS_TRUE(url->getValue() == "http://home.earthlink.net/~fdawson");
                }
                
                {
                    auto vcard = vcards[1];
                    VERIFY_IS_NOT_NULL(vcard);
                    auto vcardversion = std::dynamic_pointer_cast<VCardVersion>(vcard->getVersion());
                    VERIFY_IS_TRUE(VCardVersion::V3_0()->equals(vcardversion));
                    auto fn = vcard->getFormattedName();
                    VERIFY_ARE_EQUAL(fn->getValue(), "Tim Howes");
                    auto org = vcard->getOrganization();
                    VERIFY_IS_TRUE(org->getValues() == std::vector<std::string> {"Netscape Communications Corp."});
                    
                    auto addresses = vcard->getAddresses();
                    VERIFY_IS_TRUE(addresses.size() == 1);
                    {
                        auto address = addresses[0];
                        VERIFY_IS_NOT_NULL(address);
                        VERIFY_IS_TRUE(address->getStreetAddress() == "501 E. Middlefield Rd.");
                        VERIFY_IS_TRUE(address->getLocality() == "Mountain View");
                        VERIFY_IS_TRUE(address->getRegion() == "CA");
                        VERIFY_IS_TRUE(address->getPostalCode() == " 94043");
                        VERIFY_IS_TRUE(address->getCountry() == "U.S.A.");
                        std::vector<std::string> types{"WORK"};
                        auto ts = address->getTypes();
                        VERIFY_IS_TRUE(ts == types);
                    }
                    
                    auto telephones = vcard->getTelephoneNumbers();
                    VERIFY_IS_TRUE(telephones.size() == 2);
                    {
                        
                        auto tel1 = telephones[0];
                        VERIFY_IS_NOT_NULL(tel1);
                        std::vector<std::string> types{"VOICE","MSG","WORK"};
                        auto ts = tel1->getTypes();
                        VERIFY_IS_TRUE(ts == types);
                        VERIFY_IS_TRUE(tel1->getText() == "+1-415-937-3419");
                    }
                    {
                        auto tel2 = telephones[1];
                        VERIFY_IS_NOT_NULL(tel2);
                        std::vector<std::string> types{"FAX","WORK"};
                        auto ts = tel2->getTypes();
                        VERIFY_IS_TRUE(ts == types);
                        VERIFY_IS_TRUE(tel2->getText() == "+1-415-528-4164");
                    }
                    
                    auto emails = vcard->getEmails();
                    VERIFY_IS_TRUE(emails.size() == 1);
                    {
                        auto email = emails[0];
                        VERIFY_IS_NOT_NULL(email);
                        std::vector<std::string> types{"INTERNET"};
                        auto ts = email->getTypes();
                        VERIFY_IS_TRUE(ts == types);
                        VERIFY_IS_TRUE(email->getValue() == "howes@netscape.com");
                    }
                }
            }
            
            
            TEST(fullcontact) {
                //                VCardAsserter asserter = read("fullcontact.vcf");
                //                asserter.next(V4_0);
                //
                //                //@formatter:off
                //                asserter.structuredName()
                //                .family("LastName")
                //                .given("FirstName")
                //                .additional("MiddleName")
                //                .prefixes("Prefix")
                //                .suffixes("Suffix")
                //                .noMore();
                //
                //                asserter.simpleProperty(FormattedName.class)
                //                .value("Prefix FirstName MiddleName LastName Suffix")
                //                .noMore();
                //
                //                asserter.telephone()
                //                .types(TelephoneType.HOME, TelephoneType.VOICE)
                //                .text("555-555-1111")
                //                .next()
                //                .types(TelephoneType.WORK, TelephoneType.VOICE)
                //                .text("555-555-1112")
                //                .next()
                //                .types(TelephoneType.CELL, TelephoneType.VOICE)
                //                .text("555-555-1113")
                //                .next()
                //                .types(TelephoneType.CELL, TelephoneType.VOICE)
                //                .text("555-555-1114")
                //                .next()
                //                .types(TelephoneType.VOICE)
                //                .text("555-555-1115")
                //                .next()
                //                .types(TelephoneType.HOME, TelephoneType.FAX)
                //                .text("555-555-1116")
                //                .next()
                //                .types(TelephoneType.WORK, TelephoneType.FAX)
                //                .text("555-555-1117")
                //                .next()
                //                .types(TelephoneType.VOICE)
                //                .text("555-555-1118")
                //                .next()
                //                .types(TelephoneType.VOICE)
                //                .text("555-555-1119")
                //                .noMore();
                //
                //                asserter.email()
                //                .types(EmailType.HOME)
                //                .value("home@example.com")
                //                .next()
                //                .types(EmailType.WORK)
                //                .value("work@example.com")
                //                .next()
                //                .types(EmailType.get("SCHOOL"))
                //                .value("school@example.com")
                //                .next()
                //                .types(EmailType.get("OTHER"))
                //                .value("other@example.com")
                //                .next()
                //                .types(EmailType.get("CUSTOMTYPE"))
                //                .value("custom@example.com")
                //                .noMore();
                //
                //                asserter.binaryProperty(Photo.class)
                //                .url("https://d3m0kzytmr41b1.cloudfront.net/c335e945d1b60edd9d75eb4837c432f637e95c8a")
                //                .next()
                //                .url("https://d3m0kzytmr41b1.cloudfront.net/c335e945d1b60edd9d75eb4837c432f637e95c8a")
                //                .next()
                //                .url("https://d2ojpxxtu63wzl.cloudfront.net/static/aa915d1f29f19baf560e5491decdd30a_67c95da9133249fde8b0da7ceebc298bf680117e6f52054f7f5f7a95e8377238")
                //                .noMore();
                //
                //                asserter.listProperty(Organization.class)
                //                .values("Organization1", "Department1")
                //                .next()
                //                .values("Organization2", "Department2")
                //                .noMore();
                //
                //                asserter.simpleProperty(Title.class)
                //                .value("Title1")
                //                .next()
                //                .value("Title2")
                //                .noMore();
                //
                //                asserter.dateProperty(Birthday.class)
                //                .param("ALTID", "1")
                //                .date("2016-08-01")
                //                .next()
                //                .param("ALTID", "1")
                //                .text("2016-08-01")
                //                .noMore();
                //
                //                asserter.property(Gender.class)
                //                .expected(Gender.male())
                //                .noMore();
                //
                //                asserter.rawProperty("X-GENDER")
                //                .value("male")
                //                .noMore();
                //
                //                asserter.rawProperty("X-ID")
                //                .value("14f9aba0c9422da9ae376fe28bd89c2a.0")
                //                .noMore();
                //
                //                asserter.rawProperty("X-ETAG")
                //                .value("fffffea9056d8166e2b7a427977e570c87dd51279d11d9b137c593eb")
                //                .noMore();
                //
                //                asserter.rawProperty("X-FC-TAGS")
                //                .value("579c773f-736d-11e6-8dff-0ac8448704fb")
                //                .noMore();
                //
                //                asserter.rawProperty("X-FC-LIST-ID")
                //                .value("8ad23200aa3e1984736b11e688dc0add41994b95")
                //                .noMore();
                //
                //                asserter.rawProperty("X-FCENCODED-582D46432D52656C617465644E616D65733A4D6F74686572")
                //                .value("Mother")
                //                .noMore();
                //
                //                asserter.rawProperty("X-FCENCODED-582D46432D52656C617465644E616D65733A466174686572")
                //                .value("Father")
                //                .noMore();
                //
                //                asserter.rawProperty("X-FCENCODED-582D46432D52656C617465644E616D65733A506172656E74")
                //                .value("Parent")
                //                .noMore();
                //
                //                asserter.rawProperty("X-FCENCODED-582D46432D52656C617465644E616D65733A42726F74686572")
                //                .value("Brother")
                //                .noMore();
                //
                //                asserter.rawProperty("X-FCENCODED-582D46432D52656C617465644E616D65733A536973746572")
                //                .value("Sister")
                //                .noMore();
                //
                //                asserter.rawProperty("X-FCENCODED-582D46432D52656C617465644E616D65733A4368696C64")
                //                .value("Child")
                //                .noMore();
                //
                //                asserter.rawProperty("X-FCENCODED-582D46432D52656C617465644E616D65733A467269656E64")
                //                .value("Friend")
                //                .noMore();
                //
                //                asserter.rawProperty("X-FCENCODED-582D46432D52656C617465644E616D65733A53706F757365")
                //                .value("Spouse")
                //                .noMore();
                //
                //                asserter.rawProperty("X-FCENCODED-582D46432D52656C617465644E616D65733A4669616E63C3A9")
                //                .value("Fiance")
                //                .noMore();
                //
                //                asserter.rawProperty("X-FCENCODED-582D46432D52656C617465644E616D65733A506172746E6572")
                //                .value("Partner")
                //                .noMore();
                //
                //                asserter.rawProperty("X-FCENCODED-582D46432D52656C617465644E616D65733A417373697374616E74")
                //                .value("Assistant")
                //                .noMore();
                //
                //                asserter.rawProperty("X-FCENCODED-582D46432D52656C617465644E616D65733A4D616E61676572")
                //                .value("Manager")
                //                .noMore();
                //
                //                asserter.rawProperty("X-FCENCODED-582D46432D52656C617465644E616D65733A4F74686572")
                //                .value("Other")
                //                .noMore();
                //
                //                asserter.rawProperty("X-FCENCODED-582D46432D52656C617465644E616D65733A437573746F6D54595045")
                //                .value("Custom")
                //                .noMore();
                //
                //                asserter.rawProperty("X-FCENCODED-582D46432D4F7468657244617465733A416E6E6976657273617279")
                //                .value("2016-08-02")
                //                .noMore();
                //
                //                asserter.rawProperty("X-FCENCODED-582D46432D4F7468657244617465733A4F74686572")
                //                .value("2016-08-03")
                //                .noMore();
                //
                //                asserter.rawProperty("X-FCENCODED-582D46432D4F7468657244617465733A437573746F6D54595045")
                //                .value("2016-08-04")
                //                .noMore();
                //
                //                asserter.simpleProperty(Note.class)
                //                .value("Notes line 1" + NEWLINE + "Notes line 2")
                //                .noMore();
                //
                //                asserter.simpleProperty(Url.class)
                //                .value("http://www.homepage.com")
                //                .next()
                //                .value("http://www.blog.com")
                //                .next()
                //                .value("http://www.other.com")
                //                .next()
                //                .value("http://www.custom.com")
                //                .noMore();
                //                
                //                asserter.address()
                //                .types(AddressType.HOME)
                //                .extendedAddress("HomeExtended")
                //                .streetAddress("HomeStreet")
                //                .locality("HomeCity")
                //                .region("HomeState")
                //                .postalCode("HomePostal")
                //                .country("HomeCountry")
                //                .next()
                //                .types(AddressType.WORK)
                //                .extendedAddress("WorkExtended")
                //                .streetAddress("WorkStreet")
                //                .locality("WorkCity")
                //                .region("WorkState")
                //                .postalCode("WorkPostal")
                //                .country("WorkCountry")
                //                .next()
                //                .types(AddressType.get("OTHER"))
                //                .extendedAddress("OtherExtended")
                //                .streetAddress("OtherStreet")
                //                .locality("OtherCity")
                //                .region("OtherState")
                //                .postalCode("OtherPostal")
                //                .country("OtherCountry")
                //                .next()
                //                .types(AddressType.get("CUSTOMTYPE"))
                //                .extendedAddress("CustomExtended")
                //                .streetAddress("CustomStreet")
                //                .locality("CustomCity")
                //                .region("CustomState")
                //                .postalCode("CustomPostal")
                //                .country("CustomCountry")
                //                .noMore();
                //                
                //                asserter.listProperty(Nickname.class)
                //                .values("NickName")
                //                .noMore();
                //                
                //                asserter.impp()
                //                .param("X-SERVICE-TYPE", "GTalk")
                //                .uri("xmpp:gtalk")
                //                .next()
                //                .param("X-SERVICE-TYPE", "Skype")
                //                .uri("skype:skype")
                //                .next()
                //                .param("X-SERVICE-TYPE", "Yahoo")
                //                .uri("ymsgr:yahoo")
                //                .next()
                //                .param("X-SERVICE-TYPE", "AIM")
                //                .uri("aim:aim")
                //                .next()
                //                .param("X-SERVICE-TYPE", "Jabber")
                //                .uri("xmpp:jabber")
                //                .next()
                //                .param("X-SERVICE-TYPE", "Other")
                //                .uri("other:other")
                //                .next()
                //                .param("X-SERVICE-TYPE", "CustomTYPE")
                //                .uri("customtype:custom")
                //                .noMore();
                //                
                //                asserter.listProperty(Categories.class)
                //                .values("Tag")
                //                .noMore();
                //                
                //                asserter.simpleProperty(ProductId.class)
                //                .value("ez-vcard 0.9.14-fc")
                //                .noMore();
                //                //@formatter:on
                //                
                //                asserter.validate().run();
                //                asserter.done();
            }
            
        }
    }
}
