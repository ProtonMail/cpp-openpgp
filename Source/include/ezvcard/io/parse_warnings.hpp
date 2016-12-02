//
//  parse_warnings.hpp
//  OpenPGP
//
//  Created by Yanfeng Zhang on 12/5/16.
//  Copyright © 2016 Yanfeng Zhang. All rights reserved.
//

#ifndef parse_warnings_hpp
#define parse_warnings_hpp

#include <string>
#include <list>

class ParseWarnings {
private:
    std::list<std::string> _warnings = std::list<std::string>();

public:
    //void add(Integer line, std::string propertyName, int code, Object... args);
    void add(int line, std::string propertyName, std::string message);
    std::list<std::string> copy();
    void clear();
};

#endif /* parse_warnings_hpp */
