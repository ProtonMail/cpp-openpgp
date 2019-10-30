//
//  buffer.hpp
//  OpenPGP
//
//  Created by Yanfeng Zhang on 12/6/16.
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

#ifndef buffer_hpp
#define buffer_hpp

#include <string>       // std::string
#include <iostream>     // std::cout
#include <sstream>      // std::stringstream

class Buffer {
    
private:
    std::stringstream ss;
    
public:
    typedef std::shared_ptr<Buffer> Ptr;
    
    void clear();
    std::string get();
    std::string getAndClear();
    void append(const char& ch);
    void append(const std::string& str);
    void append(const std::string& str, int start, int size);
    void chop();
    size_t size();
};

#endif /* buffer_hpp */
