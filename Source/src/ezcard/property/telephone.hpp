//
//  telephone.hpp
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


#ifndef telephone_hpp
#define telephone_hpp

#include <stdio.h>



#include <stdio.h>
#include <string>
#include <list>

#include "text_property.hpp"
#include "has_alt_Id.hpp"
#include "tel_uri.hpp"
#include <bridge/i_telephone.hpp>

using namespace ProtonMail;
namespace ezvcard {
    
    /**
     * <p>
     * Defines a telephone number.
     * </p>
     *
     * <p>
     * <b>Code sample</b>
     * </p>
     *
     * <pre class="brush:java">
     * VCard vcard = new VCard();
     *
     * //text
     * Telephone tel = new Telephone("(123) 555-6789");
     * tel.getTypes().add(TelephoneType.HOME);
     * tel.setPref(2); //the second-most preferred
     * vcard.addTelephoneNumber(tel);
     *
     * //URI (vCard version 4.0 only)
     * TelUri uri = new TelUri.Builder("+1-800-555-9876").extension("111").build();
     * tel = new Telephone(uri);
     * tel.getTypes().add(TelephoneType.WORK);
     * tel.setPref(1); //the most preferred
     * vcard.addTelephoneNumber(tel);
     * </pre>
     *
     * <p>
     * <b>Property name:</b> {@code TEL}
     * </p>
     * <p>
     * <b>Supported versions:</b> {@code 2.1, 3.0, 4.0}
     * </p>
     * @author Michael Angstadt
     * @see <a href="http://tools.ietf.org/html/rfc6350#page-34">RFC 6350 p.34</a>
     * @see <a href="http://tools.ietf.org/html/rfc2426#page-14">RFC 2426 p.14</a>
     * @see <a href="http://www.imc.org/pdi/vcard-21.doc">vCard 2.1 p.13</a>
     */
    class Telephone : public VCardProperty, public ITelephone, HasAltId {
        
    public:
        const static std::string PROPERTYNAME;
        const static std::string CLASSNAME;
        
        typedef std::shared_ptr<Telephone> Ptr;
        
        
    private:
        std::string _text;
        TelUri::Ptr _uri;
        
    public:
        ~Telephone() {
            
        }
        Telephone(const std::string& text);
        Telephone(const std::string& text, const std::string& type);
        Telephone(const TelUri::Ptr& uri);
        //public Telephone(Telephone original) {
        
        void setText(const std::string& text);
        TelUri::Ptr getUri();
        void setUri(const TelUri::Ptr& uri);
        
        
        //    public List<TelephoneType> getTypes();
        //    public List<Pid> getPids();
        //    public Integer getPref();
        //    public void setPref(Integer pref);
        //    public String getAltId();
        //    public void setAltId(String altId);
        
        
    protected:
        
        void _validate(std::list<ValidationWarning::Ptr>& warnings, const VCardVersion::Ptr& version, const std::shared_ptr<VCard>& vcard) {
            if (_uri == nullptr && _text == "") {
                warnings.push_back(std::make_shared<ValidationWarning>(8));
            }
            
            if (_uri == nullptr && (version == VCardVersion::V2_1() || version == VCardVersion::V3_0())) {
                warnings.push_back(std::make_shared<ValidationWarning>(19));
            }
            
//            for (TelephoneType type : getTypes()) {
//                if (type == TelephoneType.PREF) {
//                    //ignore because it is converted to a PREF parameter for 4.0 vCards
//                    continue;
//                }
//                
//                if (!type.isSupportedBy(version)) {
//                    warnings.add(new ValidationWarning(9, type.getValue()));
//                }
//            }
        }
        
        //    protected Map<String, Object> toStringValues();
        //    public Telephone copy();
        //    public int hashCode();
        //    public boolean equals(Object obj);
        
    protected:
        std::string _className() {
            return CLASSNAME;
        }
        
        std::string _getPropertyName() {
            return PROPERTYNAME;
        }
        
        std::string getAltId();
        void setAltId(const std::string& altId);
      
        
        
    public: //ITelephone impl
        std::vector<std::string> getTypes();
        std::string getText();
    };
    
}

#endif /* telephone_hpp */
