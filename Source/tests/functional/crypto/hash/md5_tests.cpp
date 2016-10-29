//
//  md5_test.cpp
//  OpenPGP
//
//  Created by Yanfeng Zhang on 10/28/16.
//  Copyright © 2016 Yanfeng Zhang. All rights reserved.
//

#import "utils_test.h"
#include <hash/MD5.h>

namespace tests {
    namespace md5_tests {
        SUITE(md5)
        {
            // Note: base64 works by encoding any 3 bytes as a four-byte string. Each triple is encoded independently of
            // previous and subsequent triples. If, for a given set of input bytes, the number is not an even multiple of 3,
            // the remaining 1 or two bytes are encoded and padded using '=' characters at the end. The encoding format is
            // defined by IETF RFC 4648. Such padding is only allowed at the end of a encoded string, which makes it impossible
            // to generally concatenate encoded strings and wind up with a string that is a valid base64 encoding.
            //
            // Since each triple of bytes is independent of others, we don't have to test particularly large sets if input data,
            // validating that the algorithm can process at least two triples should be sufficient.
            //
            
            TEST(MD5_RFC_1321) {
                
            }
        }
    }
}
