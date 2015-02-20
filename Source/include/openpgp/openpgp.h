//
//  openpgp.h
//  OpenPGP
//
//  Created by Yanfeng Zhang on 1/21/15.
//  Copyright (c) 2015 UP-NEXT. All rights reserved.
//

#ifndef __OpenPGP__openpgp__
#define __OpenPGP__openpgp__

#include <utility>
#include <string>


#ifdef HAVE_SYS_CDEFS_H
#include <sys/cdefs.h>
#endif

#if defined(__NetBSD__)
__COPYRIGHT("@(#) Copyright (c) 2009 The NetBSD Foundation, Inc. All rights reserved.");
__RCSID("$NetBSD: openssl_crypto.c,v 1.32 2010/11/07 06:56:52 agc Exp $");
#endif

#ifdef HAVE_OPENSSL_DSA_H
#include <openssl/dsa.h>
#endif

#ifdef HAVE_OPENSSL_RSA_H
#include <openssl/rsa.h>
#endif

#ifdef HAVE_OPENSSL_ERR_H
#include <openssl/err.h>
#endif

#include <openssl/pem.h>
#include <openssl/evp.h>

#include <stdlib.h>
#include <string.h>

#ifdef HAVE_UNISTD_H
#include <unistd.h>
#endif
#define NETPGP_BUFSIZ	8192

#include "BaseObject.h"

namespace pgp {

    class openpgp : public BaseObject {
    
public:
    openpgp();
    ~openpgp();
    void generate_new_key(int bits, std::string passphrase, std::string userid);
    void encrypt_message();
};

    
}



#endif /* defined(__OpenPGP__openpgp__) */
