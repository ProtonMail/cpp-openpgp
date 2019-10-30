//
//  agent.hpp
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


#ifndef agent_hpp
#define agent_hpp

#include <stdio.h>
#include <string>
#include <list>

#include "text_property.hpp"
#include "has_alt_Id.hpp"
#include "vcard.hpp"

namespace ezvcard {
    
    /**
     * <p>
     * Defines information about the person's agent.
     * </p>
     *
     * <p>
     * <b>Code sample (creating)</b>
     * </p>
     *
     * <pre class="brush:java">
     * VCard vcard = new VCard();
     *
     * //URL
     * Agent agent = new Agent("http://www.linkedin.com/BobSmith");
     * vcard.setAgent(agent);
     *
     * //vCard
     * VCard agentVCard = new VCard();
     * agentVCard.setFormattedName("Bob Smith");
     * agentVCard.addTelephoneNumber("(555) 123-4566");
     * agentVCard.addUrl("http://www.linkedin.com/BobSmith");
     * agent = new Agent(agentVCard);
     * vcard.setAgent(agent);
     * </pre>
     *
     * <p>
     * <b>Code sample (retrieving)</b>
     * </p>
     *
     * <pre class="brush:java">
     * VCard vcard = ...
     * Agent agent = vcard.getAgent();
     *
     * String url = agent.getUrl();
     * if (url != null) {
     *   //property value is a URL
     * }
     *
     * VCard agentVCard = agent.getVCard();
     * if (agentVCard != null) {
     *   //property value is a vCard
     * }
     * </pre>
     *
     * <p>
     * <b>Property name:</b> {@code AGENT}
     * </p>
     * <p>
     * <b>Supported versions:</b> {@code 2.1, 3.0}
     * </p>
     *
     * @author Michael Angstadt
     * @see <a href="http://tools.ietf.org/html/rfc2426#page-19">RFC 2426 p.19</a>
     * @see <a href="http://www.imc.org/pdi/vcard-21.doc">vCard 2.1 p.18</a>
     */
    class Agent : public VCardProperty {
        
    public:
        typedef std::shared_ptr<Agent> Ptr;
        const static std::string PROPERTYNAME;
        const static std::string CLASSNAME;
        
        Agent();
        Agent(const std::string& url);
        Agent(const VCard::Ptr& vcard);
        Agent(const Agent::Ptr& original);
        
    private:
        std::string _url;
        VCard::Ptr _vcard;

    public:
        
        //    public String getUrl()
        //    public void setUrl(String url)
        //    public VCard getVCard() {
        //    public void setVCard(VCard vcard) {
        //    public Agent copy()
        //    public int hashCode()
        //    public boolean equals(Object obj)
        
    protected:
        std::vector<VCardVersion::Ptr> _getSupportedVersions();
        void _validate(std::list<ValidationWarning::Ptr>& warnings, const VCardVersion::Ptr& version, const std::shared_ptr<VCard>& vcard);
        //    protected Map<String, Object> toStringValues()

    protected: //PMObject part
        //override
        std::string _className() {
            return CLASSNAME;
        }
        
        std::string _getPropertyName() {
            return PROPERTYNAME;
        }
        

    };
}


#endif /* agent_hpp */
