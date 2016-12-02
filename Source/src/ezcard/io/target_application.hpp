//
//  target_application.h
//  OpenPGP
//
//  Created by Yanfeng Zhang on 5/17/17.
//  Copyright © 2017 Yanfeng Zhang. All rights reserved.
//

#ifndef target_application_hpp
#define target_application_hpp

enum TargetApplication {
    /**
     * Microsoft Outlook
     * An empty line is required after all base64-encoded property values
     * for vCard versions 2.1 and 3.0
     */
    OUTLOOK,
    
    //should be default
    Others
};


#endif /* target_application_hpp */
