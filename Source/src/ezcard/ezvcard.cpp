//
//  ezcard.cpp
//  OpenPGP
//
//  Created by Yanfeng Zhang on 12/1/16.
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


#include "ezvcard.hpp"
#include <fstream>

namespace ezvcard {
    
    
    
    std::string Ezvcard::VERSION_NUMBER = "0.0.1";
    std::string Ezvcard::GROUP_ID       = "";
    std::string Ezvcard::ARTIFACT_ID    = "";
    std::string Ezvcard::URL            = "protonmail.com/vcard";
    std::string Ezvcard::PRODID         = "pm-ez-vcard ";
    
    
    /**
     * <p>
     * Parses plain text vCards.
     * </p>
     * <p>
     * Use {@link VCardReader} for more control over the parsing.
     * </p>
     * @param str the vCard string
     * @return chainer object for completing the parse operation
     * @see VCardReader
     * @see <a href="http://www.imc.org/pdi/vcard-21.rtf">vCard 2.1</a>
     * @see <a href="http://tools.ietf.org/html/rfc2426">RFC 2426 (3.0)</a>
     * @see <a href="http://tools.ietf.org/html/rfc6350">RFC 6350 (4.0)</a>
     */
    
    ChainingTextStringParser Ezvcard::parse(std::string str) {
        return ChainingTextStringParser(str);
    }
    
    /**
     * <p>
     * Parses plain text vCards.
     * </p>
     * <p>
     * Use {@link VCardReader} for more control over the parsing.
     * </p>
     * @param file the vCard file
     * @return chainer object for completing the parse operation
     * @see VCardReader
     * @see <a href="http://www.imc.org/pdi/vcard-21.rtf">vCard 2.1</a>
     * @see <a href="http://tools.ietf.org/html/rfc2426">RFC 2426 (3.0)</a>
     * @see <a href="http://tools.ietf.org/html/rfc6350">RFC 6350 (4.0)</a>
     */
    ChainingTextStringParser Ezvcard::parse(std::ifstream& file) {
        
        std::string content( (std::istreambuf_iterator<char>(file) ),
                            (std::istreambuf_iterator<char>()    ) );
        
        
        return ChainingTextStringParser(content);
    }
    
    //    static {
    //        InputStream in = null;
    //        Properties props = new Properties();
    //        try {
    //            in = Ezvcard.class.getResourceAsStream("ez-vcard.properties");
    //            props.load(in);
    //        } catch (IOException e) {
    //            throw new RuntimeException(e);
    //        } finally {
    //            IOUtils.closeQuietly(in);
    //        }
    //
    //        VERSION = props.getProperty("version");
    //        GROUP_ID = props.getProperty("groupId");
    //        ARTIFACT_ID = props.getProperty("artifactId");
    //        URL = props.getProperty("url");
    //    }

    //    /**
    //     * <p>
    //     * Parses plain text vCards.
    //     * </p>
    //     * <p>
    //     * Use {@link VCardReader} for more control over the parsing.
    //     * </p>
    //     * @param in the input stream
    //     * @return chainer object for completing the parse operation
    //     * @see VCardReader
    //     * @see <a href="http://www.imc.org/pdi/vcard-21.rtf">vCard 2.1</a>
    //     * @see <a href="http://tools.ietf.org/html/rfc2426">RFC 2426 (3.0)</a>
    //     * @see <a href="http://tools.ietf.org/html/rfc6350">RFC 6350 (4.0)</a>
    //     */
    //    public static ChainingTextParser<ChainingTextParser<?>> parse(InputStream in) {
    //        return new ChainingTextParser<ChainingTextParser<?>>(in);
    //    }
    //
    //    /**
    //     * <p>
    //     * Parses plain text vCards.
    //     * </p>
    //     * <p>
    //     * Use {@link VCardReader} for more control over the parsing.
    //     * </p>
    //     * @param reader the reader
    //     * @return chainer object for completing the parse operation
    //     * @see VCardReader
    //     * @see <a href="http://www.imc.org/pdi/vcard-21.rtf">vCard 2.1</a>
    //     * @see <a href="http://tools.ietf.org/html/rfc2426">RFC 2426 (3.0)</a>
    //     * @see <a href="http://tools.ietf.org/html/rfc6350">RFC 6350 (4.0)</a>
    //     */
    //    public static ChainingTextParser<ChainingTextParser<?>> parse(Reader reader) {
    //        return new ChainingTextParser<ChainingTextParser<?>>(reader);
    //    }
    //
    //    /**
    //     * <p>
    //     * Parses XML-encoded vCards (xCard) from a string.
    //     * </p>
    //     * <p>
    //     * Use {@link XCardDocument} or {@link XCardReader} for more control over
    //     * the parsing.
    //     * </p>
    //     * @param xml the XML document
    //     * @return chainer object for completing the parse operation
    //     * @see XCardDocument
    //     * @see XCardReader
    //     * @see <a href="http://tools.ietf.org/html/rfc6351">RFC 6351</a>
    //     */
    //    public static ChainingXmlMemoryParser parseXml(String xml) {
    //        return new ChainingXmlMemoryParser(xml);
    //    }
    //
    //    /**
    //     * <p>
    //     * Parses XML-encoded vCards (xCard) from a file.
    //     * </p>
    //     * <p>
    //     * Use {@link XCardDocument} or {@link XCardReader} for more control over
    //     * the parsing.
    //     * </p>
    //     * @param file the XML file
    //     * @return chainer object for completing the parse operation
    //     * @see XCardDocument
    //     * @see XCardReader
    //     * @see <a href="http://tools.ietf.org/html/rfc6351">RFC 6351</a>
    //     */
    //    public static ChainingXmlParser<ChainingXmlParser<?>> parseXml(File file) {
    //        return new ChainingXmlParser<ChainingXmlParser<?>>(file);
    //    }
    //
    //    /**
    //     * <p>
    //     * Parses XML-encoded vCards (xCard) from an input stream.
    //     * </p>
    //     * <p>
    //     * Use {@link XCardDocument} or {@link XCardReader} for more control over
    //     * the parsing.
    //     * </p>
    //     * @param in the input stream to the XML document
    //     * @return chainer object for completing the parse operation
    //     * @see XCardDocument
    //     * @see XCardReader
    //     * @see <a href="http://tools.ietf.org/html/rfc6351">RFC 6351</a>
    //     */
    //    public static ChainingXmlParser<ChainingXmlParser<?>> parseXml(InputStream in) {
    //        return new ChainingXmlParser<ChainingXmlParser<?>>(in);
    //    }
    //
    //    /**
    //     * <p>
    //     * Parses XML-encoded vCards (xCard) from a reader.
    //     * </p>
    //     * <p>
    //     * Note that use of this method is discouraged. It ignores the character
    //     * encoding that is defined within the XML document itself, and should only
    //     * be used if the encoding is undefined or if the encoding needs to be
    //     * ignored for some reason. The {@link #parseXml(InputStream)} method should
    //     * be used instead, since it takes the XML document's character encoding
    //     * into account when parsing.
    //     * </p>
    //     * <p>
    //     * Use {@link XCardDocument} or {@link XCardReader} for more control over
    //     * the parsing.
    //     * </p>
    //     * @param reader the reader to the XML document
    //     * @return chainer object for completing the parse operation
    //     * @see XCardDocument
    //     * @see XCardReader
    //     * @see <a href="http://tools.ietf.org/html/rfc6351">RFC 6351</a>
    //     */
    //    public static ChainingXmlParser<ChainingXmlParser<?>> parseXml(Reader reader) {
    //        return new ChainingXmlParser<ChainingXmlParser<?>>(reader);
    //    }
    //
    //    /**
    //     * <p>
    //     * Parses XML-encoded vCards (xCard).
    //     * </p>
    //     * <p>
    //     * Use {@link XCardDocument} or {@link XCardReader} for more control over
    //     * the parsing.
    //     * </p>
    //     * @param document the XML document
    //     * @return chainer object for completing the parse operation
    //     * @see XCardDocument
    //     * @see XCardReader
    //     * @see <a href="http://tools.ietf.org/html/rfc6351">RFC 6351</a>
    //     */
    //    public static ChainingXmlMemoryParser parseXml(Document document) {
    //        return new ChainingXmlMemoryParser(document);
    //    }
    //
    //    /**
    //     * <p>
    //     * Parses HTML-encoded vCards (hCard).
    //     * </p>
    //     * <p>
    //     * Use {@link HCardParser} for more control over the parsing.
    //     * </p>
    //     * @param html the HTML page
    //     * @return chainer object for completing the parse operation
    //     * @see HCardParser
    //     * @see <a href="http://microformats.org/wiki/hcard">hCard 1.0</a>
    //     */
    //    public static ChainingHtmlStringParser parseHtml(String html) {
    //        return new ChainingHtmlStringParser(html);
    //    }
    //
    //    /**
    //     * <p>
    //     * Parses HTML-encoded vCards (hCard).
    //     * </p>
    //     * <p>
    //     * Use {@link HCardParser} for more control over the parsing.
    //     * </p>
    //     * @param file the HTML file
    //     * @return chainer object for completing the parse operation
    //     * @see HCardParser
    //     * @see <a href="http://microformats.org/wiki/hcard">hCard 1.0</a>
    //     */
    //    public static ChainingHtmlParser<ChainingHtmlParser<?>> parseHtml(File file) {
    //        return new ChainingHtmlParser<ChainingHtmlParser<?>>(file);
    //    }
    //
    //    /**
    //     * <p>
    //     * Parses HTML-encoded vCards (hCard).
    //     * </p>
    //     * <p>
    //     * Use {@link HCardParser} for more control over the parsing.
    //     * </p>
    //     * @param in the input stream to the HTML page
    //     * @return chainer object for completing the parse operation
    //     * @see HCardParser
    //     * @see <a href="http://microformats.org/wiki/hcard">hCard 1.0</a>
    //     */
    //    public static ChainingHtmlParser<ChainingHtmlParser<?>> parseHtml(InputStream in) {
    //        return new ChainingHtmlParser<ChainingHtmlParser<?>>(in);
    //    }
    //
    //    /**
    //     * <p>
    //     * Parses HTML-encoded vCards (hCard).
    //     * </p>
    //     * <p>
    //     * Use {@link HCardParser} for more control over the parsing.
    //     * </p>
    //     * @param reader the reader to the HTML page
    //     * @return chainer object for completing the parse operation
    //     * @see HCardParser
    //     * @see <a href="http://microformats.org/wiki/hcard">hCard 1.0</a>
    //     */
    //    public static ChainingHtmlParser<ChainingHtmlParser<?>> parseHtml(Reader reader) {
    //        return new ChainingHtmlParser<ChainingHtmlParser<?>>(reader);
    //    }
    //
    //    /**
    //     * <p>
    //     * Parses HTML-encoded vCards (hCard).
    //     * </p>
    //     * <p>
    //     * Use {@link HCardParser} for more control over the parsing.
    //     * </p>
    //     * @param url the URL of the webpage
    //     * @return chainer object for completing the parse operation
    //     * @see HCardParser
    //     * @see <a href="http://microformats.org/wiki/hcard">hCard 1.0</a>
    //     */
    //    public static ChainingHtmlParser<ChainingHtmlParser<?>> parseHtml(URL url) {
    //        return new ChainingHtmlParser<ChainingHtmlParser<?>>(url);
    //    }
    //
    //    /**
    //     * <p>
    //     * Parses JSON-encoded vCards (jCard).
    //     * </p>
    //     * <p>
    //     * Use {@link JCardReader} for more control over the parsing.
    //     * </p>
    //     * @param json the JSON string
    //     * @return chainer object for completing the parse operation
    //     * @see JCardReader
    //     * @see <a href="http://tools.ietf.org/html/rfc7095">RFC 7095</a>
    //     */
    //    public static ChainingJsonStringParser parseJson(String json) {
    //        return new ChainingJsonStringParser(json);
    //    }
    //
    //    /**
    //     * <p>
    //     * Parses JSON-encoded vCards (jCard).
    //     * </p>
    //     * <p>
    //     * Use {@link JCardReader} for more control over the parsing.
    //     * </p>
    //     * @param file the JSON file
    //     * @return chainer object for completing the parse operation
    //     * @see JCardReader
    //     * @see <a href="http://tools.ietf.org/html/rfc7095">RFC 7095</a>
    //     */
    //    public static ChainingJsonParser<ChainingJsonParser<?>> parseJson(File file) {
    //        return new ChainingJsonParser<ChainingJsonParser<?>>(file);
    //    }
    //
    //    /**
    //     * <p>
    //     * Parses JSON-encoded vCards (jCard).
    //     * </p>
    //     * <p>
    //     * Use {@link JCardReader} for more control over the parsing.
    //     * </p>
    //     * @param in the input stream
    //     * @return chainer object for completing the parse operation
    //     * @see JCardReader
    //     * @see <a href="http://tools.ietf.org/html/rfc7095">RFC 7095</a>
    //     */
    //    public static ChainingJsonParser<ChainingJsonParser<?>> parseJson(InputStream in) {
    //        return new ChainingJsonParser<ChainingJsonParser<?>>(in);
    //    }
    //
    //    /**
    //     * <p>
    //     * Parses JSON-encoded vCards (jCard).
    //     * </p>
    //     * <p>
    //     * Use {@link JCardReader} for more control over the parsing.
    //     * </p>
    //     * @param reader the reader
    //     * @return chainer object for completing the parse operation
    //     * @see JCardReader
    //     * @see <a href="http://tools.ietf.org/html/rfc7095">RFC 7095</a>
    //     */
    //    public static ChainingJsonParser<ChainingJsonParser<?>> parseJson(Reader reader) {
    //        return new ChainingJsonParser<ChainingJsonParser<?>>(reader);
    //    }
    
    /**
     * <p>
     * Marshals one or more vCards to their traditional, plain-text
     * representation.
     * </p>
     * <p>
     * Use {@link VCardWriter} for more control over how the vCards are written.
     * </p>
     * @param vcards the vCards to marshal
     * @return chainer object for completing the write operation
     * @see VCardWriter
     * @see <a href="http://www.imc.org/pdi/vcard-21.rtf">vCard 2.1</a>
     * @see <a href="http://tools.ietf.org/html/rfc2426">RFC 2426 (3.0)</a>
     * @see <a href="http://tools.ietf.org/html/rfc6350">RFC 6350 (4.0)</a>
     */
    ChainingTextWriter::Ptr Ezvcard::write(const VCard::Ptr& vcard) {
        return write(std::vector<VCard::Ptr>{ vcard } );
    }
    
    /**
     * <p>
     * Marshals one or more vCards to their traditional, plain-text
     * representation.
     * </p>
     * <p>
     * Use {@link VCardWriter} for more control over how the vCards are written.
     * </p>
     * @param vcards the vCards to marshal
     * @return chainer object for completing the write operation
     * @see VCardWriter
     * @see <a href="http://www.imc.org/pdi/vcard-21.rtf">vCard 2.1</a>
     * @see <a href="http://tools.ietf.org/html/rfc2426">RFC 2426 (3.0)</a>
     * @see <a href="http://tools.ietf.org/html/rfc6350">RFC 6350 (4.0)</a>
     */
    ChainingTextWriter::Ptr Ezvcard::write(std::vector<VCard::Ptr> vcards) {
        return std::make_shared<ChainingTextWriter>(vcards);
    }
    //
    //    /**
    //     * <p>
    //     * Marshals one or more vCards to their XML representation (xCard).
    //     * </p>
    //     * <p>
    //     * Use {@link XCardDocument} or {@link XCardWriter} for more control over
    //     * how the vCards are written.
    //     * </p>
    //     * @param vcards the vCards to marshal
    //     * @return chainer object for completing the write operation
    //     * @see XCardDocument
    //     * @see XCardWriter
    //     * @see <a href="http://tools.ietf.org/html/rfc6351">RFC 6351</a>
    //     */
    //    public static ChainingXmlWriter writeXml(VCard... vcards) {
    //        return writeXml(Arrays.asList(vcards));
    //    }
    //
    //    /**
    //     * <p>
    //     * Marshals one or more vCards to their XML representation (xCard).
    //     * </p>
    //     * <p>
    //     * Use {@link XCardDocument} or {@link XCardWriter} for more control over
    //     * how the vCards are written.
    //     * </p>
    //     * @param vcards the vCard to marshal
    //     * @return chainer object for completing the write operation
    //     * @see XCardDocument
    //     * @see XCardWriter
    //     * @see <a href="http://tools.ietf.org/html/rfc6351">RFC 6351</a>
    //     */
    //    public static ChainingXmlWriter writeXml(Collection<VCard> vcards) {
    //        return new ChainingXmlWriter(vcards);
    //    }
    //
    //    /**
    //     * <p>
    //     * Marshals one or more vCards their HTML representation (hCard).
    //     * </p>
    //     * <p>
    //     * Use {@link HCardPage} for more control over how the vCards are written.
    //     * </p>
    //     * @param vcards the vCard(s) to marshal
    //     * @return chainer object for completing the write operation
    //     * @see HCardPage
    //     * @see <a href="http://microformats.org/wiki/hcard">hCard 1.0</a>
    //     */
    //    public static ChainingHtmlWriter writeHtml(VCard... vcards) {
    //        return writeHtml(Arrays.asList(vcards));
    //    }
    //
    //    /**
    //     * <p>
    //     * Marshals one or more vCards their HTML representation (hCard).
    //     * </p>
    //     * <p>
    //     * Use {@link HCardPage} for more control over how the vCards are written.
    //     * </p>
    //     * @param vcards the vCard(s) to marshal
    //     * @return chainer object for completing the write operation
    //     * @see HCardPage
    //     * @see <a href="http://microformats.org/wiki/hcard">hCard 1.0</a>
    //     */
    //    public static ChainingHtmlWriter writeHtml(Collection<VCard> vcards) {
    //        return new ChainingHtmlWriter(vcards);
    //    }
    //
    //    /**
    //     * <p>
    //     * Marshals one or more vCards to their JSON representation (jCard).
    //     * </p>
    //     * <p>
    //     * Use {@link JCardWriter} for more control over how the vCards are written.
    //     * </p>
    //     * @param vcards the vCards to marshal
    //     * @return chainer object for completing the write operation
    //     * @see JCardWriter
    //     * @see <a href="http://tools.ietf.org/html/rfc7095">RFC 7095</a>
    //     */
    //    public static ChainingJsonWriter writeJson(VCard... vcards) {
    //        return writeJson(Arrays.asList(vcards));
    //    }
    //
    //    /**
    //     * <p>
    //     * Marshals one or more vCards to their JSON representation (jCard).
    //     * </p>
    //     * <p>
    //     * Use {@link JCardWriter} for more control over how the vCards are written.
    //     * </p>
    //     * @param vcards the vCards to marshal
    //     * @return chainer object for completing the write operation
    //     * @see JCardWriter
    //     * @see <a href="http://tools.ietf.org/html/rfc7095">RFC 7095</a>
    //     */
    //    public static ChainingJsonWriter writeJson(Collection<VCard> vcards) {
    //        return new ChainingJsonWriter(vcards);
    //    }
    //
    //    private Ezvcard() {
    //        //hide
    //    }
    
}
