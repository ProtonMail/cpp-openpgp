//
//  clearable_string_builder.hpp
//  OpenPGP
//
//  Created by Yanfeng Zhang on 1/18/17.
//  Copyright © 2017 Yanfeng Zhang. All rights reserved.
//

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
