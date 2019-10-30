//
//  write_context.hpp
//  OpenPGP
//
//  Created by Yanfeng Zhang on 5/17/17.
//  Copyright © 2017 Yanfeng Zhang. All rights reserved.
//

#ifndef write_context_hpp
#define write_context_hpp

#include <stdio.h>

#include "vcard_version.hpp"
#include "target_application.hpp"


/**
 * Used to pass information about the vCard being written to the property
 * scribes.
 * @author Michael Angstadt
 */
class WriteContext {
public:
    typedef std::shared_ptr<WriteContext> Ptr;
    
    
private:
    VCardVersion::Ptr _version;
    TargetApplication _targetApplication = TargetApplication::Others;
    bool _includeTrailingSemicolons;
    
public:
    WriteContext(VCardVersion::Ptr version, TargetApplication targetApplication, bool includeTrailingSemicolons);

    VCardVersion::Ptr getVersion();
    TargetApplication getTargetApplication();
    bool isIncludeTrailingSemicolons();
};



#endif /* write_context_hpp */
