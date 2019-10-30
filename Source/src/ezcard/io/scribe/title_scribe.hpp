//
//  title_scribe.hpp
//  OpenPGP
//
//  Created by Yanfeng Zhang on 6/12/17.
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

#ifndef title_scribe_hpp
#define title_scribe_hpp

#include <stdio.h>
#include "string_property_scribe.hpp"
#include "title.hpp"

namespace ezvcard {
    
    /**
     * Marshals {@link Title} properties.
     * @author Michael Angstadt
     */
    class TitleScribe : public StringPropertyScribe<Title> {
    public:
        typedef std::shared_ptr<TitleScribe> Ptr;
        TitleScribe();
        
        
    protected:
        Title::Ptr _parseValue(const std::string& value);
        
        
    protected://PMObject
        std::string _className() {
            return "TitleScribe";
        }
    };
    
}

#endif /* title_scribe_hpp */
