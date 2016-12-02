//
//  title.hpp
//  OpenPGP
//
//  Created by Yanfeng Zhang on 1/10/17.
//  Copyright © 2017 Yanfeng Zhang. All rights reserved.
//

#ifndef title_hpp
#define title_hpp

#include <stdio.h>
#include "text_property.hpp"
#include "has_alt_Id.hpp"
#include "i_title.hpp"

namespace ezvcard {
    
    /**
     * <p>
     * Defines the person's title in his or her organization.
     * </p>
     *
     * <p>
     * <b>Code sample</b>
     * </p>
     *
     * <pre class="brush:java">
     * VCard vcard = new VCard();
     *
     * Title title = new Title("Research Scientist");
     * vcard.addTitle(title);
     * </pre>
     *
     * <p>
     * <b>Property name:</b> {@code TITLE}
     * </p>
     * <p>
     * <b>Supported versions:</b> {@code 2.1, 3.0, 4.0}
     * </p>
     *
     * @author Michael Angstadt
     * @see <a href="http://tools.ietf.org/html/rfc6350#page-39">RFC 6350 p.39</a>
     * @see <a href="http://tools.ietf.org/html/rfc2426#page-17">RFC 2426 p.17</a>
     * @see <a href="http://www.imc.org/pdi/vcard-21.doc">vCard 2.1 p.17</a>
     */
    class Title : public TextProperty, public ITitle, HasAltId {
        
    public:
        typedef std::shared_ptr<Title> Ptr;
        const static std::string PROPERTYNAME;
        const static std::string CLASSNAME;
        
        Title(const std::string& title);

        //        public Title(Title original) {
        
        //        public String getLanguage() {
        //        public void setLanguage(String language) {
        std::string getType();
        void setType(const std::string& type);
        
        
        //        @Override
        //        public List<Pid> getPids() {
        //        @Override
        //        public Integer getPref() {
        //        @Override
        //        public void setPref(Integer pref) {
        //        @Override
        //        public Title copy() {
        
        
        std::string getTitle();
        
    protected: //PMObject
        std::string _className();
        std::string _getPropertyName();
        
    protected: //impl HasAltId
        std::string getAltId();
        void setAltId(const std::string& altId);


    };
}


#endif /* title_hpp */


