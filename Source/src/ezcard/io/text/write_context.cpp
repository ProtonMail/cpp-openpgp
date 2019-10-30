//
//  write_context.cpp
//  OpenPGP
//
//  Created by Yanfeng Zhang on 5/17/17.
//  Copyright © 2017 Yanfeng Zhang. All rights reserved.
//

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
