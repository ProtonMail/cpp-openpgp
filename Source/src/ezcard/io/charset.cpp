//
//  charset.cpp
//  OpenPGP
//
//  Created by Yanfeng Zhang on 5/22/17.
//  Copyright © 2017 Yanfeng Zhang. All rights reserved.
//

#include "charset.hpp"
#include <ezvcard/util/string_util.hpp>

#include <string>
#include <codecvt>
#include <list>
#include <locale>


const  Charset::Ptr Charset::UTF_8 = std::make_shared<Charset>("UTF-8");
const  Charset::Ptr Charset::UTF_16 = std::make_shared<Charset>("UTF-16");

Charset::Charset(const std::string& name) {
    auto n = str_to_upper(name);
    if (n == "UTF-8" ||
        n == "UTF-16") {
        _name = n;
    } else {
        throw std::invalid_argument("Unsupported Charset");
    }
}

std::string Charset::getString(const std::string& input) {
    auto n = str_to_upper(_name);
    if (n == "UTF-16") {
        return to_utf16(input);
    }
    return input;
}

std::string Charset::getString(const std::wstring& input) {
    auto n = str_to_upper(_name);
    if (n == "UTF-16") {
        return to_utf16(input);
    }
    return to_string(input);
}

std::string Charset::to_utf16(const std::wstring &input) {
    std::wstring_convert<std::codecvt_utf16<wchar_t, 0x10ffff,  std::generate_header>> conv2;
    std::string u16str = conv2.to_bytes(input);
    return u16str;
}

std::string Charset::to_utf16(const std::string &input) {
    std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;
    std::wstring wide = converter.from_bytes(input);

    std::wstring_convert<std::codecvt_utf16<wchar_t, 0x10ffff,  std::generate_header>> conv2;
    std::string u16str = conv2.to_bytes(wide);
    
    return u16str;
}


std::string Charset::to_string(const std::wstring& input) {
    //setup converter
    using convert_type = std::codecvt_utf8<wchar_t>;
    std::wstring_convert<convert_type, wchar_t> converter;
    
    return converter.to_bytes( input );
}

Charset::Ptr Charset::forName(const std::string& name) {
    auto n = str_to_upper(name);
    
    if (n == "UTF-8") {
        return Charset::UTF_8;
    }
    if (n == "UTF-16") {
        return Charset::UTF_16;
    }
    
    throw std::invalid_argument("Unsupported Charset");
}

std::string Charset::name() {
    return _name;
}

