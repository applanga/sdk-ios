// swift-tools-version:5.3

//  Package.swift


import PackageDescription
let package = Package(
    exclude: [
                "Applanga.framework",
                "Applanga.json",
                "Applanga.podspec",
                "CHANGELOG.md",
                "LICENSE"
            ],
    name: "applanga",
    products: [
        .library(
            name: "Applanga",
            targets: ["Applanga"])
            
    ],
    targets: [
        .binaryTarget(name: "Applanga", 
			path: "Applanga.xcframework"),
    ]
)
