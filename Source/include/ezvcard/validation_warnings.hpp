//
//  validation_warnings.hpp
//  OpenPGP
//
//  Created by Yanfeng Zhang on 12/2/16.
//  Copyright © 2016 Yanfeng Zhang. All rights reserved.
//

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
