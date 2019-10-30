//
//  quoted_printable.hpp
//  OpenPGP
//
//  Created by Yanfeng Zhang on 5/19/17.
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


#ifndef quoted_printable_hpp
#define quoted_printable_hpp

#include <stdio.h>
#include <string>
#include <sstream>

#include "charset.hpp"


//refer current code : https://github.com/bluetiger9/Qt-Quoted-Printable

class QuotedPrintable
{
public:
    QuotedPrintable(const Charset::Ptr& name);
    
    std::string encode(const std::string &input);
    std::string decode(const std::string &input);
    
private:
    
    std::string _encode(const std::string &input);
    std::string _decode(const std::string &input);
    
    Charset::Ptr _charset;
    
    
};






//refer of reminder for later: https://gist.github.com/rane-hs/1372517#file-quoted_printable-hpp



#endif /* quoted_printable_hpp */
