/****************************************************************************
 Copyright (c) 2010 cocos2d-x.org
 
 http://www.cocos2d-x.org
 
 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:
 
 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.
 
 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
 ****************************************************************************/
#import <UIKit/UIKit.h>
#import "AppController.h"
#import "cocos2d.h"
#import "CCEAGLView.h"
#import "AppDelegate.h"
#import "NSCCConverter.h"

#import "RootViewController.h"

#import "ImagePicker.h"
#import "FenneX.h"
#import "Flurry.h"
#import "AppMacros.h"
#import "TestFlight.h"
#include "NativeUtility.h"
#include "Shorteners.h"

static AppController* _sharedController = NULL;

@implementation AppController

#pragma mark -
#pragma mark Application lifecycle

@synthesize window;
@synthesize viewController;

// cocos2d application instance
static AppDelegate s_sharedApplication;

+ (AppController*) sharedController
{
    return _sharedController;
}

- (void) sendMail:(NSString*)address subject:(NSString*)subject message:(NSString*)message attachment:(NSString*)attachment
{
    [self.viewController setModalTransitionStyle: UIModalTransitionStyleCoverVertical];
    
    
    MFMailComposeViewController *mailer = [[MFMailComposeViewController alloc] init];
    //If mailer is NULL, it means the user didn't set up a mail account, and he will be warned by iOS
    if(mailer != NULL)
    {
        mailer.mailComposeDelegate = self;
        
        [mailer setSubject:subject];
        
        NSArray *toRecipients = [NSArray arrayWithObject:address];
        [mailer setToRecipients:toRecipients];
        
        [mailer setMessageBody:message isHTML:NO];
        if(attachment != nil)
        {
            NSArray *paths = NSSearchPathForDirectoriesInDomains(NSDocumentDirectory, NSUserDomainMask, YES);
            NSString *documentsPath = [paths objectAtIndex:0];
            NSLog(@"Documents path : %@", documentsPath);
            NSLog(@"with getenv : %s/Documents/%@", getenv("HOME"), attachment);
            NSString* path= [NSString stringWithFormat:@"%s/Documents/%@", getenv("HOME"), attachment];
            
            NSLog(@"Path : %@", path);
            
            [mailer addAttachmentData:[NSData dataWithContentsOfFile:path] mimeType:@"application/xml" fileName:@"results.plist"];
        }
        [self.viewController presentModalViewController:mailer animated:YES];
        
        [mailer release];
    }
}

- (void) mailComposeController:(MFMailComposeViewController*)controller didFinishWithResult:(MFMailComposeResult)result error:(NSError*)error
{
    switch (result)
    {
        case MFMailComposeResultCancelled:
            NSLog(@"Mail cancelled: you cancelled the operation and no email message was queued.");
            CCNotificationCenter::sharedNotificationCenter()->postNotification("MailCanceled");
            break;
        case MFMailComposeResultSaved:
            NSLog(@"Mail saved: you saved the email message in the drafts folder.");
            CCNotificationCenter::sharedNotificationCenter()->postNotification("MailSaved");
            break;
        case MFMailComposeResultSent:
            NSLog(@"Mail send: the email message is queued in the outbox. It is ready to send.");
            CCNotificationCenter::sharedNotificationCenter()->postNotification("MailSent");
            break;
        case MFMailComposeResultFailed:
            NSLog(@"Mail failed: the email message was not saved or queued, possibly due to an error.");
            CCNotificationCenter::sharedNotificationCenter()->postNotification("MailFailed");
            break;
        default:
            NSLog(@"Mail not sent.");
            CCNotificationCenter::sharedNotificationCenter()->postNotification("MailNotSent");
            break;
    }
	
	// Remove the mail view
    [self.viewController dismissModalViewControllerAnimated:YES];
}

void uncaughtExceptionHandler(NSException *exception)
{
    [Flurry logError:@"Uncaught" message:@"Crash!" exception:exception];
}

- (BOOL)application:(UIApplication *)application didFinishLaunchingWithOptions:(NSDictionary *)launchOptions
{
    //NSSetUncaughtExceptionHandler(&uncaughtExceptionHandler);
    // Override point for customization after application launch.
    _sharedController = self;
    
    // Add the view controller's view to the window and display.
    window = [[UIWindow alloc] initWithFrame: [[UIScreen mainScreen] bounds]];
    CCEAGLView *eaglView = [CCEAGLView viewWithFrame: [window bounds]
                                     pixelFormat: kEAGLColorFormatRGBA8
                                     depthFormat: GL_DEPTH24_STENCIL8_OES
                              preserveBackbuffer: NO
                                      sharegroup:nil
                                   multiSampling:NO
                                 numberOfSamples:0];
    [eaglView setMultipleTouchEnabled:YES];
    
    // Use RootViewController manage EAGLView
    viewController = [[RootViewController alloc] initWithNibName:nil bundle:nil];
    viewController.wantsFullScreenLayout = YES;
    viewController.view = eaglView;
    
    // Set RootViewController to window
    if ( [[UIDevice currentDevice].systemVersion floatValue] < 6.0)
    {
        // warning: addSubView doesn't work on iOS6
        [window addSubview: viewController.view];
    }
    else
    {
        // use this method on ios6
        [window setRootViewController:viewController];
    }
    
    
    [window makeKeyAndVisible];
    
    [[UIApplication sharedApplication] setStatusBarHidden: YES];
    
    // IMPORTANT: Setting the GLView should be done after creating the RootViewController
    cocos2d::GLView *glview = cocos2d::GLView::createWithEAGLView(eaglView);
    cocos2d::Director::getInstance()->setOpenGLView(glview);
    
    cocos2d::Application::getInstance()->run();
    
#ifdef TESTFLIGHT_TOKEN
#if DEBUG_ANALYTICS
    [TestFlight takeOff:TESTFLIGHT_TOKEN];
#else
    NSLog(@"Not in debug mode, not launching testflight");
#endif
#else
    NSLog(@"TestFlight token not defined, not launching it");
#endif
    
    NSLog(@"app launch");
    if([launchOptions objectForKey:UIApplicationLaunchOptionsLocalNotificationKey] != NULL)
    {
        UILocalNotification* notif = [launchOptions objectForKey:UIApplicationLaunchOptionsLocalNotificationKey];
        if([notif.userInfo objectForKey:@"CallbackEvent"] != nil)
        {
            NSLog(@"local notif with callback event");
            performNotificationAfterDelay([[notif.userInfo objectForKey:@"CallbackEvent"] UTF8String], [NSCCConverter ccDictionaryFromNSDictionary:notif.userInfo], 0.01);
        }
    }
    return YES;
}

- (void)application:(UIApplication *)application didReceiveLocalNotification:(UILocalNotification*)notif
{
    if (application.applicationState == UIApplicationStateActive) {
        NSLog(@"receive local notif in UIApplicationStateActive : do not intercept notification");
    }
    else if(application.applicationState == UIApplicationStateInactive){
        NSLog(@"receive local notif in UIApplicationStateInActive : receive local notif");
        //[[NSUserDefaults standardUserDefaults] removeObjectForKey:@"ExitDate"];
        if([notif.userInfo objectForKey:@"CallbackEvent"] != nil)
        {
            NSLog(@"local notif with callback event");
            CCNotificationCenter::sharedNotificationCenter()->postNotification([[notif.userInfo objectForKey:@"CallbackEvent"] UTF8String], [NSCCConverter ccDictionaryFromNSDictionary:notif.userInfo]);
        }
    }
}


- (void)applicationWillResignActive:(UIApplication *)application {
    /*
     Sent when the application is about to move from active to inactive state. This can occur for certain types of temporary interruptions (such as an incoming phone call or SMS message) or when the user quits the application and it begins the transition to the background state.
     Use this method to pause ongoing tasks, disable timers, and throttle down OpenGL ES frame rates. Games should use this method to pause the game.
     */
    //cocos2d::CCDirector::sharedDirector()->pause();
    cocos2d::NotificationCenter::sharedNotificationCenter()->postNotification("AppWillResignActive");
}

- (void)applicationDidBecomeActive:(UIApplication *)application {
    /*
     Restart any tasks that were paused (or not yet started) while the application was inactive. If the application was previously in the background, optionally refresh the user interface.
     */
    //cocos2d::CCDirector::sharedDirector()->resume();
}

- (void)applicationDidEnterBackground:(UIApplication *)application {
    /*
     Use this method to release shared resources, save user data, invalidate timers, and store enough application state information to restore your application to its current state in case it is terminated later.
     If your application supports background execution, called instead of applicationWillTerminate: when the user quits.
     */
    cocos2d::CCApplication::sharedApplication()->applicationDidEnterBackground();
}

- (void)applicationWillEnterForeground:(UIApplication *)application {
    /*
     Called as part of  transition from the background to the inactive state: here you can undo many of the changes made on entering the background.
     */
    cocos2d::CCApplication::sharedApplication()->applicationWillEnterForeground();
}

- (void)applicationWillTerminate:(UIApplication *)application {
    /*
     Called when the application is about to terminate.
     See also applicationDidEnterBackground:.
     */
}

- (NSUInteger)application:(UIApplication *)application supportedInterfaceOrientationsForWindow:(UIWindow *)w {
    /*
     Avoid crash with UIImagePicker because UIImagePicker doesn't support UIInterfaceOrientationLandscape
     */
    return (NSUInteger)[application supportedInterfaceOrientationsForWindow:w] | (1<<UIInterfaceOrientationPortrait);
}


#pragma mark -
#pragma mark Memory management

- (void)applicationDidReceiveMemoryWarning:(UIApplication *)application {
    notifyMemoryWarning();
}


- (void)dealloc {
    _sharedController = NULL;
    [super dealloc];
}


@end
