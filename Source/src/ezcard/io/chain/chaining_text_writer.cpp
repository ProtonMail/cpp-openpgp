//
//  chaining_text_writer.cpp
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


#include "chaining_text_writer.hpp"
#include "vcard_writer.hpp"
#include <iostream>
#include <fstream>


namespace ezvcard {
    
    
    
    ChainingTextWriter::ChainingTextWriter(std::vector<VCard::Ptr> vcards) : ChainingWriter(vcards) {
        
    }
    
    
    /**
     * <p>
     * Gets the {@link VCardVersion} object to pass into the {@link VCardWriter}
     * constructor. The constructor does not allow a null version, so this
     * method ensures that a non-null version is passed in.
     * </p>
     * <p>
     * If the user hasn't chosen a version, the version that is passed into the
     * constructor doesn't matter. This is because the writer's target version
     * is reset every time a vCard is written (see the {@link #go(VCardWriter)}
     * method).
     * </p>
     * @return the version to pass into the constructor
     */
    VCardVersion::Ptr ChainingTextWriter::getVCardWriterConstructorVersion() {
        return (_version == nullptr) ? VCardVersion::V3_0() : _version;
    }
    
    
    
    void ChainingTextWriter::go(const VCardWriter::Ptr& writer) {
        writer->setAddProdId(_prodId);
        writer->setCaretEncodingEnabled(_caretEncoding);
        writer->setVersionStrict(_versionStrict);
        writer->setIncludeTrailingSemicolons(_includeTrailingSemicolons);
        writer->setTargetApplication(_targetApplication);
        if (_index != nullptr) {
            writer->setScribeIndex(_index);
        }
        
        for (auto vcard : _vcards) {
            if (_version == nullptr) {
                //use the version that's assigned to each individual vCard
                auto vcardVersion = std::dynamic_pointer_cast<VCardVersion>(vcard->getVersion());
                if (vcardVersion == nullptr) {
                    vcardVersion = VCardVersion::V3_0();
                }
                writer->setTargetVersion(vcardVersion);
            }
            writer->write(vcard);
        }
    }
    
    /**
     * <p>
     * Sets the version that all the vCards will be marshalled to. The version
     * that is attached to each individual {@link VCard} object will be ignored.
     * </p>
     * <p>
     * If no version is passed into this method, the writer will look at the
     * version attached to each individual {@link VCard} object and marshal it
     * to that version. And if a {@link VCard} object has no version attached to
     * it, then it will be marshalled to version 3.0.
     * </p>
     * @param version the version to marshal the vCards to
     * @return this
     */
    void ChainingTextWriter::version(const VCardVersion::Ptr& version) {
        _version = version;
    }
    
    
    /**
     * Sets whether the writer will use circumflex accent encoding for vCard 3.0
     * and 4.0 parameter values (disabled by default).
     * @param enable true to use circumflex accent encoding, false not to
     * @return this
     * @see VCardWriter#setCaretEncodingEnabled(boolean)
     * @see <a href="http://tools.ietf.org/html/rfc6868">RFC 6868</a>
     */
    void ChainingTextWriter::caretEncoding(bool enable) {
        _caretEncoding = enable;
    }
    
    //    /**
    //     * <p>
    //     * Sets whether to include trailing semicolon delimiters for structured
    //     * property values whose list of values end with null or empty values.
    //     * Examples of properties that use structured values are
    //     * {@link StructuredName} and {@link Address}.
    //     * </p>
    //     * <p>
    //     * This setting exists for compatibility reasons and should not make a
    //     * difference to consumers that correctly implement the vCard grammar.
    //     * </p>
    //     * @param include true to include the trailing semicolons, false not to,
    //     * null to use the default behavior (defaults to false for vCard versions
    //     * 2.1 and 3.0 and true for vCard version 4.0)
    //     * @return this
    //     * @see <a href="https://github.com/mangstadt/ez-vcard/issues/57">Issue
    //     * 57</a>
    //     */
    //    public ChainingTextWriter includeTrailingSemicolons(Boolean include) {
    //        this.includeTrailingSemicolons = include;
    //        return this;
    //    }
    //
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
     * @return this
     * @see VCardWriter#setTargetApplication(TargetApplication)
     */
    void ChainingTextWriter::targetApplication(TargetApplication targetApplication) {
        _targetApplication = targetApplication;
    }
    
    //
    //    @Override
    //    public ChainingTextWriter prodId(boolean include) {
    //        return super.prodId(include);
    //    }
    //
    //    @Override
    //    public ChainingTextWriter versionStrict(boolean versionStrict) {
    //        return super.versionStrict(versionStrict);
    //    }
    //
    //    @Override
    //    public ChainingTextWriter register(VCardPropertyScribe<? extends VCardProperty> scribe) {
    //        return super.register(scribe);
    //    }
    //
    
    /**
     * Writes the vCards to a string.
     * @return the vCard string
     */
    std::string ChainingTextWriter::go() {
        auto sw = std::make_shared<std::stringstream>("");
        try {
            go(sw);
        } catch (const std::ios_base::failure& e) {
            //should never be thrown because we're writing to a string
            throw std::runtime_error(e);
        }
        return sw->str();
    }
    //
    //    /**
    //     * Writes the vCards to an output stream.
    //     * @param out the output stream to write to
    //     * @throws IOException if there's a problem writing to the output stream
    //     */
    //    public void go(OutputStream out) throws IOException {
    //        go(new VCardWriter(out, getVCardWriterConstructorVersion()));
    //    }
    //
    //    /**
    //     * Writes the vCards to a file. If the file exists, it will be overwritten.
    //     * @param file the file to write to
    //     * @throws IOException if there's a problem writing to the file
    //     */
    //    public void go(File file) throws IOException {
    //        go(file, false);
    //    }
    //
    //    /**
    //     * Writes the vCards to a file.
    //     * @param file the file to write to
    //     * @param append true to append onto the end of the file, false to overwrite
    //     * it
    //     * @throws IOException if there's a problem writing to the file
    //     */
    //    public void go(File file, boolean append) throws IOException {
    //        VCardWriter writer = new VCardWriter(file, append, getVCardWriterConstructorVersion());
    //        try {
    //            go(writer);
    //        } finally {
    //            writer.close();
    //        }
    //    }
    //
    /**
     * Writes the vCards to a writer.
     * @param writer the writer to write to
     * @throws IOException if there's a problem writing to the writer
     */
    void ChainingTextWriter::go(const std::shared_ptr<std::stringstream>& writer) {
        auto w = std::make_shared<VCardWriter>(writer, getVCardWriterConstructorVersion());
        go(w);
    }
    
    
    
}
