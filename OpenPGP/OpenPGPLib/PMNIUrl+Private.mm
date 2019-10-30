// AUTOGENERATED FILE - DO NOT MODIFY!
// This file generated by Djinni from open_pgp.djinni

#import "PMNIUrl+Private.h"
#import "PMNIUrl.h"
#import "DJICppWrapperCache+Private.h"
#import "DJIError.h"
#import "DJIMarshal+Private.h"
#include <exception>
#include <stdexcept>
#include <utility>

static_assert(__has_feature(objc_arc), "Djinni requires ARC to be enabled for this file");

@interface PMNIUrl ()

- (id)initWithCpp:(const std::shared_ptr<::ProtonMail::IUrl>&)cppRef;

@end

@implementation PMNIUrl {
    ::djinni::CppProxyCache::Handle<std::shared_ptr<::ProtonMail::IUrl>> _cppRefHandle;
}

- (id)initWithCpp:(const std::shared_ptr<::ProtonMail::IUrl>&)cppRef
{
    if (self = [super init]) {
        _cppRefHandle.assign(cppRef);
    }
    return self;
}

- (nonnull NSString *)getValue {
    try {
        auto objcpp_result_ = _cppRefHandle.get()->getValue();
        return ::djinni::String::fromCpp(objcpp_result_);
    } DJINNI_TRANSLATE_EXCEPTIONS()
}

- (nonnull NSString *)getType {
    try {
        auto objcpp_result_ = _cppRefHandle.get()->getType();
        return ::djinni::String::fromCpp(objcpp_result_);
    } DJINNI_TRANSLATE_EXCEPTIONS()
}

+ (nullable PMNIUrl *)createInstance:(nonnull NSString *)type
                               value:(nonnull NSString *)value {
    try {
        auto objcpp_result_ = ::ProtonMail::IUrl::create_instance(::djinni::String::toCpp(type),
                                                                  ::djinni::String::toCpp(value));
        return ::OBJ_ProtonMail::IUrl::fromCpp(objcpp_result_);
    } DJINNI_TRANSLATE_EXCEPTIONS()
}

namespace OBJ_ProtonMail {

auto IUrl::toCpp(ObjcType objc) -> CppType
{
    if (!objc) {
        return nullptr;
    }
    return objc->_cppRefHandle.get();
}

auto IUrl::fromCppOpt(const CppOptType& cpp) -> ObjcType
{
    if (!cpp) {
        return nil;
    }
    return ::djinni::get_cpp_proxy<PMNIUrl>(cpp);
}

}  // namespace OBJ_ProtonMail

@end