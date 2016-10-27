//
//  ViewController.h
//  ObjectiveC_Test
//
//  Created by Yanfeng Zhang on 1/29/15.
//  Copyright (c) 2015 Yanfeng Zhang. All rights reserved.
//

#import <UIKit/UIKit.h>

@interface ViewController : UIViewController

- (IBAction)large_test_clicked:(id)sender;
- (IBAction)tiny_test_clicked:(id)sender;

- (IBAction)decrypt_test_clicked:(id)sender;



@property (weak, nonatomic) IBOutlet UILabel *log_lable;

@property (nonatomic, strong) NSString* private_key_;
@property (nonatomic, strong) NSString* public_key_;
-(NSString*)encodeURIComponent:(NSString*)str;
@end

