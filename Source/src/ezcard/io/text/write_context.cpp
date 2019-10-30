//
//  write_context.cpp
//  OpenPGP
//
//  Created by Yanfeng Zhang on 5/17/17.
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


#include "write_context.hpp"



/**
 * @param version the version that the vCard should adhere to
 * @param targetApplication the application that the vCard is being targeted
 * for or null not to target any specific application
 * @param includeTrailingSemicolons true to include trailing semicolon
 * delimiters for structured property values whose list of values end with
 * null or empty values, false not to
 */
WriteContext::WriteContext(VCardVersion::Ptr version, TargetApplication targetApplication, bool includeTrailingSemicolons) {
    _version = version;
    _targetApplication = targetApplication;
    _includeTrailingSemicolons = includeTrailingSemicolons;
}

/**
 * Gets the version that the vCard should adhere to.
 * @return the vCard version
 */
VCardVersion::Ptr WriteContext::getVersion() {
    return _version;
}

/**
 * Gets the application that the vCard is being targeted for.
 * @return the target application or null not to target any specific
 * application
 */
TargetApplication WriteContext::getTargetApplication() {
    return _targetApplication;
}

/**
 * Gets whether to include trailing semicolon delimiters for structured
 * property values whose list of values end with null or empty values.
 * @return true to include the trailing semicolons, false not to
 */
bool WriteContext::isIncludeTrailingSemicolons() {
    return _includeTrailingSemicolons;
}
