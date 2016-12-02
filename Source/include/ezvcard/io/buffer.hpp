//
//  buffer.hpp
//  OpenPGP
//
//  Created by Yanfeng Zhang on 12/6/16.
//  Copyright © 2016 Yanfeng Zhang. All rights reserved.
//

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
