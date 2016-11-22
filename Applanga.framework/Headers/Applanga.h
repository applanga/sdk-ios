//
//  Applanga.h
//  Applanga
//
//  https://www.applanga.com
//
//  Created by Steffen Römer on 03/12/14.
//  Copyright (c) 2015 Mbaas Development GmbH. All rights reserved.
//

#import <Foundation/Foundation.h>

typedef NS_ENUM(NSInteger, ALPluralRule) {
    ALPluralRuleZero = 0,
    ALPluralRuleOne,
    ALPluralRuleTwo,
    ALPluralRuleFew,
    ALPluralRuleMany,
    ALPluralRuleOther
};

/** Applanga
 */
@interface Applanga : NSObject

/** get pluralisation rule for current language and given quantity based on:
 *  http://unicode.org/repos/cldr-tmp/trunk/diff/supplemental/language_plural_rules.html
 */
ALPluralRule ALPluralRuleForQuantity(NSUInteger quantity);

/**  manually fetch latest localisation updates from Applanga
 @param completionHandler handler that gets triggered when the localisation update finishes
 */
+ (void)updateWithCompletionHandler:(void (^)(BOOL success))completionHandler;

/**  manually fetch latest localisation updates from Applanga for given group and languages
 @param completionHandler handler that gets triggered when the localisation update finishes
 */
+ (void)updateGroups:(NSArray*)groups andLanguages:(NSArray*)languages withCompletionHandler:(void (^)(BOOL success))completionHandler;


/** get localized string for current language and given key
 */
+ (NSString*)localizedStringForKey:(NSString*)key withDefaultValue:(NSString*)value;
+ (NSString*)localizedStringForKey:(NSString*)key __attribute__((deprecated));

/** get localized string for given key and arguments
 */
+ (NSString*)localizedStringForKey:(NSString*)key withDefaultValue:(NSString*)value andArguments:(NSDictionary*)arguments;
+ (NSString*)localizedStringForKey:(NSString*)key withArguments:(NSDictionary*)arguments __attribute__((deprecated));

/** get localized string for given key, arguments and pluralisation
 */
+ (NSString*)localizedStringForKey:(NSString*)key withDefaultValue:(NSString*)value andArguments:(NSDictionary*)arguments andPluralRule:(ALPluralRule)pluralRule;
+ (NSString*)localizedStringForKey:(NSString*)key withArguments:(NSDictionary*)arguments andPluralRule:(ALPluralRule)pluralRule __attribute__((deprecated));

+ (void)captureScreenshotWithTag:(NSString*)tag andIDs:(NSArray*)applangaIDs;

+ (void)captureScreenshotWithTag:(NSString*)tag andIDs:(NSArray*)applangaIDs withCompletionHandler: (void (^)(BOOL success))completionHandler;

+ (BOOL)setScreenShotMenuVisible:(BOOL)visible;

/** change phone language to new language
 */
+ (BOOL)setLanguage:(NSString*)language;


/** reset the instance and saved values
 */
+ (void)reset;

/** get current sdk version
 */
+ (NSString*)sdkVersion;

@end

#ifndef ALLocalizedString
#define ALLocalizedString(key, defaultValue) [Applanga localizedStringForKey:key withDefaultValue:defaultValue]
#endif

#ifndef ALLocalizedStringWithArgs
#define ALLocalizedStringWithArgs(key, defaultValue, args) [Applanga localizedStringForKey:key withDefaultValue:defaultValue andArguments:args]
#endif

#ifndef ALLocalizedStringWithPluralRule
#define ALLocalizedStringWithPluralRule(key, defaultValue, rule) [Applanga localizedStringForKey:key withDefaultValue:defaultValue andArguments:nil andPluralRule:rule]
#endif

#ifndef ALLocalizedStringWithQuantity
#define ALLocalizedStringWithQuantity(key, defaultValue, quantity) [Applanga localizedStringForKey:key withDefaultValue:defaultValue andArguments:nil andPluralRule:ALPluralRuleForQuantity(quantity)]
#endif

#ifndef ALLocalizedStringWithPluralRuleAndArgs
#define ALLocalizedStringWithPluralRuleAndArgs(key, defaultValue, rule, args) [Applanga localizedStringForKey:key withDefaultValue:defaultValue andArguments:args andPluralRule:rule]
#endif

#ifndef ALLocalizedStringWithQuantityAndArgs
#define ALLocalizedStringWithQuantityAndArgs(key, defaultValue, quantity, args) [Applanga localizedStringForKey:key withDefaultValue:defaultValue andArguments:args andPluralRule:ALPluralRuleForQuantity(quantity)]
#endif


