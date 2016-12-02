//
//  ezcard.hpp
//  OpenPGP
//
//  Created by Yanfeng Zhang on 12/1/16.
//  Copyright © 2016 Yanfeng Zhang. All rights reserved.
//

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
