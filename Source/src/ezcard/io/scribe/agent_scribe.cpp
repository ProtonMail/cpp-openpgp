//
//  agent_scribe.cpp
//  OpenPGP
//
//  Created by Yanfeng Zhang on 1/11/17.
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


#include "agent_scribe.hpp"

namespace ezvcard {
    

AgentScribe::AgentScribe() : VCardPropertyScribeWrapper(Agent::PROPERTYNAME) {
    
}

//            @Override
//            protected VCardDataType _defaultDataType(VCardVersion version) {
//                return null;
//            }
//
//            @Override
//            protected VCardDataType _dataType(Agent property, VCardVersion version) {
//                if (property.getUrl() != null) {
//                    return (version == VCardVersion.V2_1) ? VCardDataType.URL : VCardDataType.URI;
//                }
//                return null;
//            }
//
//            @Override
//            protected String _writeText(Agent property, WriteContext context) {
//                String url = property.getUrl();
//                if (url != null) {
//                    return url;
//                }
//
//                VCard vcard = property.getVCard();
//                if (vcard != null) {
//                    throw new EmbeddedVCardException(vcard);
//                }
//
//                //don't write an empty value because parsers could interpret that as there being an embedded vCard on the next line
//                throw new SkipMeException(Messages.INSTANCE.getValidationWarning(8));
//            }
//
//            @Override
//            protected Agent _parseText(String value, VCardDataType dataType, VCardParameters parameters, ParseContext context) {
//                Agent property = new Agent();
//
//                if (dataType == null) {
//                    throw new EmbeddedVCardException(new Injector(property));
//                }
//
//                property.setUrl(VObjectPropertyValues.unescape(value));
//                return property;
//            }
//
//            @Override
//            protected Agent _parseHtml(HCardElement element, ParseContext context) {
//                Agent property = new Agent();
//
//                Set<String> classes = element.classNames();
//                if (classes.contains("vcard")) {
//                    throw new EmbeddedVCardException(new Injector(property));
//                }
//
//                String url = element.absUrl("href");
//                if (url.length() == 0) {
//                    url = element.value();
//                }
//                property.setUrl(url);
//
//                return property;
//            }
//
//            private static class Injector implements EmbeddedVCardException.InjectionCallback {
//                private final Agent property;
//
//                public Injector(Agent property) {
//                    this.property = property;
//                }
//
//                public void injectVCard(VCard vcard) {
//                    property.setVCard(vcard);
//                }
//
//                public VCardProperty getProperty() {
//                    return property;
//                }
//            }


}
