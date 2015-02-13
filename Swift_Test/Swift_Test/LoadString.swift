//
//  LoadString.swift
//  SwiftObjC
//
//  Created by Yanfeng Zhang on 1/30/15.
//  Copyright (c) 2015 Yanfeng Zhang. All rights reserved.
//

import Foundation


func GetStringFromSampleFile(key: String) -> String {
    return NSBundle.mainBundle().localizedStringForKey(key, value: key, table: "sample")
}
