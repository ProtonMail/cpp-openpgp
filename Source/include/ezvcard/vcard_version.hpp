//
//  vcard_version.hpp
//  OpenPGP
//
//  Created by Yanfeng Zhang on 12/2/16.
//  Copyright © 2016 Yanfeng Zhang. All rights reserved.
//

#ifndef vcard_version_hpp
#define vcard_version_hpp

#include <iostream>
#include <string>
#include <vector>
#include <list>

#include <bridge/i_v_card_version.hpp>

using namespace ProtonMail;

enum SyntaxStyle {
    OLD = 0, // "Old style" syntax (vCard 2.1 and vCal 1.0).
    NEW, //"New style" syntax (vCard 3.0/4.0 and iCal 2.0).
    NONE
};


class VCardVersion : public IVCardVersion {
    
public:
    typedef std::shared_ptr<VCardVersion> Ptr;

    std::string getVersion();
    SyntaxStyle getSyntaxStyle();
    std::string getXmlNamespace();
    static VCardVersion::Ptr valueOfByStr(const std::string& value);
    static VCardVersion::Ptr valueOfByXmlNamespace(const std::string& ns);
    
    static std::vector<VCardVersion::Ptr> values();

    bool equals(const Ptr& obj);

    //TODO::Fix later
//    bool operator==(const VCardVersion* rhs) const;
    
    std::string toString();
    static std::string toString(std::vector<VCardVersion::Ptr> versions);
    static std::vector<VCardVersion::Ptr> V21_V30();
    static VCardVersion::Ptr V2_1();
    static VCardVersion::Ptr V3_0();
    static VCardVersion::Ptr V4_0();
private:
    VCardVersion(std::string version, SyntaxStyle syntaxStyle, std::string xmlNamespace);
    static VCardVersion::Ptr Ver2_1;
    static VCardVersion::Ptr Ver3_0;
    static VCardVersion::Ptr Ver4_0;
    
    std::string _version;
    SyntaxStyle _syntaxStyle;
    std::string _xmlNamespace;
    
public: //IVCardVersion impl
    bool equals(const std::shared_ptr<IVCardVersion> & rhs);
    bool operator==(const VCardVersion& rhs);

};

bool operator==(const VCardVersion::Ptr& lhs, const VCardVersion::Ptr& rhs);

#endif /* vcard_version_hpp */
