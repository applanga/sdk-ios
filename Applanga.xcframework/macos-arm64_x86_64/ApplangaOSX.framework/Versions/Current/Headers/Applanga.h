//
//  Applanga.h
//  Applanga
//
//  https://www.applanga.com
//
//  Created by Steffen Römer on 03/12/14.
//  Copyright (c) 2018 Mbaas Development GmbH. All rights reserved.
//

#import <Foundation/Foundation.h>

/** Languages vary in how they handle plurals of nouns or unit expressions ("hour" vs "hours", and so on). Some languages have two forms, like English; some languages have only a single form; and some languages have multiple forms.
 @see http://cldr.unicode.org/index/cldr-spec/plural-rules
 @see http://www.unicode.org/cldr/charts/latest/supplemental/language_plural_rules.html
 */
typedef NS_ENUM(NSInteger, ALPluralRule) {
    /** Zero Form */ALPluralRuleZero = 0,
    /** Singular Form */ALPluralRuleOne,
    /** Dual Form */ALPluralRuleTwo,
    /** Paucal Form */ALPluralRuleFew,
    /** also used for fractions if they have a separate class */ALPluralRuleMany,
    /** general plural form—also used if the language only has a single form */ALPluralRuleOther
};

/** Some Plugins have special ways to store and retrieve String position informations on the screen and this interface is used to provide this
*/
@protocol ApplangaScreenshotInterface <NSObject>
@required
- (void)getStringPositions:(void (^)(NSString* result))completionHandler;
@end


/** Applanga Interface Specification
 *
 * *NOTE:* In most cases you do not need to manually call any of the Applanga methods and you can simply use [NSLocalizedStringWithDefaultValue(@“APPLANGA_ID”, nil, NSBundle.mainBundle, @“default value”, @“”)](https://developer.apple.com/reference/foundation/nslocalizedstringwithdefaultvalue)
 *
 * *Website*: [https://www.applanga.com](https://applanga.com)
 *
 * *Platform Docs*: [https://www.applanga.com/docs](https://www.applanga.com/docs)
 *
 * *Integration Docs*: [https://www.applanga.com/docs-integration/ios](https://www.applanga.com/docs-integration/ios)
 *
 * ---
 */
@interface Applanga : NSObject

/** get ALPluralRule pluralisation rule for current language and given quantity based on:
 @see http://cldr.unicode.org/index/cldr-spec/plural-rules
 @see http://www.unicode.org/cldr/charts/latest/supplemental/language_plural_rules.html
 */
ALPluralRule ALPluralRuleForQuantity(NSUInteger quantity);

/**  manually fetch latest localization updates from Applanga
 @param completionHandler handler that gets triggered when the localization update finishes
 */
+ (void)updateWithCompletionHandler:(void (^)(BOOL success))completionHandler;

/**  manually fetch latest localization updates from Applanga for given group and languages
 @param groups array with groups that should be updated (nil defaults to 'main' group)
 @param languages array of languages that should be updated (nil defaults to current + base langauge)
 @param completionHandler handler that gets triggered when the localization update finishes
 */
+ (void)updateGroups:(NSArray*)groups andLanguages:(NSArray*)languages withCompletionHandler:(void (^)(BOOL success))completionHandler;


/** get localized string for current language and given key
 @param key the string key from Applanga
 @param value the defaultvalue that should be used if the key does not exist or is empty (the default value will also be uploaded to Applanga)
 */
+ (NSString*)localizedStringForKey:(NSString*)key withDefaultValue:(NSString*)value;

/** *!!!DEPRECATED!!!* please see: localizedStringForKey:withDefaultValue:
 @param key the string key from Applanga
 */
+ (NSString*)localizedStringForKey:(NSString*)key __attribute__((deprecated));

/** get localized string for given key, defaultValue and arguments
 @param key the string key from Applanga
 @param value the defaultvalue that should be used if the key does not exist or is empty (the default value will also be uploaded to Applanga)
 @param arguments dictionary with named arguments that will be replaced int the string
 */
+ (NSString*)localizedStringForKey:(NSString*)key withDefaultValue:(NSString*)value andArguments:(NSDictionary*)arguments;

/** *!!!DEPRECATED!!!* please see: localizedStringForKey:withDefaultValue:andArguments:
 @param key the string key from Applanga
 @param arguments dictionary with named arguments that will be replaced int the string
 */
+ (NSString*)localizedStringForKey:(NSString*)key withArguments:(NSDictionary*)arguments __attribute__((deprecated));

/** get localized string for given key, arguments and pluralisation
 @param key the string key from Applanga
 @param value the defaultvalue that should be used if the key does not exist or is empty (the default value will also be uploaded to Applanga)
 @param arguments dictionary with named arguments that will be replaced int the string
 @param pluralRule the pluralisation / ALPluralRule that should be used
 */
+ (NSString*)localizedStringForKey:(NSString*)key withDefaultValue:(NSString*)value andArguments:(NSDictionary*)arguments andPluralRule:(ALPluralRule)pluralRule;

/** *!!!DEPRECATED!!!* please see: localizedStringForKey:withDefaultValue:andArguments:andPluralRule:
 @param key the string key from Applanga
 @param arguments dictionary with named arguments that will be replaced int the string
 @param pluralRule the pluralisation / ALPluralRule that should be used
 */
+ (NSString*)localizedStringForKey:(NSString*)key withArguments:(NSDictionary*)arguments andPluralRule:(ALPluralRule)pluralRule __attribute__((deprecated));

/** *!!!SLOW!!!* should not be used often
 * returns a list of all localized strings for given language
 @param language the language iso code
 */
+ (NSDictionary*)localizedStringsForLanguage:(NSString*)language;

/** *!!!SLOW!!!* should not be used often
 * returns a list of all localized strings for current language
 */
+ (NSDictionary*)localizedStringsForCurrentLanguage;

+ (NSDictionary*) localizeMap:(NSDictionary*)map;

/** capture a screenshot, upload it and link it to the given tag and ids
 @param tag the tag this screenshot should be assigned to
 @param applangaIDs optional array of ids that should be linked in this screenshot
 */
+ (void)captureScreenshotWithTag:(NSString*)tag andIDs:(NSArray*)applangaIDs;

/** capture a screenshot, upload it and link it to the given tag and ids
 @param tag the tag this screenshot should be assigned to
 @param applangaIDs optional array of ids that should be linked in this screenshot
 @param enableOcr Enable OCR processing on the applanga backend
 */
+ (void)captureScreenshotWithTag:(NSString*)tag andIDs:(NSArray*)applangaIDs useOcr:(BOOL)enableOcr;

/** capture a screenshot, upload it and link it to the given tag and ids
 @param tag the tag this screenshot should be assigned to
 @param applangaIDs optional array of ids that should be linked in this screenshot
 @param enableOcr Enable OCR processing on the applanga backend
 */
+ (void)captureScreenshotWithTag:(NSString*)tag andIDs:(NSArray*)applangaIDs useOcr:(BOOL)enableOcr withCompletionHandler: (void (^)(BOOL success))completionHandler;

/** capture a screenshot, upload it and link it to the given tag and ids
 @param tag the tag this screenshot should be assigned to
 @param applangaIDs optional array of ids that should be linked in this screenshot
 */
+ (void)captureScreenshotWithTag:(NSString*)tag andIDs:(NSArray*)applangaIDs withCompletionHandler: (void (^)(BOOL success))completionHandler;

/** show the tag selection menu to capture a screenshot for a tag
 @param visible boolean that indicates if menu should be visible(TRUE) or invisible (FALSE)
 */
+ (BOOL)setScreenShotMenuVisible:(BOOL)visible;

/** show the dialog to enable or disable draft mode
 */
+ (void)showDraftModeDialog;

/** change phone language to new language
 @param language the language iso code
 */
+ (BOOL)setLanguage:(NSString*)language;

/** enable or disable Applanga
 @param enabled true if applanga should be active (default)
 */
+ (void)setEnabled:(BOOL)enabled;

/** is Applanga set to be enabled (default: true)
 */
+ (BOOL)enabled;

/** Applanga set draft mode enabled 
*/
+ (void)setDraftModelEnabled:(BOOL)enabled;

/**Some Plugins have special ways to store and retrieve String position informations on the screen and this interface is used to provide this
 @param screenshotInterface ApplangaScreenshotInterface custom Protocol implementation to pass string position information when a screenshot is taken
 */
+ (void)setScreenshotInterface:(id<ApplangaScreenshotInterface>)screenshotInterface;

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


