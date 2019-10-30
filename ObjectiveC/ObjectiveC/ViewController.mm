//
//  ViewController.m
//  ObjectiveC_Test
//
//  Created by Yanfeng Zhang on 1/29/15.
//  Copyright (c) 2015 Yanfeng Zhang. All rights reserved.
//

#import "ViewController.h"
#import <OpenPGP.h>



@interface ViewController ()

@end

@implementation ViewController

@synthesize private_key_;
@synthesize public_key_;

- (void)viewDidLoad {
    [super viewDidLoad];
    
    public_key_ = @"-----BEGIN PGP PUBLIC KEY BLOCK-----\nVersion: OpenPGP.js v0.7.1\nComment: http://openpgpjs.org\n\nxsBNBFSjdRkBB/9slBPGNrHAMbYT71AnxF4a0W/fcrzCP27yd1nte+iUKGyh\nyux3xGQRIHrwB9zyYBPFORXXwaQIA3YDH73YnE0FPfjh+fBWENWXKBkOVx1R\nefPTytGIyATFtLvmN1D65WkvnIfBdcOc7FWj6N4w5yOajpL3u/46Pe73ypic\nhe10XuwO4198q/8YamGpTFgQVj4H7QbtuIxoV+umIAf96p9PCMAxipF+piao\nD8LYWDUCK/wr1tSXIkNKL+ZCyuCYyIAnOli7xgIlKNCWvC8csuJEYcZlmf42\n/iHyrWeusyumLeBPhRABikE2ePSo+XI7LznD/CIrLhEk6RJT31+JR0NlABEB\nAAHNBlVzZXJJRMLAcgQQAQgAJgUCVKN1JAYLCQgHAwIJEH0tU95Lz7QEBBUI\nAgoDFgIBAhsDAh4BAAAXCgf8CsNCB0tKdLrwGe+dDLTGGdgyYr33Jz6GVta6\nJMl4rccf5T8QiRPkOIWITITpi5maxrn1w7yOUI3xkqCLCEO9vqLhIRr1/aBq\nvVUI+0L7goJoVrx6ynSR1KNNHM/hkttA+t1t894qgug6hooUfxtFWU8KesKK\ngdMFOxst3ODTeZxzO6xmiaf9Mof/y1M5y1fsKuUH57AJRzkJYviZmpEWMAxI\nmmiCPv/iMRUeR7hX9+spG2O9A0Ny46g89T59Wkerggu6/ulgX0O6MAhsuBY3\n+10TgajGyub5oJTLKVDY/nlVvmaEA+4IthepIQs+L3380oQz3GEtr/UfB1PB\nD/VfTM7ATQRUo3UkAQf/dcKxn9bt+fDMxuQT6sxSWjX4ptf6W0QbucDA/5Dw\n2vCFvCGakDdsczduFJ23QI7iZHHig5Fyp5M2MV+1DM/EJs9OZxMK6k0I4M4r\niucSf2L2XPv8m2Q5/nn7+gdvH6mO8POsDu766A0fMNhN36eHa5730dahJlIR\nYP+wOunUkQ3wzTPE4MZh878eCvkaeelMTMPNnQu9ONgxVyaO8GG09M0uJCxV\nqQ6PXBMtYSBydrYUscAeHQrreyfECNPobWgXRafTwftk/n9aGIzLViv4zo36\nGwuk7JzC3AF2PANxYus6EACPckwsjpbMVLpIpSvjDGdlYg9BPtNk0Fd4qZt2\nzwARAQABwsBfBBgBCAATBQJUo3UmCRB9LVPeS8+0BAIbDAAAgzcH/1kyh+20\ntcUGMRrT3akfhVv3o4d9C4j0Ja7PQMKwZNiSdFSbQ8ZE9xbR5cKB/Z33emMw\n+54CeJsanj7lOeefRqoHUynpirANguPLmp8SW4Dor4rwSOs4gfO1ttzw7+8M\nIeFG8p8OQ5B+J3+KCUdiuB+6zdxGW3rIfA9OAPYAObQUJ7quS/lmoNrOzKVm\nJWa7x4f9cS2Wls/vt/jeEn2j0x/GqN0KI8P2PjixiBY5Ogf6FRHvWWUD4SYx\n8YHf6rvFXGHW3tdMRRb24miP0UuhbOyUUiQm1xNIe2fJ+IUCD9cumgWbGXof\nGjz3pBuLbZus9/waqlaZWpyEUl5bKsqeifA=\n=LhM4\n-----END PGP PUBLIC KEY BLOCK-----";
    
    
    
    private_key_ = @"-----BEGIN PGP PRIVATE KEY BLOCK-----\r\nVersion: OpenPGP.js v0.9.0\r\nComment: http://openpgpjs.org\r\n\r\n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\nPPekG4ttm6z3/BqqVplanIRSXlsqyp6J8A==\r\n=Pyb1\r\n-----END PGP PRIVATE KEY BLOCK-----\r\n";
    
    
}

- (void)didReceiveMemoryWarning {
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}


- (IBAction)large_test_clicked:(id)sender {
    UIButton * button = sender;
    
    [button setEnabled:false];
    
    OpenPGP * pgp = [[OpenPGP alloc] init];
    BOOL isRight = [pgp SetupKeys:private_key_ pubKey:public_key_ pass:@"123" error:nil];
    isRight = [pgp SetupKeys:public_key_ pubKey:private_key_ pass:@"1234" error:nil];
    
    NSString* test_msg =  @"We\'ve received your order ﻿nk <IMG height=93 alt=\"\" src=\"\" width=531></A></DIV></TD></TR> --></TBODY></TABLE><!-- footerimage end --> </table>";
    
    
    int count = 1;
    
    CFTimeInterval startTime = CACurrentMediaTime();
    {
        @autoreleasepool {
            for (size_t j = 0; j < count; j++) {
                //CFTimeInterval s = CACurrentMediaTime();
                NSString* pgp_msg = [pgp encrypt_message:test_msg pub_key:public_key_ error:nil];
                //NSLog(@"%@", pgp_msg);
                
                //CFTimeInterval e = CACurrentMediaTime();
                //NSLog(@"encrypt_message Runtime: %g s", e - s);
                
                
                NSString *cleartext = [pgp decrypt_message:pgp_msg error:nil];
                // NSLog(@"%@", cleartext);
                
                if ([test_msg isEqualToString:cleartext]) {
                    NSLog(@"KLJDSKLJFKSDJFLKSDFKJSDFJSDKLJFLKSDJFKJSDLFJSDKLFSDFKLSDFSLDFLSFJKLSJDFJSLKFKLSDFSFLSJDLKFSDKLJL");
                }
                else
                {
                    NSLog(@"error");
                }
            }
        }
    }
    
    CFTimeInterval endTime = CACurrentMediaTime();
    [_log_lable setText:  [NSString stringWithFormat:@"%d Times(ENC->DEC) --- Total Runtime: %g s --- Avg %g s", count, (endTime - startTime),  (endTime - startTime)/count]];
    
    [button setEnabled:YES];
    
}

- (IBAction)tiny_test_clicked:(id)sender {
    

    
    UIButton * button = sender;
    [button setEnabled:false];
    
    OpenPGP * pgp = [[OpenPGP alloc] init];
    

    
    //NSLog(@"Documents directory: %@", [fileMgr contentsOfDirectoryAtPath:documentsDirectory error:nil]);
    NSString *path;
    NSArray *paths = NSSearchPathForDirectoriesInDomains(NSDocumentDirectory, NSUserDomainMask, YES);
    path = [[paths objectAtIndex:0] stringByAppendingPathComponent:@"test"];
    path = [path stringByAppendingPathComponent:@"1.56mb.txt"];
    NSLog(@"Documents directory: %@",path);
          
          //    if ([[NSFileManager defaultManager] fileExistsAtPath:path])		//Does file exist?
          //    {
          //        if (![[NSFileManager defaultManager] removeItemAtPath:path error:nil])	//Delete it
          //        {
          //            NSLog(@"Delete file error:");
          //        }
          //    }
    
          
    //NSData *filedata = [pgp Test_1];
    
    //BOOL Success = [[NSFileManager defaultManager] createFileAtPath:path contents:nil attributes:nil];
    
    
    
    
    [pgp SetupKeys:private_key_ pubKey:public_key_ pass:@"123" error:nil];
    
    
    NSString* test_msg = @"test_open_pgp_protonmailtest_open_pgp_protonmailtest_open_pgp_protonmailtest_open_pgp_protonmailtest_open_pgp_protonmailtest_open_pgp_protonmailtest_open_pgp_protonmailtest_open_pgp_protonmailtest_open_pgp_protonmailtest_open_pgp_protonmailtest_open_pgp_protonmailtest_open_pgp_protonmailtest_open_pgp_protonmailtest_open_pgp_protonmailtest_open_pgp_protonmailtest_open_pgp_protonmailtest_open_pgp_protonmailtest_open_pgp_protonmailtest_open_pgp_protonmailtest_open_pgp_protonmailtest_open_pgp_protonmailtest_open_pgp_protonmailtest_open_pgp_protonmailtest_open_pgp_";
    
    int count = 1;
    
    CFTimeInterval startTime = CACurrentMediaTime();
    {
        @autoreleasepool {
            for (size_t j = 0; j < count; j++) {
                //CFTimeInterval s = CACurrentMediaTime();
                NSString* pgp_msg = [pgp encrypt_message:test_msg pub_key:public_key_ error:nil];
                NSLog(@"%@", pgp_msg);
                
                //CFTimeInterval e = CACurrentMediaTime();
                // NSLog(@"encrypt_message Runtime: %g s", e - s);
                
                
                NSString *cleartext = [pgp decrypt_message:pgp_msg error:nil];
                // NSLog(@"%@", cleartext);
                
                if ([test_msg isEqualToString:cleartext]) {
                    NSLog(@"KLJDSKLJFKSDJFLKSDFKJSDFJSDKLJFLKSDJFKJSDLFJSDKLFSDFKLSDFSLDFLSFJKLSJDFJSLKFKLSDFSFLSJDLKFSDKLJL");
                }
                else
                {
                    NSLog(@"error");
                }
            }
        }
    }
    
    CFTimeInterval endTime = CACurrentMediaTime();
    [_log_lable setText:  [NSString stringWithFormat:@"%d Times(ENC->DEC) --- Total Runtime: %g s --- Avg %g s", count, (endTime - startTime),  (endTime - startTime)/count]];
    
    [button setEnabled:YES];
}
-(NSString*)encodeURIComponent:(NSString*)str{
    return CFBridgingRelease(CFURLCreateStringByAddingPercentEscapes(NULL, (__bridge CFStringRef)str, NULL, (__bridge CFStringRef)@"!*'\"();:@&=+$,/?%#[]% ", CFStringConvertNSStringEncodingToEncoding(NSUTF8StringEncoding)));
}
- (IBAction)decrypt_test_clicked:(id)sender {
    
    OpenPGP * pgp = [[OpenPGP alloc] init];
    BOOL isRight = [pgp SetupKeys:private_key_ pubKey:public_key_ pass:@"123" error:nil];
    
    if (isRight) {
        NSLog(@"key is ok");
    }
    
    
    
    //    NSString* test_msg = @"---BEGIN ENCRYPTED MESSAGE---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---END ENCRYPTED MESSAGE---||---BEGIN ENCRYPTED RANDOM KEY--------BEGIN PGP MESSAGE-----\n"
    //"Version: OpenPGP.js v0.9.0\n"
    //"Comment: http://openpgpjs.org\n"
    //"\n"
    //    "wcBMA2tjJVxNCRhtAQf/YzkQoUqaqa3NJ/c1apIF/dsl7yJ4GdVrC3/w7lxE\n"
    //    "2CO5ioQD4s6QMWP2Y9dOdVl2INwz8eXOds9NS+1nMs4SoMbrpJnAjx8Cthti\n"
    //    "1Z/8eWMU023LYahds8BYM0T435K/2tTB5GTA4uTl2y8Xzz2PbptQ4PrUDaII\n"
    //    "+egeQQyPA0yuoRDwpaeTiaBYOSa06YYuK5Agr0buQAxRIMCxI2o+fucjoabv\n"
    //    "FsQHKGu20U5GlJroSIyIVVkaH3evhNti/AnYX1HuokcGEQNsF5vo4SjWcH23\n"
    //    "2P86EIV+w5lUWC1FN9vZCyvbvyuqLHQMtqKVn4GBOkIc3bYQ0jru3a0FG4Cx\n"
    //    "bNJ0ASps2+p3Vxe0d+so2iFV92ByQ+0skyCUwCNUlwOV5V5f2fy1ImXk4mXI\n"
    //    "cO/bcbqRxx3pG9gkPIh43FoQktTT+tsJ5vS53qfaLGdhCYfkrWjsKu+2P9Xg\n"
    //    "+Cr8clh6NTblhfkoAS1gzjA3XgsgEFrtP+OGqwg=\n"
    //    "=c5WU\n"
    //    "-----END PGP MESSAGE-----\n"
    //    "---END ENCRYPTED RANDOM KEY---";
    
    NSString* test_msg = @"---BEGIN ENCRYPTED MESSAGE---FMOxw4ZkEkfDny5jw6PDtUnCiGx/wqDDjB7CskLCiEdhfcKbelY8KsOLw6N6wq1Dw69UfkM0w5oTacKvB8KJw4rDmcKEZWMtZ8KHNMKxN8K9dl94w7nDrEx2ck3Do8OZWMKxRSN9DMOXw5HCgRXDnDvCtsKuwpPDoi3DisOCwqzDvggTeSnCoMOzw5IKw7lEUQnDj8KJwrB0w6nDq13DlcKBwpUXHXnCm3TCjRUrTcONV8OTE3nDvG7CiMKNw4wzwq5JRMOIwp/DkMO8C8Krw65tYRDDp8OCbAMMw5suTi3DjMK7Qx9ww45awqVdwo3DkBDCnXvDqcOqMRXDsMOQAMO9w63CoMKLGyc1w4bCs2YZw5RmdVbDqlYcw57DucKzwrXCnH5QwoHDtsKCYQzDnG/Cu8KjPsK7woPDrcONw7zDssKuwohVw4vDuVvCsT8WwqQ2TxY9w5lIwovCgV/CsEPCvMKlw5RxcMOZw4wYanrCjVJCw6rDhkMsG30uVwMfF0nCpMO7IsKVw4piBcOQw7PDqDdKwprCi1HCqn7Ds8Oaw6zChB8LwrzCjMOOw4p6w4UzwpHCkcK9ScOpwqwJEMORAcKbPcOWBTnCribDm8KNw4rCqcK4H09nFsKvd8K4wqMyw53Dmxpbw4LCoDHCsMKyNsK/O8OpwpcbIWJ9w61EOsO5XD8ew4vDmUNVwqbDmRhzGsOOw7c5w7/CpMOPPsOPRC5nw43Cv2E4dXE+Kx7Dq8KzwrzChMOXIgrCqcOkwqpOFDoPFcKnPsKOQBUkwqXDvFIMw40Fei/DsHfDl1PCisKQUwkcw5TCmcOmDAfDjB5bwrPDjHQpw6nCshZkO8K2woTDmMOlwqIIw6w/V8O4w7JbTcOncCDClWfCv8K5woETw71KwoTCgsOOHMOeV8Kvwrtfw4UHwplAdcKjwrjDsDLCssO5w6DCkUdZwqMFUcKfwq/CuMONN8Oyw7Biw77Cg8OewrNtwpdVw6PCrsKJwobDu1hZw6lRX03ChgpRTxbCq8K6wovDpVcZwrTCvsKdc8OWcG7DncKuRcO8wqxXw7TCugg0w5LCsQfCuHDCsEpPQGjDoVPCncK1BMKRGEDCtFg0WsKlwpbCnMOVwp7DtkkuwoUMwpXCmgfDpifCnsORJn87w5HDsMKBwqTDilTDj8KPwrnCiMKWX8OTaXcmwp0TVsO8JcOWwpnCnMOZw7/DqcOxwqfDrm9awrVGwoZVwrddEsKdZ2zDlWZiwq3CuMOFFmMuwrTDtGXDnyUKwqsUSlzChcO0wqrCucO5woXDqcKFw5Nlwpg6w5vCmV/CmwvDhThoERJaaQYLw5/DgcO0w7Zocn9ww40NPMK+esK5wrcXw4zCk0Ffw5Q8XMKgwopxOifCksOsUQhDBsKzwr/ClkzDv8ORwpzDniIpDFkKwoduSRLDh8KOUsK+B8KFKU/Ct8O8fSxPGsKkwrAWw4TClMK/TTfDmcKkKsOgLMKGKCjCvjPCu8OzSV4LwqtMwppHw74AwrfCrXTCqMOiNsKwbMOMAF7CsMKPwovCscK4R3jCqMOmwrZ2c2XCunQcwrdxwoVmFMO7KDwNw6vDhsKhDcKHA2vCqgUlBcKnL8OZwpEsw7TCnl7CsQzDv8Okw6vDl8K1EsKsw6Vmw4DCusO5X1xfwo3DpFMNA04jMsOONMOdw4VhQ8KrwrgbwrjDljLDhMKtwrcobcKRTsOyw6paJgLDoh3Cu8KWw7nDiMO6bMKpPHXDqRVUw7XCkUUJdsOtw5h6w4w1eRPCq8ONw4LCt8KfPF/DocOfRis0w7bDo2kgwqjCkMK+MmbDmMOVwogzwrHCuMOaNcO7w5jCtSg+eAPDnx3Dslc4I8KZWDYUGCdzbkpOwqI4w6d8McOWSl3CicKzwrUmQ8K9w7UVbcKUaFrDosKXY8KZYwwqwoHCusKFEAk9Hx88DgYafsKFBsOAwrDCjcKMw513wq3DssOdPsO5wovDlcOQwrBuwpkBw5XDsMK/w5LCpcKGwozDisKTwpQyZcKXw4hgwo3DhsK1w7LDgMKAwrMWw57DpFYhw6t/MHfCuMKHeWrDtH7DoMKPKSESXcObDcOtw7rDucKYw5EGw6Unwrkxw5F1W8OCwpNaTm5FwqAVwr1Zw6fDrMOMShjDsi7ChsO2F3ZuwohIRcKEZgzDokR+JmvCocK1wqwPVcOxwqnDgMOxwqPCq0XDu8OQNUldTsOKw6/CosK7wpsMwq/DrsKGZ8OoOcKVWUHCgxXCuMOyAMKdwozDn8OTT8OpcT0VwovDixnDlsKYc0lfVTfCo8KUTsO4XzJsIUwBwrckwqkKeMK3T8OCRMKBw6wLMxYYw4R+cMOWw5PCosO5VMO1ESXCijBHM8KYNBLDiUltDsK6B8Kjwp3DuG5VN8O5w5Qew7HDiMK3T8KdfUUGw6/DiE3DrsObw7FLLMO9W8OHwr8zwrggfhXCu8OqYsOrLsKzRSsXT8Kfw5htWMOnHysFY8OiGcOuWsO3CcO5fsOLw6dlw53DmMKFAXFIw6rCgB8pFMKCfjfCpGAEcEpXwq5Nw74CTsOVw7Q4wqoAwoM/FV41w5LChsOkVh1cF0HDo1rCsF4mw4LDqsO+w51pHmzCsSvDmBYew4zCgw3CjQ7DjTPDn8OPIH/Dv8O8BwzDkMO7ecKJGcKeRhnCh1LDisKiwr3Ck3pFworCsMO5AcK5wq49wqXDiQFPNXnClcKOwrzCsMOcLsKaelYQw7vCsMK+L08Lwo7CssOxY3tbwpsLUCfDh8OuT8K6w5HCsmgkwp8YSsOqwrHCsSNTw5VREhXDqSbDmGVIKWbCmsOeLsKfw5jCug7DvSXCh1bCksKUwrQdccKAwpJKw41tw7oRRSN5w5FTAcKjwrfCrCkRXsKYwqvDmwTDn8KFwqszw6tFwobDrzZ5wqLCq8OgwqRJfw3DjMOOCWw3bCDDqWF9HMO7K8OjVjM7SUfCizLDphvDtg3DnsOZAVrCgQvDg8OrwpDDrsOmFmTDhcOrYhjCqDs9wqbCmMKsGcOEHMKBw4LCusOHw7HDnFrCgsKoZW/CkkN4wpfDkGXDucOGHsK0wr1Sw6cswo/Dn2/DqHcAw7jCnWnDjm4mw67DpMOVZjw/wo4cw6DDkMOWeS8AUsOOw55HHcOHZsOCw481wr7ClMKLUMOHwpw0QnloOSTCh8KfwozCocKHw4rClARow44uwqoSwrzDngbCrFrCi8KTLcKoV8OLLcK3w6DCr2nCtEbDmMO2w6o1VcK3M3vCt2fDkMOfw7TChcOoOMOYCjXCicKSfsKqFMKSw4hAwp/CrhM2OVdgw61yTkQ4w6hpw7HCtRkkw7vDp3VQTgxpwpRfIsO7wo46w6/CtcK7J8K7QCfClgR1w5gTwqYuYcOrwrNVw5oWSsKKfsOGw4Upw6pdLMOaPsKwD1I1w7nDjcKUw5Eew5odwp10wrBvKMKHJ8Kwwr3DnMOAw6NvwqVId3XCn8KwJMKddEQpFgE3wos3XsKaw5Itw6PChMKGw6LClsOewqIUMcOHLXvDvUvCkMOQQGV8wrlRw6PClXsGwr7CssKnwonDi8KawrLCpzRpwrBhwq3Do8Kzw7vCjcKqwpoCS8ONFyXDmcOqwqTDkyvDom03VT45ZsKOw7gcwqnCsEfCrQLCu2nCgMO4wqvDjnDDvcOCwoHCssO1w6TDmMOhw5prAcK2wrZtw5XCnsKoHMO1w55hVMOQw4XDrEQnAsOGwqFAL8KAwrxswqzCo8O3worCsGklZh/CuMOEQsO4wrEsRytOOxIDw6/Do8K4PidIRsOGf8KAGMKfwr3DnMO6wqXDtsK7OWI5AMOyw6ocwrw1FFvDlzDDjsKwX8KTKxFgw6nDusO6Y1gkJCHDpw/DtSk+w6nDnHM/w7fDvcOIwrPDkcOQwqMsw47CrcOXwrVjRzzDnxHDmHjCiA==---END ENCRYPTED MESSAGE---||---BEGIN ENCRYPTED RANDOM KEY--------BEGIN PGP MESSAGE-----\n"
    "Version: OpenPGP.js v0.9.0\n"
    "Comment: http://openpgpjs.org\n"
    "\n"
    "wcBMA2tjJVxNCRhtAQf8DrhLlPg73Uk9Bz8ovzGm8jcdNlY23yZyqzIW5V13\n"
    "BweV02G90XxI90gIp/Qjz7d8CwlsdCZutMgDS6+6rohGs4LEOX8q3TuyYG1s\n"
    "9wTWf9is4j+WX/prr2dRvDhBbusMwSYh/HfRLo3+R96JGBdPtjXA5zp4Fz3R\n"
    "xVBRO4bkQsd2gE5e0v1WAryq9HryzNG3Of+kItMAdlrKjO6mry7UQ7FB16wo\n"
    "gqefGhq9H+cQ1BEzf77oXSFhGwQk0EBl4h6vi1zeYFmoyjbfFDSLN0PBAriP\n"
    "z3msrI8baP2YOy6GyaXD7wylPvYcRbTAHWKPF2wKsWdz6T9GaGOnZNf2a50k\n"
    "TtKAAYmz+dS1D3RTiOmcl1sGQE+XkdieW9RjsNosMaFXFovbri+djVSUgm2W\n"
    "oMTc4Njf0W9zP0ertSY+cGt9+I3ErAn0jGL1SmJY1L6tc5wybDGtkCusyDje\n"
    "qHBl67f/+Gr5H38cG2dBvv+8T+E6J5anlHoblPMDHG3aurP1eXH7SAI=\n"
    "=DP9D\n"
    "-----END PGP MESSAGE-----\n"
    "---END ENCRYPTED RANDOM KEY---";
    
    NSString* plain_text = [pgp decrypt_message:test_msg error:nil];
    
    NSString* encrypt_msg = [pgp encrypt_message:plain_text pub_key:public_key_ error:nil];
    
    NSString* decrypt = [pgp decrypt_message:encrypt_msg error:nil];
    NSLog(@"%@", decrypt);
    
    NSError * error = nil;
    plain_text = [pgp decrypt_message:@"afdsf" error:&error];
    
    encrypt_msg = [pgp encrypt_message:@"afdsf" pub_key:public_key_ error:nil];
    
    NSLog(@"%@", encrypt_msg);
    
    decrypt = [pgp decrypt_message:encrypt_msg error:nil];
    
    
    NSLog(@"%@", decrypt);
}


@end
