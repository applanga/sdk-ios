Pod::Spec.new do |s|
  s.name                = "Applanga"
  s.version             = "1.0.54"
  s.summary             = "This is the iOS SDK for Applanga."
  s.homepage            = "http://applanga.com"
  s.license             = { :type => 'Commercial', :file => 'LICENSE' }
  s.author              = { "Mbaas Development GmbH" => "developer@applanga.com" }
  s.source              = { :git => "https://github.com/applanga/sdk-ios.git", :tag => "1.0.54" }
  s.platform            = :ios, '7.0'
  s.frameworks          = 'SystemConfiguration'
  s.library             = 'sqlite3', 'z'
  s.preserve_paths      = 'Applanga.framework'
  s.public_header_files = 'Applanga.framework/Headers/Applanga.h'
  s.vendored_frameworks = 'Applanga.framework'
  s.requires_arc        = true
end
