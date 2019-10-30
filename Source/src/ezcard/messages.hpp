//
//  messages.hpp
//  OpenPGP
//
//  Created by Yanfeng Zhang on 1/17/17.
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


#ifndef messages_hpp
#define messages_hpp

#include <stdio.h>
#include <string>
#include <unordered_map>
#include <exception>


class Messages {
public:
    typedef std::shared_ptr<Messages> Ptr;
    
private:
    static Messages::Ptr single;
    Messages();
    std::unordered_map<std::string, std::string> _error_tempate;
    
public:
    static Messages::Ptr getInstance();
    ~Messages();
    
    template<typename Arg0, typename ... Args>
    std::string getValidationWarning(Arg0 &&code, Args &&... args) {
        auto key = "validate." + std::to_string(code);
        return getMessage(key, args...);
    }
    
    template<typename Arg0, typename ... Args>
    std::string getParseMessage(Arg0 &&code, Args &&... args) {
        auto key = "parse." + std::to_string(code);
        return getMessage(key, args...);
    }
    
    template<typename Arg0, typename ... Args>
    std::string getExceptionMessage(Arg0 &&code, Args &&... args) {
        auto key = "exception." + std::to_string(code);
        return getMessage(key, args...);
    }
    
    template<typename Arg0, typename ... Args>
    std::invalid_argument getIllegalArgumentException(Arg0 &&code, Args &&... args) {
        auto message = getExceptionMessage(code, args...);
        if (message.empty()) {
            return std::invalid_argument("unknow exception." + std::to_string(code));
        } else {
            return std::invalid_argument(message);
        }
    }
    
    std::string getMessage(const std::string& key);
    std::string getMessage(const std::string& key, int value);
    std::string getMessage(const std::string& key, const std::string& value);
    std::string getMessage(const std::string& key, const std::string& value1, const std::string& value2);
    std::string getMessage(const std::string& key, const std::string& value1, const std::string& value2, const std::string& value3);
    
};


#endif /* messages_hpp */
