//
//  structured_name.hpp
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

#ifndef structured_name_hpp
#define structured_name_hpp

#include <stdio.h>
#include <string>
#include <list>

#include "text_property.hpp"
#include "has_alt_Id.hpp"

#include <bridge/i_structured_name.hpp>


using namespace ProtonMail;

namespace ezvcard {
    

class StructuredName : public VCardProperty, public IStructuredName, HasAltId {
public:
    typedef std::shared_ptr<StructuredName> Ptr;
    const static std::string PROPERTYNAME;
    const static std::string CLASSNAME;
    
private:
    std::string _family;
    std::string _given;
    std::vector<std::string> _additional;
    std::vector<std::string> _prefixes;
    std::vector<std::string> _suffixes;
    
public:
    StructuredName();
    StructuredName(const StructuredName::Ptr& original);

    std::string getFamily();
    void setFamily(const std::string& family);
    std::string getGiven();
    void setGiven(const std::string& given);

    std::vector<std::string> getAdditionalNames();
    void clearNames();
    void addAdditionalName(const std::string& name);
    void addAdditionalNames(const std::vector<std::string>& names);
    std::vector<std::string> getPrefixes();
    void clearPrefixes();
    void addPrefix(const std::string& prefix);
    void addPrefixes(const std::vector<std::string>& prefixes);
    std::vector<std::string> getSuffixes();
    void clearSuffixes();
    void addSuffix(const std::string& suffix);
    void addSuffixes(const std::vector<std::string>& suffixes);

//    public List<String> getSortAs()
//    public void setSortAs(String family)
//    public void setSortAs(String family, String given)
//    public String getLanguage()
//    public void setLanguage(String language)
//    protected Map<String, Object> toStringValues()
//    public StructuredName copy()
//    public int hashCode()
    
    bool equals(const StructuredName::Ptr& obj) {
        if (!VCardProperty::equals(obj)) {
            return false;
        }
        if ( _family != obj->getFamily() ) {
            return false;
        }
        if ( _given != obj->getGiven() ) {
            return false;
        }
        
        if ( _additional != obj->getAdditionalNames() ) {
            return false;
        }
        if ( _prefixes != obj->getPrefixes() ) {
            return false;
        }
        if ( _suffixes != obj->getSuffixes() ) {
            return false;
        }
        return true;
    }
    
protected:
    void _validate(std::list<ValidationWarning::Ptr>& warnings, const VCardVersion::Ptr& version, const std::shared_ptr<VCard>& vcard);
    
    std::string _className() {
        return CLASSNAME;
    }
    
    std::string _getPropertyName() {
        return PROPERTYNAME;
    }
    
    std::string getAltId();
    void setAltId(const std::string& altId);

};



}


#endif /* structured_name_hpp */
