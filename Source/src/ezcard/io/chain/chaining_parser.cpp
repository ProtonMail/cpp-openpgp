//
//  chaining_parser.cpp
//  OpenPGP
//
//  Created by Yanfeng Zhang on 12/2/16.
//  Copyright © 2016 Yanfeng Zhang. All rights reserved.
//

#include "chaining_parser.hpp"

namespace ezvcard {
    

ChainingParser::ChainingParser(const std::string& string) {
    _str = string;
    //this(string, null, null, null);
}


/**
 * Reads the first vCard from the stream.
 * @return the vCard or null if there are no vCards
 * @throws IOException if there's an I/O problem
 */
VCard::Ptr ChainingParser::first() { // throws IOException
    auto reader = constructReader();
    if (_index != nullptr) {
        reader->setScribeIndex(_index);
    }
    
    //try {
    auto vcard = reader->readNext();
    _warnings.push_back(reader->getWarnings());
    
    return vcard;
    //    } finally {
    //        if (closeWhenDone()) {
    //            reader.close();
    //        }
    //    }
}

/**
 * Reads all vCards from the stream.
 * @return the parsed vCards
 * @throws IOException if there's an I/O problem
 */
std::vector<VCard::Ptr> ChainingParser::all() {
    auto reader = constructReader();
//    try {
        std::vector<VCard::Ptr> vcards;
        while (auto vcard = reader->readNext()) {
//            if (warnings != null) {
//                warnings.add(reader.getWarnings());
//            }
            vcards.push_back(vcard);
        }
        return vcards;
//    } finally {
//        if (closeWhenDone()) {
//            reader.close();
//        }
//    }
}


//    private boolean closeWhenDone() {
//        return in == null && reader == null;
//    }


//    ChainingParser(InputStream in) {
//        this(null, in, null, null);
//    }
//    
//    ChainingParser(Reader reader) {
//        this(null, null, reader, null);
//    }
//    
//    ChainingParser(File file) {
//        this(null, null, null, file);
//    }
//    
//    ChainingParser() {
//        this(null, null, null, null);
//    }
//    
//    private ChainingParser(String string, InputStream in, Reader reader, File file) {
//        this.string = string;
//        this.in = in;
//        this.reader = reader;
//        this.file = file;
//    }
//
//    /**
//     * Registers a property scribe.
//     * @param scribe the scribe
//     * @return this
//     */
//    public T register(VCardPropertyScribe<? extends VCardProperty> scribe) {
//        if (index == null) {
//            index = new ScribeIndex();
//        }
//        index.register(scribe);
//        return this_;
//    }
//    
//    /**
//     * Provides a list object that any parser warnings will be put into.
//     * @param warnings the list object that will be populated with the warnings
//     * of each parsed vCard. Each element in the list is a list of warnings for
//     * one parsed vCard. Therefore, the size of this list will be equal to the
//     * number of parsed vCards. If a vCard does not have any warnings, then its
//     * warning list will be empty.
//     * @return this
//     */
//    public T warnings(List<List<String>> warnings) {
//        this.warnings = warnings;
//        return this_;
//    }
//    

}
