//
//  base64.h
//  OpenPGP
//
//  Created by Yanfeng Zhang on 1/31/15.
//  Copyright (c) 2015 Yanfeng Zhang. All rights reserved.
//

#ifndef __OpenPGP__base64__
#define __OpenPGP__base64__

#include <string>
#include "UTF8.h"


std::string base64_encode(unsigned char const* , unsigned int len);
std::string base64_encode(std::string const& s);

std::string base64_decode(std::string const& s);



std::string base64_encode(unsigned char const* , unsigned int len);


//std::string base64_decode(std::string const& s);


//std::string encode_utf8_base64(std::string & in);
std::string decode_utf8_base64(std::string & in);
//std::string encode_utf8_base64_msg(std::string & in);
std::string decode_utf8_base64_msg(std::string & in);


std::string string_to_hex(const std::string& input);
std::string hex_to_string(const std::string& input);


#endif /* defined(__OpenPGP__base64__) */
