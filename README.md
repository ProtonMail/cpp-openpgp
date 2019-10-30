# cpp-openpgp

## Introduction

This is the main crypto library on mobile since 2015. we have migrated to [gopenpgp]() start from 2018-q4. The OpenPGP part is deprecated now. we use this library to generate RSA key only.

VCard is currently in used in the iOS-mail application.

### OpenPGP

OpenPGP part originally forked from https://github.com/calccrypto/OpenPGP. 

### VCard

The VCard parser is porting from https://github.com/mangstadt/ez-vcard which is java based. 

## Building 

user the build scripts in `Scripts` folder

### iOS 

Simply use xcode.

### Android

Go to `Android_Build` folder and run `sh build_android.sh`

## Usage

Please check sample projects in the `OpenPGP.xcworkspace`.

## Commit

When patching, we need to be based on these versions

* vinnie
    * commit on Mar 1, 2017
    * 9235609703ae7cb59c356dbb18da1d642bfd4bbb
* ezvcard
    * commit on Feb 19, 2017
    * 234f3a9bb9c540dac3de67864e339bfa6e528f19
    
# Update procedure

Make sure you have `djinni` installed

## No new code file generated

### In OpenPGP repo

1. Update `open_pgp.djinni` with all the interfaces and method you need
2. Run `OpenPGP/Scripts/bridge/build_bridge.sh`
3. Let the class inherit from the auto-generated classes. e.g. let `Photo` class inherit from `IPhoto` class (don’t forget to update the include file!)
4. Under `ProtonMail` namespace, implement the methods created in the auto-generated interface class. e.g. implement `IPhoto` class methods under `ProtonMail` namespace
5. Compile the framework for iOS using `build_pgp_ios_universal.sh` 

## New code file generated

### In OpenPGP repo

1. In the `Build phase` tab, add the newly generated files in `copy file` list
2. In folder `OpenPGPlib/ezvcard`, add those new documents to the target

### In [ProtonMail iOS](https://github.com/ProtonMail/ios-mail) repo

1. Run `pod install --no-repo-update`

# TODO List

- [x] add quoted_printable encoding  
- [ ] add generic compare function
- [ ] add a base class called cloneable
- [ ] add a base class called compareable 
- [ ] split this libaray to 3 different libaraies: OpenPGP, Vinnie, VCard
- [ ] refactore OpenPGP part
- [ ] Catalyst supporting (in Beta)
