// swift-tools-version:5.3

//  Package.swift

import PackageDescription
let package = Package(
    name: "Applanga",
    products: [
        .library(
            name: "Applanga",
            targets: ["Applanga"]),
        .library(
            name: "ApplangaUITest",
            targets: ["ApplangaUITest"]),
            
    ],
    targets: [
        .binaryTarget(name: "Applanga",
			path: "Applanga.xcframework"),
        .target(
            name: "ApplangaUITest",
            dependencies: []),
    ]
)
