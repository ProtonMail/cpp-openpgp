# OpenPGP


## Building 

Must always use `test` for building!

### iOS 

Simply use xcode.

### Android

Go to Android folder and run `sh build_android.sh`

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

### In ProtonMail iOS repo

1. Run `pod install --no-repo-update`

# TODO List

- [x] add quoted_printable encoding  
- [ ] add generic compare function
- [ ] add a base class called cloneable
- [ ] add a base class called compareable 

