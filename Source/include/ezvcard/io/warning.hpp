//
//  warning.hpp
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

#ifndef warning_hpp
#define warning_hpp

#include <string>

class Warning {
    
public:
    enum TYPE {
        MALFORMED_LINE,
        EMPTY_BEGIN,
        EMPTY_END,
        UNMATCHED_END,
        UNKNOWN_VERSION,
        UNKNOWN_CHARSET,
        QUOTED_PRINTABLE_ERROR
    };
    
private:
    int _code;
    std::string _message;
    
public:
    typedef std::shared_ptr<Warning> Ptr;
    
    //Warning(int code, Object... args);
    
    Warning(std::string message);
    Warning(std::string message, int code);
    int getCode();
    std::string getMessage();
    
    
    
};

#endif /* warning_hpp */
