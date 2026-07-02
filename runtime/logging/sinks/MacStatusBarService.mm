#import "MacStatusBarService.h"
#import <AppKit/AppKit.h>
#import <Foundation/Foundation.h>
#include <QCoreApplication>
#include <QMetaObject>

@interface MacStatusBarServiceHandler : NSObject
@property (assign) MacStatusBarService *service;
- (void)onQuit:(id)sender;
- (void)onClearLogs:(id)sender;
- (void)onOpenLogViewer:(id)sender;
@end

@implementation MacStatusBarServiceHandler
- (void)onQuit:(id)sender {
    (void)sender;
    QCoreApplication::quit();
}
- (void)onClearLogs:(id)sender {
    (void)sender;
}
- (void)onOpenLogViewer:(id)sender {
    (void)sender;
}
@end

MacStatusBarService::MacStatusBarService(std::shared_ptr<IEventBus> eventBus)
    : bus(eventBus), statusItem(nullptr), menuHandler(nullptr) {
    recentLogs = {
        "Application Started",
        "Runtime Initialized",
        "Logger Ready",
        "Configuration Loaded",
        "UI Started"
    };
}

MacStatusBarService::~MacStatusBarService() {
    shutdown();
}

void MacStatusBarService::initialize() {
    MacStatusBarServiceHandler *handler = [[MacStatusBarServiceHandler alloc] init];
    handler.service = this;
    menuHandler = (__bridge_retained void *)handler;

    dispatch_async(dispatch_get_main_queue(), ^{
        NSStatusItem *item = [[NSStatusBar systemStatusBar] statusItemWithLength:NSVariableStatusItemLength];
        item.button.title = @"⚡ SWM";
        statusItem = (__bridge_retained void *)item;
        updateMenu();
    });
}

void MacStatusBarService::start() {
    if (bus) {
        token = bus->subscribe(RuntimeEvent::LogAdded, [this](const std::string &payload) {
            QMetaObject::invokeMethod(QCoreApplication::instance(), [this, payload]() {
                onLogAdded(payload);
            }, Qt::QueuedConnection);
        });
    }
}

void MacStatusBarService::stop() {
    if (bus) {
        bus->unsubscribe(token);
    }
}

void MacStatusBarService::shutdown() {
    stop();
    if (statusItem) {
        NSStatusItem *item = (__bridge_transfer NSStatusItem *)statusItem;
        [[NSStatusBar systemStatusBar] removeStatusItem:item];
        statusItem = nullptr;
    }
    if (menuHandler) {
        MacStatusBarServiceHandler *handler = (__bridge_transfer MacStatusBarServiceHandler *)menuHandler;
        (void)handler;
        menuHandler = nullptr;
    }
}

void MacStatusBarService::onLogAdded(const std::string &logMessage) {
    if (recentLogs.size() >= 5) {
        recentLogs.erase(recentLogs.begin());
    }
    recentLogs.push_back(logMessage);
    updateMenu();
}

void MacStatusBarService::updateMenu() {
    if (!statusItem) {
        return;
    }

    NSStatusItem *item = (__bridge NSStatusItem *)statusItem;
    NSMenu *menu = [[NSMenu alloc] init];

    NSMenuItem *titleItem = [[NSMenuItem alloc] initWithTitle:@"⚡ SWM Runtime" action:nil keyEquivalent:@""];
    [titleItem setEnabled:NO];
    [menu addItem:titleItem];

    NSMenuItem *statusItemRow = [[NSMenuItem alloc] initWithTitle:@"Status: 🟢 Running" action:nil keyEquivalent:@""];
    [statusItemRow setEnabled:NO];
    [menu addItem:statusItemRow];

    [menu addItem:[NSMenuItem separatorItem]];

    NSMenuItem *logsTitle = [[NSMenuItem alloc] initWithTitle:@"Recent Logs" action:nil keyEquivalent:@""];
    [logsTitle setEnabled:NO];
    [menu addItem:logsTitle];

    for (const auto &logStr : recentLogs) {
        NSString *nsStr = [NSString stringWithUTF8String:logStr.c_str()];
        NSMenuItem *logItem = [[NSMenuItem alloc] initWithTitle:nsStr action:nil keyEquivalent:@""];
        [logItem setEnabled:NO];
        [menu addItem:logItem];
    }

    [menu addItem:[NSMenuItem separatorItem]];

    MacStatusBarServiceHandler *handler = (__bridge MacStatusBarServiceHandler *)menuHandler;

    NSMenuItem *openLogViewerItem = [[NSMenuItem alloc] initWithTitle:@"Open Log Viewer" action:@selector(onOpenLogViewer:) keyEquivalent:@""];
    openLogViewerItem.target = handler;
    [menu addItem:openLogViewerItem];

    NSMenuItem *clearLogsItem = [[NSMenuItem alloc] initWithTitle:@"Clear Memory Logs" action:@selector(onClearLogs:) keyEquivalent:@""];
    clearLogsItem.target = handler;
    [menu addItem:clearLogsItem];

    [menu addItem:[NSMenuItem separatorItem]];

    NSMenuItem *quitItem = [[NSMenuItem alloc] initWithTitle:@"Quit SWM Desk" action:@selector(onQuit:) keyEquivalent:@"q"];
    quitItem.target = handler;
    [menu addItem:quitItem];

    item.menu = menu;
}
