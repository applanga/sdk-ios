#Applanga SDK for iOS
***
*Version:* 1.0.53

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

- Once Applanga is integrated and configured it synchronizes your local strings with the Applanga dashboard every time you start your app in [Debug Mode](https://developer.apple.com/library/ios/documentation/ToolsLanguages/Conceptual/Xcode_Overview/UsingtheDebugger.html#//apple_ref/doc/uid/TP40010215-CH57-SW1l) or [Draft Mode](https://applanga.com/#!/docs#draft_on_device_testing) if new missing strings are found. Translations that you have stored in local *".strings"* files in your app will be sent to the dashboard immediately. Applanga also auto detects your strings in storyboards and in the code once they are used. 
Storyboards should be enabled for [Base Localization](https://developer.apple.com/library/ios/documentation/MacOSX/Conceptual/BPInternational/InternationalizingYourUserInterface/InternationalizingYourUserInterface.html#//apple_ref/doc/uid/10000171i-CH3-SW4).
You don’t need to use any special code. 
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
        ALLocalizedString(@"APPLANGA_ID", @"default value");

	1.2 **Named Arguments**
                
        // if you pass a string:string dictionary you can get translated string
        // with named arguments. %{someArg} %{anotherArg} etc.
        NSDictionary* args = @{@"someArg": @"awesome",@"anotherArg": @"crazy"};
        ALLocalizedStringWithArgs(@"APPLANGA_ID", @"default value", args);
        
    Example:
    
    *APPLANGA_ID* = *"This value of the argument called someArg is %{someArg} and the value of anotherArg is **%{anotherArg}**. You can reuse arguments multiple times in your text wich is **%{someArg}**, **%{anotherArg}** and **%{someArg}.**"*
    
    gets converted to:
    
    *"This value of the argument called someArg is awesome and the value of anotherArg is crazy. You can reuse arguments multiple times in your text wich is awesome, crazy and awesome."*    
        
	1.3 **Pluralisation**
		
		// get translated string in given pluralisation rule (one)
		ALLocalizedStringWithPluralRule(@"APPLANGA_ID", @"default value", ALPluralRuleOne)
		
	Available pluralisation rules:
	
		ALPluralRuleZero,
    	ALPluralRuleOne,
    	ALPluralRuleTwo,
    	ALPluralRuleFew,
    	ALPluralRuleMany,
    	ALPluralRuleOther
		
	you can also specify a quantity and Applanga will pick the best pluralisation rule based on: [http://unicode.org/.../language_plural_rules.html	](http://unicode.org/repos/cldr-tmp/trunk/diff/supplemental/language_plural_rules.html)
			
		// get a string in the given quantity
		ALLocalizedStringWithQuantity(@"APPLANGA_ID", @"default value", quantity);
		// or get a formatted string with the given quantity
		NSString localizedStringWithFormat:ALLocalizedStringWithQuantity(@"APPLANGA_ID", @"default value", quantity), quantity]
		
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
            	
