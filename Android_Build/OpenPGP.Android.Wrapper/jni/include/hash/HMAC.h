//
//  HMAC.h
//  OpenPGP
//
//  Created by Yanfeng Zhang on 10/31/16.
//  Copyright © 2016 Yanfeng Zhang. All rights reserved.
//

#ifndef __HMAC_H__
#define __HMAC_H__

#include <hash/Hash.h>


namespace pm {
    std::string hash_hmac(std::string algo, std::string data, std::string key, bool is_raw_data = false);
}



#endif /* __HMAC_H__ */
