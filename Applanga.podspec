Pod::Spec.new do |s|
  s.name                = "Applanga"
  s.version             = "2.0.236"
  s.summary             = "This is the Applanga SDK"
  s.description         = "This is the final CocoaPods release of the Applanga SDK. Future versions ship via Swift Package Manager only: https://github.com/applanga/sdk-ios"
  s.deprecated          = true
  s.homepage            = "http://applanga.com"
  s.license             = { :type => 'Commercial', :file => 'LICENSE' }
  s.author              = { "Mbaas Development GmbH" => "developer@applanga.com" }
  s.source              = { :git => "https://github.com/applanga/sdk-ios.git", :tag => "2.0.236" }
  s.library             = 'sqlite3', 'z'
  s.vendored_frameworks = ""
  s.requires_arc        = true

  s.ios.deployment_target = '15.0'
  s.ios.vendored_frameworks = 'Applanga.xcframework'

  s.watchos.deployment_target   = '9.0'
  s.watchos.preserve_paths      = 'ApplangaWatchOS.framework'
  s.watchos.public_header_files = 'ApplangaWatchOS.framework/Headers/Applanga.h'
  s.watchos.source_files        = 'ApplangaWatchOS.framework/Headers/Applanga.h'
  s.watchos.vendored_frameworks = 'ApplangaWatchOS.framework'

  s.osx.deployment_target = '12.0'
  s.osx.vendored_frameworks = 'ApplangaOSX.framework'

  s.tvos.deployment_target = '15.0'
  s.tvos.vendored_frameworks = 'Applanga.xcframework'
end


