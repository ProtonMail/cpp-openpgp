//
//  vcard_reader.hpp
//  OpenPGP
//
//  Created by Yanfeng Zhang on 12/2/16.
//  Copyright © 2016 Yanfeng Zhang. All rights reserved.
//

#ifndef vcard_reader_hpp
#define vcard_reader_hpp

#include <string>
#include <sstream>
#include <iostream>
#include <ezvcard/io/stream_reader.hpp>
#include <ezvcard/vcard_version.hpp>
#include "vobject_reader.hpp"


namespace ezvcard {
    
    using namespace vinnie;
    
    class VCardReader : public StreamReader {
    private:
        void init(const std::string& str, VCardVersion::Ptr defaultVersion);
        VObjectReader::Ptr _reader;
        VCardVersion::Ptr _defaultVersion;
        
    protected:
        VCard::Ptr _readNext();
        
    public:
        VCardReader(const std::string& str);
        VCardReader(const std::string& str, VCardVersion::Ptr defaultVersion);
        
        bool isCaretDecodingEnabled();
        void setCaretDecodingEnabled(bool enable);
        
        
        
        
        //VCardReader(InputStream in);
        //VCardReader(InputStream in, VCardVersion defaultVersion);
        //VCardReader(File file) throws FileNotFoundException;
        //VCardReader(File file, VCardVersion defaultVersion);
        
        
        //    Charset getDefaultQuotedPrintableCharset();
        //    void setDefaultQuotedPrintableCharset(Charset charset);
        
        //    private class VObjectDataListenerImpl implements VObjectDataListener {
        //        private VCard root;
        //        private final VCardStack stack = new VCardStack();
        //        private EmbeddedVCardException embeddedVCardException;
        //
        //        public void onComponentBegin(String name, Context context) {
        //            if (!isVCardComponent(name)) {
        //                //ignore non-VCARD components
        //                return;
        //            }
        //
        //            VCard vcard = new VCard(defaultVersion);
        //            if (stack.isEmpty()) {
        //                root = vcard;
        //            }
        //            stack.push(vcard);
        //
        //            if (embeddedVCardException != null) {
        //                embeddedVCardException.injectVCard(vcard);
        //                embeddedVCardException = null;
        //            }
        //        }
        //
        //        public void onComponentEnd(String name, Context context) {
        //            if (!isVCardComponent(name)) {
        //                //ignore non-VCARD components
        //                return;
        //            }
        //
        //            VCardStack.Item item = stack.pop();
        //            assignLabels(item.vcard, item.labels);
        //
        //            if (stack.isEmpty()) {
        //                context.stop();
        //            }
        //        }
        //
        //        public void onProperty(VObjectProperty vobjectProperty, Context context) {
        //            if (!inVCardComponent(context.getParentComponents())) {
        //                //ignore properties that are not directly inside a VCARD component
        //                return;
        //            }
        //
        //            if (embeddedVCardException != null) {
        //                //the next property was supposed to be the start of a nested vCard, but it wasn't
        //                embeddedVCardException.injectVCard(null);
        //                embeddedVCardException = null;
        //            }
        //
        //            VCard curVCard = stack.peek().vcard;
        //            VCardVersion version = curVCard.getVersion();
        //
        //            VCardProperty property = parseProperty(vobjectProperty, version, context.getLineNumber());
        //            if (property != null) {
        //                curVCard.addProperty(property);
        //            }
        //        }
        //
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
        //        public void onVersion(String value, Context context) {
        //            VCardVersion version = VCardVersion.valueOfByStr(value);
        //            stack.peek().vcard.setVersion(version);
        //        }
        //
        //        public void onWarning(Warning warning, VObjectProperty property, Exception thrown, Context context) {
        //            if (!inVCardComponent(context.getParentComponents())) {
        //                //ignore warnings that are not directly inside a VCARD component
        //                return;
        //            }
        //
        //            String name = (property == null) ? null : property.getName();
        //            warnings.add(context.getLineNumber(), name, 27, warning.getMessage(), context.getUnfoldedLine());
        //        }
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
        //    }
        //
        //    /**
        //     * Keeps track of the hierarchy of nested vCards.
        //     */
        //    private static class VCardStack {
        //        private final List<Item> stack = new ArrayList<Item>();
        //
        //        /**
        //         * Adds a vCard to the stack.
        //         * @param vcard the vcard to add
        //         */
        //        public void push(VCard vcard) {
        //            stack.add(new Item(vcard, new ArrayList<Label>()));
        //        }
        //
        //        /**
        //         * Removes the top item from the stack and returns it.
        //         * @return the last item or null if the stack is empty
        //         */
        //        public Item pop() {
        //            return isEmpty() ? null : stack.remove(stack.size() - 1);
        //        }
        //        
        //        /**
        //         * Gets the top item of the stack.
        //         * @return the top item
        //         */
        //        public Item peek() {
        //            return isEmpty() ? null : stack.get(stack.size() - 1);
        //        }
        //        
        //        /**
        //         * Determines if the stack is empty.
        //         * @return true if it's empty, false if not
        //         */
        //        public boolean isEmpty() {
        //            return stack.isEmpty();
        //        }
        //        
        //        private static class Item {
        //            public final VCard vcard;
        //            public final List<Label> labels;
        //            
        //            public Item(VCard vcard, List<Label> labels) {
        //                this.vcard = vcard;
        //                this.labels = labels;
        //            }
        //        }
        //    }
        //    
        //    /**
        //     * Closes the input stream.
        //     * @throws IOException if there's a problem closing the input stream
        //     */
        //    public void close() throws IOException {
        //        reader.close();
        //    }
    };
    
}

#endif /* vcard_reader_hpp */
