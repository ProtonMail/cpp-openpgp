//
//  vobject_data_listener_impl.hpp
//  OpenPGP
//
//  Created by Yanfeng Zhang on 1/11/17.
//  Copyright © 2017 Yanfeng Zhang. All rights reserved.
//

#ifndef vobject_data_listener_impl_hpp
#define vobject_data_listener_impl_hpp

#include <stdio.h>
#include <list>

#include "vobject_reader.hpp"
#include "vcard.hpp"
#include "vcard_stack.hpp"
#include "vcard_property.hpp"
#include "scribe_index.hpp"


namespace vinnie {
    using namespace ezvcard;
    
    class VObjectDataListenerImpl : public VObjectDataListener {
    public:
        typedef std::shared_ptr<VObjectDataListenerImpl> Ptr;
        
        VCard::Ptr root;
        VCardVersion::Ptr _defaultVersion;
        ScribeIndex::Ptr _index;
        
        VObjectDataListenerImpl();
        VObjectDataListenerImpl(const VCardVersion::Ptr v, ScribeIndex::Ptr index);
        VCardStack::Ptr _stack = std::make_shared<VCardStack>();
        
        //private EmbeddedVCardException embeddedVCardException;
        void onComponentBegin(const std::string& name, const Context::Ptr &context);
        void onComponentEnd(const std::string& name, const Context::Ptr &context);
        void onProperty(const VObjectProperty::Ptr& property, const Context::Ptr &context);
        void onVersion(const std::string& value, const Context::Ptr &context);
        void onWarning(Warning::TYPE warning, const VObjectProperty::Ptr& property, std::exception* thrown, const Context::Ptr &context);
        
    private:
        bool isVCardComponent(const std::string& componentName);
        bool inVCardComponent(const std::list<std::string>& parentComponents);
        VCardProperty::Ptr parseProperty(const VObjectProperty::Ptr& vobjectProperty, VCardVersion::Ptr version, int lineNumber);
        void processNamelessParameters(VCardParameters::Ptr parameters);
        void processQuotedMultivaluedTypeParams(VCardParameters::Ptr parameters, VCardVersion::Ptr version);
        std::string guessParameterName(const std::string value);
    public:
        //        private VCardProperty parseProperty(VObjectProperty vobjectProperty, VCardVersion version, int lineNumber) {
        //            String group = vobjectProperty.getGroup();
        //            String name = vobjectProperty.getName();
        //            VCardParameters parameters = new VCardParameters(vobjectProperty.getParameters().getMap());
        //            String value = vobjectProperty.getValue();
        //
        //            //sanitize the parameters
        //            processNamelessParameters(parameters);
        //            processQuotedMultivaluedTypeParams(parameters, version);
        //
        //            //get the scribe
        //            VCardPropertyScribe<? extends VCardProperty> scribe = index.getPropertyScribe(name);
        //            if (scribe == null) {
        //                scribe = new RawPropertyScribe(name);
        //            }
        //
        //            //get the data type (VALUE parameter)
        //            VCardDataType dataType = parameters.getValue();
        //            parameters.setValue(null);
        //            if (dataType == null) {
        //                //use the default data type if there is no VALUE parameter
        //                dataType = scribe.defaultDataType(version);
        //            }
        //
        //            VCardProperty property;
        //            try {
        //                Result<? extends VCardProperty> result = scribe.parseText(value, dataType, version, parameters);
        //                for (String warning : result.getWarnings()) {
        //                    warnings.add(lineNumber, name, warning);
        //                }
        //                property = result.getProperty();
        //            } catch (SkipMeException e) {
        //                handleSkippedProperty(name, lineNumber, e);
        //                return null;
        //            } catch (CannotParseException e) {
        //                property = handleUnparseableProperty(name, parameters, value, dataType, lineNumber, version, e);
        //            } catch (EmbeddedVCardException e) {
        //                handledEmbeddedVCard(name, value, lineNumber, e);
        //                property = e.getProperty();
        //            }
        //
        //            property.setGroup(group);
        //
        //            /*
        //             * LABEL properties must be treated specially so they can be matched
        //             * up with the ADR properties that they belong to. LABELs are not
        //             * added to the vCard as properties, they are added to the ADR
        //             * properties they belong to (unless they cannot be matched up with
        //             * an ADR).
        //             */
        //            if (property instanceof Label) {
        //                Label label = (Label) property;
        //                stack.peek().labels.add(label);
        //                return null;
        //            }
        //
        //            handleLabelParameter(property);
        //
        //            return property;
        //        }
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
        
        //
        
        //
        //        /**
        //         * Assigns names to all nameless parameters. v3.0 and v4.0 require all
        //         * parameters to have names, but v2.1 does not.
        //         * @param parameters the parameters
        //         */
        //        private void processNamelessParameters(VCardParameters parameters) {
        //            List<String> namelessValues = parameters.removeAll(null);
        //            for (String value : namelessValues) {
        //                String name = guessParameterName(value);
        //                parameters.put(name, value);
        //            }
        //        }
        //
        //        /**
        //         * Makes a guess as to what a parameter value's name should be.
        //         * @param value the parameter value (e.g. "HOME")
        //         * @return the guessed name (e.g. "TYPE")
        //         */
        //        private String guessParameterName(String value) {
        //            if (VCardDataType.find(value) != null) {
        //                return VCardParameters.VALUE;
        //            }
        //
        //            if (Encoding.find(value) != null) {
        //                return VCardParameters.ENCODING;
        //            }
        //
        //            //otherwise, assume it's a TYPE
        //            return VCardParameters.TYPE;
        //        }
        //
        //        /**
        //         * <p>
        //         * Accounts for multi-valued TYPE parameters being enclosed entirely in
        //         * double quotes (for example: ADR;TYPE="home,work").
        //         * </p>
        //         * <p>
        //         * Many examples throughout the 4.0 specs show TYPE parameters being
        //         * encoded in this way. This conflicts with the ABNF and is noted in the
        //         * errata. This method will parse these incorrectly-formatted TYPE
        //         * parameters as if they were multi-valued, even though, technically,
        //         * they are not.
        //         * </p>
        //         * @param parameters the parameters
        //         * @param version the version
        //         */
        //        private void processQuotedMultivaluedTypeParams(VCardParameters parameters, VCardVersion version) {
        //            if (version == VCardVersion.V2_1) {
        //                return;
        //            }
        //
        //            List<String> types = parameters.getTypes();
        //            if (types.isEmpty()) {
        //                return;
        //            }
        //
        //            String valueWithComma = null;
        //            for (String value : types) {
        //                if (value.indexOf(',') >= 0) {
        //                    valueWithComma = value;
        //                    break;
        //                }
        //            }
        //            if (valueWithComma == null) {
        //                return;
        //            }
        //
        //            types.clear();
        //            int prev = -1, cur;
        //            while ((cur = valueWithComma.indexOf(',', prev + 1)) >= 0) {
        //                types.add(valueWithComma.substring(prev + 1, cur));
        //                prev = cur;
        //            }
        //            types.add(valueWithComma.substring(prev + 1));
        //        }
    };
    
}
#endif /* vobject_data_listener_impl_hpp */
