//
//  applanga.h
//  applanga
//
//  Created by Steffen Römer on 03/12/14.
//  Copyright (c) 2014 Mbaas Development GmbH. All rights reserved.
//

#import <Foundation/Foundation.h>

@interface Applanga : NSObject
+ (void)localizeWithCompletionHandler:(void (^)(BOOL success))completionHandler;
+ (NSString*)sdkVersion;
@end
