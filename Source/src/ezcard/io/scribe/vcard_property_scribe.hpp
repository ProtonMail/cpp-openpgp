//
//  vcard_property_scribe.hpp
//  OpenPGP
//
//  Created by Yanfeng Zhang on 1/11/17.
//  Copyright © 2017 Yanfeng Zhang. All rights reserved.
//

#ifndef vcard_property_scribe_hpp
#define vcard_property_scribe_hpp

#include <stdio.h>
#include <string>

#include "vcard_data_type.hpp"
#include "vcard_version.hpp"
#include "vcard_parameters.hpp"
#include "vcard_property.hpp"

#include "object_base.hpp"

#include "write_context.hpp"
#include "vcard.hpp"

namespace ezvcard {
    
    
    class Result {
    private:
        VCardProperty::Ptr _property;
        std::list<std::string> _warnings;
        
    public:
        typedef std::shared_ptr<Result> Ptr;
        
        /**
         * Creates a new result.
         * @param property the property object
         * @param warnings the warnings
         */
        Result(const VCardProperty::Ptr& property, std::list<std::string> warnings) {
            _property = property;
            _warnings = warnings;
        }
        
        /**
         * Gets the warnings.
         * @return the warnings
         */
        std::list<std::string> getWarnings() {
            return _warnings;
        }
        
        /**
         * Gets the property object.
         * @return the property object
         */
        VCardProperty::Ptr getProperty() {
            return _property;
        }
    };
    
    
    class VCardPropertyScribe : public PMObject {
    public:
        typedef std::shared_ptr<VCardPropertyScribe> Ptr;
        
    protected:
        std::string _propertyName;
        
        static std::string escape(const std::string& value,
                                  const WriteContext::Ptr& context);
        
        std::string _getPropertyName() final;
        
    public:
        VCardPropertyScribe(const std::string& propertyName);
        
        virtual Result::Ptr parseText(const std::string& value,
                                      const VCardDataType::Ptr& dataType,
                                      const VCardVersion::Ptr& version,
                                      const VCardParameters::Ptr& parameters) = 0;
        
        virtual VCardDataType::Ptr dataType(const VCardProperty::Ptr& property,
                                            const VCardVersion::Ptr& version) = 0;
        
        virtual VCardParameters::Ptr prepareParameters(const VCardProperty::Ptr& property,
                                                       const VCardVersion::Ptr& version,
                                                       const VCard::Ptr& vcard) = 0;
        
        virtual VCardDataType::Ptr defaultDataType(const VCardVersion::Ptr& version) = 0;
        
        virtual std::string writeText(const VCardProperty::Ptr& property,
                                      const WriteContext::Ptr& context) = 0;
        
        //    protected final QName qname;
        //    protected final Class<T> clazz;
        //    VCardPropertyScribe(Class<T> clazz, String propertyName)
        //    public VCardPropertyScribe(Class<T> clazz, String propertyName, QName qname);
        //    public Class<T> getPropertyClass();
        //    public QName getQName();
        //    public final void writeXml(T property, Element element);
        //    public final JCardValue writeJson(T property);
        //    public final Result<T> parseXml(Element element, VCardParameters parameters);
        //    public final Result<T> parseHtml(HCardElement element) ;
        //    public final Result<T> parseJson(JCardValue value, VCardDataType dataType, VCardParameters parameters);
        //    protected void _writeXml(T property, XCardElement element);
        //    protected JCardValue _writeJson(T property);
        //    protected abstract //    protected T _parseXml(XCardElement element, VCardParameters parameters, List<String> warnings);
        //    protected T _parseHtml(HCardElement element, List<String> warnings) ;
        //    protected T _parseJson(JCardValue value, VCardDataType dataType, VCardParameters parameters, List<String> warnings);
        //    private static String jcardValueToString(JCardValue value);
        //    protected static Date date(String value);
        //    protected static DateWriter date(Date date) ;
        
    };
    
    
    template <class T>
    class VCardPropertyScribeWrapper : public VCardPropertyScribe {
        static_assert(std::is_base_of<VCardProperty, T>::value, "ImagePropertyScribe<T>: T must be extent of ImageProperty type :-(");
    public:
        
        VCardPropertyScribeWrapper(const std::string& propertyName) : VCardPropertyScribe(propertyName) {
            
        }
        
    protected://subclass need to override those functions
        virtual std::string _writeText(const std::shared_ptr<T>& property,
                                       const WriteContext::Ptr& context) = 0;
        
        virtual VCardDataType::Ptr _defaultDataType(const VCardVersion::Ptr& version) = 0;
        
        virtual std::shared_ptr<T> _parseText(const std::string& value,
                                              const VCardDataType::Ptr& dataType,
                                              const VCardVersion::Ptr& version,
                                              const VCardParameters::Ptr& parameters,
                                              std::list<std::string> warnings) = 0;
        
    protected:
        //    protected static CannotParseException missingXmlElements(VCardDataType... dataTypes);
        //    protected static CannotParseException missingXmlElements(String... elements);
        /**
         * A utility method for switching between the "PREF" and "TYPE=PREF"
         * parameters when marshalling a property (version 4.0 vCards use "PREF=1",
         * while version 3.0 vCards use "TYPE=PREF"). This method is meant to be
         * called from a scribe's {@link #_prepareParameters} method.
         * @param property the property that is being marshalled
         * @param parameters the parameters that are being marshalled (this should
         * be a copy of the property's parameters so that changes can be made to
         * them without affecting the original object)
         * @param version the vCard version that the vCard is being marshalled to
         * @param vcard the vCard that's being marshalled
         */
        void handlePrefParam(const std::shared_ptr<T>& property, const VCardParameters::Ptr& parameters, const VCardVersion::Ptr& version, const VCard::Ptr& vcard) {
            //    switch (version) {
            //        case V2_1:
            //        case V3_0:
            //            parameters.setPref(null);
            //
            //            //find the property with the lowest PREF value in the vCard
            //            VCardProperty mostPreferred = null;
            //            Integer lowestPref = null;
            //            for (VCardProperty p : vcard.getProperties(property.getClass())) {
            //                Integer pref;
            //                try {
            //                    pref = p.getParameters().getPref();
            //                } catch (IllegalStateException e) {
            //                    continue;
            //                }
            //
            //                if (pref == null) {
            //                    continue;
            //                }
            //
            //                if (lowestPref == null || pref < lowestPref) {
            //                    mostPreferred = p;
            //                    lowestPref = pref;
            //                }
            //            }
            //
            //            if (property == mostPreferred) {
            //                parameters.put(VCardParameters.TYPE, "pref");
            //            }
            //            
            //            break;
            //        case V4_0:
            //            for (String type : property.getParameters().get(VCardParameters.TYPE)) {
            //                if ("pref".equalsIgnoreCase(type)) {
            //                    parameters.remove(VCardParameters.TYPE, type);
            //                    parameters.setPref(1);
            //                    break;
            //                }
            //            }
            //            break;
            //    }
        }

        
        /**
         * <p>
         * Determines the data type of a property instance.
         * </p>
         * <p>
         * This method should be overridden by child classes if a property's data
         * type changes depending on its value. The default implementation of this
         * method calls {@link #_defaultDataType}.
         * </p>
         * @param property the property
         * @param version the version of the vCard that is being generated
         * @return the data type or null if unknown
         */
        virtual VCardDataType::Ptr _dataType(const std::shared_ptr<T>& property, const VCardVersion::Ptr& version) {
            return _defaultDataType(version);
        }
        /**
         * <p>
         * Sanitizes a property's parameters before the property is written.
         * </p>
         * <p>
         * This method should be overridden by child classes that wish to tweak the
         * property's parameters before the property is written. The default
         * implementation of this method does nothing.
         * </p>
         * @param property the property
         * @param copy the list of parameters to make modifications to (it is a copy
         * of the property's parameters)
         * @param version the version of the vCard that is being generated
         * @param vcard the vCard that the property belongs to
         */
        virtual void _prepareParameters(const std::shared_ptr<T>& property, const VCardParameters::Ptr& copy, const VCardVersion::Ptr& version, const VCard::Ptr& vcard) {
            //do nothing
        }
        
    protected: // VCardPropertyScribe wrapper functions. all should be finial
        /**
         * Sanitizes a property's parameters (called before the property is
         * written). Note that a copy of the parameters is returned so that the
         * property object does not get modified.
         * @param property the property
         * @param version the version of the vCard that is being generated
         * @param vcard the vCard that the property belongs to
         * @return the sanitized parameters
         */
        VCardParameters::Ptr prepareParameters(const VCardProperty::Ptr& property, const VCardVersion::Ptr& version, const VCard::Ptr& vcard) final {
            //make a copy because the property should not get modified when it is marshalled
            auto convertObj = std::dynamic_pointer_cast<T>(property); //TODO::fix later to add null handling
            VCardParameters::Ptr copy = std::make_shared<VCardParameters>(convertObj->getParameters()->getMap());
            _prepareParameters(convertObj, copy, version, vcard);
            return copy;
        }
        /**
         * <p>
         * Determines the property's default data type.
         * </p>
         * <p>
         * When writing a plain-text vCard, if the data type of a property instance
         * (as determined by the {@link #dataType} method) matches the default data
         * type, then a VALUE parameter will *not* be written.
         * </p>
         * <p>
         * When parsing a plain-text vCard, if a property has no VALUE parameter,
         * then the property's default data type will be passed into the
         * {@link #parseText} method.
         * </p>
         * @param version the vCard version
         * @return the default data type or null if unknown
         */
        VCardDataType::Ptr defaultDataType(const VCardVersion::Ptr& version) final {
            return _defaultDataType(version);
        }
        /**
         * Marshals a property's value to a string.
         * @param property the property
         * @param context contains information about the vCard being written, such
         * as the target version
         * @return the string value
         * @throws SkipMeException if the property should not be written to the data
         * stream
         */
        std::string writeText(const VCardProperty::Ptr& property, const WriteContext::Ptr& context) final {
            auto convertObj = std::dynamic_pointer_cast<T>(property); //TODO::fix later to add null handling
            return _writeText(convertObj, context);
        }
        /**
         * Unmarshals a property from a plain-text vCard.
         * @param value the value as read off the wire
         * @param dataType the data type of the property value. The property's VALUE
         * parameter is used to determine the data type. If the property has no
         * VALUE parameter, then this parameter will be set to the property's
         * default datatype, as determined by the {@link #defaultDataType} method.
         * Note that the VALUE parameter is removed from the property's parameter
         * list after it has been read.
         * @param version the version of the vCard that is being parsed
         * @param parameters the parsed parameters
         * @return the unmarshalled property and its warnings
         * @throws CannotParseException if the marshaller could not parse the
         * property's value
         * @throws SkipMeException if the property should not be added to the final
         * {@link VCard} object
         * @throws EmbeddedVCardException if the property value is an embedded vCard
         * (i.e. the AGENT property)
         */
        Result::Ptr parseText(const std::string& value, const VCardDataType::Ptr& dataType, const VCardVersion::Ptr& version, const VCardParameters::Ptr& parameters) final {
            std::list<std::string> warnings = std::list<std::string> ();
            auto property = _parseText(value, dataType, version, parameters, warnings);
            property->setParameters(parameters);
            return std::make_shared<Result>(property, warnings);
        }
        /**
         * Determines the data type of a property instance.
         * @param property the property
         * @param version the version of the vCard that is being generated
         * @return the data type or null if unknown
         */
        VCardDataType::Ptr dataType(const VCardProperty::Ptr& property, const VCardVersion::Ptr& version) final {
            auto convertObj = std::dynamic_pointer_cast<T>(property); //TODO::fix later to add null handling
            return _dataType(convertObj, version);
        }
    };
    
}

#endif /* vcard_property_scribe_hpp */
