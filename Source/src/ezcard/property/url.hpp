//
//  url.hpp
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

#ifndef url_hpp
#define url_hpp

#include "uri_property.hpp"
#include "has_alt_Id.hpp"

#include <bridge/i_url.hpp>

using namespace ProtonMail;

namespace ezvcard {
    
    /**
     * <p>
     * Defines a URL that points to the person's homepage or business website.
     * </p>
     *
     * <p>
     * <b>Code sample</b>
     * </p>
     *
     * <pre class="brush:java">
     * VCard vcard = new VCard();
     *
     * Url url = new Url("http://www.company.com");
     * vcard.addUrl(url);
     * </pre>
     *
     * <p>
     * <b>Property name:</b> {@code URL}
     * </p>
     * <p>
     * <b>Supported versions:</b> {@code 2.1, 3.0, 4.0}
     * </p>
     * @author Michael Angstadt
     * @see <a href="http://tools.ietf.org/html/rfc6350#page-47">RFC 6350 p.47</a>
     * @see <a href="http://tools.ietf.org/html/rfc2426#page-25">RFC 2426 p.25</a>
     * @see <a href="http://www.imc.org/pdi/vcard-21.doc">vCard 2.1 p.21</a>
     */
    class Url : public UriProperty, public IUrl, HasAltId {
    public:
        const static std::string PROPERTYNAME;
        const static std::string CLASSNAME;
        
        typedef std::shared_ptr<Url> Ptr;

    public:
        /**
         * Creates a URL property.
         * @param url the URL (e.g. "http://example.com")
         */
        Url(const std::string& url) : UriProperty(url) {
            
        }
        
        //    public Url(Url original) {
        //    public String getMediaType() {
        //    public void setMediaType(String mediaType) {
        //    public List<Pid> getPids() {
        //    public Integer getPref() {
        //    public void setPref(Integer pref) {
        void setType(const std::string& type);
        //    public Url copy() {

        
    protected:
        std::string _className() {
            return CLASSNAME;
        }
        
        std::string _getPropertyName() {
            return PROPERTYNAME;
        }
        
        std::string getAltId();
        void setAltId(const std::string& altId);
        
    public: // bridge IUrl impl
        std::string getValue() final;
        std::string getType() final;
        
    };
    
}

#endif /* url_hpp */
