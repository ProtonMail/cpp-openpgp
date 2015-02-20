//
//  BaseObject.h
//  OpenPGP_OSX_Lib
//
//  Created by Yanfeng Zhang on 2/19/15.
//  Copyright (c) 2015 Yanfeng Zhang. All rights reserved.
//

#ifndef __OpenPGP_OSX_Lib__BaseObject__
#define __OpenPGP_OSX_Lib__BaseObject__


class BaseObject
{
private:
    bool is_debug_;
    
    
public:
    void set_is_debug(bool debug);
    bool get_is_debug();
    
    BaseObject();
    BaseObject(bool debug);
    ~BaseObject();
};

#endif /* defined(__OpenPGP_OSX_Lib__BaseObject__) */
