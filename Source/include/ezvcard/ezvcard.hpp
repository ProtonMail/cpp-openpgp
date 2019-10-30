//
//  ezcard.hpp
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


#ifndef ezvcard_hpp
#define ezvcard_hpp

#include <string>
#include <fstream>
#include "chaining_text_string_parser.hpp"
#include "chaining_text_writer.hpp"

namespace ezvcard {
    
    class Ezvcard {
        
    public:
        /**
         * The version of the library.
         */
        static std::string VERSION_NUMBER;
        
        /**
         * The Maven group ID.
         */
        static std::string GROUP_ID;
        
        /**
         * The Maven artifact ID.
         */
        static std::string ARTIFACT_ID;
        
        /**
         * The project webpage.
         */
        static std::string URL;
        
        static std::string PRODID;
        
        
        static ChainingTextStringParser parse(std::string str);
        static ChainingTextStringParser parse(std::ifstream& file);
        
        
        //    public static ChainingTextParser<ChainingTextParser<?>> parse(InputStream in);
        //    public static ChainingTextParser<ChainingTextParser<?>> parse(Reader reader);
        
        //    public static ChainingXmlMemoryParser parseXml(String xml);
        //    public static ChainingXmlParser<ChainingXmlParser<?>> parseXml(File file);
        //    public static ChainingXmlParser<ChainingXmlParser<?>> parseXml(InputStream in);
        //    public static ChainingXmlParser<ChainingXmlParser<?>> parseXml(Reader reader);
        //    public static ChainingXmlMemoryParser parseXml(Document document);
        //    public static ChainingHtmlStringParser parseHtml(String html);
        //    public static ChainingHtmlParser<ChainingHtmlParser<?>> parseHtml(File file);
        //    public static ChainingHtmlParser<ChainingHtmlParser<?>> parseHtml(InputStream in);
        //    public static ChainingHtmlParser<ChainingHtmlParser<?>> parseHtml(Reader reader);
        //    public static ChainingHtmlParser<ChainingHtmlParser<?>> parseHtml(URL url);
        
        //    public static ChainingJsonStringParser parseJson(String json);
        //    public static ChainingJsonParser<ChainingJsonParser<?>> parseJson(File file);
        //    public static ChainingJsonParser<ChainingJsonParser<?>> parseJson(InputStream in);
        //    public static ChainingJsonParser<ChainingJsonParser<?>> parseJson(Reader reader);
        
        static ChainingTextWriter::Ptr write(const VCard::Ptr& vcard);
        static ChainingTextWriter::Ptr write(std::vector<VCard::Ptr> vcards);
        
        
        //    public static ChainingXmlWriter writeXml(VCard... vcards) {
        //        return writeXml(Arrays.asList(vcards));
        //    }
        //
        //    public static ChainingXmlWriter writeXml(Collection<VCard> vcards) {
        //        return new ChainingXmlWriter(vcards);
        //    }
        //
        //    public static ChainingHtmlWriter writeHtml(VCard... vcards) {
        //        return writeHtml(Arrays.asList(vcards));
        //    }
        //
        //    public static ChainingHtmlWriter writeHtml(Collection<VCard> vcards) {
        //        return new ChainingHtmlWriter(vcards);
        //    }
        //
        //    public static ChainingJsonWriter writeJson(VCard... vcards) {
        //        return writeJson(Arrays.asList(vcards));
        //    }
        // 
        //    public static ChainingJsonWriter writeJson(Collection<VCard> vcards) {
        //        return new ChainingJsonWriter(vcards);
        //    }
    private:
        Ezvcard();
    };
    
}

#endif /* ezvcard_hpp */
