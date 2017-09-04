// AUTOGENERATED FILE - DO NOT MODIFY!
// This file generated by Djinni from open_pgp.djinni

#import "PMNDecryptSignVerify+Private.h"
#import "DJIMarshal+Private.h"
#include <cassert>

namespace OBJ_ProtonMail {

auto DecryptSignVerify::toCpp(ObjcType obj) -> CppType
{
    assert(obj);
    return {::djinni::String::toCpp(obj.plainText),
            ::djinni::Bool::toCpp(obj.verify)};
}

auto DecryptSignVerify::fromCpp(const CppType& cpp) -> ObjcType
{
    return [[PMNDecryptSignVerify alloc] initWithPlainText:(::djinni::String::fromCpp(cpp.plain_text))
                                                    verify:(::djinni::Bool::fromCpp(cpp.verify))];
}

}  // namespace OBJ_ProtonMail
