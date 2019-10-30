//
//  validation_warnings.hpp
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

#ifndef validation_warnings_hpp
#define validation_warnings_hpp

#include <stdio.h>

#include <string>
#include "messages.hpp"

class ValidationWarning {
private:
    int _code;
    std::string _message;
    

public:
    typedef std::shared_ptr<ValidationWarning> Ptr;
    
    ValidationWarning(std::string message);
    ValidationWarning(int code, std::string message);
    template<typename Arg0, typename ... Args>
    ValidationWarning(Arg0 &&arg0, Args &&... args) {
        _code = arg0;
        _message = Messages::getInstance()->getValidationWarning(arg0, args...);
    }
    int getCode();
    std::string getMessage();
    std::string toString();
    
    
    bool operator==(const int& rhs);

    
//    Or like this:
//    
//    bool Symbol::operator==(Symbol*& rhs)const{
//        cout << "operatore overloaded == " << rhs->name;
//        if (this->name==rhs->name)
//            return true;
//        return false;
//    }

};

bool operator==(const ValidationWarning::Ptr& lhs, const ValidationWarning::Ptr& rhs);

bool operator==(const ValidationWarning::Ptr& lhs, const int& rhs);

#endif /* validation_warnings_hpp */
