//
//  quoted_printable.hpp
//  OpenPGP
//
//  Created by Yanfeng Zhang on 5/19/17.
//  Copyright © 2017 Yanfeng Zhang. All rights reserved.
//

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
