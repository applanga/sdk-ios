Pod::Spec.new do |s|
  s.name                = "Applanga"
  s.version             = "2.0.153"
  s.summary             = "This is the Applanga SDK"
  s.homepage            = "http://applanga.com"
  s.license             = { :type => 'Commercial', :file => 'LICENSE' }
  s.author              = { "Mbaas Development GmbH" => "developer@applanga.com" }
  s.source              = { :git => "https://github.com/applanga/sdk-ios.git", :tag => "2.0.153" }
  s.library             = 'sqlite3', 'z'
  s.vendored_frameworks = ""
  s.requires_arc        = true

  s.pod_target_xcconfig = { 'EXCLUDED_ARCHS[sdk=iphonesimulator*]' => 'arm64' }
  s.user_target_xcconfig = { 'EXCLUDED_ARCHS[sdk=iphonesimulator*]' => 'arm64' }

  s.ios.deployment_target = '9.0'
  s.ios.frameworks      = 'SystemConfiguration'
  s.ios.preserve_paths      = 'Applanga.framework'
  s.ios.public_header_files = 'Applanga.framework/Headers/Applanga.h'
  s.ios.source_files        = 'Applanga.framework/Headers/Applanga.h'
  s.ios.vendored_frameworks = 'Applanga.framework'

  s.watchos.deployment_target = '2.0'
  s.watchos.preserve_paths      = 'ApplangaWatchOS.framework'
  s.watchos.public_header_files = 'ApplangaWatchOS.framework/Headers/Applanga.h'
  s.watchos.source_files        = 'ApplangaWatchOS.framework/Headers/Applanga.h'
  s.watchos.vendored_frameworks = 'ApplangaWatchOS.framework'

  s.osx.deployment_target = '10.9'
  s.osx.preserve_paths      = 'ApplangaOSX.framework'
  s.osx.public_header_files = 'ApplangaOSX.framework/Headers/Applanga.h'
  s.osx.source_files        = 'ApplangaOSX.framework/Headers/Applanga.h'
  s.osx.vendored_frameworks = 'ApplangaOSX.framework'

end


