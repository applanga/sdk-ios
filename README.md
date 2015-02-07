#Applanga SDK for iOS
***
*Version:* 1.0.0

*URL:* <http://applanga.com> 
***

##Installation
####CocoaPods [[?](http://cocoapods.org)]

1. Refer to CocoaPod’s [Getting Started Guide](http://cocoapods.org/#getstarted) for detailed instructions about Cocoapods.

2. Once you have created your Podfile, insert this line of code: pod 'Applanga'

3. Once you have done so, re-run pod install from the command line.
	
####Manual (zero-code)

1. After you’re signed in, you’ll be able to download the Applanga iOS SDK. Unzip it, then drag and drop Applanga.framework into your project. You’ll probably want to check the Copy items into destination group’s folder (if needed) option.Add the Applanga Framework

2. Add Security.framework and CFNetwork.framework to your list of libraries. To do this, click on your project, then the Build Phases tab, expand the Link Binary With Libraries, and click the plus symbol (+).

3. Under the Build Settings tab, you need to change Basic to All and search for Other Linker Flags. Double click on the white space to the right of Other Linker Flags and a popup will open.Other Linker Flags Click the plus (+), and add -ObjC. 
 
##Configuration
1. Download the Applanga Settings file for your app from the Applanga App Overview by clicking [download settings]. (The Filename should reflect your bundle id or package name with the ending applanga)
 
2. Add the settings file to your Apps Resources it will be automatically loaded if the name matches your bundle id.

3. **Optional: ** If you want to use a settingsfile for One or more Apps with a different bundle/package name. you can do so by specifying the name of the applanga settings file in your Info.plist under the key **ApplangaSettingsFilename**
 
4. Now if you start your app you should see a log message that tells you that Applanga was initialized or a Warning message in case of a missing Configuration.

##Usage