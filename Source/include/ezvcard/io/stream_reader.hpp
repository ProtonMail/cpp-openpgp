//
//  StreamReader.hpp
//  OpenPGP
//
//  Created by Yanfeng Zhang on 12/2/16.
//  Copyright © 2016 Yanfeng Zhang. All rights reserved.
//

#ifndef StreamReader_hpp
#define StreamReader_hpp


#include <ezvcard/io/scribe/scribe_index.hpp>
#include <ezvcard/vcard.hpp>
#include <list>

#include <ezvcard/io/parse_warnings.hpp>

namespace ezvcard {
    

class StreamReader {
protected:
    ParseWarnings _warnings = ParseWarnings();
    ScribeIndex::Ptr _index = std::make_shared<ScribeIndex>();
    virtual VCard::Ptr _readNext() = 0;
    //
    //    /**
    //     * Matches up a list of {@link Label} properties with their corresponding
    //     * {@link Address} properties. If no match can be found, then the LABEL
    //     * property itself is assigned to the vCard.
    //     * @param vcard the vCard that the properties belong to
    //     * @param labels the LABEL properties
    //     */
    //    protected void assignLabels(VCard vcard, List<Label> labels);
    
public:
    typedef std::shared_ptr<StreamReader> Ptr;
    
    void setScribeIndex(ScribeIndex::Ptr index);
    ScribeIndex::Ptr getScribeIndex();
    VCard::Ptr readNext();
    std::list<VCard::Ptr> readAll();
    //void registerScribe(VCardPropertyScribe<? extends VCardProperty> scribe)
    std::list<std::string> getWarnings();
};

}
#endif /* StreamReader_hpp */
