#Applanga SDK for iOS
***
*Version:* 1.0.10

*URL:* <http://applanga.com> 
***

##Installation
####CocoaPods [[?](http://cocoapods.org)]

1. Refer to CocoaPod’s [Getting Started Guide](http://cocoapods.org/#getstarted) for detailed instructions about Cocoapods.

2. After you have created your Podfile, insert this line of code: ***pod 'Applanga'***

3. Once you have done so, re-run **pod install** from the command line.
	
####Manual (zero-code)

1. Download the latest release of the Applanga iOS SDK from [Github](https://github.com/applanga/sdk-ios/releases). Unzip it, then drag and drop Applanga.framework into your project. You’ll probably want to check the Copy items into destination group’s folder (if needed) option.

2. Under the ***Build Settings*** tab, you need to change ***Basic*** to ***All*** and search for ***Other Linker Flags***. Double click on the white space to the right of Other Linker Flags and a popup will open. Click the plus (+), and add ***-ObjC***. 
 
##Configuration
1. Download the Applanga *settingsfile* for your app from the Applanga App Overview by clicking ***[Download Settings]***.
 
2. Add the *settingsfile* to your apps resources it will be automatically loaded.
 
3. Now if you start your app you should see a log message that tells you that Applanga was initialized or a warning in case of a missing configuration.

##Usage
Once Applanga is integrated and configured it is synchronizing your local strings with the Applanga dashboard every time you start your app or if new missing strings are found. Translations that you have stored in local *".strings"* files in your app will be sent to the dashboard immediately. Applanga also auto detects your strings in storyboards and in the code once they are used. 
Storyboards should be enabled for [Base Localisation](https://developer.apple.com/library/ios/documentation/MacOSX/Conceptual/BPInternational/InternationalizingYourUserInterface/InternationalizingYourUserInterface.html#//apple_ref/doc/uid/10000171i-CH3-SW4).You don’t need to use any special methods just continue using ***[NSLocalizedString](https://developer.apple.com/library/mac/documentation/Cocoa/Reference/Foundation/Miscellaneous/Foundation_Functions/#//apple_ref/c/macro/NSLocalizedString)*** like you are used to do.
