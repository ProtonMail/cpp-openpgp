//
//  ViewController.swift
//  OSX_Test
//
//  Created by Yanfeng Zhang on 3/2/15.
//  Copyright (c) 2015 Yanfeng Zhang. All rights reserved.
//

import Cocoa


class ViewController: NSViewController {
    
    @IBOutlet weak var labelDisplay: NSTextField!
    override func viewDidLoad() {
        super.viewDidLoad()
        // Do any additional setup after loading the view.
    }
    
    @IBOutlet weak var test_change_pwd: NSButton!
    @IBOutlet weak var vcard_write_test: NSButton!
    
    @IBAction func test_change_pwd_clicked(_ sender: AnyObject) {
        //let pgp:OpenPGP = OpenPGP()
        //        let location = "testpub.txt"
        //        let location_1 = "testprivat.txt"
        //        let fileContent = NSString(contentsOfFile: location, encoding: NSUTF8StringEncoding, error: nil) as! String
        //        let fileContent_1 = NSString(contentsOfFile: location_1, encoding: NSUTF8StringEncoding, error: nil) as! String
        //
        //        let value = pgp.SetupKeys(fileContent_1, pubKey: fileContent, pass: "321", error:nil)
        //        var keys = pgp.update_key_password("123", new_pwd:"321", error: nil)
        
    }
    @IBAction func test_new_key(_ sender: AnyObject) {
        if  let newKey = PMNOpenPgp.createInstance()?.generateKey("feng", domain: "protonmail.com", passphrase: "123", bits: 2048) {
            let privateKey = newKey.privateKey
            print(privateKey);
            NSLog(newKey.publicKey)
            NSLog(newKey.privateKey)
            
            
        } else {
            
        }
    }
    @IBAction func test_import_clicked(_ sender: AnyObject) {
        //        let pgp:OpenPGP = OpenPGP();
        //        //pgp.SetupKeys("", pubKey: public_key_, pass: "123", error: nil)
        //
        //        let testStr : String = "-----BEGIN PGP MESSAGE-----\nVersion: OpenPGP.js v0.10.1-IE\nComment: http://openpgpjs.org\n\nww0ECQMIina34sp8Nlpg0sAbAc/x6pR8h57OJv9pklLuEc/aH5lFT9OpWS+N\n7oPaJCGK1f3aQV7g5V5INlUvwICeDiSkDMo+hHGtFgDFEwgNiMDc7wAtod1U\nZ5PTHegr8KWWmBiDIYuPVFJH8mALVcQen9MI1xFSYO8RvSxM/P6dJPzrVZQK\noIRW98dxMjJqMWW9HgqWCej6TRDua65r/X7Ucco9tWpwzmQCnvJLqpcYYrEk\ngcGyXsp3RvISG6pWh8ZFemeO6yoqnphYmcAa/i4h4CiMqKDDJuOg4UdpW46U\nGoNSV+C4hz5ymRDj\n=hUe3\n-----END PGP MESSAGE-----"
        //
        //        pgp.decrypt_message_aes(testStr, pwd: "123", error: nil)
        //
        //        let test_message = "this is a test message";
        //        let enc_msg = pgp.encrypt_message_aes(test_message, pwd: "123", error: nil)
        //        NSLog(enc_msg)
        //        let un_enc_msg = pgp.decrypt_message_aes(enc_msg, pwd: "123", error: nil)
        //        NSLog(un_enc_msg)
        //
        //
        //        let location = "testpub.txt"
        //
        //        let location_1 = "testprivat.txt"
        //
        //        let fileContent = NSString(contentsOfFile: location, encoding: NSUTF8StringEncoding, error: nil) as! String
        //        let fileContent_1 = NSString(contentsOfFile: location_1, encoding: NSUTF8StringEncoding, error: nil) as! String
        //
        //        let PublicKey = "-----BEGIN PGP PUBLIC KEY BLOCK-----\nVersion: OpenPGP.js v0.7.1\nComment: http://openpgpjs.org\n\nxsBNBFSjdRkBB/9slBPGNrHAMbYT71AnxF4a0W/fcrzCP27yd1nte+iUKGyh\nyux3xGQRIHrwB9zyYBPFORXXwaQIA3YDH73YnE0FPfjh+fBWENWXKBkOVx1R\nefPTytGIyATFtLvmN1D65WkvnIfBdcOc7FWj6N4w5yOajpL3u/46Pe73ypic\nhe10XuwO4198q/8YamGpTFgQVj4H7QbtuIxoV+umIAf96p9PCMAxipF+piao\nD8LYWDUCK/wr1tSXIkNKL+ZCyuCYyIAnOli7xgIlKNCWvC8csuJEYcZlmf42\n/iHyrWeusyumLeBPhRABikE2ePSo+XI7LznD/CIrLhEk6RJT31+JR0NlABEB\nAAHNBlVzZXJJRMLAcgQQAQgAJgUCVKN1JAYLCQgHAwIJEH0tU95Lz7QEBBUI\nAgoDFgIBAhsDAh4BAAAXCgf8CsNCB0tKdLrwGe+dDLTGGdgyYr33Jz6GVta6\nJMl4rccf5T8QiRPkOIWITITpi5maxrn1w7yOUI3xkqCLCEO9vqLhIRr1/aBq\nvVUI+0L7goJoVrx6ynSR1KNNHM/hkttA+t1t894qgug6hooUfxtFWU8KesKK\ngdMFOxst3ODTeZxzO6xmiaf9Mof/y1M5y1fsKuUH57AJRzkJYviZmpEWMAxI\nmmiCPv/iMRUeR7hX9+spG2O9A0Ny46g89T59Wkerggu6/ulgX0O6MAhsuBY3\n+10TgajGyub5oJTLKVDY/nlVvmaEA+4IthepIQs+L3380oQz3GEtr/UfB1PB\nD/VfTM7ATQRUo3UkAQf/dcKxn9bt+fDMxuQT6sxSWjX4ptf6W0QbucDA/5Dw\n2vCFvCGakDdsczduFJ23QI7iZHHig5Fyp5M2MV+1DM/EJs9OZxMK6k0I4M4r\niucSf2L2XPv8m2Q5/nn7+gdvH6mO8POsDu766A0fMNhN36eHa5730dahJlIR\nYP+wOunUkQ3wzTPE4MZh878eCvkaeelMTMPNnQu9ONgxVyaO8GG09M0uJCxV\nqQ6PXBMtYSBydrYUscAeHQrreyfECNPobWgXRafTwftk/n9aGIzLViv4zo36\nGwuk7JzC3AF2PANxYus6EACPckwsjpbMVLpIpSvjDGdlYg9BPtNk0Fd4qZt2\nzwARAQABwsBfBBgBCAATBQJUo3UmCRB9LVPeS8+0BAIbDAAAgzcH/1kyh+20\ntcUGMRrT3akfhVv3o4d9C4j0Ja7PQMKwZNiSdFSbQ8ZE9xbR5cKB/Z33emMw\n+54CeJsanj7lOeefRqoHUynpirANguPLmp8SW4Dor4rwSOs4gfO1ttzw7+8M\nIeFG8p8OQ5B+J3+KCUdiuB+6zdxGW3rIfA9OAPYAObQUJ7quS/lmoNrOzKVm\nJWa7x4f9cS2Wls/vt/jeEn2j0x/GqN0KI8P2PjixiBY5Ogf6FRHvWWUD4SYx\n8YHf6rvFXGHW3tdMRRb24miP0UuhbOyUUiQm1xNIe2fJ+IUCD9cumgWbGXof\nGjz3pBuLbZus9/waqlaZWpyEUl5bKsqeifA=\n=LhM4\n-----END PGP PUBLIC KEY BLOCK-----";
        //
        //
        //        let PrivateKey = "-----BEGIN PGP PRIVATE KEY BLOCK-----\r\nVersion: OpenPGP.js v0.9.0\r\nComment: http://openpgpjs.org\r\n\r\n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\nPPekG4ttm6z3/BqqVplanIRSXlsqyp6J8A==\r\n=Pyb1\r\n-----END PGP PRIVATE KEY BLOCK-----\r\n";
        //        pgp.SetupKeys(fileContent_1, pubKey: fileContent, pass: "123", error:nil)
        //
        //        pgp.Test_Privatekey(PrivateKey, pass: "123");
    }
    
    @IBAction func test_aes_clicked(_ sender: AnyObject) {
        
        //        let pgp:OpenPGP = OpenPGP();
        //
        //        let test_file = "aestest.txt"
        //
        //        let testStr = NSString(contentsOfFile: test_file, encoding: NSUTF8StringEncoding, error: nil) as! String
        //
        //
        //        //let testStr : String = "-----BEGIN PGP MESSAGE-----\nVersion: OpenPGP.js v0.10.1-IE\nComment: http://openpgpjs.org\n\nww0ECQMIina34sp8Nlpg0sAbAc/x6pR8h57OJv9pklLuEc/aH5lFT9OpWS+N\n7oPaJCGK1f3aQV7g5V5INlUvwICeDiSkDMo+hHGtFgDFEwgNiMDc7wAtod1U\nZ5PTHegr8KWWmBiDIYuPVFJH8mALVcQen9MI1xFSYO8RvSxM/P6dJPzrVZQK\noIRW98dxMjJqMWW9HgqWCej6TRDua65r/X7Ucco9tWpwzmQCnvJLqpcYYrEk\ngcGyXsp3RvISG6pWh8ZFemeO6yoqnphYmcAa/i4h4CiMqKDDJuOg4UdpW46U\nGoNSV+C4hz5ymRDj\n=hUe3\n-----END PGP MESSAGE-----"
        //
        //        let message = pgp.decrypt_message_aes(testStr, pwd: "123", error: nil)
        //        if(message == "<div>lajflkjasklfjlksdfkl</div><div><br></div><div>Sent from iPhone <a href=\"https://protonmail.ch\">ProtonMail</a>, encrypted email based in Switzerland.<br></div>")
        //        {
        //            NSLog("OK")
        //        }
        //
        //        let test_message = "this is a test message";
        //        let enc_msg = pgp.encrypt_message_aes(test_message, pwd: "123", error: nil)
        //        //NSLog(enc_msg)
        //        let un_enc_msg = pgp.decrypt_message_aes(enc_msg, pwd: "123", error: nil)
        //        //NSLog(un_enc_msg)
        //        if(test_message == un_enc_msg)
        //        {
        //            NSLog("OK")
        //        }
        //
        //        let test_keys = pgp.encrypt_message_aes(test_message, pwd: "123", error: nil)
        //        let data_key = test_keys.dataUsingEncoding(NSUTF8StringEncoding)
        //        let symSession = pgp.getSymmetricSessionKey(data_key, password: "123", error: nil)
        //
        //        let newSessionKeyPackage = pgp.getNewSymmetricKeyPackage(symSession, password: "1234", error: nil)
        //
        //        let out = pgp.decrypt_message_aes(newSessionKeyPackage, data: data_key, pwd: "1234", error: nil)
        //
        //        var strout = NSString(data: out, encoding:NSUTF8StringEncoding)
        
    }
    @IBAction func EncryptMailboxPWD(_ sender: AnyObject) {
        
        //        let pgp:OpenPGP = OpenPGP();
        //
        //        let v = pgp.encrypt_mailbox_pwd("thisisatestmailbox", slat: "4428c82a118a2dc76f53dab507d3b1d69850ebb9")
        //
        //        let out = pgp.decrypt_mailbox_pwd(v, slat: "4428c82a118a2dc76f53dab507d3b1d69850ebb9")
        //
        //        println(out);
    }
    
    @IBAction func test_bad_message(_ sender: AnyObject) {
        
        //        let location = "publickey.txt"
        //        let location_1 = "privatekey.txt"
        //        let location_2 = "bad_feng_email_fb.txt"
        //        let location_3 = "bad_feng_email_tool.txt"
        //        let location_4 = "bad_feng_email_emoji.txt"
        //        let bad_location_1 = bad_fengt_zhj4478_message.txt"
        //
        //        let fengtPublicKeyLocation = "fengt_publickey.txt"
        //        let fengtPrivateKeyLocation = "fengt_privatekey.txt"
        //
        //        let fileContent = NSString(contentsOfFile: location, encoding: NSUTF8StringEncoding, error: nil) as! String
        //        let fileContent_1 = NSString(contentsOfFile: location_1, encoding: NSUTF8StringEncoding, error: nil) as! String
        //        let fileContent_2 = NSString(contentsOfFile: location_2, encoding: NSUTF8StringEncoding, error: nil) as! String
        //        let fileContent_3 = NSString(contentsOfFile: location_3, encoding: NSUTF8StringEncoding, error: nil) as! String
        //        let fileContent_4 = NSString(contentsOfFile: location_4, encoding: NSUTF8StringEncoding, error: nil) as! String
        //
        //        let bad_file_1 = NSString(contentsOfFile: bad_location_1, encoding: NSUTF8StringEncoding, error: nil) as! String
        //
        //        let fengtPublickey = NSString(contentsOfFile: fengtPublicKeyLocation, encoding: NSUTF8StringEncoding, error: nil) as! String
        //        let fengtPrivatekey = NSString(contentsOfFile: fengtPrivateKeyLocation, encoding: NSUTF8StringEncoding, error: nil) as! String
        //
        //        var pgp:OpenPGP = OpenPGP()
        //        let value = pgp.SetupKeys(fengtPrivatekey, pubKey: fengtPublickey, pass: "123", error:nil)
        //        let enc_m = pgp.encrypt_message("test", error: nil)
        //        let asfsdfa = pgp.decrypt_message(enc_m, error: nil)
        //        let  keyString : String = "c1c04c038eac9f302e252bc3010800bba534aedfeb1f72ab4930e2f1f508c96a0cc44ce8fc975f4f185f38d3b712dd7a0f124e6447d7d300752b11db8717385d560867e5bf6b68592d7b4cacca1f633083928dbf7d93ea7eebb993949ddefe737e5c365cd539afece7a5a27af182b229ca18e522c1d8d16d241d91bb38c847250c134d6bddd28b8c8db971015fc11c18f46e74c0e7bed6ac5ace05e445eea3660518b9c781fb24c312d3eac7c96761b4579de0d8da8a6363f1a53716a6aaeeca535026c1552362d90d80c977414a257a0d4b8172194557018b1bdd5b20ae715497487689e53761366d92607343b379246487759357b9b4792fd85fc2ce18477de75a3e4837f78cda1c0cf4b8299f92";
        //        let dataString : String = "d259018f44a04a1b5bee3d567b197278ce4d94d5b3c958e422150f7edb481bd648ee1b08d7718283866eeb1dc7028c1cd1b315adf5354b5e98be7ba8a9e5acd454f004462ed543136a8506e0a9382ff9652bfc7c186288cce0b420";
        //        pgp.decrypt_attachment(keyString.dataFromHexadecimalString()!, data: dataString.dataFromHexadecimalString()!, error: nil)
        //
        //        var bad_file_1_check = pgp.decrypt_message(bad_file_1, error: nil)
        //
        //        pgp = OpenPGP()
        //        let o_value = pgp.SetupKeys(fileContent_1, pubKey: fileContent, pass: "Jiao2Jian", error:nil)
        //        let o_enc_m = pgp.encrypt_message("test", error: nil)
        //        let o_asfsdfa = pgp.decrypt_message(enc_m, error: nil)
        //        let o_dec_m = pgp.decrypt_message(fileContent_2, error: nil)
        //        println(o_dec_m);
        //        let o_dec_m2 = pgp.decrypt_message(fileContent_3, error: nil)
        //        println(o_dec_m2);
        //        let o_dec_4 = pgp.decrypt_message(fileContent_4, error: nil)
        //        println(o_dec_4);
        //        bad_file_1_check = pgp.decrypt_message(bad_file_1, error: nil)
        //        println(bad_file_1_check);
        
    }
    @IBAction func test_encrypt_decrypt_attachment(_ sender: AnyObject) {
        //        let pgp:OpenPGP = OpenPGP()
        //
        //
        //        let tet_att = "2step.pdf.pgp"
        //
        //        // pgp.Test_Attachment("", data: "")
        //
        //        let pub_location = "publickey.net.txt"
        //        let priv_location = "privatekey.net.txt"
        //        let key_package_location = "keypackage.txt"
        //        let data_package_location = "dataPack.txt"
        //
        //        let pubkey = NSString(contentsOfFile: pub_location, encoding: NSUTF8StringEncoding, error: nil) as! String
        //        let privkey = NSString(contentsOfFile: priv_location, encoding: NSUTF8StringEncoding, error: nil) as! String
        //        let key_package = NSString(contentsOfFile: key_package_location, encoding: NSUTF8StringEncoding, error: nil) as! String
        //        do {
        //            var privateKey = ""
        //            var publicKey = ""
        //
        //            let privatePassphrase = "123"
        //
        //            let bundleInstance : Bundle = Bundle(for: type(of: self))
        //
        //            if let localFile = bundleInstance.path(forResource: "privatekey", ofType: "txt") {
        //                if let content = try? String(contentsOfFile:localFile, encoding:String.Encoding.utf8) {
        //                    privateKey = content
        //                }
        //            }
        //
        //            if let localFile = bundleInstance.path(forResource: "publickey", ofType: "txt") {
        //                if let content = try?  String(contentsOfFile:localFile, encoding:String.Encoding.utf8) {
        //                    publicKey = content
        //                }
        //            }
        //
        //            try pgp.setupKeys(privateKey, pubKey: publicKey, pass: privatePassphrase)
        //
        //            let data_package = try? Data(contentsOf: URL(fileURLWithPath: tet_att))
        //            let decrypted_data = try pgp.decrypt_attachment(data_package, data: data_package)
        //
        //            try? decrypted_data.write(to: URL(fileURLWithPath: "2step.pdf"), options: [])
        //
        //        } catch let ex as NSError {
        //            print(ex)
        //        }
        //
        
        
        //
        //        let value = pgp.SetupKeys(privkey, pubKey: pubkey, pass: "123", error:nil)
        //
        //
        //
        //        let armored_key_package_location = "new_att_key.txt"
        //        let armored_data_package_location = "new_att_data.txt"
        //        let armored_key_package = NSString(contentsOfFile: armored_key_package_location, encoding: NSUTF8StringEncoding, error: nil) as! String
        //        let armored_data_package = NSString(contentsOfFile: armored_data_package_location, encoding: NSUTF8StringEncoding, error: nil) as! String
        //  let decrypted_data = pgp.decrypt_attachment_armored(armored_key_package, data: armored_data_package, error:nil)
        //        decrypted_data.writeToFile("new_unencrypted.png", atomically: false)
        //
        //
        //
        //        let data = pgp.Test_Attachment(key_package, data: data_package)
        //
        //        data.writeToFile("1.png", atomically: false)
        //
        //        let un_encrypt_attachment = "2.png"
        //        let un_encrypt_attachment_data_package = NSData(contentsOfFile: un_encrypt_attachment)
        //
        //        //println(un_encrypt_attachment_data_package)
        //        pgp.encrypt_attachment(un_encrypt_attachment_data_package, fileNam:"", pub_key: pubkey, error: nil)
        //        let dictOut = pgp.encrypt_attachments(un_encrypt_attachment_data_package, fileNam:"", pub_keys: ["zhj4478@protonmail.com" : pubkey], error: nil)
        //
        //        //        let key = dictOut["zhj4478@protonmail.com"] as! String
        //        //        let d = dictOut["DataPacket"] as! String
        //        //
        //        //        let test_data = pgp.decrypt_attachment_armored(key, data: d, error:nil)
        //        //        test_data.writeToFile("3.png", atomically: false)
        //
        //
        //        println("Done");
    }
    
    @IBAction func large_attachment_testing(_ sender: AnyObject) {
        
        //        let pgp:OpenPGP = OpenPGP()
        //
        //        let pub_location = "publickey.net.txt"
        //        let priv_location = "privatekey.net.txt"
        //        let key_package_location = "keypackage.txt"
        //        let data_package_location = "dataPack.txt"
        //
        //        let pubkey = NSString(contentsOfFile: pub_location, encoding: NSUTF8StringEncoding, error: nil) as! String
        //        let privkey = NSString(contentsOfFile: priv_location, encoding: NSUTF8StringEncoding, error: nil) as! String
        //
        //        let checkOne = pgp.CheckPassphrase(privkey, pass: "123", error: nil)
        //
        //        let checkTwo = pgp.CheckPassphrase(privkey, pass: "1231", error: nil)
        //
        //        let checkThree = pgp.CheckPassphrase(privkey, pass: "", error: nil)
        //
        //
        //        let key_package = NSString(contentsOfFile: key_package_location, encoding: NSUTF8StringEncoding, error: nil) as! String
        //        let data_package = NSString(contentsOfFile: data_package_location, encoding: NSUTF8StringEncoding, error: nil) as! String
        //
        //        let value = pgp.SetupKeys(privkey, pubKey: pubkey, pass: "123", error:nil)
        //
        //
        //
        //        let Start:CFTimeInterval  = CACurrentMediaTime();
        //        let StartEncryptTime:CFTimeInterval  = CACurrentMediaTime();
        //
        //        let un_encrypt_attachment = "19691487.jpg"
        //        let un_encrypt_attachment_data_package = NSData(contentsOfFile: un_encrypt_attachment)
        //
        //        let LoadFile:CFTimeInterval  = CACurrentMediaTime()
        //
        //        let dictOut = pgp.encrypt_attachments(un_encrypt_attachment_data_package, fileNam: "", pub_keys: ["zhj4478@protonmail.com" : pubkey], error: nil)
        //
        //        let EncryptTime:CFTimeInterval  = CACurrentMediaTime()
        //
        //        let key = dictOut["zhj4478@protonmail.com"] as! NSData
        //        let d = dictOut["DataPacket"] as! NSData
        //
        //        let TransforTime:CFTimeInterval  = CACurrentMediaTime();
        //
        //
        //        let sessenKey = pgp.getPublicKeySessionKey(key, error: nil)
        //        let newSessionKey = pgp.getNewSymmetricKeyPackage(sessenKey, password: "123", error: nil)
        //        //let newSessionKey = pgp.getNewPublicKeyPackage(sessenKey, pub_key: pubkey, error: nil)
        //
        //        //pgp.decrypt_attachment(<#keyPackage: NSData!#>, data: <#NSData!#>, error: <#NSErrorPointer#>)
        //        let test_data = pgp.decrypt_attachment(newSessionKey, data: d, error:nil)
        //
        //        let DecryptTime:CFTimeInterval  = CACurrentMediaTime();
        //
        //        test_data.writeToFile("img_0147.png.bak", atomically: false)
        //
        //        let WriteTime:CFTimeInterval  = CACurrentMediaTime();
        //
        //
        //
        //        let total = (WriteTime - Start);
        //
        //        let encrypt = (EncryptTime - LoadFile);
        //        let decrypt = (DecryptTime - TransforTime);
        //
        //        self.labelDisplay.stringValue = NSString(format: "Total Runtime: %g s --- Enrypt: %g s ---- Decrypt %g s", total, encrypt , decrypt) as String;
        //
        //
        //        let test_string_test = "adlfjasljflkasjfjskdlfjkjfljskldfjlkasjfljsdklfjalsfjlksdjfklsjdf"
        //        let test_data_test = test_string_test.dataUsingEncoding(NSUTF8StringEncoding)
        //        let test_data_test_out = pgp.encrypt_attachments(test_data_test, fileNam: "", pub_keys: ["zhj4478@protonmail.com" : pubkey], error: nil)
        //
        //
        //        let key_a = test_data_test_out["zhj4478@protonmail.com"] as! NSData
        //        let d_a = test_data_test_out["DataPacket"] as! NSData
    }
    
    
    @IBAction func multiple_keys_encrypt_decrypt(_ sender: NSButton) {
        //        if let localFile = NSBundle.mainBundle().pathForResource("feng_addresses", ofType: "geojson") {
        //            if let content = String(contentsOfFile:localFile, encoding:NSUTF8StringEncoding, error: nil) {
        //
        //                let pgp:OpenPGP = OpenPGP()
        //
        //                var parseError: NSError?
        //                let parsedObject: AnyObject? = NSJSONSerialization.JSONObjectWithData(content.dataUsingEncoding(NSUTF8StringEncoding, allowLossyConversion: false)!, options: NSJSONReadingOptions.AllowFragments, error: nil)
        //
        //                if let topApps = parsedObject as? NSDictionary {
        //                    if let feed = topApps["User"] as? NSDictionary {
        //                        if let addresses = feed["Addresses"] as? NSArray {
        //                            for address in addresses {
        //                                if let address = address as? NSDictionary {
        //                                    if let keys = address["Keys"] as? NSArray {
        //                                        for key in keys {
        //                                            if let key = key as? NSDictionary {
        //                                                print(key);
        //                                                if let priv_key = key["PrivateKey"] as? String {
        //                                                    print(priv_key);
        //                                                    pgp.AddKeys(priv_key, pubKey: "", error: nil)
        //                                                }
        //                                            }
        //                                        }
        //                                    }
        //                                }
        //                            }
        //                        }
        //                    }
        //                }
        //
        //                let test_body = "test_new_key.txt"
        //
        //                let test = NSString(contentsOfFile: test_body, encoding: NSUTF8StringEncoding, error: nil) as! String
        //
        //
        //                let out = pgp.decrypt_message(test, error: nil)
        //
        //            }
        //        }
    }
    @IBAction func new_jni_test(_ sender: AnyObject) {
//        if let openPgp : PMNOpenPgp = PMNOpenPgp.createInstance() {
//            //openPgp.encryptHashCbc("asdfsdfasdfsaf", "")
//        }
        let expected = "$2a$06$DCq7YPn5Rq63x1Lad4cll.TV4S6ytwfsfvkgY8jIucDrjc8deX1s."
        let hashed = PMNBCryptHash.hashString("", salt: "$2a$06$DCq7YPn5Rq63x1Lad4cll.")
        if expected == hashed {
            NSLog("expected == hashed")
        }
        //        if let openPgp : PMNOpenPgp = PMNOpenPgp.createInstance() {
        //            //openPgp.encryptHashCbc("asdfsdfasdfsaf", "")
        //        }
        //
        let data = Data()
        //
        //
        //let out = PMNSrpClient.expandHash(data)
        
//        
//       let data = Data()
////
////
//        //let out = PMNSrpClient.expandHash(data)
//
//        PMNSrpClient.generateProofs(2048, modulusRepr: data, serverEphemeralRepr: data, hashedPasswordRepr: data)
//        PMNSrpClient.generateVerifier(2048, modulusRepr: data, hashedPasswordRepr: data)
        
        
        //        if let localFile = NSBundle.mainBundle().pathForResource("feng_addresses", ofType: "geojson") {
        //            if let content = String(contentsOfFile:localFile, encoding:NSUTF8StringEncoding, error: nil) {
        //
        //                let openPgp : PMNOpenPgp = PMNOpenPgp.createInstance()!
        //
        //                var parseError: NSError?
        //                let parsedObject: AnyObject? = NSJSONSerialization.JSONObjectWithData(content.dataUsingEncoding(NSUTF8StringEncoding, allowLossyConversion: false)!, options: NSJSONReadingOptions.AllowFragments, error: nil)
        //
        //                if let topApps = parsedObject as? NSDictionary {
        //                    if let feed = topApps["User"] as? NSDictionary {
        //                        if let addresses = feed["Addresses"] as? NSArray {
        //                            for address in addresses {
        //                                if let address = address as? NSDictionary {
        //                                    let addressID = address["ID"] as! String;
        //                                    let addressName = address["Email"] as! String;
        //                                    var address_keys : [PMNOpenPgpKey] = [PMNOpenPgpKey]()
        //                                    if let keys = address["Keys"] as? NSArray {
        //                                        for key in keys {
        //                                            if let key = key as? NSDictionary {
        //                                                let keyo = PMNOpenPgpKey(publicKey: key["PublicKey"] as! String, privateKey: key["PrivateKey"] as! String);
        //                                                address_keys.append(keyo)
        //                                            }
        //                                        }
        //                                    }
        //                                    let newAddress = PMNAddress(addressId: addressID, addressName: addressName, keys: address_keys);
        //                                    openPgp.addAddress(newAddress);
        //                                }
        //                            }
        //                        }
        //                    }
        //                }
        //
        //                let test_body = "test_new_key.txt"
        //                let test = NSString(contentsOfFile: test_body, encoding: NSUTF8StringEncoding, error: nil) as! String
        //
        //                for i in 0 ..< 200 {
        //                    print(" start \(i)");
        //                    let tmp_out = openPgp.decryptMessage(test, passphras: "123");
        //                    println(" end \(i)");
        //                }
        //
        //                openPgp.cleanAddresses()
        //                if let topApps = parsedObject as? NSDictionary {
        //                    if let feed = topApps["User"] as? NSDictionary {
        //                        if let addresses = feed["Addresses"] as? NSArray {
        //                            for address in addresses {
        //                                if let address = address as? NSDictionary {
        //                                    let addressID = address["ID"] as! String;
        //                                    let addressName = address["Email"] as! String;
        //                                    var address_keys : [PMNOpenPgpKey] = [PMNOpenPgpKey]()
        //                                    if let keys = address["Keys"] as? NSArray {
        //                                        for key in keys {
        //                                            if let key = key as? NSDictionary {
        //                                                let keyo = PMNOpenPgpKey(publicKey: key["PublicKey"] as! String, privateKey: key["PrivateKey"] as! String);
        //                                                address_keys.append(keyo)
        //                                            }
        //                                        }
        //                                    }
        //                                    let newAddress = PMNAddress(addressId: addressID, addressName: addressName, keys: address_keys);
        //                                    openPgp.addAddress(newAddress);
        //                                }
        //                            }
        //                        }
        //                    }
        //                }
        //
        //                for i in 0 ..< 200 {
        //                    print(" start \(i)");
        //                    let tmp_out = openPgp.decryptMessage(test, passphras: "123");
        //                    println(" end \(i)");
        //                }
        //
        //            }
        //        }
        
        
        //        let keys = [ PMNOpenPgpKey(publicKey: "publickey_1", privateKey: "privatekey_1"), PMNOpenPgpKey(publicKey: "publickey_2", privateKey: "privatekey_2"),PMNOpenPgpKey(publicKey: "publickey_3", privateKey: "privatekey_3"),PMNOpenPgpKey(publicKey: "publickey_4", privateKey: "privatekey_4") ]
        //
        //        var address = PMNAddress(addressId: "1", addressName: "feng@protonmail.blue", keys: keys)
        
        //        let pgp:PMNOpenPgp = PMNOpenPgp.createInstance()!
        //
        ////
        ////        SwiftTryCatch.tryBlock({ () -> Void in
        ////            pgp.throwAnException()
        ////        }, catchBlock: { (error) -> Void in
        ////            println("\(error.description)")
        ////        }) { () -> Void in
        ////            //
        ////        }
        ////
        //
        //        let newKey = pgp.generateKey("feng_test", domain: "protonmail.com", passphrase: "123");
        //
        //         print(newKey.publicKey)
        //         print(newKey.privateKey)
        //        //                    String test_encrypt = OpenPGP.EncryptMailboxPWD("thisisatestmailbox", "4428c82a118a2dc76f53dab507d3b1d69850ebb9");
        //        //                    String test_plain_text = OpenPGP.DecryptMailboxPWD(test_encrypt, "4428c82a118a2dc76f53dab507d3b1d69850ebb9");
        //        //let en_pwd = pgp?.encryptMailboxPwd("thisisatestmailbox", salt: "4428c82a118a2dc76f53dab507d3b1d69850ebb9");
        //        //let plain_pwd = pgp?.decryptMailboxPwd(en_pwd!, salt: "4428c82a118a2dc76f53dab507d3b1d69850ebb9");
        //
        //
        //        let openpgp_old = OpenPGP();
        //        let en_pwd = pgp.encryptMailboxPwd("thisisatestmailbox", salt: "4428c82a118a2dc76f53dab507d3b1d69850ebb9");
        //        let plain_pwd = pgp.decryptMailboxPwd(en_pwd, salt: "4428c82a118a2dc76f53dab507d3b1d69850ebb9");
        ////        let en_pwd_old = openpgp_old.encrypt_mailbox_pwd("thisisatestmailbox", slat: "4428c82a118a2dc76f53dab507d3b1d69850ebb9" );
        ////
        ////         let plain_pwd_old = openpgp_old.decrypt_mailbox_pwd(en_pwd_old!, slat: "4428c82a118a2dc76f53dab507d3b1d69850ebb9");
        //        print("");
    }
    @IBAction func test_vcard_action(_ sender: NSButtonCell) {
        
        let str  : String =
            "BEGIN:VCARD\r\n" +
                "VERSION:3.0\r\n" +
                "N:1\\;&\\;1\r\n" +
                "FN:1 & 1\r\n" +
                "EMAIL;TYPE=Email:test@example.com\r\n" +
                "EMAIL;TYPE=Home:test1@example.com\r\n" +
                "EMAIL;TYPE=Work:test3@example.com\r\n" +
        "END:VCARD\r\n"
        
        var vcard = PMNIEzvcard.parseFirst(str)
        assert(vcard != nil)
        var fn = vcard!.getFormattedName()
        assert(fn != nil)
        var name = fn!.getValue()
        assert("1 & 1" == name)
        var sn = vcard!.getStructuredName()
        assert(sn != nil)
        var f = sn!.getFamily()
        assert(f == "1;&;1")
        let ems = vcard!.getEmails()
        assert(ems.count == 3)
        
        let e1 = ems[0]
        assert(e1.getTypes() == ["Email"])
        assert(e1.getValue() == "test@example.com")
        let e2 = ems[1]
        assert(e2.getTypes() == ["Home"])
        assert(e2.getValue() == "test1@example.com")
        let e3 = ems[2]
        assert(e3.getTypes() == ["Work"])
        assert(e3.getValue() == "test3@example.com")
        
        let rfc2426_str : String =
            "BEGIN:vCard\r\n" +
                "VERSION:3.0\r\n" +
                "FN:Frank Dawson\r\n" +
                "ORG:Lotus Development Corporation\r\n" +
                "ADR;TYPE=Work,POSTAL,PARCEL:;;6544 Battleford Drive\r\n" +
                " ;Raleigh;NC;27613-3502;U.S.A.\r\n" +
                "TEL;TYPE=VOICE,MSG,WORK:+1-919-676-9515\r\n" +
                "TEL;TYPE=FAX,WORK:+1-919-676-9564\r\n" +
                "EMAIL;TYPE=INTERNET,PREF:Frank_Dawson@Lotus.com\r\n" +
                "EMAIL;TYPE=INTERNET:fdawson@earthlink.net\r\n" +
                "URL:http://home.earthlink.net/~fdawson\r\n" +
                "END:vCard\r\n" +
                "BEGIN:vCard\r\n" +
                "VERSION:3.0\r\n" +
                "FN:Tim Howes\r\n" +
                "ORG:Netscape Communications Corp.\r\n" +
                "ADR;TYPE=WORK:;;501 E. Middlefield Rd.;Mountain View;\r\n" +
                " CA; 94043;U.S.A.\r\n" +
                "TEL;TYPE=VOICE,MSG,WORK:+1-415-937-3419\r\n" +
                "TEL;TYPE=FAX,WORK:+1-415-528-4164\r\n" +
                "EMAIL;TYPE=INTERNET:howes@netscape.com\r\n" +
        "END:vCard\r\n";
        
        var vcards = PMNIEzvcard.parseAll(rfc2426_str)
        assert(vcards.count == 2)
        let vcardOne = vcards[0]
        var version = vcardOne.getVersion()
        let d = PMNIVCardVersion.vCard30()?.equals(version)
        assert(d!)
        fn = vcardOne.getFormattedName()
        assert(fn != nil)
        name = fn!.getValue()
        assert(name == "Frank Dawson")
        var org = vcardOne.getOrganization();
        assert(org?.getValues()[0] == "Lotus Development Corporation")
        var addresses = vcardOne.getAddresses()
        assert(addresses.count == 1)
        var address = addresses[0]
        assert(address.getStreetAddress() == "6544 Battleford Drive")
        assert(address.getLocality() == "Raleigh")
        assert(address.getRegion() == "NC");
        assert(address.getPostalCode() == "27613-3502");
        assert(address.getCountry() == "U.S.A.")
        assert(address.getTypes() == ["Work","POSTAL","PARCEL"])
        
        var telephones = vcardOne.getTelephoneNumbers()
        assert(telephones.count == 2)
        var tel1 = telephones[0]
        assert(tel1.getTypes() == ["VOICE","MSG","WORK"])
        assert(tel1.getText() == "+1-919-676-9515")
        var tel2 = telephones[1]
        assert(tel2.getTypes() == ["FAX","WORK"])
        assert(tel2.getText() == "+1-919-676-9564")
        
        var emails = vcardOne.getEmails()
        assert(emails.count == 2)
        let email1 = emails[0];
        assert(email1.getTypes() == ["INTERNET","PREF"])
        assert(email1.getValue() == "Frank_Dawson@Lotus.com")
        let email2 = emails[1];
        assert(email2.getTypes() == ["INTERNET"])
        assert(email2.getValue() == "fdawson@earthlink.net")
        let urls = vcardOne.getUrls()
        assert(urls.count == 1)
        let url = urls[0];
        assert(url.getValue() == "http://home.earthlink.net/~fdawson");
    
        let vcardTwo = vcards[1]
        version = vcardTwo.getVersion()
        assert(PMNIVCardVersion.vCard30()!.equals(version))
        fn = vcardTwo.getFormattedName();
        assert(fn != nil)
        assert(fn!.getValue() == "Tim Howes")
        org = vcardTwo.getOrganization()
        assert(org != nil)
        assert(org!.getValues() == ["Netscape Communications Corp."])
        addresses = vcardTwo.getAddresses()
        assert(addresses.count == 1)
        address = addresses[0]
        assert(address.getStreetAddress() == "501 E. Middlefield Rd.")
        assert(address.getLocality() == "Mountain View")
        assert(address.getRegion() == "CA");
        assert(address.getPostalCode() == " 94043")
        assert(address.getCountry() == "U.S.A.")
        assert(address.getTypes() == ["WORK"])
        telephones = vcardTwo.getTelephoneNumbers()
        assert(telephones.count == 2)
        tel1 = telephones[0]
        assert(tel1.getTypes() == ["VOICE","MSG","WORK"])
        assert(tel1.getText() == "+1-415-937-3419")
        tel2 = telephones[1]
        assert(tel2.getTypes() == ["FAX","WORK"])
        assert(tel2.getText() == "+1-415-528-4164")
        emails = vcardTwo.getEmails()
        assert(emails.count == 1)
        var email = emails[0];
        assert(email.getTypes() == ["INTERNET"])
        assert(email.getValue() == "howes@netscape.com");
        
        let str_protonmail_web =
        "BEGIN:VCARD\r\n" +
        "VERSION:3.0\r\n" +
        "N:1\\;&\\;1\r\n" +
        "FN:1 & 1\r\n" +
        "EMAIL;TYPE=Email:test@example.com\r\n" +
        "EMAIL;TYPE=Home:test1@example.com\r\n" +
        "EMAIL;TYPE=Work:test3@example.com\r\n" +
        "TEL;TYPE=Cell:6176767087\r\n" +
        "TEL;TYPE=Fax:6414551782\r\n" +
        "ADR;TYPE=Home:500 King Dr Daly City CA\\, 94080\r\n" +
        "ORG;TYPE=Org:TestOrg\r\n" +
        "TITLE;TYPE=Title:TestTitle\r\n" +
        "NICKNAME:TestNickName\r\n" +
        "BDAY;TYPE=Bday:19841007\r\n" +
        "ITEM1.CUSTOM:TestCustomField1\r\n" +
        "ITEM1.X-ABLABEL:Custom\r\n" +
        "ITEM2.CUSTOM:TestCustomField2\r\n" +
        "ITEM2.X-ABLABEL:Custom\r\n" +
        "ITEM3.CUSTOM:333333\r\n" +
        "ITEM3.X-ABLABEL:Custom\r\n" +
        "NOTE;TYPE=Note:test notes 11\r\n" +
        "END:VCARD\r\n"
        
        vcards = PMNIEzvcard.parseAll(str_protonmail_web)
        assert(vcards.count == 1)
        vcard = vcards[0]
        
        version = vcard!.getVersion()
        let check = PMNIVCardVersion.vCard30()?.equals(version)
        assert(check!)
        
        fn = vcard!.getFormattedName()
        assert(fn != nil)
        name = fn!.getValue()
        assert(name == "1 & 1")
        
        sn = vcard!.getStructuredName()
        assert(sn != nil)
        f = sn!.getFamily()
        assert(f == "1;&;1")
        
        emails = vcard!.getEmails()
        assert(emails.count == 3)
        
        email = emails[0]
        assert(email.getTypes() == ["Email"])
        assert(email.getValue() == "test@example.com")

        email = emails[1]
        assert(email.getTypes() == ["Home"])
        assert(email.getValue() == "test1@example.com")
        
        email = emails[2]
        assert(email.getTypes() == ["Work"])
        assert(email.getValue() == "test3@example.com")
        
        telephones = vcard!.getTelephoneNumbers()
        assert(telephones.count == 2)
        
        var tel = telephones[0]
        assert(tel.getTypes() == ["Cell"])
        assert(tel.getText() == "6176767087")
        tel = telephones[1];
        assert(tel.getTypes() == ["Fax"])
        assert(tel.getText() == "6414551782")
        
        addresses = vcard!.getAddresses()
        assert(addresses.count == 1)
        let addr = addresses[0]
        let pobox = addr.getPoBox()
        assert(pobox == "500 King Dr Daly City CA, 94080")
        
        org = vcard!.getOrganization()
        assert(org!.getValues()[0] == "TestOrg")
        
        let title = vcard!.getTitle()
        assert(title!.getType() == "Title")
        assert(title!.getTitle() == "TestTitle")

        let nickName = vcard?.getNickname()
        assert(nickName!.getType() == "")
        assert(nickName!.getNickname() == "TestNickName")

        let birthday = vcard!.getBirthday()    
        assert(birthday!.getType() == "Bday")
        assert(birthday!.getDate() == "19841007")
        
        let note = vcard!.getNote()
        assert(note!.getType() == "Note")
        assert(note!.getNote() == "test notes 11")
        
        let customs = vcard!.getPMCustoms()
        let custom0 = customs[0];
        assert(custom0.getType() == "")
        assert(custom0.getValue() == "TestCustomField1")
        assert(custom0.getGroup() == "ITEM1")
        
        let custom1 = customs[1];
        assert(custom1.getType() == "")
        assert(custom1.getValue() == "TestCustomField2")
        assert(custom1.getGroup() == "ITEM2")
        
        let custom2 = customs[2];
        assert(custom2.getType() == "")
        assert(custom2.getValue() == "333333")
        assert(custom2.getGroup() == "ITEM3")
    }
    
    @IBAction func vcard_write_test_action(_ sender: Any) {
        
        
        let _  : String =
            "BEGIN:VCARD\r\n" +
                "VERSION:3.0\r\n" +
                "N:1\\;&\\;1\r\n" +
                "FN:1 & 1\r\n" +
                "EMAIL;TYPE=Email:test@example.com\r\n" +
                "EMAIL;TYPE=Home:test1@example.com\r\n" +
                "EMAIL;TYPE=Work:test3@example.com\r\n" +
        "END:VCARD\r\n"
        
        
        let vcard = PMNIVCard.createInstance()!
        vcard.setVersion(PMNIVCardVersion.vCard30())
        let fn = PMNIFormattedName.createInstance("John Doe")
        vcard.setFormattedName(fn)
        let email1 = PMNIEmail.createInstance("Home", email: "feng@protonmail.com")
        vcard.add(email1)
        let email2 = PMNIEmail.createInstance("Work", email: "zh4478@protonmail.com")
        vcard.add(email2)
        _ = PMNIEzvcard.write(vcard)

        
//        VCard::Ptr vcard1 = std::make_shared<VCard>();
//        vcard1->setVersion(VCardVersion::V2_1);
//        vcard1->setFormattedName(std::make_shared<FormattedName>("John Doe"));
//        VCard::Ptr vcard2 = std::make_shared<VCard>();
//        vcard2->setVersion(VCardVersion::V3_0);
//        vcard2->setFormattedName(std::make_shared<FormattedName>("Jane Doe"));
//        VCard::Ptr vcard3 = std::make_shared<VCard>();
//        vcard3->setVersion(VCardVersion::V4_0);
//        vcard3->setFormattedName(std::make_shared<FormattedName>("Janet Doe"));
        
//        auto actual = Ezvcard::write( { vcard1, vcard2, vcard3 })->go();
        
        
//        let vcard = PMNIEzvcard.parseFirst(str)
//        assert(vcard != nil)
//        var fn = vcard!.getFormattedName()
//        assert(fn != nil)
//        var name = fn!.getValue()
//        assert("1 & 1" == name)
//        let sn = vcard!.getStructuredName()
//        assert(sn != nil)
//        let f = sn!.getFamily()
//        assert(f == "1;&;1")
//        let ems = vcard!.getEmails()
//        assert(ems.count == 3)
//        
//        let e1 = ems[0]
//        assert(e1.getTypes() == ["Email"])
//        assert(e1.getValue() == "test@example.com")
//        let e2 = ems[1]
//        assert(e2.getTypes() == ["Home"])
//        assert(e2.getValue() == "test1@example.com")
//        let e3 = ems[2]
//        assert(e3.getTypes() == ["Work"])
//        assert(e3.getValue() == "test3@example.com")
        
    }
}

