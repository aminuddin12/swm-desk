#import "MacStatusBarLogViewer.h"
#import <AppKit/AppKit.h>
#import <Foundation/Foundation.h>
#include <QCoreApplication>
#include <QMetaObject>

@interface MacStatusBarHandler : NSObject
@property (assign) MacStatusBarLogViewer *viewer;
- (void)onQuit:(id)sender;
- (void)onClear:(id)sender;
@end

@implementation MacStatusBarHandler
- (void)onQuit:(id)sender {
    QCoreApplication::quit();
}
- (void)onClear:(id)sender {
    (void)sender;
}
@end

MacStatusBarLogViewer::MacStatusBarLogViewer(std::shared_ptr<IEventBus> eventBus)
    : bus(eventBus), statusItem(nullptr), menuHandler(nullptr) {
}

MacStatusBarLogViewer::~MacStatusBarLogViewer() {
    if (bus) {
        bus->unsubscribe(token);
    }
    if (statusItem) {
        NSStatusItem *item = (__bridge_transfer NSStatusItem *)statusItem;
        [[NSStatusBar systemStatusBar] removeStatusItem:item];
    }
    if (menuHandler) {
        MacStatusBarHandler *handler = (__bridge_transfer MacStatusBarHandler *)menuHandler;
        (void)handler;
    }
}

void MacStatusBarLogViewer::initialize() {
    if (!bus) {
        return;
    }
    
    MacStatusBarHandler *handler = [[MacStatusBarHandler alloc] init];
    handler.viewer = this;
    menuHandler = (__bridge_retained void *)handler;
    
    dispatch_async(dispatch_get_main_queue(), ^{
        NSStatusItem *item = [[NSStatusBar systemStatusBar] statusItemWithLength:NSVariableStatusItemLength];
        item.button.title = @"SWM";
        statusItem = (__bridge_retained void *)item;
        updateMenu();
    });

    token = bus->subscribe(RuntimeEvent::LogAdded, [this](const std::string &payload) {
        QMetaObject::invokeMethod(QCoreApplication::instance(), [this, payload]() {
            onLogAdded(payload);
        }, Qt::QueuedConnection);
    });
}

void MacStatusBarLogViewer::onLogAdded(const std::string &formattedLog) {
    if (recentLogs.size() >= 5) {
        recentLogs.erase(recentLogs.begin());
    }
    recentLogs.push_back(formattedLog);
    updateMenu();
}

void MacStatusBarLogViewer::updateMenu() {
    if (!statusItem) {
        return;
    }
    
    NSStatusItem *item = (__bridge NSStatusItem *)statusItem;
    NSMenu *menu = [[NSMenu alloc] init];
    
    NSMenuItem *titleItem = [[NSMenuItem alloc] initWithTitle:@"SWM Desk" action:nil keyEquivalent:@""];
    [menu addItem:titleItem];
    [menu addItem:[NSMenuItem separatorItem]];
    
    for (const auto &logStr : recentLogs) {
        NSString *nsStr = [NSString stringWithUTF8String:logStr.c_str()];
        NSMenuItem *logItem = [[NSMenuItem alloc] initWithTitle:nsStr action:nil keyEquivalent:@""];
        [menu addItem:logItem];
    }
    
    [menu addItem:[NSMenuItem separatorItem]];
    
    MacStatusBarHandler *handler = (__bridge MacStatusBarHandler *)menuHandler;
    
    NSMenuItem *clearItem = [[NSMenuItem alloc] initWithTitle:@"Clear Logs" action:@selector(onClear:) keyEquivalent:@""];
    clearItem.target = handler;
    [menu addItem:clearItem];
    
    NSMenuItem *quitItem = [[NSMenuItem alloc] initWithTitle:@"Quit" action:@selector(onQuit:) keyEquivalent:@"q"];
    quitItem.target = handler;
    [menu addItem:quitItem];
    
    item.menu = menu;
}
