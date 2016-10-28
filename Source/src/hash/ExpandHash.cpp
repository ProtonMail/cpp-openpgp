//
//  ExpandHash.cpp
//  OpenPGP_OSX_Lib
//
//  Created by Yanfeng Zhang on 10/6/16.
//  Copyright © 2016 Yanfeng Zhang. All rights reserved.
//

#include <hash/ExpandHash.h>
#include <sstream>
#include <hash/Hashes.h>

std::string ExpandHash(const std::string & input) {
    
    std::stringstream s;
    
    std::string sha1 = SHA512(input).digest();
    
    
    std::string sha2 = SHA512(input).digest();
    
    std::string sha3 = SHA512(input).digest();
    
    std::string sha4 = SHA512(input).digest();
    //
    //    var value: UInt8 = 0x00
    //    ret_data.appendData(input.sha512_byte)
    //    ret_data.appendBytes(&value, length: 1)
    //
    //    value = 0x01
    //    ret_data.appendData(input.sha512_byte)
    //    ret_data.appendBytes(&value, length: 1)
    //
    //    value = 0x02
    //    ret_data.appendData(input.sha512_byte)
    //    ret_data.appendBytes(&value, length: 1)
    //
    //    value = 0x03
    //    ret_data.appendData(input.sha512_byte)
    //    ret_data.appendBytes(&value, length: 1)
    //    
    //    return NSData(data: ret_data)
    return input;
}
