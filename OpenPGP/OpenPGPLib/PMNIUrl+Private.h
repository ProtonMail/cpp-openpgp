// AUTOGENERATED FILE - DO NOT MODIFY!
// This file generated by Djinni from open_pgp.djinni

#include "bridge/i_url.hpp"
#include <memory>

static_assert(__has_feature(objc_arc), "Djinni requires ARC to be enabled for this file");

@class PMNIUrl;

namespace OBJ_ProtonMail {

class IUrl
{
public:
    using CppType = std::shared_ptr<::ProtonMail::IUrl>;
    using CppOptType = std::shared_ptr<::ProtonMail::IUrl>;
    using ObjcType = PMNIUrl*;

    using Boxed = IUrl;

    static CppType toCpp(ObjcType objc);
    static ObjcType fromCppOpt(const CppOptType& cpp);
    static ObjcType fromCpp(const CppType& cpp) { return fromCppOpt(cpp); }

private:
    class ObjcProxy;
};

}  // namespace OBJ_ProtonMail
