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
        
        
        
        PMNOpenPgp.createInstance()?.generateKey("feng@pm.me", domain: "", passphrase: "123", bits: 2048, time: 0)
        
        let str = """
        BEGIN:VCARD
        VERSION:4.0
        PRODID:test 111.00
        END:VCARD
        """
//        PHOTO:data:image/jpeg;base64,cLaxHfZiBSjwsi5i
//        FN:Andrew Smith
//        URL:SJSU.com
//        NOTE:Wuaues
//        ORG:Is kid
        guard let vcard = PMNIEzvcard.parseFirst(str) else {
            return
        }
//        let newNotes = "По секоја од петте точки за кои е прогласен за виновен, австралискиот кардинал Џорџ Пел би можел да добие до максимални 10 години затвор, објави судот.\n\nКардиналот, кој по едномесечно судење во декември 2018 година, е прогласен за виновен за сексуални злоупотрби на две малолетни момчиња. Тој ќе остане во затвор бидејќи судот му ја отфрли кауцијата.\n\nТретиот човек на Ватикан е осуден за сексуална злоупотреба за што тој тврди дека е невин, а неговиот адвокат поднесе жалба на пресудата. Изрекувањето на должината на казната се очекува на 13 март.\n\nПоротата уште во декември едногласно го прогласи за виновен по пет точки за сексуална злоупотреба на деца помлади од 16 години. Самата пресуда и деталите на целиот случај остануваат тајна сè до следниот вторник поради правни причини.\n\nПо секоја од петте точки за кои е прогласен виновен, Пел би можел да добие до максимални 10 години затвор."

        let newNotes = "Поротата уште во декември едногласно го прогласи за виновен по пет точки за сексуална злоупотреба на деца помлади од 16 години. Самата пресуда и деталите на целиот случај остануваат тајна сè до следниот вторник поради правни причини.\n\n"
        
        
//         let newNotes = "случај остануваат тајна сè до test \n\nПоротата у \r\n,  't' 'e' 's' 't' \n \\x"
//        print(newNotes)
        let n = PMNINote.createInstance("", note: newNotes)!
//        vcard3.setNote(n)
//        isCard3Set = true
//
//        let testnote = n.getNote()
//
//        let testnobj = vcard3.getNote()
//        let testnote2 = testnobj?.getNote()
//        let note =
        vcard.setNote(n)
        
        let out = PMNIEzvcard.write(vcard)
        
        guard let vcard1 = PMNIEzvcard.parseFirst(out) else {
            return
        }
        let n2 = vcard1.getNote()
        
        let noteout = n2?.getNote()
        print(noteout!)
        print(out)
        
        
        
//        auto vcard = Ezvcard::parse(str).first();
//        auto formattedName = vcard->getFormattedName();
//        VERIFY_ARE_EQUAL(formattedName->getValue(), "Andrew Smith");
//
//        // clone and verify the new vCard
//        auto newVCard = std::make_shared<VCard>();
//        newVCard->setVersion(VCardVersion::V4_0());
//        newVCard->setFormattedName(std::make_shared<FormattedName>(formattedName->getValue()));
//
//        auto photos = vcard->getPhotos();
//        for(auto photo : photos)
//            newVCard->addPhoto(photo);
//
//        std::string note = "По секоја од петте точки за кои е прогласен за виновен, австралискиот кардинал Џорџ Пел би можел да добие до максимални 10 години затвор, објави судот.\n\nКардиналот, кој по едномесечно судење во декември 2018 година, е прогласен за виновен за сексуални злоупотрби на две малолетни момчиња. Тој ќе остане во затвор бидејќи судот му ја отфрли кауцијата.\n\nТретиот човек на Ватикан е осуден за сексуална злоупотреба за што тој тврди дека е невин, а неговиот адвокат поднесе жалба на пресудата. Изрекувањето на должината на казната се очекува на 13 март.\n\nПоротата уште во декември едногласно го прогласи за виновен по пет точки за сексуална злоупотреба на деца помлади од 16 години. Самата пресуда и деталите на целиот случај остануваат тајна сè до следниот вторник поради правни причини.\n\nПо секоја од петте точки за кои е прогласен виновен, Пел би можел да добие до максимални 10 години затвор.";
//        Note::Ptr newNote = std::make_shared<ezvcard::Note>(note);
//        newNote->setType("");
//        newVCard->setNote(newNote);
//        auto out = Ezvcard::write(newVCard)->go();
//        VERIFY_ARE_EQUAL(out, str);
        
        
        
//        let button:UIButton = sender as! UIButton;
//        
//        button.isEnabled = false;
//        
//        let data = Data()
//        
//        
//        let out = PMNSrpClient.expandHash(data)
        
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

