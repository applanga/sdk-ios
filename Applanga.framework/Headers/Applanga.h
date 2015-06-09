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

/** get localized string for current language and given key
 */
+ (NSString*)localizedStringForKey:(NSString*)key;

/** get localized string for given key and language
 */
+ (NSString*)localizedStringForKey:(NSString*)key andLanguage:(NSString*)languageName;

/** reset the instance and saved values
 */
+ (void)reset;

/** get current sdk version
 */
+ (NSString*)sdkVersion;

@end
