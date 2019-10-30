// AUTOGENERATED FILE - DO NOT MODIFY!
// This file generated by Djinni from open_pgp.djinni

#import "PMNIFormattedName+Private.h"
#import "PMNIFormattedName.h"
#import "DJICppWrapperCache+Private.h"
#import "DJIError.h"
#import "DJIMarshal+Private.h"
#include <exception>
#include <stdexcept>
#include <utility>

static_assert(__has_feature(objc_arc), "Djinni requires ARC to be enabled for this file");

@interface PMNIFormattedName ()

- (id)initWithCpp:(const std::shared_ptr<::ProtonMail::IFormattedName>&)cppRef;

@end

@implementation PMNIFormattedName {
    ::djinni::CppProxyCache::Handle<std::shared_ptr<::ProtonMail::IFormattedName>> _cppRefHandle;
}

- (id)initWithCpp:(const std::shared_ptr<::ProtonMail::IFormattedName>&)cppRef
{
    if (self = [super init]) {
        _cppRefHandle.assign(cppRef);
    }
    return self;
}

- (nonnull NSString *)getLanguage {
    try {
        auto objcpp_result_ = _cppRefHandle.get()->getLanguage();
        return ::djinni::String::fromCpp(objcpp_result_);
    } DJINNI_TRANSLATE_EXCEPTIONS()
}

- (void)setLanguage:(nonnull NSString *)language {
    try {
        _cppRefHandle.get()->setLanguage(::djinni::String::toCpp(language));
    } DJINNI_TRANSLATE_EXCEPTIONS()
}

- (nonnull NSString *)getParameter:(nonnull NSString *)name {
    try {
        auto objcpp_result_ = _cppRefHandle.get()->getParameter(::djinni::String::toCpp(name));
        return ::djinni::String::fromCpp(objcpp_result_);
    } DJINNI_TRANSLATE_EXCEPTIONS()
}

- (nonnull NSString *)getValue {
    try {
        auto objcpp_result_ = _cppRefHandle.get()->getValue();
        return ::djinni::String::fromCpp(objcpp_result_);
    } DJINNI_TRANSLATE_EXCEPTIONS()
}

+ (nullable PMNIFormattedName *)createInstance:(nonnull NSString *)name {
    try {
        auto objcpp_result_ = ::ProtonMail::IFormattedName::create_instance(::djinni::String::toCpp(name));
        return ::OBJ_ProtonMail::IFormattedName::fromCpp(objcpp_result_);
    } DJINNI_TRANSLATE_EXCEPTIONS()
}

namespace OBJ_ProtonMail {

auto IFormattedName::toCpp(ObjcType objc) -> CppType
{
    if (!objc) {
        return nullptr;
    }
    return objc->_cppRefHandle.get();
}

auto IFormattedName::fromCppOpt(const CppOptType& cpp) -> ObjcType
{
    if (!cpp) {
        return nil;
    }
    return ::djinni::get_cpp_proxy<PMNIFormattedName>(cpp);
}

}  // namespace OBJ_ProtonMail

@end