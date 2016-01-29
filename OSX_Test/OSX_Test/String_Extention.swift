//
//  String_Extention.swift
//  OSX_Test
//
//  Created by Yanfeng Zhang on 1/13/16.
//  Copyright (c) 2016 Yanfeng Zhang. All rights reserved.
//

import Foundation


extension String {
    
    /// Create NSData from hexadecimal string representation
    ///
    /// This takes a hexadecimal representation and creates a NSData object. Note, if the string has any spaces, those are removed. Also if the string started with a '<' or ended with a '>', those are removed, too. This does no validation of the string to ensure it's a valid hexadecimal string
    ///
    /// The use of `strtoul` inspired by Martin R at http://stackoverflow.com/a/26284562/1271826
    ///
    /// :returns: NSData represented by this hexadecimal string. Returns nil if string contains characters outside the 0-9 and a-f range.
    
    func dataFromHexadecimalString() -> NSData? {
//        let trimmedString = self.stringByTrimmingCharactersInSet(NSCharacterSet(charactersInString: "<> ")).stringByReplacingOccurrencesOfString(" ", withString: "")
//        
//        // make sure the cleaned up string consists solely of hex digits, and that we have even number of them
//        
//        var error: NSError?
//        let regex = NSRegularExpression(pattern: "^[0-9a-f]*$", options: .CaseInsensitive, error: &error)
//        let found = regex?.firstMatchInString(trimmedString, options: nil, range: NSMakeRange(0, count(trimmedString)))
//        if found == nil || found?.range.location == NSNotFound || count(trimmedString) % 2 != 0 {
//            return nil
//        }
//        
//        // everything ok, so now let's build NSData
//        
//        let data = NSMutableData(capacity: count(trimmedString) / 2)
//        
//        for var index = trimmedString.startIndex; index < trimmedString.endIndex; index = index.successor().successor() {
//            let byteString = trimmedString.substringWithRange(Range<String.Index>(start: index, end: index.successor().successor()))
//            let num = UInt8(byteString.withCString { strtoul($0, nil, 16) })
//            data?.appendBytes([num] as [UInt8], length: 1)
//        }
//        
//        return data
        return nil
    }
}

extension NSData {
    
    /// Create hexadecimal string representation of NSData object.
    ///
    /// :returns: String representation of this NSData object.
    
    func hexadecimalString() -> String {
        var string = NSMutableString(capacity: length * 2)
        var byte: UInt8 = 0
        
        for i in 0 ..< length {
            getBytes(&byte, range: NSMakeRange(i, 1))
            string.appendFormat("%02x", byte)
        }
        
        return string as String
    }
}