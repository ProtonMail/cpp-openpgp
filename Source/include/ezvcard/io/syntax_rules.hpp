//
//  SyntaxRules.hpp
//  OpenPGP
//
//  Created by Yanfeng Zhang on 12/5/16.
//  Copyright © 2016 Yanfeng Zhang. All rights reserved.
//

#ifndef SyntaxRules_hpp
#define SyntaxRules_hpp

#include <ezvcard/vcard_version.hpp>
#include <string>
#include <unordered_map>

class SyntaxRules {
private:
    SyntaxStyle _defaultSyntaxStyle;
    std::unordered_map<std::string, std::unordered_map<std::string, SyntaxStyle>> _syntaxRules = std::unordered_map<std::string, std::unordered_map<std::string, SyntaxStyle>>();
 
public:
    SyntaxRules(SyntaxStyle defaultSyntaxStyle);
    SyntaxStyle getDefaultSyntaxStyle();
    
    void setDefaultSyntaxStyle(SyntaxStyle defaultSyntaxStyle);
    
    bool hasSyntaxRules(const std::string& component);
    SyntaxStyle getSyntaxStyle(std::string component, std::string versionValue);
    
    void addRule(std::string component, std::string version, SyntaxStyle syntaxStyle);
    
    static SyntaxRules iCalendar();
    static SyntaxRules vcard();

};


#endif /* SyntaxRules_hpp */
