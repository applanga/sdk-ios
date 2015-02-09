Pod::Spec.new do |s|
  s.name                = "Applanga"
  s.version             = "1.0.0"
  s.summary             = "This is the iOS SDK for Applanga."
  s.homepage            = "http://applanga.com"
  s.license             = { :type => 'Commercial', :file => 'LICENSE' }
  s.author              = { "Steffen Roemer" => "steffen@applanga.com" }
  s.source              = { :git => "https://github.com/applanga/sdk-ios.git", :tag => "v1.0.0" }
  s.platform            = :ios, '7.0'
  s.framework           = 'SystemConfiguration'
  s.preserve_paths      = 'Applanga.framework'
  s.public_header_files = 'Applanga.framework/Headers/Applanga.h'
  s.vendored_frameworks = 'Applanga.framework'
  s.requires_arc        = true
end