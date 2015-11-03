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

/** Applanga
 */
@interface Applanga : NSObject

typedef NS_ENUM(NSInteger, ALPluralRule) {
    ALPluralRuleZero = 0,
    ALPluralRuleOne,
    ALPluralRuleTwo,
    ALPluralRuleFew,
    ALPluralRuleMany,
    ALPluralRuleOther
};

/** get pluralisation rule for current language and given quantity based on:
 *  http://unicode.org/repos/cldr-tmp/trunk/diff/supplemental/language_plural_rules.html
 */
extern ALPluralRule ALPluralRuleForQuantity(NSUInteger quantity);

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
+ (NSString*)localizedStringForKey:(NSString*)key;

/** get localized string for given key and arguments
 */
+ (NSString*)localizedStringForKey:(NSString*)key withArguments:(NSDictionary*)arguments;

/** get localized string for given key, arguments and pluralisation
 */
+ (NSString*)localizedStringForKey:(NSString*)key withArguments:(NSDictionary*)arguments andPluralRule:(ALPluralRule)pluralRule;

/** override phone language with custom language
 */
/*+ (void)setLanguage:(NSString*)language;*/

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
#define ALLocalizedString(key) [Applanga localizedStringForKey:key]
#endif

#ifndef ALLocalizedStringWithArgs
#define ALLocalizedStringWithArgs(key, args) [Applanga localizedStringForKey:key withArguments:args]
#endif

#ifndef ALLocalizedStringWithPluralRule
#define ALLocalizedStringWithPluralRule(key, rule) [Applanga localizedStringForKey:key withArguments:nil andPluralRule:rule]
#endif

#ifndef ALLocalizedStringWithQuantity
#define ALLocalizedStringWithQuantity(key, quantity) [Applanga localizedStringForKey:key withArguments:nil andPluralRule:ALPluralRuleForQuantity(quantity)]
#endif

#ifndef ALLocalizedStringWithPluralRuleAndArgs
#define ALLocalizedStringWithPluralRuleAndArgs(key, rule, args) [Applanga localizedStringForKey:key withArguments:args andPluralRule:rule]
#endif

#ifndef ALLocalizedStringWithQuantityAndArgs
#define ALLocalizedStringWithQuantityAndArgs(key, quantity, args) [Applanga localizedStringForKey:key withArguments:args andPluralRule:ALPluralRuleForQuantity(quantity)]
#endif

#ifndef ALSdkVersion
#define ALSdkVersion() [Applanga sdkVersion]
#endif

