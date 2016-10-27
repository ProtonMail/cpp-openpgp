//
//  TestView.swift
//  SwiftObjC
//
//  Created by Yanfeng Zhang on 1/29/15.
//  Copyright (c) 2015 Yanfeng Zhang. All rights reserved.
//

import Foundation
import UIKit

class TestView: UIViewController {
    
    fileprivate var public_key_:String!
    fileprivate var private_key_:String!
    
    
    @IBOutlet weak var log_lable_: UILabel!
    
    
    ///
    override func viewDidLoad() {
        super.viewDidLoad()
        
        public_key_ = GetStringFromSampleFile("PublicKey")
        private_key_  = GetStringFromSampleFile("PrivateKey")
        
    }
    
    override func didReceiveMemoryWarning() {
        super.didReceiveMemoryWarning()
    }
    
    
    
    
    
    @IBAction func large_test_clicked(_ sender: AnyObject) {
        let button:UIButton = sender as! UIButton;
        
        button.isEnabled = false;
        
        let data = Data()
        
        
        let out = PMNSrpClient.expandHash(data)
        
//        let pgp:OpenPGP = OpenPGP();
//        pgp.SetupKeys(private_key_, pubKey: public_key_, pass: "123", error:nil)
//        
//        let test_msg:String = GetStringFromSampleFile("large_test_msg")
//        
//        let count:Int32 = 50;
//        let startTime:CFTimeInterval  = CACurrentMediaTime();
//        for var i:Int32 = 0; i < count; ++i {
//            let s:CFTimeInterval = CACurrentMediaTime();
//            
//            let pgp_msg:String = pgp.encrypt_message(test_msg, error:nil)
//            
//            let e:CFTimeInterval = CACurrentMediaTime();
//            
//            
//            var writeError: NSError?
//            var errors: NSErrorPointer = nil
//            let cleartext:String = pgp.decrypt_message(pgp_msg, error:&writeError)
//            if cleartext == "" {
//                
//                
//            }
//            
//            if cleartext == test_msg  {
//                //println("OK");
//            }
//            else
//            {
//                println("error");
//            }
//        }
//        
//        let endTime:CFTimeInterval  = CACurrentMediaTime();
//        let total = (endTime - startTime);
//        let cot:Double = Double( count )
//        let avg:Double = (endTime - startTime)/cot;
//        log_lable_.text = NSString(format: "%d Times(ENC->DEC) --- Total Runtime: %g s --- Avg %g s", count, total , avg) as String
//        button.enabled = true;
    }
    
    @IBAction func tiny_test_clicked(_ sender: AnyObject) {
        let button:UIButton = sender as! UIButton;
        
        button.isEnabled = false;
        
//        let pgp:OpenPGP = OpenPGP();
//        pgp.SetupKeys(private_key_, pubKey: public_key_, pass: "123", error: nil)
//        
//        let test_msg:String = GetStringFromSampleFile("tiny_test_msg");
//        
//        let count:Int = 50
//        let startTime:CFTimeInterval  = CACurrentMediaTime()
//        for var i:Int = 0; i < count; ++i {
//            let s:CFTimeInterval = CACurrentMediaTime();
//            let pgp_msg:String = pgp.encrypt_message(test_msg, error:nil)
//            let e:CFTimeInterval = CACurrentMediaTime();
//            let cleartext:String = pgp.decrypt_message(pgp_msg, error:nil)
//            if cleartext == test_msg  {
//                println("OK");
//            }
//            else
//            {
//                println("error");
//            }
//        }
//        
//        let endTime:CFTimeInterval  = CACurrentMediaTime();
//        let total = (endTime - startTime);
//        let cot:Double = Double( count )
//        let avg:Double = (endTime - startTime)/cot;
//        log_lable_.text = NSString(format: "%d Times(ENC->DEC) --- Total Runtime: %g s --- Avg %g s", count, total , avg) as String;
//        button.enabled = true;
    }
    @IBAction func other_test_clicked(_ sender: AnyObject) {
        let button:UIButton = sender as! UIButton;
        
               
        button.isEnabled = false;
        
//        public_key_ = GetStringFromSampleFile("PublicKey")
//        
//        var test_private_key:String = GetStringFromSampleFile("pgp_tool_private_key")
//        let pgp:OpenPGP = OpenPGP()
//        pgp.SetupKeys(test_private_key, pubKey: public_key_, pass: "123", error:nil)
//        
//        
//        
//      //  pgp.Test_2();
//        
        
        button.isEnabled = true;
    }
    
    @IBAction func generate_new_key_clicked(_ sender: AnyObject) {
        
 //       let button:UIButton = sender as! UIButton;
 //       button.isEnabled = false;
        
//        let openpgp = PMNOpenPgp.createInstance()
        
//        let count:Int = 10
//        let startTime:CFTimeInterval  = CACurrentMediaTime()
//        for i:Int in 0 ..< count += 1 {
//            openpgp?.generateKey("feng", domain: "protonmail.com", passphrase: "123", bits: 4096)
 //       }
        
 //       let endTime:CFTimeInterval  = CACurrentMediaTime();
 //       let total = (endTime - startTime);
 //       let cot:Double = Double( count )
//        let avg:Double = (endTime - startTime)/cot;
//        log_lable_.text = NSString(format: "%d Times(ENC->DEC) --- Total Runtime: %g s --- Avg %g s", count, total , avg) as String;
//        button.isEnabled = true;
        
    }
    
    
    
    
}

