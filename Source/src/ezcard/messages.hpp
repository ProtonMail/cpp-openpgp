//
//  messages.hpp
//  OpenPGP
//
//  Created by Yanfeng Zhang on 1/17/17.
//  Copyright © 2017 Yanfeng Zhang. All rights reserved.
//

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
