//
//  pid.hpp
//  OpenPGP
//
//  Created by Yanfeng Zhang on 1/10/17.
//  Copyright © 2017 Yanfeng Zhang. All rights reserved.
//

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
