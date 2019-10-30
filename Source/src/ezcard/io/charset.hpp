//
//  charset.hpp
//  OpenPGP
//
//  Created by Yanfeng Zhang on 5/22/17.
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
