# Applanga SDK for iOS Localization
***
*Version:* 2.0.205

*Website:* <https://www.applanga.com> 

*Changelog:* <https://www.applanga.com/changelog/ios>
***


## Table of Contents

  1. [Installation](#installation)
  2. [Configuration](#configuration)
  3. [Usage](#usage)
  4. [Optional settings](#optional-settings)
  5. [Localize Push Notifications & Info.plist](#automatic-push-notification-localization-and-infoplist-strings)
  6. [SwiftUI](#swiftui)
  7. [WatchOS](#watchos)
  8. [MacOS](#macos)
  9. [Branching](#branching)


Automatic Push Notification Localization and InfoPlist.strings

## Installation
#### CocoaPods [[?](http://cocoapods.org)]

1. Refer to CocoaPod’s [Getting Started Guide](http://cocoapods.org/#getstarted) for detailed instructions about CocoaPods.

2. After you have created your Podfile, insert this line of code: `pod 'Applanga'`, to be able to do screenshots during UI Tests insert `pod 'ApplangaUITest'` for your UI Test Target.

3. Once you have done so, re-run **pod install** from the command line.

#### Carthage [[?](https://github.com/Carthage/Carthage)]
1. If you are new to Carthage, please refer to their [documentation](https://github.com/Carthage/Carthage#installing-carthage) first.

2. Add the following line to your Cartfile:

	```
	binary "https://raw.githubusercontent.com/applanga/sdk-ios/master/Applanga.json" ~> 2.0
	```

3. Run `carthage update` from the command line and link the ***Applanga.framework*** to your project as it is described in the carthage documentation: [Getting started for iOS](https://github.com/Carthage/Carthage#if-youre-building-for-ios-tvos-or-watchos).

#### Swift Package Manager [[?](https://swift.org/package-manager/)]

##### NOTE: This is only supported in Xcode versions 12+

1: Simply add the repo url https://github.com/applanga/sdk-ios as a swift package dependency, and select the latest release tag 

#### Manual (zero-code)

1. If you want to translate your iOS app download the latest release of the Applanga iOS SDK from [Github](https://github.com/applanga/sdk-ios/releases). Unzip it, then drag and drop Applanga.framework into into the `Embedded Binaries` section of your target and check the "Copy items into destination group’s folder (if needed)" option.

2. Under the ***Build Settings*** tab, you need to change ***Basic*** to ***All*** and search for ***Other Linker Flags***. Double click on the white space to the right of Other Linker Flags and a popup will open. Click the plus (+), and add ***-ObjC, -lsqlite3, -lz***.

3. To be able to properly upload your app to iTunesConnect you need to work around an App Store submission bug triggered by universal binaries. To do that add a new `Run Script Phase` in your target’s `Build Phases`. **IMPORTANT:** Make sure this `Run Script Phase` is below the `Embed Frameworks` build phase.
You can drag and drop build phases to rearrange them.
Paste the following line in this `Run Script Phase`'s script text field:

	```bash
	bash "$BUILT_PRODUCTS_DIR/$FRAMEWORKS_FOLDER_PATH/Applanga.framework/strip-framework.sh"
	```
 
## Configuration
1. To start iOS Localization with Applanga download the *Applanga Settings File* for your app from the Project Overview in the dashboard by clicking the ***[Prepare Release]*** button and then clicking ***[Get Settings File]***.
 
2. Add the *Applanga Settings File* to your apps resources. It will be automatically loaded.
 
3. Now, if you start your app you should see a log message that confirms that Applanga was initialized or a warning in case of a missing configuration.

4. To make sure your settings file is always up to date for every build see the doc section about **Automatic Applanga Settings File update** in the **Optional settings**

---

###### *NOTE: To have native iOS dialogs properly translated and to show your supported languages on the Appstore you need to have atleast one .strings file bundled with your app for every language. (The file can be empty)*

---

## Usage
### Basic:

- Once Applanga is integrated and configured it synchronizes your local strings with the Applanga dashboard every time you start your app in [Debug Mode](https://developer.apple.com/library/content/documentation/DeveloperTools/Conceptual/debugging_with_xcode/chapters/debugging_tools.html) or [Draft Mode](https://www.applanga.com/docs/applanga-mobile-sdks/draft_on-device-testing) if new missing strings are found. Translations that you have stored in your *"Localizable.strings"* file or in *".strings""* that belong to storyboard or xib files of your app will be sent to the dashboard immediately. Applanga also auto detects your strings in storyboards and in the code once they are used.
Storyboards should be enabled for [Base Localization](https://developer.apple.com/library/ios/documentation/MacOSX/Conceptual/BPInternational/InternationalizingYourUserInterface/InternationalizingYourUserInterface.html#//apple_ref/doc/uid/10000171i-CH3-SW4). If you have additional *".strings"* files that should be automatically uploaded you can add them in your Info.plist with the key **ApplangaAdditionalStringFiles** & if you have parts of your code in additional *".framework"* bundles you can add them with the key **ApplangaAdditionalFrameworks** as a comma seperated lists. You don’t need to use any special code. 
	- With ***Objective-C*** use the native method ***[NSLocalizedStringWithDefaultValue(@"APPLANGA_ID", nil, NSBundle.mainBundle, @"default value", @"")](https://developer.apple.com/reference/foundation/nslocalizedstringwithdefaultvalue?language=objc)*** 
	
	- With ***Swift*** use ***[NSLocalizedString("APPLANGA_ID", value: "default value", comment: "")](https://developer.apple.com/reference/foundation/1418095-nslocalizedstring)*** like you are used to do.


---
###### *NOTE: If you do not specifiy a default value the string will not be created on the Applanga dashboard.*
---

### Extended:

Besides the Basic usage Applanga offers support for ***named arguments*** in your strings, ***pluralisation***, ***partial updates*** to save space and bandwith as well as translation of html and javascript content in ```UIWebView``` instances.

1. **Code Localization**
 
	1.1 **Strings** 
	
	```objc
	//objc
	// get translated string for the current device locale
	[Applanga localizedStringForKey:@"APPLANGA_ID" withDefaultValue:@"default value"];
	```
	
	```swift
	//swift
	Applanga.localizedString(forKey: "APPLANGA_ID", withDefaultValue: "default value")
	```

	1.2 **Named Arguments**
	
	```objc
	//objc
	// if you pass a string:string dictionary you can get translated string
	// with named arguments. %{someArg} %{anotherArg} etc.
	NSDictionary* args = @{@"someArg": @"awesome",@"anotherArg": @"crazy"};
	[Applanga localizedStringForKey:@"APPLANGA_ID" withDefaultValue:@"default value" andArguments:args]
	```
	
	```swift
	//swift
	var args: [String: String] = ["someArg": "awesome", "anotherArg": "crazy"];
	Applanga.localizedString(forKey: "APPLANGA_ID", withDefaultValue: "default", andArguments: args)
	```
	Example:
	
	*APPLANGA_ID* = *"This value of the argument called someArg is %{someArg} and the value of anotherArg is **%{anotherArg}**. You can reuse arguments multiple times in your text wich is **%{someArg}**, **%{anotherArg}** and **%{someArg}.**"*
	
	gets converted to:
	
	*"This value of the argument called someArg is awesome and the value of anotherArg is crazy. You can reuse arguments multiple times in your text wich is awesome, crazy and awesome."*	
		
	1.3 **Pluralisation**
	
	```objc
	//objc
	// get translated string in given pluralisation rule (one)
	[Applanga localizedStringForKey:@"APPLANGA_ID" withDefaultValue:@"default value" andArguments:nil andPluralRule:ALPluralRuleOne]
	```
	
	```swift
	//swift
	Applanga.localizedString(forKey: "no default", withDefaultValue: "default", andArguments: nil, andPluralRule: ALPluralRule.one)
	```
	
	Available pluralisation rules:
	
	```objc
	//objc
	ALPluralRuleZero,
	ALPluralRuleOne,
	ALPluralRuleTwo,
	ALPluralRuleFew,
	ALPluralRuleMany,
	ALPluralRuleOther
	```
	```swift
	//swift
	ALPluralRule.zero,
	ALPluralRule.one,
	ALPluralRule.two,
	ALPluralRule.few,
	ALPluralRule.many,
	ALPluralRule.other
	```
	you can also specify a quantity and Applanga will pick the best pluralisation rule based on: [http://unicode.org/.../language_plural_rules.html	](http://www.unicode.org/cldr/charts/latest/supplemental/language_plural_rules.html)
	
	```objc
	//objc
	// get a string in the given quantity
	[Applanga localizedStringForKey:@"APPLANGA_ID" withDefaultValue:@"default value" andArguments:nil andPluralRule:ALPluralRuleForQuantity(quantity)]

	// or get a formatted string with the given quantity
	[NSString localizedStringWithFormat:[Applanga localizedStringForKey:@"APPLANGA_ID" withDefaultValue:@"default value" andArguments:nil andPluralRule:ALPluralRuleForQuantity(quantity)], quantity]
	```
	```swift
	//swift
	// get a string in the given quantity
	Applanga.localizedString(forKey: "APPLANGA_ID", withDefaultValue: "default value", andArguments: nil, andPluralRule: ALPluralRuleForQuantity(quantity))
	
	//or get a formatted string with the given quantity
	NSString.localizedStringWithFormat(NSString(string:(Applanga.localizedString(forKey: "APPLANGA_ID", withDefaultValue: "default", andArguments: nil, andPluralRule: ALPluralRuleForQuantity(quantity)))), quantity)
	
	```
	In the dashboard you create a **puralized ID** by appending the Pluralisation rule to your **ID** in the following format: `[zero]`, `[one]`,`[two]`,`[few]`,`[many]`, `[other]`.
	
	So the ***zero*** pluralized ID for ***"APPLANGA_ID"*** is ***"APPLANGA_ID[zero]"***
		
2. **Update Content**
	
	To trigger an update call:
	
	```objc
	//objc
	[Applanga updateWithCompletionHandler:^(BOOL success) {
		//called if update is complete
	}];
	```
	
	```swift
	//swift
	Applanga.update { (success: Bool) in
		//called if update is complete
	}
	```

	This will request the baselanguage, the development language and the long and short versions of the device's current language. If you are using groups, be aware that this will only update the **main** group.
		
	To trigger an update for a specific set of groups and languages call:
	
	```objc
	//objc
	NSArray* groups = @[@"GroupA", @"GroupB"];
	NSArray* languages = @[@"en", @"de", @"fr"];
	 	
	[Applanga updateGroups:groups andLanguages:languages withCompletionHandler:^(BOOL success) {
		//called if update is complete
	}];
	```
	```swift
	//swift
	var groups: [String] = ["GroupA", "GroupB"]
	var languages: [String] = ["en", "de", "fr"]
	
	Applanga.updateGroups(groups, andLanguages: languages, withCompletionHandler:  {(success: Bool) in
		//called if update is complete
	})
	```

3. **Change Language**
 
  	You can change your app's language at runtime using the following call:
  	
	```objc
	//objc
	BOOL success = [Applanga setLanguage: language];
	```
	```swift
	//swift
	var success: Bool = Applanga.setLanguage(language)
	```
	*language* must be the iso string of a language that has been added in 	the dashboard. 
  	The return value will be *YES* if the language could be set, or if it already was the 	current language, otherwise it will be *NO*. 
  	The set language will be saved, to reset to the 	device language call:
  	
	```objc
	//objc
	Applanga.setLanguage(nil); 
	```
	```swift
	//swift
	Applanga.setLanguage(nil);
	```
  	After a successful call you need to reinitialize your UI for the changes to 	take effect, for example you might recreate the root Storyboard controller and present it.
  	
  	The *language* parameter is expected in the format **[language]-[region]** or 	**[language]_[region]** with region being optional. Examples: "fr_CA", "en-us", "de". 
  	
  	If you have problems switching to a specific language you can update your settings file 	or specifically request that language within an update content call (see **2. Update Content**). You can also 	specify the language as a default language to have it requested on each update call (see **Optional settings**).
  	
	```objc
	+ (void) changeAppLanguage:(NSString *)language {
			[Applanga updateGroups:nil andLanguages:@[language] withCompletionHandler:^( BOOL updateSuccess ){
			
			if(updateSuccess){
					BOOL languageChangedSuccess = [Applanga setLanguage:language];
				
					if(languageChangedSuccess) {
							//recreate ui
					} 
			} 
	}
	```
	
4. **WebViews**
	
	Applanga can also translate content in your WebViews if it is enabled.
	
	Add `ApplangaTranslateWebViews` set to `YES` to your Info.plist to enable translation support for all WebViews.
	
	There are some differences if you use the deprecated `UIWebView` or the newer `WKWebView` whereas direct Applanga calls in `UIWebView` ar synchronous but in `WKWebView` the need to be async.
	
	To initalize Applanga for your webcontent in a `UIWebView` you need to initialize Applanga from JavaScript like this:
	
	```javascript
	<script type="text/javascript">
		window.initApplanga = function() {
			if(typeof window.ApplangaNative !== 'undefined') { window.ApplangaNative.loadScript();
	  		} else { setTimeout(window.initApplanga, 180); } 
	  	}; window.initApplanga();
	</script>
	```
	
	This is not needed if you use a `WKWebView`.

	4.1 **Strings**
		
	The inner text and html of tags wich have a `applanga-text="APPLANGA_ID"` attribute will be replaced with the translated value of ***APPLANGA_ID***
	
	```html
	<div applanga-text="APPLANGA_ID">
			***This will be replaced with the value of APPLANGA_ID***
	</div>
	```
	
	Alternatively you can call `Applanga.getString` directly like this:
	
	```javascript
	//UIWebView
	translation = Applanga.getString('APPLANGA_ID')
	//WKWebView
	Applanga.getString('APPLANGA_ID', undefined, undefined,  undefined, undefined, undefined, 
	 function(translation) {
	})
	```
	
	4.2 **Arguments**
	
	You can pass arguments with the ```applanga-args``` attribute.
	By default the arguments are parsed as a comma seperated list wich then will replace fields as %{arrayIndex}. 
	
	```html
	<div applanga-text="APPLANGA_ID" applanga-args="arg1,arg2,etc">
		***This will be replaced with the value of APPLANGA_ID***
		***and formatted with arguments***
	</div>
	```
	Direct call: 
	
	```javascript
	//UIWebView
	translation = Applanga.getString('APPLANGA_ID', 'arg1,arg2,etc')
	//WKWebView
	Applanga.getString('APPLANGA_ID', 'arg1,arg2,etc', undefined,  undefined, undefined, undefined, 
	 function(translation) {
	})
	```
	
	To define a different separator instead of ```,``` e.g. if your arguments contain commas use ```applanga-args-separator```.
	
	```html
	<div applanga-text="APPLANGA_ID" 
		applanga-args="arg1;arg2;etc"
		applanga-args-separator=";">
			***This will be replaced with the value of APPLANGA_ID***
			***and formatted with arguments***
	</div> 
	```

	Direct call: 
	
	```javascript
	//UIWebView
	translation = Applanga.getString('APPLANGA_ID', 'arg1,arg2,etc', ';')
	//WKWebView
	Applanga.getString('APPLANGA_ID', 'arg1,arg2,etc', ';',  undefined,  undefined,  undefined, 
	 function(translation) {
	})
	```
		
	One Dimensional **JSON** Objects can also be used as ***Named Arguments*** if you add `applanga-args-separator="json"`
	
	```html
	<div applanga-text="APPLANGA_ID" 
		 applanga-args="{'arg1':'value1', 'arg2':'value2', 'arg3':'etc'}"
		 applanga-args-separator="json">
			***This will be replaced with the value of APPLANGA_ID***
			***and formatted with json arguments***
	</div> 
	```
	 Direct call: 
	 
	 ```javascript
	 //UIWebView
	 translation = Applanga.getString('APPLANGA_ID', "{'arg1':'value1', 'arg2':'value2', 'arg3':'etc'}", 'json')
	 //WKWebView
	 Applanga.getString('APPLANGA_ID', "{'arg1':'value1', 'arg2':'value2', 'arg3':'etc'}", 'json',  undefined,  undefined,  undefined, 
	  function(translation) {
	})
	 ```
	
	4.3 **Pluralisation**
		
	To pluralize a html tag you can pass the ```applanga-plural-rule``` attribute with the value `zero`, `one`, `two`, `few`, `many` and `other`.
	
	```html
	<div applanga-text="APPLANGA_ID" applanga-plural-rule="one">
		***This will be replaced with the pluralized value of APPLANGA_ID***
	</div> 
	```

	Direct call: 
	
	```javascript
	//UIWebView
	translation = Applanga.getPluralString('APPLANGA_ID', 'one')
	//WKWebView
	Applanga.getPluralString('APPLANGA_ID', 'one', undefined, undefined,
	 function(translation) {
	})
	``` 
	
	or with arguments: 	
	
	```javascript
	//UIWebView
	translation = Applanga.getPluralString('APPLANGA_ID', 'one', 'arg1;arg2;etc', ';')
	//WKWebView
	Applanga.getPluralString('APPLANGA_ID', 'one', 'arg1;arg2;etc', ';', 
	 function(translation) {
	})
	```
		
	You can also pluralize by quantity via `applanga-plural-quantity`

	```html
	<div applanga-text="APPLANGA_ID" applanga-plural-quantity=42>
		***This will be replaced with the pluralized value of APPLANGA_ID***
	</div> 
	```

	Direct call: 
	
	```javascript
	//UIWebView
	translation = Applanga.getQuantityString('APPLANGA_ID', 42)
	//WKWebView
	Applanga.getQuantityString('APPLANGA_ID', 42,  undefined, undefined, 
	 function(translation) {
	})
	```
	
	or with arguments:
	
	```javascript
	//UIWebView
	translation = Applanga.getQuantityString('APPLANGA_ID', 42, 'arg1;arg2;etc', ';')
	//WKWebView
	Applanga.getQuantityString('APPLANGA_ID', 42, 'arg1;arg2;etc', ';', 
	 function(translation) {
	})
	```

	4.4 **Update Content**
	
	To trigger a content update from a WebView use javascript:
	
	```javascript
	Applanga.updateGroups("GroupA, GroupB", "de, en, fr", function(success){
		//called if update is complete
	});		
	```
 
    4.5 **Enable Show ID Mode**

    ```javascript
    Applanga.setShowIdModeEnabled(true);
    ```

    If Show ID Mode is enabled, applanga will return your string ids instead of you localisations. This can become important for screenshots (especially SwiftUI as stated in automated screenshots with SwiftUI below). For instance if you have an argument string or any string which changes at runtime it is possible that this specific string won't be collected on a Screenshot. If Show ID Mode is activated, applanga can make an exact match of the string id so the screenshot string collection will be accurate. 

    Don't use this flag in Production. To be able to the see changes you have to reload your UI after changing this flag.

5. **Screenshot Capturing**
 	
 	To provide context for translation, the Applanga SDK offers 	functionality to upload screenshots of your app combined with meta data such as the current language, resolution and the strings that are visible, 	including their positions.
 	Each screenshot will be assigned to a tag. A tag may have multiple screenshots with 	differing core meta data: language, app version, device, platform, OS and resolution. 
 	You can read more here : [Work with Screenshots](https://www.applanga.com/docs/applanga-screenshots/screenshots-on-applanga) and here: [Upload Screenshot](https://www.applanga.com/docs/applanga-screenshots/uploading-screenshots).
 	
 	5.1 **Manual Screenshot Capture & Upload**
 	
 	To manually make a screenshot you first have to set your app into [draft mode](https://www.applanga.com/docs/translation-management-dashboard/draft_on-device-testing).
 	 
 	With your app in draft mode, all you have to do is to make a two finger swipe downwards.
 	This will show the screenshot menu and load a list of [tags](https://applanga.com/docs#manage_tags).
 	
 	You can now choose a tag and press *capture screenshot* to capture and upload a screenshot including all meta data for the currently visible screen and assign it to the selected tag.
 	Tags have to be created in the dashboard before they are available in the screenshot menu.

 	5.2 **Automatic Screenshot Capture & Upload via UITests**
 	
 	The screenshotting can be automated by either extending your existing UI Tests and capture a screenshot on every View or by creating a dedicated script that traverses your App an calls the Applanga screenshot capture method on each view.

    Please refer to [Installation](#Installation) how to add the `ApplangaUITest` package to your project.

 	To capture screenshots from UITests running in Xcode you first have to initialize Applanga with the current app instance so it can set specific launch arguments before starting the tests:

	```objc
	//objc
	XCUIApplication* app = [[XCUIApplication alloc] init];
	ApplangaUITest* applangaUITest = [[ApplangaUITest alloc] initWithApp:app enableShowIdMode:false];
	```
	```swift
	//swift 
	let app = XCUIApplication()
	let applangaUITest = ApplangaUITest(app: app)
	```
	
   To take a screenshot specify a tag/screen name and wait for the method to finish:
    
   ```objc
   //objc
   NSArray* expectations = [NSArray arrayWithObject:[self.applangaUITest takeScreenshotWithTag:@"ScreenName"]];
   [self waitForExpectations:expectations timeout:10];
   ```

   ```swift
	//swift 
	wait(for: [applangaUITest!.takeScreenshot(tag: "ScreenName")], timeout: 10.0)
	```
	
	Full example:
	
	```objc
	#import <ApplangaUITest-Swift.h>
	
	@interface MyUITestCase : XCTestCase
	@property ApplangaUITest *applangaUITest;
	@end
	
	@implementation MyUITestCase
	- (void)setUp {
		...
		XCUIApplication* app = [[XCUIApplication alloc] init];
		self.applangaUITest = [[ApplangaUITest alloc] initWithApp:app enableShowIdMode:false];
		[app launch];
	}
	
	- (void)testScreenshot {
		XCUIApplication *app = [[XCUIApplication alloc] init];
		
		NSArray* expectations = [NSArray arrayWithObject:[self.applangaUITest takeScreenshotWithTag:@"ScreenName1"]];
		[self waitForExpectations:expectations timeout:10];
		//navigate to next view
		...
		NSArray* expectations = [NSArray arrayWithObject:[self.applangaUITest takeScreenshotWithTag:@"ScreenName2"]];
		[self waitForExpectations:expectations timeout:10];
	}
	@end
	```
    ```swift
    import ApplangaUITest
    class AutomatedScreenshotsTest: XCTestCase {
        let app = XCUIApplication()
        var applangaUITest: ApplangaUITest?

        func testScreenshot() {
            // enable show id mode if you are using swift ui so the string id will be linked to the tag name correctly
            // after that repeat the screenshot without show id mode
            applangaUITest = ApplangaUITest(app: app, enableShowIdMode: false) 
            app.launch()
            wait(for: [applangaUITest!.takeScreenshot(tag: "ScreenName")], timeout: 10.0)
        }
    }
    ```

6. **Get available languages**

  	It is possible to get the currently added languages on the dashboard:
  	
	```objc
	//objc
	NSArray *languages = [Applanga availableLanguages];
	```
	```swift
	//swift
	let languages = Applanga.availableLanguages()
	```
	
	The result will contain the iso string of each language that has been added on the dashboard.
	These values are synced during the `Applanaga.update()` response. So to retrieve any changes to the available languages on the dashboard, an update() should be performed manually before using this list. 
		
## Optional settings

You can specify a set of default groups and languages in your plist, which will be updated on every Applanga.update() or Applanga.updateGroups() call. These groups and languages will be added to any that are specified in the call itself, they will *always* be requested.
	The Parameter value must be a string, with a list of groups or languages separated by commata.

1. **Specify default groups**

	```xml
	...
   <key>ApplangaUpdateGroups</key>
	<string>turorial,chapter1,chapter2</string>
	...
	```

2. **Specify default languages**

	```xml
	...
	<key>ApplangaUpdateLanguages</key>
	<string>en,de-at,fr</string>
	...
	```

3. **Disable upload of storyboard strings**
	You have the option to disable the collection of storyboard strings, by setting this value 	to false. This will not prevent the upload of localized .strings files that you may have 	created for your storyboard, but will stop the default upload of the cryptic string ids 	that are created for text ui elements in the storyboard.
	
	```xml
	...
	<key>ApplangaCollectStoryBoardStrings</key>
	<false/>
	...
	```
	

4. **Automatic Applanga Settings File update**

	In case your app's user has no internet connection, new translation updates can't be fetched, so the Applanga SDK falls back to the last locally cached version. If the app was started for the first time, there are no strings locally cached yet so Applanga SDK falls back to the Applanga Settings File which contains all strings from the moment it was generated, downloaded and integrated into your app before release. 

	The Applanga SDK comes with a python script called `settingsfile_update.py` which makes sure your app has always the latest settings file version. The script searches recursively for `*.applanga` files in your project and checks if a newer version is available. If so it replaces the old file with the newer Applanga Settings File from the Applanga backend. 
	
	In XCode you go to `Build Phases` and `New Run Script Phase` and add the following line (if you are using CocoaPods):

	```
	bash "$SOURCE_ROOT/Pods/Applanga/Applanga.xcframework/update-settingsfile.sh" "$SOURCE_ROOT/$TARGET_NAME"
	```
	
	or if you are using Swift Package Manager:
	
	```
	bash "${BUILD_DIR%Build/*}/SourcePackages/checkouts/sdk-ios/Applanga.xcframework/update-settingsfile.sh" "$SOURCE_ROOT/$TARGET_NAME"
	```
	
	or if you are integrated the Applanga SDK manually:
	
	```
	bash "$BUILT_PRODUCTS_DIR/$FRAMEWORKS_FOLDER_PATH/Applanga.xcframework/update-settingsfile.sh" "$SOURCE_ROOT/$TARGET_NAME"
	```
	--
	
	Optionally you can also run the update script manually from the command line. Navigate to the `Applanga.framework` directory, where `settingsfile_update.py` is located and run:

	```
	bash update-settingsfile.sh ${YOUR TARGET DIRECTORY PATH}
	```

	To make sure that the script is running and to see when it does or doesnt update, check the build report in the report navigator window in xcode. There you will find logs for each update step.

    If the file is update successfully you shoudl see the log "Settingsfile updated!". If it is already up to date you will see the log "Settingsfile up-to-date".


5. **Disable automatic string update on init**
	
	If you wish to stop the sdk from automatically updating your strings on app launch you can set the following

	```xml
	...
   <key>ApplangaInitialUpdate</key>
	<false/>
	...
	```
	You will still be able to call Applanga.Update() at any time to update your strings

6. **Disable Draft Mode**

    If you wish to create a build that cannot enable draft mode at any time, you can include the following setting to your plist.

	```xml
	...
   <key>ApplangaDraftModeEnabled</key>
	<false/>
	...
	```
	You can also use the following method at runtime

	```
	Applanga.setDraftModeEnabled(bool);
   ```
    This will overide the setting in the plist, but it will not override draft mode being disabled in the applanga dashboard.

7. **Convert Placeholders**

    To convert placeholders between iOS and Android style you need to enable the following in your plist: 
	
	```xml
	...
   <key>ApplangaConvertPlaceholders</key>
	<true/>
	...
   ```

    ***Common placeholders***

    These placeholder will not be converted as they are supported on iOS and Android.

    - Scientific notation `%e` and `%E`
    - `%c` and `%C` Unicode Characters
    - `%f` floating point number
    - `%g` and `%G` computerized scientific notation
    - `%a` and `%A` Floating point numbers
    - Octal integer `%o` (for `%O` see Android to iOS conversion)
    - `%x` and `%X` hexadecimal presentation using lowercase letters (`%x`) or uppercase letters (`%X`)
    - `%d` will remain `%d`
    - Positional placeholder as `%1$s` are converted to `%1$@` and vice-versa

    ***Android placeholders***
    
    - All instances of `%s` and `%S` will be converted to `%@`
    - Unsupported conversion types such as `%h` and `%tY` will convert to default `%@` type.
    - Boolean types `%b` and `%B` will be converted to `%@`
    - `%h` and `%H` are converted to `%@`
    - Positional strings using '<' are supported. "Duke's Birthday: `%1$tm` `%<te`,`%<tY`" results in "Duke's Birthday: `%1$@` `%1$@`,`%1$@`"

8. **Language Mapping**

    You can map a locale to another locale. For example if you don't have `es-CL` added to your dashboard it usually has a fallback to `es`. But if you want to treat `es-CL` as `es-MX` then you could add it to the map. Watch out for the log:
    
    `ApplangaLanguageMap: es-CL is mapped to es-MX`

    Example:

    ```xml
    ...
	<key>ApplangaLanguageMap</key>
	<string>zh-Hant-HK=zh-HK,es-CL=es-MX</string>
    ...
    ```

	The locale is mapped in all places in the sdk, except when used in combination with [custom language fallback](#enable-custom-language-fallback). In this case the custom fallback performed as set in the plist, no additional mapping occurres for the entries in that plist.
    If you have a locale that maps to another locale that has a custom fallback, this would also work, and the custom fallback will be performed after the mapping.

9. **Enable system language fallback**
	
	By default applanga uses a custom device locale order, this plist value makes the SDK iterate over the languages by using the priority set by the system. This order is used when translating strings and performing a fallback when the string wasn't found for a specified language. Then the SDK would try to translate using the next language in the list. The available possibilites are:

	`applanga`: The default SDK order
	`system`: Use the device system order

	```xml
	...
	<key>ApplangaLanguageFallback</key>
	<string>system</string>
	...
	```

10. **Enable custom language fallback**<a name="enable-custom-language-fallback"></a>
	
	This plist value is a dictionary which allows to set a custom fallback per language. When the SDK would need to translate a key with a specified language, it uses the order as provided. This overrides any other system or default fallbacks only for those languages. Other languages work according to the fallback specified using the ApplangaLanguageFallback value (or default if it's not set). The fallback is only overriden for the top level language, so it's not possible to "nest" the custom fallbacks.

	Example
	```xml
	...
	<key>ApplangaCustomLanguageFallback</key>
	<dict>
		<key>es-MX</key>
		<array>
			<string>es-MX</string>
			<string>es-US</string>
			<string>es</string>
		</array>
		<key>en-US</key>
		<array>
			<string>en-GB</string>
			<string>de-DE</string>
		</array>
	</dict>
	...
	```

11. **Wait on App Start**

    In order to receive the latest strings from your Applanga dashboard into your app, the sdk will wait until the initial update has finished, this causes up to a 10 second delay (typically faster) when starting.If the setting is set to Yes. If youd like this to happen in the background you can add the key `ApplangaWaitOnAppStart` and set it to NO as in the following example to your info.plist. The Applanga SDK will not delay the appstart but that comes with the downside that initial screens my not have the latest over the air strings. So if you enable this you should make sure that your settingsfile is up to date before a release and be aware that some outdated strings may be displayed.  

	 Example:

    ```xml
    ...
	<key>ApplangaWaitOnAppStart</key>
	<false/>
    ...
    ```

12. **Automatic upload of a tag with current app strings**

	In case you would like to upload a tag with all the local strings in your app, add the following key in the plist
    
	```xml
    ...
	<key>ApplangaTagLocalStringsPrefix</key>
	<string>some_tag</string>
    ...
    ```

	This plist value would be used as the tag prefix combined with the bundle version (for example some_tag1), then when you are running with the app with the debugger connected, an automatic tag upload would be performed after Applanga.update(), which is also done on app start. The tag would be created on the dashboard if it doesn't exist yet.

	It's possible to combine this option with the `ApplangaAdditionalStringFiles`, and with `ApplangaAdditionalFrameworks` keys to include strings also from those places

13. **Use supported language as screenshot language value**

	By default, when uploading a screenshot using the SDK,
	it sets the language of the screenshot as the current preferred device locale 
	(if it was mapped, or overriden with Applanga.setLanguage then that value will be used).
	It is possible to make the sdk set the actual language used for localizing the strings,
	by adding the following key in the plist:
    
	```xml
    ...
	<key>ApplangaScreenshotUseSupportedLanguageFallback</key>
	<true/>
    ...
    ```

	When set to `true`, the value will be the first supported language in the fallback list. 


## Automatic Push Notification Localization and InfoPlist strings

With the Applanga SDK you can only localize local notifications because remote notifications, the app display name (CFBundleDisplayName) as well as the several other NS*UsageDescription etc strings defined in your Info.plist are not using the app runtime and therefore can not be localized at runtime with a SDK. For these kind of strings you can use the [Applanga Command Line Interface](https://www.applanga.com/docs-integration/cli) to manage the strings on the [Applanga Dashboard](https://dashboard.applanga.com) and update the InfoPlist.strings files whenever you create a new build.

For more details on that please have a look at our blogpost on [Translating Push Notifications and Info.plist localization](https://www.applanga.com/blog/infoplist-strings-and-ios-push-notification-localization-automation/).

## SwiftUI

To use Applana with SwiftUI please include the ApplanaSwiftUI framework into your project, follow the integration instructions in the [Readme](https://github.com/applanga/sdk-swiftui/blob/main/README.md).

If you would like to keep using only the base Applanga framework, you could localize Text components using this extention:

```swift
	//First add this extention to your project:
	extension Text {
	    init(applangaKey : String){
	        self.init(NSLocalizedString(applangaKey, tableName: nil, bundle: Bundle.main, value: "", comment:""))
	    }
	    init(applangaKey : String, defaultValue : String){
	        self.init(NSLocalizedString(applangaKey, tableName: nil, bundle: Bundle.main, value: defaultValue, comment:""))
    	}
	}
	
	//Then localise a text like so:
	
	Text(applangaKey: "hello_world")
	
	//or
	
   	Text(applangaKey: "hello_world", defaultValue: "Hello World")

```
### SwiftUI Screenshots
The best method to take screenshots for your translations with SwiftUI is doing your screenshots within UITests as described in [Automated during UITests](#Automated-during-UITests).

To enable the collection of string positions on your screen with SwiftUI you need to enable the applanga ID mode, which means that every string will shown by its ID and not by its localization. This is the only method to be 100% accurate on linking the correct ids with their positions to the screenshot.
To enable the applanga show ID mode pass the parameter to your ApplangaUITest instance:

```swift
    let app = XCUIApplication()
    let applangaUITest = ApplangaUITest(app: app, enableShowIdMode: true)
    app.launch()
```

A good practice is to take all your screenshots with show id mode enabled once and then take all screenshots without the show id mode. Then all screenshots have the correct translations linked to them and you still can see the screenshot with the actual translations.

## WatchOS 

While screenshots and the draft mode menu are not available, string upload and automatic storyboard translation work in WatchOS targets, just follow these extra steps to get it working.

**a.** When installing with cocoa pods or SPM you must also apply the applanga sdk to the watch target that ends with the word "extension".  

**b.** Make sure that any storyboard or string file you want to localise is also a member of the extension target.

**c.** Add the name of the string file or storyboard that you want to localise to the info.plist of the extension target. For example if you are localising the Interface.storyboard, then add it like so: 
`key="ApplangaAdditionalStringFiles" value="Interface".`

**d.** In the info.plist of your watch extension target, add the following entry: `key="ApplangaAdditionalFrameworks" value="NAME OF YOUR PROJECT WatchKit App".`

## MacOS 

While screenshots and the draft mode menu are not available, string upload and automatic storyboard translation work in MacOS targets, just install as you would the iOS sdk and use as normal.
	
## TV OS

Automatic translations will work on TV OS without requiring any special changes. 

To present the draft mode, use the following code :

```swift
	Applanga.showDraftModeDialog()
```

after the draft mode has been enabled, you can present the test menu overlay:
```swift
	Applanga.setScreenShotMenuVisible(true)
```

## Branching

If your project is a branching project use at least SDK version 2.0.205 and update your settings file.
The settings file defines the default branch for your current app.
This branch is used on app start and for update calls.
To be sure branching is working look for the log line: `Branching is enabled.`

To learn more about branching please have a look [here](www.applanga.com/docs/advanced-features/branching).

### Draft Mode

When enabling the Draft Mode you can switch your branch at runtime - an app restart is required.
You also can use our draft overlay to switch your current branch.
Every screenshot you take is linked to the current branch.

### Production Apps

Already published apps that still use settings files without branching and older SDKs will still work and they will use the default branch defined on the Applanga dashboard.

 
## Privacy Manifest

The SDK includes a privacy manifest which declares these items, all of which marked as `tracking`=`NO`:

### API Usage
 - `NSPrivacyAccessedAPICategoryUserDefaults` - UserDefaults is only used to save SDK internal state, for example if the draft mode was enabled.

 ### Collected Data
 - `NSPrivacyCollectedDataTypeOtherDiagnosticData` - The SDK sends data when it detects runtime exceptions. The data contains SDK internal values and stack traces.
 - `NSPrivacyCollectedDataTypeDeviceID` - The `identifierForVendor` is used to count MAU


