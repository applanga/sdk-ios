#Applanga SDK for iOS
***
*Version:* 1.0.34

*URL:* <http://applanga.com> 
***

##Installation
####CocoaPods [[?](http://cocoapods.org)]

1. Refer to CocoaPod’s [Getting Started Guide](http://cocoapods.org/#getstarted) for detailed instructions about Cocoapods.

2. After you have created your Podfile, insert this line of code: ***pod 'Applanga'***

3. Once you have done so, re-run **pod install** from the command line.
	
####Manual (zero-code)

1. Download the latest release of the Applanga iOS SDK from [Github](https://github.com/applanga/sdk-ios/releases). Unzip it, then drag and drop Applanga.framework into your project. You’ll probably want to check the "Copy items into destination group’s folder (if needed)" option.

2. Under the ***Build Settings*** tab, you need to change ***Basic*** to ***All*** and search for ***Other Linker Flags***. Double click on the white space to the right of Other Linker Flags and a popup will open. Click the plus (+), and add ***-ObjC***. 
 
##Configuration
1. Download the Applanga *settingsfile* for your app from the Applanga App Overview in the dashboard by clicking ***[Download Settings]***.
 
2. Add the *settingsfile* to your apps resources. It will be automatically loaded.
 
3. Now, if you start your app you should see a log message that confirms that Applanga was initialized or a warning in case of a missing configuration.

##Usage
###Basic:

- Once Applanga is integrated and configured it synchronizes your local strings with the Applanga dashboard every time you start your app or if new missing strings are found. Translations that you have stored in local *".strings"* files in your app will be sent to the dashboard immediately. Applanga also auto detects your strings in storyboards and in the code once they are used. 
Storyboards should be enabled for [Base Localisation](https://developer.apple.com/library/ios/documentation/MacOSX/Conceptual/BPInternational/InternationalizingYourUserInterface/InternationalizingYourUserInterface.html#//apple_ref/doc/uid/10000171i-CH3-SW4).
You don’t need to use any special methods just continue using ***[NSLocalizedString](https://developer.apple.com/library/mac/documentation/Cocoa/Reference/Foundation/Miscellaneous/Foundation_Functions/#//apple_ref/c/macro/NSLocalizedString)*** like you are used to do.


###Extended:

Besides the Basic usage Applanga offers support for ***named arguments*** in your strings, ***pluralisation***, ***partial updates*** to save space and bandwith as well as translation of html and javascript content in ```UIWebView``` instances.

1. **Code Localisation**
 
	1.1 **Strings** 

		// get translated string for the current device locale
        ALLocalizedString(@"APPLANGA_ID");

	1.2 **Named Arguments**
                
        // if you pass a string:string dictionary you can get translated string
        // with named arguments. %{someArg} %{anotherArg} etc.
        NSDictionary* args = [[NSDictionary alloc] init];
        args[@"someArg"] = @"awesome";
        args[@"anotherArg"] = @"crazy";
        ALLocalizedStringWithArgs(@"APPLANGA_ID", args);
        
    Example:
    
    *APPLANGA_ID* = *"This value of the argument called someArg is %{someArg} and the value of anotherArg is **%{anotherArg}**. You can reuse arguments multiple times in your text wich is **%{someArg}**, **%{anotherArg}** and **%{someArg}.**"*
    
    gets converted to:
    
    *"This value of the argument called someArg is awesome and the value of anotherArg is crazy. You can reuse arguments multiple times in your text wich is awesome, crazy and awesome."*    
        
	1.3 **Pluralisation**
		
		// get translated string in given pluralisation rule (one)
		ALLocalizedStringWithPluralRule(@"APPLANGA_ID", ALPluralRuleOne)
		
	Available pluralisation rules:
	
		ALPluralRuleZero,
    	ALPluralRuleOne,
    	ALPluralRuleTwo,
    	ALPluralRuleFew,
    	ALPluralRuleMany,
    	ALPluralRuleOther
		
	you can also specify a quantity and Applanga will pick the best pluralisation rule based on: [http://unicode.org/.../language_plural_rules.html	](http://unicode.org/repos/cldr-tmp/trunk/diff/supplemental/language_plural_rules.html)
			
		// get a string in the given quantity
		ALLocalizedStringWithQuantity(@"APPLANGA_ID", quantity);
		
	In the dashboard you create a **puralized ID** by appending the Pluralisation rule to your **ID** in the following format: ```[zero]```, ```[one]```,```[two]```,```[few]```,```[many]```, ```[other]```.
	
	So the ***zero*** pluralized ID for ***"APPLANGA_ID"*** is ***"APPLANGA_ID[zero]"***
		
2. **Update Content**
	
	To trigger a full update call:
	 	
	 	[Applanga updateWithCompletionHandler:^(BOOL success) {
        	//called if update is complete
    	}];
    	
    To trigger a update for a subset of groups and languages call:
	 	
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
               		
4. **WebViews**
	
	Applanga can also translate content in your WebViews if it is enabled.
	
	Add ```ApplangaTranslateWebViews``` set to ```YES``` to your Info.plist to enable translation support for all WebViews.
    
    To initalize Applanga for your webcontent you need to initialize Applanga from JavaScript:
	
		<script type="text/javascript">
    		var applanga = Applanga({});
		</script>
		
	4.1 **Strings**
		
	The inner text and html of tags wich have a ```applanga-text="APPLANGA_ID"``` attribute will be replaced with the translated value of ***APPLANGA_ID***
	
		<div applanga-text="APPLANGA_ID">
			***This will be replaced with the value of APPLANGA_ID***
		</div>
	
	4.2 **Arguments**
	
	You can pass arguments with the ```applanga-args``` attribute.
	By default the arguments are parsed as a comma seperated list wich then will replace fields as %{arrayIndex}. 
	
		<div applanga-text="APPLANGA_ID" applanga-args="arg1,arg2,etc">
			***This will be replaced with the value of APPLANGA_ID***
			***and formatted with arguments***
		</div>
	
	To define a different separator instead of ```,``` e.g. if your arguments contain commas use ```applanga-args-separator```.
	
		<div applanga-text="APPLANGA_ID" applanga-args="arg1;arg2;etc"
		 applanga-args-separator=";">
			***This will be replaced with the value of APPLANGA_ID***
			***and formatted with arguments***
		</div> 
		
	1 Dimensional **JSON** Objects can also be used as ***Named Arguments*** if you add ```applanga-args-separator="json"```
 	
		<div applanga-text="APPLANGA_ID" 
		 applanga-args="{'arg1':'value1', 'arg2':'value2', 'arg3':'etc'}"
		 applanga-args-separator="json">
			***This will be replaced with the value of APPLANGA_ID***
			***and formatted with json arguments***
		</div> 
	
	4.3 **Pluralisation**
		
	To pluralize a html tag you can pass the ```applanga-plural-rule``` attribute with the value ```zero```, ```one```, ```two```, ```few```, ```many``` and ```other```.
	
		<div applanga-text="APPLANGA_ID" applanga-plural-rule="one">
			***This will be replaced with the pluralized value of APPLANGA_ID***
		</div> 
		
	You can also pluralize by quantity via ```applanga-plural-quantity```	
		
		<div applanga-text="APPLANGA_ID" applanga-plural-quantity=42>
			***This will be replaced with the pluralized value of APPLANGA_ID***
		</div> 	
		
	4.4 **Update Content**
	
	To trigger a content update from a WebView use javascript:
		
		applanga.updateGroups("GroupA, GroupB", "de, en, fr", function(success){
        	//called if update is complete
    	});	
