//
//  clearable_string_builder.hpp
//  OpenPGP
//
//  Created by Yanfeng Zhang on 1/18/17.
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

#ifndef clearable_string_builder_hpp
#define clearable_string_builder_hpp

#include <stdio.h>
#include <sstream>      


namespace ezvcard {
    

class ClearableStringBuilder {
public:
    typedef std::shared_ptr<ClearableStringBuilder> Ptr;
    
private:
    std::stringstream ss;
    
public:
    void clear();
    std::string get();
    std::string getAndClear();
    void append(char ch);
    void append(const std::string& string);
    void append(const std::string& str, int start, int length);
    void chop();
    size_t length();
};

    
}

#endif /* clearable_string_builder_hpp */
