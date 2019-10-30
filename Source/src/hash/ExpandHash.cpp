//
//  ExpandHash.cpp
//  OpenPGP_OSX_Lib
//
//  Created by Yanfeng Zhang on 10/6/16.
//
//  The MIT License
// 
//  Copyright (c) 2019 Proton Technologies AG
// 
//  Permission is hereby granted, free of charge, to any person obtaining a copy
//  of this software and associated documentation files (the "Software"), to deal
//  in the Software without restriction, including without limitation the rights
//  to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
//  copies of the Software, and to permit persons to whom the Software is
//  furnished to do so, subject to the following conditions:
// 
//  The above copyright notice and this permission notice shall be included in
//  all copies or substantial portions of the Software.
// 
//  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
//  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
//  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
//  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
//  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
//  OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
//  THE SOFTWARE.

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
