//
//  vcard_writer.hpp
//  OpenPGP
//
//  Created by Yanfeng Zhang on 5/8/17.
//  Copyright © 2017 Yanfeng Zhang. All rights reserved.
//

#ifndef vcard_writer_hpp
#define vcard_writer_hpp

#include <stdio.h>
#include "vobject_writer.hpp"
#include "vcard_version.hpp"
#include "stream_writer.hpp"
#include "vcard.hpp"
#include "target_application.hpp"

namespace ezvcard {
    using namespace vinnie;
    
    class VCardWriter : public StreamWriter {
    public:
        typedef std::shared_ptr<VCardWriter> Ptr;
        
    private:
        VObjectWriter::Ptr _writer;
        VCardVersion::Ptr _targetVersion;
        bool _includeTrailingSemicolons;
        bool _isIncludeTrailingSemicolonsSet = false;
        TargetApplication _targetApplication = TargetApplication::Others;
        //final List<Boolean> prodIdStack = new ArrayList<Boolean>();
        
    protected:
        void _write(VCard::Ptr vcard, std::vector<VCardProperty::Ptr> propertiesToAdd);
        VCardVersion::Ptr getTargetVersion();
        void writeNestedVCard(VCard::Ptr nestedVCard, VCardProperty::Ptr property, VCardPropertyScribe::Ptr scribe, VCardParameters::Ptr parameters, std::string value);
        void handleValueParameter(VCardProperty::Ptr property, VCardPropertyScribe::Ptr scribe, VCardParameters::Ptr parameters);
        void handleLabelParameter(VCardProperty::Ptr property, VCardParameters::Ptr parameters);
        void fixBinaryPropertyForOutlook(VCardProperty::Ptr property);
        bool isDateTimeValueParameterSpecialCase(VCardDataType::Ptr defaultDataType, VCardDataType::Ptr dataType);
        
    public:
        VCardWriter(const std::shared_ptr<std::stringstream>& writer, const VCardVersion::Ptr& targetVersion);
        
        bool isCaretEncodingEnabled();
        void setCaretEncodingEnabled(bool enable);
        VObjectWriter::Ptr getVObjectWriter();
        
        //    public VCardWriter(OutputStream out, VCardVersion targetVersion);
        //    public VCardWriter(File file, VCardVersion targetVersion);
        //    public VCardWriter(File file, boolean append, VCardVersion targetVersion);
        
        void setTargetVersion(VCardVersion::Ptr targetVersion);
        
        TargetApplication getTargetApplication();
        void setTargetApplication(TargetApplication targetApplication);
        
        bool isIncludeTrailingSemicolons();
        void setIncludeTrailingSemicolons(bool include);
        
    };
    
}


#endif /* vcard_writer_hpp */
