//
//  applanga.h
//  applanga
//
//  Created by Steffen Römer on 03/12/14.
//  Copyright (c) 2015 Mbaas Development GmbH. All rights reserved.
//

#import <Foundation/Foundation.h>

/** Applanga allows your app to communicate with the Applanga backend.
 */
@interface Applanga : NSObject

/**  manually trigger a localisation update.
 @param completionHandler handler that gets triggered when the localisation update finishes
 */
+ (void)localizeWithCompletionHandler:(void (^)(BOOL success))completionHandler;

/** get current sdk version
 */
+ (NSString*)sdkVersion;
@end
