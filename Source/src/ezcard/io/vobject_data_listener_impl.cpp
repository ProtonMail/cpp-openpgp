//
//  vobject_data_listener_impl.cpp
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


#include "vobject_data_listener_impl.hpp"
#include "label.hpp"
#include "vcard_parameters.hpp"
#include "raw_property_scribe.hpp"
#include "vcard_data_type.hpp"
#include "vcard_version.hpp"


namespace vinnie {
    
    VObjectDataListenerImpl::VObjectDataListenerImpl() : _defaultVersion(VCardVersion::V2_1()), _index(nullptr) {
        
    }
    
    VObjectDataListenerImpl::VObjectDataListenerImpl(const VCardVersion::Ptr v, ScribeIndex::Ptr index) : _defaultVersion(v), _index(index) {
        
    }
    
    bool VObjectDataListenerImpl::isVCardComponent(const std::string &componentName)
    {
        return "VCARD" == componentName;
    }
    
    bool VObjectDataListenerImpl::inVCardComponent(const std::list<std::string> &parentComponents)  {
        if (parentComponents.size() <= 0) {
            return false;
        }
        auto last = parentComponents.back();
        return isVCardComponent(last);
    }
    
    void VObjectDataListenerImpl::onComponentBegin(const std::string& name, const Context::Ptr &context) {
        if (!isVCardComponent(name)) {
            //ignore non-VCARD components
            return;
        }
        
        auto vcard = std::make_shared<VCard>(_defaultVersion);
        if (_stack->isEmpty()) {
            root = vcard;
        }
        _stack->push(vcard);
        
        //    if (embeddedVCardException != null) {
        //        embeddedVCardException.injectVCard(vcard);
        //        embeddedVCardException = null;
        //    }
    }
    
    void VObjectDataListenerImpl::onComponentEnd(const std::string& name, const Context::Ptr& context) {
        if (!isVCardComponent(name)) {
            //ignore non-VCARD components
            return;
        }
        
        inVCardComponent(*context->getParentComponents());
        auto item = _stack->pop();
        // assignLabels(item.vcard, item.labels);
        
        if (_stack->isEmpty()) {
            context->stop();
        }
    }
    
    void VObjectDataListenerImpl::onProperty(const VObjectProperty::Ptr& vobjectProperty, const Context::Ptr& context) {
        if (!inVCardComponent(*context->getParentComponents())) {
            //ignore properties that are not directly inside a VCARD component
            return;
        }
        //
        //        if (embeddedVCardException != null) {
        //            //the next property was supposed to be the start of a nested vCard, but it wasn't
        //            embeddedVCardException.injectVCard(null);
        //            embeddedVCardException = null;
        //        }
        //
        
        auto curVCard = _stack->peek()->_vcard;
        auto version = std::dynamic_pointer_cast<VCardVersion>(curVCard->getVersion());
        
        VCardProperty::Ptr property = parseProperty(vobjectProperty, version, context->getLineNumber());
        if (property != nullptr) {
            curVCard->addProperty(property);
        }
    }
    
    VCardProperty::Ptr VObjectDataListenerImpl::parseProperty(const VObjectProperty::Ptr& vobjectProperty, VCardVersion::Ptr version, int lineNumber) {
        if (vobjectProperty == nullptr) {
            std::cout << "error" << std::endl;
        }
        
        auto group = vobjectProperty->getGroup();
        auto name = vobjectProperty->getName();
        
        auto parameters =  std::make_shared<VCardParameters>(vobjectProperty->getParameters()->getMap());
        auto value = vobjectProperty->getValue();
        
        //sanitize the parameters
        processNamelessParameters(parameters);
        processQuotedMultivaluedTypeParams(parameters, version);
        
        //get the scribe
        
        VCardPropertyScribe::Ptr scribe = _index->getPropertyScribe(name);
        if (scribe == nullptr) {
            scribe = std::make_shared<RawPropertyScribe>(name);
        }
        //get the data type (VALUE parameter)
        VCardDataType::Ptr dataType = VCardDataType::TEXT; //parameters.getValue();
        //parameters.setValue(null);
        if (dataType == nullptr) {
            //use the default data type if there is no VALUE parameter
            dataType = scribe->defaultDataType(version);
        }
        //
        VCardProperty::Ptr property;
        
        Result::Ptr result = scribe->parseText(value, dataType, version, parameters);
        
        for (auto warning : result->getWarnings()) {
            //warnings.add(lineNumber, name, warning);
        }
        property = result->getProperty();
        
        //    try {
        //        Result<? extends VCardProperty> result = scribe.parseText(value, dataType, version, parameters);
        //        for (String warning : result.getWarnings()) {
        //            warnings.add(lineNumber, name, warning);
        //        }
        //        property = result.getProperty();
        //    } catch (SkipMeException e) {
        //        handleSkippedProperty(name, lineNumber, e);
        //        return null;
        //    } catch (CannotParseException e) {
        //        property = handleUnparseableProperty(name, parameters, value, dataType, lineNumber, version, e);
        //    } catch (EmbeddedVCardException e) {
        //        handledEmbeddedVCard(name, value, lineNumber, e);
        //        property = e.getProperty();
        //    }
        
        property->setGroup(group);
        
        /*
         * LABEL properties must be treated specially so they can be matched
         * up with the ADR properties that they belong to. LABELs are not
         * added to the vCard as properties, they are added to the ADR
         * properties they belong to (unless they cannot be matched up with
         * an ADR).
         */
        //    if (property instanceof Label) {
        //        Label label = (Label) property;
        //        stack.peek().labels.add(label);
        //        return null;
        //    }
        //
        //    handleLabelParameter(property);
        
        return property;
    }
    //
    //        private void handleSkippedProperty(String propertyName, int lineNumber, SkipMeException e) {
    //            warnings.add(lineNumber, propertyName, 22, e.getMessage());
    //        }
    //
    //        private VCardProperty handleUnparseableProperty(String name, VCardParameters parameters, String value, VCardDataType dataType, int lineNumber, VCardVersion version, CannotParseException e) {
    //            warnings.add(lineNumber, name, 25, value, e.getMessage());
    //            RawPropertyScribe scribe = new RawPropertyScribe(name);
    //            return scribe.parseText(value, dataType, version, parameters).getProperty();
    //        }
    //
    //        private void handledEmbeddedVCard(String name, String value, int lineNumber, EmbeddedVCardException exception) {
    //            /*
    //             * If the property does not have a value, a nested vCard is expected
    //             * to be next (2.1 style).
    //             */
    //            if (value.trim().length() == 0) {
    //                embeddedVCardException = exception;
    //                return;
    //            }
    //
    //            /*
    //             * If the property does have a value, the property value should be
    //             * an embedded vCard (3.0 style).
    //             */
    //            value = VObjectPropertyValues.unescape(value);
    //
    //            VCardReader agentReader = new VCardReader(value);
    //            agentReader.setCaretDecodingEnabled(isCaretDecodingEnabled());
    //            agentReader.setDefaultQuotedPrintableCharset(getDefaultQuotedPrintableCharset());
    //            agentReader.setScribeIndex(index);
    //
    //            try {
    //                VCard nestedVCard = agentReader.readNext();
    //                if (nestedVCard != null) {
    //                    exception.injectVCard(nestedVCard);
    //                }
    //            } catch (IOException e) {
    //                //shouldn't be thrown because we're reading from a string
    //            } finally {
    //                for (String warning : agentReader.getWarnings()) {
    //                    warnings.add(lineNumber, name, 26, warning);
    //                }
    //                IOUtils.closeQuietly(agentReader);
    //            }
    //        }
    //
    //        /**
    //         * <p>
    //         * Unescapes newline sequences in the LABEL parameter of {@link Address}
    //         * properties. Newlines cannot normally be escaped in parameter values.
    //         * </p>
    //         * <p>
    //         * Only version 4.0 allows this (and only version 4.0 defines a LABEL
    //         * parameter), but do this for all versions for compatibility.
    //         * </p>
    //         * @param property the property
    //         */
    //        private void handleLabelParameter(VCardProperty property) {
    //            if (!(property instanceof Address)) {
    //                return;
    //            }
    //
    //            Address adr = (Address) property;
    //            String label = adr.getLabel();
    //            if (label == null) {
    //                return;
    //            }
    //
    //            label = label.replace("\\n", StringUtils.NEWLINE);
    //            adr.setLabel(label);
    //        }
    //
    void VObjectDataListenerImpl::onVersion(const std::string& value, const Context::Ptr &context) {
        auto version = VCardVersion::valueOfByStr(value);
        _stack->peek()->_vcard->setVersion(version);
    }
    
    void VObjectDataListenerImpl::onWarning( Warning::TYPE warning, const VObjectProperty::Ptr& property, std::exception* thrown, const Context::Ptr &context) {
        //        if (!inVCardComponent(context.getParentComponents())) {
        //            //ignore warnings that are not directly inside a VCARD component
        //            return;
        //        }
        //
        //        String name = (property == null) ? null : property.getName();
        //        warnings.add(context.getLineNumber(), name, 27, warning.getMessage(), context.getUnfoldedLine());
    }
    //
    //        private boolean inVCardComponent(List<String> parentComponents) {
    //            if (parentComponents.isEmpty()) {
    //                return false;
    //            }
    //            String last = parentComponents.get(parentComponents.size() - 1);
    //            return isVCardComponent(last);
    //        }
    //
    //        private boolean isVCardComponent(String componentName) {
    //            return "VCARD".equals(componentName);
    //        }
    //
    /**
     * Assigns names to all nameless parameters. v3.0 and v4.0 require all
     * parameters to have names, but v2.1 does not.
     * @param parameters the parameters
     */
    void VObjectDataListenerImpl::processNamelessParameters(VCardParameters::Ptr parameters) {
        //TODO::fix later
        //    std::list<std::string> namelessValues = parameters.removeAll(null);
        //    for (auto value : namelessValues) {
        //        auto name = guessParameterName(value);
        //        //parameters.put(name, value);
        //    }
    }
    /**
     * <p>
     * Accounts for multi-valued TYPE parameters being enclosed entirely in
     * double quotes (for example: ADR;TYPE="home,work").
     * </p>
     * <p>
     * Many examples throughout the 4.0 specs show TYPE parameters being
     * encoded in this way. This conflicts with the ABNF and is noted in the
     * errata. This method will parse these incorrectly-formatted TYPE
     * parameters as if they were multi-valued, even though, technically,
     * they are not.
     * </p>
     * @param parameters the parameters
     * @param version the version
     */
    void VObjectDataListenerImpl::processQuotedMultivaluedTypeParams(VCardParameters::Ptr parameters, VCardVersion::Ptr version) {
        if (VCardVersion::V2_1()->equals(version)) {
            return;
        }
        
        
        //TODO::later
        
        //    List<String> types = parameters.getTypes();
        //    if (types.isEmpty()) {
        //        return;
        //    }
        //
        //    String valueWithComma = null;
        //    for (String value : types) {
        //        if (value.indexOf(',') >= 0) {
        //            valueWithComma = value;
        //            break;
        //        }
        //    }
        //    if (valueWithComma == null) {
        //        return;
        //    }
        //
        //    types.clear();
        //    int prev = -1, cur;
        //    while ((cur = valueWithComma.indexOf(',', prev + 1)) >= 0) {
        //        types.add(valueWithComma.substring(prev + 1, cur));
        //        prev = cur;
        //    }
        //    types.add(valueWithComma.substring(prev + 1));
    }
    
    
    /**
     * Makes a guess as to what a parameter value's name should be.
     * @param value the parameter value (e.g. "HOME")
     * @return the guessed name (e.g. "TYPE")
     */
    std::string VObjectDataListenerImpl::guessParameterName(std::string value) {
        //    if (VCardDataType.find(value) != null) {
        //        return VCardParameters.VALUE;
        //    }
        //    
        //    if (Encoding.find(value) != null) {
        //        return VCardParameters.ENCODING;
        //    }
        //    
        //    //otherwise, assume it's a TYPE
        //    return VCardParameters.TYPE;
        //    
        return "";
    }
    
}
