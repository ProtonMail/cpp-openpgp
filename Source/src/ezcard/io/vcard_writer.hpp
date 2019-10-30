//
//  vcard_writer.hpp
//  OpenPGP
//
//  Created by Yanfeng Zhang on 5/8/17.
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
