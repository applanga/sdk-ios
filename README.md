# Applanga SDK for iOS Localization
***
*Version:* 2.0.147

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


Automatic Push Notification Localization and InfoPlist.strings

## Installation
#### CocoaPods [[?](http://cocoapods.org)]

1. Refer to CocoaPod’s [Getting Started Guide](http://cocoapods.org/#getstarted) for detailed instructions about CocoaPods.

2. After you have created your Podfile, insert this line of code: `pod 'Applanga'`

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
1. To start iOS Localization with Applanga download the *Applanga Settings File* for your app from the App Overview in the dashboard by clicking the ***[Prepare Release]*** button and then clicking ***[Get Settings File]***.
 
2. Add the *Applanga Settings File* to your apps resources. It will be automatically loaded.
 
3. Now, if you start your app you should see a log message that confirms that Applanga was initialized or a warning in case of a missing configuration.

4. To make sure your settings file is always up to date for every build see the doc section about **Automatic Applanga Settings File update** in the **Optional settings**

---

###### *NOTE: To have native iOS dialogs properly translated and to show your supported languages on the Appstore you need to have atleast one .strings file bundled with your app for every language. (The file can be empty)*

---

## Usage
### Basic:

- Once Applanga is integrated and configured it synchronizes your local strings with the Applanga dashboard every time you start your app in [Debug Mode](https://developer.apple.com/library/content/documentation/DeveloperTools/Conceptual/debugging_with_xcode/chapters/debugging_tools.html) or [Draft Mode](https://www.applanga.com/docs/translation-management-dashboard/draft_on-device-testing) if new missing strings are found. Translations that you have stored in your *"Localizable.strings"* file or in *".strings""* that belong to storyboard or xib files of your app will be sent to the dashboard immediately. Applanga also auto detects your strings in storyboards and in the code once they are used.
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

5. **Automatic Screenshot Upload**
 	
 	To give translators some context for translating strings, the Applanga SDK offers the 	functionality to upload screenshots of your app, while collecting meta data such as the 	currrent language, resolution and the Applanga translated strings that are visible, 	including their positions.
 	Each screenshot will be assigned to a tag. A tag may have multiple screenshots with 	differing core meta data: language, app version, device, platform, OS and resolution. 
 	You can read more here : [Manage Tags](https://applanga.com/docs#manage_tags) and here: 	[Uploading screenshots](https://applanga.com/docs#uploading_screenshots).
 	
 	5.1 **Make screenshots manually**
 	
 	To manually make a screenshot you first have to set your app into [draft mode](https://www.applanga.com/docs/translation-management-dashboard/draft_on-device-testing).
 	 
 	With your app in draft mode, all you have to do is to make a two finger swipe downwards.
 	This will show the screenshot menu and load a list of [tags](https://applanga.com/docs#manage_tags).
 	
 	You can now choose a tag and press *capture screenshot* to capture and upload a screenshot including all meta data for the currently visible screen and assign it to the selected tag.
 	Tags have to be created in the dashboard before they are available in the screenshot menu.
 	
 	5.2 **Display screenshot menu programmatically**
 	
 	You also have the option to open the screenshot menu programmatically, this also requires the app to be in draft mode:

	```objc
	//objc
	[Applanga setScreenShotMenuVisible:YES]
	```
	```swift
	//swift
	Applanga.setScreenShotMenuVisible(true)
	```

 	5.3 **Make screenshots programmatically**
 	
 	To create a screenshot programmatically you call the following function:
 	
	```objc
	//objc
	NSString* tag = @"MainMenu";
	NSArray* applangaIDs = [NSArrayarrayWithObjects:@"String1",@"String2",@"String3",nil];
	[Applanga captureScreenshotWithTag:tag andIDs:applangaIDs];
	```
	```swift
	//swift
	var tag:String = "MainMenu"
	var applangaIDs:[String] = ["String1", "String2", "String3"]
	Applanga.captureScreenshot(withTag: tag, andIDs: applangaIDs)
	```
	
	
	if for some reason a text is not tagged or the sdk cannot find the correct tag, you may take a screenshot programmatically using the enableOcr param like so.
	
	```objc
	//objc
	NSString* tag = @"MainMenu";
	[Applanga captureScreenshotWithTag:tag andIDs:nil useOcr:true];
	```
	
	```swift
	//swift
	Applanga.captureScreenshot(withTag: tag, andIDs: null, useOcr: true)
	```
	
	Please note: in most cases enabling OCR is not necessary and will slow down the processing of screenshots for the dashboard, so please only use if needed. Feel free to reach out to applanga support for more info.
	
 	The Applanga SDK tries to find all IDs on the screen but you can also pass additional IDs in the **applangaIDs** parameter. 
 	
 	5.4 **Automated during UITests**
 	
 	To capture screenshots from UITests running in xcode you first have to add a specific launch argument in your test classes setup function:

	```objc
	//objc
	- (void)setUp {
			[super setUp];
			XCUIApplication *app =[[XCUIApplication alloc] init];
			app.launchArguments = @[@"ApplangaUITestScreenshotEnabled"];
			[app launch];
	}
	```

	```swift
	//swift
	override func setUp() {
		super.setUp()
		let app = XCUIApplication();
		app.launchArguments.append("ApplangaUITestScreenshotEnabled");
		app.launch();
	}
    ```

 	Now you can capture screenshots as shown in the following example:
 	
	```objc
	//objc
	- (void)testExample2 {

		XCUIApplication *app = [app init];
	
		//open screenshot menu by tapping invisible Applanga button
		[[app.buttons[@"Applanga.ToggleDraftMenu"] coordinateWithNormalizedOffset:CGVectorMake(0.5, 0.5)] tap];
		[[app.buttons[@"Applanga.ToggleScreenShotMenu"] coordinateWithNormalizedOffset:CGVectorMake(0.5, 0.5)] tap];
		//toggle tag selection
		[[app.buttons[@"Applanga.SelectTag"] coordinateWithNormalizedOffset:CGVectorMake(0.5, 0.5)] tap];
		//select tag named "MainMenu"
		[[app.tables.staticTexts[@"MainMenu"]coordinateWithNormalizedOffset:CGVectorMake(0.5, 0.5)] tap];
		//capture screenshot
		[[app.buttons[@"Applanga.CaptureScreen"] coordinateWithNormalizedOffset:CGVectorMake(0.5, 0.5)] tap];
	
		//screenshot upload takes a while so we need to wait until the screenshot menu is visible again until we can proceed
		NSPredicate *waitPredicate = [NSPredicate predicateWithFormat:@"exists == 1"];
		[self expectationForPredicate:waitPredicate evaluatedWithObject:app.buttons[@"Applanga.SelectTag"] handler:nil];
		[self waitForExpectationsWithTimeout:30 handler:nil];
		...
	}		
	
	  	//if you want to then hide the draft menu again, then do the following
        //Close the screenshot menu
		[[app.buttons[@"Applanga.CancelScreenshot"] coordinateWithNormalizedOffset:CGVectorMake(0.5, 0.5)] tap];
       	//Close the draft menu
		[[app.buttons[@"Applanga.ToggleDraftMenu"] coordinateWithNormalizedOffset:CGVectorMake(0.5, 0.5)] tap];


	
	```

	```swift
	//swift
	func testExample() {
		let app = XCUIApplication();
        
		//open screenshot menu by tapping invisible Applanga button
		app.buttons["Applanga.ToggleDraftMenu"].coordinate(withNormalizedOffset: CGVector(dx: 0.5, dy: 0.5)).tap()
        app.buttons["Applanga.OpenScreenshotView"].coordinate(withNormalizedOffset: CGVector(dx: 0.5, dy: 0.5)).tap()
        app.buttons["Applanga.SelectTag"].coordinate(withNormalizedOffset: CGVector(dx: 0.5, dy: 0.5)).tap()
        app.tables.staticTexts["MainMenu"].tap();
        app.buttons["Applanga.ConfirmScreenshot"].coordinate(withNormalizedOffset: CGVector(dx: 0.5, dy: 0.5)).tap()

		//screenshot upload takes a while so we need to wait until the screenshot menu is visible again until we can proceed
		let predicate = NSPredicate(format: "exists == 1")
        let query = XCUIApplication().buttons["Applanga.SelectTag"];
        expectation(for: predicate, evaluatedWith: query, handler: nil)
        waitForExpectations(timeout: 30, handler: nil)
    }
    
    	//if you want to then hide the draft menu again, then do the following
        //Close the screenshot menu
       	app.buttons["Applanga.CancelScreenshot"].coordinate(withNormalizedOffset: CGVector(dx: 0.5, dy: 0.5)).tap()
       	//Close the draft menu
		app.buttons["Applanga.ToggleDraftMenu"].coordinate(withNormalizedOffset: CGVector(dx: 0.5, dy: 0.5)).tap()

    
    ```
		
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

	The Applanga SDK comes with a python (2.7) script called `settingsfile_update.py` which makes sure your app has always the latest settings file version. The script searches recursively for `*.applanga` files in your project and checks if a newer version is available. If so it replaces the old file with the newer Applanga Settings File from the Applanga backend. 
	
	In XCode you go to `Build Phases` and `New Run Script Phase` and add the following line (if you are using CocoaPods):

	```
	bash "$SOURCE_ROOT/Pods/Applanga/Applanga.framework/update-settingsfile.sh" "$SOURCE_ROOT/$TARGET_NAME"
	```
	
	or if you are using Carthage:

	```
	bash "$SOURCE_ROOT/Carthage/Checkouts/sdk-ios/Applanga.framework/update-settingsfile.sh" "$SOURCE_ROOT/$TARGET_NAME"
	```
	
	or if you are integrated the Applanga SDK manually:
	
	```
	bash "$BUILT_PRODUCTS_DIR/$FRAMEWORKS_FOLDER_PATH/Applanga.framework/update-settingsfile.sh" "$SOURCE_ROOT/$TARGET_NAME"
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
	Applanga.setDraftModelEnabled(bool);
   ```
This will overide the setting in the plist, but it will not override draft mode being disabled in the applanga dashboard.

## Automatic Push Notification Localization and InfoPlist strings

With the Applanga SDK you can only localize local notifications because remote notifications, the app display name (CFBundleDisplayName) as well as the several other NS*UsageDescription etc strings defined in your Info.plist are not using the app runtime and therefore can not be localized at runtime with a SDK. For these kind of strings you can use the [Applanga Command Line Interface](https://www.applanga.com/docs-integration/cli) to manage the strings on the [Applanga Dashboard](https://dashboard.applanga.com) and update the InfoPlist.strings files whenever you create a new build.

For more details on that please have a look at our blogpost on [Translating Push Notifications and Info.plist localization](https://www.applanga.com/blog/infoplist-strings-and-ios-push-notification-localization-automation/).

## SwiftUI

Although not all Applanga features are supported yet in SwiftUI, you can easily localise your text components using this extention:

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
Screenshots uploaded from SwiftUI apps are proccesed server side with OCR to try and read the texts present as it is not possible yet client side. This means that in rare cases they will not be 100% accurate.
	
## WatchOS 

While screenshots and the draft mode menu are not availble, string upload and automatic storyboard translation work in WatchOS targets, just follow these extra steps to get it working.

**a.** When installing with cocoa pods or SPM you must also apply the applanga sdk to the watch target that ends with the word "extension".  

**b.** Make sure that any storyboard or string file you want to localise is also a member of the extension target.

**c.** Add the name of the string file or storyboard that you want to localise to the info.plist of the extension target. For example if you are localising the Interface.storyboard, then add it like so: 
`key="ApplangaAdditionalStringFiles" value="Interface".`

**d.** In the info.plist of your watch extension target, add the following entry: `key="ApplangaAdditionalFrameworks" value="NAME OF YOUR PROJECT WatchKit App".`

## MacOS 

While screenshots and the draft mode menu are not availble, string upload and automatic storyboard translation work in MacOS targets, just install as you would the iOS sdk and use as normal.
	
## TV OS

Automatic translations and draft mode will work on TV OS without requiring any special changes. 

The only feature not avalabile currently is the draft mode screenshot menu.



