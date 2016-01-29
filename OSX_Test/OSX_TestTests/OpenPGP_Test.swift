//
//  OpenPGP_Test.swift
//
//
//  Created by Yanfeng Zhang on 1/13/16.
//
//

import Cocoa
import XCTest

class OpenPGP_Test: XCTestCase {
    
    var privateKey = ""
    var publicKey = ""
    
    let privatePassphrase = "123"
    
    var bundleInstance : NSBundle!;
    
    override func setUp() {
        super.setUp()
        
//        bundleInstance = NSBundle(forClass: self.dynamicType)
//        let filePath = bundleInstance.pathForResource("privatekey", ofType: "txt")
//        XCTAssertNotNil(filePath)
//        
//        if let localFile = bundleInstance.pathForResource("privatekey", ofType: "txt") {
//            if let content = String(contentsOfFile:localFile, encoding:NSUTF8StringEncoding, error: nil) {
//                privateKey = content
//            }
//        }
//        
//        if let localFile = bundleInstance.pathForResource("publickey", ofType: "txt") {
//            if let content = String(contentsOfFile:localFile, encoding:NSUTF8StringEncoding, error: nil) {
//                publicKey = content
//            }
//        }
//        
//        XCTAssertFalse(privateKey.isEmpty, "private is empty");
//        XCTAssertFalse(publicKey.isEmpty, "public is empty");
    }
    
    override func tearDown() {
        // Put teardown code here. This method is called after the invocation of each test method in the class.
        super.tearDown()
    }
    
    func testExample() {
        // This is an example of a functional test case.
        XCTAssert(true, "Pass")
    }
    
    func testPerformanceExample() {
        // This is an example of a performance test case.
        self.measureBlock() {
            // Put the code you want to measure the time of here.
        }
    }
    
    func test_generateNewKey() {
        let openPgp : PMNOpenPgp = PMNOpenPgp.createInstance()!
        
        let newKey = openPgp.generateKey("feng", domain: "protonmail.com", passphrase: "123123")
        XCTAssertNotNil(newKey, "new key can't be nil")
        XCTAssertNotNil(newKey.privateKey)
        XCTAssertNotNil(newKey.publicKey)
        
        let check1 = openPgp.checkPassphrase(newKey.privateKey, passphrase: "")
        XCTAssertTrue(check1 == false, "here should be a wrong pwd")
        let check2 = openPgp.checkPassphrase(newKey.privateKey, passphrase: "123") //ok
        XCTAssertTrue(check2 == false, "here should be a wrong pwd")
        let check3 = openPgp.checkPassphrase(newKey.privateKey, passphrase: "123123")
        XCTAssertTrue(check3 == true, "here should be a right pwd")
        
        let newKey1 = openPgp.updateSinglePassphrase(newKey.privateKey, oldPassphrase: "", newPassphrase: "123")
        XCTAssertTrue(newKey1.isEmpty, "here should be a wrong pwd and return a null new key")
        let newKey2 = openPgp.updateSinglePassphrase(newKey.privateKey, oldPassphrase: "123", newPassphrase: "123")
        XCTAssertTrue(newKey2.isEmpty, "here should be a wrong pwd and return a null new key")
        let updatedPrivateKey = openPgp.updateSinglePassphrase(newKey.privateKey, oldPassphrase: "123123", newPassphrase: "123") //ok
        XCTAssertNotNil(updatedPrivateKey, "here should be a right pwd and return not null value")
        XCTAssertFalse(updatedPrivateKey.isEmpty, "here should be a right pwd and return not empty value")
        
        let check4 = openPgp.checkPassphrase(updatedPrivateKey, passphrase: "")
        XCTAssertFalse(check4, "here should be a wrong pwd")
        let check5 = openPgp.checkPassphrase(updatedPrivateKey, passphrase: "123") //ok
        XCTAssertTrue(check5, "here should be a right pwd")
        let check6 = openPgp.checkPassphrase(updatedPrivateKey, passphrase: "123123")
        XCTAssertFalse(check6, "here should be a wrong pwd")
    }
    
    func test_checkPassword() {
        let openPgp : PMNOpenPgp = PMNOpenPgp.createInstance()!
        
        let isOk = openPgp.checkPassphrase(privateKey, passphrase: privatePassphrase)
        XCTAssertTrue(isOk, "The password not match")
        let check4 = openPgp.checkPassphrase(privateKey, passphrase: "")
        XCTAssertFalse(check4, "The password not match")
        let check5 = openPgp.checkPassphrase(privateKey, passphrase: privatePassphrase)
        XCTAssertTrue(check5, "The password not match")
        let check6 = openPgp.checkPassphrase(privateKey, passphrase: "123123")
        XCTAssertFalse(check6, "The password not match")
    }
    
    func test_encryptMessage() {
//        var plain_text : String = ""
//        if let localFile = bundleInstance.pathForResource("test_plain_message", ofType: "txt") {
//            if let content = String(contentsOfFile:localFile, encoding:NSUTF8StringEncoding, error: nil) {
//                plain_text = content;
//            }
//        }
//        
//        XCTAssertFalse(plain_text.isEmpty, "test file can't be empty");
//        
//        let openPgp : PMNOpenPgp = PMNOpenPgp.createInstance()!
//        var keys : [PMNOpenPgpKey] = [PMNOpenPgpKey]()
//        let key = PMNOpenPgpKey(publicKey: publicKey, privateKey: privateKey)
//        keys.append(PMNOpenPgpKey(publicKey: publicKey, privateKey: privateKey))
//        openPgp.addAddress(PMNAddress(addressId: "1", addressName: "feng@protonmail.ch", keys: keys))
//        
//        for i in 0 ..< 200 {
//            print(" start \(i)");
//            let encryptedText = openPgp.encryptMessage("1", plainText: plain_text)
//            XCTAssertNotNil(encryptedText, "encryptedText can't null")
//            XCTAssertFalse(encryptedText.isEmpty, "cleartext can't empty")
//            
//            let decryptedText = openPgp.decryptMessage(encryptedText, passphras: privatePassphrase)
//            XCTAssertNotNil(encryptedText, "decryptedText can't null")
//            XCTAssertFalse(encryptedText.isEmpty, "decryptedText can't empty")
//            XCTAssertTrue(decryptedText == plain_text, "decryptedText should be same as cleartext")
//            print(" end \(i)");
//        }
        
    }
    
    func test_encryptMessage_multiple_key() {
//        var plain_text : String = ""
//        if let localFile = bundleInstance.pathForResource("feng_mulitiple_test_message", ofType: "txt") {
//            if let content = String(contentsOfFile:localFile, encoding:NSUTF8StringEncoding, error: nil) {
//                plain_text = content
//            }
//        }
//        
//        var multiple_key_json : String = ""
//        if let localFile = bundleInstance.pathForResource("feng_addresses", ofType: "geojson") {
//            if let content = String(contentsOfFile:localFile, encoding:NSUTF8StringEncoding, error: nil) {
//                multiple_key_json = content
//            }
//        }
//        XCTAssertFalse(multiple_key_json.isEmpty, "keys file can't be empty");
//        XCTAssertFalse(plain_text.isEmpty, "test file can't be empty");
//        
//        let openPgp : PMNOpenPgp = PMNOpenPgp.createInstance()!
//        
//        var parseError: NSError?
//        let parsedObject: AnyObject? = NSJSONSerialization.JSONObjectWithData(multiple_key_json.dataUsingEncoding(NSUTF8StringEncoding, allowLossyConversion: false)!, options: NSJSONReadingOptions.AllowFragments, error: nil)
//        
//        if let topApps = parsedObject as? NSDictionary {
//            if let feed = topApps["User"] as? NSDictionary {
//                if let addresses = feed["Addresses"] as? NSArray {
//                    for address in addresses {
//                        if let address = address as? NSDictionary {
//                            let addressID = address["ID"] as! String;
//                            let addressName = address["Email"] as! String;
//                            var address_keys : [PMNOpenPgpKey] = [PMNOpenPgpKey]()
//                            if let keys = address["Keys"] as? NSArray {
//                                for key in keys {
//                                    if let key = key as? NSDictionary {
//                                        let keyo = PMNOpenPgpKey(publicKey: key["PublicKey"] as! String, privateKey: key["PrivateKey"] as! String);
//                                        address_keys.append(keyo)
//                                    }
//                                }
//                            }
//                            let newAddress = PMNAddress(addressId: addressID, addressName: addressName, keys: address_keys);
//                            openPgp.addAddress(newAddress);
//                        }
//                    }
//                }
//            }
//        }
//        
//        for i in 0 ..< 200 {
//            print(" start \(i)");
//            let tmp_out = openPgp.decryptMessage(plain_text, passphras: privatePassphrase);
//            XCTAssertNotNil(tmp_out, "decryptedText can't null");
//            XCTAssertFalse(tmp_out.isEmpty, "decryptedText can't empty");
//            print(" end \(i)");
//        }
    }
    
    func test_encryptMessageAES() {
        let original_text = "<div>lajflkjasklfjlksdfkl</div><div><br></div><div>Sent from iPhone <a href=\"https://protonmail.ch\">ProtonMail</a>, encrypted email based in Switzerland.<br></div>";
        let test_aes_str = "-----BEGIN PGP MESSAGE-----\nVersion: OpenPGP.js v0.10.1-IE\nComment: http://openpgpjs.org\n\nww0ECQMIina34sp8Nlpg0sAbAc/x6pR8h57OJv9pklLuEc/aH5lFT9OpWS+N\n7oPaJCGK1f3aQV7g5V5INlUvwICeDiSkDMo+hHGtFgDFEwgNiMDc7wAtod1U\nZ5PTHegr8KWWmBiDIYuPVFJH8mALVcQen9MI1xFSYO8RvSxM/P6dJPzrVZQK\noIRW98dxMjJqMWW9HgqWCej6TRDua65r/X7Ucco9tWpwzmQCnvJLqpcYYrEk\ngcGyXsp3RvISG6pWh8ZFemeO6yoqnphYmcAa/i4h4CiMqKDDJuOg4UdpW46U\nGoNSV+C4hz5ymRDj\n=hUe3\n-----END PGP MESSAGE-----";
        
        let openPgp : PMNOpenPgp = PMNOpenPgp.createInstance()!
        
        for i in 0 ..< 200 {
            print(" start \(i)");
            let plain_text = openPgp.decryptMessageAes(test_aes_str, password: privatePassphrase)
            XCTAssertTrue(plain_text == original_text, "plain_text should be same as original_text")
            
            let new_enc_msg = openPgp.encryptMessageAes(original_text, password: privatePassphrase)
            XCTAssertNotNil(new_enc_msg, "decryptedText should be same as cleartext")
            
            let new_dec_msg = openPgp.decryptMessageAes(new_enc_msg, password: privatePassphrase)
            XCTAssertNotNil(new_dec_msg, "new_dec_msg should not be null")
            XCTAssertTrue(new_dec_msg == original_text, "new_dec_msg should be same as new_dec_msg")
            print(" end \(i)");
        }
    }
    
    func test_badMsg_emojiOne() {
//        var plain_text : String = ""
//        if let localFile = bundleInstance.pathForResource("feng_bad_msg_emoji_1", ofType: "txt") {
//            if let content = String(contentsOfFile:localFile, encoding:NSUTF8StringEncoding, error: nil) {
//                plain_text = content
//            }
//        }
//        XCTAssertFalse(plain_text.isEmpty, "test file can't be empty");
//        
//        let openPgp : PMNOpenPgp = PMNOpenPgp.createInstance()!
//        var keys : [PMNOpenPgpKey] = [PMNOpenPgpKey]()
//        let key = PMNOpenPgpKey(publicKey: publicKey, privateKey: privateKey)
//        keys.append(PMNOpenPgpKey(publicKey: publicKey, privateKey: privateKey))
//        openPgp.addAddress(PMNAddress(addressId: "1", addressName: "feng@protonmail.ch", keys: keys))
//        
//        for i in 0 ..< 200 {
//            print(" start \(i)");
//            let out = openPgp.decryptMessage(plain_text, passphras: privatePassphrase);
//            XCTAssertNotNil(out, "decrypt out can't be nil");
//            print(" end \(i)");
//        }
    }
    
    func test_badCase() {
        let test_string = "this is a test attachment1111111";
        let keyString = "c1c04c038eac9f302e252bc3010800bba534aedfeb1f72ab4930e2f1f508c96a0cc44ce8fc975f4f185f38d3b712dd7a0f124e6447d7d300752b11db8717385d560867e5bf6b68592d7b4cacca1f633083928dbf7d93ea7eebb993949ddefe737e5c365cd539afece7a5a27af182b229ca18e522c1d8d16d241d91bb38c847250c134d6bddd28b8c8db971015fc11c18f46e74c0e7bed6ac5ace05e445eea3660518b9c781fb24c312d3eac7c96761b4579de0d8da8a6363f1a53716a6aaeeca535026c1552362d90d80c977414a257a0d4b8172194557018b1bdd5b20ae715497487689e53761366d92607343b379246487759357b9b4792fd85fc2ce18477de75a3e4837f78cda1c0cf4b8299f92";
        
        let key_packet = keyString.dataFromHexadecimalString()!
        
        let dataString = "d259018f44a04a1b5bee3d567b197278ce4d94d5b3c958e422150f7edb481bd648ee1b08d7718283866eeb1dc7028c1cd1b315adf5354b5e98be7ba8a9e5acd454f004462ed543136a8506e0a9382ff9652bfc7c186288cce0b420";
        let data_packet = dataString.dataFromHexadecimalString()!
        
        let openPgp : PMNOpenPgp = PMNOpenPgp.createInstance()!
        var keys : [PMNOpenPgpKey] = [PMNOpenPgpKey]()
        let key = PMNOpenPgpKey(publicKey: publicKey, privateKey: privateKey)
        keys.append(PMNOpenPgpKey(publicKey: publicKey, privateKey: privateKey))
        openPgp.addAddress(PMNAddress(addressId: "1", addressName: "feng@protonmail.ch", keys: keys))
        
        let new_out_data = openPgp.decryptAttachment(key_packet, data: data_packet, passphras: privatePassphrase);
        
        XCTAssertNotNil(new_out_data, "DecryptAttachment out data");
        XCTAssertTrue(new_out_data.length > 0);
        let test_out_msg = NSString(data: new_out_data, encoding: NSUTF8StringEncoding)
        
        XCTAssertTrue(test_out_msg == test_string, "test_out_msg should be same as test_string");
    }
    
    func test_encryptSmallAttachment() {
        let test_string = "this is a test attachment1111111";
        let data_in = test_string.dataUsingEncoding(NSUTF8StringEncoding)!
        
        let openPgp : PMNOpenPgp = PMNOpenPgp.createInstance()!
        var keys : [PMNOpenPgpKey] = [PMNOpenPgpKey]()
        let key = PMNOpenPgpKey(publicKey: publicKey, privateKey: privateKey)
        keys.append(PMNOpenPgpKey(publicKey: publicKey, privateKey: privateKey))
        openPgp.addAddress(PMNAddress(addressId: "1", addressName: "feng@protonmail.ch", keys: keys))
        
        for i in 0 ..< 200 {
            print(" start \(i)");
            let encryptPackage = openPgp.encryptAttachment("1", unencryptData: data_in, fileName: "test.txt");
            XCTAssertNotNil(encryptPackage, "");
            XCTAssertNotNil(encryptPackage.keyPackage, "");
            XCTAssertNotNil(encryptPackage.dataPackage, "");
            
            let new_out_data = openPgp.decryptAttachment(encryptPackage.keyPackage, data: encryptPackage.dataPackage, passphras: privatePassphrase);
            XCTAssertNotNil(new_out_data, "DecryptAttachment 1 out not null");
            XCTAssertTrue(new_out_data.length > 0, "out length can't be 0");
            let test_out_msg = NSString(data: new_out_data, encoding: NSUTF8StringEncoding)
            XCTAssertTrue(test_out_msg == test_string, "test_out_msg should be same as test_string");
            
//            let sessionBytes = openPgp.getPublicKeySessionKey(encryptPackage.keyPackage, privateKey: privateKey, passphrase: privatePassphrase);
//            XCTAssertNotNil(sessionBytes, "getPublicKeySessionKey can't be nil");
//            XCTAssertTrue(sessionBytes.length > 0, "getPublicKeySessionKey session key length <= 0");
//            
//            let newKeyPackage = openPgp.getNewPublicKeyPackage(sessionBytes, publicKey: publicKey);
//            XCTAssertNotNil(newKeyPackage, "getNewPublicKeyPackage can't be nil");
//            XCTAssertTrue(newKeyPackage.length > 0, "getNewPublicKeyPackage out key length <= 0");
//            
//            let out = openPgp.decryptAttachment(newKeyPackage, data: encryptPackage.dataPackage, passphras: privatePassphrase);
//            XCTAssertNotNil(out, "DecryptAttachment 2 out not null");
//            XCTAssertTrue(out.length > 0, "out length can't be 0");
//            let test_out_msg1 = NSString(data: out, encoding: NSUTF8StringEncoding)
//            XCTAssertTrue(test_out_msg1 == test_string, "test_out_msg1 should be same as test_string");
//            
//            let newSymKeyPackage = openPgp.getNewSymmetricKeyPackage(sessionBytes, password: privatePassphrase);
//            XCTAssertNotNil(newSymKeyPackage, "getNewSymmetricKeyPackage out can't be null");
//            XCTAssertTrue(newSymKeyPackage.length > 0, "getNewSymmetricKeyPackage out length <= 0");
//            
//            let out1 = openPgp.decryptAttachmentWithPassword(newSymKeyPackage, data: encryptPackage.dataPackage, password: privatePassphrase);
//            XCTAssertNotNil(out1, "decryptAttachmentWithPassword out can't be null");
//            XCTAssertTrue(out1.length > 0, "decryptAttachmentWithPassword out length <= 0");
//            
//            let test_out_msg2 = NSString(data: out1, encoding: NSUTF8StringEncoding)
//            XCTAssertTrue(test_out_msg2 == test_string, "test_out_msg2 should be same as test_string");
//            print(" end \(i)");
        }
    }
    
    
    func test_encryptMediumAttachment() {
        var data_in : NSData?
        if let localFile = bundleInstance.pathForResource("testpdf", ofType: "pdf") {
            if let content = NSData(contentsOfFile: localFile) {
                data_in = content;
            }
        }
        
        XCTAssertNotNil(data_in, "test file can't be nil");
        
        let openPgp : PMNOpenPgp = PMNOpenPgp.createInstance()!
        var keys : [PMNOpenPgpKey] = [PMNOpenPgpKey]()
        let key = PMNOpenPgpKey(publicKey: publicKey, privateKey: privateKey)
        keys.append(PMNOpenPgpKey(publicKey: publicKey, privateKey: privateKey))
        openPgp.addAddress(PMNAddress(addressId: "1", addressName: "feng@protonmail.ch", keys: keys))
        
        for i in 0 ..< 30 {
            print(" start \(i)");
            let encryptPackage = openPgp.encryptAttachment("1", unencryptData: data_in!, fileName: "test.txt");
            XCTAssertNotNil(encryptPackage, "");
            XCTAssertNotNil(encryptPackage.keyPackage, "");
            XCTAssertNotNil(encryptPackage.dataPackage, "");
            
            let new_out_data = openPgp.decryptAttachment(encryptPackage.keyPackage, data: encryptPackage.dataPackage, passphras: privatePassphrase);
            XCTAssertNotNil(new_out_data, "DecryptAttachment 1 out not null");
            XCTAssertTrue(new_out_data.length > 0, "out length can't be 0");
            
//            let sessionBytes = openPgp.getPublicKeySessionKey(encryptPackage.keyPackage, privateKey: privateKey, passphrase: privatePassphrase);
//            XCTAssertNotNil(sessionBytes, "getPublicKeySessionKey can't be nil");
//            XCTAssertTrue(sessionBytes.length > 0, "getPublicKeySessionKey session key length <= 0");
//            
//            let newKeyPackage = openPgp.getNewPublicKeyPackage(sessionBytes, publicKey: publicKey);
//            XCTAssertNotNil(newKeyPackage, "getNewPublicKeyPackage can't be nil");
//            XCTAssertTrue(newKeyPackage.length > 0, "getNewPublicKeyPackage out key length <= 0");
//            
//            let out = openPgp.decryptAttachment(newKeyPackage, data: encryptPackage.dataPackage, passphras: privatePassphrase);
//            XCTAssertNotNil(out, "DecryptAttachment 2 out not null");
//            XCTAssertTrue(out.length > 0, "out length can't be 0");
//            
//            let newSymKeyPackage = openPgp.getNewSymmetricKeyPackage(sessionBytes, password: privatePassphrase);
//            XCTAssertNotNil(newSymKeyPackage, "getNewSymmetricKeyPackage out can't be null");
//            XCTAssertTrue(newSymKeyPackage.length > 0, "getNewSymmetricKeyPackage out length <= 0");
//            
//            let out1 = openPgp.decryptAttachmentWithPassword(newSymKeyPackage, data: encryptPackage.dataPackage, password: privatePassphrase);
//            XCTAssertNotNil(out1, "decryptAttachmentWithPassword out can't be null");
//            XCTAssertTrue(out1.length > 0, "decryptAttachmentWithPassword out length <= 0");
//            print(" end \(i)");
        }
    }
    
    
    func test_encryptLargeAttachment() {
        var data_in : NSData?;
        if let localFile = bundleInstance.pathForResource("large", ofType: "zip") {
            if let content = NSData(contentsOfFile: localFile) {
                data_in = content;
            }
        }
        
        XCTAssertNotNil(data_in, "test file can't be nil");
        
        let openPgp : PMNOpenPgp = PMNOpenPgp.createInstance()!
        var keys : [PMNOpenPgpKey] = [PMNOpenPgpKey]()
        let key = PMNOpenPgpKey(publicKey: publicKey, privateKey: privateKey)
        keys.append(PMNOpenPgpKey(publicKey: publicKey, privateKey: privateKey))
        openPgp.addAddress(PMNAddress(addressId: "1", addressName: "feng@protonmail.ch", keys: keys))
        
        for i in 0 ..< 1 {
            print(" start \(i)");
            let encryptPackage = openPgp.encryptAttachment("1", unencryptData: data_in!, fileName: "test.txt");
            XCTAssertNotNil(encryptPackage, "");
            XCTAssertNotNil(encryptPackage.keyPackage, "");
            XCTAssertNotNil(encryptPackage.dataPackage, "");
            
            let new_out_data = openPgp.decryptAttachment(encryptPackage.keyPackage, data: encryptPackage.dataPackage, passphras: privatePassphrase);
            XCTAssertNotNil(new_out_data, "DecryptAttachment 1 out not null");
            XCTAssertTrue(new_out_data.length > 0, "out length can't be 0");
            
//            let sessionBytes = openPgp.getPublicKeySessionKey(encryptPackage.keyPackage, privateKey: privateKey, passphrase: privatePassphrase);
//            XCTAssertNotNil(sessionBytes, "getPublicKeySessionKey can't be nil");
//            XCTAssertTrue(sessionBytes.length > 0, "getPublicKeySessionKey session key length <= 0");
//            
//            let newKeyPackage = openPgp.getNewPublicKeyPackage(sessionBytes, publicKey: publicKey);
//            XCTAssertNotNil(newKeyPackage, "getNewPublicKeyPackage can't be nil");
//            XCTAssertTrue(newKeyPackage.length > 0, "getNewPublicKeyPackage out key length <= 0");
//            
//            let out = openPgp.decryptAttachment(newKeyPackage, data: encryptPackage.dataPackage, passphras: privatePassphrase);
//            XCTAssertNotNil(out, "DecryptAttachment 2 out not null");
//            XCTAssertTrue(out.length > 0, "out length can't be 0");
//            
//            let newSymKeyPackage = openPgp.getNewSymmetricKeyPackage(sessionBytes, password: privatePassphrase);
//            XCTAssertNotNil(newSymKeyPackage, "getNewSymmetricKeyPackage out can't be null");
//            XCTAssertTrue(newSymKeyPackage.length > 0, "getNewSymmetricKeyPackage out length <= 0");
//            
//            let out1 = openPgp.decryptAttachmentWithPassword(newSymKeyPackage, data: encryptPackage.dataPackage, password: privatePassphrase);
//            XCTAssertNotNil(out1, "decryptAttachmentWithPassword out can't be null");
//            XCTAssertTrue(out1.length > 0, "decryptAttachmentWithPassword out length <= 0");
//            print(" end \(i)");
        }
    }
    
    
    
    func test_singleKeyEncryptDecrypt() {
//        var plain_text : String = ""
//        if let localFile = bundleInstance.pathForResource("test_plain_message", ofType: "txt") {
//            if let content = String(contentsOfFile:localFile, encoding:NSUTF8StringEncoding, error: nil) {
//                plain_text = content;
//            }
//        }
//        XCTAssertFalse(plain_text.isEmpty, "test file can't be empty");
//        
//        let openPgp : PMNOpenPgp = PMNOpenPgp.createInstance()!
//        
//        for i in 0 ..< 100 {
//            print(" start \(i)");
//            let encryptedText = openPgp.encryptMessageSingleKey(publicKey, plainText: plain_text)
//            XCTAssertNotNil(encryptedText, "encryptedText can't null")
//            XCTAssertFalse(encryptedText.isEmpty, "cleartext can't empty")
//            
//            let decryptedText = openPgp.decryptMessageSingleKey(encryptedText, privateKey: privateKey, passphras: privatePassphrase)
//            XCTAssertNotNil(encryptedText, "decryptedText can't null")
//            XCTAssertFalse(encryptedText.isEmpty, "decryptedText can't empty")
//            XCTAssertTrue(decryptedText == plain_text, "decryptedText should be same as cleartext")
//            print(" end \(i)");
//        }

    }
    
    
}
