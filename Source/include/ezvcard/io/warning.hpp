//
//  warning.hpp
//  OpenPGP
//
//  Created by Yanfeng Zhang on 12/2/16.
//  Copyright © 2016 Yanfeng Zhang. All rights reserved.
//

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
