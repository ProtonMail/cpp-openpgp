// AUTOGENERATED FILE - DO NOT MODIFY!
// This file generated by Djinni from open_pgp.djinni

#import <Foundation/Foundation.h>
@class PMNIPMMimeType;


@interface PMNIPMMimeType : NSObject

- (nonnull NSString *)getValue;

- (nonnull NSString *)getType;

- (nonnull NSString *)getGroup;

+ (nullable PMNIPMMimeType *)createInstance:(nonnull NSString *)type
                                      value:(nonnull NSString *)value;

@end
