# Applanga SDK for iOS Localization CHANGELOG
***
*Website:* <https://www.applanga.com> 

*Applanga iOS Documentation:* <https://www.applanga.com/docs-integration/ios> 
***

### Version 2.0.212 (27 Feb 2025)
#### Fixed
- possible crash during network requests

#### Added
- improvements for low disk space

---
### Version 2.0.211 (24 Feb 2025)
#### Fixed
- app freeze on launch when update request fails

---
### Version 2.0.207 (21 Feb 2025)
#### Added
- internal performance improvements

---
### Version 2.0.205 (23 Jan 2025)
#### Added
- smaller bugfixes and internal performance improvements 

---
### Version 2.0.204 (10 Dec 2024)
#### Added
- new plist setting `ApplangaScreenshotUseSupportedLanguageFallback`

---
### Version 2.0.203 (21 Nov 2024)
#### Fixed
- issues with internal exception logging in certain scenarios

---
### Version 2.0.202 (31 Oct 2024)
#### Fixed
- draft mode dialog current branch selection appears blank
- draft mode text font issue
- Locale.preferredLanguages growing indefinitely when setting different languages using Applanga.setLanguage
- handle possible crash during internal sdk exception handling

---
### Version 2.0.200 (9 Oct 2024)
#### Added
- privacy manifest

---
### Version 2.0.198 (17 Sep 2024)
#### Added
- internal changes

---
### Version 2.0.197 (16 Sep 2024)
#### Added
- Fix CHANGELOG.md formatting 

---
### Version 2.0.196 (13 Sep 2024)
#### Added
- internal exception logging

---
### Version 2.0.195 (9 Jul 2024)
#### Fixed
- settings file auto update script causing xcode build failure

---
### Version 2.0.194 (4 Jul 2024)
#### Fixed
- MAU request

---
### Version 2.0.193 (20 Jun 2024)
#### Added
- smaller general code optimizations

#### Fixed
- possible macOS compilation failure when using SPM

---
### Version 2.0.191 (13 May 2024)
#### Added
- tvos draft mode support

---
### Version 2.0.187 (26 Apr 2024)
#### Fixed
- tvos projects compilation failure

---
### Version 2.0.185 (18 Apr 2024)
#### Added
- public method to retrieve available languages on the dashboard

---
### Version 2.0.184 (12 Mar 2024)
#### Added
- improved Appium Screenshot support

#### Fixed
- removed unnecessary warnings for Flutter and React-Native builds
- possible placeholder crash while being in draftmode

---
### Version 2.0.182 (15 Feb 2024)
#### Added
- smaller general code optimizations

#### Fixed
- missing applanga_settings file alert was not showing

---
#### Version 2.0.181 (25 Jan 2024)
#### Added
- smaller general code optimizations

#### Fixed
- missing applanga_settings file alert was not showing

---
#### Version 2.0.181 (25 Jan 2024)
#### Added
- shrinked very first Applanga.update() response
- smaller general code optimizations
#### Fixed
- fixed possible caching issues

---
### Version 2.0.180 (4 Jan 2024)
### Added
- introducing error messages for read-only branches
- smaller general code optimizations

---
### Version 2.0.177 (12 Oct 2023)
#### Added
- option for system language fallback
- more performant settings file handling
- option for custom fallbacks
- option for local string tagging in draft mode

#### Fixed
- new language on the dashboard sync on first app start

--- 
### Version 2.0.174 (20 Jul 2023)
#### Added
- branching support for Flutter and React-Native 

--- 
### Version 2.0.173 (29 Jun 2023)
#### Fixed
- Auto allow pasteboard permission during UI tests screenshot
- Only show a warning for a screenshot when an actual SwiftUI view is in the presented view controller hierarchy 

--- 
### Version 2.0.171 (25 May 2023)
#### Added
- improved settings file handling

--- 
### Version 2.0.170 (28 Mar 2023)
#### Fixed
- fix swiftUI string interpolation

--- 
### Version 2.0.167 (2 Mar 2023)
#### Added
- new Draft Mode dialog

---
### Version 2.0.161 (15 Sep 2022)
#### Fixed
- build issues for carthage and cocoapods related to m1 macbooks
- ui test issues on objective-c

---
### Version 2.0.160 (5 Aug 2022)
#### Fixed
- reduced initial delay lock

#### Added
- minor documentation improvements

---
### Version 2.0.159 (27 Apr 2022)
#### Fixed
- automatic settings file update with macOS Monterey 12.3

---
### Version 2.0.158 (9 Mar 2022)
#### Added
- localizeMap support for empty (null) translations

---
### Version 2.0.157 (1 Mar 2022)
#### Added
- ApplangaUITest package to improve testing + automatic screenshot captures

---
### Version 2.0.155 (17 Feb 2022)
#### Added
- language mapping option 
- zh-Hant-HK support

---
### Version 2.0.154 (20 Jan 2022)
#### Added
- support for placeholder conversion with relative android placeholder such as `%1$tm` `%<te`

---
### Version 2.0.153 (17 Dec 2021)
#### Added
- renamed params for captureScreenshotWithTag and localizedStringForKey to match the apple naming guidelines and deprecated old ones
- Applanga setLanguageAndUpdate()

#### Fixed
- warning on no space for settings file extraction

---
### Version 2.0.151 (6 Oct 2021)

#### Fixed
- recovery if cache gets corrupted or deleted in the background

---

### Version 2.0.150 (28 Sep 2021)

#### Fixed
- warning about missing settings file after iOS 15 update

---

### Version 2.0.149 (2 Sep 2021)

#### Added
- Applanga Show Id Mode
- Applanga Convert Placeholder

#### Fixed
- renamed setDraftModelEnabled to setDraftModeEnabled

---

### Version 2.0.147 (7 Apr 2021)
#### Fixed
- Fix for automated screenshots with new draft mode layout
- Fix for retrieving new language after setLanguage call

---

### Version 2.0.146 (27 Jan 2021)
#### Fixed
- Support for tl language on ios

---

### Version 2.0.145 (6 Jan 2021)
#### Added
- Support for watchOS and MacOS
- Draft menu redesign

---

### Version 2.0.140 (24 Sep 2020)
#### Added
- Error when key is too long
- Added accessibility ids for appium testing

---

### Version 2.0.139 (28 Jul 2020)
#### Added
- Gzip https requests as default
- Optional interface for providing string positions
- Support for swift package manager

---

### Version 2.0.137 (25 May 2020)
#### Added
- Automatic removal of language databases that dont exist on the dashboard

---

### Version 2.0.136 (6 May 2020)
#### Added
- Allow flutter to take screenshots outside of draft mode
- Added ocr option to programmatic screenshots

---

### Version 2.0.135 (9 Apr 2020)
#### Added
- only request supported languages in update

---

### Version 2.0.134 (2 Apr 2020)
#### Added
- setDraftModeEnabled at runtime

---

### Version 2.0.133 (18 Mar 2020)
#### Fixed
- Settingsfile update for Mojave and above

---

### Version 2.0.132 (28 Feb 2020)
#### Added
- Screenshots from apps using swiftUI will now be proccessed with OCR
- Support for flutter OCR screenshots

---

### Version 2.0.131 (30 Jan 2020)
#### Added
- Added screenshot menu support for iOS 13 apps using scene delegates and swiftUI 
- Including strings with missing keys when taking a screen shot
- Added support for apple TvOS
- Sending current language when reporting an issue

---

### Version 2.0.129 (2 Oct 2019)
#### Added
- added check for keys longer than 997 bytes to meet database requirements
- added check for new lines in keys
- added support options for swiftui in documentation
- fix for draft mode dialog in SwiftUI 
- added ApplangaDraftModeEnabled setting

---
### Version 2.0.127 (9 Aug 2019)
#### Fixed

- added ApplangaInitialUpdate setting
- added support for async javascript localization calls in WKWebViews

---
### Version 2.0.126 (18 Jul 2019)
#### Fixed
- added support for sr and sr-Latn

---
### Version 2.0.122 (11 Mar 2019)
#### Fixed
- fixed 1 second freeze on app start

---
### Version 2.0.121 (4 Feb 2019)
#### Fixed
- fixed settingsfile update on path with spaces and quotes

---
### Version 2.0.120 (28 Jan 2019)
#### Fixed
- fixed missing ids in screenshots when using Applanga.localizedString

---
### Version 2.0.118 (22 Jan 2019)
#### Fixed
- settingsfile update fix

---
### Version 2.0.116 (6 Dec 2018)
#### Fixed
- crash on number value response

---
### Version 2.0.115 (23 Oct 2018)
#### Fixed
- properly update only draft changes
- localizeMap do not return ids for untranslated strings

---
### Version 2.0.114 (1 Oct 2018)
#### Fixed
- draftmode dialog not shown on some swift apps


---
### Version 2.0.113 (28 Sep 2018)
#### Added
- method to show draftmode dialog programmatically

---
### Version 2.0.112 (31 Aug 2018)
#### Fixed
- carthage localization integration documentation

---
### Version 2.0.110 (30 Aug 2018)
#### Fixed
- new carthage binary support

---
### Version 2.0.108 (15 Aug 2018)
#### Fixed
- fixed crash on app extension check if UIApplication load is called twice

---
### Version 2.0.107 (14 Aug 2018)
#### Added
- React-Native support

---
### Version 2.0.106 (26 Jul 2018)
#### Fixed
- draft mode not opening because keyWindow not found

---
### Version 2.0.105 (4 Jul 2018)
#### Added
- documentation update for automated push notification localization
- documentation update for App Name localization and Usage description Localization e.g. (CFBundleDisplayName, NSCalendarsUsageDescription, NSPhotoLibraryUsageDescription, NSCameraUsageDescription, NSHealthShareUsageDescription, NSHealthUpdateUsageDescription)

---
### Version 2.0.103 (31 May 2018)
#### Added
- support for delta string updates / smaller response size

---
### Version 2.0.102 (30 May 2018)
#### Added
- support for uploading .string files from linked .frameworks

---
### Version 2.0.97 (28 Mar 2018)
#### Fixed
- screenshot fix for NSAttributedString

---
### Version 2.0.95 (13 Mar 2018)
#### Fixed
- ui test / automatic screenshots are now working again also when the app is running from the commandline

---
### Version 2.0.94 (1 Mar 2018)
#### Fixed
- removed all app extension warnings

---
### Version 2.0.93 (1 Mar 2018)
#### Fixed
- [UIApplication sharedApplication] nil fix

---
### Version 2.0.92 (27 Feb 2018)
#### Fixed
- app extension upload warnings
- ui tests automated screenshots

---
### Version 2.0.90 (6 Feb 2018)
#### Added
- proxy support

---
### Version 2.0.89 (12 Jan 2018)
#### Fixed
- fixed issue that prevented archive due to automatic settingsfile update script

---
### Version 2.0.88 (5 Jan 2018)
#### Added
- carthage build fix

---
### Version 2.0.82 (5 Jan 2018)
#### Added
- automatic settingsfile update
 
---
### Version 2.0.81 (24 Nov 2017)
#### Added
- full bitcode support

---
### Version 2.0.80 (15 Nov 2017)
#### Changed
- xcode9 build support
- added changelog

---
### Version 2.0.75 (25 Aug 2017)
#### Changed
- removed deprecated methods

---
### Version 2.0.74 (23 Aug 2017)
#### Added
- method to get all strings for react native support

---
### Version 2.0.72 (14 Jul 2017)
#### Added
- carthage support

#### Fixed
- debugger detection

---
### Version 2.0.71 (23 May 2017)
#### Fixed
- root window detection

---
### Version 2.0.68 (18 May 2017)
#### Added
- UILabel support in screenshots

---
### Version 2.0.66 (17 May 2017)
#### Changed
- sdk is now a dynamic library

#### Fixed
- Thai support
- argument documentation
- debugger connected log

---
### Version 1.0.63 (5 Apr 2017)
#### Added
- fallback to local strings if device has no memory for settingsfile

---
### Version 1.0.62 (10 Mar 2017)
#### Fixed
- md files 
- indentation
- string position detection in screenshots

---
### Version 1.0.61 (26 Jan 2017)
#### Fixed
- documentation
- screenshot menu allow swipe in both directions
- json parsing

---
### Version 1.0.60 (22 Nov 2016)
#### Updated
- screenshot menu

---
### Version 1.0.56 (10 Nov 2016)
#### Added
- automatic screenshot support

---
### Version 1.0.55 (20 Oct 2016)
#### Changed
- performance improvements

---
### Version 1.0.54 (11 Oct 2016)
#### Changed
- missing string performance improvements

---
### Version 1.0.53 (10 Oct 2016)
#### Fixed
- webview issue

---
### Version 1.0.52 (22 Sep 2016)
#### Fixed
- documentation for manual installation
- documentation for dictionary

---
### Version 1.0.51 (12 Sep 2016)
#### Fixed
- fixed setLanguage string case parsing for zh-Hant & zh-Hans

---
### Version 1.0.43 (25 Aug 2016)
#### Added
- option to disable storyboard string collection

#### Fixed
- setLanguage on pre iOS 9 devices

---
### Version 1.0.42 (13 Jul 2016)
#### Updated
- Unity support
- air sdk version 21 support

---
### Version 1.0.41 (22 Jun 2016)
#### Updated
- setLanguage not case sensitive

---
### Version 1.0.40 (26 May 2016)
#### Updated
- documentation

---
### Version 1.0.39 (25 May 2016)
#### Added
- bitcode support

---
### Version 1.0.38 (16 Feb 2016)
#### Changed
- aligned log output on android and iOS
- only collect missing strings if app is beeing debugged or in draft mode

---
### Version 1.0.37 (14 Jan 2016)
#### Added
- webview support

#### Fixed
- db crash
- adobe air sdk issues
- default language issues

---
### Version 1.0.36 (1 Dec 2015)
####Changed
- method names to be similar to android sdk

#### Added
- setLanguage method

#### Fixed
- hanging if servers are not available
- documentation

---
### Version 1.0.34 (3 Nov 2015)
#### Fixed
- applanga xcii test compatibility
- proper usage of nil and Nil
- groupversionname instead of main
- missingstring collection

---
### Version 1.0.31 (14 Oct 2015)
#### Fixed
- removed usage of CACurrentMediaTime

---
### Version 1.0.21 (13 Oct 2015)
#### Updated
- xcode version settings

---
### Version 1.0.20 (12 Oct 2015)
#### Fixed
- issues with empty strings

---
### Version 1.0.18 (10 Oct 2015)
#### Added
- adobe air support
- group support

#### Fixed
- ssl issues

---
### Version 1.0.17 (30 Jun 2015)
#### Added
- option to disable sending of missing ids
- option to disable draft mode

---
### Version 1.0.16 (24 Jun 2015)
#### Added
- configurable waiting timeouts on app start

---
### Version 1.0.15 (23 Jun 2015)
#### Changed
- extended log output in verbose mode
- log output formatting

---
### Version 1.0.14 (22 Jun 2015)
#### Added
- configurable log options

---
### Version 1.0.13 (9 Jun 2015)
#### Changed
- do not translate ids from other frameworks

---
### Version 1.0.11 (20 Apr 2015)
#### Changed
- only update languages that exist on the dashboard
- documentation updates

---
### Version 1.0.6 (24 Mar 2015)
#### Added
- chinese support

---
### Version 1.0.4 (21 Mar 2015)
#### Fixed
- concurrency issue fixed

---
### Version 1.0.3 (20 Mar 2015)
#### Added
- recursive search for settingsfile

---
### Version 1.0.2 (17 Mar 2015)
#### Added
- draft mode support

#### Fixed
- cleaned up logs
- podfile settings

---
### Version 1.0.1 (13 Mar 2015)
#### Fixed
- minor bugfixes for initial release

---
### Version 1.0.0 (7 Feb 2015)
#### Added
- Initial release of the Applanga SDK for iOS.
