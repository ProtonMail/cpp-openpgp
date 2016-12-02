//
//  scribe_index.hpp
//  OpenPGP
//
//  Created by Yanfeng Zhang on 12/2/16.
//  Copyright © 2016 Yanfeng Zhang. All rights reserved.
//

#ifndef scribe_index_hpp
#define scribe_index_hpp

#include <iostream>
#include <string>
#include <unordered_map>
#include <map>

#include "vcard_property_scribe.hpp"

namespace ezvcard{
    
    //define standard property scribes
    class ScribeIndex {
    private:
        std::map<std::string, VCardPropertyScribe::Ptr> standardByName = std::map<std::string, VCardPropertyScribe::Ptr>();
        std::map<std::string, VCardPropertyScribe::Ptr> standardByClass = std::map<std::string, VCardPropertyScribe::Ptr>();
        
        //TODO::use it later.
        std::map<std::string, VCardPropertyScribe::Ptr> extendedByName = std::map<std::string, VCardPropertyScribe::Ptr>();
        std::map<std::string, VCardPropertyScribe::Ptr> extendedByClass = std::map<std::string, VCardPropertyScribe::Ptr>();
        
        
        //    void registerStandard(VCardPropertyScribe<? extends VCardProperty> scribe);
        //        private static final Map<QName, VCardPropertyScribe<? extends VCardProperty>> standardByQName = new HashMap<QName, VCardPropertyScribe<? extends VCardProperty>>();
        //    private final Map<QName, VCardPropertyScribe<? extends VCardProperty>> extendedByQName = new HashMap<QName, VCardPropertyScribe<? extends VCardProperty>>(0);
        
        void registerStandard(const VCardPropertyScribe::Ptr& scribe);
        void registerExtended(const VCardPropertyScribe::Ptr& scribe);
        
    public:
        typedef std::shared_ptr<ScribeIndex> Ptr;
        
        ScribeIndex();
        ~ScribeIndex();
        
        VCardPropertyScribe::Ptr getPropertyScribe(const std::string& propertyName);
        VCardPropertyScribe::Ptr getPropertyScribe(const VCardProperty::Ptr& property);
        
        bool hasPropertyScribe(const VCardProperty::Ptr& property);
        
        //    /**
        //     * Gets the appropriate property scribe for a given property instance.
        //     * @param property the property instance
        //     * @return the property scribe or null if not found
        //     */
        //    public VCardPropertyScribe<? extends VCardProperty> getPropertyScribe(VCardProperty property) {
        //        if (property instanceof RawProperty) {
        //            RawProperty raw = (RawProperty) property;
        //            return new RawPropertyScribe(raw.getPropertyName());
        //        }
        //
        //        return getPropertyScribe(property.getClass());
        //    }
        //
        //    /**
        //     * Gets a property scribe by XML local name and namespace.
        //     * @param qname the XML local name and namespace
        //     * @return the property scribe or a {@link XmlScribe} if not found
        //     */
        //    public VCardPropertyScribe<? extends VCardProperty> getPropertyScribe(QName qname) {
        //        VCardPropertyScribe<? extends VCardProperty> scribe = extendedByQName.get(qname);
        //        if (scribe != null) {
        //            return scribe;
        //        }
        //
        //        scribe = standardByQName.get(qname);
        //        if (scribe != null) {
        //            return scribe;
        //        }
        //
        //        if (VCardVersion.V4_0.getXmlNamespace().equals(qname.getNamespaceURI())) {
        //            return new RawPropertyScribe(qname.getLocalPart().toUpperCase());
        //        }
        //
        //        return getPropertyScribe(Xml.class);
        //    }
        //	public VCardPropertyScribe<? extends VCardProperty> getPropertyScribe(Class<? extends VCardProperty> clazz) {
        //    VCardPropertyScribe<? extends VCardProperty> scribe = extendedByClass.get(clazz);
        //    if (scribe != null) {
        //        return scribe;
        //    }
        //
        //    return standardByClass.get(clazz);
        //}
        
        //    /**
        //     * Registers a property scribe.
        //     * @param scribe the scribe to register
        //     */
        //    public void register(VCardPropertyScribe<? extends VCardProperty> scribe) {
        //        extendedByName.put(scribe.getPropertyName().toUpperCase(), scribe);
        //        extendedByClass.put(scribe.getPropertyClass(), scribe);
        //        extendedByQName.put(scribe.getQName(), scribe);
        //    }
        //
        //    /**
        //     * Unregisters a property scribe.
        //     * @param scribe the scribe to unregister
        //     */
        // void unregister(VCardPropertyScribe<? extends VCardProperty> scribe);
    };
    
}

#endif /* scribe_index_hpp */
