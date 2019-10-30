//
//  StreamReader.cpp
//  OpenPGP
//
//  Created by Yanfeng Zhang on 12/2/16.
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

#include "stream_reader.hpp"

namespace ezvcard {
    
/**
 * Reads all vCards from the data stream.
 * @return the vCards
 * @throws IOException if there's a problem reading from the stream
 */
std::list<VCard::Ptr> StreamReader::readAll() {
//    List<VCard> vcards = new ArrayList<VCard>();
//    VCard vcard = null;
//    while ((vcard = readNext()) != null) {
//        vcards.add(vcard);
//    }
//    return vcards;
    return std::list<VCard::Ptr>();
}

/**
 * Reads the next vCard from the data stream.
 * @return the next vCard or null if there are no more
 * @throws IOException if there's a problem reading from the stream
 */
VCard::Ptr StreamReader::readNext() {
    _warnings.clear();
    return _readNext();
}

/**
 * Gets the scribe index.
 * @return the scribe index
 */
ScribeIndex::Ptr StreamReader::getScribeIndex() {
    return _index;
}

/**
 * Sets the scribe index.
 * @param index the scribe index
 */
void StreamReader::setScribeIndex(ScribeIndex::Ptr index) {
    _index = index;
}

/**
 * Gets the warnings from the last vCard that was unmarshalled. This list is
 * reset every time a new vCard is read.
 * @return the warnings or empty list if there were no warnings
 */
std::list<std::string> StreamReader::getWarnings() {
    return _warnings.copy();
}

//
//    /**
//     * Matches up a list of {@link Label} properties with their corresponding
//     * {@link Address} properties. If no match can be found, then the LABEL
//     * property itself is assigned to the vCard.
//     * @param vcard the vCard that the properties belong to
//     * @param labels the LABEL properties
//     */
//    protected void assignLabels(VCard vcard, List<Label> labels) {
//        List<Address> adrs = vcard.getAddresses();
//        for (Label label : labels) {
//            boolean orphaned = true;
//            Set<AddressType> labelTypes = new HashSet<AddressType>(label.getTypes());
//            for (Address adr : adrs) {
//                if (adr.getLabel() != null) {
//                    //a label has already been assigned to it
//                    continue;
//                }
//                
//                Set<AddressType> adrTypes = new HashSet<AddressType>(adr.getTypes());
//                if (adrTypes.equals(labelTypes)) {
//                    adr.setLabel(label.getValue());
//                    orphaned = false;
//                    break;
//                }
//            }
//            if (orphaned) {
//                vcard.addOrphanedLabel(label);
//            }
//        }
//    }
//    
//    /**
//     * <p>
//     * Registers a property scribe. This is the same as calling:
//     * </p>
//     * <p>
//     * {@code getScribeIndex().register(scribe)}
//     * </p>
//     * @param scribe the scribe to register
//     */
//    public void registerScribe(VCardPropertyScribe<? extends VCardProperty> scribe) {
//        index.register(scribe);
//    }


}
