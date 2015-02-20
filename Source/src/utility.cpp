//
//  utility.cpp
//  OpenPGP
//
//  Created by Yanfeng Zhang on 1/31/15.
//  Copyright (c) 2015 Yanfeng Zhang. All rights reserved.
//

#include "utility.h"


namespace pm {
    void optimized_trim(std::string& s)
    {
        std::string::size_type pos = s.find_last_not_of(' ');
        if(pos != std::string::npos)
        {
            if (s.length()!=pos+1)//if there are trailing whitespaces erase them
                s.erase(pos+1);
            pos = s.find_first_not_of(' ');
            if(pos!=0) //if there are leading whitespaces erase them
                s.erase(0, pos);
        }
        else s="";
    }
}

