//
//  ezvcard_impl.hpp
//  OpenPGP
//
//  Created by Yanfeng Zhang on 5/31/17.
//  Copyright © 2017 Yanfeng Zhang. All rights reserved.
//

#ifndef ezvcard_impl_h
#define ezvcard_impl_h


#include <bridge/i_ezvcard.hpp>

namespace ProtonMail {
    
    class EzvcardImpl : public IEzvcard {
        
    public:
        EzvcardImpl();
        ~EzvcardImpl();
        
    };
    
}


#endif /* ezvcard_impl_h */
