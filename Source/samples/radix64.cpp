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


#include <utilities/radix64.h>

std::string ascii2radix64(std::string str, char char62, char char63){
    std::string out = "", bin = "", pad = "";
    while (str.size() % 3){
        str += zero;
        pad += "=";
    }
    for(unsigned int x = 0; x < str.size(); x++){
        bin += makebin(str[x], 8);
    }
    unsigned int x = 0;
    while (x < bin.size()){
        out += ("ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789" + std::string(1, char62) + std::string(1, char63))[toint(bin.substr(x, 6), 2)];
        x += 6;
    }
    if (pad.size() == 2){                                            // string length % 3 == 1
        out = out.substr(0, out.size() - 2);
    }
    if (pad.size() == 1){                                            // string length % 3 == 2
        out = out.substr(0, out.size() - 1);
    }
    return out + pad;
}




std::string radix642ascii(std::string str, char char62, char char63){
    if (str.size() & 3){
        throw std::runtime_error("Error: Input string length is not a multiple of 4.");
    }
    
    std::string bin = "";
    
    // count padding
    uint8_t unpad = 0;
    while (str[str.size() - 1] == '='){
        unpad++;
        str = str.substr(0, str.size() - 1);
    }
    
    for(unsigned int x = 0; x < str.size(); x++){
        if (('A' <= str[x]) && (str[x] <= 'Z')){
            bin += makebin(str[x] - 0x41, 6);
        }
        else if (('a' <= str[x]) && (str[x] <= 'z')){
            bin += makebin(str[x] - 0x47, 6);
        }
        else if (('0' <= str[x]) && (str[x] <= '9')){
            bin += makebin(str[x] + 4, 6);
        }
        else if (str[x] == char62){
            bin += makebin(0x3e, 6);
        }
        else if (str[x] == char63){
            bin += makebin(0x3f, 6);
        }
        else{
            throw std::runtime_error("Error: Invalid Radix64 character found: " + std::string(1, str[x]));
        }
    }
    bin += std::string(unpad * 6, '0');
    str = "";
    for(unsigned int x = 0; x < bin.size(); x += 8){
        str += std::string(1, static_cast <unsigned char> (toint(bin.substr(x, 8), 2)));
    }
    return str.substr(0, str.size() - unpad); // remove padding when returning
}




// OpenPGP has an optional CRC24 checksum at the end of its Radix-64 encoded data
uint32_t crc24(const std::string & str){
    const uint32_t INIT = 0xB704CE;
    const uint32_t POLY = 0x1864CFB;
    uint32_t crc = INIT;
    for(unsigned int x = 0; x < str.size(); x++){
        crc ^= static_cast <unsigned char> (str[x]) << 16;
        for(unsigned int y = 0; y < 8; y++){
            crc <<= 1;
            if (crc & 0x1000000){
                crc ^= POLY;
            }
        }
    }
    return crc & 0xFFFFFF;
}




