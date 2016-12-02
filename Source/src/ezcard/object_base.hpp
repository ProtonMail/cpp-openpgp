//
//  object_base.hpp
//  OpenPGP
//
//  Created by Yanfeng Zhang on 1/12/17.
//  Copyright © 2017 Yanfeng Zhang. All rights reserved.
//

#ifndef object_base_hpp
#define object_base_hpp

#include <stdio.h>
#include <string>

class PMObject {
protected:
    virtual std::string _className() = 0;
    virtual std::string _getPropertyName() = 0;
    
public:
    std::string className() {
        return _className();
    }
    
    std::string getPropertyName() {
        return _getPropertyName();
    }
    
    
};


#endif /* object_base_hpp */
