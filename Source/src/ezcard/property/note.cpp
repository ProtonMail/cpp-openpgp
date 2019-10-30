//
//  note.cpp
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


#include "note.hpp"

namespace ProtonMail {
    
    std::shared_ptr<INote> INote::create_instance(const std::string &type, const std::string &note) {
        auto out = std::make_shared<ezvcard::Note>(note);
        out->setType(type);
        return out;
    }
}

namespace ezvcard {
    
    const std::string Note::PROPERTYNAME = "NOTE";
    const std::string Note::CLASSNAME = "Note";

    std::string Note::_className() {
        return CLASSNAME;
    }
    std::string Note::_getPropertyName() {
        return PROPERTYNAME;
    }
    
    std::string Note::getAltId() {
        return _parameters->getAltId();
    }
    void Note::setAltId(const std::string& altId) {
        _parameters->setAltId(altId);
    }
}

//
//
///**
// * <p>
// * Defines a free-form text field that contains miscellaneous information.
// * </p>
// *
// * <p>
// * <b>Code sample</b>
// * </p>
// *
// * <pre class="brush:java">
// * VCard vcard = new VCard();
// *
// * Note note = new Note("This is a\nnote property.");
// * vcard.addNote(note);
// * </pre>
// *
// * <p>
// * <b>Property name:</b> {@code NOTE}
// * </p>
// * <p>
// * <b>Supported versions:</b> {@code 2.1, 3.0, 4.0}
// * </p>
// * @author Michael Angstadt
// * @see <a href="http://tools.ietf.org/html/rfc6350#page-44">RFC 6350 p.44</a>
// * @see <a href="http://tools.ietf.org/html/rfc2426#page-21">RFC 2426 p.21</a>
// * @see <a href="http://www.imc.org/pdi/vcard-21.doc">vCard 2.1 p.19</a>
// */
//public class Note extends TextProperty implements HasAltId {
//    /**
//     * Creates a note property.
//     * @param note the note text
//     */
//    public Note(String note) {
//        super(note);
//    }
//    
//    /**
//     * Copy constructor.
//     * @param original the property to make a copy of
//     */
//    public Note(Note original) {
//        super(original);
//    }
//    
//    @Override
//    public List<Pid> getPids() {
//        return super.getPids();
//    }
//    
//    @Override
//    public Integer getPref() {
//        return super.getPref();
//    }
//    
//    @Override
//    public void setPref(Integer pref) {
//        super.setPref(pref);
//    }
//    
//    //@Override
//    public String getAltId() {
//        return parameters.getAltId();
//    }
//    
//    //@Override
//    public void setAltId(String altId) {
//        parameters.setAltId(altId);
//    }
//    
//    /**
//     * Gets the TYPE parameter.
//     * <p>
//     * <b>Supported versions:</b> {@code 4.0}
//     * </p>
//     * @return the TYPE value (typically, this will be either "work" or "home")
//     * or null if it doesn't exist
//     */
//    public String getType() {
//        return parameters.getType();
//    }
//    
//    /**
//     * Sets the TYPE parameter.
//     * <p>
//     * <b>Supported versions:</b> {@code 4.0}
//     * </p>
//     * @param type the TYPE value (this should be either "work" or "home") or
//     * null to remove
//     */
//    public void setType(String type) {
//        parameters.setType(type);
//    }
//    
//    @Override
//    public String getLanguage() {
//        return super.getLanguage();
//    }
//    
//    @Override
//    public void setLanguage(String language) {
//        super.setLanguage(language);
//    }
//    
//    @Override
//    public Note copy() {
//        return new Note(this);
//    }
//}
