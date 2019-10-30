//
//  vcard_writer.cpp
//  OpenPGP
//
//  Created by Yanfeng Zhang on 5/8/17.
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

#include "vcard_writer.hpp"
#include "write_context.hpp"
#include "binary_property.hpp"
#include "address_property.hpp"

namespace ezvcard {
    /**
     * @param writer the writer to write to
     * @param targetVersion the version that the vCards should conform to
     */
    VCardWriter::VCardWriter(const std::shared_ptr<std::stringstream>& writer, const VCardVersion::Ptr& targetVersion) {
        _writer = std::make_shared<VObjectWriter>(writer, targetVersion->getSyntaxStyle());
        _targetVersion = targetVersion;
    }
    
    void VCardWriter::_write(VCard::Ptr vcard, std::vector<VCardProperty::Ptr> propertiesToAdd) {
        auto targetVersion = getTargetVersion();
        TargetApplication targetApplication = getTargetApplication();
        
        bool includeTrailingSemicolons = _includeTrailingSemicolons;
        if (_isIncludeTrailingSemicolonsSet == false) {
            includeTrailingSemicolons = (targetVersion == VCardVersion::V4_0());
        }
        
        WriteContext::Ptr context = std::make_shared<WriteContext>(targetVersion, targetApplication, includeTrailingSemicolons);
        
        _writer->writeBeginComponent("VCARD");
        _writer->writeVersion(targetVersion->getVersion());
        
        for (auto property : propertiesToAdd) {
            auto scribe = _index->getPropertyScribe(property);

            std::string value = "";
            VCard::Ptr nestedVCard = nullptr;
            try {
                value = scribe->writeText(property, context);
            } catch (const std::exception& e) {
                continue;
            }
            //catch (EmbeddedVCardException e) {
            //    nestedVCard = e.getVCard();
            //}

            auto parameters = scribe->prepareParameters(property, targetVersion, vcard);
            
            if (nestedVCard != nullptr) {
                writeNestedVCard(nestedVCard, property, scribe, parameters, value);
                continue;
            }
            
            handleValueParameter(property, scribe, parameters);
            handleLabelParameter(property, parameters);
            
            _writer->writeProperty(property->getGroup(),
                                   scribe->getPropertyName(),
                                   std::make_shared<VObjectParameters>(parameters->getMap()),
                                   value);
            
            fixBinaryPropertyForOutlook(property);
        }
        
        _writer->writeEndComponent("VCARD");
    }
    
    //
    //    /**
    //     * @param out the output stream to write to
    //     * @param targetVersion the version that the vCards should conform to (if
    //     * set to "4.0", vCards will be written in UTF-8 encoding)
    //     */
    //    public VCardWriter(OutputStream out, VCardVersion targetVersion) {
    //        this((targetVersion == VCardVersion.V4_0) ? new Utf8Writer(out) : new OutputStreamWriter(out), targetVersion);
    //    }
    //
    //    /**
    //     * @param file the file to write to
    //     * @param targetVersion the version that the vCards should conform to (if
    //     * set to "4.0", vCards will be written in UTF-8 encoding)
    //     * @throws IOException if there's a problem opening the file
    //     */
    //    public VCardWriter(File file, VCardVersion targetVersion) throws IOException {
    //        this(file, false, targetVersion);
    //    }
    //
    //    /**
    //     * @param file the file to write to
    //     * @param append true to append to the end of the file, false to overwrite
    //     * it
    //     * @param targetVersion the version that the vCards should conform to (if
    //     * set to "4.0", vCards will be written in UTF-8 encoding)
    //     * @throws IOException if there's a problem opening the file
    //     */
    //    public VCardWriter(File file, boolean append, VCardVersion targetVersion) throws IOException {
    //        this((targetVersion == VCardVersion.V4_0) ? new Utf8Writer(file, append) : new FileWriter(file, append), targetVersion);
    //    }
    //
    
    
    /**
     * Gets the version that the vCards should adhere to.
     * @return the vCard version
     */
    VCardVersion::Ptr VCardWriter::getTargetVersion() {
        return _targetVersion;
    }
    
    /**
     * Sets the version that the vCards should adhere to.
     * @param targetVersion the vCard version
     */
    void VCardWriter::setTargetVersion(VCardVersion::Ptr targetVersion) {
        _writer->setSyntaxStyle(targetVersion->getSyntaxStyle());
        _targetVersion = targetVersion;
    }
    
    /**
     * <p>
     * Gets the application that the vCards will be targeted for.
     * </p>
     * <p>
     * Some vCard consumers do not completely adhere to the vCard specifications
     * and require their vCards to be formatted in a specific way. See the
     * {@link TargetApplication} class for a list of these applications.
     * </p>
     * @return the target application or null if the vCards do not be given any
     * special processing (defaults to null)
     */
    TargetApplication VCardWriter::getTargetApplication() {
        return _targetApplication;
    }
    
    /**
     * <p>
     * Sets the application that the vCards will be targeted for.
     * </p>
     * <p>
     * Some vCard consumers do not completely adhere to the vCard specifications
     * and require their vCards to be formatted in a specific way. See the
     * {@link TargetApplication} class for a list of these applications.
     * </p>
     * @param targetApplication the target application or null if the vCards do
     * not require any special processing (defaults to null)
     */
    void VCardWriter::setTargetApplication(TargetApplication targetApplication) {
        _targetApplication = targetApplication;
    }
    
    
    /**
     * <p>
     * Gets whether this writer will include trailing semicolon delimiters for
     * structured property values whose list of values end with null or empty
     * values. Examples of properties that use structured values are
     * {@link StructuredName} and {@link Address}.
     * </p>
     * <p>
     * This setting exists for compatibility reasons and should not make a
     * difference to consumers that correctly implement the vCard grammar.
     * </p>
     * @return true to include the trailing semicolons, false not to, null to
     * use the default behavior (defaults to false for vCard versions 2.1 and
     * 3.0 and true for vCard version 4.0)
     * @see <a href="https://github.com/mangstadt/ez-vcard/issues/57">Issue
     * 57</a>
     */
    bool VCardWriter::isIncludeTrailingSemicolons() {
        return _includeTrailingSemicolons;
    }
    
    /**
     * <p>
     * Sets whether to include trailing semicolon delimiters for structured
     * property values whose list of values end with null or empty values.
     * Examples of properties that use structured values are
     * {@link StructuredName} and {@link Address}.
     * </p>
     * <p>
     * This setting exists for compatibility reasons and should not make a
     * difference to consumers that correctly implement the vCard grammar.
     * </p>
     * @param include true to include the trailing semicolons, false not to,
     * null to use the default behavior (defaults to false for vCard versions
     * 2.1 and 3.0 and true for vCard version 4.0)
     * @see <a href="https://github.com/mangstadt/ez-vcard/issues/57">Issue
     * 57</a>
     */
    void VCardWriter::setIncludeTrailingSemicolons(bool include) {
        _includeTrailingSemicolons = include;
        _isIncludeTrailingSemicolonsSet = true;
    }
    
    
    /**
     * <p>
     * Gets whether the writer will apply circumflex accent encoding on
     * parameter values (disabled by default). This escaping mechanism allows
     * for newlines and double quotes to be included in parameter values. It is
     * only supported by vCard versions 3.0 and 4.0.
     * </p>
     *
     * <p>
     * Note that this encoding mechanism is defined separately from the vCard
     * specification and may not be supported by the consumer of the vCard.
     * </p>
     * @return true if circumflex accent encoding is enabled, false if not
     * @see VObjectWriter#isCaretEncodingEnabled()
     */
    bool VCardWriter::isCaretEncodingEnabled() {
        return _writer->isCaretEncodingEnabled();
    }
    
    /**
     * <p>
     * Sets whether the writer will apply circumflex accent encoding on
     * parameter values (disabled by default). This escaping mechanism allows
     * for newlines and double quotes to be included in parameter values. It is
     * only supported by vCard versions 3.0 and 4.0.
     * </p>
     *
     * <p>
     * Note that this encoding mechanism is defined separately from the vCard
     * specification and may not be supported by the consumer of the vCard.
     * </p>
     * @param enable true to use circumflex accent encoding, false not to
     * @see VObjectWriter#setCaretEncodingEnabled(boolean)
     */
    void VCardWriter::setCaretEncodingEnabled(bool enable) {
        _writer->setCaretEncodingEnabled(enable);
    }
    
    
    
    void VCardWriter::writeNestedVCard(VCard::Ptr nestedVCard, VCardProperty::Ptr property, VCardPropertyScribe::Ptr scribe, VCardParameters::Ptr parameters, std::string value)  {
        //        if (targetVersion == VCardVersion.V2_1) {
        //            //write a nested vCard (2.1 style)
        //            writer.writeProperty(property.getGroup(), scribe.getPropertyName(), new VObjectParameters(parameters.getMap()), value);
        //            prodIdStack.add(addProdId);
        //            addProdId = false;
        //            write(nestedVCard);
        //            addProdId = prodIdStack.remove(prodIdStack.size() - 1);
        //        } else {
        //            //write an embedded vCard (3.0 style)
        //            StringWriter sw = new StringWriter();
        //            VCardWriter agentWriter = new VCardWriter(sw, targetVersion);
        //            agentWriter.getVObjectWriter().getFoldedLineWriter().setLineLength(null);
        //            agentWriter.setAddProdId(false);
        //            agentWriter.setCaretEncodingEnabled(isCaretEncodingEnabled());
        //            agentWriter.setIncludeTrailingSemicolons(this.includeTrailingSemicolons);
        //            agentWriter.setScribeIndex(index);
        //            agentWriter.setTargetApplication(targetApplication);
        //            agentWriter.setVersionStrict(versionStrict);
        //            try {
        //                agentWriter.write(nestedVCard);
        //            } catch (IOException e) {
        //                //should never be thrown because we're writing to a string
        //            } finally {
        //                IOUtils.closeQuietly(agentWriter);
        //            }
        //
        //            String vcardStr = sw.toString();
        //            vcardStr = VObjectPropertyValues.escape(vcardStr);
        //            writer.writeProperty(property.getGroup(), scribe.getPropertyName(), new VObjectParameters(parameters.getMap()), vcardStr);
        //        }
    }
    
    /**
     * <p>
     * Sets the property's VALUE parameter. This method only adds a VALUE
     * parameter if all the following conditions are met:
     * </p>
     * <ol>
     * <li>The data type is NOT "unknown"</li>
     * <li>The data type is different from the property's default data type</li>
     * <li>The data type does not fall under the "date/time special case" (see
     * {@link #isDateTimeValueParameterSpecialCase()})</li>
     * </ol>
     * @param property the property
     * @param scribe the property scribe
     * @param parameters the property parameters
     */
    void VCardWriter::handleValueParameter(VCardProperty::Ptr property, VCardPropertyScribe::Ptr scribe, VCardParameters::Ptr parameters) {
        auto dataType = scribe->dataType(property, _targetVersion);
        if (dataType == nullptr) {
            return;
        }
        
        auto defaultDataType = scribe->defaultDataType(_targetVersion);
        if (dataType == defaultDataType) {
            return;
        }
        
        if (isDateTimeValueParameterSpecialCase(defaultDataType, dataType)) {
            return;
        }
        
        parameters->setValue(dataType);
    }
    
    /**
     * <p>                                        * Escapes newline sequences in the LABEL parameter of {@link Address}
     * properties. Newlines cannot normally be escaped in parameter values.
     * </p>
     * <p>
     * Only version 4.0 allows this (and only version 4.0 defines a LABEL
     * parameter), but this method does this for all versions for compatibility.
     * </p>
     * @param property the property
     * @param parameters the property parameters
     */
    void VCardWriter::handleLabelParameter(VCardProperty::Ptr property, VCardParameters::Ptr parameters) {
        if (Address::Ptr binaryProperty = std::dynamic_pointer_cast<Address>(property)) {
            auto label = parameters->getLabel();
            if (label.empty()) {
                return;
            }
            label = escapeNewlines(label);
            parameters->setLabel(label);
        }
    }
    
    
    
    /**
     * @see TargetApplication#OUTLOOK
     */
    void VCardWriter::fixBinaryPropertyForOutlook(VCardProperty::Ptr property) {
        if (_targetApplication != TargetApplication::OUTLOOK) {
            return;
        }
        
        if (getTargetVersion() == VCardVersion::V4_0()) {
            //only do this for 2.1 and 3.0 vCards
            return;
        }
        
        //only when it is a binary property
        if (property->isBinaryProperty()) {
            if (property->isDataNull()) {
                return;
            }
            _writer->getFoldedLineWriter()->writeln();
        }
    }
    
    
    /**
     * Determines if the given default data type is "date-and-or-time" and the
     * given data type is time-based. Properties that meet this criteria should
     * NOT be given a VALUE parameter.
     * @param defaultDataType the property's default data type
     * @param dataType the current property instance's data type
     * @return true if the default data type is "date-and-or-time" and the data
     * type is time-based, false otherwise
     */
    bool VCardWriter::isDateTimeValueParameterSpecialCase(VCardDataType::Ptr defaultDataType, VCardDataType::Ptr dataType) {
        return
        defaultDataType == VCardDataType::DATE_AND_OR_TIME &&
        (
            dataType == VCardDataType::DATE ||
            dataType == VCardDataType::DATE_TIME ||
            dataType == VCardDataType::TIME
        );
    }

}
