//
//  vcard_version.hpp
//  OpenPGP
//
//  Created by Yanfeng Zhang on 12/2/16.
//
//  The MIT License
// 
//  Copyright (c) 2019 Proton Technologies AG
// 
//  Permission is hereby granted, free of charge, to any person obtaining a copy
//  of this software and associated documentation files (the "Software"), to deal
//  in the Software without restriction, including without limitation the rights
//  to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
//  copies of the Software, and to permit persons to whom the Software is
//  furnished to do so, subject to the following conditions:
// 
//  The above copyright notice and this permission notice shall be included in
//  all copies or substantial portions of the Software.
// 
//  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
//  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
//  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
//  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
//  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
//  OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
//  THE SOFTWARE.

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
