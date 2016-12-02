// AUTOGENERATED FILE - DO NOT MODIFY!
// This file generated by Djinni from open_pgp.djinni

#include "bridge/i_gender.hpp"
#include <memory>

static_assert(__has_feature(objc_arc), "Djinni requires ARC to be enabled for this file");

@class PMNIGender;

namespace OBJ_ProtonMail {

class IGender
{
public:
    using CppType = std::shared_ptr<::ProtonMail::IGender>;
    using CppOptType = std::shared_ptr<::ProtonMail::IGender>;
    using ObjcType = PMNIGender*;

    using Boxed = IGender;

    static CppType toCpp(ObjcType objc);
    static ObjcType fromCppOpt(const CppOptType& cpp);
    static ObjcType fromCpp(const CppType& cpp) { return fromCppOpt(cpp); }

private:
    class ObjcProxy;
};

}  // namespace OBJ_ProtonMail

