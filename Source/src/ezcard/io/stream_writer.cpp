//
//  stream_writer.cpp
//  OpenPGP
//
//  Created by Yanfeng Zhang on 5/17/17.
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


#include "stream_writer.hpp"
#include "product_id.hpp"
#include "address_property.hpp"
#include <sstream>
#include "ezvcard.hpp"

namespace ezvcard {
    
    
    /**
     * Writes a vCard to the stream.
     * @param vcard the vCard that is being written
     * @throws IOException if there's a problem writing to the output stream
     * @throws IllegalArgumentException if a scribe hasn't been registered for a
     * custom property class (see: {@link #registerScribe registerScribe})
     */
    void StreamWriter::write(VCard::Ptr vcard) {
        auto properties = prepare(vcard);
        _write(vcard, properties);
    }
    
    
    
    /**
     * Gets whether a {@link ProductId} property will be added to each vCard
     * that marks it as having been generated by this library. For 2.1 vCards,
     * the extended property "X-PRODID" will be added, since {@link ProductId}
     * is not supported by that version.
     * @return true if the property will be added, false if not (defaults to
     * true)
     */
    bool StreamWriter::isAddProdId() {
        return _addProdId;
    }
    
    /**
     * Sets whether to add a {@link ProductId} property to each vCard that marks
     * it as having been generated by this library. For 2.1 vCards, the extended
     * property "X-PRODID" will be added, since {@link ProductId} is not
     * supported by that version.
     * @param addProdId true to add the property, false not to (defaults to
     * true)
     */
    void StreamWriter::setAddProdId(bool addProdId) {
        _addProdId = addProdId;
    }
    
    /**
     * Gets whether properties that do not support the target version will be
     * excluded from the written vCard.
     * @return true to exclude properties that do not support the target
     * version, false not to (defaults to true)
     */
    bool StreamWriter::isVersionStrict() {
        return _versionStrict;
    }
    
    /**
     * Sets whether to exclude properties that do not support the target version
     * from the written vCard.
     * @param versionStrict true to exclude such properties, false not to
     * (defaults to true)
     */
    void StreamWriter::setVersionStrict(bool versionStrict) {
        _versionStrict = versionStrict;
    }
    
    /**
     * <p>
     * Registers a property scribe. This is the same as calling:
     * </p>
     * <p>
     * {@code getScribeIndex().register(scribe)}
     * </p>
     * @param scribe the scribe to register
     */
    //void registerScribe(VCardPropertyScribe<? extends VCardProperty> scribe) {
    //    index.register(scribe);
    //}
    
    /**
     * Gets the scribe index.
     * @return the scribe index
     */
    ScribeIndex::Ptr StreamWriter::getScribeIndex() {
        return _index;
    }
    
    /**
     * Sets the scribe index.
     * @param index the scribe index
     */
    void StreamWriter::setScribeIndex(ScribeIndex::Ptr index) {
        _index = index;
    }
    
    /**
     * Determines which properties need to be written.
     * @param vcard the vCard to write
     * @return the properties to write
     * @throws IllegalArgumentException if a scribe hasn't been registered for a
     * custom property class (see: {@link #registerScribe(VCardPropertyScribe)
     * registerScribe})
     */
    std::vector<VCardProperty::Ptr> StreamWriter::prepare(VCard::Ptr vcard) {
        VCardVersion::Ptr targetVersion = getTargetVersion();
        std::vector<VCardProperty::Ptr> propertiesToAdd;
        std::set<std::string> unregistered;
        
        VCardProperty::Ptr prodIdProperty = nullptr;
        for (auto property : vcard->getProperties()) {
            if (_versionStrict && !property->isSupportedBy(targetVersion)) {
                //do not add the property to the vCard if it is not supported by the target version
                continue;
            }
            
            //do not add PRODID to the property list yet
            if (typeid(property.get()) == typeid(ProductId)) {
                prodIdProperty = property;
                continue;
            }
            
            if ( std::dynamic_pointer_cast<ProductId>(property) ) {
                prodIdProperty = property;
                continue;
            }
            
            //check for scribe
            if (!_index->hasPropertyScribe(property)) {
                unregistered.insert(property->className());
                continue;
            }
            propertiesToAdd.push_back(property);
            
            //add LABEL properties for each ADR property if the target version is 2.1 or 3.0
            if ((targetVersion == VCardVersion::V2_1() || targetVersion == VCardVersion::V3_0()) &&
                std::dynamic_pointer_cast<Address>(property) /*typeid(property) == typeid(Address)*/) {
                if (Address::Ptr adr = std::dynamic_pointer_cast<Address>(property)) {
                    //TODO:: add later
//                    Address adr = (Address) property;
//                    String labelStr = adr.getLabel();
//                    if (labelStr == null) {
//                        continue;
//                    }
//                    
//                    Label label = new Label(labelStr);
//                    label.getTypes().addAll(adr.getTypes());
//                    propertiesToAdd.add(label);
                }
            }
        }
        
        if (unregistered.size() > 0) {
            std::list<std::string> classes;
            for (auto s : unregistered) {
                classes.push_back(s);
            }
            std::stringstream ss;
            std::copy(classes.begin(), classes.end(), std::ostream_iterator<std::string>(ss, ","));
            throw std::invalid_argument(ss.str());
        }
        
        //create a PRODID property, saying the vCard was generated by this library
        if (_addProdId) {
            if (targetVersion == VCardVersion::V2_1()) {
                prodIdProperty = std::make_shared<RawProperty>("X-PRODID", Ezvcard::PRODID + Ezvcard::VERSION_NUMBER);
            } else {
                prodIdProperty = std::make_shared<ProductId>(Ezvcard::PRODID + Ezvcard::VERSION_NUMBER);
            }
        }
        
        //add PRODID to the beginning of the vCard
        if (prodIdProperty != nullptr) {
            auto it = propertiesToAdd.begin();
            propertiesToAdd.insert(it, prodIdProperty);
        }
        
        return propertiesToAdd;
    }
}

