#Applanga SDK for iOS
***
*Version:* 1.0.60

*URL:* <http://applanga.com> 
***

##Installation
####CocoaPods [[?](http://cocoapods.org)]

1. Refer to CocoaPod’s [Getting Started Guide](http://cocoapods.org/#getstarted) for detailed instructions about CocoaPods.

2. After you have created your Podfile, insert this line of code: ***pod 'Applanga'***

3. Once you have done so, re-run **pod install** from the command line.
	
####Manual (zero-code)

1. Download the latest release of the Applanga iOS SDK from [Github](https://github.com/applanga/sdk-ios/releases). Unzip it, then drag and drop Applanga.framework into your project. You’ll probably want to check the "Copy items into destination group’s folder (if needed)" option.

2. Under the ***Build Settings*** tab, you need to change ***Basic*** to ***All*** and search for ***Other Linker Flags***. Double click on the white space to the right of Other Linker Flags and a popup will open. Click the plus (+), and add ***-ObjC, -lsqlite3, -lz***. 
 
##Configuration
1. Download the *Applanga Settings File* for your app from the Applanga App Overview in the dashboard by clicking the ***[Prepare Release]*** button and then clicking ***[Get Settings File]***.
 
2. Add the *Applanga Settings File* to your apps resources. It will be automatically loaded.
 
3. Now, if you start your app you should see a log message that confirms that Applanga was initialized or a warning in case of a missing configuration.

---

######*NOTE: To have native iOS dialogs properly translated and to show your supported languages on the Appstore you need to have atleast one .strings file bundled with your app for every language. (The file can be empty)*

---

##Usage
###Basic:

- Once Applanga is integrated and configured it synchronizes your local strings with the Applanga dashboard every time you start your app in [Debug Mode](https://developer.apple.com/library/ios/documentation/ToolsLanguages/Conceptual/Xcode_Overview/UsingtheDebugger.html#//apple_ref/doc/uid/TP40010215-CH57-SW1l) or [Draft Mode](https://applanga.com/#!/docs#draft_on_device_testing) if new missing strings are found. Translations that you have stored in your *"Localizable.strings"* file or in *".strings""* that belong to storyboard or xib files of your app will be sent to the dashboard immediately. Applanga also auto detects your strings in storyboards and in the code once they are used. 
Storyboards should be enabled for [Base Localization](https://developer.apple.com/library/ios/documentation/MacOSX/Conceptual/BPInternational/InternationalizingYourUserInterface/InternationalizingYourUserInterface.html#//apple_ref/doc/uid/10000171i-CH3-SW4). If you have additional *".strings"* files that should be automatically uploaded you can add them in your Info.plist with the key **ApplangaAdditionalStringFiles** as a comma seperated list. You don’t need to use any special code. 
	- With ***Objective-C*** use the native method ***[NSLocalizedStringWithDefaultValue(@"APPLANGA_ID", nil, NSBundle.mainBundle, @"default value", @"")](https://developer.apple.com/reference/foundation/nslocalizedstringwithdefaultvalue?language=objc)*** 
	
	- With ***Swift*** use ***[NSLocalizedString("APPLANGA_ID", value: "default value", comment: "")](https://developer.apple.com/reference/foundation/1418095-nslocalizedstring)*** like you are used to do.


---
######*NOTE: If you do not specifiy a default value the string will not be created on the Applanga dashboard.*
---

###Extended:

Besides the Basic usage Applanga offers support for ***named arguments*** in your strings, ***pluralisation***, ***partial updates*** to save space and bandwith as well as translation of html and javascript content in ```UIWebView``` instances.

1. **Code Localization**
 
	1.1 **Strings** 

		// get translated string for the current device locale
		[Applanga localizedStringForKey:@"APPLANGA_ID" withDefaultValue:@"default value"];

	1.2 **Named Arguments**
                
        // if you pass a string:string dictionary you can get translated string
        // with named arguments. %{someArg} %{anotherArg} etc.
        NSDictionary* args = @{@"someArg": @"awesome",@"anotherArg": @"crazy"};
        [Applanga localizedStringForKey:@"APPLANGA_ID" withDefaultValue:@"default value" andArguments:args]
        
    Example:
    
    *APPLANGA_ID* = *"This value of the argument called someArg is %{someArg} and the value of anotherArg is **%{anotherArg}**. You can reuse arguments multiple times in your text wich is **%{someArg}**, **%{anotherArg}** and **%{someArg}.**"*
    
    gets converted to:
    
    *"This value of the argument called someArg is awesome and the value of anotherArg is crazy. You can reuse arguments multiple times in your text wich is awesome, crazy and awesome."*    
        
	1.3 **Pluralisation**
		
		// get translated string in given pluralisation rule (one)
		[Applanga localizedStringForKey:@"APPLANGA_ID" withDefaultValue:@"default value" andArguments:nil andPluralRule:ALPluralRuleOne]
		
	Available pluralisation rules:
	
		ALPluralRuleZero,
    	ALPluralRuleOne,
    	ALPluralRuleTwo,
    	ALPluralRuleFew,
    	ALPluralRuleMany,
    	ALPluralRuleOther
		
	you can also specify a quantity and Applanga will pick the best pluralisation rule based on: [http://unicode.org/.../language_plural_rules.html	](http://unicode.org/repos/cldr-tmp/trunk/diff/supplemental/language_plural_rules.html)
			
		// get a string in the given quantity
		[Applanga localizedStringForKey:@"APPLANGA_ID" withDefaultValue:@"default value" andArguments:nil andPluralRule:ALPluralRuleForQuantity(quantity)]

		// or get a formatted string with the given quantity
		NSString localizedStringWithFormat:[Applanga localizedStringForKey:@"APPLANGA_ID" withDefaultValue:@"default value" andArguments:nil andPluralRule:ALPluralRuleForQuantity(quantity)], quantity]
		
	In the dashboard you create a **puralized ID** by appending the Pluralisation rule to your **ID** in the following format: ```[zero]```, ```[one]```,```[two]```,```[few]```,```[many]```, ```[other]```.
	
	So the ***zero*** pluralized ID for ***"APPLANGA_ID"*** is ***"APPLANGA_ID[zero]"***
		
2. **Update Content**
	
	To trigger an update call:
	 	
	 	[Applanga updateWithCompletionHandler:^(BOOL success) {
        	//called if update is complete
    	}];
    
    This will request the baselanguage, the development language and the long and short versions of the device's current language. If you are using groups, be aware that this will only update the **main** group.
    	
    To trigger an update for a specific set of groups and languages call:
	 	
	 	NSArray* groups = @[@"GroupA", @"GroupB"];
	 	NSArray* languages = @[@"en", @"de", @"fr"];
	 	
	 	[Applanga updateGroups:groups 
	 			  andLanguages:languages  
	 	 withCompletionHandler:^(BOOL success) {
        		//called if update is complete
    	}];
    
3. **Change Language**
 
  	You can change your app's language at runtime using the following call: 
  	
		BOOL success = [Applanga setLanguage: language];
  	 
  	 *language* must be the iso string of a language that has been added in 	the dashboard. 
  	The return value will be *YES* if the language could be set, or if it already was the 	current language, otherwise it will be *NO*. 
  	The set language will be saved, to reset to the 	device language call:
  		
  		Applanga.setLanguage(nil); 
  	
  	After a successful call you need to reinitialize your UI for the changes to 	take effect, for example you might recreate the root Storyboard controller and present it.
  	
  	The *language* parameter is expected in the format **[language]-[region]** or 	**[language]_[region]** with region being optional. Examples: "fr_CA", "en-us", "de". 
  	
  	If you have problems switching to a specific language you can update your settings file 	or specifically request that language within an update content call (see **2. Update Content**). You can also 	specify the language as a default language to have it requested on each update call (see **Optional settings**).
  			
		+ (void) changeAppLanguage:(NSString *)language {
			[Applanga updateGroups:nil andLanguages:@[language] withCompletionHandler:^( BOOL updateSuccess ){
			
			if(updateSuccess){
				BOOL languageChangedSuccess = [Applanga setLanguage:language];
				
				if(languageChangedSuccess) {
					//recreate ui
				} 
			} 
		}

4. **WebViews**
	
	Applanga can also translate content in your WebViews if it is enabled.
	
	Add ```ApplangaTranslateWebViews``` set to ```YES``` to your Info.plist to enable translation support for all WebViews.
    
    To initalize Applanga for your webcontent you need to initialize Applanga from JavaScript:
	
		<script type="text/javascript">
    		window.initApplanga = function()
    		{if(typeof window.ApplangaNative !== 'undefined'){
        			window.ApplangaNative.loadScript();
      			}else{setTimeout(window.initApplanga, 180);}};
    		window.initApplanga();
		</script>
		
	4.1 **Strings**
		
	The inner text and html of tags wich have a ```applanga-text="APPLANGA_ID"``` attribute will be replaced with the translated value of ***APPLANGA_ID***
	
		<div applanga-text="APPLANGA_ID">
			***This will be replaced with the value of APPLANGA_ID***
		</div>
	
	Alternatively you can call `Applanga.getString('APPLANGA_ID')` directly.
	
	4.2 **Arguments**
	
	You can pass arguments with the ```applanga-args``` attribute.
	By default the arguments are parsed as a comma seperated list wich then will replace fields as %{arrayIndex}.  
	
		<div applanga-text="APPLANGA_ID" applanga-args="arg1,arg2,etc">
			***This will be replaced with the value of APPLANGA_ID***
			***and formatted with arguments***
		</div>
	
	Direct call : `Applanga.getString('APPLANGA_ID', 'arg1,arg2,etc')`
	
	To define a different separator instead of ```,``` e.g. if your arguments contain commas use ```applanga-args-separator```.
	
		<div applanga-text="APPLANGA_ID" applanga-args="arg1;arg2;etc"
		 applanga-args-separator=";">
			***This will be replaced with the value of APPLANGA_ID***
			***and formatted with arguments***
		</div> 
		
	Direct call : `Applanga.getString('APPLANGA_ID', 'arg1,arg2,etc', ';')`
		
	One Dimensional **JSON** Objects can also be used as ***Named Arguments*** if you add ```applanga-args-separator="json"```
 	
		<div applanga-text="APPLANGA_ID" 
		 applanga-args="{'arg1':'value1', 'arg2':'value2', 'arg3':'etc'}"
		 applanga-args-separator="json">
			***This will be replaced with the value of APPLANGA_ID***
			***and formatted with json arguments***
		</div> 
		
	 Direct call : `Applanga.getString('APPLANGA_ID', "{'arg1':'value1', 'arg2':'value2', 'arg3':'etc'}", 'json')`
	
	4.3 **Pluralisation**
		
	To pluralize a html tag you can pass the ```applanga-plural-rule``` attribute with the value ```zero```, ```one```, ```two```, ```few```, ```many``` and ```other```.
	
		<div applanga-text="APPLANGA_ID" applanga-plural-rule="one">
			***This will be replaced with the pluralized value of APPLANGA_ID***
		</div> 
	
	Direct call : `Applanga.getPluralString('APPLANGA_ID', 'one')` or with arguments : 	`applanga.getPluralString('APPLANGA_ID', 'one', 'arg1;arg2;etc', ';')`
		
	You can also pluralize by quantity via ```applanga-plural-quantity```	
		
		<div applanga-text="APPLANGA_ID" applanga-plural-quantity=42>
			***This will be replaced with the pluralized value of APPLANGA_ID***
		</div> 
		
	Direct call : `Applanga.getQuantityString('APPLANGA_ID', 42)` or with arguments : 	`applanga.getQuantityString('APPLANGA_ID', 42, 'arg1;arg2;etc', ';')`	
	
	4.4 **Update Content**
	
	To trigger a content update from a WebView use javascript:
		
		Applanga.updateGroups("GroupA, GroupB", "de, en, fr", function(success){
        	//called if update is complete
    	});		
    	
5. **Automatic Screenshot Upload**
 	
 	To give translators some context for translating strings, the Applanga SDK offers the 	functionality to upload screenshots of your app, while collecting meta data such as the 	currrent language, resolution and the Applanga translated strings that are visible, 	including their positions.
 	Each screenshot will be assigned to a tag. A tag may have multiple screenshots with 	differing core meta data: language, app version, device, platform, OS and resolution. 
 	You can read more here : [Manage Tags](https://applanga.com/#!/docs#manage_tags) and here: 	[Uploading screenshots](https://applanga.com/#!/docs#uploading_screenshots).
 	
 	5.1 **Make screenshots manually**
 	
 	To manually make a screenshot you first have to set your app into [draft mode](https://applanga.com/#!/docs#draft_on_device_testing).
 	 
 	With your app in draft mode, all you have to do is to make a two finger swipe downwards.
 	This will show the screenshot menu and load a list of [tags](https://applanga.com/#!/docs#manage_tags). 
 	
 	You can now choose a tag and press *capture screenshot* to capture and upload a screenshot including all meta data for the currently visible screen and assign it to the selected tag.
 	Tags have to be created in the dashboard before they are available in the screenshot menu.
 	
 	5.2 **Display screenshot menu programmatically**
 	
 	You also have the option to open the screenshot menu programmatically, this also requires the app to be in draft mode:
 		
		[Applanga setScreenShotMenuVisible:YES]
 				
 	5.3 **Make screenshots programmatically**
 	
 	To create a screenshot programmatically you call the following function:
 	
		NSString* tag = @"MainMenu";
		NSArray* applangaIDs = [NSArrayarrayWithObjects:@"String1",@"String2",@"String3",nil];
		[Applanga captureScreenshotWithTag:tag andIDs:applangaIDs];
			
 	The Applanga SDK tries to find all IDs on the screen but you can also pass additional IDs in the **applangaIDs** parameter. 
 	
 	5.4 **Automated during UITests**
 	
 	To capture screenshots from UITests running in xcode you first have to add a specific launch argument in your test classes setup function:
 	
		- (void)setUp {
			[super setUp];
			XCUIApplication *app =[[XCUIApplication alloc] init];
			app.launchArguments = @[@"ApplangaUITestScreenshotEnabled"];
			[app launch];
		}
 	
 	Now you can capture screenshots as shown in the following example:

		- (void)testExample2 {

    		XCUIApplication *app = [app init];
    
    		//open screenshot menu by tapping invisible Applanga button
    		[app.buttons[@"Applanga.ToggleScreenShotMenu"] tap];
    		//toggle tag selection
    		[app.buttons[@"Applanga.SelectTag"] tap];
    		//select tag named "MainMenu"
    		[app.tables.staticTexts[@"MainMenu"] tap];
    		//capture screenshot
    		[app.buttons[@"Applanga.CaptureScreen"] tap];
    
    		//screenshot upload takes a while so we need to wait until the screenshot menu is visible again until we can proceed
    		NSPredicate *waitPredicate = [NSPredicate predicateWithFormat:@"exists == 1"];
    		[self expectationForPredicate:waitPredicate evaluatedWithObject:app.buttons[@"Applanga.SelectTag"] handler:nil];
    		[self waitForExpectationsWithTimeout:30 handler:nil];
    		...
    	}		
 	
    	
##Optional settings

You can specify a set of default groups and languages in your plist, which will be updated on every Applanga.update() or Applanga.updateGroups() call. These groups and languages will be added to any that are specified in the call itself, they will *always* be requested.
	The Parameter value must be a string, with a list of groups or languages separated by commata.

1. **Specify default groups**

        		...
        		<key>ApplangaUpdateGroups</key>
            	<string>turorial,chapter1,chapter2</string>
            	...        
	
2. **Specify default languages**

        		...
        		<key>ApplangaUpdateLanguages</key>
            	<string>en,de-at,fr</string>
            	...
            	
3. **Disable upload of storyboard strings**
	You have the option to disable the collection of storyboard strings, by setting this value 	to false. This will not prevent the upload of localized .strings files that you may have 	created for your storyboard, but will stop the default upload of the cryptic string ids 	that are created for text ui elements in the storyboard.
	
				...
        		<key>ApplangaCollectStoryBoardStrings</key>
            	<false/>
            	...
            	
