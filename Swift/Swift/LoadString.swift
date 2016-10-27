//
//  LoadString.swift
//  SwiftObjC
//
//  Created by Yanfeng Zhang on 1/30/15.
//  Copyright (c) 2015 Yanfeng Zhang. All rights reserved.
//

import Foundation


func GetStringFromSampleFile(_ key: String) -> String {
    return Bundle.main.localizedString(forKey: key, value: key, table: "sample")
}
