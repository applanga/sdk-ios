Pod::Spec.new do |s|
  s.name                = "ApplangaUITest"
  s.version             = "2.0.201"
  s.summary             = "This is the iOS Testing SDK for Applanga."
  s.homepage            = "http://applanga.com"
  s.license             = { :type => 'Commercial', :file => 'LICENSE' }
  s.author              = { "Mbaas Development GmbH" => "developer@applanga.com" }
  s.source              = { :git => "https://github.com/applanga/sdk-ios.git", :tag => "2.0.201" }
  s.source_files        = 'Sources/ApplangaUITest/*.swift'
  s.requires_arc        = true
  s.module_name = "ApplangaUITest"

  s.ios.deployment_target = '9.0'
  s.swift_versions = '5.0'
  s.framework = 'XCTest'
end
