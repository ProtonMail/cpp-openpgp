//
//  rsa_key.h
//  UNNetPGP
//
//  Created by Yanfeng Zhang on 1/22/15.
//  Copyright (c) 2015 UP-NEXT. All rights reserved.
//

#ifndef __UNNetPGP__rsa_key__
#define __UNNetPGP__rsa_key__

#include <stdio.h>
#include "openpgp.h"


class rsa_key {
public:
    BIGNUM         *d;
    BIGNUM         *p;
    BIGNUM         *q;
    BIGNUM         *u;
};




#endif /* defined(__UNNetPGP__rsa_key__) */
