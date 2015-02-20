//
//  BaseObject.cpp
//  OpenPGP_OSX_Lib
//
//  Created by Yanfeng Zhang on 2/19/15.
//  Copyright (c) 2015 Yanfeng Zhang. All rights reserved.
//

#include "base/BaseObject.h"



void BaseObject::set_is_debug(bool debug)
{
    is_debug_ = debug;
}

bool BaseObject::get_is_debug()
{
    return is_debug_;
}

BaseObject::BaseObject()
{
    is_debug_ = false;
}

BaseObject::BaseObject(bool debug)
{
    set_is_debug(debug);
}

BaseObject::~BaseObject()
{
    
}