import XCTest
import Foundation
import UIKit
//wait(for: [applangaUITest.takeScreenshot(tag: "Home")], timeout: 10.0)
public class ApplangaUITest {
    private final var enableUITestsLaunchArg = "ApplangaUITestScreenshotEnabled";
    private final var enableShowIdModeLaunchArg = "ApplangaShowIdModeEnabled";
    
    fileprivate let darwinNotificationCenter: CFNotificationCenter
    fileprivate let prefix: String = "com.applanga:"
    fileprivate let tagScreenshotStart = "screenshot_start"
    fileprivate let tagScreenshotDone = "screenshot_done_"
    var app: XCUIApplication
    var expectationDict: [String: XCTestExpectation] = [:]
    private var rawPointerToSelf: UnsafeRawPointer {
        return UnsafeRawPointer(Unmanaged.passUnretained(self).toOpaque())
    }
    
    public init(app: XCUIApplication, enableShowIdMode: Bool = false) {
        self.app = app
        darwinNotificationCenter = CFNotificationCenterGetDarwinNotifyCenter()
        app.launchArguments.append(enableUITestsLaunchArg)
        if(enableShowIdMode){
            app.launchArguments.append(enableShowIdModeLaunchArg)
        }
    }
    
    public func takeScreenshot(tag: String) -> XCTestExpectation{
       let uuid = UUID().uuidString
        let screenshotInfo = getScreenshotInfo(tag: tag, uuid: uuid)
        
        let expectation = XCTestExpectation(description: "Taking screenshot for tag: \(tag)")
        expectationDict[uuid] = expectation
        
        registerScreenshotCallback(uuid: uuid)
        
        var jsonString = "";
        if let json = try? JSONEncoder().encode(screenshotInfo) {
            jsonString = String(data: json, encoding: .utf8)!
        }
        let pasteBoard = UIPasteboard.general
        jsonString = "applanga:" + jsonString
        pasteBoard.string = jsonString;
        
        sleep(1)
        
        CFNotificationCenterPostNotification(darwinNotificationCenter,
                                             CFNotificationName(prefix + tagScreenshotStart as CFString),
                                             nil,
                                             nil,
                                             true)
        return expectation
    }
    
    private func registerScreenshotCallback(uuid: String) {
            CFNotificationCenterAddObserver(self.darwinNotificationCenter,
                                            self.rawPointerToSelf,
                                            handleDarwinNotification,
                                            (prefix + tagScreenshotDone + uuid)  as CFString,
                                            nil,
                                            .coalesce)
            
    }
    
    fileprivate func handleNotification(name: String) {
        let screenshotDonePrefix = prefix + tagScreenshotDone
        if(name.hasPrefix(screenshotDonePrefix)){
            let uuid = String(name.dropFirst(screenshotDonePrefix.count));
            expectationDict[uuid]?.fulfill()
        }
    }
    
    
    private func getScreenshotInfo(tag: String, uuid:String) -> ScreenshotInfo{
        let debugDesc = app.debugDescription
        var idsAndPosDict: [String: String] = [:]
        func matchAndAdd(pattern: String){
            let regex = try! NSRegularExpression(pattern: pattern);
            let matches = regex.matches(in: debugDesc,
                                        range: NSRange(debugDesc.startIndex..., in: debugDesc));
            for(match) in matches{
                guard let posRange = Range(match.range(at: 2), in: debugDesc) else {
                    continue
                }
                guard let labelRange = Range(match.range(at: 3), in: debugDesc) else {
                    continue
                }
                let pos = String(debugDesc[posRange]);
                let label = String(debugDesc[labelRange]);
                idsAndPosDict[label] = pos;
            }
        }
        matchAndAdd(pattern: "StaticText,(\\s|[0-9]|x|[a-f])+,\\s(\\{\\{.*\\}\\}),\\slabel:\\s\\'(.*)\\'")
        matchAndAdd(pattern: "Button,(\\s|[0-9]|x|[a-f])+,\\s(\\{\\{.*\\}\\}).*label:\\s\\'([^']*)")
        
        return ScreenshotInfo(tag: tag, uuid: uuid, idsAndPos: idsAndPosDict)
    }
    

}

struct ScreenshotInfo: Codable {
    let tag: String
    let uuid: String
    let idsAndPos: [String: String]
}

private func handleDarwinNotification(notificationCenter: CFNotificationCenter?,
                              observer: UnsafeMutableRawPointer?,
                              notificationName: CFNotificationName?,
                              unusedObject: UnsafeRawPointer?,
                              unusedUserInfo: CFDictionary?) -> Void {
    guard let observer = observer,
          let notificationName = notificationName else {
              return
          }
    let utils = Unmanaged<ApplangaUITest>.fromOpaque(observer).takeUnretainedValue()
    let name = (notificationName.rawValue as String)
    utils.handleNotification(name: name)
    
}

public enum ApplangaUITestError: Error {
    case notInitialisedBeforeAppLaunch
}

