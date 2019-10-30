//
//  pid.hpp
//  OpenPGP
//
//  Created by Yanfeng Zhang on 1/10/17.
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

#ifndef pid_hpp
#define pid_hpp

#include <stdio.h>
#include <string>

class Pid {
public:
    typedef std::shared_ptr<Pid> Ptr;
    
private:
    uint64_t _localID, _clientPidMapReference = UINT32_MAX;
    
public:
    Pid(uint64_t localId, uint64_t clientPidMapReference);
    Pid(uint64_t localId);
    uint64_t getLocalId();
    uint64_t getClientPidMapReference();
    static Pid::Ptr valueOf(const std::string& value);
    std::string toString();
    bool equals(const Ptr& obj);
    //int hashCode() ;
};

inline bool operator==(const Pid::Ptr& lhs, const Pid::Ptr& rhs)
{
    return lhs->equals(rhs);
}

#endif /* pid_hpp */
