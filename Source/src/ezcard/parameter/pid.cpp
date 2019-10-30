//
//  pid.cpp
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


#include "pid.hpp"
#include <iostream>
#include <strstream>

/**
 * Creates a new PID.
 * @param localId the local ID (cannot be null, must be positive)
 * @param clientPidMapReference an integer that references the property's
 * globally unique ID (optional, must be positive). It must match the first
 * value in an existing {@link ClientPidMap} property
 * @throws NullPointerException if local ID is null
 */
Pid::Pid(uint64_t localId, uint64_t clientPidMapReference) {
    _localID = localId;
    _clientPidMapReference = clientPidMapReference;
}

/**
 * Creates a new PID.
 * @param localId the local ID (cannot be null, must be positive)
 * @throws NullPointerException if local ID is null
 */
Pid::Pid(uint64_t localId) {
    _localID = localId;
    _clientPidMapReference = UINT32_MAX;
}

/**
 * Gets the local ID
 * @return the local ID
 */
uint64_t Pid::getLocalId() {
    return _localID;
}

/**
 * Gets the reference to the property's globally unique ID (stored in a
 * {@link ClientPidMap} property).
 * @return the reference ID or null if not set
 */
uint64_t Pid::getClientPidMapReference() {
    return _clientPidMapReference;
}

/**
 * Parses a string into a {@link Pid} object.
 * @param value the string value (e.g. "1.2")
 * @return the {@link Pid} object
 * @throws NumberFormatException if there's a problem parsing the string
 */
 Pid::Ptr Pid::valueOf(const std::string& value) {
     
     std::string localIdStr, clientPidMapReferenceStr;
     auto found = value.find('.');
     if (found != std::string::npos) {
         localIdStr = value.substr(0, found);
         clientPidMapReferenceStr = value.substr(found+1, value.size() - found);
     } else {
         localIdStr = value;
         clientPidMapReferenceStr = "";
     }
     Pid::Ptr out = nullptr;
     try {
         uint64_t myint = std::stoi(localIdStr);
         out = std::make_shared<Pid>(myint);
     } catch (std::exception& ex) {
         //TODO:: handle exception later
         return out;
     }
     
     try {
         uint64_t myint = std::stoi(clientPidMapReferenceStr);
         out->_clientPidMapReference = myint;
     } catch (std::exception& ex) {
         //TODO:: handle exception later
         //std::cout << ex.what() << std::endl;
     }
     return out;
}

std::string Pid::toString() {
    std::strstream ss;
    if (_clientPidMapReference == UINT32_MAX) {
        ss << _localID;
    } else {
        ss << _localID;
        ss << ".";
        ss << _clientPidMapReference;
    }
    return ss.str();
}

//@Override
//public int Pid::hashCode() {
//    final int prime = 31;
//    int result = 1;
//    result = prime * result + ((clientPidMapReference == null) ? 0 : clientPidMapReference.hashCode());
//    result = prime * result + localId.hashCode();
//    return result;
//}

bool Pid::equals(const Ptr& obj) {
    if (obj == nullptr)
        return false;
    if (this == obj.get())
        return true;
    
    if (_clientPidMapReference != obj->getClientPidMapReference())
        return false;
    
    if (_localID != obj->getLocalId())
        return false;
    
    return true;
}

