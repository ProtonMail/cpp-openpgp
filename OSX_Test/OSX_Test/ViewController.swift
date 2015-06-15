//
//  ViewController.swift
//  OSX_Test
//
//  Created by Yanfeng Zhang on 3/2/15.
//  Copyright (c) 2015 Yanfeng Zhang. All rights reserved.
//

import Cocoa

class ViewController: NSViewController {

    override func viewDidLoad() {
        super.viewDidLoad()

        // Do any additional setup after loading the view.
    }

    override var representedObject: AnyObject? {
        didSet {
        // Update the view, if already loaded.
        }
    }
    @IBOutlet weak var test_change_pwd: NSButton!

    @IBAction func test_change_pwd_clicked(sender: AnyObject) {
        let pgp:OpenPGP = OpenPGP()
        let location = "/Users/Yanfeng/Desktop/testpub.txt"
        let location_1 = "/Users/Yanfeng/Desktop/testprivat.txt"
        let fileContent = NSString(contentsOfFile: location, encoding: NSUTF8StringEncoding, error: nil) as! String
        let fileContent_1 = NSString(contentsOfFile: location_1, encoding: NSUTF8StringEncoding, error: nil) as! String
        
        let value = pgp.SetupKeys(fileContent_1, pubKey: fileContent, pass: "321", error:nil)
        var keys = pgp.update_key_password("123", new_pwd:"321", error: nil)
        
    }
    @IBAction func test_new_key(sender: AnyObject) {
        
        
        let pgp:OpenPGP = OpenPGP();
        var pub_key:String?;
        var priv_key:String?;
        var keys = pgp.generate_key("123", username:"feng_test_1", error: nil);

        
    }
    @IBAction func test_import_clicked(sender: AnyObject) {
        
        
        let pgp:OpenPGP = OpenPGP();
        //pgp.SetupKeys("", pubKey: public_key_, pass: "123", error: nil)
        
        let testStr : String = "-----BEGIN PGP MESSAGE-----\nVersion: OpenPGP.js v0.10.1-IE\nComment: http://openpgpjs.org\n\nww0ECQMIina34sp8Nlpg0sAbAc/x6pR8h57OJv9pklLuEc/aH5lFT9OpWS+N\n7oPaJCGK1f3aQV7g5V5INlUvwICeDiSkDMo+hHGtFgDFEwgNiMDc7wAtod1U\nZ5PTHegr8KWWmBiDIYuPVFJH8mALVcQen9MI1xFSYO8RvSxM/P6dJPzrVZQK\noIRW98dxMjJqMWW9HgqWCej6TRDua65r/X7Ucco9tWpwzmQCnvJLqpcYYrEk\ngcGyXsp3RvISG6pWh8ZFemeO6yoqnphYmcAa/i4h4CiMqKDDJuOg4UdpW46U\nGoNSV+C4hz5ymRDj\n=hUe3\n-----END PGP MESSAGE-----"
        
        pgp.decrypt_message_aes(testStr, pwd: "123", error: nil)
        
        let test_message = "this is a test message";
        let enc_msg = pgp.encrypt_message_aes(test_message, pwd: "123", error: nil)
        NSLog(enc_msg)
        let un_enc_msg = pgp.decrypt_message_aes(enc_msg, pwd: "123", error: nil)
        NSLog(un_enc_msg)
        
        
        let location = "/Users/Yanfeng/Desktop/testpub.txt"
        
        let location_1 = "/Users/Yanfeng/Desktop/testprivat.txt"//"/Users/Yanfeng/Desktop/old/sample/private_key.txt"//
        
        
        let fileContent = NSString(contentsOfFile: location, encoding: NSUTF8StringEncoding, error: nil) as! String
        let fileContent_1 = NSString(contentsOfFile: location_1, encoding: NSUTF8StringEncoding, error: nil) as! String
        
        let PublicKey = "-----BEGIN PGP PUBLIC KEY BLOCK-----\nVersion: OpenPGP.js v0.7.1\nComment: http://openpgpjs.org\n\nxsBNBFSjdRkBB/9slBPGNrHAMbYT71AnxF4a0W/fcrzCP27yd1nte+iUKGyh\nyux3xGQRIHrwB9zyYBPFORXXwaQIA3YDH73YnE0FPfjh+fBWENWXKBkOVx1R\nefPTytGIyATFtLvmN1D65WkvnIfBdcOc7FWj6N4w5yOajpL3u/46Pe73ypic\nhe10XuwO4198q/8YamGpTFgQVj4H7QbtuIxoV+umIAf96p9PCMAxipF+piao\nD8LYWDUCK/wr1tSXIkNKL+ZCyuCYyIAnOli7xgIlKNCWvC8csuJEYcZlmf42\n/iHyrWeusyumLeBPhRABikE2ePSo+XI7LznD/CIrLhEk6RJT31+JR0NlABEB\nAAHNBlVzZXJJRMLAcgQQAQgAJgUCVKN1JAYLCQgHAwIJEH0tU95Lz7QEBBUI\nAgoDFgIBAhsDAh4BAAAXCgf8CsNCB0tKdLrwGe+dDLTGGdgyYr33Jz6GVta6\nJMl4rccf5T8QiRPkOIWITITpi5maxrn1w7yOUI3xkqCLCEO9vqLhIRr1/aBq\nvVUI+0L7goJoVrx6ynSR1KNNHM/hkttA+t1t894qgug6hooUfxtFWU8KesKK\ngdMFOxst3ODTeZxzO6xmiaf9Mof/y1M5y1fsKuUH57AJRzkJYviZmpEWMAxI\nmmiCPv/iMRUeR7hX9+spG2O9A0Ny46g89T59Wkerggu6/ulgX0O6MAhsuBY3\n+10TgajGyub5oJTLKVDY/nlVvmaEA+4IthepIQs+L3380oQz3GEtr/UfB1PB\nD/VfTM7ATQRUo3UkAQf/dcKxn9bt+fDMxuQT6sxSWjX4ptf6W0QbucDA/5Dw\n2vCFvCGakDdsczduFJ23QI7iZHHig5Fyp5M2MV+1DM/EJs9OZxMK6k0I4M4r\niucSf2L2XPv8m2Q5/nn7+gdvH6mO8POsDu766A0fMNhN36eHa5730dahJlIR\nYP+wOunUkQ3wzTPE4MZh878eCvkaeelMTMPNnQu9ONgxVyaO8GG09M0uJCxV\nqQ6PXBMtYSBydrYUscAeHQrreyfECNPobWgXRafTwftk/n9aGIzLViv4zo36\nGwuk7JzC3AF2PANxYus6EACPckwsjpbMVLpIpSvjDGdlYg9BPtNk0Fd4qZt2\nzwARAQABwsBfBBgBCAATBQJUo3UmCRB9LVPeS8+0BAIbDAAAgzcH/1kyh+20\ntcUGMRrT3akfhVv3o4d9C4j0Ja7PQMKwZNiSdFSbQ8ZE9xbR5cKB/Z33emMw\n+54CeJsanj7lOeefRqoHUynpirANguPLmp8SW4Dor4rwSOs4gfO1ttzw7+8M\nIeFG8p8OQ5B+J3+KCUdiuB+6zdxGW3rIfA9OAPYAObQUJ7quS/lmoNrOzKVm\nJWa7x4f9cS2Wls/vt/jeEn2j0x/GqN0KI8P2PjixiBY5Ogf6FRHvWWUD4SYx\n8YHf6rvFXGHW3tdMRRb24miP0UuhbOyUUiQm1xNIe2fJ+IUCD9cumgWbGXof\nGjz3pBuLbZus9/waqlaZWpyEUl5bKsqeifA=\n=LhM4\n-----END PGP PUBLIC KEY BLOCK-----";
        
        
        let PrivateKey = "-----BEGIN PGP PRIVATE KEY BLOCK-----\r\nVersion: OpenPGP.js v0.9.0\r\nComment: http://openpgpjs.org\r\n\r\n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\nPPekG4ttm6z3/BqqVplanIRSXlsqyp6J8A==\r\n=Pyb1\r\n-----END PGP PRIVATE KEY BLOCK-----\r\n";
        pgp.SetupKeys(fileContent_1, pubKey: fileContent, pass: "123", error:nil)

        pgp.Test_Privatekey(PrivateKey, pass: "123");
        
        
    }

    @IBAction func test_aes_clicked(sender: AnyObject) {
        
        let pgp:OpenPGP = OpenPGP();
        
        let testStr : String = "-----BEGIN PGP MESSAGE-----\nVersion: OpenPGP.js v0.10.1-IE\nComment: http://openpgpjs.org\n\nww0ECQMIina34sp8Nlpg0sAbAc/x6pR8h57OJv9pklLuEc/aH5lFT9OpWS+N\n7oPaJCGK1f3aQV7g5V5INlUvwICeDiSkDMo+hHGtFgDFEwgNiMDc7wAtod1U\nZ5PTHegr8KWWmBiDIYuPVFJH8mALVcQen9MI1xFSYO8RvSxM/P6dJPzrVZQK\noIRW98dxMjJqMWW9HgqWCej6TRDua65r/X7Ucco9tWpwzmQCnvJLqpcYYrEk\ngcGyXsp3RvISG6pWh8ZFemeO6yoqnphYmcAa/i4h4CiMqKDDJuOg4UdpW46U\nGoNSV+C4hz5ymRDj\n=hUe3\n-----END PGP MESSAGE-----"
        
        let message = pgp.decrypt_message_aes(testStr, pwd: "123", error: nil)
        if(message == "<div>lajflkjasklfjlksdfkl</div><div><br></div><div>Sent from iPhone <a href=\"https://protonmail.ch\">ProtonMail</a>, encrypted email based in Switzerland.<br></div>")
        {
            NSLog("OK")
        }
        
        let test_message = "this is a test message";
        let enc_msg = pgp.encrypt_message_aes(test_message, pwd: "123", error: nil)
        //NSLog(enc_msg)
        let un_enc_msg = pgp.decrypt_message_aes(enc_msg, pwd: "123", error: nil)
        //NSLog(un_enc_msg)
        
        if(test_message == un_enc_msg)
        {
            NSLog("OK")
        }

    }
    @IBAction func EncryptMailboxPWD(sender: AnyObject) {
        let pgp:OpenPGP = OpenPGP();
        
        let v = pgp.encrypt_mailbox_pwd("thisisatestmailbox", slat: "4428c82a118a2dc76f53dab507d3b1d69850ebb9")
        
        let out = pgp.decrypt_mailbox_pwd(v, slat: "4428c82a118a2dc76f53dab507d3b1d69850ebb9")
        
        println(out);

        
    }
    
    @IBAction func test_bad_message(sender: AnyObject) {
        let pgp:OpenPGP = OpenPGP()
        let location = "/Users/Yanfeng/Desktop/publickey.txt"
        let location_1 = "/Users/Yanfeng/Desktop/privatekey.txt"
        let location_2 = "/Users/Yanfeng/Desktop/bad.message.txt"
        let fileContent = NSString(contentsOfFile: location, encoding: NSUTF8StringEncoding, error: nil) as! String
        let fileContent_1 = NSString(contentsOfFile: location_1, encoding: NSUTF8StringEncoding, error: nil) as! String
        let fileContent_2 = NSString(contentsOfFile: location_2, encoding: NSUTF8StringEncoding, error: nil) as! String
        
        let value = pgp.SetupKeys(fileContent_1, pubKey: fileContent, pass: "Jiao2Jian", error:nil)
        let enc_m = pgp.encrypt_message("test", error: nil)
        let asfsdfa = pgp.decrypt_message(enc_m, error: nil)
        let dec_m = pgp.decrypt_message(fileContent_2, error: nil)

        println(dec_m);
        
    }
    @IBAction func test_encrypt_decrypt_attachment(sender: AnyObject) {
        let pgp:OpenPGP = OpenPGP()
        let pub_location = "/Users/Yanfeng/Desktop/publickey.net.txt"
        let priv_location = "/Users/Yanfeng/Desktop/privatekey.net.txt"
        let key_package_location = "/Users/Yanfeng/Desktop/keypackage.txt"
        let data_package_location = "/Users/Yanfeng/Desktop/dataPack.txt"

        let pubkey = NSString(contentsOfFile: pub_location, encoding: NSUTF8StringEncoding, error: nil) as! String
        let privkey = NSString(contentsOfFile: priv_location, encoding: NSUTF8StringEncoding, error: nil) as! String
        let key_package = NSString(contentsOfFile: key_package_location, encoding: NSUTF8StringEncoding, error: nil) as! String
        let data_package = NSString(contentsOfFile: data_package_location, encoding: NSUTF8StringEncoding, error: nil) as! String
        
        let value = pgp.SetupKeys(privkey, pubKey: pubkey, pass: "123", error:nil)
        
        
        let data = pgp.Test_Attachment(key_package, data: data_package)

        data.writeToFile("/Users/Yanfeng/Desktop/1.png", atomically: false)

        
        println("Done");

    }
}

