//
//  charset.hpp
//  OpenPGP
//
//  Created by Yanfeng Zhang on 5/22/17.
//  Copyright © 2017 Yanfeng Zhang. All rights reserved.
//

#ifndef charset_hpp
#define charset_hpp

#include <stdio.h>
#include <string>

class Charset {
    
public:
    typedef std::shared_ptr<Charset> Ptr;
    
    const static Charset::Ptr UTF_8;
    const static Charset::Ptr UTF_16;
    
    
    std::string getString(const std::string& input);
    std::string getString(const std::wstring& input);
    
private:
    std::string _name;
    
    std::string to_utf16(const std::wstring& input);
    std::string to_utf16(const std::string& input);
    std::string to_string(const std::wstring& input);

public:
    Charset(const std::string& name);
    std::string name();
    
    static Charset::Ptr forName(const std::string& name);
    
};

#endif /* charset_hpp */
