//
//  categories.hpp
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

#ifndef categories_hpp
#define categories_hpp

#include <stdio.h>
#include "text_list_property.hpp"
#include "has_alt_Id.hpp"
#include "i_categories.hpp"

namespace ezvcard {
    
    /**
     * <p>
     * Defines a list of keywords that can be used to describe the person.
     * </p>
     *
     * <p>
     * <b>Code sample</b>
     * </p>
     *
     * <pre class="brush:java">
     * VCard vcard = new VCard();
     *
     * Categories categories = new Categories();
     * categories.getValues().add("Developer");
     * categories.getValues().add("Java coder");
     * categories.getValues().add("Ladies' man");
     * vcard.setCategories(categories);
     * </pre>
     *
     * <p>
     * <b>Property name:</b> {@code CATEGORIES}
     * </p>
     * <p>
     * <b>Supported versions:</b> {@code 3.0, 4.0}
     * </p>
     * @author Michael Angstadt
     * @see <a href="http://tools.ietf.org/html/rfc6350#page-43">RFC 6350 p.43</a>
     * @see <a href="http://tools.ietf.org/html/rfc2426#page-20">RFC 2426 p.20</a>
     */
    //    @SupportedVersions({ VCardVersion.V3_0, VCardVersion.V4_0 })
    class Categories : public TextListProperty, public ICategories, HasAltId {
    public:
        typedef std::shared_ptr<Categories> Ptr;
        const static std::string PROPERTYNAME;
        const static std::string CLASSNAME;
        
        Categories();
        //std::string getType();
        //void setType(const std::string& type);
        
    protected: //PMObject
        std::string _className();
        std::string _getPropertyName();
        
    protected: //impl HasAltId
        std::string getAltId();
        void setAltId(const std::string& altId);
        
    protected: //TextListProperty : VCardProperty
        std::vector<VCardVersion::Ptr> _getSupportedVersions();
        
    public: //ICategories
        std::vector<std::string> getValues() final;
        void addValue(const std::string & text) final;
        void setValues(const std::vector<std::string> & values) final;
        std::string getGroup() final;
        void setGroup(const std::string & g) final;
    };
}



#endif /* categories_hpp */
